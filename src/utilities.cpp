#include "utilities.h"
#include <iostream>


Inputs input;
Path bestSolution;
int currentReward = -9999; // initialisasi reward

/* BRUTEFORCE ALGORITHM*/
bool hasSequence(const vector<TokenItems>& path, const vector<TokenItems>& sequence) {
    if (path.size() >= sequence.size()) {
        int lenDiff = path.size() - sequence.size();
        for (int i = 0; i <= lenDiff; i++) {
            int j = 0;
            while (j < sequence.size() && path[i + j].token == sequence[j].token) {
                j++;
            }
            if (j == sequence.size()) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

bool hasVisited(vector<Coordinates>& visitedTokens, TokenItems& currentPath) {
    Coordinates position = currentPath.position;
    for (const auto& pos : visitedTokens) {
        if (position.x == pos.x && position.y == pos.y) {
            return true;
        }
    }
    return false;
}

void insertCoor(TokenItems& token, int x, int y){
    token.position.x = x;
    token.position.y = y;
}

Path addToken(Path path, TokenItems item) {
    path.item.push_back(item);
    return path;
}

void findPaths(TokenItems token,
               Path currentSolution,
               bool isVertical,
               vector<Coordinates> visitedToken,
               int remainingMove) {

    if (remainingMove == 0) {
        int reward = 0;
        for (size_t i = 0; i < input.sequence.item.size(); ++i) {
            const auto& seq = input.sequence.item[i];
            if (hasSequence(currentSolution.item, seq)) {
                reward += input.sequence.reward[i];
            }
        }
        if (reward > currentReward) {
            currentReward = reward;
            bestSolution = currentSolution;
        }
    } else {
        if (isVertical) {
            // Moves Downward
            for (int i = token.position.x + 1; i < input.matrix.rows; i++) {
                TokenItems next = input.matrix.item[i][token.position.y];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(next, path, false, visitedToken, remainingMove - 1);
                }
            }

            // Moves upwards
            for (int i = token.position.x - 1; i >= 0; i--) {
                TokenItems next = input.matrix.item[i][token.position.y];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(next, path, false, visitedToken, remainingMove - 1);
                }
            }
        } else {

            // Moves right
            for (int j = token.position.y + 1; j < input.matrix.cols; j++) {
                TokenItems next = input.matrix.item[token.position.x][j];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(next, path, true, visitedToken, remainingMove - 1);
                }
            }

            // Moves left
            for (int j = token.position.y - 1; j >= 0; j--) {
                TokenItems next = input.matrix.item[token.position.x][j];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(next, path, true, visitedToken, remainingMove - 1);
                }
            }
        }

    }
}

void solve(Matrix matrix, Sequences sequences, int bufferSize, int& currentReward, Path& bestSolution){
    for (int i=2;i <=bufferSize;i++){
        for (int j = 0 ; j < matrix.cols;j++){
            Path currentSolution;
            vector<Coordinates> visitedToken;
            TokenItems start = matrix.item[0][j];
            currentSolution = addToken(currentSolution, start);
            visitedToken.clear();
            visitedToken.push_back(start.position);
            findPaths(start,currentSolution,true,visitedToken,i);
        }
    }
}

/* DIPLAYING STRUCTS */
void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            cout << matrix.item[i][j].token << " ";
        }
        cout << endl;
    }
}

void printSequence(Sequences sequence) {
    for (int i = 0; i < sequence.number; i++) {
        cout << YELLOW << "Sequence " << i + 1 << " : " << RESET;
        for (size_t j = 0; j < sequence.item[i].size(); j++) {
            cout << sequence.item[i][j].token;
            if (j < (sequence.item[i].size() - 1)) {
                cout << " ";
            }
        }
        cout << YELLOW << ", Reward: " <<  RESET << sequence.reward[i] << endl;
    }
}

void printInputs(Inputs input) {
    cout << BOLD << MAGENTA << "Data yang akan digunakan" << RESET << endl;
    cout << YELLOW << "Buffer: " << RESET << input.bufferSize << endl;
    cout << YELLOW << "Matrix-width: " << RESET << input.matrix.cols  << YELLOW << " Matrix-height: " << RESET << input.matrix.rows << endl;
    cout << YELLOW << "Matrix: " << RESET << endl;
    printMatrix(input.matrix);
    cout << YELLOW << "Number of sequence: " << RESET << input.sequence.number << endl;
    printSequence(input.sequence);
}

void printPath(const Path& path) {
    for (const auto& tokenItem : path.item) {
        cout << tokenItem.token << " ";
    }
    cout << endl;
    cout << BOLD << BLUE << "Coordinates: " << RESET << endl;
    for (const auto& token : path.item) {
        cout << "(" << token.position.y + 1 << ", " << token.position.x + 1 << ")" << endl;
    }
}



/* RANDOMIZE */
int randomize(int min,int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> range(min,max);

    return range(gen);
}

Tokens getTokens() {
    Tokens tokens;
    cout << GREEN << "Masukkan jumlah token: " << RESET;
    cin >> tokens.jumlah;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');    

    string line;
    cout << GREEN << "Masukkan token dalam satu baris: " << RESET;

    getline(cin,line);
    istringstream iss(line);
    
    string token;
    while (iss >> token)
    {
        tokens.item.push_back(token);
    }
    return tokens; 
}

Matrix getRandomMatrix(Tokens token) {
    Matrix matrix;
    string line;
    cout << GREEN << "Masukkan ukuran matrix (lebar<spasi>tinggi): " << RESET;
    cin >> matrix.cols >> matrix.rows;
    
    // Seed
    shuffle(token.item.begin(), token.item.end(), default_random_engine(time(0)));

    matrix.item.resize(matrix.rows, vector<TokenItems>(matrix.cols));

    for (int i =0; i< matrix.rows;i++){
        for (int j=0; j<matrix.cols;j++){
            int index = randomize(0,token.jumlah-1);
            matrix.item[i][j].token = token.item[index];
            matrix.item[i][j].position.x = i;
            matrix.item[i][j].position.y = j;
        }
    }
    return matrix;
}

Sequences getRandomSequence(Tokens token){
    Sequences sequence;
    int maxSeq;
    cout << GREEN << "Masukkan jumlah sequence: " << RESET;
    cin >> sequence.number;
    
    cout << GREEN << "Masukkan ukuran maksimal sequence: " << RESET;
    cin >> maxSeq;

    // Seed
    shuffle(token.item.begin(), token.item.end(), default_random_engine(time(0)));

    
    for (int i=0;i<sequence.number;i++){
        vector<TokenItems> list;
        int length = randomize(2,maxSeq-1);
        for (int j=0; j < length ; j++){
            int index = randomize(0,token.jumlah-1);
            TokenItems temp;
            temp.token = token.item[index];
            list.push_back(temp);
        }
        sequence.item.push_back(list);

        int points = randomize(-10,50);
        sequence.reward.push_back(points); 
    }

    return sequence;
}

Inputs getRandomInputs(){
    Inputs input;
    Tokens token;
    Matrix matrix;
    Sequences sequence;
    int buffer;
    
    token = getTokens();
    matrix = getRandomMatrix(token);

    // Buffer
    cout << GREEN << "Masukkan panjang buffer: " << RESET;
    cin >> buffer;

    sequence = getRandomSequence(token);

    input.tokens = token;
    input.bufferSize = buffer;
    input.sequence = sequence;
    input.matrix = matrix;
    
    return input;
}

/* FILE HANDLING */
Inputs fileParser() {
    string fileName;
    cout << endl;
    cout << BLUE << "Silahkan masukkan nama file dengan .txt, contoh \'hi.txt\': " << RESET;
    cin >> fileName;
    cout << endl;

    string filepath = "../test/input/" + fileName;
    
    Inputs input;

    ifstream inputFile(filepath, ios::in);

    // Error handling
    if (!inputFile.is_open()) {
        cerr  << BOLD << RED << "File Error" << filepath << RESET << endl;
        return input;
    }

    string line;

    // Read buffer length
    getline(inputFile, line);
    istringstream(line) >> input.bufferSize;

    // Read matrix rows and columns
    getline(inputFile, line);
    istringstream(line) >> input.matrix.cols >> input.matrix.rows;

    // Initialize matrix item vector
    input.matrix.item.resize(input.matrix.rows, vector<TokenItems>(input.matrix.cols));

    // Read matrix
    for (int i = 0; i < input.matrix.rows; i++) {
        getline(inputFile, line);
        istringstream issMatrix(line);
        for (int j = 0; j < input.matrix.cols; j++) {
            issMatrix >> input.matrix.item[i][j].token;
            input.matrix.item[i][j].position.x = i;
            input.matrix.item[i][j].position.y = j;
        }
    }

    // Read number of sequences
    getline(inputFile, line);
    istringstream(line) >> input.sequence.number;

    input.sequence.reward.resize(input.sequence.number);

    // Read sequence and reward
    for (int i = 0; i < input.sequence.number; i++) {
        getline(inputFile, line);
        istringstream iss(line);
        vector<TokenItems> list;
        string code;
        while (iss >> code){
            TokenItems temp;
            temp.token = code;
            list.push_back(temp);
        }
        input.sequence.item.push_back(list);
        getline(inputFile, line);
        istringstream(line) >> input.sequence.reward[i];
    }

    inputFile.close();
    return input;
}




void txtWrite(int reward, Path bestSolution, int duration){
    string fileName;
    cout << endl;
    cout << BLUE << "Silahkan masukkan nama file dengan .txt, contoh \'hi.txt\': " << RESET;
    cin >> fileName;

    string filepath = "../test/output/" + fileName;

    ofstream outputFile(filepath);

    if (!outputFile.is_open()){
        cerr << RED <<  "File error" << filepath << endl;
    } else {
        outputFile << customArt << endl << endl;

        outputFile << "-- MASUKAN DATA -- " << endl;
        outputFile << "Matriks: " << endl;
        for (int i = 0; i < input.matrix.rows; i++) {
            for (int j = 0; j < input.matrix.cols; j++) {
                outputFile << input.matrix.item[i][j].token << " ";
            }
            outputFile << endl;
        }

        outputFile << "Sekuens-sekuens: " << endl;
        for (int i = 0; i < input.sequence.number; i++) {
            outputFile << "Sequence " << i + 1 << " : ";
            for (size_t j = 0; j < input.sequence.item[i].size(); j++) {
                outputFile << input.sequence.item[i][j].token;
                if (j < (input.sequence.item[i].size() - 1)) {
                    outputFile << " ";
                }
            }
            outputFile << ", Reward: " << input.sequence.reward[i] << endl;
        }
        outputFile << endl;
        outputFile << "----- HASIL ALGORITMA ---- " << endl;
        outputFile << "Total hadiah: " << reward << endl;
        outputFile << "Solusi: ";
        
        for (size_t i = 0; i < bestSolution.item.size(); i++){
            outputFile << bestSolution.item[i].token;
            outputFile << " ";
        }
        outputFile << endl;

        outputFile << "Koordinat: " << endl;
        for (size_t i = 0; i < bestSolution.item.size(); i++){
            outputFile << bestSolution.item[i].position.y + 1 << ",";
            outputFile << bestSolution.item[i].position.x + 1 << endl;
        }
        
        outputFile << "Waktu eksekusi: ";
        outputFile << duration << " ms" << endl;

        outputFile.close();
        cout << endl;    
        cout  << UNDERLINE << GREEN << "File berhasil ditulis" << RESET << endl;
    }
}

/* TEXT DECORATION */

const char* customArt = R"(
   ___      _                                 _      ____   ___ _____ _____ 
  / __\   _| |__   ___ _ __ _ __  _   _ _ __ | | __ |___ \ / _ \___  |___  |
 / / | | | | '_ \ / _ \ '__| '_ \| | | | '_ \| |/ /   __) | | | | / /   / / 
/ /__| |_| | |_) \  __/ |  | |_) | |_| | | | |   <   / __/| |_| |/ /   / /  
\____/\__, |_.__/ \___|_|  | .__/ \__,_|_| |_|_|\_\ |_____|\___//_/   /_/   
      |___/                |_|
)";
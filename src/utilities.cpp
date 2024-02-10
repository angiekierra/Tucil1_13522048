#include "struct.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>


// Reading txt 
Inputs fileParser(string filepath) {
    Inputs input;

    ifstream inputFile(filepath, ios::in);

    // Error handling
    if (!inputFile.is_open()) {
        cerr << "File Error" << filepath << endl;
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

// void txtWrite(string filepath, Result result){
//     ofstream outputFile(filepath);

//     if (!outputFile.is_open()){
//         cerr << "File error" << filepath << endl;
//     } else {
//         outputFile << "Total hadiah: " << result.reward << endl;
//         outputFile << "Solusi: ";
        
//         for (size_t i = 0; i < result.solution.item.size(); i++){
//             outputFile << result.solution.item[i].token;
//             outputFile << " ";
//         }
//         outputFile << endl;

//         outputFile << "Koordinat: " << endl;
//         for (size_t i = 0; i < result.solution.item.size(); i++){
//             outputFile << result.solution.item[i].position.x << ",";
//             outputFile << result.solution.item[i].position.y << endl;
//         }
        
//         outputFile << "Waktu eksekusi: ";
//         outputFile << result.time << "ms" << endl;

//         outputFile.close();

//         cout << "File written successfully";

//     }
// }

// Displaying structs
void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            cout << matrix.item[i][j].token << " ";
        }
        cout << endl;
    }
}

void printCorr (Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            cout << "(" << matrix.item[i][j].position.x + 1 << "," << matrix.item[i][j].position.y + 1 << ") ";
        }
        cout << endl;
    }
}

void printSequence(Sequences sequence) {
    for (int i = 0; i < sequence.number; i++) {
        cout << "Sequence " << i + 1 << " : ";
        for (size_t j = 0; j < sequence.item[i].size(); j++) {
            cout << sequence.item[i][j].token;
            if (j < (sequence.item[i].size() - 1)) {
                cout << " ";
            }
        }
        cout << endl;
        cout << "Reward: " << sequence.reward[i] << endl;
    }
}

void printInputs(Inputs input) {
    cout << "Buffer: " << input.bufferSize << endl;
    cout << "Matrix-width: " << input.matrix.rows << " Matrix-height: " << input.matrix.cols << endl;
    printMatrix(input.matrix);
    printCorr(input.matrix);
    cout << "Number of sequence: " << input.sequence.number << endl;
    printSequence(input.sequence);
}

// Generating random items
int randomize(int min,int max){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> range(min,max);

    return range(gen);
}

Tokens getTokens() {
    Tokens tokens;
    cout << "Masukkan jumlah token:" << endl;
    cin >> tokens.jumlah;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');    

    string line;
    cout << "Masukkan token dalam satu baris:" << endl;

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
    cout << "Masukkan ukuran matrix (lebar<spasi>tinggi): " << endl;
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
    cout << "Masukkan jumlah sequence: " << endl;
    cin >> sequence.number;

    cout << "Masukkan ukuran maksimal sequence: " << endl;
    cin >> maxSeq;

    // Seed
    shuffle(token.item.begin(), token.item.end(), default_random_engine(time(0)));

    
    for (int i=0;i<sequence.number;i++){
        vector<TokenItems> list;
        int length = randomize(1,maxSeq-1);
        for (int j=0; j < length ; j++){
            int index = randomize(0,token.jumlah-1);
            TokenItems temp;
            temp.token = token.item[index];
            list.push_back(temp);
        }
        sequence.item.push_back(list);

        int points = randomize(1,50);
        sequence.reward.push_back(points); // range masih ngasal
    }

    return sequence;
}

// void printResult(const Result& result) {
//     cout << "reward = " << result.reward << endl;
//     cout << "time = " << result.time << endl;

//     cout << "solution = [";
//     for (int i = 0; i < result.solution.count; ++i) {
//         cout << "\"" << result.solution.item[i].token << "\"";
//         if (i < result.solution.count - 1) {
//             cout << ",";
//         }
//     }
//     cout << "]" << endl;
// }

int main() {
    // Inputs input;
    // input = fileParser("../test/input/hi.txt");
    // printInputs(input);
    // cout << "done" << endl;

    Tokens token;
    Matrix matrix;
    Sequences sequence;
    
    token = getTokens();
    matrix = getRandomMatrix(token);
    sequence = getRandomSequence(token);
    printMatrix(matrix);
    printSequence(sequence);

    //  Initialize Result structure
    // Result myResult;
    // myResult.reward = 50;
    // myResult.time = 10;

    // Solution mySolution;
    // mySolution.count = 5;

    // // Adding token items to solution
    // for (int i = 0; i < mySolution.count; ++i) {
    //     TokenItems tokenItem;
    //     tokenItem.position.x = i;  // You may set appropriate values for x and y
    //     tokenItem.position.y = i;
    //     tokenItem.token = "AA";  // You may set appropriate token value
    //     mySolution.item.push_back(tokenItem);
    // }

    // myResult.solution = mySolution;

    // // Print the result
    // printResult(myResult);
    // txtWrite("../test/output/haha.txt",myResult);
}


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

struct Coordinates
{
    int x;
    int y;
};

struct TokenItems
{
    Coordinates position;
    string token;
};

struct Matrix {
    int rows;
    int cols;
    vector<vector<TokenItems>> item;
};

struct Tokens {
    int jumlah;
    vector<string> item;
};

struct Sequences {      
    int number;
    vector<int> reward;
    vector<vector<TokenItems>> item;
};

struct Path {
    vector<TokenItems> item;
};

struct Inputs {
    int bufferSize;
    Tokens tokens;
    Sequences sequence;
    Matrix matrix;
};

struct Result
{
    int reward;
    Path solution;
    int time;
};

bool hasSequence(const std::vector<TokenItems>& path, const std::vector<TokenItems>& sequence) {
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

bool hasVisited(const vector<Coordinates>& visitedPaths, const TokenItems& currentPath) {
    Coordinates position = currentPath.position;
    for (const auto& pos : visitedPaths) {
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

void printCoordinates(const vector<Coordinates>& coordinates) {
    cout << "Coordinates:" << endl;
    for (const auto& coord : coordinates) {
        cout << "(" << coord.x << ", " << coord.y << ")" << endl;
    }
}

void printPath(const Path& path) {
    cout << "Path Contents:" << endl;
    for (const auto& tokenItem : path.item) {
        cout << "Token: " << tokenItem.token << ", Position: (" << tokenItem.position.x + 1 << ", " << tokenItem.position.y + 1 << ")" << endl;
    }
}

void findPaths(Matrix matrix,
               Sequences sequence,
               TokenItems token,
               Path currentSolution,
               bool isVertical,
               vector<Coordinates> visitedToken,
               int remainingMove,
               int& currentReward,
               Path& bestSolution) {

    if (remainingMove == 0) {
        int reward = 0;
        for (size_t i = 0; i < sequence.item.size(); ++i) {
            const auto& seq = sequence.item[i];
            if (hasSequence(currentSolution.item, seq)) {
                reward += sequence.reward[i];
            }
        }
        if (reward > currentReward) {
            currentReward = reward;
            bestSolution = currentSolution;
        }
    } else {
        if (isVertical) {
            // Moves Downward
            for (int i = token.position.x + 1; i < matrix.rows; i++) {
                TokenItems next = matrix.item[i][token.position.y];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(matrix, sequence, next, path, false, visitedToken, remainingMove - 1, currentReward, bestSolution);
                }
            }

            // Moves upwards
            for (int i = token.position.x - 1; i >= 0; i--) {
                TokenItems next = matrix.item[i][token.position.y];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(matrix, sequence, next, path, false, visitedToken, remainingMove - 1, currentReward, bestSolution);
                }
            }
        } else {

            // Moves right
            for (int j = token.position.y + 1; j < matrix.cols; j++) {
                TokenItems next = matrix.item[token.position.x][j];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(matrix, sequence, next, path, true, visitedToken, remainingMove - 1, currentReward, bestSolution);
                }
            }

            // Moves left
            for (int j = token.position.y - 1; j >= 0; j--) {
                TokenItems next = matrix.item[token.position.x][j];
                if (!hasVisited(visitedToken, next)) {
                    Path path = addToken(currentSolution, next);
                    visitedToken.push_back(next.position);
                    findPaths(matrix, sequence, next, path, true, visitedToken, remainingMove - 1, currentReward, bestSolution);
                }
            }
        }

    }
}

void solve(Matrix matrix, Sequences sequences, int bufferSize, int& currentReward, Path& bestSolution){
    for (int i=2;i <=bufferSize;i++){
        //determining starting point in first row
        for (int j = 0 ; j < matrix.cols;j++){
            Path currentSolution;
            TokenItems start = matrix.item[0][j];
            currentSolution = addToken(currentSolution, start);
            visitedToken.clear();
            visitedToken.push_back(start.position);
            findPaths(matrix,sequences,start,currentSolution,true,visitedToken,i,currentReward,bestSolution);
        }
    }
}

// int main() {
//     Path bestSolution;
//     int currentReward = 0;
//     Inputs input;
//     input = fileParser("../test/input/hi.txt");
//     // printMatrix(input.matrix);
//     // printCorr(input.matrix);
//     solve(input.matrix,input.sequence,input.bufferSize,currentReward,bestSolution);
//     cout << currentReward << endl;
//     printPath(bestSolution);
// }


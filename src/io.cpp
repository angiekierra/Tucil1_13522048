#include "utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Reading from txt 
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
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

// struct Result
// {
//     int reward;
//     Solution solution;
//     int time;
// };






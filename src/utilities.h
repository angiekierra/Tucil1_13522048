#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

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

struct Result
{
    int reward;
    Path solution;
    int time;
};

extern Inputs input;
extern Path bestSolution;
extern int currentReward;

/* BRUTEFORCE ALGORITHM*/
bool hasSequence(const vector<TokenItems>& path, const vector<TokenItems>& sequence);
bool hasVisited(vector<Coordinates>& visitedPaths,TokenItems& currentPath);
void insertCoor(TokenItems& token, int x, int y);
Path addToken(Path path, TokenItems item);
void findPaths(TokenItems token,
               Path currentSolution,
               bool isVertical,
               vector<Coordinates> visitedToken,
               int remainingMove);
void solve(Matrix matrix, Sequences sequences, int bufferSize, int& currentReward, Path& bestSolution);

/* DIPLAYING STRUCTS */
void printMatrix(Matrix matrix);
void printCoordinates(const vector<Coordinates>& coordinates);
void printSequence(Sequences sequence);
void printInputs(Inputs input);
void printPath(const Path& path);

/* RANDOMIZE */
int randomize(int min, int max);
Tokens getTokens();
Matrix getRandomMatrix(Tokens token);
Sequences getRandomSequence(Tokens token);
Inputs getRandomInputs();

/* FILE HANDLING */
Inputs fileParser();
void txtWrite(int reward, Path bestSolution, int duration);

#endif

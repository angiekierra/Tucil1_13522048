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

// ANSI escape codes for text formatting
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

// ANSI escape codes for text colors
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

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

/* TEXT DECORATION */
extern const char* customArt;

#endif

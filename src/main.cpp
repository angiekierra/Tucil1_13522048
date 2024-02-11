#include "utilities.h"
#include <chrono>

using namespace chrono;


int main(){
    int type;
    bool txt;
    Inputs input;
    cout << "Selamat datang di permainan!" << endl;
    cout << "Silahkan pilih mode input: " << endl;
    cout << "1. Menggunakan file txt" << endl;
    cout << "2. Menggunakan CLI/Randomize" << endl;

    do {
        cout << "Masukkan angka yang dipilih (1/2)" << endl;
        cin >> type;
    } while (type != 1 and type != 2);

    if (type == 1){
        input = fileParser();
        txt = true;
    } else {
        input = getRandomInputs();
        txt = false;
    }

    cout << "CALCULATING......" << endl;
    
    // ALGORITHM
    Path bestSolution;
    int currentReward = 0;
    auto start = high_resolution_clock::now();
    solve(input.matrix,input.sequence,input.bufferSize,currentReward,bestSolution);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Reward:" << currentReward << endl;
    cout << "Solusi: " << endl; 
    printPath(bestSolution);
    cout << duration.count() << "ms";


}
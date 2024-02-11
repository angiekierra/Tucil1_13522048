#include "utilities.h"
#include <chrono>

using namespace chrono;


int main(){
    int type;
    bool txt;
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
    auto start = high_resolution_clock::now();
    solve(input.matrix,input.sequence,input.bufferSize,currentReward,bestSolution);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Reward:" << currentReward << endl;
    cout << "Solusi: " << endl; 
    printPath(bestSolution);
    cout << endl;
    cout << duration.count() << " ms" << endl << endl;

    if (txt){
        txtWrite(currentReward,bestSolution,duration.count());
        cout << "Terima kasih sudah melakukan permainan" << endl;
    } else {
        string ans;
        do {
            cout << "Apakah ingin menyimpan solusi? (y/n)" << endl;
            cin >> ans;
        } while (ans != "y" and ans != "n" and ans != "Y" and ans != "N");

        if (ans == "y" || ans == "Y"){
            txtWrite(currentReward,bestSolution,duration.count());
        } 
        cout << "Terima kasih sudah melakukan permainan" << endl;
    }


}
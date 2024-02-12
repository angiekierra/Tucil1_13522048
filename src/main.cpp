#include "utilities.h"
#include <chrono>

using namespace chrono;


int main(){
    int type;
    cout << BOLD << YELLOW << customArt << RESET << endl;
    cout << BOLD << CYAN << "Selamat datang di permainan!" << RESET << endl << endl;
    

    cout << RED << "Silahkan pilih mode input: " << RESET << endl;
    cout << "1. Menggunakan file txt" << endl;
    cout << "2. Menggunakan CLI/Randomize" << endl << endl;

    do {
        cout << GREEN << "Masukkan angka yang dipilih (1/2): " << RESET;
        cin >> type;
    } while (type != 1 and type != 2);

    cout << endl;

    if (type == 1){
        cout << MAGENTA << "Anda memilih: " << BOLD << "INPUT DARI TXT" << RESET << endl;
        input = fileParser();
    } else {
        cout << MAGENTA << "Anda memilih: " << BOLD << "INPUT DARI CLI" << RESET << endl;
        cout << "Matrix dan Sequence akan dihasilkan secara acak" << endl << endl;
        input = getRandomInputs();
    }

    if (input.bufferSize != 0){

        printInputs(input);

        cout << endl;
        cout << BOLD << RED << "CALCULATING......"  << RESET << endl;
        
        // ALGORITHM
        auto start = high_resolution_clock::now();
        solve(input.matrix,input.sequence,input.bufferSize,currentReward,bestSolution);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << endl;
        cout << BOLD << BLUE << "Reward: " << RESET << currentReward << endl;
        cout << BOLD << BLUE << "Solusi: " << RESET; 
        printPath(bestSolution);
        cout << endl;
        cout << UNDERLINE << RED << duration.count() << " ms" << RESET << endl << endl;

        string ans;
            do {
                cout << GREEN << "Apakah ingin menyimpan solusi? (y/n): " << RESET;
                cin >> ans;
            } while (ans != "y" and ans != "n" and ans != "Y" and ans != "N");

            if (ans == "y" || ans == "Y"){
                txtWrite(currentReward,bestSolution,duration.count());
            } 
            cout << endl;
            cout << BOLD << CYAN << "Terima kasih sudah melakukan permainan" << RESET << endl;

    } else {
        cout << BOLD << RED << "Panjang Buffer 0, tidak ada solusi yang memungkinkan" << RESET << endl;
        cout << BOLD << CYAN << "Terima kasih sudah melakukan permainan" << RESET << endl;
    }

}
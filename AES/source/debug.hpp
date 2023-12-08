#pragma once
#include "previos.hpp"

void debug_print_v4v4_bit(vector<vector<bitset<8>>> V){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << std::hex << V[j][i].to_ullong() << " ";
        }
        cout << endl;
    }
    cout << endl;
}



void debug_print_v4_bit(vector<bitset<8>> V){
    for(int i = 0; i < 4; i++){
        cout << hex << V[i].to_ullong() << " ";
    }
    cout << endl;
}
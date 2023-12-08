#pragma once
#include "previos.hpp"
#include "function.cpp"
#include "debug.hpp"

vector<vector<vector<bitset<8>>>> KeyExpansion(vector<vector<bitset<8>>> key){
    vector<vector<vector<bitset<8>>>> w(11, vector<vector<bitset<8>>>(4, vector<bitset<8>> (4)));
    vector<bitset<8>> temp(4);  //1ワードを格納

    w[0]= key;
    temp= w[0][3];   //temp= w[i-1] (初回)

    for(int i = 1; i < 11; i++){   //i= 1 => i= Nk
        for(int j = 0; j < 4; j++){
            if(j%Nk == 0){
                temp= SubWord(RotWord(temp));
                for(int k = 0; k < 4; k++){
                    temp[k]= temp[k]^Rcon[i-1][k];
                }
            }

            for(int k = 0; k < 4; k++){
                w[i][j][k]= w[i-1][j][k]^temp[k];   //w[i]= w[i-Nk] ⊕ temp
            }
            temp= w[i][j];  //temp= w[i-1]
        }
    }
    return w;
}
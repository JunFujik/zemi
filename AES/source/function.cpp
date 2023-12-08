#pragma once
#include "previos.hpp"
#include "debug.hpp"



vector<bitset<8>> RotWord(vector<bitset<8>> temp){
    vector<bitset<8>> t(4);
    for(int k = 4; k < 8; k++){
        t[(k-1)%4] = temp[k%4];
    }
    
    return t;
}


vector<bitset<8>> SubWord(vector<bitset<8>> temp){
    bitset<8> high, low;
    for(int j = 0; j < 4; j++){
        high= (temp[j] >> 4);   //右シフトで下位4bitを消去
        bitset<8> t = 0x0f; 
        low= (temp[j] & t);  //上位4bitを0ANDで消去

        temp[j]= sbox[high.to_ullong()][low.to_ullong()];
    }

    return temp;
}



void Add_Round_Key(vector<vector<bitset<8>>> &state, vector<vector<bitset<8>>> w){    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            state[j][i] = state[j][i]^w[j][i];
        }
    }
}



void SubBytes(vector<vector<bitset<8>>> &state){
    bitset<8> high, low;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            high= (state[j][i] >> 4);   //右シフトで下位4bitを消去
            bitset<8> temp = 0x0f; 
            low= (state[j][i] & temp);  //上位4bitを0ANDで消去

            // cout << hex << state[j][i].to_ullong() << endl;
            // cout << hex << high.to_ullong() << low.to_ullong() << endl;
            //cout << hex << sbox[high.to_ullong()][low.to_ullong()] << endl; 

            state[j][i]= sbox[high.to_ullong()][low.to_ullong()];
            
            //cout << state[j][i].to_ullong() << endl;
        }
    }
}



void InvSubBytes(vector<vector<bitset<8>>> &state){
    bitset<8> high, low;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            high= (state[j][i] >> 4);
            bitset<8> temp = 0x0f;
            low= (state[j][i] & temp);

            state[j][i]= inv_sbox[high.to_ullong()][low.to_ullong()];
        }
    }
}



void ShiftRows(vector<vector<bitset<8>>> &state){   //rotl()に変更したい
    vector<bitset<8>> temp(4);
    for(int i = 0; i < 4; i++){
        for(int k = 4; k < 8; k++){
            temp[(k-i)%4] = state[k%4][i];
        }
        for(int j = 0; j < 4; j++){
            state[j][i] = temp[j];
        }
    }
}



void InvShiftRows(vector<vector<bitset<8>>> &state){
    vector<bitset<8>> temp(4);
    for(int i = 0; i < 4; i++){
        for(int k = 4; k < 8; k++){
            temp[(k+i)%4] = state[k%4][i];
        }
        for(int j = 0; j < 4; j++){
            state[j][i] = temp[j];
        }
    }
}




bitset<8> xtime(bitset<8> b){
    bitset<8> mx= 0x1b;
    if(b.test(7) == 1){
        b= (b << 1) ^ mx;
    }
    else{
        b= b << 1;
    }
    return b;
}


bitset<8> multiple(bitset<8> b, bitset<8> c){   //b: 固定値 c: バラバラにされる側兼変数
    bitset<8> x;    //返り値
    for(int i = 0; i < 8; i++){
        if(c.test(0) == 1){ //2bitで分解したときに存在するならば
            x= x^b;
        }
        b= xtime(b);    //xtime([i])= xtime(xtime([i-1]))より
        c = c >> 1; //分解するためのシフト(1bitずつ見てるので)
    }
    return x;
}

void MixCulumns(vector<vector<bitset<8>>> &state){
    vector<bitset<8>> t(4);
    for(int i = 0; i < 4; i++){
        t[0]= state[i][0]; t[1]= state[i][1]; t[2]= state[i][2]; t[3]= state[i][3];
        
        state[i][0]= multiple(0x02, t[0]) ^ multiple(0x03, t[1]) ^ t[2] ^ t[3];
        state[i][1]= t[0] ^ multiple(0x02, t[1]) ^ multiple(0x03, t[2]) ^ t[3]; 
        state[i][2]= t[0] ^ t[1] ^ multiple(0x02, t[2]) ^ multiple(0x03, t[3]);
        state[i][3]= multiple(0x03, t[0]) ^ t[1] ^ t[2] ^ multiple(0x02, t[3]);
    }
}



void InvMixCulumns(vector<vector<bitset<8>>> &state){
    vector<bitset<8>> t(4);
    for(int i = 0; i < 4; i++){
        t[0]= state[i][0]; t[1]= state[i][1]; t[2]= state[i][2]; t[3]= state[i][3];
        
        state[i][0]= multiple(0x0e, t[0]) ^ multiple(0x0b, t[1]) ^ multiple(0x0d, t[2]) ^ multiple(0x09, t[3]);
        state[i][1]= multiple(0x09, t[0]) ^ multiple(0x0e, t[1]) ^ multiple(0x0b, t[2]) ^ multiple(0x0d, t[3]); 
        state[i][2]= multiple(0x0d, t[0]) ^ multiple(0x09, t[1]) ^ multiple(0x0e, t[2]) ^ multiple(0x0b, t[3]);
        state[i][3]= multiple(0x0b, t[0]) ^ multiple(0x0d, t[1]) ^ multiple(0x09, t[2]) ^ multiple(0x0e, t[3]);
    }
}
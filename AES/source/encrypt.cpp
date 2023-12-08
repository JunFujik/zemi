#include "previos.hpp"
#include "function.cpp"
#include "KeyExpansion.cpp"
#include "debug.hpp"



int main(){
    const vector<vector<bitset<8>>> in={
        {0x32, 0x43, 0xf6, 0xa8},
        {0x88, 0x5a, 0x30, 0x8d},
        {0x31, 0x31, 0x98, 0xa2},
        {0xe0, 0x37, 0x07, 0x34}
    };

    const vector<vector<bitset<8>>> key= {
        {0x2b, 0x7e, 0x15, 0x16},
        {0x28, 0xae, 0xd2, 0xa6}, 
        {0xab, 0xf7, 0x15, 0x88},
        {0x09, 0xcf, 0x4f, 0x3c}
    };

    vector<vector<vector<bitset<8>>>> w = KeyExpansion(key);

    vector<vector<bitset<8>>> state = in;
    Add_Round_Key(state, w[0]);  //retern state;
    for(int r = 1; r < Nr; r++){
        SubBytes(state);
        ShiftRows(state);
        MixCulumns(state);
        Add_Round_Key(state, w[r]);
    }
    SubBytes(state);
    ShiftRows(state);
    Add_Round_Key(state, w[Nr]);
    debug_print_v4v4_bit(state);
}
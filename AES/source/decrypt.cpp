#include "previos.hpp"
#include "function.cpp"
#include "KeyExpansion.cpp"
#include "debug.hpp"



int main(){
    const vector<vector<bitset<8>>> in= {
        {0x39, 0x25, 0x84, 0x1d},
        {0x02, 0xdc, 0x09, 0xfb},
        {0xdc, 0x11, 0x85, 0x97},
        {0x19, 0x6a, 0x0b, 0x32}
    };
    const vector<vector<bitset<8>>> key= {
        {0x2b, 0x7e, 0x15, 0x16},
        {0x28, 0xae, 0xd2, 0xa6}, 
        {0xab, 0xf7, 0x15, 0x88},
        {0x09, 0xcf, 0x4f, 0x3c}
    };

    vector<vector<vector<bitset<8>>>> w = KeyExpansion(key);
    vector<vector<bitset<8>>> state = in;
    //FIPS Begin
    
    Add_Round_Key(state, w[Nr]);  //retern state;
    for(int r = 1; r < Nr; r++){
        InvShiftRows(state);
        InvSubBytes(state);
        Add_Round_Key(state, w[Nr-r]);
        InvMixCulumns(state);
    }
    InvShiftRows(state);
    InvSubBytes(state);
    Add_Round_Key(state, w[0]);

    debug_print_v4v4_bit(state);
}


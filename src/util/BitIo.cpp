#include "BitIo.h"

#include <limits>
BitIo::BitIo(std::ifstream &in,std::ofstream &out): input(in),output(out), temp(0), bitOff(0),bitIn(0){}

int BitIo::read(){
    if(temp == -1)
        return -1;
    if(bitOff == 0){
        temp = input.get();
        if(temp == EOF)
            return -1;
        bitOff = 8;
    }
    bitOff--;
    return (temp >> bitOff) & 1;
}
void BitIo::write(int b){
    temp = (temp << 1) | b;

    bitIn++;
    if(bitIn == 8){
        if (std::numeric_limits<char>::is_signed)
            temp -= (temp >> 7) << 8;
        output.put(static_cast<char>(temp));
        temp = 0;
        bitIn = 0;
    }
}

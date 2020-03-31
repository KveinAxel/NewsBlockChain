#ifndef BIT_IO_H
#define BIT_IO_H

#include <fstream>

class BitIo
{
public:
    int temp;
    int bitOff;
    int bitIn;

    std::ifstream & input;
    std::ofstream & output;

    BitIo(std::ifstream & in, std::ofstream &out);

    int read();
    void write(int b);
};

#endif // BIT_IO_H

#ifndef BITIO_H
#define BITIO_H

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

#endif // BITIO_H

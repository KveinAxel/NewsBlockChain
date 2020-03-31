#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "HuffmanTree.h"
#include "BitIo.h"

class Huffman
{
public:

    HuffmanTree * huffmanTree;
    BitIo * bitIo{};
public:
    Huffman();
    void Compress(char * input, char * output);
    void DeCompress(char * input, char * output);
    static constexpr int32_t MAX_NUM = 257;
};

#endif // HUFFMAN_H

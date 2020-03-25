#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "huffmantree.h"
#include "bitio.h"

class Huffman
{
public:

    HuffmanTree * huffmantree;
    BitIo * bitio;
public:
    Huffman();
    void Compress(char * input, char * output);
    void DeCompress(char * input, char * output);
    //quint32 reGetCode(Node *root, std::ifstream in);
    static quint32 MAX_NUM;

};

#endif // HUFFMAN_H

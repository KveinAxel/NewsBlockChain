#include "huffman.h"
#include <QDebug>
quint32 Huffman::MAX_NUM = 257;

Huffman::Huffman()
{
    huffmantree = new HuffmanTree(MAX_NUM);
}
void Huffman::Compress(char *input, char *output){
    std::ifstream in;
    in.open(input,std::ios_base::binary);
    std::ofstream out;
    out.open(output,std::ios_base::binary);
    bitio = new BitIo(in,out);


    if(in.is_open())
        qDebug()<<"right";
    quint32 freq[MAX_NUM] = {0};

    while(1){
        quint32 c = in.get();
        qDebug()<<c;
        if(c == EOF)
            break;
        freq[c]++;
    }
    freq[256]++;

    Node * root = huffmantree->createTree(freq);
    QVector <char> path;
    huffmantree->getCodeTree(root, path);
    delete root;
    //qDebug()<<"here";
    in.clear();
    in.seekg(0);
    //写入频率
    for (quint32 i = 0; i < MAX_NUM; i++) {
        quint32 val = freq[i];
        for (int j = 7; j >= 0; j--)
            bitio->write((val >> j) & 1);
    }
    //qDebug()<<"translate";
    //进行转换
    while(1){
        int symbol = in.get();
        if(symbol == EOF)
            break;
        for(QChar b : huffmantree->getCode(symbol))
        {
            bitio->write(b.toLatin1());
            //qDebug()<<b;

        }
        //qDebug()<<"----";
    }
    for(char b : huffmantree->getCode(256)){
        bitio->write(b);
        //qDebug()<<b;
       }
    //qDebug()<<"----";
    while(bitio->bitIn!= 0)
    {
        //qDebug()<<'0';
        bitio->write(0);
    }
    //qDebug()<<"over";
    delete bitio;
}
void Huffman::DeCompress(char * input,char * output){
    std::ifstream in;
    in.open(input,std::ios_base::binary);
    std::ofstream out;
    out.open(output,std::ios_base::binary);
    bitio = new BitIo(in,out);

    quint32 freq[MAX_NUM];
    for(quint32 i = 0; i < MAX_NUM; i++){
        quint32 val = 0;
        for(int j = 0; j < 8; j++)
            val = (val << 1) | bitio->read();
        freq[i] = val;
    }
    //freq[256] = 1;
    //根据频率重新建树
    Node * root = huffmantree->createTree(freq);

    while(1){
        quint32 symbol;
        Node * current = root;
        //得到symbol值
        while(1){
            int temp = bitio->read();
            //qDebug()<<"read temp"<<temp;
            Node * next;
            if(temp == 1)
                next = current->rightChild.get();
            else
                next = current->leftChild.get();
            //qDebug()<<"current"<<current->symbol;
            if((next->leftChild.get() == NULL)&& (next->rightChild.get() == NULL)&& (next)){
               symbol = next->symbol;
               break;
            }
            else if (next)
                current = next;
        }
        if(symbol == 256)
            break;
        int b = static_cast<int>(symbol);
        if (std::numeric_limits<char>::is_signed)
            b -= (b >> 7) << 8;
        //写入symbol
        out.put(static_cast<char>(b));
    }
    //qDebug()<<"out";
}

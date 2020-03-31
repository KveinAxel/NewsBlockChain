#include <wsman.h>
#include "Huffman.h"
#include "../Global.h"

Huffman::Huffman() {
    huffmanTree = new HuffmanTree(MAX_NUM);
}

void Huffman::Compress(char *input, char *output) {
    std::ifstream in;
    in.open(input, std::ios_base::binary);
    std::ofstream out;
    out.open(output, std::ios_base::binary);
    bitIo = new BitIo(in, out);

    auto logger = Global::getGlobal()->getLogger();

    if (in.is_open())
        logger->traceInfo("right");
    int32_t freq[MAX_NUM] = {0};

    int32_t c;
    while (EOF != (c = in.get())) {
        logger->traceInfo("%d", c);
        freq[c]++;
    }
    freq[256]++;

    Node *root = HuffmanTree::createTree(freq);
    std::vector<char> path;
    huffmanTree->getCodeTree(root, path);
    delete root;
    //qDebug()<<"here";
    in.clear();
    in.seekg(0);
    //写入频率
    for (int val : freq) {
        for (int j = 7; j >= 0; j--)
            bitIo->write((val >> j) & 1);
    }
    //qDebug()<<"translate";
    //进行转换
    while (1) {
        int symbol = in.get();
        if (symbol == EOF)
            break;
        for (QChar b : huffmanTree->getCode(symbol)) {
            bitIo->write(b.toLatin1());
            //qDebug()<<b;

        }
        //qDebug()<<"----";
    }
    for (char b : huffmanTree->getCode(256)) {
        bitIo->write(b);
        //qDebug()<<b;
    }
    //qDebug()<<"----";
    while (bitIo->bitIn != 0) {
        //qDebug()<<'0';
        bitIo->write(0);
    }
    //qDebug()<<"over";
    delete bitIo;
}

void Huffman::DeCompress(char *input, char *output) {
    std::ifstream in;
    in.open(input, std::ios_base::binary);
    std::ofstream out;
    out.open(output, std::ios_base::binary);
    bitIo = new BitIo(in, out);

    int32_t freq[MAX_NUM];
    for (int &i : freq) {
        int32_t val = 0;
        for (int j = 0; j < 8; j++)
            val = (val << 1) | bitIo->read();
        i = val;
    }
    //freq[256] = 1;
    //根据频率重新建树
    Node *root = HuffmanTree::createTree(freq);

    while (1) {
        int32_t symbol;
        Node *current = root;
        //得到symbol值
        while (1) {
            int temp = bitIo->read();
            Node *next;
            if (temp == 1)
                next = current->rightChild.get();
            else
                next = current->leftChild.get();
            if (next && next->leftChild == nullptr && next->rightChild == nullptr) {
                symbol = next->symbol;
                break;
            } else if (next)
                current = next;
        }
        if (symbol == 256)
            break;
        int b = static_cast<int>(symbol);
        if (std::numeric_limits<char>::is_signed)
            b -= (b >> 7) << 8;
        //写入symbol
        out.put(static_cast<char>(b));
    }
}

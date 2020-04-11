#ifndef HASH_H
#define HASH_H

#include <string>
#include <iostream>
using namespace std;


/*定义类型*/
typedef unsigned int uint32;
typedef unsigned char byte;


class Hash{

    uint32 state[8];     //用于存放这256为bit，用于变化的
    uint32 count[2];          //数据的长度
    byte buffer[64];        //需要处理的512位值
    byte digest[32];     //存放最后的
    bool finished;     //用于判断是否结束

    static const byte PADDING[64];   //用于填补信息，至少填补一位信息
    static const char HEX[16];
    enum {BUFFER_SIZE = 1024};

public:
    Hash();
    Hash(const string& message);
    string toString();      //输出的是64位十六进制的字符串

protected:
    void set();
    void init(const byte* input,size_t len);
    void transform(const byte block[64]);
    const byte* getDigest();
    uint32 fmix(uint32 h);
    void encode(const uint32* input,byte* output,size_t length);
    void decode(const byte* input,uint32* output, size_t length);
};


#endif // HASH_H

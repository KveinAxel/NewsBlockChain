#ifndef NEWS_BLOCK_CHAIN_HASH_H
#define NEWS_BLOCK_CHAIN_HASH_H

#include <string>
#include <iostream>

using namespace std;


/*定义类型*/
typedef unsigned int uint32;
typedef unsigned char byte;

class Hash {

    /**
     * 用于存放这256为bit，用于变化的
     */
    uint32 state[8];

    /**
     * 数据的长度
     */
    uint32 count[2]{0};

    /**
     * 需要处理的512位值
     */
    byte buffer[64];

    /**
     * 存放最后的
     */
    byte digest[32];

    /**
     * 用于判断是否结束
     */
    bool finished;

    /**
     * 用于填补信息，至少填补一位信息
     */
    static const byte PADDING[64];

    static const char HEX[16];

    enum {
        BUFFER_SIZE = 1024
    };

public:
    Hash();

    Hash(const string &message);

    /**
     * 将哈希值转换成64位十六进制的字符串
     * @return 转换后的hash值
     */
    string toString();

protected:

    /**
     * 找8个初始值
     */
    void set();

    /**
     * 对数据进行处理
     * @param input 输入数据
     * @param len 数据长度
     */
    void init(const byte *input, size_t len);

    void transform(const byte block[64]);

    /**
     * 判断数据是否处理完成
     * @return 原来的hash值
     */
    const byte *getDigest();

    /**
     * 使所有位都有翻转的可能
     * @param h
     * @return
     */
    static uint32 fmix(uint32 h);

    /**
     * 将32bit转换成8bit
     * @param input
     * @param output
     * @param length
     */
    static void encode(const uint32 *input, byte *output, size_t length);

    /**
     * 将8bit转换成32bit
     * @param input
     * @param output
     * @param length
     */
    static void decode(const byte *input, uint32 *output, size_t length);
};


#endif // NEWS_BLOCK_CHAIN_HASH_H

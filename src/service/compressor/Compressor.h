#ifndef NEWS_BLOCK_CHAIN_COMPRESSOR_H
#define NEWS_BLOCK_CHAIN_COMPRESSOR_H

#include "HuffmanTree.h"

/**
 * 压缩器
 */
class Compressor {
private:
    /**
     * 哈夫曼树
     */
    HuffmanTree *huffmanTree;

    /**
     * 序列化字典
     */
    std::string serializedDict;

    /**
     * 数据压缩后的字节数组
     */
    std::vector<uint32_t> bytes;

    /**
     * 填充长度
     */
    uint32_t filler = 0;

    /**
     * 未(解)压缩数据
     */
    std::string data;

    /**
     * 0: 压缩器
     * 1: 解压缩器
     */
    uint32_t compressorType;

    /**
     * 是否完成工作
     */
    bool completed = false;

    /**
     * 字符集大小
     */
    static constexpr uint32_t MAX_NUM = 257;
public:
    /**
     * 压缩器构造
     * @param data 待压缩数据
     */
    explicit Compressor(std::string data);

    /**
     * 解压缩器构造
     * @param serializedDict 序列化字典
     * @param bytes 字节数组
     */
    explicit Compressor(std::string serializedDict, std::vector<uint32_t> bytes, uint32_t filler);

    /**
     * 压缩
     */
    void compress();

    /**
     * 解压缩
     */
    void decompress();

    /**
     * 获取序列化字典
     * @return 序列化字典
     */
    std::string getSerializedDict() const;

    /**
     * 获取压缩后的字节数组
     * @return 字节数组
     */
    std::vector<uint32_t> getBytes() const;

    /**
     * 获取解压缩数据
     * @return 解压缩数据
     */
    std::string getData() const;

    /**
     * 获取填充长度
     * @return 填充长度
     */
    uint32_t getFiller() const;

    /**
     * 是否完成工作
     * @return
     */
    bool isCompleted() const;
};

#endif // NEWS_BLOCK_CHAIN_COMPRESSOR_H

#include <wsman.h>
#include <unordered_map>
#include <utility>
#include "Compressor.h"
#include "../Global.h"


Compressor::Compressor(std::string data) : data(std::move(data)) {
    this->huffmanTree = new HuffmanTree(MAX_NUM);
    this->compressorType = 0;
}

Compressor::Compressor(std::string serializedDict, std::vector<uint32_t> bytes)
        : serializedDict(std::move(serializedDict)), bytes(std::move(bytes)) {
    this->huffmanTree = new HuffmanTree(MAX_NUM);
    this->compressorType = 1;
}

void Compressor::compress() {

    // 压缩器类型不符合要求
    if (this->compressorType == 1) {
        completed = false;
        return;
    }

    uint32_t dict[MAX_NUM] = {0}; // 字典

    // 将数据转化为频数字典，字典的key为对应字节的偏移(+128)
    for (char c : data)
        dict[c + 128]++;
    dict[128]++;

    // 利用频数字典建立哈夫曼树，并获得树根
    Node *root = HuffmanTree::createTree(dict);

    // 获取序列化的字典
    this->serializedDict = root->serialize();

    // 建立编码向量
    std::string code;
    huffmanTree->getCodeTree(root, code);

    // 获取压缩后数据
    std::string compressData;
    std::string tmp;
    uint32_t encode = 0;
    uint32_t bit = 0;
    for (auto &c : data) {
        tmp = huffmanTree->codeVector[c + 128];
        for (auto &i : tmp) {
            encode <<= 1u;
            bit += 1;
            encode |= unsigned(i - '0');
            if (bit == 32) {
                this->bytes.push_back(encode);
                bit = 0;
                encode = 0;
            }
        }
    }
    // 填充未满数据
    while (bit != 32) {
        encode <<= 1u;
        bit += 1;
        this->filler += 1;
    }
    this->bytes.push_back(encode);
    this->completed = true;
}

void Compressor::decompress() {

    // 压缩器类型不符合要求
    if (this->compressorType == 0) {
        this->completed = false;
        return;
    }

    // 获取哈夫曼树
    Node* root = Node::deserialize(this->serializedDict);

    std::string tmp; // 字符化字节
    std::string str; // 字符化字节数组
    uint32_t bit; // 位
    uint32_t len = 0;
    for (uint32_t i = 0; i < this->bytes.size(); i++) {
        tmp.clear();
        bit = 1;
        // 如果是最后则去除填充
        if (i == this->bytes.size() - 1)
            len = this->filler;
        // 将字节转化为字符
        while (bit <= 32) {
            if (bit > len)
                tmp += std::to_string(this->bytes[i] & 1u);
            this->bytes[i] >>= 1u;
            bit++;
        }
        std::reverse(tmp.begin(), tmp.end());
        str += tmp;
    }

    Node* cur = root; // 游标
    for (auto &c: str) {
        if(c == '0') {
            // 递归左子树
            cur = cur->leftChild.get();
            if(cur->leftChild == nullptr && cur->rightChild == nullptr) {
                this->data += char(cur->symbol - 128);
                cur = root;
            }
        } else {
            // 递归右子树
            cur = cur->rightChild.get();
            if(cur->leftChild == nullptr && cur->rightChild == nullptr) {
                this->data += char(cur->symbol - 128);
                cur = root;
            }
        }
    }

    this->completed = true;
}

std::string Compressor::getSerializedDict() const{
    if (this->compressorType == 0 && this->completed)
        return this->serializedDict;
    else
        return "";
}

std::vector<uint32_t> Compressor::getBytes() const{
    if (this->compressorType == 0 && this->completed)
        return this->bytes;
    else
        return std::vector<uint32_t>();
}

std::string Compressor::getData() const{
    if (this->compressorType == 1 && this->completed)
        return this->data;
    else
        return "";
}

bool Compressor::isCompleted() const{
    return this->completed;
}

uint32_t Compressor::getFiller() const {
    return this->filler;
}

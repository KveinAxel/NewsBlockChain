#ifndef NEWS_BLOCK_CHAIN_HUFFMAN_TREE_H
#define NEWS_BLOCK_CHAIN_HUFFMAN_TREE_H

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

/**
 * 哈夫曼树节点
 */
class Node {
private:
    /**
     * 利用序列化的编码字典建树
     * @param head 树根
     * @param serializedDict 序列化字典
     */
    static void build(std::unique_ptr<Node> &head, std::string &serializedDict);

public:
    // 偏移后的符号(+128)
    uint32_t symbol;

    // 左右子树
    std::unique_ptr<Node> leftChild;
    std::unique_ptr<Node> rightChild;

    /**
     * 构造器
     * @param symbol 偏移后的符号(+128)
     */
    explicit Node(uint32_t symbol);

    /**
     * 构造器
     * @param symbol 偏移后的符号(+128)
     * @param left 左子树
     * @param right 右子树
     */
    explicit Node(uint32_t symbol, std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right);

    /**
     * 序列化
     * @return 序列化得到的字符串
     */
    std::string serialize();

    /**
     * 反序列化
     * @param serializedDict 序列化后的编码字典
     * @return 反序列化得到的哈夫曼树根
     */
    static Node* deserialize(std::string& serializedDict);
};

/**
 * 带频数的哈夫曼节点
 */
class NodeFrequency {
public:
    /**
     * 节点
     */
    std::unique_ptr<Node> node;

    /**
     * 子节点(如果有)符号较小的
     */
    int32_t symbol;

    /**
     * 符号频数
     */
    int32_t frequency;

    /**
     * 构造器
     * @param node 节点
     * @param minSymbol 子节点(如果有)符号较小的
     * @param frequency 符号频数
     */
    explicit NodeFrequency(Node *node, uint32_t minSymbol, uint32_t frequency);

    // 重载偏序关系，用于排序
    bool operator<(const NodeFrequency &other) const;
};

/**
 * 哈夫曼树
 */
class HuffmanTree {
public:
    /**
     * 构造器
     * @param symbolLimit 带压缩数据的字符空间上限
     */
    explicit HuffmanTree(uint32_t symbolLimit);

    /**
     * 编码向量，可以通过字符获取对应编码
     */
    std::vector<std::string> codeVector;

    /**
     * 通过哈夫曼树获取编码向量
     * @param node 哈夫曼(子)树根
     * @param code 编码
     */
    void getCodeTree(Node *node, std::string &code);

    /**
     * 给定字符，获取对应编码
     * @param symbol 字符
     * @return 编码
     */
    std::string getCode(uint32_t symbol) const;

    /**
     * 通过频数字典建立哈夫曼树
     * @param dict 频数字典
     * @return 哈夫曼树树根
     */
    static Node *createTree(uint32_t *dict);

};

#endif // NEWS_BLOCK_CHAIN_HUFFMAN_TREE_H

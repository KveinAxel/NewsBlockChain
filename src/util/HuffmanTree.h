#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <utility>
#include <memory>
#include <vector>

class Node {
public:
    int32_t symbol;
    std::unique_ptr<Node> leftChild;
    std::unique_ptr<Node> rightChild;
    std::string code;

    explicit Node(int32_t sym);

    Node(int32_t sym, std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right);
};

class Node_freq {
public:
    std::unique_ptr<Node> node;
    int32_t minSymbol;
    int32_t freq;

    Node_freq(Node *nd, int32_t minSym, int32_t f);

    bool operator<(const Node_freq &other) const;
};

class HuffmanTree {
public:
    //Node root;
    std::vector <std::vector<char>> codes;
    //QVector<quint32> lengths;
public:
    explicit HuffmanTree(int32_t symbolLimit);

    void getCodeTree(Node *node, std::vector<char> &path);

    std::vector<char> getCode(int32_t sym) const;

    static Node *createTree(int32_t *freq);

};


#endif // HUFFMAN_TREE_H

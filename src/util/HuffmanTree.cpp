#include "HuffmanTree.h"
#include "../Global.h"
#include <memory>
#include <queue>
#include <memory>

Node::Node(uint32_t symbol) : symbol(symbol) {}

Node::Node(uint32_t symbol, std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right) :
        symbol(symbol), leftChild(std::move(left)), rightChild(std::move(right)) {}

std::string Node::serialize() {
    // 其中#表示非叶子节点， $表示空节点
    std::string res;

    // 叶子节点字节返回字符,非叶子节点返回#
    if (nullptr == this->leftChild && nullptr == this->rightChild)
        res += char(this->symbol - 128);
    else
        res += "#";

    // 递归左子树
    if (nullptr == this->leftChild)
        res += "$";
    else
        res += this->leftChild->serialize();

    // 递归右子树
    if (nullptr == this->rightChild)
        res += "$";
    else
        res += this->rightChild->serialize();
}

void Node::build(std::unique_ptr<Node> &head, std::string &serializedDict) {
    char ch;

    // 获取根
    ch = serializedDict[0];

    // 去除根
    serializedDict = serializedDict.substr(1);

    //递归获得子树
    if (ch != '$') {
        head = std::make_unique<Node>(ch + 128);
        build(head->leftChild, serializedDict);
        build(head->rightChild, serializedDict);
    }
}

Node *Node::deserialize(std::string &serializedDict) {
    if (serializedDict.empty())
        return nullptr;

    // 调用build函数获取哈夫曼树
    std::unique_ptr<Node> root;
    build(root, serializedDict);
    return root.release();
}

NodeFrequency::NodeFrequency(Node *node, uint32_t minSymbol, uint32_t frequency) :
        node(std::unique_ptr<Node>(node)), symbol(minSymbol), frequency(frequency) {}

HuffmanTree::HuffmanTree(uint32_t symbolLimit) {
    codeVector = std::vector<std::string>(symbolLimit, "");
}

std::string HuffmanTree::getCode(uint32_t symbol) const {
    return codeVector.at(symbol);
}

Node *HuffmanTree::createTree(uint32_t *dict) {
    // 获取日志接口
    auto logger = Global::getGlobal()->getLogger();
    logger->traceInfo("create Tree");

    // 创建字典
    std::priority_queue<NodeFrequency> queue;
    for (int i = 0; i < 257; i++)
        if (dict[i] > 0)
            queue.push(NodeFrequency(new Node(i), i, dict[i]));

    while (queue.size() > 1) {

        // 取出前两个元素
        NodeFrequency x = std::move(const_cast<NodeFrequency &&>(queue.top()));
        queue.pop();
        NodeFrequency y = std::move(const_cast<NodeFrequency &&>(queue.top()));
        queue.pop();

        // 合并节点
        int32_t minSym = std::min(x.symbol, y.symbol);
        Node *newNode = new Node(minSym, std::move(x.node), std::move(y.node));
        NodeFrequency newNodeFrequency(newNode, minSym, x.frequency + y.frequency);

        // 放入优先队列
        queue.push(newNodeFrequency);
        logger->traceInfo("symbol: %d %d", x.symbol, y.symbol);
        logger->traceInfo("dict: %d", x.frequency + y.frequency);
    }

    // 取出最后剩下的根节点
    NodeFrequency temp = std::move(const_cast<NodeFrequency &&>(queue.top()));
    queue.pop();
    Node *root = temp.node.release();
    return root;
}

void HuffmanTree::getCodeTree(Node *node, std::string &code) {
    if (nullptr == node)
        return;
    else if (nullptr == node->leftChild && nullptr == node->rightChild) {
        // 递归终点， 记录编码
        codeVector[node->symbol] = code;
    } else {
        // 递归左子树
        code += "0";
        getCodeTree(node->leftChild.get(), code);
        code.pop_back();

        // 递归右子树
        code += "1";
        getCodeTree(node->rightChild.get(), code);
        code.pop_back();
    }
}

bool NodeFrequency::operator<(const NodeFrequency &other) const {
    if (frequency > other.frequency)
        return true;
    else if (frequency < other.frequency)
        return false;
    else return symbol > other.symbol;
}

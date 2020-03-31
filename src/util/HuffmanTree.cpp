#include "HuffmanTree.h"
#include "../Global.h"
#include <queue>

Node::Node(int32_t sym) : symbol(sym) {}

Node::Node(int32_t sym, std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right) :
        symbol(sym), leftChild(std::move(left)), rightChild(std::move(right)), code("") {}

Node_freq::Node_freq(Node *nd, int32_t minSym, int32_t f) :
        node(std::unique_ptr<Node>(nd)), minSymbol(minSym), freq(f) {}

HuffmanTree::HuffmanTree(int32_t symbolLimit) {
    codes = std::vector<std::string>(symbolLimit, "");
    //lengths = QVector<quint32> (symbolLimit,0);
}

std::vector<char> HuffmanTree::getCode(int32_t sym) const {
    return codes.at(sym);
}

Node *HuffmanTree::createTree(int32_t *freq) {
    auto logger = Global::getGlobal()->getLogger();
    logger->traceInfo("create Tree");
    std::priority_queue<Node_freq> pq;
    for (int i = 0; i < 257; i++)
        if (freq[i] > 0) {
            pq.push(Node_freq(new Node(i), i, freq[i]));
        }
    //每次选取两个权值最小的
    while (pq.size() > 1) {
        Node_freq x = std::move(const_cast<Node_freq &&>(pq.top()));
        pq.pop();
        Node_freq y = std::move(const_cast<Node_freq &&>(pq.top()));
        pq.pop();
        int32_t minSym = std::min(x.minSymbol, y.minSymbol);
        pq.push(Node_freq(new Node(minSym, std::move(x.node), std::move(y.node)), minSym, x.freq + y.freq));
        logger->traceInfo("symbol: %d %d", x.minSymbol, y.minSymbol);
        logger->traceInfo("freq: %d", x.freq + y.freq);
    }
    //最后只剩下一个根节点
    Node_freq temp = std::move(const_cast<Node_freq &&>(pq.top()));
    pq.pop();
    Node *root = temp.node.release();
    return root;
}

void HuffmanTree::getCodeTree(Node *node, std::vector<char> &path) {
    if (node == nullptr)
        return;
    else if ((node->leftChild == nullptr) && (node->rightChild == nullptr)) {
        codes[node->symbol] = path;
    } else {
        path.push_back(0);
        getCodeTree(node->leftChild.get(), path);
        path.pop_back();

        path.push_back(1);
        getCodeTree(node->rightChild.get(), path);
        path.pop_back();
    }
}

bool Node_freq::operator<(const Node_freq &other) const {
    if (freq > other.freq)
        return true;
    else if (freq < other.freq)
        return false;
    else return minSymbol > other.minSymbol;
}

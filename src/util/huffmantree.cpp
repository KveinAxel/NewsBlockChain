#include "huffmantree.h"

#include <QQueue>
#include <queue>
#include <QDebug>
Node::Node(quint32 sym):symbol(sym){}
Node::Node(quint32 sym, std::unique_ptr <Node> &&left, std::unique_ptr <Node> &&right):
            symbol(sym),leftChild(std::move(left)),rightChild(std::move(right)),code(""){}

Node_freq::Node_freq(Node *nd, quint32 minSym, quint32 f):
    node(std::unique_ptr <Node> (nd)), minSymbol(minSym),freq(f){}

HuffmanTree::HuffmanTree(quint32 symbolLimit){
    codes = QVector<QString>(symbolLimit,"");
    //lengths = QVector<quint32> (symbolLimit,0);
}
QVector<char> HuffmanTree::getCode(quint32 sym) const{
    return codes.at(sym);
}
Node * HuffmanTree::createTree(quint32 *freq){
    qDebug()<<"create Tree";
    std::priority_queue <Node_freq> pq;
    for(int i = 0; i < 257; i++)
        if(freq[i] > 0)
        {
            pq.push(Node_freq(new Node(i), i, freq[i]));
        }
    //每次选取两个权值最小的
    while(pq.size() > 1)
    {
        Node_freq x = std::move(const_cast<Node_freq&&>(pq.top()));
        pq.pop();
        Node_freq y = std::move(const_cast<Node_freq&&>(pq.top()));
        pq.pop();
        quint32 minSym = qMin(x.minSymbol, y.minSymbol);
        pq.push(Node_freq(new Node(minSym, std::move(x.node), std::move(y.node)), minSym, x.freq+y.freq));
        qDebug()<<"symbol: "<<x.minSymbol<<"  "<<y.minSymbol;
        qDebug()<<"freq: "<<x.freq+y.freq;
    }
    //最后只剩下一个根节点
    Node_freq temp = std::move(const_cast<Node_freq&&>(pq.top()));
    pq.pop();
    Node * root = temp.node.release();
    return root;
}
void HuffmanTree::getCodeTree(Node *node ,QVector <char>& path){
    if(node == NULL)
        return;
    else if((node->leftChild.get() == NULL) &&(node->rightChild.get()==NULL))
    {
        codes[node->symbol] = path;
    }
    else
    {
        path.push_back(0);
        getCodeTree(node->leftChild.get(),path);
        path.pop_back();

        path.push_back(1);
        getCodeTree(node->rightChild.get(),path);
        path.pop_back();
    }
}

bool Node_freq::operator <(const Node_freq & other)const{
    if (freq > other.freq)
        return true;
    else if (freq < other.freq)
        return false;
    else if (minSymbol > other.minSymbol)
        return true;
    else if (minSymbol < other.minSymbol)
        return false;
    else
        return false;
}

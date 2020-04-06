#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <QScopedPointer>
#include <QVector>
#include <utility>
#include <memory>

class Node
{
public:
    quint32 symbol;
    std::unique_ptr <Node> leftChild;
    std::unique_ptr <Node> rightChild;
    QString code;
    Node(quint32 sym);
    Node(quint32 sym, std::unique_ptr <Node> &&left, std::unique_ptr <Node> &&right);

};
class Node_freq
{
public:
    std::unique_ptr <Node> node;
    quint32 minSymbol;
    quint32 freq;
    Node_freq(Node * nd, quint32 minSym, quint32 f);
    bool operator <(const Node_freq &other) const;
};

class HuffmanTree
{
public:
    //Node root;
    QVector< QVector<char> > codes;
    //QVector<quint32> lengths;
public:
    HuffmanTree(quint32 symbolLimit);
    void getCodeTree(Node * node, QVector<char> &path);
    QVector<char> getCode(quint32 sym)const;
    Node* createTree(quint32 * freq);
    void simplifytheTree();
    void reGetCode(Node * node);
};


#endif // HUFFMANTREE_H

#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <QtCore/QVector>
#include "QList"
#include "string"
class MerkleTree{
    //这是个工具类，你不需要实例化，我在静态方法中会给返回的指针分配内存，你记得用完之后delete[]  即可。
public:
    typedef struct TreeNode{
        quint16 left;
        quint16 right;
        std::string hash;
    }TreeNode;
    static QList<int> modifyCheck(QList<std::string> article,QVector<std::string>* merkleIndex);//false是指此段被修改,这个数组为段数＋1大小，即下表为0的项直接不作考虑，下表跟段号是直接对应的
    static QVector<std::string>* getMerkleArray(QList<std::string> article);//需要先调用generateMerkelTreeIntoArray才会分配内存
    //直接放着把，开一次资源就行
    //std::string* merkleIndex;
};

#endif // MERKLE_TREE_H

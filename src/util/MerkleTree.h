#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H
#include "QList"
#include "string"
class MerkleTree{
public:
    typedef struct TreeNode{
        int id;
        int para;//-1表示非叶节点
        int left;
        int right;
        std::string hash;
    }TreeNode;
    MerkleTree(const QList<std::string> article,std::string*& merkleArray);//返回值是数组大小
    QList<int> modifyCheck(QList<std::string> article);//false是指此段被修改,这个数组为段数＋1大小，即下表为0的项直接不作考虑，下表跟段号是直接对应的
    //std::string* getMerkleArray();//需要先调用generateMerkelTreeIntoArray才会分配内存
    ~MerkleTree();
    QVector<TreeNode> nodeList;//直接放着把，开一次资源就行
    std::string* merkleIndex;
};

#endif // MERKLE_TREE_H

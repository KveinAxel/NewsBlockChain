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
    QList<bool> modifyCheck(QList<std::string> article,std::string* merkleIndex);//false是指此段被修改,这个数组为段数＋1大小，即下表为0的项直接不作考虑，下表跟段数是直接对应的
    int generateMerkelTreeIntoArray(const QList<std::string> article);//返回值是数组大小
    std::string* getMerkleArray();//需要先调用generateMerkelTreeIntoArray才会分配内存
    ~MerkleTree();
private:
    std::string* merkleArray;//这个数组，尾部才是merkle树根的哈希值
};

#endif // MERKLE_TREE_H

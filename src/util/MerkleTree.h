#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H
#include "QList"
#include "string"
class MerkleTree{
    //我给的接口有点糊，我当时脑子有点糊，我在调用modifyCheck时会保证待检测的文章与区块体中文章段数一定一样，这块你不要担心出bug，我建议你把merkle树改了吧，
    //这种TreeNode的结构太占空间，你该成不需要QVector<TreeNode> nodeList作为成员的，而是std::string* merkleIndex作为成员的数组树吧，要不你展示的时候没有特色
    //std::string* merkleIndex作为成员的数组树就是只需要数组指针就可以了，id相当于数组坐标，你可以上网搜，或是其他的高效结构，但是你返回的是QList<int>就行了
    //比如1，3，7段被改了，放回list（1，3，7），我最近家里有点事，可能没时间，如果你做完了，可以帮凡神做一下dev分支吧，本来是我做的
public:
    typedef struct TreeNode{
        qint16 left;
        qint16 right;
        std::string hash;
    }TreeNode;
    MerkleTree(const QList<std::string> article);//返回值是数组大小
    QList<int> modifyCheck(QList<std::string> article);//false是指此段被修改,这个数组为段数＋1大小，即下表为0的项直接不作考虑，下表跟段号是直接对应的
    //std::string* getMerkleArray();//需要先调用generateMerkelTreeIntoArray才会分配内存
    std::string merkleRoot();
    ~MerkleTree();
    QVector<TreeNode> nodeList;//直接放着把，开一次资源就行
    //std::string* merkleIndex;
};

#endif // MERKLE_TREE_H

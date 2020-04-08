#include "MerkleTree.h"
#include "Hash.h"
#include "QVector"
#include "QQueue"
MerkleTree::~MerkleTree() {
    delete[] merkleIndex;
}
QList<int> MerkleTree::modifyCheck(QList<std::string> article) {
    int ID = 0;
    int paraNum = article.size();
    for(int i=0;i<paraNum;i++){
        Hash hashCode(article.at(i));

        TreeNode newTreeNode;
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;
        newTreeNode.left = -1;
        newTreeNode.right = -1;
        newTreeNode.para = i+1;

        nodeList.push_back(newTreeNode);
    }
    for(int i=0;i<nodeList.size();i+=2){
        TreeNode newTreeNode;
        Hash hashCode(nodeList.at(i).hash+nodeList.at(i+1).hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;
        newTreeNode.left = nodeList.at(i).id;
        newTreeNode.right = nodeList.at(i+1).id;//这样改高效一点，以后编程也要尽量这样，时间上也差不多，应为文章段数比较小
        newTreeNode.para = -1;
        nodeList.push_back(newTreeNode);
        if(nodeList.size()+1==2*i){
            break;
        }
    }
    QList<int> output;
    if(nodeList.last().hash == merkleIndex[nodeList.size()-1]){
        return output;
    } else{
        QQueue<TreeNode> q;
        q.push_back(nodeList[paraNum-1]);
        do{
            TreeNode nextSearch = q.front();
            q.pop_front();
            if(nodeList[nextSearch.left].hash != merkleIndex[nextSearch.left]){
                if(nodeList[nextSearch.left].para != -1){
                    output[nextSearch.left+1] = false;
                }else{
                    q.push_back(nodeList[nextSearch.left]);
                }
            }
            if(nodeList[nextSearch.right].hash != merkleIndex[nextSearch.right]){
                if(nodeList[nextSearch.right].para != -1){
                    output[nextSearch.right+1] = false;
                }else{
                    q.push_back(nodeList[nextSearch.right]);
                }
            }
        }while(!q.empty());
    }
    return output;
}
MerkleTree::MerkleTree(const QList<std::string> article,std::string*& merkleArray){
    int ID = 0;
    int paraNum = article.size();
    for(int i=0;i<paraNum;i++){
        Hash hashCode(article.at(i));

        TreeNode newTreeNode;
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;

        nodeList.push_back(newTreeNode);
    }
    for(int i=0;i<nodeList.size();i+=2){
        TreeNode newTreeNode;
        Hash hashCode(nodeList.at(i).hash+nodeList.at(i+1).hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;
        nodeList.push_back(newTreeNode);
        if(nodeList.size()+1==2*i){
            break;
        }
    }
    merkleArray = new string[nodeList.size()];
    this->merkleIndex=merkleArray;
    for(int i=0;i<nodeList.size();i++){
        merkleArray[i] = nodeList.at(i).hash;
    }
    //return ID;
}

//std::string * MerkleTree::getMerkleArray() {
//    return merkleArray;
//}这个不需要了，我直接在block里掉成员,是我之前搞得有点复杂

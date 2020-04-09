#include "MerkleTree.h"
#include "Hash.h"
#include "QVector"
#include "QQueue"
QList<int> MerkleTree::modifyCheck(QList<std::string> article,QVector<std::string>* merkleIndex) {
    int paraNum = article.size();
    QVector<TreeNode> nodeList;
    for(int i=0;i<paraNum;i++){
        Hash hashCode(article.at(i));

        TreeNode newTreeNode;
        newTreeNode.hash = hashCode.toString();
        newTreeNode.left = -1;
        newTreeNode.right = -1;

        nodeList.push_back(newTreeNode);
    }
    for(int i=0;i<nodeList.size();i+=2){
        TreeNode newTreeNode;
        Hash hashCode(nodeList.at(i).hash+nodeList.at(i+1).hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.left = i;
        newTreeNode.right = i+1;//这样改高效一点，以后编程也要尽量这样，时间上也差不多，应为文章段数比较小
        nodeList.push_back(newTreeNode);
        if(nodeList.size() < i+2){
            break;
        }
    }
    QList<int> output;
    if(nodeList.last().hash == merkleIndex->last()){
        return output;
    } else{
        QQueue<TreeNode> q;
        q.push_back(nodeList[paraNum-1]);
        do{
            TreeNode nextSearch = q.front();
            q.pop_front();
            if(nodeList[nextSearch.left].hash != merkleIndex->at(nextSearch.left)){
                if(nextSearch.left < article.size()){
                    output.append(nextSearch.left+1);
                }else{
                    q.push_back(nodeList[nextSearch.left]);
                }
            }
            if(nodeList[nextSearch.right].hash != merkleIndex->at(nextSearch.right)){
                if(nextSearch.right < article.size()){
                    output.append(nextSearch.right+1);
                }else{
                    q.push_back(nodeList[nextSearch.right]);
                }
            }
        }while(!q.empty());
    }
    return output;
}
QVector<std::string>* MerkleTree::getMerkleArray(QList<std::string> article){
    int paraNum = article.size();
    QVector<TreeNode> nodeList;
    for(int i=0;i<paraNum;i++){
        Hash hashCode(article.at(i));

        TreeNode newTreeNode;
        newTreeNode.hash = hashCode.toString();

        nodeList.push_back(newTreeNode);
    }
    for(int i=0;i<nodeList.size();i+=2){
        TreeNode newTreeNode;
        Hash hashCode(nodeList.at(i).hash+nodeList.at(i+1).hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.left = i;
        newTreeNode.right = i+1;//这样改高效一点，以后编程也要尽量这样，时间上也差不多，应为文章段数比较小
        nodeList.push_back(newTreeNode);
        if(nodeList.size() < i+2){
            break;
        }
    }
    QVector<std::string>* merkleIndex;
    merkleIndex = new QVector<std::string>;
    for(int i=0;i<nodeList.size();i++){
        merkleIndex->push_back(nodeList.at(i).hash);
    }
    return merkleIndex;
}

//std::string * MerkleTree::getMerkleArray() {
//    return merkleArray;
//}这个不需要了，我直接在block里掉成员,是我之前搞得有点复杂

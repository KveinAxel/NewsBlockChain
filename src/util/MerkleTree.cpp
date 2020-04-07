#include "MerkleTree.h"
#include "Hash.h"
#include "QVector"
#include "QQueue"
MerkleTree::~MerkleTree() {
    delete[] merkleArray;
}
QList<bool> MerkleTree::modifyCheck(QList<std::string> article, std::string* merkleIndex) {
    int ID = 0;
    int paraNum = article.size();
    QVector<TreeNode> nodeList;
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
        TreeNode leftNode = nodeList.at(i);
        TreeNode rightNode = nodeList.at(i+1);
        TreeNode newTreeNode;
        Hash hashCode(leftNode.hash+rightNode.hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;
        newTreeNode.left = leftNode.id;
        newTreeNode.right = rightNode.id;
        newTreeNode.para = -1;
        nodeList.push_back(newTreeNode);
        if(nodeList.size()-i-2 < 2){
            break;
        }
    }
    QList<bool> output;
    for(int i=0;i<paraNum;i++){
        output.push_back(true);
    }
    if(nodeList.at(paraNum-1).hash == merkleIndex[paraNum-1]){
        return output;
    } else{
        QQueue<TreeNode> q;
        q.push_back(nodeList[paraNum-1]);
        do{
            TreeNode nextSearch = q.front();
            q.pop_front();
            if(nodeList[nextSearch.left].hash != merkleIndex[nextSearch.left]){
                if(nodeList[nextSearch.left].para != -1){
                    output[nextSearch.left] = false;
                }else{
                    q.push_back(nodeList[nextSearch.left]);
                }
            }
            if(nodeList[nextSearch.right].hash != merkleIndex[nextSearch.right]){
                if(nodeList[nextSearch.right].para != -1){
                    output[nextSearch.right] = false;
                }else{
                    q.push_back(nodeList[nextSearch.right]);
                }
            }
        }while(!q.empty());
    }
    return output;
}

int MerkleTree::generateMerkelTreeIntoArray(const QList<std::string> article) {
    int ID = 0;
    int paraNum = article.size();
    QVector<TreeNode> nodeList;
    for(int i=0;i<paraNum;i++){
        Hash hashCode(article.at(i));

        TreeNode newTreeNode;
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;

        nodeList.push_back(newTreeNode);
    }
    for(int i=0;i<nodeList.size();i+=2){
        TreeNode leftNode = nodeList.at(i);
        TreeNode rightNode = nodeList.at(i+1);
        TreeNode newTreeNode;
        Hash hashCode(leftNode.hash+rightNode.hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.id = ID++;
        nodeList.push_back(newTreeNode);
        if(nodeList.size()-i-2 < 2){
            break;
        }
    }
    merkleArray = new string[nodeList.size()];
    for(int i=0;i<nodeList.size();i++){
        merkleArray[i] = nodeList.at(i).hash;
    }
    return ID;
}

std::string * MerkleTree::getMerkleArray() {
    return merkleArray;
}
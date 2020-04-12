#include "MerkleTree.h"

Message<std::vector<int>> MerkleTree::modifyCheck(std::vector<std::string> article) {
    // 构建新默克尔树
    auto newMerkleTree = MerkleTree(article);
    auto& newNodeList = newMerkleTree.nodeList;

    std::vector<int> *output = new std::vector<int>;
    if (newNodeList.back().hash == this->nodeList.back().hash)
        return Message<std::vector<int>>::success("无篡改");
    else if (newNodeList.size() == 1)
        return Message<std::vector<int>>(400, "有篡改", new std::vector<int>({1}));
    else {
        // 查找错误段落位置
        std::queue<TreeNode> q;
        q.push(newNodeList.back());
        while (!q.empty()) {
            // 取出不匹配节点
            TreeNode index = q.front();
            q.pop();
            auto leftNode = nodeList.at(index.left);
            auto rightNode = nodeList.at(index.right);
            if (leftNode.hash != this->nodeList.at(index.left).hash) {
                if (leftNode.left == -1 && leftNode.right == -1)
                    output->push_back(index.left + 1);
                else
                    q.push(leftNode);
            }
            if (rightNode.hash != this->nodeList[index.right].hash) {
                if (rightNode.left == -1 && rightNode.right == -1)
                    output->push_back(index.right + 1);
                else
                    q.push(rightNode);
            }
        }
    }
    return Message<std::vector<int>>(400, "有篡改", output);
}

MerkleTree::MerkleTree(const std::vector<std::string> article) {
    // 段落号
    int paraNum = article.size();
    // 构建默克尔树叶子节点
    for (int i = 0; i < paraNum; i++) {
        Hash hashCode(article.at(i));
        TreeNode newTreeNode;
        newTreeNode.hash = hashCode.toString();
        nodeList.push_back(newTreeNode);
    }
    // 构建默克尔树非叶子节点
    for (int i = 0; i < nodeList.size(); i += 2) {
        TreeNode newTreeNode;
        Hash hashCode(nodeList.at(i).hash + nodeList.at(i + 1).hash);
        newTreeNode.hash = hashCode.toString();
        newTreeNode.left = i;
        newTreeNode.right = i + 1;
        nodeList.push_back(newTreeNode);
        if (nodeList.size() == i + 3) {
            break;
        }
    }
}

std::string MerkleTree::merkleRootHash() {
    return Hash(nodeList.back().hash).toString();
}

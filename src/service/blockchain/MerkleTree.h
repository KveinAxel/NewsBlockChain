#ifndef NEWS_BLOCK_CHAIN_BLOCK_CHAIN_MERKLE_TREE_H
#define NEWS_BLOCK_CHAIN_BLOCK_CHAIN_MERKLE_TREE_H

#include <vector>
#include <string>
#include <service/hash/Hash.h>
#include <queue>
#include <Message.h>

/**
 * 默克尔树
 */
class MerkleTree {
public:

    typedef struct TreeNode {
        uint32_t left;
        uint32_t right;
        std::string hash;
    } TreeNode;

    /**
     * 传入一篇文章，构造默克尔树
     * @param article
     */
    MerkleTree(const std::vector<std::string> article);

    /**
     * 篡改检测
     * code = 200 无篡改
     * code  = 400 有篡改 篡改放在data里
     * @param article 文章
     * @return vector 中的int说明段落号
     */
    Message<std::vector<int>> modifyCheck(std::vector<std::string> article);

    /**
     * 默克尔树根的哈希值
     * @return
     */
    std::string merkleRootHash();

    std::vector<TreeNode> nodeList;
};

#endif // NEWS_BLOCK_CHAIN_BLOCK_CHAIN_MERKLE_TREE_H

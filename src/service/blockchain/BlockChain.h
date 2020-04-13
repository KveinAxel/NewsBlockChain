#ifndef NEWS_BLOCK_CHAIN_BLOCK_CHAIN_BLOCK_CHAIN_H
#define NEWS_BLOCK_CHAIN_BLOCK_CHAIN_BLOCK_CHAIN_H

#include "Block.h"
#include <map>
#include <service/hash/Hash.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class BlockChain {
public:
    /**
     * 区块头哈希与区块的映射
     */
    std::map<std::string, BlockObj*> blockChainHash;

    /**
     * 区块头列表
     */
    std::vector<std::string> blockChainHeadList;
    /**
     * 本地最新区块的hash
     */
    std::string lastHash;

     /**
      * 更新区块链
      * @param block
      * @return
      */
    bool updateBlock(std::string block);

    /**
     * 选定区块后检测篡改
     * @param article
     * @param keyOfResponse
     * @return
     */
    Message<std::vector<int>> modifyCheckLocal(const std::vector<std::string> &article, std::string &keyOfResponse);

    /**
     * 本地拿到文章产生块，返回区块头的哈希
     * @param article
     * @return
     */
    std::string appendBlock(const std::vector<std::string> &article);

    /**
     * 返回指定key以后的所有区块
     * @param keyOfResponse
     * @return
     */
    Message<std::pair<std::string, int>> responseBlockList(std::string key);

    std::string serialize();

    static BlockChain* deserialize(std::string blockchain);
};

#endif // NEWS_BLOCK_CHAIN_BLOCK_CHAIN_BLOCK_CHAIN_H

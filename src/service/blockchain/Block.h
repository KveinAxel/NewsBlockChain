#ifndef NEWS_BLOCK_CHAIN_BLOCK_CHAIN_BLOCK_H
#define NEWS_BLOCK_CHAIN_BLOCK_CHAIN_BLOCK_H

#include <ctime>
#include <string>
#include "MerkleTree.h"
#include <service/searcher/Searcher.h>
#include <service/searcher/SearchResultImpl.h>
#include <service/searcher/SearcherImpl.h>
#include <service/hash/Hash.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <service/compressor/Compressor.h>

class BlockObj {
public:
    /**
     * 上一个区块头的Hash
     */
    std::string previousHash;

    /**
     * 当前区块的hash
     */
    std::string currentHash;

    /**
     * 出块时间
     */
    time_t createdTime;

    /**
     * 默克尔树的树根的hash
     */
    std::string merkleRootHash;

    /**
     * 默克尔树
     */
    MerkleTree *merkletree;

    /**
     * 分段的文章
     */
    std::vector<std::string> article;

    /**
     * 序列化字典
     */
    std::string serializedDict;

    /**
     * 数据压缩后的字节数组
     */
    std::vector<uint32_t> bytes;

    /**
     * 填充长度
     */
    uint32_t filler = 0;

    /**
     * 文章构造区块
     * @param article
     * @param lastHashKey
     */
    BlockObj(const std::vector<std::string> &article, std::string previousHash);

    /**
     * 拷贝构造区块
     * @param article
     * @param lastHashKey
     */
    BlockObj(const std::vector<std::string> &article, std::string previousHash, std::string currentHash,
             time_t created_time);

    /**
     * 返回块头的的hash
     * @return
     */
    std::string blockHeadHash();

    /**
     * 篡改检查
     * @param article
     * @return
     */
    Message<std::vector<int>> modifyCheck(const std::vector<std::string> article);

    ~BlockObj();

    /**
     * 序列化
     * @return
     */
    std::string serialize();

    static BlockObj *deserialize(std::string block);

    int searchKeyword(const std::vector<std::string> &keywords_list);

    std::vector<std::string>* getArticle();
};

#endif // NEWS_BLOCK_CHAIN_BLOCK_CHAIN_BLOCK_H

#ifndef NEWS_BLOCK_CHAIN_BLOCK_CHAIN_SERVICE_H
#define NEWS_BLOCK_CHAIN_BLOCK_CHAIN_SERVICE_H
#include <string>
#include <service/hash/Hash.h>
#include <vector>
#include <Message.h>

class BlockChainService {
public:
    /**
     * 将一篇文章加入到区块链
     * @param article 文章
     * @return 返回结果被含成功与否，如果失败请说明原因
     */
    static Message<std::string> addToBlockChain(std::string article);

    /**
     * 传入一篇文章，返回是否篡改
     * @param article 文章
     * @return 无篡改返回200， 有篡改返回400， 其他事件返回500
     */
    static Message<std::vector<int>> confirmArticle(std::string article, std::string hash);

    /**
     * 获取所有区块头哈希及时间的列表
     */
     static Message<std::vector<std::pair<std::string, time_t>>> list();

     /**
      * 获取整条序列化后的区块链
      * @return
      */
     static Message<std::pair<std::string, int>> getBlockChain();

     /**
      * 将广播到本地的区块加入到本地
      * @param block 区块
      * @return
      */
     static Message<std::string> broadcast(std::string block);

     /**
      * 获取区块头列表
      * @return
      */
     static Message<std::vector<std::string>> getBlockHeadHashList();

     /**
      * 获取key以后的区块
      * @param keyList
      * @return
      */
     static Message<std::pair<std::vector<std::string>, int>> getBlockList(std::string key);
};


#endif // NEWS_BLOCK_CHAIN_BLOCK_CHAIN_SERVICE_H

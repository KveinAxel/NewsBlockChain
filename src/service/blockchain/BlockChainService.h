#ifndef NEWS_BLOCK_CHAIN_BLOCK_CHAIN_SERVICE_H
#define NEWS_BLOCK_CHAIN_BLOCK_CHAIN_SERVICE_H

#include <string>
#include <service/hash/Hash.h>
#include "../../Message.h"

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
    static Message<std::string> confirmArticle(std::string article);

    /**
     * 获取所有区块头哈希及时间
     */
     static Message<std::pair<byte, std::string>> list();
};


#endif // NEWS_BLOCK_CHAIN_BLOCK_CHAIN_SERVICE_H

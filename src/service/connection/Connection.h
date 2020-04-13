#ifndef NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H
#define NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H

#include <string>
#include <Message.h>
#include <vector>

class Connection {
public:
    /**
     * 注册成为普通节点
     * @return
     */
    static Message<std::string> node();

    /**
     * 注册成为超级节点
     * @return
     */
    static Message<std::string> superNone();

    /**
     * 将区块广播至普通节点
     * @param block
     * @return
     */
    static Message<std::string> broadcastBlockToNode(std::string block, std::string url, int port);

    /**
     * 将区块广播至超级节点
     * @param block
     * @param url
     * @param port
     * @return
     */
    static Message<std::string> broadcastBlockToSuperNode(std::string block, std::string url, int port);

    /**
     * 将区块广播至DNS
     * @param block
     * @return
     */
    static Message<std::string> broadcastBlockToDNS(std::string block);

    /**
     * 从零获取整条区块链
     * @return
     */
    static Message<std::string> getBlockChain();

    /**
     * 增量更新区块链
     * @return
     */
    static Message<std::string> getBlockChainPartly();
};


#endif // NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H

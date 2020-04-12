#ifndef NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H
#define NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H
#include <string>
#include <Message.h>

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
     * 从上级节点获取区块数据
     * @param url
     * @return
     */
    static Message<std::string> getBlockChainData(std::string url, int port);

    /**
     * 将区块广播至普通节点
     * @param block
     * @return
     */
    static Message<std::string> broadcastBlockToNode(std::string block, std::string url, int port);

    /**
     * 将区块广播至DNS
     * @param block
     * @return
     */
    static Message<std::string> broadcastBlockToDNS(std::string block);
};


#endif // NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H

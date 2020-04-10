#ifndef NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H
#define NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H
#include <string>
#include <Message.h>
class Connection {
    static Message<std::string> getServerURL();

    static Message<std::string> getBlockChainData(std::string url);
};


#endif // NEWS_BLOCK_CHAIN_CONNECTION_SERVICE_H

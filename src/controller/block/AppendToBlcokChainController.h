#ifndef NEWS_BLOCK_CHAIN_APPEND_TO_BLOCK_CHAIN_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_APPEND_TO_BLOCK_CHAIN_CONTROLLER_H
#include "../BaseController.h"


/**
 * 我有一篇文章，我要加入区块链
 */
class AppendToBlockChain: public BaseController {
public:
    AppendToBlockChain();

    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // NEWS_BLOCK_CHAIN_APPEND_TO_BLOCK_CHAIN_CONTROLLER_H

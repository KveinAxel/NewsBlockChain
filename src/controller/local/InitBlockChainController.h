#ifndef NEWS_BLOCK_CHAIN_INIT_BLOCKCHAIN_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_INIT_BLOCKCHAIN_CONTROLLER_H

#include <controller/BaseController.h>
class InitBlockChainController :public BaseController{
public:
    InitBlockChainController();

    void service(const httplib::Request &req, httplib::Response &res) override;

};


#endif // NEWS_BLOCK_CHAIN_INIT_BLOCKCHAIN_CONTROLLER_H

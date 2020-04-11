#ifndef NEWS_BLOCK_CHAIN_BROADCAST_BLOCK_BY_NODE_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_BROADCAST_BLOCK_BY_NODE_CONTROLLER_H

#include <controller/BaseController.h>

class BroadcastBlockByNodeController: public BaseController {
public:
    BroadcastBlockByNodeController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_BROADCAST_BLOCK_BY_NODE_CONTROLLER_H

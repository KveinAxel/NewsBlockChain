#ifndef NEWS_BLOCK_CHAIN_RECEIVE_BLOCK_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_RECEIVE_BLOCK_CONTROLLER_H


#include <controller/BaseController.h>

class BroadcastBlockBySuperNodeController : public BaseController {
public:
    BroadcastBlockBySuperNodeController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_RECEIVE_BLOCK_CONTROLLER_H

#ifndef NEWS_BLOCK_CHAIN_RECEIVE_BLOCK_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_RECEIVE_BLOCK_CONTROLLER_H


#include <controller/BaseController.h>

class ReceiveBlockController : public BaseController {
public:
    ReceiveBlockController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_RECEIVE_BLOCK_CONTROLLER_H

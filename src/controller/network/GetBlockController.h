#ifndef NEWS_BLOCK_CHAIN_GET_BLOCK_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_GET_BLOCK_CONTROLLER_H

#include <controller/BaseController.h>

class GetBlockController: public BaseController {
public:
    GetBlockController();

    void service(const httplib::Request &req, httplib::Response &res) override;

};


#endif // NEWS_BLOCK_CHAIN_GET_BLOCK_CONTROLLER_H

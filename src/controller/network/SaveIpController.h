#ifndef NEWS_BLOCK_CHAIN_SAVE_IP_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_SAVE_IP_CONTROLLER_H


#include <controller/BaseController.h>

class SaveIpController : public BaseController {
public:
    SaveIpController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_SAVE_IP_CONTROLLER_H

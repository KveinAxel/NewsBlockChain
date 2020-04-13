#ifndef NEWS_BLOCK_CHAIN_LOAD_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_LOAD_CONTROLLER_H
#include <controller/BaseController.h>

class LoadController: public BaseController {
public:
    LoadController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_LOAD_CONTROLLER_H

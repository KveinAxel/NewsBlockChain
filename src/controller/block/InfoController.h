#ifndef NEWS_BLOCK_CHAIN_INFO_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_INFO_CONTROLLER_H
#include "../BaseController.h"

class InfoController: public BaseController {
public:
    InfoController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // NEWS_BLOCK_CHAIN_INFO_CONTROLLER_H

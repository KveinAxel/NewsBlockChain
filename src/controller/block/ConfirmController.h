#ifndef NEWS_BLOCK_CHAIN_CONFIRM_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_CONFIRM_CONTROLLER_H

#include "../BaseController.h"

class ConfirmController: public BaseController {
public:
    ConfirmController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // NEWS_BLOCK_CHAIN_CONFIRM_CONTROLLER_H

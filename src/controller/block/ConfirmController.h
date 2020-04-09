#ifndef NEWS_BLOCK_CHAIN_CONFIRM_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_CONFIRM_CONTROLLER_H

#include "../BaseController.h"

/**
 * 我给你一篇区块链有的文章，你给我检测有没有篡改
 */
class ConfirmController: public BaseController {
public:
    ConfirmController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // NEWS_BLOCK_CHAIN_CONFIRM_CONTROLLER_H

#ifndef NEWS_BLOCK_CHAIN_LIST_HASH_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_LIST_HASH_CONTROLLER_H

#include "../BaseController.h"

/**
 * 查看区块链历史文章
 */
class ListHashController: public BaseController {
public:
    ListHashController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};
#endif // NEWS_BLOCK_CHAIN_LIST_HASH_CONTROLLER_H

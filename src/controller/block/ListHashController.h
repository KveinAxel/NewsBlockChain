#ifndef NEWS_BLOCK_CHAIN_LIST_HASH_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_LIST_HASH_CONTROLLER_H

#include "../BaseController.h"

class ListHashController: public BaseController {
public:
    ListHashController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};
#endif // NEWS_BLOCK_CHAIN_LIST_HASH_CONTROLLER_H

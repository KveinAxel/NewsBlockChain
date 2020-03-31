#ifndef NEWS_BLOCK_CHAIN_SEARCH_BLOCKS_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_SEARCH_BLOCKS_CONTROLLER_H

#include "../BaseController.h"

class SearchBlocksController: public BaseController {
public:
    SearchBlocksController();
    
    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // NEWS_BLOCK_CHAIN_SEARCH_BLOCKS_CONTROLLER_H

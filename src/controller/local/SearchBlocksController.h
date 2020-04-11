#ifndef NEWS_BLOCK_CHAIN_SEARCH_BLOCKS_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_SEARCH_BLOCKS_CONTROLLER_H

#include "../BaseController.h"

/**
 * 我给你至少三个关键字，你给我统计所有新闻中关键字出现的次数，并返回次数最高的三篇文章
 */
class SearchBlocksController: public BaseController {
public:
    SearchBlocksController();
    
    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // NEWS_BLOCK_CHAIN_SEARCH_BLOCKS_CONTROLLER_H

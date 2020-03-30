#ifndef SEARCH_BLOCKS_CONTROLLER_H
#define SEARCH_BLOCKS_CONTROLLER_H

#include "../BaseController.h"

class SearchBlocksController: public BaseController {
public:
    SearchBlocksController();
    
    void service(const httplib::Request &req, httplib::Response &res) override;
};

#endif // SEARCH_BLOCKS_CONTROLLER_H

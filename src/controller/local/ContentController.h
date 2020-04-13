#ifndef NEWS_BLOCK_CHAIN_CONTENTCONTROLLER_H
#define NEWS_BLOCK_CHAIN_CONTENTCONTROLLER_H

#include "../BaseController.h"

class ContentController: public BaseController  {
public:
    ContentController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif //NEWS_BLOCK_CHAIN_CONTENTCONTROLLER_H

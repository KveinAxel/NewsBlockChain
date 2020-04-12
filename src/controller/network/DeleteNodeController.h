#ifndef NEWS_BLOCK_CHAIN_DELETENODECONTROLLER_H
#define NEWS_BLOCK_CHAIN_DELETENODECONTROLLER_H

#include <controller/BaseController.h>

class DeleteNodeController: public BaseController {
public:
    DeleteNodeController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif //NEWS_BLOCK_CHAIN_DELETENODECONTROLLER_H

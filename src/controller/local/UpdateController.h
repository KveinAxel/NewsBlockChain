#ifndef NEWS_BLOCK_CHAIN_UPDATE_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_UPDATE_CONTROLLER_H

#include "../BaseController.h"
class UpdateController :public BaseController{
public:
    UpdateController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_UPDATE_CONTROLLER_H

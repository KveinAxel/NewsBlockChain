#ifndef NEWS_BLOCK_CHAIN_UPDATE_PARTLY_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_UPDATE_PARTLY_CONTROLLER_H

#include "../BaseController.h"
class UpdatePartlyController :public BaseController{
public:
    UpdatePartlyController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_UPDATE_PARTLY_CONTROLLER_H

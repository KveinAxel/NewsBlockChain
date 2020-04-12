#ifndef NEWS_BLOCK_CHAIN_GET_BLOCK_PARTLY_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_GET_BLOCK_PARTLY_CONTROLLER_H
#include <controller/BaseController.h>

/**
 * 增量更新区块链
 */
class GetBlockPartlyController : public BaseController{
public:
    GetBlockPartlyController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_GET_BLOCK_PARTLY_CONTROLLER_H

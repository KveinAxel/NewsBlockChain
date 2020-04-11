#ifndef NEWS_BLOCK_CHAIN_REGISTER_SUPERNODE_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_REGISTER_SUPERNODE_CONTROLLER_H

#include <controller/BaseController.h>

/**
 * 前端发送请求至后端，后端向DNS发送请求注册为超级节点
 */
class RegisterSuperNodeController: public BaseController {
public:
    RegisterSuperNodeController();

    void service(const httplib::Request &req, httplib::Response &res) override;
};


#endif // NEWS_BLOCK_CHAIN_REGISTER_SUPERNODE_CONTROLLER_H

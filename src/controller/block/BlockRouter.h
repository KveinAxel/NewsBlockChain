#ifndef BLOCK_ROUTER_H
#define BLOCK_ROUTER_H
#include "Router.h"

class BlockRouter : public Router {
public:
    /**
     * 构造器
     * @param server 服务器实例指针
     */
    explicit BlockRouter(httplib::Server *server);

    /**
     * 路径注册
     */
    void routeRegister() override;
};

#endif // BLOCK_ROUTER_H

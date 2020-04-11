#ifndef NEWS_BLOCK_CHAIN_NETWORK_ROUTER_H
#define NEWS_BLOCK_CHAIN_NETWORK_ROUTER_H
#include <Router.h>

class NetworkRouter: public Router {
public:
    /**
     * 构造器
     * @param server 服务器实例指针
     */
    explicit NetworkRouter(httplib::Server *server);

    /**
     * 路径注册
     */
    void routeRegister() override;
};


#endif // NEWS_BLOCK_CHAIN_NETWORK_ROUTER_H

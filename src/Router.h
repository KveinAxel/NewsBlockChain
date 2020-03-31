#ifndef NEWS_BLOCK_CHAIN_ROUTER_H
#define NEWS_BLOCK_CHAIN_ROUTER_H

#include "../ext/cpp-httplib/httplib.h"

class Router{
protected:
    httplib::Server *server;
public:

    /**
     * 构造器
     * @param server 服务器实例指针
     */
    explicit Router(httplib::Server *server);

    /**
     * 路径注册
     */
    virtual void routeRegister();

};

#endif // NEWS_BLOCK_CHAIN_ROUTER_H

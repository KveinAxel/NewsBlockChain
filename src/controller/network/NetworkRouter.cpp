#include "NetworkRouter.h"

NetworkRouter::NetworkRouter(httplib::Server *server) : Router(server) { }

void NetworkRouter::routeRegister() {
    this->server->Get("/network/receiveBlock", [](const httplib::Request& req, httplib::Response& res) {
        // todo 将被广播区块加入本地，并广播下一层
    });
    this->server->Get("/network/saveIp", [](const httplib::Request& req, httplib::Response& res) {
        // todo 保存ip至本地以便广播
    });
}

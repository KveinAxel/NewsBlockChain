#include "NetworkRouter.h"
#include <controller/network/BroadcastBlockByNodeController.h>
#include <controller/network/BroadcastBlockBySuperNodeController.h>
#include <controller/network/GetBlockController.h>
#include <controller/network/SaveIpController.h>

NetworkRouter::NetworkRouter(httplib::Server *server) : Router(server) { }

void NetworkRouter::routeRegister() {
    this->server->Get("/network/broadcastBlockBySuperNode", [](const httplib::Request& req, httplib::Response& res) {
        BroadcastBlockBySuperNodeController().service(req, res);
    });
    this->server->Get("/network/broadcastBlockByNode", [](const httplib::Request& req, httplib::Response& res) {
        BroadcastBlockByNodeController().service(req, res);
    });
    this->server->Get("/network/saveIp", [](const httplib::Request& req, httplib::Response& res) {
        SaveIpController().service(req, res);
    });
    this->server->Get("/network/getBlock", [](const httplib::Request& req, httplib::Response& res) {
        GetBlockController().service(req, res);
    });

}

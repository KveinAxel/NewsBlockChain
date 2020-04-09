#include "BlockRouter.h"
#include "ConfirmController.h"
#include "AppendToBlcokChainController.h"
#include "ListHashController.h"
#include "SearchBlocksController.h"


void BlockRouter::routeRegister() {
    this->server->Get("/block/confirm", [](const httplib::Request& req, httplib::Response& res) {
        ConfirmController().service(req, res);
    });
    this->server->Get("/block/append", [](const httplib::Request& req, httplib::Response& res) {
        AppendToBlockChain().service(req, res);
    });
    this->server->Get("/block/list", [](const httplib::Request& req, httplib::Response& res) {
        ListHashController().service(req, res);
    });
    this->server->Get("/block/search", [](const httplib::Request& req, httplib::Response& res) {
        SearchBlocksController().service(req, res);
    });

}

BlockRouter::BlockRouter(httplib::Server *server) : Router(server) {}

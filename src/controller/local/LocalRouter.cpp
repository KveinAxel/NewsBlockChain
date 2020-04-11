#include "LocalRouter.h"
#include "ConfirmController.h"
#include "AppendToBlcokChainController.h"
#include "ListHashController.h"
#include "SearchBlocksController.h"


void LocalRouter::routeRegister() {
    this->server->Get("/local/confirm", [](const httplib::Request& req, httplib::Response& res) {
        ConfirmController().service(req, res);
    });
    this->server->Get("/local/append", [](const httplib::Request& req, httplib::Response& res) {
        AppendToBlockChain().service(req, res);
    });
    this->server->Get("/local/list", [](const httplib::Request& req, httplib::Response& res) {
        ListHashController().service(req, res);
    });
    this->server->Get("/local/search", [](const httplib::Request& req, httplib::Response& res) {
        SearchBlocksController().service(req, res);
    });

}

LocalRouter::LocalRouter(httplib::Server *server) : Router(server) {}

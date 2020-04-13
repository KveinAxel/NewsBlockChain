#include "LocalRouter.h"
#include "ConfirmController.h"
#include "AppendToBlcokChainController.h"
#include "ListHashController.h"
#include "SearchBlocksController.h"
#include "RegisterSuperNodeController.h"
#include "InitBlockChainController.h"
#include "ContentController.h"
#include "RegisterNodeController.h"
#include <controller/local/SaveController.h>
#include <controller/local/LoadController.h>

void LocalRouter::routeRegister() {
    this->server->Get("/local/confirm", [](const httplib::Request &req, httplib::Response &res) {
        ConfirmController().service(req, res);
    });
    this->server->Get("/local/append", [](const httplib::Request &req, httplib::Response &res) {
        AppendToBlockChain().service(req, res);
    });
    this->server->Get("/local/list", [](const httplib::Request &req, httplib::Response &res) {
        ListHashController().service(req, res);
    });
    this->server->Get("/local/search", [](const httplib::Request &req, httplib::Response &res) {
        SearchBlocksController().service(req, res);
    });
    this->server->Get("/local/superNode", [](const httplib::Request &req, httplib::Response &res) {
        RegisterSuperNodeController().service(req, res);
    });
    this->server->Get("/local/init", [](const httplib::Request &req, httplib::Response &res) {
        InitBlockChainController().service(req, res);
    });
    this->server->Get("/local/content", [](const httplib::Request &req, httplib::Response &res) {
        ContentController().service(req, res);
    });
    this->server->Get("/local/node", [](const httplib::Request &req, httplib::Response &res) {
        RegisterNodeController().service(req, res);
    });
    this->server->Get("/local/save", [](const httplib::Request &req, httplib::Response &res) {
        SaveController().service(req, res);
    });
    this->server->Get("/local/load", [](const httplib::Request &req, httplib::Response &res) {
        LoadController().service(req, res);
    });

}

LocalRouter::LocalRouter(httplib::Server *server) : Router(server) {}

#include "Router.h"
#include "controller/block/BlockRouter.h"
Router::Router(httplib::Server *server) {
    this->server = server;
}

void Router::routeRegister() {
    Router* blockRouter = new BlockRouter(this->server);
    blockRouter->routeRegister();
}
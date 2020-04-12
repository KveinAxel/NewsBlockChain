#include "Router.h"
#include <controller/local/LocalRouter.h>
#include <controller/network/NetworkRouter.h>
Router::Router(httplib::Server *server) {
    this->server = server;
}

void Router::routeRegister() {
    Router* localRouter = new LocalRouter(this->server);
    Router* networkRouter = new NetworkRouter(this->server);
    localRouter->routeRegister();
    networkRouter->routeRegister();
}
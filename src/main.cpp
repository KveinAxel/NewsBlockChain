#include <winsock2.h>
#include <iostream>
#include <httplib.h>
#include "util/Logger.h"
#include "Global.h"
#include "Router.h"

int main(int argc, char *argv[]) {
    auto global = Global::getGlobal();
    std::cout << "请输入本机IP" << std::endl;
    std::cin >> global->localURL;
    std::cout << "请输入本机端�?" << std::endl;
    std::cin >> global->localPort;

    httplib::Server* svr = new httplib::Server;
    Router* router = new Router(svr);
    router->routeRegister();
    svr->listen("localhost", 8001);
    return 0;
}

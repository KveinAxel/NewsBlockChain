#include <winsock2.h>
#include <iostream>
#include <httplib.h>
#include "util/Logger.h"
#include "Global.h"
#include "Router.h"

int main(int argc, char *argv[]) {
    auto global = Global::getGlobal();
    std::cout << "请输入本机端口" << std::endl;
    std::cin >> global->localPort;
    global->localURL = "127.0.0.1";
    httplib::Server* svr = new httplib::Server;
    Router* router = new Router(svr);
    router->routeRegister();
    svr->listen("127.0.0.1", global->localPort);
    return 0;
}

#include <iostream>
#include "util/Logger.h"
#include "Global.h"

int main(int argc, char *argv[]) {
    auto global = Global::getGlobal();
    std::cout << "请输入本机IP" << std::endl;
    std::cin >> global->localURL;
    std::cout << "请输入本机端口" << std::endl;
    std::cin >> global->localPort;
    std::cout << "news block chain" << std::endl;
    return 0;
}

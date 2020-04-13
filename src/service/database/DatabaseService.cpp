#include <Global.h>
#include "DatabaseService.h"
#include <fstream>

Message<std::string> DatabaseService::save() {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        return Message<std::string>::fail(400, "无本地区块链");
    } else {
        std::ofstream out("blockchain.dat");
        out << global->blockChain->serialize();
        out.close();
        return Message<std::string>::success("存储至硬盘成功");
    }
}

Message<std::string> DatabaseService::load() {
    auto global = Global::getGlobal();
    std::ifstream in("blockchain.dat");
    if(in.is_open()) {
        std::string str;
        getline(in, str);
        if (global->blockChain == nullptr) {
            global->blockChain = BlockChain::deserialize(str);
            return Message<std::string>::success("加载成功");
        } else {
            auto chain = BlockChain::deserialize(str);
            if (chain->blockChainHash.size() > global->blockChain->blockChainHash.size()) {
                delete global->blockChain;
                global->blockChain = chain;
                return Message<std::string>::success("加载成功");
            } else {
                delete chain;
                return Message<std::string>::success("本地文件过于陈旧");
            }
        }
    } else {
        return Message<std::string>::fail(400, "存储文件不存在");
    }
}

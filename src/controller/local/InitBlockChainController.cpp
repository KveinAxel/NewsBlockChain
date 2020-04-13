#include <Global.h>
#include "InitBlockChainController.h"

InitBlockChainController::InitBlockChainController() = default;


void InitBlockChainController::service(const httplib::Request &req, httplib::Response &res) {
    auto global = Global::getGlobal();
    global->blockChain = new BlockChain();
    global->blockChain->lastHash = "初始化hash初始化hash初始化hash初始化hash初始化hash初始化hash初始化hash";
    std::vector<std::string> article({"创世区块", "创世区块", "创世区块", "创世区块", "创世区块", "创世区块"});
    global->blockChain->appendBlock(article);
    rapidjson::Value resValue;
    resValue.SetObject();
    rapidjson::Document document;
    resValue.AddMember("message", "初始化成功", document.GetAllocator());
    result(res, resValue);
}

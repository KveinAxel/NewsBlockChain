#include <Global.h>
#include <util/BullShitArticleGenerator.h>
#include "InitBlockChainController.h"

InitBlockChainController::InitBlockChainController() = default;


void InitBlockChainController::service(const httplib::Request &req, httplib::Response &res) {
    auto global = Global::getGlobal();
    global->blockChain = new BlockChain();
    global->blockChain->lastHash = "0047ac81c5b0deaa5151482df2c03717baa17b4fe4e1d726392bc2fe9fc34e41";
    std::vector<std::string> article;
    std::vector<unsigned> seeds;
    srand(time(NULL));
    for (int i = 1; i <= 200; i++) {
        article.clear();
        std::string clob;
        while(clob.size() < 2200)
            clob += BullShitArticleGenerator::generator(rand());

        std::stringstream ss(clob);
        std::string para;
        while(std::getline(ss, para))
            article.push_back(para);

        global->blockChain->appendBlock(article);
    }
    rapidjson::Value resValue;
    resValue.SetObject();
    rapidjson::Document document;
    resValue.AddMember("message", "初始化成功", document.GetAllocator());
    result(res, resValue);
}

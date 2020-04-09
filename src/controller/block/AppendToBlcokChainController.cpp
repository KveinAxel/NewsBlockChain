#include "AppendToBlcokChainController.h"
#include <service/blockchain/BlockChainService.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
AppendToBlockChain::AppendToBlockChain() = default;

void AppendToBlockChain::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("article")) {
        std::string article = req.get_param_value("article");
        auto msg = BlockChainService::addToBlockChain(article);
        rapidjson::Value resValue;
        resValue.SetObject();
        rapidjson::Document document;
        if (msg.code == 200) {
            resValue.AddMember("message", "添加成功", document.GetAllocator());
            result(res, resValue);
        } else {
            error(res, "400", msg.msg);
        }
    }
}

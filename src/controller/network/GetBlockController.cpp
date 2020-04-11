#include <service/blockchain/BlockChainService.h>
#include "GetBlockController.h"

GetBlockController::GetBlockController() = default;

void GetBlockController::service(const httplib::Request &req, httplib::Response &res) {
    auto serviceRes = BlockChainService::getBlockChain();
    if (serviceRes.code == 200) {
        auto block = serviceRes.data;
        rapidjson::Value resValue;
        rapidjson::Value value;
        rapidjson::Document document;
        value.SetString(block->c_str(), document.GetAllocator());
        resValue.SetObject();
        resValue.AddMember("message", "获取区块信息成功", document.GetAllocator());
        resValue.AddMember("data", value, document.GetAllocator());
        result(res, resValue);
    } else {
        error(res, "400", "获取区块信息失败");
    }
}

#include <service/blockchain/BlockChainService.h>
#include "GetBlockController.h"

GetBlockController::GetBlockController() = default;

void GetBlockController::service(const httplib::Request &req, httplib::Response &res) {
    auto serviceRes = BlockChainService::getBlockChain();
    if (serviceRes.code == 200) {
        rapidjson::Value resValue(rapidjson::kObjectType);
        rapidjson::Value dataJson(rapidjson::kObjectType);
        rapidjson::Document document;

        rapidjson::Value value(serviceRes.data->first.c_str(), document.GetAllocator());

        dataJson.AddMember("block", value, document.GetAllocator());
        dataJson.AddMember("nth", serviceRes.data->second, document.GetAllocator());

        resValue.AddMember("message", "获取区块信息成功", document.GetAllocator());
        resValue.AddMember("data", dataJson, document.GetAllocator());
        delete serviceRes.data;
        result(res, resValue);
    } else {
        error(res, "400", "获取区块信息失败");
    }
}

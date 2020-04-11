#include <service/blockchain/BlockChainService.h>
#include "ListHashController.h"

ListHashController::ListHashController()
= default;

void ListHashController::service(const httplib::Request &req, httplib::Response &res) {
    auto msg = BlockChainService::list();
    rapidjson::Value resValue;
    resValue.SetObject();
    rapidjson::Document document;
    if (msg.code == 200) {
        auto vec = msg.data;
        rapidjson::Value arr(rapidjson::kArrayType);
        if (vec != nullptr) {
            for (auto i: *vec) {
                rapidjson::Value item;
                item.SetObject();
                rapidjson::Value byte;
                byte.SetString(i.first.c_str(), document.GetAllocator());
                item.AddMember("byte", byte, document.GetAllocator());
                item.AddMember("time", i.second, document.GetAllocator());
                arr.PushBack(item, document.GetAllocator());
            }
        }
        resValue.AddMember("message", "列表获取成功", document.GetAllocator());
        resValue.AddMember("data", arr, document.GetAllocator());
        result(res, resValue);
    } else {
        error(res, "400", msg.msg);
    }
}


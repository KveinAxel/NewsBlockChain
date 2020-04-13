#include <service/blockchain/BlockChainService.h>
#include "GetBlockPartlyController.h"

void GetBlockPartlyController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("key")) {
        auto serviceRes = BlockChainService::getBlockList(req.get_param_value("key"));
        if (serviceRes.code == 200) {
            rapidjson::Value resValue(rapidjson::kObjectType);
            rapidjson::Value dataJson(rapidjson::kObjectType);
            rapidjson::Document document;
            if (serviceRes.data != nullptr) {
                rapidjson::Value hashJson(serviceRes.data->first.c_str() , document.GetAllocator());
                rapidjson::Value times(serviceRes.data->second);
                dataJson.AddMember("block", hashJson, document.GetAllocator());
                dataJson.AddMember("nth", times, document.GetAllocator());

                rapidjson::Value value(serviceRes.msg.c_str(), document.GetAllocator());

                resValue.AddMember("message", value, document.GetAllocator());
                resValue.AddMember("data", dataJson, document.GetAllocator());

                delete serviceRes.data;
                result(res, resValue);
            } else {
                error(res, "400", "无区块可取");
            }

        } else
            error(res, "400", "请求参数异常");
    } else {
        error(res, "400", "请求参数异常");
    }
}

GetBlockPartlyController::GetBlockPartlyController() = default;
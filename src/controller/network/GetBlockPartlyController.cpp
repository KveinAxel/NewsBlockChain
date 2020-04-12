#include <service/blockchain/BlockChainService.h>
#include "GetBlockPartlyController.h"

void GetBlockPartlyController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("key")) {
        auto serviceRes = BlockChainService::getBlockList(req.get_param_value("key"));
        if (serviceRes.code == 200) {
            rapidjson::Value resValue;
            resValue.SetObject();
            rapidjson::Document document;
            rapidjson::Value arr(rapidjson::kArrayType);
            if (serviceRes.data != nullptr) {
                for (auto i: serviceRes.data->first) {
                    rapidjson::Value value;
                    value.SetString(i.c_str(), document.GetAllocator());
                    arr.PushBack(value, document.GetAllocator());
                }
            }
            resValue.AddMember("data", arr, document.GetAllocator());
            result(res, resValue);
        } else
            error(res, "400", "请求参数异常");
    } else {
        error(res, "400", "请求参数异常");
    }
}

GetBlockPartlyController::GetBlockPartlyController() = default;
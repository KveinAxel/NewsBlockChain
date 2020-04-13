#include <service/blockchain/BlockChainService.h>
#include "ContentController.h"

ContentController::ContentController() = default;

void ContentController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("hash")) {
        std::string hash = req.get_param_value("hash");
        auto serviceRes = BlockChainService::getContent(hash);
        if (serviceRes.code == 200) {
            rapidjson::Value resValue(rapidjson::kObjectType);
            rapidjson::Value arr(rapidjson::kArrayType);
            rapidjson::Document document;
            for (auto& para: *(serviceRes.data)) {
                rapidjson::Value value(para.c_str(), document.GetAllocator());
                arr.PushBack(value, document.GetAllocator());
            }
            delete serviceRes.data;
            resValue.AddMember("message", "文章内容获取成功", document.GetAllocator());
            resValue.AddMember("data", arr, document.GetAllocator());
            result(res, resValue);
        } else {
            error(res, "400", serviceRes.msg);
        }
    }
}

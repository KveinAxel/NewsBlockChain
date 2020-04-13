#include <service/blockchain/BlockChainService.h>
#include "ConfirmController.h"

ConfirmController::ConfirmController()
= default;

void ConfirmController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("article")) {
        std::string articleJson = req.get_param_value("article");
        rapidjson::Document document;
        document.Parse(articleJson.c_str());
        std::vector<std::string> article;
        for (auto &itr: document.GetArray()) {
            article.push_back(itr.GetString());
        }
        if (req.has_param("hash")) {
            std::string hash = req.get_param_value("hash");
            auto msg = BlockChainService::confirmArticle(article, hash);
            rapidjson::Value resValue;
            resValue.SetObject();

            if (msg.code == 200) {
                resValue.AddMember("message", "无篡改", document.GetAllocator());
                result(res, resValue);
            } else if (msg.code == 400) {
                rapidjson::Value arr(rapidjson::kArrayType);
                for (auto &itr: *(msg.data)) {
                    rapidjson::Value arrValue(itr);
                    arr.PushBack(arrValue, document.GetAllocator());
                }
                delete msg.data;
                resValue.AddMember("message", "有篡改", document.GetAllocator());
                resValue.AddMember("data", arr, document.GetAllocator());
                result(res, resValue);
            }
            else {
                error(res, "400", msg.msg);
            }
        } else {
            error(res, "400", "请求参数异常");
        }
    } else {
        error(res, "400", "请求参数异常");
    }
}


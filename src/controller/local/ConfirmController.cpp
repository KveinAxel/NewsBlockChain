#include <service/blockchain/BlockChainService.h>
#include "ConfirmController.h"

ConfirmController::ConfirmController()
= default;

void ConfirmController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("article")) {
        std::string article = req.get_param_value("article");
        if (req.has_param("hash")) {
            std::string hash = req.get_param_value("hash");
            auto msg = BlockChainService::confirmArticle(article, hash);
            rapidjson::Value resValue;
            resValue.SetObject();
            rapidjson::Document document;
            if (msg.code == 200) {
                resValue.AddMember("message", "添加成功", document.GetAllocator());
                result(res, resValue);
            } else {
                error(res, "400", msg.msg);
            }
        } else {
            error(res, "400", "请求参数异常");
        }
    } else {
        error(res, "400", "请求参数异常");
    }
}


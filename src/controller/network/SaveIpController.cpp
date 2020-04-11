#include <Global.h>
#include "SaveIpController.h"

void SaveIpController::service(const httplib::Request &req, httplib::Response &res) {
    auto global = Global::getGlobal();
    if (global->isSuperNode) {
        if (req.has_param("url")) {
            if (req.has_param("port")) {
                auto url = req.get_param_value("url");
                auto port = atoi(req.get_param_value("port").c_str());
                global->ip_tables[url] = port;
                rapidjson::Value resValue;
                resValue.SetObject();
                rapidjson::Document document;
                resValue.AddMember("message", "保存IP成功", document.GetAllocator());
                result(res, resValue);
            } else {
                error(res, "400", "请求参数异常");
            }
        } else {
            error(res, "400", "请求参数异常");
        }
    } else {
        error(res, "400", "异常请求");
    }
}

SaveIpController::SaveIpController() = default;
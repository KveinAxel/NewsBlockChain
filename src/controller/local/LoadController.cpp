#include <service/database/DatabaseService.h>
#include "LoadController.h"

LoadController::LoadController() = default;

void LoadController::service(const httplib::Request &req, httplib::Response &res) {
    auto serviceRes = DatabaseService::load();
    rapidjson::Document document;
    rapidjson::Value resValue;
    resValue.SetObject();
    if (serviceRes.code == 200) {
        rapidjson::Value value(serviceRes.msg.c_str(), document.GetAllocator());
        resValue.AddMember("message", value, document.GetAllocator());
        result(res, resValue);
    } else {
        error(res, "400", serviceRes.msg);
    }
}

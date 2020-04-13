#include <service/connection/Connection.h>
#include "UpdateController.h"

void UpdateController::service(const httplib::Request &req, httplib::Response &res) {
    auto serviceRes = Connection::getBlockChainPartly();
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

UpdateController::UpdateController() = default;

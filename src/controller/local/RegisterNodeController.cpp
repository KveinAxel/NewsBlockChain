#include <service/connection/Connection.h>
#include "RegisterNodeController.h"

RegisterNodeController::RegisterNodeController() = default;

void RegisterNodeController::service(const httplib::Request &req, httplib::Response &res) {
    auto serviceRes = Connection::node();
    rapidjson::Value resValue;
    rapidjson::Document document;
    resValue.SetObject();
    if (serviceRes.code == 200) {
        resValue.AddMember("message", "加入区块链网络成功", document.GetAllocator());
        result(res, resValue);
    } else {
        error(res, "400", serviceRes.msg);
    }
}

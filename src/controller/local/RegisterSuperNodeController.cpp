#include "RegisterSuperNodeController.h"
#include <service/connection/Connection.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

RegisterSuperNodeController::RegisterSuperNodeController() = default;

void RegisterSuperNodeController::service(const httplib::Request &req, httplib::Response &res) {
    auto serviceRes = Connection::superNone();
    rapidjson::Value resValue;
    resValue.SetObject();
    rapidjson::Document document;
    if (serviceRes.code == 200) {
        resValue.AddMember("message", "添加成功", document.GetAllocator());
        result(res, resValue);
    } else {
        error(res, "400", serviceRes.msg);
    }
}

#include <Global.h>
#include "DeleteNodeController.h"

DeleteNodeController::DeleteNodeController() = default;

void DeleteNodeController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("url")) {
        auto url = req.get_param_value("url");
        if (req.has_param("port")) {
            auto port = atoi(req.get_param_value("port").c_str());
            auto global = Global::getGlobal();
            for (auto itr = global->ip_tables.begin(); itr != global->ip_tables.end();itr++) {
                if (itr->first == url && itr->second == port) {
                    global->ip_tables.erase(itr);
                    rapidjson::Value resValue;
                    resValue.SetObject();
                    rapidjson::Document document;
                    resValue.AddMember("message", "删除节点成功", document.GetAllocator());
                    result(res, resValue);
                    return;
                }
            }
        }
    }
    error(res, "400", "删除失败");
}

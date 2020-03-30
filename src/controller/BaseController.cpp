#include "BaseController.h"
#include <ctime>

BaseController::BaseController() = default;

void BaseController::result(httplib::Response &res, const std::string &status, const rapidjson::Value &value) {
    rapidjson::Document document;
    auto& allocator = document.GetAllocator();
    rapidjson::Value resObj(value, allocator);

    resObj.AddMember("ts", time(nullptr), allocator);
    resObj.AddMember("status", status, allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resObj.Accept(writer);

    // 构建返回
    res.set_content(buffer.GetString(), "application/json");
}

void BaseController::result(httplib::Response &res, const rapidjson::Value &value) {
    result(res, "OK", value);
}

void BaseController::error(httplib::Response &res, const std::string &code, const std::string &info) {
    rapidjson::Document document;
    rapidjson::Value resObj;
    resObj.SetObject();
    resObj.AddMember("code", code, document.GetAllocator());
    resObj.AddMember("info", info, document.GetAllocator());
    result(res, "ERR", resObj);
}

void BaseController::service(const httplib::Request &req, httplib::Response &res) {}

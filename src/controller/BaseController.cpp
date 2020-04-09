#include "BaseController.h"
#include <ctime>
#include <utility>

BaseController::BaseController() = default;

void BaseController::result(httplib::Response &res, const std::string& status, const rapidjson::Value &value) {
    rapidjson::Document document;
    rapidjson::Value resObj(value, document.GetAllocator());
    rapidjson::Value val;

    resObj.AddMember("ts", time(nullptr), document.GetAllocator());
    resObj.AddMember("status", val.SetString(status.c_str(), document.GetAllocator()), document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resObj.Accept(writer);

    // 构建返回
    res.set_content(buffer.GetString(), "application/json");
}

void BaseController::result(httplib::Response &res, const rapidjson::Value &value) {
    result(res, "200", value);
}

void BaseController::error(httplib::Response &res, const std::string &code, const std::string &info) {
    rapidjson::Document document;
    rapidjson::Value resObj;
    rapidjson::Value codeVal;
    rapidjson::Value infoVal;

    resObj.SetObject();
    resObj.AddMember("code", codeVal.SetString(code.c_str(), document.GetAllocator()), document.GetAllocator());
    resObj.AddMember("info", infoVal.SetString(info.c_str(), document.GetAllocator()), document.GetAllocator());
    result(res, "ERR", resObj);
}


#include "Connection.h"
#include <httplib.h>
#include <rapidjson/document.h>
Message<std::string> Connection::getServerURL() {
    // todo substitute the serverUrl and serverPort with the hard encode server url and port
    std::string serverUrl;
    int serverPort = 0;
    httplib::Client cli(serverUrl, serverPort);
    // todo
    auto res = cli.Get("/");
    if (res && res->status == 200) {
        auto json = res->body;
        rapidjson::Document document;
        document.Parse(json.c_str());
        if (document.IsObject()) {
            auto value = document.FindMember("data");
            std::string url = value->value.GetString();
            return Message<std::string>::success("获取URL成功", &url);
        }
    }
    return Message<std::string>::fail(400, "获取URL失败");
}

Message<std::string> Connection::getBlockChainData(std::string url) {
    auto pos = url.find(':');
    auto uri = url.substr(0, pos);
    auto port = url.substr(pos + 1);
    httplib::Client cli(uri, atoi(port.c_str()));
    // todo 改成获取区块链
    auto res = cli.Get("/block/list");
    if (res && res->status == 200) {
        auto json = res->body;
        rapidjson::Document document;
        document.Parse(json.c_str());
        if (document.IsObject()) {
            auto value = document.FindMember("data");
            std::string data = value->value.GetString();
            // todo 改成返回区块链
            return Message<std::string>::success("获取data成功", &data);
        }
    }
    return Message<std::string>::fail(400, "获取区块信息失败");
}

#include "Connection.h"
#include <httplib.h>
#include <rapidjson/document.h>
#include <Global.h>

Message<std::string> Connection::node() {
    auto global = Global::getGlobal();
    httplib::Client cli(Global::serverURL, Global::serverPort);
    auto requirePath = "/node?url=" + global->localURL + "&port=" + std::to_string(global->localPort);
    auto res = cli.Get(requirePath.c_str());
    if (res && res->status == 200) {
        auto json = res->body;
        rapidjson::Document document;
        document.Parse(json.c_str());
        if (document.IsObject()) {
            auto value = document.FindMember("data");
            if (value->value.IsObject()) {
                std::string url = value->value.FindMember("url")->value.GetString();
                int port = value->value.FindMember("port")->value.GetInt();
                global->ip_tables[url] = port;
                return Message<std::string>::success("加入区块网络成功");
            }
        }
    }
    return Message<std::string>::fail(400, "加入区块网络失败");
}

Message<std::string> Connection::superNone() {
    auto global = Global::getGlobal();
    httplib::Client cli(Global::serverURL, Global::serverPort);
    auto requirePath = "/superNode?url=" + global->localURL + "&port=" + std::to_string(global->localPort);
    auto res = cli.Get(requirePath.c_str());
    if (res && res->status == 200) {
        global->isSuperNode = true;
        global->ip_tables.clear();
        return Message<std::string>::success("注册超级节点成功");
    }
    return Message<std::string>::fail(400, "注册超级节点失败");
}


Message<std::string> Connection::getBlockChainData(std::string url) {
    auto pos = url.find(':');
    auto uri = url.substr(0, pos);
    auto port = url.substr(pos + 1);
    httplib::Client cli(uri, atoi(port.c_str()));
    // todo 改成获取区块链
    auto res = cli.Get("/local/list");
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

Message<std::string> Connection::broadcastBlockToNode(std::string block, std::string url, int port) {
    // todo
    return Message<std::string>::success(block);
}

Message<std::string> Connection::broadcastBlockToDNS(std::string block) {
    // todo 广播至DNS
    return Message<std::string>::success(block);
}

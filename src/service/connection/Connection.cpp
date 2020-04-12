#include "Connection.h"
#include <httplib.h>
#include <rapidjson/document.h>
#include <Global.h>
#include <service/blockchain/BlockChainService.h>

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


Message<std::string> Connection::getBlockChainData(std::string url, int port) {
    httplib::Client cli(url, port);
    auto res = cli.Get("/network/getBlock");
    if (res && res->status == 200) {
        auto json = res->body;
        rapidjson::Document document;
        document.Parse(json.c_str());
        if (document.IsObject()) {
            auto value = document.FindMember("data");
            std::string data = value->value.GetString();
            auto serviceRes = BlockChainService::deserializeBlockChain(data);
            if (serviceRes.code == 200) {
                return Message<std::string>::success("反序列化区块链成功");
            } else {
                return Message<std::string>::fail(400,"获取区块链失败");
            }
        }
    }
    return Message<std::string>::fail(400, "获取区块链失败");
}

Message<std::string> Connection::broadcastBlockToNode(std::string block, std::string url, int port) {
    auto global = Global::getGlobal();
    auto cli = httplib::Client(url, port);
    auto queryPath = "/broadcastBlockBySuperNode?block=" + block;
    auto res = cli.Get(queryPath.c_str());
    if (res && res->status == 200) {
        return Message<std::string>::success("广播至普通节点成功");
    } else {
        return Message<std::string>::fail(400, "广播至普通节点失败");
    }
    return Message<std::string>::success(block);
}

Message<std::string> Connection::broadcastBlockToDNS(std::string block) {
    auto global = Global::getGlobal();
    auto cli = httplib::Client(Global::serverURL, Global::serverPort);
    auto queryPath = "/broadcast?block=" + block;
    auto res = cli.Get(queryPath.c_str());
    if (res && res->status == 200) {
        return Message<std::string>::success("广播至DNS成功");
    } else {
        return Message<std::string>::fail(400, "广播至DNS失败");
    }
}

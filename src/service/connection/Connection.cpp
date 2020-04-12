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

Message<std::string> Connection::broadcastBlockToNode(std::string block, std::string url, int port) {
    auto global = Global::getGlobal();
    auto cli = httplib::Client(url, port);
    auto queryPath = "/network/broadcastBlockBySuperNode?block=" + block;
    auto res = cli.Get(queryPath.c_str());
    if (res && res->status == 200) {
        return Message<std::string>::success("广播至普通节点成功");
    } else {
        return Message<std::string>::fail(400, "广播至普通节点失败");
    }
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

Message<std::string> Connection::getBlockChain() {
    auto global = Global::getGlobal();
    std::string url;
    int port = 0;
    auto queryPath = "/network/getBlock";
    if (global->isSuperNode) {
        queryPath = "/getBlockChain";
        url = Global::serverURL;
        port = Global::serverPort;
    } else {
        if (global->ip_tables.size() == 0) {
            return Message<std::string>::fail(400, "尚未加入区块网络");
        } else {
            url = global->ip_tables.begin()->first;
            port = global->ip_tables.begin()->second;
        }
    }
    auto cli = httplib::Client(url, port);
    auto res = cli.Get(queryPath);
    if (res && res->status == 200) {
        auto json = res->body;
        rapidjson::Document document;
        document.Parse(json.c_str());
        if (document.IsObject()) {
            auto data = document.FindMember("data")->value.GetString();
            global->blockChain = BlockChain::deserialize(data);
            return Message<std::string>::success("获取区块成功");
        }
        return Message<std::string>::fail(400, "获取区块失败");
    } else {
        return Message<std::string>::fail(400, "获取区块失败");
    }
}

Message<std::string> Connection::getBlockChainPartly() {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        return getBlockChain();
    } else {
        auto key = global->blockChain->lastHash;
        std::string url;
        int port = 0;
        auto queryPath = "/network/getBlockPartly?key=" + key;
        if (global->isSuperNode) {
            queryPath = "/getBlockChainPartly?key=" + key;
            url = Global::serverURL;
            port = Global::serverPort;
        } else {
            if (global->ip_tables.size() == 0) {
                return Message<std::string>::fail(400, "尚未加入区块网络");
            } else {
                url = global->ip_tables.begin()->first;
                port = global->ip_tables.begin()->second;
            }
        }
        auto cli = httplib::Client(url, port);
        auto res = cli.Get(queryPath.c_str());
        if (res && res->status == 200) {
            auto json = res->body;
            rapidjson::Document document;
            document.Parse(json.c_str());
            if (document.IsObject()) {
                auto arr = document.FindMember("data")->value.GetArray();
                std::vector<std::string> vec;
                for (auto &itr: arr) {
                    global->blockChain->updateBlock(itr.GetString());
                }
                return Message<std::string>::success("增量获取区块成功");
            }
        }
    }
    return Message<std::string>::fail(400, "增量获取区块失败");
}

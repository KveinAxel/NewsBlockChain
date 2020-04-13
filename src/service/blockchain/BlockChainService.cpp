#include <Global.h>
#include <service/connection/Connection.h>
#include <util/StringUtil.h>
#include "BlockChainService.h"

Message<std::string> BlockChainService::addToBlockChain(std::vector<std::string> article) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            return Message<std::string>::fail(400, "本地无法加载区块链");
        }
    }
    auto currentHash = global->blockChain->appendBlock(article);
    std::string *res = new std::string(currentHash);
    if (global->isSuperNode) {
        Connection::broadcastBlockToDNS(global->blockChain->blockChainHash[global->blockChain->lastHash]->serialize());
    } else {
        if (global->ip_tables.size() != 0)
            Connection::broadcastBlockToSuperNode(global->blockChain->blockChainHash[global->blockChain->lastHash]->serialize(),
                global->ip_tables.begin()->first, global->ip_tables.begin()->second);
    }
    return Message<std::string>::success( "加入区块链成功，并获得该区块头的哈希", res);
}

Message<std::vector<int>> BlockChainService::confirmArticle(std::vector<std::string> article, std::string hash) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            return Message<std::vector<int>>::fail(400, "本地无法加载区块链");
        }
    }
    return global->blockChain->modifyCheckLocal(article, hash);
}

Message<std::vector<std::pair<std::string, time_t>>> BlockChainService::list() {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            return Message<std::vector<std::pair<std::string, time_t>>>::fail(400, "本地无法加载区块链");
        }
    }
    auto res = new std::vector<std::pair<std::string, time_t>>;
    for (auto &itr: global->blockChain->blockChainHash) {
        res->push_back(std::make_pair(itr.first, itr.second->createdTime));
    }
    return Message<std::vector<std::pair<std::string, time_t>>>::success("获取区块信息成功", res);
}

Message<std::string> BlockChainService::broadcast(std::string block) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            return Message<std::string>::fail(400, "本地无法加载区块链");
        }
    }
    auto ok = global->blockChain->updateBlock(block);
    if (ok) {
        return Message<std::string>::success( "广播成功");
    } else {
        return Message<std::string>::fail( 400, "广播失败，无法加入区块链");
    }
}

Message<std::pair<std::string, int>> BlockChainService::getBlockChain() {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200)
            return Message<std::pair<std::string, int>>::fail(400, "本地无法加载区块链");
    }
    auto *res = new std::pair<std::string, int>(global->blockChain->serialize(), global->blockChain->blockChainHash.size());
    return Message<std::pair<std::string, int>>::success("请求获取区块链成功", res);
}

Message<std::vector<std::string>> BlockChainService::getBlockHeadHashList() {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            Message<std::vector<std::string>>::fail(400, "本地无法加载区块链");
        }
    }
    auto *res = new std::vector<std::string>(global->blockChain->blockChainHeadList);
    return Message<std::vector<std::string>>::success("获取区块头列表成功", res);
}

Message<std::pair<std::string, int>> BlockChainService::getBlockList(std::string key) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            Message<std::pair<std::vector<std::string>, int>>::fail(400, "本地无法加载区块链");
        }
    }
    return global->blockChain->responseBlockList(key);
}

Message<std::vector<std::string>> BlockChainService::getContent(std::string hash) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            Message<std::vector<std::string>>::fail(400, "本地无法加载区块链");
        }
    }
    auto itr = global->blockChain->blockChainHash.find(hash);
    if (itr != global->blockChain->blockChainHash.end()) {
        auto art = itr->second->getArticle();
        std::vector<std::string> *newVec = new std::vector<std::string>(*art);
        delete art;
        return Message<std::vector<std::string>>::success("获取成功", newVec);
    } else {
        return Message<std::vector<std::string>>::fail(400, "区块不存在");
    }
}

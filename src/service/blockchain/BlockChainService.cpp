#include <Global.h>
#include <service/connection/Connection.h>
#include <util/StringUtil.h>
#include "BlockChainService.h"

Message<std::string> BlockChainService::addToBlockChain(std::string article) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            return Message<std::string>::fail(400, "本地无法加载区块链");
        }
    }
    auto articleVec = stringSplit(article, "\n");
    auto currentHash = global->blockChain->appendBlock(articleVec);
    std::string *res = new std::string(currentHash);
    return Message<std::string>::success( "加入区块链成功，并获得该区块头的哈希", res);
}

Message<std::vector<int>> BlockChainService::confirmArticle(std::string article, std::string hash) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            return Message<std::vector<int>>::fail(400, "本地无法加载区块链");
        }
    }
    auto articleVec = stringSplit(article, "\n");
    return global->blockChain->modifyCheckLocal(articleVec, hash);
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

Message<std::pair<std::vector<std::string>, int>> BlockChainService::getBlockList(std::string key) {
    auto global = Global::getGlobal();
    if (global->blockChain == nullptr) {
        auto res = Connection::getBlockChain();
        if (res.code != 200) {
            Message<std::pair<std::vector<std::string>, int>>::fail(400, "本地无法加载区块链");
        }
    }
    return global->blockChain->responseBlockList(key);
}

#include "BlockChain.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
Message<std::pair<std::string, int>> BlockChain::responseBlockList(std::string key) {
    bool ok = false;
    std::vector<std::string> vec;
    for (auto& itr: this->blockChainHeadList) {
        if (ok) {
            vec.push_back(this->blockChainHash[itr]->serialize());
        }
        if (itr == key)
            ok = true;
    }
    rapidjson::Document document;
    rapidjson::Value arr(rapidjson::kObjectType);
    rapidjson::Value resJson(rapidjson::kObjectType);
    rapidjson::Value lastHashJson(this->lastHash.c_str(), document.GetAllocator());
    for (auto itr: vec) {
        rapidjson::Value value(itr.c_str(), document.GetAllocator());
        arr.PushBack(value, document.GetAllocator());
    }
    resJson.AddMember("list", arr, document.GetAllocator());
    resJson.AddMember("lastHash", lastHashJson, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resJson.Accept(writer);
    auto res = new std::pair<std::string, int>(buffer.GetString(), this->blockChainHash.size());
    return Message<std::pair<std::string, int>>::success("查询成功", res);

}

bool BlockChain::updateBlock(std::string block) {
    BlockObj *newBlock = BlockObj::deserialize(block);
    if (BlockChain::lastHash.length() == 0 || newBlock->previousHash == this->lastHash) {
        this->lastHash = newBlock->currentHash;
        this->blockChainHash[newBlock->currentHash] = newBlock;
        this->blockChainHeadList.push_back(newBlock->currentHash);
        return true;
    } else
        return false;
}

std::string BlockChain::appendBlock(const std::vector<std::string> &article) {
    BlockObj *blockObj = new BlockObj(article, this->lastHash);
    this->blockChainHash[blockObj->currentHash] = blockObj;
    this->lastHash = blockObj->currentHash;
    this->blockChainHeadList.push_back(blockObj->currentHash);
    return blockObj->currentHash;
}

Message<std::vector<int>> BlockChain::modifyCheckLocal(const std::vector<std::string> &article, std::string &key) {
    auto itr = this->blockChainHash.find(key);
    if (itr == this->blockChainHash.end()) {
        return Message<std::vector<int>>::fail(500, "区块不存在");
    } else {
        return itr->second->modifyCheck(article);
    }
}

std::string BlockChain::serialize() {
    rapidjson::Document document;
    rapidjson::Value mapJson(rapidjson::kObjectType);
    rapidjson::Value resJson(rapidjson::kObjectType);
    rapidjson::Value lastHashJson(this->lastHash.c_str(), document.GetAllocator());
    for (auto itr: this->blockChainHash) {
        rapidjson::Value key;
        rapidjson::Value value;
        key.SetString(itr.first.c_str(), document.GetAllocator());
        value.SetString(itr.second->serialize().c_str(), document.GetAllocator());
        mapJson.AddMember(key, value, document.GetAllocator());
    }
    resJson.AddMember("map", mapJson, document.GetAllocator());
    resJson.AddMember("lastHash", lastHashJson, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resJson.Accept(writer);
    return buffer.GetString();
}

BlockChain *BlockChain::deserialize(std::string blockchain) {
    rapidjson::Document document;
    document.Parse(blockchain.c_str());
    BlockChain* resBlockChain = new BlockChain;
    auto mapJson = document.GetObject().FindMember("map")->value.GetObject();
    auto lastHash = document.GetObject().FindMember("lastHash")->value.GetString();
    for (auto &itr: mapJson) {
        resBlockChain->blockChainHash[itr.name.GetString()] = BlockObj::deserialize(itr.value.GetString());
        resBlockChain->blockChainHeadList.push_back(itr.name.GetString());
    }
    resBlockChain->lastHash = lastHash;
    return resBlockChain;
}

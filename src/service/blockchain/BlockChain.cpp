#include "BlockChain.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
Message<std::pair<std::vector<std::string>, int>> BlockChain::responseBlockList(std::string key) {
    bool ok = false;
    std::vector<std::string> vec;
    for (auto& itr: this->blockChainHeadList) {
        if (ok) {
            vec.push_back(this->blockChainHash[itr]->serialize());
        }
        if (itr == key)
            ok = true;
    }
    auto res = new std::pair<std::vector<std::string>, int>(vec, this->blockChainHash.size());
    return Message<std::pair<std::vector<std::string>, int>>::success("查询成功", res);
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
    BlockObj *blockObj = new BlockObj(article, BlockChain::lastHash);
    this->blockChainHash[blockObj->currentHash] = blockObj;
    this->blockChainHeadList.push_back(blockObj->currentHash);
    return blockObj->currentHash;
}

Message<std::vector<int>> BlockChain::modifyCheckLocal(const std::vector<std::string> &article, std::string &key) {
    auto itr = this->blockChainHash.find(key);
    if (itr == this->blockChainHash.end()) {
        return Message<std::vector<int>>::fail(400, "区块不存在");
    } else {
        return itr->second->modifyCheck(article);
    }
}

std::string BlockChain::serialize() {
    rapidjson::Document document;
    rapidjson::Value resJson(rapidjson::kObjectType);
    for (auto itr: this->blockChainHash) {
        rapidjson::Value key;
        rapidjson::Value value;
        key.SetString(itr.first.c_str(), document.GetAllocator());
        value.SetString(itr.second->serialize().c_str(), document.GetAllocator());
        resJson.AddMember(key, value, document.GetAllocator());
    }
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    resJson.Accept(writer);
    return buffer.GetString();
}

BlockChain *BlockChain::deserialize(std::string blockchain) {
    rapidjson::Document document;
    document.Parse(blockchain.c_str());
    BlockChain* resBlockChain = new BlockChain;
    for (auto &itr: document.GetObject()) {
        resBlockChain->blockChainHash[itr.name.GetString()] = BlockObj::deserialize(itr.value.GetString());
        resBlockChain->blockChainHeadList.push_back(itr.name.GetString());

    }
    return resBlockChain;
}

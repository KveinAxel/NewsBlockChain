#include "Block.h"

BlockObj::~BlockObj() {
    delete BlockObj::merkletree;
}

Message<std::vector<int>> BlockObj::modifyCheck(const std::vector<std::string> art) {
    if (article.size() != this->article.size()) {
        return Message<std::vector<int>>::fail(500, "文章分段不匹配");
    }
    return merkletree->modifyCheck(art);
}

BlockObj::BlockObj(const std::vector<std::string> &article, std::string previousHash) {
    this->createdTime = time(nullptr);
    for (auto paragraph: article) {
        this->article.push_back(paragraph);
    }
    merkletree = new MerkleTree(article);
    this->merkleRootHash = merkletree->merkleRootHash();
    this->previousHash = previousHash;
    this->currentHash = this->blockHeadHash();
}

std::string BlockObj::blockHeadHash() {
    std::string headHash = previousHash;
    headHash.push_back(this->createdTime);
    headHash += this->merkleRootHash;
    Hash temp = Hash(headHash);
    return temp.toString();
}

std::string BlockObj::serialize() {
    rapidjson::Document document;
    rapidjson::Value jsonObject;
    jsonObject.SetObject();
    rapidjson::Value currentHashJson;

    currentHashJson.SetString(this->currentHash.c_str(),document.GetAllocator());
    rapidjson::Value previousHashJson;
    previousHashJson.SetString(this->previousHash.c_str(),document.GetAllocator());

    jsonObject.AddMember("currentHash", currentHashJson, document.GetAllocator());
    jsonObject.AddMember("previousHash", previousHashJson, document.GetAllocator());
    jsonObject.AddMember("createdTime", this->createdTime, document.GetAllocator());

    rapidjson::Value arr(rapidjson::kArrayType);
    for (auto &paragraph: this->article) {
        rapidjson::Value paraValue;
        paraValue.SetString(paragraph.c_str(), document.GetAllocator());
        arr.PushBack(paraValue, document.GetAllocator());
    }
    jsonObject.AddMember("article", arr, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);

    return buffer.GetString();
}

BlockObj *BlockObj::deserialize(std::string block) {
    rapidjson::Document document;
    document.Parse(block.c_str());
    std::string currentHash = document.FindMember("currentHash")->value.GetString();
    std::string previousHash = document.FindMember("previousHash")->value.GetString();
    std::time_t created_time = document.FindMember("created_time")->value.GetInt();
    auto arr = document.FindMember("article")->value.GetArray();
    std::vector<std::string> article;
    for (auto& v: arr) {
        article.push_back(v.GetString());
    }
    return new BlockObj(article, previousHash, currentHash, created_time);
}

BlockObj::BlockObj(const std::vector<std::string> &article, std::string previousHash, std::string currentHash,
                   size_t created_time): article(article), previousHash(previousHash), currentHash(currentHash){ }

int BlockObj::searchKeyword(const std::vector<std::string> &keywords_list) {
    // todo
    Searcher *searcherHandle = new SearcherImpl();
    searcherHandle->Enter_Keywords(keywords_list);
    std::string searchText;
    for (int i = 0; i < BlockObj::article.size(); i++) {
        searchText.append(article.at(i));
    }
    SearchResult &resultHandle = searcherHandle->Keyword_Search(searchText);//要改接口这里
    int temp = resultHandle.Get_Total();
    return temp;
}
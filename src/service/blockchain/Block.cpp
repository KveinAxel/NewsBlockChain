#include "Block.h"
#include <sstream>

BlockObj::~BlockObj() {
    delete BlockObj::merkletree;
}

Message<std::vector<int>> BlockObj::modifyCheck(const std::vector<std::string> art) {
    if (art.size() != this->article.size()) {
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
    std::string tot;
    std::stringstream ss;
    for (auto &i: this->article) {
        ss << i << "\n";
    }
    Compressor compressor(ss.str());
    compressor.compress();
    this->serializedDict = compressor.getSerializedDict();
    this->bytes = compressor.getBytes();
    this->filler = compressor.getFiller();
    this->article.clear();
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
    jsonObject.AddMember("created_time", this->createdTime, document.GetAllocator());

    rapidjson::Value arr(rapidjson::kArrayType);
    auto art = this->getArticle();
    for (auto &paragraph: *art) {
        rapidjson::Value paraValue;
        paraValue.SetString(paragraph.c_str(), document.GetAllocator());
        arr.PushBack(paraValue, document.GetAllocator());
    }
    jsonObject.AddMember("article", arr, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonObject.Accept(writer);
    delete art;
    return buffer.GetString();
}

BlockObj *BlockObj::deserialize(std::string block) {
    rapidjson::Document document;
    document.Parse(block.c_str());
    std::string currentHash = document.FindMember("currentHash")->value.GetString();
    std::string previousHash = document.FindMember("previousHash")->value.GetString();
    std::time_t created_time = document.FindMember("created_time")->value.GetUint();
    auto arr = document.FindMember("article")->value.GetArray();
    std::vector<std::string> article;
    for (auto& v: arr) {
        article.push_back(v.GetString());
    }
    return new BlockObj(article, previousHash, currentHash, created_time);
}

BlockObj::BlockObj(const std::vector<std::string> &article, std::string previousHash, std::string currentHash,
                   time_t created_time): article(article), previousHash(previousHash), currentHash(currentHash), createdTime(created_time){
    std::string tot;
    std::stringstream ss;
    for (auto &i: this->article) {
        ss << i;
    }
    Compressor compressor(ss.str());
    compressor.compress();
    this->serializedDict = compressor.getSerializedDict();
    this->bytes = compressor.getBytes();
    this->filler = compressor.getFiller();
    this->article.clear();
}

int BlockObj::searchKeyword(const std::vector<std::string> &keywords_list) {
    Searcher *searcherHandle = new SearcherImpl();
    searcherHandle->Enter_Keywords(keywords_list);
    std::string searchText;
    auto art = this->getArticle();
    for (int i = 0; i < art->size(); i++) {
        searchText.append(art->at(i));
    }
    SearchResult &resultHandle = searcherHandle->Keyword_Search(searchText);//要改接口这里
    int temp = resultHandle.Get_Total();
    return temp;
}

std::vector<std::string>* BlockObj::getArticle() {
    if (this->article.size() != 0) {
        return new std::vector<std::string>(this->article);
    } else {
        Compressor compressor(this->serializedDict, this->bytes, this->filler);
        compressor.decompress();
        std::stringstream ss(compressor.getData());
        std::string str;
        auto *art = new std::vector<std::string>;
        while (std::getline(ss, str)) {
            art->push_back(str);
        }
        return art;
    }
}

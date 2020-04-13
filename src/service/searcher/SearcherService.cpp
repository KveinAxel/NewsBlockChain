#include <Global.h>
#include "SearcherService.h"

Message<std::vector<std::string>> SearcherService::search(std::vector<std::string> keywords) {
    auto global = Global::getGlobal();
    std::map<int, BlockObj *> map;
    auto list = new std::vector<std::string>;
    auto itr = global->blockChain->blockChainHash.begin();
    while (itr != global->blockChain->blockChainHash.end()) {
        map[itr->second->searchKeyword(keywords)] = itr->second;
        itr++;
    }
    int step = 1;
    auto itr2 = map.crbegin();
    while (itr2 != map.crend() && step <= 3) {
        rapidjson::Document document;
        rapidjson::Value resObj(rapidjson::kObjectType);
        rapidjson::Value currentHash(itr2->second->currentHash.c_str(), document.GetAllocator());
        rapidjson::Value created_time(itr2->second->createdTime);

        resObj.AddMember("byte", currentHash, document.GetAllocator());
        resObj.AddMember("time", created_time, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        resObj.Accept(writer);
        list->push_back(buffer.GetString());
        step++;
        itr2++;
    }
    return Message<std::vector<std::string>>::success("查询成功", list);
}

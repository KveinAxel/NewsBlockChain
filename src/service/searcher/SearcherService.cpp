#include <Global.h>
#include "SearcherService.h"

# define MAX_SEARCH 2000

Message<std::vector<std::string>> SearcherService::search(std::vector<std::string> keywords) {
    auto global = Global::getGlobal();
    std::string temp = global->blockChain->lastHash;
    std::map<int, BlockObj *> map;
    auto list = new std::vector<std::string>;
    auto itr = global->blockChain->blockChainHash.find(temp);
    while (itr != global->blockChain->blockChainHash.end()) {
        map[MAX_SEARCH - itr->second->searchKeyword(keywords)] = itr->second;
        temp = itr->second->previousHash;
    }
    int step = 1;
    auto itr2 = map.cend();
    while (itr2 != map.cbegin() && step <= 2) {
        list->push_back(itr2->second->serialize());
        step++;
        itr2--;
    }
    return Message<std::vector<std::string>>::success("查询成功", list);
}

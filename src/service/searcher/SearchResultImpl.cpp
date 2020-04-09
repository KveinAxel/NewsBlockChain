#include "SearchResultImpl.h"

#include <utility>

void SearchResultImpl::push(const std::vector<std::string> &words) {
    keyword_list.assign(words.begin(), words.end());
}

void SearchResultImpl::insert(int sum, const std::vector<std::vector<int>> &location) {
    passage.sum = sum;
    if (!keyword_list.empty()) {
        int i = 0;
        auto it = keyword_list.begin();
        for (; it != keyword_list.end(); it++, i++) {
            passage.location.insert(std::map<std::string, std::vector<int>>::value_type(*it, location[i]));
        }
    }
}

int SearchResultImpl::Get_Total() {
    return passage.sum;
}

std::vector<std::string> SearchResultImpl::Get_Keyword_List() {
    return keyword_list;
}

int SearchResultImpl::Get_num(std::string keyword) {
    return passage.location[keyword].size();
}

std::vector<int> SearchResultImpl::Get_Location_list(std::string keyword) {
    std::vector<int> location_list;
    int num = keyword.size();
    auto lit = passage.location[keyword].begin();
    auto end = passage.location[keyword].end();
    for (; lit != end; lit++) {
        location_list.push_back((*lit) - num + 1);
    }
    return location_list;
}

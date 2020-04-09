#include "SearchResultImpl.h"

#include <utility>

void SearchResultImpl::push(std::vector<std::string> &words) {
    keyword_list.assign(words.begin(), words.end());
}

void SearchResultImpl::insert(std::string hash, int sum, const std::vector<std::vector<int>> &location) {
    news *np = new news;
    np->hash_code = std::move(hash);
    np->sum = sum;
    if (!keyword_list.empty()) {
        int i = 0;
        auto it = keyword_list.begin();
        for (; it != keyword_list.end(); it++, i++) {
            np->location.insert(std::map<std::string, std::vector<int>>::value_type(*it, location[i]));
        }
    }
    news_list.push_back(np);
}

bool cmp(SearchResultImpl::news *a, SearchResultImpl::news *b) {
    return a->sum > b->sum;
}

void SearchResultImpl::Sort() {
    sort(news_list.begin(), news_list.end(), cmp);
}

std::vector <std::string> SearchResultImpl::Get_News_list() {
    std::vector <std::string> N_list;
    for (auto &it : news_list) {
        N_list.push_back(it->hash_code);
    }
    return N_list;
}

std::vector <std::string> SearchResultImpl::Get_Keyword_List() {
    return keyword_list;
}

std::vector<int> SearchResultImpl::Get_Location_list(std::string block_header, std::string keyword) {
    std::vector<int> location_list;
    for (auto &it : news_list) {
        if (it->hash_code == block_header) {
            int num = keyword.size();
            auto lit = it->location[keyword].begin();
            auto end = it->location[keyword].end();
            for (; lit != end; lit++) {
                location_list.push_back((*lit) - num + 1);
            }
            break;
        }
    }
    return location_list;
}

void SearchResultImpl::Destruction() {
    if (!news_list.empty())
        for (auto &it : news_list) {
            delete it;
        }
}
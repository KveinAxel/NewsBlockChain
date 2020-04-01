#include "Search_Result_impl.h"

#include <utility>

void Search_Result_impl::push(std::vector<std::string> &words) {
    keyword_list.assign(words.begin(), words.end());
}

void Search_Result_impl::insert(std::string hash, int sum, const std::vector<std::vector<int>> &location) {
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

bool cmp(Search_Result_impl::news *a, Search_Result_impl::news *b) {
    return a->sum > b->sum;
}

void Search_Result_impl::Sort() {
    sort(news_list.begin(), news_list.end(), cmp);
}

std::vector <std::string> Search_Result_impl::Get_News_list() {
    std::vector <std::string> N_list;
    for (auto &it : news_list) {
        N_list.push_back(it->hash_code);
    }
    return N_list;
}

std::vector <std::string> Search_Result_impl::Get_Keyword_List() {
    return keyword_list;
}

std::vector<int> Search_Result_impl::Get_Location_list(std::string block_header, std::string keyword) {
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

void Search_Result_impl::Destruction() {
    if (!news_list.empty())
        for (auto &it : news_list) {
            delete it;
        }
}
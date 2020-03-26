//
// Created by administrator-PC on 2020/3/25.
//

#include "Search_Result_impl.h"
void Search_Result_impl::push(vector<string> &words) {

    keyword_list.assign(words.begin(),words.end());
}
void Search_Result_impl::insert(string hash_code, int sum, const vector<vector<int>>& location) {
    news* np=new news;
    np->hash_code=hash_code;
    np->sum=sum;
    if (!keyword_list.empty()) {
        int i = 0;
        auto it = keyword_list.begin();
        for (; it != keyword_list.end(); it++, i++) {
            np->location.insert(map<string, vector<int>>::value_type(*it,location[i]));
        }
    }
    news_list.push_back(np);
}
bool cmp(Search_Result_impl::news *a, Search_Result_impl::news *b) {
    return a->sum>b->sum;
}
void Search_Result_impl::Sort() {
    sort(news_list.begin(),news_list.end(),cmp);
}
vector<string> Search_Result_impl::Get_News_list(){
    vector<string> N_list;
    for (auto it =news_list.begin() ; it !=news_list.end() ; ++it) {
        N_list.push_back((*it)->hash_code);
    }
    return N_list;
}
vector<string> Search_Result_impl::Get_Keyword_List() {
    return keyword_list;
}
vector<int> Search_Result_impl::Get_Location_list(string block_header, string keyword) {
    vector<int> location_list;
    for (auto it =news_list.begin() ; it !=news_list.end() ; ++it) {
        if((*it)->hash_code==block_header){
            int num = keyword.size();
            auto lit=(*it)->location[keyword].begin();
            auto end=(*it)->location[keyword].end();
            for ( ;lit!=end  ; lit++) {
                location_list.push_back((*lit)-num+1);
            }
            break;
        }
    }
    return location_list;
}
void Search_Result_impl:: Destruction()
{
    if (!news_list.empty())
        for (auto it= news_list.begin();  it!=news_list.end() ; it++) {
            delete *it;
        }
    delete this;
}
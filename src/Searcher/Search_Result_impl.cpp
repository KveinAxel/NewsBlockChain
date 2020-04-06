//
// Created by administrator-PC on 2020/3/25.
//

#include "Search_Result_impl.h"
void Search_Result_impl::push(const vector<string> &words) {

    keyword_list.assign(words.begin(),words.end());
}
void Search_Result_impl::insert(int sum, const vector<vector<int>>& location) {
    passage.sum=sum;
    if (!keyword_list.empty()) {
        int i = 0;
        auto it = keyword_list.begin();
        for (; it != keyword_list.end(); it++, i++) {
            passage.location.insert(map<string, vector<int>>::value_type(*it,location[i]));
        }
    }
}
int Search_Result_impl::Get_Total(){
    return passage.sum;
}
vector<string> Search_Result_impl::Get_Keyword_List() {
    return keyword_list;
}
int Search_Result_impl::Get_num(string keyword) {
    return passage.location[keyword].size();
}
vector<int> Search_Result_impl::Get_Location_list(string keyword) {
    vector<int> location_list;
    int num = keyword.size();
    auto lit=passage.location[keyword].begin();
    auto end=passage.location[keyword].end();
    for ( ;lit!=end  ; lit++) {
        location_list.push_back((*lit)-num+1);
    }
    return location_list;
}
void Search_Result_impl:: Destruction()
{
    delete this;
}
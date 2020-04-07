//
// Created by administrator-PC on 2020/3/25.
//

#include "SearcherImpl.h"
SearcherImpl::SearcherImpl() {
    TrieDictionary* dictionary1=new TrieDictionary;
    setDictionary(dictionary1);
}
void SearcherImpl::setDictionary(TrieDictionary *dictionary) {
    SearcherImpl::dictionary = dictionary;
}
void SearcherImpl::Enter_Keywords(const vector<string>&keywords){
    keywords_list.assign(keywords.begin(),keywords.end());
    dictionary->push(keywords);
    dictionary->build_failure_pointer();
}
search_result& SearcherImpl::Keyword_Search(const string& text) {
    vector<vector<int>> loca(keywords_list.size());
    int sum=0;

    sum=dictionary->find(text,loca);

    Search_Result_impl* result=new Search_Result_impl;
    result->push(keywords_list);
    result->insert(sum,loca);
    return *result;
}



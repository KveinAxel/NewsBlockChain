#include "SearcherImpl.h"
#include "Search_Result_impl.h"

SearcherImpl::SearcherImpl() = default;

void SearcherImpl::setDictionary(TrieDictionary *dict) {
    SearcherImpl::dictionary = dict;
}

search_result& SearcherImpl::Keyword_Search(string block_header, const vector<string> &keywords_list) {
    return *(new Search_Result_impl);
}



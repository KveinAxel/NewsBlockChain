#include "SearcherImpl.h"

SearcherImpl::SearcherImpl() {
    TrieDictionary *dictionary1 = new TrieDictionary;
    setDictionary(dictionary1);
}

void SearcherImpl::setDictionary(TrieDictionary *dict) {
    SearcherImpl::dictionary = dict;
}

void SearcherImpl::Enter_Keywords(const std::vector<std::string> &keywords) {
    keywords_list.assign(keywords.begin(), keywords.end());
    dictionary->push(keywords);
    dictionary->build_failure_pointer();
}

SearchResult &SearcherImpl::Keyword_Search(const std::string &text) {
    std::vector<std::vector<int>> loca(keywords_list.size());
    int sum = 0;

    sum = dictionary->find(text, loca);

    SearchResultImpl *result = new SearchResultImpl;
    result->push(keywords_list);
    result->insert(sum, loca);
    return *result;
}

SearcherImpl::~SearcherImpl() {
    delete this->dictionary;
}

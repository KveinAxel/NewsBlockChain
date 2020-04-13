#ifndef NEWS_BLOCK_CHAIN_SEARCHER_IMPL_H
#define NEWS_BLOCK_CHAIN_SEARCHER_IMPL_H

#include "Searcher.h"
#include "TrieDictionary.h"
#include "SearchResultImpl.h"

/**
 * 搜索器的实现类
 */
class SearcherImpl: public Searcher {
private:
    TrieDictionary* dictionary;
    std::vector<std::string> keywords_list;

public:
    SearcherImpl();

    /**
     * 注入字典类后使用
     * @param dictionary
     */
    void setDictionary(TrieDictionary *dictionary);

    void Enter_Keywords(const std::vector<std::string> &keywords);

    SearchResult& Keyword_Search(const std::string &text);

    ~SearcherImpl();
};


#endif //NEWS_BLOCK_CHAIN_SEARCHER_IMPL_H

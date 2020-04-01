#ifndef NEWS_BLOCK_CHAIN_SEARCHER_IMPL_H
#define NEWS_BLOCK_CHAIN_SEARCHER_IMPL_H

#include "Searcher.h"
#include "TrieDictionary.h"

/**
 * 搜索器的实现类
 */
class SearcherImpl: public searcher {
private:
    TrieDictionary* dictionary{};
public:
    SearcherImpl();

    /**
     * 注入字典类后使用
     * @param dictionary
     */
    void setDictionary(TrieDictionary *dictionary);

    // todo 搜索函数
    search_result& Keyword_Search(std::string block_header,const std::vector<std::string>&keywords_list) override;
};


#endif //NEWS_BLOCK_CHAIN_SEARCHER_IMPL_H

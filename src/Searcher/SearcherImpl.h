//
// Created by administrator-PC on 2020/3/25.
//

#ifndef PART1_SEARCHERIMPL_H
#define PART1_SEARCHERIMPL_H

#include "Searcher.h"
#include "TrieDictionary.h"
/**
 * 搜索器的实现类
 */
class SearcherImpl: public searcher {
private:
    TrieDictionary* dictionary;
public:
    SearcherImpl();
    void setDictionary(TrieDictionary *dictionary);//注入字典类后使用
    //搜索函数（差其它组件配合还没写完）
    search_result& Keyword_Search(string block_header,const vector<string>&keywords_list);
};


#endif //PART1_SEARCHERIMPL_H

#ifndef NEWS_BLOCK_CHAIN_SEARCH_RESULT_IMPL_H
#define NEWS_BLOCK_CHAIN_SEARCH_RESULT_IMPL_H

#include "Searcher.h"
#include <map>
#include <algorithm>

/**
 * 搜索结果的实现类
 */
class SearchResultImpl : public SearchResult {
public:
    struct news{
        /**
         * 单词总数
         */
        int sum;

        std::map<std::string,std::vector<int>> location;
    };
    /**
     * 插入一组词
     * @param words
     */
    void push(const std::vector<std::string> &words);

    /**
     *
     * @param hash
     * @param sum
     * @param location
     */
    void insert(int sum, const std::vector<std::vector<int>> &location);

    /**
     * 得到所有关键词加起来总数
     * @return
     */
    int Get_Total() override;


    /**
     * 得到关键词列表
     * @return
     */
    std::vector<std::string> Get_Keyword_List() override;

    /**
     * 得到单个单词数量
     * @param keyword
     * @return
     */
    virtual int Get_num(std::string keyword) override;

    /**
     * 按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
     * @param block_header
     * @param keyword
     * @return
     */
    std::vector<int> Get_Location_list(std::string keyword) override;

private:
    /**
     * 关键词列表
     */
    std::vector<std::string> keyword_list;

    /**
     * 新闻列表
     */
    news passage;//新闻列表
};


#endif // NEWS_BLOCK_CHAIN_SEARCH_RESULT_IMPL_H

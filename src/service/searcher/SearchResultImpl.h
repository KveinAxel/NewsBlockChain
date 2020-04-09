#ifndef NEWS_BLOCK_CHAIN_SEARCHRESULTIMPL_H
#define NEWS_BLOCK_CHAIN_SEARCHRESULTIMPL_H

#include "Searcher.h"
#include <map>
#include <algorithm>

/**
 * 搜索结果的实现类
 */
class SearchResultImpl : public SearchResult {
public:
    struct news {
        /**
         * 文章哈希值
         */
        std::string hash_code;

        /**
         * 单词总数
         */
        int sum;

        std::map<std::string, std::vector<int>> location;
    };

    /**
     * 插入一组词
     * @param words
     */
    void push(std::vector<std::string> &words);

    /**
     *
     * @param hash
     * @param sum
     * @param location
     */
    void insert(std::string hash, int sum, const std::vector<std::vector<int>> &location);

    /**
     *
     */
    void Sort();

    /**
     * 按关键词搜索总数从高到低得到新闻区块头列表
     * @return
     */
    std::vector<std::string> Get_News_list() override;

    /**
     * 得到关键词列表
     * @return
     */
    std::vector<std::string> Get_Keyword_List() override;

    /**
     * 按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
     * @param block_header
     * @param keyword
     * @return
     */
    std::vector<int> Get_Location_list(std::string block_header, std::string keyword) override;

    /**
     * 不再使用时手动销毁这个对象
     */
    void Destruction() override;

private:
    /**
     * 关键词列表
     */
    std::vector<std::string> keyword_list;

    /**
     * 新闻列表
     */
    std::vector<news *> news_list;
};


#endif //NEWS_BLOCK_CHAIN_SEARCHRESULTIMPL_H

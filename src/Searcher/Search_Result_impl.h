#ifndef NEWS_BLOCK_CHAIN_SEARCH_RESULT_IMPL_H
#define NEWS_BLOCK_CHAIN_SEARCH_RESULT_IMPL_H

#include "../util/Searcher.h"
#include <map>
#include <algorithm>
using std::map;

/**
 * 搜索结果的实现类
 */
class Search_Result_impl: public search_result {
public:
    struct news{
        /**
         * 文章哈希值
         */
        string hash_code;

        /**
         * 单词总数
         */
        int sum;

        map<string,vector<int>> location;
    };
    /**
     * 插入一组词
     * @param words
     */
    void push(vector<string> & words);

    /**
     *
     * @param hash
     * @param sum
     * @param location
     */
    void insert(string hash,int sum,const vector<vector<int>>&location);

    /**
     *
     */
    void Sort();

    /**
     * 按关键词搜索总数从高到低得到新闻区块头列表
     * @return
     */
    vector<string> Get_News_list() override;

    /**
     * 得到关键词列表
     * @return
     */
    vector<string> Get_Keyword_List() override;

    /**
     * 按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
     * @param block_header
     * @param keyword
     * @return
     */
    vector<int> Get_Location_list(string block_header,string keyword) override;

    /**
     * 不再使用时手动销毁这个对象
     */
    void Destruction() override;
private:
    /**
     * 关键词列表
     */
    vector<string> keyword_list;

    /**
     * 新闻列表
     */
    vector<news*> news_list;
};


#endif //NEWS_BLOCK_CHAIN_SEARCH_RESULT_IMPL_H

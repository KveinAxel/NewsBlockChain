#ifndef NEWS_BLOCK_CHAIN_SEARCHER_H
#define NEWS_BLOCK_CHAIN_SEARCHER_H

#include <vector>
#include <string>

class SearchResult {
public:
    /**
     * 得到所有关键词加起来总数
     * @return
     */
    virtual int Get_Total() = 0;

    /**
     * 得到单个单词数量
     * @param keyword
     * @return
     */
    virtual int Get_num(std::string keyword) = 0;

    //
    /**
     * 得到关键词列表
     * @return
     */
    virtual std::vector<std::string> Get_Keyword_List() = 0;

    /**
     * 按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
     * @param keyword
     * @return
     */
    virtual std::vector<int> Get_Location_list(std::string keyword)=0;
};

class Searcher {
public:
    /**
     * 一个接口
     * @param text 搜索开始时的区块头
     * @param keywords_list 关键词列表
     * @return 返回一个结果对象引用，使用后需手动销毁
     */
    virtual SearchResult &Keyword_Search(const std::string &text) = 0;

    /**
     * 查找前先注入关键词
     * @param keywords_list
     */
    virtual void Enter_Keywords(const std::vector<std::string> &keywords_list) = 0;//查找前先注入关键词

};

#endif // NEWS_BLOCK_CHAIN_SEARCHER_H

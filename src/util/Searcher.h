#ifndef NEWS_BLOCK_CHAIN_SEARCHER_H
#define NEWS_BLOCK_CHAIN_SEARCHER_H
#include <vector>
#include <string>

class search_result {
public:
    /**
     * 按关键词搜索总数从高到低得到新闻区块头列表
     * @return
     */
    virtual std::vector<std::string> Get_News_list() = 0;

    //
    /**
     * 得到关键词列表
     * @return
     */
    virtual std::vector<std::string> Get_Keyword_List() = 0;

    /**
     * 按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
     * @param block_header
     * @param keyword
     * @return
     */
    virtual std::vector<int> Get_Location_list(std::string block_header, std::string keyword) = 0;

    /**
     * 不再使用时手动销毁这个对象
     */
    virtual void Destruction() = 0;
};

class searcher {
public:
    /**
     * 一个接口
     * @param block_header 搜索开始时的区块头
     * @param keywords_list 关键词列表
     * @return 返回一个结果对象引用，使用后需手动销毁
     */
    virtual search_result &Keyword_Search(std::string block_header, const std::vector<std::string> &keywords_list) = 0;
};

#endif // NEWS_BLOCK_CHAIN_SEARCHER_H

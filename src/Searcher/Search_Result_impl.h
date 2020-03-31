//
// Created by administrator-PC on 2020/3/25.
//

#ifndef PART1_SEARCH_RESULT_IMPL_H
#define PART1_SEARCH_RESULT_IMPL_H

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
        string hash_code;//文章哈希值
        int sum;//单词总数
        map<string,vector<int>> location;
    };
private:
    vector<string> keyword_list;//关键词列表
    vector<news*> news_list;//新闻列表
public:
    //内部调用
    void push(vector<string> & words);//插入一组词
    void insert(string hash,int sum,const vector<vector<int>>&location);
    void Sort();
public:
    //对外接口
    vector<string> Get_News_list();//按关键词搜索总数从高到低得到新闻区块头列表
    vector<string> Get_Keyword_List();//得到关键词列表
    /*按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
    */
    vector<int> Get_Location_list(string block_header,string keyword);
    void Destruction();//不再使用时手动销毁这个对象
};


#endif //PART1_SEARCH_RESULT_IMPL_H

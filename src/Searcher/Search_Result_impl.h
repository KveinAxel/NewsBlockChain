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
        int sum;//单词总数
        map<string,vector<int>> location;
    };
private:
    vector<string> keyword_list;//关键词列表
    news passage;//新闻列表
public:
    //内部调用
    void push(const vector<string> & words);//插入一组词
    void insert(int sum,const vector<vector<int>>&location);
public:
    //对外接口
    int Get_Total();//得到所有关键词加起来总数
    vector<string> Get_Keyword_List();//得到关键词列表
    virtual int Get_num(string keyword);//得到单个单词数量
    /*按关键词得到新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
    */
    vector<int> Get_Location_list(string keyword);
    void Destruction();//不再使用时手动销毁这个对象
};


#endif //PART1_SEARCH_RESULT_IMPL_H

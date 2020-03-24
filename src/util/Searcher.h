//
// Created by administrator-PC on 2020/3/24.
//

#ifndef SEARCHER_H
#define SEARCHER_H
#include <vector>
#include <string>
using namespace std;
class search_result
{
public:
    //按关键词搜索总数从高到低得到新闻区块头列表
    virtual vector<string> Get_News_list()=0;
    //得到关键词列表
    virtual vector<string> Get_Keyword_List()=0;
    /*按新闻区块头和关键词得到区块头指向的新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
    */
    virtual vector<int> Get_Location_list(string block_header,string keyword)=0;
    //不再使用时手动销毁这个对象
    virtual void Destruction()=0;
};
class searcher
{
public:
    /**
     * @author lichangguisheng
     * @param block_header 搜索开始时的区块头
     * @param keywords_list 关键词列表
     * @return 返回一个结果对象引用，使用后需手动销毁
     * 一个接口
     */
    virtual search_result& Keyword_Search(string block_header,const vector<string>&keywords_list)=0;
};
#endif SEARCHER_H

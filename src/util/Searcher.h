//
// Created by administrator-PC on 2020/3/25.
//

#ifndef PART1_SEARCHER_H
#define PART1_SEARCHER_H
#include <vector>
#include <string>
using namespace std;
class search_result
{
public:
    //得到所有关键词加起来总数
    virtual int Get_Total()=0;
    //得到关键词列表
    virtual vector<string> Get_Keyword_List()=0;
    //得到单个单词数量
    virtual int Get_num(string keyword)=0;
    /*按关键词得到新闻中关键词出现的位置列表（关键词开头所在位置）
     * 如果找不到则返回空向量
    */
    virtual vector<int> Get_Location_list(string keyword)=0;
    //不再使用时手动销毁这个对象
    virtual void Destruction()=0;
};
class searcher
{
public:
    /**
     * @author lichangguisheng
     * @param text 搜索开始时的区块头
     * @param keywords_list 关键词列表
     * @return 返回一个结果对象引用，使用后需手动销毁
     * 一个接口
     */
    virtual void Enter_Keywords(const vector<string>&keywords_list)=0;//查找前先注入关键词
    virtual search_result* Keyword_Search(const string& text)=0;
};
#endif //PART1_SEARCHER_H

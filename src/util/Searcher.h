//
// Created by administrator-PC on 2020/3/24.
//

#ifndef SEARCHER_H
#define SEARCHER_H
#include <vector>
#include <string>
using namespace std;
class searcher
{
public:
    /**
     * @author lichangguisheng
     * @param block_header 搜索开始时的区块头
     * @param keywords_list 关键词列表
     * @return 区块头列表，值传递
     * 一个接口
     */
    virtual vector<string> Keyword_Search(string block_header,const vector<string>&keywords_list)=0;
};
#endif //MAXSUB_SEARCHER_H

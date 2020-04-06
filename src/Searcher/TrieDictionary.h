//
// Created by administrator-PC on 2020/3/25.
//

#ifndef PART1_TRIEDICTIONARY_H
#define PART1_TRIEDICTIONARY_H

#include <string.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
/**
 * @author lichangguisheng
 * 构建Tire字典树
 */
struct DictElem//单个节点
{
    string _word;//保存的单字
    DictElem* fail;//失败指针
    int _wordId;//在叶子节点中指向表示的单词下标
    unordered_map<string, shared_ptr<DictElem> > _words;//子节点保存在无序图中
};
typedef shared_ptr<DictElem> pDictElem;
//字典类
class TrieDictionary {
    typedef unordered_map<string, pDictElem>::iterator WordIt;
public:
    TrieDictionary();
    void push(const string & word, int location);//插入一个词
    void push(const vector<string> & words);//插入一组词
    void build_failure_pointer();//建立失败指针
    int find(const string& text,vector<vector<int>>& location_list);//查找函数
private:
    void splitWord(const string & word, vector<string> & characters);//把词拆成字
    pDictElem _dictionary;//字典树的根节点
};


#endif //PART1_TRIEDICTIONARY_H

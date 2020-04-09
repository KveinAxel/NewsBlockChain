#ifndef NEWS_BLOCK_CHAIN_TRIE_DICTIONARY_H
#define NEWS_BLOCK_CHAIN_TRIE_DICTIONARY_H

#include <cstring>
#include <unordered_map>
#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

/**
 * 单个节点
 */
struct DictElement {
    /**
     * 保存的单字
     */
    std::string _word;

    /**
     * 失败指针
     */
    DictElement *fail;

    /**
     * 在叶子节点中指向表示的单词下标
     */
    int _wordId;

    /**
     * 子节点保存在无序图中
     */
    std::unordered_map<std::string, std::shared_ptr<DictElement> > _words;
};

typedef std::shared_ptr<DictElement> pDictElem;

/**
 * 字典类
 */
class TrieDictionary {
public:
    typedef std::unordered_map<std::string, pDictElem>::iterator WordIt;
    TrieDictionary();

    /**
     * 插入一个词
     * @param word
     * @param location
     */
    void push(const std::string &word, int location);

    /**
     * 插入一组词
     * @param words
     */
    void push(const std::vector<std::string> &words);

    /**
     * 建立失败指针
     */
    void build_failure_pointer();

    /**
     * 查找函数
     * @param text
     * @param location_list
     * @return
     */
    int find(const std::string &text, std::vector<std::vector<int>> &location_list);
private:

    /**
     * 把词拆成字
     * @param word
     * @param characters
     */
    static void splitWord(const std::string &word, std::vector<std::string> &characters);

    /**
     * 字典树的根节点
     */
    pDictElem _dictionary;
};

#endif // NEWS_BLOCK_CHAIN_TRIE_DICTIONARY_H

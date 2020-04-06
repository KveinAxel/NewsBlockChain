//
// Created by administrator-PC on 2020/3/25.
//

#include "TrieDictionary.h"
TrieDictionary::TrieDictionary(): _dictionary(new DictElem)
{
    _dictionary->_wordId = 0;
    _dictionary->fail= nullptr;
}
//UTF-8的分字
void TrieDictionary::splitWord(const string & word, vector<string> & characters)
{

    int num = word.size();
    int i = 0;
    while(i < num)
    {
        int size = 1;
        if(word[i] & 0x80)
        {
            char temp = word[i];
            temp <<= 1;
            do{
                temp <<= 1;
                ++size;
            }while(temp & 0x80);
        }
        string subWord;
        subWord = word.substr(i, size);
        transform(subWord.begin(),subWord.end(),subWord.begin(),::tolower);
        characters.push_back(subWord);
        i += size;
    }
}
void TrieDictionary::push(const string & word, int location)
{
    vector<string> characters;//单字集合
    splitWord(word, characters);
    vector<string>::iterator it_char;
    it_char = characters.begin();
    pDictElem cur;//当前节点
    cur = _dictionary;//初始值为根节点
    for(; it_char != characters.end(); ++it_char)
    {
        WordIt it_word;//无序图迭代器
        it_word = cur->_words.find(*it_char);//在每层子节点中找相应的单字
        if(it_word == cur->_words.end())//没找到则新增节点
        {
            pair<string, pDictElem> temp;
            temp.first = *it_char;

            pDictElem dictemp(new DictElem);
            dictemp->_word = *it_char;
            dictemp->fail= nullptr;
            if(it_char==characters.end()-1)//到了单词末尾时指向单词下标
                dictemp->_wordId=location;
            else
                dictemp->_wordId = -1;

            temp.second = dictemp;
            cur->_words.insert(temp);
            cur = dictemp;
        }else{
            cur = it_word->second;
            if(it_char==characters.end()-1)//到了单词末尾时指向单词下标
                cur->_wordId=location;
        }
    }
}

void TrieDictionary::push(const vector<string> & words)
{
    int size = words.size();
    for(int i = 0; i < size; ++i)
    {
        push(words[i],i);
    }
}

void TrieDictionary::build_failure_pointer()
{
    DictElem* root=_dictionary.get();
    queue<DictElem*> queue;
    queue.push(root);
    while (!queue.empty()) {
        DictElem* cur = queue.front();
        queue.pop();
        WordIt dit=cur->_words.begin();
        for (; dit != cur->_words.end(); dit++) {
            if (cur == root) dit->second->fail = root;
            else {
                DictElem* tmp = cur->fail;
                while (tmp != nullptr) {
                    if (tmp->_words.count(dit->first)!=0) {
                        dit->second->fail = tmp->_words.find(dit->first)->second.get();
                        break;
                    }
                    tmp = tmp->fail;
                }
                if (tmp == nullptr) dit->second->fail = root;
            }
            queue.push(dit->second.get());
        }
    }
}

int TrieDictionary::find(const string& text, vector<vector<int>> &location_list) {
    int sum=0;
    int i=1;
    DictElem* root=_dictionary.get();
    DictElem* pre = root;
    vector<string> characters;//单字集合
    splitWord(text, characters);
    vector<string>::iterator cit=characters.begin();
    for (; cit != characters.end(); cit++,i++) {
        string index = *(cit);
        while (pre->_words.find(index) == pre->_words.end() && pre != root) {
            pre = pre->fail;
        }
        if (pre == root && pre->_words.find(index) == pre->_words.end())
            continue;
        pre = pre->_words.find(index)->second.get();
        DictElem* tmp = pre;
        if (tmp != root && tmp->_wordId!=-1) {
            sum++;
            location_list[tmp->_wordId].push_back(i);
        }
    }
    return sum;
}
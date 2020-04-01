#include "TrieDictionary.h"

TrieDictionary::TrieDictionary() : _dictionary(new DictElement) {
    _dictionary->_wordId = 0;
    _dictionary->fail = nullptr;
}

// UTF-8的分字
void TrieDictionary::splitWord(const std::string &word, std::vector<std::string> &characters) {

    uint32_t num = word.size();
    uint32_t i = 0;
    while (i < num) {
        int size = 1;
        uint8_t ch = word[i];
        if (ch & 0x80u) {
            uint8_t temp = word[i];
            temp <<= 1u;
            do {
                temp <<= 1u;
                ++size;
            } while (temp & 0x80u);
        }
        std::string subWord;
        subWord = word.substr(i, size);
        transform(subWord.begin(), subWord.end(), subWord.begin(), ::tolower);
        characters.push_back(subWord);
        i += size;
    }
}

void TrieDictionary::push(const std::string &word, int location) {
    std::vector<std::string> characters; // 单字集合
    splitWord(word, characters);
    std::vector<std::string>::iterator it_char;
    it_char = characters.begin();
    pDictElem cur; // 当前节点
    cur = _dictionary; // 初始值为根节点
    for (; it_char != characters.end(); ++it_char) {
        WordIt it_word; // 无序图迭代器
        it_word = cur->_words.find(*it_char); // 在每层子节点中找相应的单字
        // 没找到则新增节点
        if (it_word == cur->_words.end()) {
            std::pair<std::string, pDictElem> temp;
            temp.first = *it_char;

            pDictElem dictemp(new DictElement);
            dictemp->_word = *it_char;
            dictemp->fail = nullptr;
            if (it_char == characters.end() - 1) // 到了单词末尾时指向单词下标
                dictemp->_wordId = location;
            else
                dictemp->_wordId = -1;

            temp.second = dictemp;
            cur->_words.insert(temp);
            cur = dictemp;
        } else {
            cur = it_word->second;
            if (it_char == characters.end() - 1) // 到了单词末尾时指向单词下标
                cur->_wordId = location;
        }
    }
}

void TrieDictionary::push(std::vector<std::string> &words) {
    int size = words.size();
    for (int i = 0; i < size; ++i) {
        push(words[i], i);
    }
}

void TrieDictionary::build_failure_pointer() {
    DictElement *root = _dictionary.get();
    std::queue<DictElement *> queue;
    queue.push(root);
    while (!queue.empty()) {
        DictElement *cur = queue.front();
        queue.pop();
        auto dit = cur->_words.begin();
        for (; dit != cur->_words.end(); dit++) {
            if (cur == root) dit->second->fail = root;
            else {
                DictElement *tmp = cur->fail;
                while (tmp != nullptr) {
                    if (tmp->_words.count(dit->first) != 0) {
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

int TrieDictionary::find(const std::string &text, std::vector<std::vector<int>> &location_list) {
    int sum = 0;
    int i = 1;
    DictElement *root = _dictionary.get();
    DictElement *pre = root;
    std::vector<std::string> characters;//单字集合
    splitWord(text, characters);
    auto cit = characters.begin();
    for (; cit != characters.end(); cit++, i++) {
        std::string index = *(cit);
        while (pre->_words.find(index) == pre->_words.end() && pre != root) {
            pre = pre->fail;
        }
        if (pre == root && pre->_words.find(index) == pre->_words.end())
            continue;
        pre = pre->_words.find(index)->second.get();
        DictElement *tmp = pre;
        if (tmp != root && tmp->_wordId != -1) {
            sum++;
            location_list[tmp->_wordId].push_back(i);
        }
    }
    return sum;
}
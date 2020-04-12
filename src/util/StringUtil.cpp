#include "StringUtil.h"

std::vector<std::string> stringSplit(const std::string &s, const std::string &note) {
    std::vector<std::string> res;
    size_t pos = 0;
    size_t len = s.length();
    size_t noteLen = note.length();
    if (noteLen == 0) return res;
    while (pos < len) {
        int find_pos = s.find(note, pos);
        if (find_pos < 0) {
            res.push_back(s.substr(pos, len - pos));
            break;
        }
        res.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + noteLen;
    }
    return res;
}

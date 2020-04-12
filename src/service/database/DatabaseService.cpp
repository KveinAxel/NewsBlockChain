#include <Global.h>
#include "DatabaseService.h"

Message<std::string> DatabaseService::saveBlock(std::string key, std::string value) {
    auto global = Global::getGlobal();
    global->database[key] = value;
    return Message<std::string>::success("保存成功");
}

Message<std::string> DatabaseService::getBlock(std::string key) {
    auto global = Global::getGlobal();
    auto itr = global->database.find(key);
    if (itr == global->database.end()) {
        return Message<std::string>::fail(400, "查找失败");
    } else {
        std::string *str = new std::string(itr->second);
        return Message<std::string>::success("查找成功", str);
    }
}

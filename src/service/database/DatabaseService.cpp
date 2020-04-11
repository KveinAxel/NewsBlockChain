#include "DatabaseService.h"

Message<std::string> DatabaseService::saveBlock(std::string key, std::string value) {
    // todo 将区块保存至数据库
    return Message<std::string>::success(key);
}

Message<std::string> DatabaseService::getBlock(std::string key) {
    // todo 从数据库得到区块内容
    return Message<std::string>::success(key);
}

#include "BlockChainService.h"

Message<std::string> BlockChainService::addToBlockChain(std::string article) {
    // todo
    return Message<std::string>::success(article);
}

Message<std::string> BlockChainService::confirmArticle(std::string article) {
    // todo
    return Message<std::string>::success(article);
}

Message<std::vector<std::pair<std::string, time_t>>> BlockChainService::list() {
    // todo
    return Message<std::vector<std::pair<std::string, time_t>>>::success("成功");
}

Message<std::string> BlockChainService::broadcast(std::string block) {
    // todo
    return Message<std::string>::success(block);
}

Message<std::string> BlockChainService::getBlockChain() {
    // todo
    return Message<std::string>::success("成功");
}

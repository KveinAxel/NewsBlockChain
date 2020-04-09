#include "BlockChainService.h"

Message<std::string> BlockChainService::addToBlockChain(std::string article) {
    // todo
    return Message<std::string>::success(article);
}

Message<std::string> BlockChainService::confirmArticle(std::string article) {
    // todo
    return Message<std::string>::success(article);
}

Message<std::pair<byte, std::string>> BlockChainService::list() {
    // todo
    return Message<std::pair<byte, std::string>>::success("成功");
}

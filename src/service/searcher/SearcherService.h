#ifndef NEWS_BLOCK_CHAIN_SEARCHER_SERVICE_H
#define NEWS_BLOCK_CHAIN_SEARCHER_SERVICE_H

#include <vector>
#include <Message.h>


class SearcherService {
public:
    static Message<std::vector<std::string>> search(std::vector<std::string> keywords);
};


#endif // NEWS_BLOCK_CHAIN_SEARCHER_SERVICE_H

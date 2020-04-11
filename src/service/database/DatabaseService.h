#ifndef NEWS_BLOCK_CHAIN_DATABA_SESERVICE_H
#define NEWS_BLOCK_CHAIN_DATABA_SESERVICE_H

#include <Message.h>

class DatabaseService {
public:
    static Message<std::string> saveBlock(std::string key, std::string value);

    static Message<std::string> getBlock(std::string key);
};


#endif // NEWS_BLOCK_CHAIN_DATABA_SESERVICE_H

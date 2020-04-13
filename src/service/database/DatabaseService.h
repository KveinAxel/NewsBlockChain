#ifndef NEWS_BLOCK_CHAIN_DATABASE_SERVICE_H
#define NEWS_BLOCK_CHAIN_DATABASE_SERVICE_H

#include <Message.h>

class DatabaseService {
public:
    static Message<std::string> save();

    static Message<std::string> load();
};


#endif // NEWS_BLOCK_CHAIN_DATABASE_SERVICE_H

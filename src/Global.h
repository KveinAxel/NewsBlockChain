#ifndef NEWS_BLOCK_CHAIN_GLOBAL_H
#define NEWS_BLOCK_CHAIN_GLOBAL_H

#include <vector>
#include "util/Logger.h"

class Global {
private:
    LOGGER::CLogger *logger;
    Global();
public:
    std::vector<std::string> ip_tables;
    bool isSuperNode;
    static Global* global;
    ~Global();
    LOGGER::CLogger* getLogger();
    static Global* getGlobal();
};


#endif //NEWS_BLOCK_CHAIN_GLOBAL_H

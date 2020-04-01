#ifndef NEWS_BLOCK_CHAIN_GLOBAL_H
#define NEWS_BLOCK_CHAIN_GLOBAL_H

#include "util/Logger.h"

class Global {
private:
    LOGGER::CLogger *logger;
    Global();
public:

    static Global* global;
    ~Global();
    LOGGER::CLogger* getLogger();
    static Global* getGlobal();
};


#endif //NEWS_BLOCK_CHAIN_GLOBAL_H

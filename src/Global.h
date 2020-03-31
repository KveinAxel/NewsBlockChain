#ifndef NEWS_BLOCK_CHAIN_GLOBAL_H
#define NEWS_BLOCK_CHAIN_GLOBAL_H


#include "../ext/cpp-httplib/httplib.h"
#include "util/Logger.h"

class Global {
private:
    httplib::Server *server;
    LOGGER::CLogger *logger;
    static Global* global;
    Global();

public:
    ~Global();
    httplib::Server* getServer();
    LOGGER::CLogger* getLogger();
    static Global* getGlobal();
};


#endif //NEWS_BLOCK_CHAIN_GLOBAL_H

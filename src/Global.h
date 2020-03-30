//
// Created by Kevin on 2020/3/30.
//

#ifndef NEWS_BLOCK_CHAIN_GLOBAL_H
#define NEWS_BLOCK_CHAIN_GLOBAL_H


#include "../ext/cpp-httplib/httplib.h"

class Global {
private:
    httplib::Server *server;
public:
    Global();
    ~Global();
    httplib::Server* getServer();
};


#endif //NEWS_BLOCK_CHAIN_GLOBAL_H

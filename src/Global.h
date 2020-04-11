#ifndef NEWS_BLOCK_CHAIN_GLOBAL_H
#define NEWS_BLOCK_CHAIN_GLOBAL_H

#include <vector>
#include <map>
#include "util/Logger.h"

class Global {
private:
    LOGGER::CLogger *logger;
    Global();
public:
    std::map<std::string, int> ip_tables{};
    bool isSuperNode = false;
    std::string localURL;
    int localPort;
    static Global* global;
    ~Global();
    LOGGER::CLogger* getLogger();
    static Global* getGlobal();
    static std::string serverURL;
    static int serverPort;
};


#endif //NEWS_BLOCK_CHAIN_GLOBAL_H

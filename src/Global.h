#ifndef NEWS_BLOCK_CHAIN_GLOBAL_H
#define NEWS_BLOCK_CHAIN_GLOBAL_H

#include <vector>
#include <map>
#include <service/blockchain/BlockChain.h>
#include "util/Logger.h"

class Global {
private:
    LOGGER::CLogger *logger;
    Global();
public:
    std::vector<std::pair<std::string, int>> ip_tables;
    std::map<std::string, std::string> database{};
    BlockChain* blockChain = nullptr;
    bool isSuperNode = false;
    std::string localURL;
    int localPort = 0;
    static Global* global;
    ~Global();
    LOGGER::CLogger* getLogger();
    static Global* getGlobal();
    static std::string serverURL;
    static int serverPort;
};


#endif //NEWS_BLOCK_CHAIN_GLOBAL_H

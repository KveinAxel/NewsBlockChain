#ifndef NEWS_BLOCK_CHAIN_HASH_H
#define NEWS_BLOCK_CHAIN_HASH_H

#include <string>

class Hash{

public:
    static char* hash(const unsigned char* ikm, size_t ikmlen, const std::string& salt);
};


#endif // HASH_H

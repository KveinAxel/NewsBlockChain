#ifndef HASH_H
#define HASH_H

#include <string>

class Hash{

public:
    static char* hash(const unsigned char* ikm, size_t ikmlen, const std::string& salt);
};


#endif // HASH_H

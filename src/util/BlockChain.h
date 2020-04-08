#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "Block.h"
#include <QHash>
class BlockChain{
public:
    QHash<int,BlockObj*> blockChainHash;//使用hash来实现链
};

#endif // BLOCKCHAIN_H

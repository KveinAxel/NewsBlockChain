#include "Block.h"
BlockObj::~BlockObj(){
    delete BlockObj::merkletree;
    //delete BlockObj::merkleIndex;
}
QList<int> BlockObj::modifyCheck(const QList<std::string> article){
    return merkletree->modifyCheck(article);
}

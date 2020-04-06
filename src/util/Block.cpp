#include "Block.h"
BlockObj::~BlockObj(){
    delete BlockObj::merkletree;
    delete BlockObj::merkleIndex;
}

#include "BlockChain.h"


BlockChain::BlockChain(){
}
QJsonObject BlockChain::serializeToJson(BlockObj* block){
    QJsonObject jsonObject;
    jsonObject.insert("hashKey",QString::fromUtf8(block->blockHeadHash().data()));
    for(int i=0;i<block->paragraphNum();i++){
            jsonObject[QString("article_%1").arg(i+1)]=QString::fromStdString(block->article.at(i));
    }
    jsonObject.insert("lastHash",QString::fromUtf8(block->lastHash.data()));
    jsonObject.insert("createTime",block->createTime);
    jsonObject.insert("merkleRoot",QString::fromUtf8(block->merkleRoot.data()));
    return jsonObject;
}
BlockObj* BlockChain::unserializeFromJson(QJsonObject& jsonObject){
    BlockObj* blockObj=new BlockObj(jsonObject);
    return blockObj;
}
bool BlockChain::updateBlock(BlockObj *request){
    if(BlockChain::blockChainHash.contains(request->currentHash)){
        delete request;
        return false;//链中已有，数据库里一定也存了
    }
    if(request->isLegal==true){
        request->store();
        BlockChain::blockChainHash.insert(request->currentHash,request);
        if(request->lastHash==BlockChain::currentHashKey||BlockChain::currentHashKey.length()==0){
            //如果一开始BlockChain::currentHashKey为空，这也要更新BlockChain::currentHashKey
            BlockChain::currentHashKey=request->currentHash;
        }
        return true;
    }
    else{
        delete request;//不合法
        qDebug()<<"不合法！";
        return false;
    }
}
BlockChain::~BlockChain(){
    QHashIterator<string,BlockObj*> iterator(BlockChain::blockChainHash);
    while (iterator.hasNext()){
        iterator.next();
        delete iterator.value();
    }
}

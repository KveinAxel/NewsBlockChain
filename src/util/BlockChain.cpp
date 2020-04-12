#include "BlockChain.h"


BlockChain::BlockChain(){
}
QPair<QJsonObject,bool> BlockChain::responseBlock(string &keyOfResponse){
        if(!BlockChain::blockChainHash.contains(keyOfResponse)){
            if(!BlockChain::containLegalBlock(keyOfResponse)){
                qDebug()<<"本地不存在该块";//首先应该去向别的节点请求，这里先这样写
                QJsonObject json;
                json["content"]="not find";
                return QPair<QJsonObject,bool>(json,false);
            }
           else{
                //向数据库请求
                BlockObj* blockObj=new BlockObj(keyOfResponse);
                BlockChain::updateBlock(blockObj);
        }
        return QPair<QJsonObject,bool>(BlockChain::serializeToJson(BlockChain::blockChainHash.value(keyOfResponse)),true);
}
}
QJsonObject BlockChain::serializeToJson(BlockObj* block){
    QJsonObject jsonObject;
    jsonObject.insert("hashKey",QString::fromUtf8(block->blockHeadHash().data()));
    for(int i=0;i<block->article.size();i++){
            jsonObject[QString("article_%1").arg(i+1)]=QString::fromStdString(block->article.at(i));
    }
    jsonObject.insert("lastHash",QString::fromUtf8(block->lastHash.data()));
    jsonObject.insert("createTime",block->createTime.toString("yyyy.MM.dd hh:mm:ss"));
    jsonObject.insert("merkleRoot",QString::fromUtf8(block->merkleRoot.data()));
    return jsonObject;
}
BlockObj* BlockChain::unserializeFromJson(QJsonObject& jsonObject){
    BlockObj* blockObj=new BlockObj(jsonObject);
    return blockObj;
}
bool BlockChain::updateBlock(BlockObj *request){
//    if(BlockChain::blockChainHash.contains(request->currentHash)){
//        delete request;
//        return false;//链中已有，数据库里一定也存了
//    }
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
bool BlockChain::containLegalBlock(QJsonObject &jsonObject){
    string headHash=jsonObject.value("lastHash").toString().toStdString().data();
    headHash.append(jsonObject.value("createTime").toString().toStdString().data());
    headHash.append(jsonObject.value("merkleRoot").toString().toStdString().data());
    Hash temp=Hash(headHash);
    if(jsonObject.value("hashKey").toString().toStdString()!=temp.toString()){
        return false;
    }
    //验证josn里的hashKey与其实际头的hash一定是相符合的，不符合则返回false,本节点不接纳连hashKey与其实际头的hash都不符合的数据，也确保一些
    //连本系统的hash函数都不知道的恶意人士攻击
    //验证数据库有没有该块 jsonObject.value("hashKey").toString().toStdString()为验证的key
    return true;
}
bool BlockChain::containLegalBlock(string& hashKey){
    //验证数据库有没有该块
}
QJsonObject BlockChain::createBlockLocal(const QList<std::string> &article){
    BlockObj* blockObj=new BlockObj(article,BlockChain::currentHashKey);
    return BlockChain::serializeToJson(blockObj);
}
QJsonObject BlockChain::createBlock(const QList<std::string>& article){
    BlockObj* blockObj=new BlockObj(article,this->currentHashKey);
    return BlockChain::serializeToJson(blockObj);
}
BlockChain::~BlockChain(){
    QHashIterator<string,BlockObj*> iterator(BlockChain::blockChainHash);
    while (iterator.hasNext()){
        iterator.next();
        delete iterator.value();
    }
}
QList<int> BlockChain::modifyCheckLocal(const QList<std::string> &article, string& keyOfResponse){
    QList<int> result;
    if(!BlockChain::blockChainHash.contains(keyOfResponse)){
        if(!BlockChain::containLegalBlock(keyOfResponse)){
            qDebug()<<"本地不存在该块";//首先应该去向别的节点请求，这里先这样写
            return result;
        }
       else{
            //向数据库请求
            BlockObj* blockObj=new BlockObj(keyOfResponse);
            BlockChain::updateBlock(blockObj);
        }
    }
    return BlockChain::blockChainHash.value(keyOfResponse)->modifyCheck(article);//返回哪些文章不一致
}
QList<BlockObj*> BlockChain::searchKeywordLocal(const vector<string> &keywords_list){
    std::string temp=BlockChain::currentHashKey;
    QMap<int,BlockObj*> map;
    QList<BlockObj*> list;
    while(BlockChain::blockChainHash.contains(temp)||BlockChain::containLegalBlock(temp)){
        if(!BlockChain::blockChainHash.contains(temp)){
            BlockObj* blockObj=new BlockObj(temp);
            BlockChain::updateBlock(blockObj);
        }
        map.insert(MAX_SEARCH-BlockChain::blockChainHash.value(temp)->searchKeyword(keywords_list),BlockChain::blockChainHash.value(temp));
        temp=BlockChain::blockChainHash.value(temp)->lastHash.data();
    }
    QMap<int,BlockObj*>::ConstIterator i=map.constBegin();
    int step=1;
        while(i!=map.constEnd()&&step<=2)
        {
            list.append(i.value());
            --i;
            step++;
        }
        return list;
}

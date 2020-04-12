#include "Block.h"
BlockObj::~BlockObj(){
    delete BlockObj::merkletree;
    //delete BlockObj::merkleIndex;
}
BlockObj::BlockObj(string hashKey){
    QByteArray storeInfo;//从数据库中得到
    Huffman compress;
    char* output;
    compress.Compress(storeInfo.data(),output);
    QByteArray storeBlock(output);
    QJsonDocument document=QJsonDocument::fromJson(storeBlock);
    QJsonObject jsonObject = document.object();
    this->createTime=QDateTime::fromString(jsonObject.value("createTime").toString(),"yyyy.MM.dd hh:mm:ss");
    this->merkleRoot=jsonObject.value("merkleRoot").toString().toStdString();
    this->currentHash=this->blockHeadHash();
    //this->currentHash=jsonObject.value("hashKey").toString().toStdString();
    //由于前面验证过，josn里的hashKey与其实际头的hash一定是相符合的，否者在containLegalBlock()函数直接就会被不接受
    string articlePara;
    int i=1;
    while(1){
        if(jsonObject.contains(QString("article_%1").arg(i+1))){
            articlePara=jsonObject.value(QString("article_%1").arg(i)).toString().toStdString();
            this->article.append(articlePara);
        }
        else break;
    }
    merkletree=new MerkleTree(article);
    if(merkleRoot!=merkletree->merkleRoot())
        isLegal=false;
    else
        isLegal=true;
    this->currentHash=BlockObj::blockHeadHash();
}
bool BlockObj::store(){
    //可以store说明数据库中应该没有储存它，因为在生成这个对象前确保了static bool containLegalBlock(string& hashKey);不存在
    if(isLegal==false)
        return false;//再次确保不存非法区块
    QJsonDocument storeText;
    storeText.setObject(BlockObj::serializeToJsonForStore());
    QByteArray jsonBytes = storeText.toJson(QJsonDocument::Compact);
    Huffman compress;
    char* output;
    compress.Compress(jsonBytes.data(),output);
    QByteArray storeInfo(output);
    //用数据库存QByteArray
    //....
    return true;
}
QJsonObject BlockObj::serializeToJsonForStore(){
    QJsonObject jsonObject;
    for(int i=0;i<article.size();i++){
            jsonObject[QString("article_%1").arg(i+1)]=QString::fromStdString(block->article.at(i));
    }
    jsonObject.insert("lastHash",QString::fromUtf8(this->lastHash.data()));
    jsonObject.insert("createTime",this->createTime.toString("yyyy.MM.dd hh:mm:ss"));
    jsonObject.insert("merkleRoot",QString::fromUtf8(this->merkleRoot.data()));
    return jsonObject;
}
QList<int> BlockObj::modifyCheck(const QList<std::string> article){
    if(article.size()!=this->article.size()){
        qDebug()<<"文章段落与区块中不符合！";//ui报错!
        QList<int> wrongreturn;
        return wrongreturn;
    }
    return merkletree->modifyCheck(article);
}

BlockObj::BlockObj(QJsonObject& jsonObject){
    this->createTime=QDateTime::fromString(jsonObject.value("createTime").toString(),"yyyy.MM.dd hh:mm:ss");
    this->merkleRoot=jsonObject.value("merkleRoot").toString().toStdString();
    this->currentHash=this->blockHeadHash();
    this->currentHash=jsonObject.value("hashKey").toString().toStdString();
    //由于前面验证过，josn里的hashKey与其实际头的hash一定是相符合的，否者在containLegalBlock()函数直接就会被不接受
    string articlePara;
    int i=1;
    while(1){
        if(jsonObject.contains(QString("article_%1").arg(i+1))){
            articlePara=jsonObject.value(QString("article_%1").arg(i)).toString().toStdString();
            this->article.append(articlePara);
        }
        else break;
    }
    merkletree=new MerkleTree(article);
    if(merkleRoot!=merkletree->merkleRoot())
        isLegal=false;
    else
        isLegal=true;
}

BlockObj::BlockObj(const QList<std::string> &article,string lastHashKey){
    this->createTime=QDateTime::currentDateTime();
    for(int i=0;i<article.size();i++){
            this->article.append(article.at(i));
    }
    merkletree=new MerkleTree(article);
    this->merkleRoot=merkletree->merkleRoot();
    this->lastHash=lastHashKey;
    this->isLegal=true;
    this->currentHash=BlockObj::blockHeadHash();
}

string BlockObj::blockArticleHash(){
    string headHash=lastHash;
    headHash.append(createTime.toString("yyyy.MM.dd hh:mm:ss").toStdString());
    headHash.append(merkleRoot);
    Hash temp=Hash(headHash);
    return temp.toString();
}

int BlockObj::searchKeyword(const vector<string> &keywords_list){
    searcher* searcherHandle= new SearcherImpl();
    searcherHandle->Enter_Keywords(keywords_list);
    string searchText;
    for(int i=0;i<BlockObj::article.size();i++){
        searchText.append(article.at(i));
    }
    search_result& resultHandle=searcherHandle->Keyword_Search(searchText);//要改接口这里
    int temp=resultHandle.Get_Total();
    resultHandle.Destruction();
    return temp;
}

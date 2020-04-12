#include "Block.h"
BlockObj::~BlockObj(){
    delete BlockObj::merkletree;
    //delete BlockObj::merkleIndex;
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

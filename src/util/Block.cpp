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
    this->currentHash=jsonObject.value("hashKey").toString().toStdString();
    this->lastHash=jsonObject.value("lastHash").toString().toStdString();
    this->createTime=jsonObject.value("createTime").toString().toLongLong();
    this->merkleRoot=jsonObject.value("merkleRoot").toString().toStdString();
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
QList<int> BlockObj::searchKeyword(const vector<string> &keywords_list){
    searcher* searcherHandle= new SearcherImpl();
    searcherHandle->Enter_Keywords(keywords_list);
    search_result& resultHandle=searcherHandle->Keyword_Search(BlockObj::article);
    resultHandle.Destruction();
}

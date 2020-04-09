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
BlockObj::BlockObj(){
    merkletree=new MerkleTree(article);
    if(merkleRoot!=merkletree->merkleRoot())
        isLegal=false;
    else
        isLegal=true;
}
QList<int> BlockObj::searchKeyword(const vector<string> &keywords_list){
    SearcherImpl searcherHandle=SearcherImpl();
    searcherHandle.Enter_Keywords(keywords_list);
    search_result* resultHandle=searcherHandle.Keyword_Search(BlockObj::blockArticle());
    //
}

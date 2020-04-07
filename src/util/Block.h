#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <ctime>
#include <QObject>
#include <QList>
#include <string>
#include "MerkleTree.h"
using namespace std;
class BlockObj: public QObject
{
    Q_OBJECT
public:
    BlockObj(int hashKey);//由数据库中的key值连接数据库可得对象，由于我没有权限知道数据库，所以该函数我不会实现
    //Block(xxx);//参数未填，但并不为空，该函数是请求其他节点的信息，由网络信息的结构来构造，由于不知道网络框架暂时不实现
    bool store();//完成block的数据库存储，若数据库中已存在hashkey的，这返回false，并不载入数据库，若之前没有，则调用此函数载入
    string blockArticle();//返回文章的string型，供Keyword_Search（）使用searcher.h中定义
    string blockHead();//返回块头的string型,供取hash
    QList<int> modifyCheck();//会调用this.merkletree的函数，也是返回QList<int> int为修改过的段，为空则没有错
    ~BlockObj();


    //head部分
    int lastHash;//上一块的哈希
    time_t createTime;//出块时间
    short paragraphNum;//文章段落数
    int merkleRoot;
    MerkleTree* merkletree;//吕民轩请注意这个结构,构造函数中会实例化  merkletree=new MerkleTree（this）;   应该有 QList<bool>

    //body部分
    QList<string> article;//文章按段分块
    string* merkleIndex;//索引哈希指针数组，吕民轩请注意，大小根据paragraphNum及你所定义的结构有关，比如老师的那个pdf的结构，假如4段，则size为6.
    //我不知道的new多大，你写完结构我才知道，你merkle tree 的构造函数为block指针（merkleRoot，article，merkleIndex）
};
#endif // BLOCKCHAIN_H

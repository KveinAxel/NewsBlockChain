#ifndef BLOCK_H
#define BLOCK_H
#include <ctime>
#include <QObject>
#include <QList>
#include <string>
#include "MerkleTree.h"
#include <QDebug>
#include <QDateTime>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include "../Searcher/SearcherImpl.h"
#include "../Searcher/Search_Result_impl.h"
#include "search.h"
#include "Hash.h"
#include "huffman.h"
//#include "BlockChain.h"
using namespace std;
class BlockObj: public QObject
{
    Q_OBJECT
public:
    BlockObj(string hashKey);//由数据库中的key值连接数据库可得对象，由于我没有权限知道数据库，所以该函数我不会实现
    BlockObj(QJsonObject&);//该函数是请求其他节点的信息，由网络信息的结构来构造，由于不知道网络框架暂时不实现
    BlockObj(const QList<std::string> &article,string lastHashKey);//用文章造块
    bool store();//完成block的数据库存储，若数据库中已存在hashkey的，这返回false，并不载入数据库，若之前没有，则调用此函数载入
    //存储的块体是压缩码，先把blockArticle和blockHead合并成json，转utf-8，得到QByteArray,在调data（）函数，huffman.h。最后压缩后变回QByteArray，然后存在本地
    string blockArticleHash();//返回块文章的string的hash
    string blockHeadHash();//返回块头的string的hash
    QList<int> modifyCheck(const QList<std::string> article);//会调用this.merkletree的函数，也是返回QList<int> int为修改过的段，为空则没有错,这个article是外部的，待检测的,还有这是之前是我突然改了接口，传达了错误的信息，所以我会帮改一下代码
    int searchKeyword(const vector<string>&keywords_list);//放回关键词在文章中出现的次数的list
    ~BlockObj();
    QJsonObject serializeToJsonForStore();//把自身序列化，好储存到数据库
    /*QJsonObject有
     * :hashKey-QString//这个没有了
     * :article_1-QString
     * :***
     * :article_paragragh-QString
     * //文章按段落分开序列化
     * merkleRoot
     * createTime
     * lastHash
    */
    //head部分
    bool isLegal;//因为区块链理论上是只保证验证块体的某一区段“有可能"有错误，不能精确查到某段是错的,所以，在做merkle检测的时候我们老师的意思是默认区块链里的是好的，然后拿一篇文章来，通过merkle树快速验错，而不用和区块里原文一个一个字符比
    //为了保证区块里的原文是合法的（因为merkle根一定是合法），在构造block时就会set isLegal的值，如果从网络上传来的block的article对不上merkle根，则不合法，也没有资格做merkletree的检测-modifyCheck()和储存在本地的数据库-store(），
    //bool isHead;//如果该区块在本地只有头，则为真，否者为假，算了不搞那么复杂了，我tm都不知道自己再写什么，我连框架都不知道
    string lastHash;//上一块的哈希
    string currentHash;//本块的hash
    //time_t createTime;//出块时间
    QDateTime  createTime;
    //short paragraphNum;//文章段落数
    string merkleRoot;
    MerkleTree* merkletree;//吕民轩请注意这个结构,构造函数中会实例化  merkletree=new MerkleTree（this）;   应该有 QList<bool>

    //body部分
    QList<string> article;//文章按段分块
    //string* merkleIndex;
    //我的错误，我的block是不可见merkleIndex的，但是我很草率的写了接口，打乱了你的思维，这应该是你merkletree里的指针，但是你是用TreeNode实现的，也不需要merkleIndex，也不是我设想的节约空间的数组树
};
#endif // BLOCK_H

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "Block.h"
#include <QHash>
#include <QJsonObject>
/*QJsonObject有
 * ：hashkey-string
 * ：blockArticle-QByteArray(string转utf-8)
 * :blockHead-QByteArray(string转utf-8)
*/
//我是真的不知道框架，以及我现在写的节点面向的对象是什么，所有可能会有很多莫名其妙的地方
class BlockChain{
public:
    QHash<string,BlockObj*> blockChainHash;//使用hash来实现链
    string currentHashKey;//该节点认可的最新区块的hash，最好要再磁盘上实时更新，万一没电啥的


    bool updateBlock(QJsonObject request);//从网络中请求的东西或其他节点推送的东西，转化本地的块，如果合法，在内存中不释放它生成的blockObj，并储存到数据库
    //从实际上说，是BLockObj的blockArticle()，和blockHead()返回的string的结合体，如何request的块的lastHash为currentHashKey，还要更新currentHashKey;
    QJsonObject responseBlock(string keyOfResponse,int flag);//返回请求的区块，如果blockChainHash内存中没有，则数据库中调用block先到内存，再
    //响应，如果本地没有该keyOfResponse对应的块，则返回空，并bug或提示,如果flag==1，则回应整个区块，如果为0，则返回的QJsonObject没有blockArticle
    BlockChain(string currentHashKey,int size=-1);//从本地数据库中加载区块链，初始化,size为选择初始化加载的最新几个区块，如果-1就是把当前数据库所有的块加载
    QList<BlockObj*> searchKeywordLocal(const vector<string>&keywords_list);//返回检索到的文章，这个是本地的函数，不返回json格式
    QList<int>  modifyCheckLocal(const QList<std::string> article,string keyOfResponse);//要选定区块的才能检测，这个函数就离谱，这老师脑子有坑，不懂区块链就别乱定规则,还定什么一个区块一篇文章，我tm真的服了
    QJsonObject createBlockLocal(const QList<std::string> article);//本地拿到文章产生块，返回块的json信息，发送到其他本节点可见的节点，按理说能够调用这个函数只应该是一个节点，否者会引发分布式系统的不一致性，但是框架能制定有效的应用层协议避免不一致性也行
    QJsonObject createBlock(const QByteArray article);//提供这个函数功能，从网络request中拿到文章，远程造块，返回信息同上
};

#endif // BLOCKCHAIN_H

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "Block.h"
#include <QHash>
class BlockChain{
public:
    QHash<string,BlockObj*> blockChainHash;//使用hash来实现链
    string currentHashKey;//该节点认可的最新区块的hash，最好要再磁盘上实时更新，万一没电啥的
    bool updateBlock(string request);//从网络中请求的东西或其他节点推送的东西，转化本地的块，如果合法，在内存中不释放它生成的blockObj，并储存到数据库
    //从实际上说，是BLockObj的blockArticle()，和blockHead()返回的string的结合体，如何request的块的lastHash为currentHashKey，还要更新currentHashKey;
    void requestBlock(string HashKey);//请求hash块
    string responseBlock(string keyOfResponse);//返回请求的区块，如果blockChainHash内存中没有，则数据库中调用block先到内存，再
    //响应，如果本地没有该keyOfResponse对应的块，则返回空，并bug或提示
    BlockChain(string currentHashKey,int size=-1);//从本地数据库中加载区块链，初始化,size为选择初始化加载的最新几个区块，如果-1就是把当前数据库所有的块加载




    //这只是一部分对外通讯的接口，还有检测，文章，等接口，先这么多吧，压缩也没用上，blockObj那还得改
};

#endif // BLOCKCHAIN_H

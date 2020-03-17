#ifndef CURRENTBLOCKROUTER_H
#define CURRENTBLOCKROUTER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

/**
 * 对guest请求进行分发
 */
class CurrentBlockRouter : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(CurrentBlockRouter)

public:

    /**
      构造器
      @param parent 父对象
    */
    CurrentBlockRouter(QObject *parent = nullptr);

    /**
      析构器
    */
    ~CurrentBlockRouter();

    /**
      按路径分发
      @param request 请求信息
      @param response 待构造的返回信息
    */
    void service(HttpRequest &request, HttpResponse &response);

};

#endif // CURRENTBLOCKROUTER_H

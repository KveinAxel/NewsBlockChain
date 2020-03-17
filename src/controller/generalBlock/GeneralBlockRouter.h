#ifndef GENERALBLOCKROUTER_H
#define GENERALBLOCKROUTER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

/**
 * 对guest请求进行分发
 */
class GeneralBlockRouter : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(GeneralBlockRouter)

public:

    /**
      构造器
      @param parent 父对象
    */
    GeneralBlockRouter(QObject *parent = nullptr);

    /**
      析构器
    */
    ~GeneralBlockRouter();

    /**
      按路径分发
      @param request 请求信息
      @param response 待构造的返回信息
    */
    void service(HttpRequest &request, HttpResponse &response);

};

#endif // GENERALBLOCKROUTER_H

/**
  @file
  @author Stefan Frings
*/

#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"

using namespace stefanfrings;

/**
 * 对HTTP请求按照Path进行分发
 */
class Router : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(Router)

public:

    /**
      构造器
      @param parent 父对象
    */
    Router(QObject *parent = nullptr);

    /**
      析构器
    */
    ~Router();

    /**
      按路径分发
      @param request 请求信息
      @param response 待构造的返回信息
    */
    void service(HttpRequest &request, HttpResponse &response);

};

#endif // REQUESTMAPPER_H

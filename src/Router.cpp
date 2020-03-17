/**
  @file
  @author Kevin Axel
*/

#include <QCoreApplication>
#include "Global.h"
#include "Router.h"
#include "filelogger.h"
#include "staticfilecontroller.h"

Router::Router(QObject *parent) : HttpRequestHandler(parent) {
    qDebug("Router: created");
}


Router::~Router() {
    qDebug("Router: deleted");
}


void Router::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path = request.getPath();
    qDebug("Router: path=%s", path.data());

    // 对请求进行匹配以选择控制器或相关Router

    if (path.startsWith("")) {
//        OauthRouter().service(request, response);
    }

        // 其余路径通过静态文件控制器进行处理
    else {
        staticFileController->service(request, response);
    }

    qDebug("Router: end request");

    // 清空logger
    if (logger) {
        logger->clear();
    }
}

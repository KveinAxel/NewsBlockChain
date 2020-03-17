#include <QCoreApplication>
#include "CurrentBlockRouter.h"
#include "filelogger.h"
#include <src/Global.h>
#include "CurrentCompressInfoController.h"
#include "CurrentConfirmController.h"
#include "CurrentInfoController.h"

CurrentBlockRouter::CurrentBlockRouter(QObject *parent) : HttpRequestHandler(parent) {
    qDebug("GuestRouter: created");
}


CurrentBlockRouter::~CurrentBlockRouter() {
    qDebug("GuestRouter: deleted");
}


void CurrentBlockRouter::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path = request.getPath();
    qDebug("GuestRouter: path=%s", path.data());

    // 对请求进行匹配以选择控制器或相关Router

    if (path == "/currentBlock/confirm") {
        CurrentConfirmController().service(request, response);
    } else if (path == "/currentBlock/compressInfo") {
        CurrentCompressInfoController().service(request, response);
    } else if (path == "/currentBlock/info") {
        CurrentInfoController().service(request, response);
    }

    // 其余路径通过静态文件控制器进行处理
    else {
        staticFileController->service(request, response);
    }

    qDebug("GuestRouter: end request");
}

#include <QCoreApplication>
#include "GeneralBlockRouter.h"
#include "filelogger.h"
#include <src/Global.h>
#include "CompressInfoController.h"
#include "ConfirmController.h"
#include "InfoController.h"
#include "ListHashController.h"
#include "SearchBlocksController.h"

GeneralBlockRouter::GeneralBlockRouter(QObject *parent) : HttpRequestHandler(parent) {
    qDebug("GuestRouter: created");
}


GeneralBlockRouter::~GeneralBlockRouter() {
    qDebug("GuestRouter: deleted");
}


void GeneralBlockRouter::service(HttpRequest &request, HttpResponse &response) {
    QByteArray path = request.getPath();
    qDebug("GuestRouter: path=%s", path.data());

    // 对请求进行匹配以选择控制器或相关Router

    if (path == "/generalBlock/confirm") {
        ConfirmController().service(request, response);
    } else if (path == "/generalBlock/compressInfo") {
        CompressInfoController().service(request, response);
    } else if (path == "/generalBlock/info") {
        InfoController().service(request, response);
    } else if (path == "/generalBlock/list") {
        ListHashController().service(request, response);
    } else if (path == "/generalBlock/search") {
        SearchBlocksController().service(request, response);
    }

    // 其余路径通过静态文件控制器进行处理
    else {
        staticFileController->service(request, response);
    }

    qDebug("GuestRouter: end request");
}

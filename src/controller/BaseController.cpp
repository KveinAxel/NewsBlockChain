#include "BaseController.h"
#include <QVariant>
#include <QDateTime>
#include <QThread>
#include <ctime>
#include <QCoreApplication>

BaseController::BaseController() {}

void BaseController::service(HttpRequest &request, HttpResponse &response) {}

void BaseController::result(HttpResponse &response, const QString &status, const QJsonObject &jsonResponse) {
    QJsonObject responseObj = jsonResponse;

    // 增加通用返回
    responseObj["ts"] = time(nullptr);
    responseObj["status"] = status;

    // 构建Json文档
    QJsonDocument jsonDocument;
    jsonDocument.setObject(responseObj);
    QByteArray jsonBytes = jsonDocument.toJson(QJsonDocument::Compact);

    QString strJson(jsonBytes);
    qDebug() << "Response generated: " << strJson;

    // 构建返回
    appendCommonHeader(response);
    response.setHeader("Content-Type", "application/json; charset=UTF-8");
    response.write(jsonBytes, true);
}

void BaseController::result(HttpResponse &response, const QJsonObject &jsonResponse) {
    result(response, "OK", jsonResponse);
}

void BaseController::error(HttpResponse &response, const QString &code, const QString &info) {
    result(response, "ERR",
           {
                   {"code", code},
                   {"info", info}
           });
}

void BaseController::appendCommonHeader(HttpResponse &response) {
    response.setHeader("Server", QCoreApplication::applicationName().toLatin1());
    response.setHeader("Access-Control-Allow-Origin", "*");
}

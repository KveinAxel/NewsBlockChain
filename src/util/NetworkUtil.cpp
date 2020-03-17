#include "NetworkUtil.h"
#include <QDebug>
#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>
#include <QUrlQuery>

NetworkUtil::NetworkUtil()
{

}

QString NetworkUtil::get(const QUrl &url)
{
    QTimer timer;

    // 超时设置
    timer.setInterval(TIMEOUT);
    timer.setSingleShot(true);

    // 初始化网络请求上下文
    QNetworkAccessManager* networkManger = new QNetworkAccessManager;
    QNetworkReply *networkReply = networkManger->get(QNetworkRequest(url));

    // 事件循环
    QEventLoop loop;
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    QObject::connect(networkReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();

    if(!timer.isActive()) {
        // 成功
        timer.stop();
        if(networkReply->error() != QNetworkReply::NoError) {
            qDebug() << "Error fetching url: " << url << ". " << networkReply->errorString();
            return "";
        } else {
            QVariant variant = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            int nStatusCode = variant.toInt();
            qDebug() << "Status Code:" << nStatusCode;
        }
    } else {
        // 超时
        qDebug() << "Fetching url timeout: " << url << ". " << networkReply->errorString();
        QObject::disconnect(networkReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        networkReply->abort();
        networkReply->deleteLater();
    }
    QString responseContent;
    if (networkReply->error() == QNetworkReply::NoError) {
        QByteArray bytes = networkReply->readAll();
        responseContent = QString::fromUtf8(bytes);
    } else {
        qDebug()<< networkReply->errorString();
    }
    networkReply->deleteLater();
    qDebug() << "Successful get: " << url << ", data: " << responseContent;
    return responseContent;
}

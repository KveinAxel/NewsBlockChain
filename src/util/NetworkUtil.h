#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QString>
#include <QUrl>

class NetworkUtil {
    NetworkUtil();

    static const qint32 TIMEOUT = 5000;
public:

    static QString get(const QUrl& url);
};

#endif // NETWORKUTILS_H

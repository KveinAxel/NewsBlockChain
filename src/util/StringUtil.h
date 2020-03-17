#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <QTypeInfo>
#include <QString>

class StringUtil {
public:
    StringUtil();

    static QString getRandomString(qint32 len = 32, QString dict = "abcdefghijklmnopqrstuvwxyz1234567890");
};

#endif // STRINGUTILS_H

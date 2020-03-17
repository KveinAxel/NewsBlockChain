#include "StringUtil.h"

#include <ctime>

StringUtil::StringUtil()
{

}

QString StringUtil::getRandomString(qint32 len, QString dict)
{
    srand(time(nullptr));
    QString ret;
    for (int i = 0; i < len; i++) {
        ret.append(dict[rand() % dict.size()]);
    }
    return ret;
}

#include "FileUtil.h"

#include <QFile>

FileUtil::FileUtil()
{

}

QString FileUtil::readStringFromFile(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    return t;
}


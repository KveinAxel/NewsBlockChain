#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QString>

class FileUtil
{
    FileUtil();
public:
    static QString readStringFromFile(QString filename);
};

#endif // FILEUTIL_H

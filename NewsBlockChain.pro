TARGET = NewsBlockChain
TEMPLATE = app
QT       += core network
CONFIG += console

SOURCES += \
    src/Global.cpp \
    src/Router.cpp \
    src/main.cpp \
    src/controller/BaseController.cpp \
    src/util/Fileutil.cpp \
    src/util/Hash.cpp \
    src/util/Haffman.cpp \
    src/util/MerkleTree.cpp \ \
    src/util/NetworkUtil.cpp \
    src/util/StringUtil.cpp

HEADERS += \
    src/Global.h \
    src/Router.h \
    src/controller/BaseController.h \
    src/util/Fileutil.h \
    src/util/Hash.h \
    src/util/Haffman.h \
    src/util/MerkleTree.h \ \
    src/util/NetworkUtil.h \
    src/util/StringUtil.h


OTHER_FILES += etc/*


include(lib/QtWebApp/logging/logging.pri)
include(lib/QtWebApp/httpserver/httpserver.pri)
include(lib/QtWebApp/templateengine/templateengine.pri)
# Not used: include(lib/QtWebApp/qtservice/qtservice.pri)

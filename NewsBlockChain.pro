TARGET = NewsBlockChain
TEMPLATE = app
QT       += core network
CONFIG += console

SOURCES += \
    src/Global.cpp \
    src/Router.cpp \
    src/controller/currentBlock/CurrentBlockRouter.cpp \
    src/controller/currentBlock/CurrentCompressInfoController.cpp \
    src/controller/currentBlock/CurrentConfirmController.cpp \
    src/controller/currentBlock/CurrentInfoController.cpp \
    src/controller/generalBlock/CompressInfoController.cpp \
    src/controller/generalBlock/ConfirmController.cpp \
    src/controller/generalBlock/GeneralBlockRouter.cpp \
    src/controller/generalBlock/InfoController.cpp \
    src/controller/generalBlock/ListHashController.cpp \
    src/controller/generalBlock/SearchBlocksController.cpp \
    src/main.cpp \
    src/controller/BaseController.cpp \
    src/service/MerkleTreeService.cpp \
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
    src/controller/currentBlock/CurrentBlockRouter.h \
    src/controller/currentBlock/CurrentCompressInfoController.h \
    src/controller/currentBlock/CurrentConfirmController.h \
    src/controller/currentBlock/CurrentInfoController.h \
    src/controller/generalBlock/CompressInfoController.h \
    src/controller/generalBlock/ConfirmController.h \
    src/controller/generalBlock/GeneralBlockRouter.h \
    src/controller/generalBlock/InfoController.h \
    src/controller/generalBlock/ListHashController.h \
    src/controller/generalBlock/SearchBlocksController.h \
    src/service/MerkleTreeService.h \
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

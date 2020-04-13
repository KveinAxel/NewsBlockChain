TARGET = NewsBlockChain
TEMPLATE = app
QT       += core network
CONFIG += console
CONFIG += C++11

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
    src/util/Block.cpp \
    src/util/BlockChain.cpp \
    src/util/Fileutil.cpp \
    src/util/Hash.cpp \
    src/util/MerkleTree.cpp \
    src/util/NetworkUtil.cpp \
    src/util/StringUtil.cpp \
    src/util/huffmantree.cpp \
    src/util/bitio.cpp \
    src/util/huffman.cpp\
    src/Searcher/Search_Result_impl.cpp\
    src/Searcher/SearcherImpl.cpp\
    src/Searcher/TrieDictionary.cpp
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
    src/util/Block.h \
    src/util/BlockChain.h \
    src/util/Fileutil.h \
    src/util/Hash.h \
    src/util/MerkleTree.h \ \
    src/util/NetworkUtil.h \
    src/util/StringUtil.h \
    src/util/huffmantree.h \
    src/util/bitio.h \
    src/util/huffman.h\
    src/util/searcher.h\
    src/Searcher/Search_Result_impl.h\
    src/Searcher/SearcherImpl.h\
    src/Searcher/TrieDictionary.h

OTHER_FILES += etc/*


include(lib/QtWebApp/logging/logging.pri)
include(lib/QtWebApp/httpserver/httpserver.pri)
include(lib/QtWebApp/templateengine/templateengine.pri)
# Not used: include(lib/QtWebApp/qtservice/qtservice.pri)

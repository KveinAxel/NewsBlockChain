#include "Global.h"

httplib::Server *Global::getServer() {
    return this->server;
}

Global::Global() {
    this->server = new httplib::Server();
    this->logger = new LOGGER::CLogger(LOGGER::LogLevel_Info,
                                       LOGGER::CLogger::GetAppAbsolutePath().append("log\\"));

}

Global::~Global() {
    delete this->server;
    delete this->logger;
}

LOGGER::CLogger *Global::getLogger() {
    return this->logger
}

Global *Global::getGlobal() {
    if (nullptr == Global::global) {
        global = new Global();
    } else {
        return global;
    }
}

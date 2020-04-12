#include "Global.h"

Global *Global::global = nullptr;
std::string Global::serverURL = "127.0.0.1";
int Global::serverPort = 8000;

Global::Global() {
    this->logger = new LOGGER::CLogger(LOGGER::LogLevel_Info,
                                       LOGGER::CLogger::GetAppAbsolutePath().append("log\\"));
}

Global::~Global() {
    delete this->logger;
}

LOGGER::CLogger *Global::getLogger() {
    return this->logger;
}

Global *Global::getGlobal() {
    if (nullptr == Global::global) {
        global = new Global();
    }
    return global;
}

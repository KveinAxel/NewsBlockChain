//
// Created by Kevin on 2020/3/30.
//

#include "Global.h"

httplib::Server* Global::getServer() {
    return this->server;
}

Global::Global() {
    this->server = new httplib::Server();
}

Global::~Global() {
    delete this->server;
}

#include "AppendToBlcokChainController.h"

AppendToBlockChain::AppendToBlockChain() = default;

void AppendToBlockChain::service(const httplib::Request &req, httplib::Response &res) {
    BaseController::service(req, res);
}

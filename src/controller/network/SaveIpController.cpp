#include "SaveIpController.h"

void SaveIpController::service(const httplib::Request &req, httplib::Response &res) {
    // 保存请求中的ip，如果本节点不是超级节点则拒绝
}

SaveIpController::SaveIpController() = default;
#include "RegisterSuperNodeController.h"

RegisterSuperNodeController::RegisterSuperNodeController()= default;

void RegisterSuperNodeController::service(const httplib::Request &req, httplib::Response &res) {
    // todo 向DNS发送请求注册为超级节点
    // todo 更新本地配置为超级节点
}

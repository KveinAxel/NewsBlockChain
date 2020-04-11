#include <service/blockchain/BlockChainService.h>
#include <service/connection/Connection.h>
#include "BroadcastBlockByNodeController.h"

BroadcastBlockByNodeController::BroadcastBlockByNodeController() = default;

void BroadcastBlockByNodeController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("block")) {
        auto block = req.get_param_value("block");
        auto serviceRes = BlockChainService::broadcast(block);
        rapidjson::Value resValue;
        resValue.SetObject();
        rapidjson::Document document;
        if (serviceRes.code == 200) {
            resValue.AddMember("message", "接受广播成功", document.GetAllocator());
            Connection::broadcastBlockToDNS(block);
            // todo 可选 处理返回结果
            result(res, resValue);
        } else {
            error(res, "400", serviceRes.msg);
        }
    } else {
        error(res, "400", "请求参数异常");
    }
}

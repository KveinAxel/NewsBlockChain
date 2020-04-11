#include "BroadcastBlockBySuperNodeController.h"
#include <service/blockchain/BlockChainService.h>
#include <Global.h>
#include <service/connection/Connection.h>

void BroadcastBlockBySuperNodeController::service(const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("block")) {
        auto block = req.get_param_value("block");
        auto serviceRes = BlockChainService::broadcast(block);
        rapidjson::Value resValue;
        resValue.SetObject();
        rapidjson::Document document;
        if (serviceRes.code == 200) {
            resValue.AddMember("message", "接受广播成功", document.GetAllocator());
            auto global = Global::getGlobal();
            if (global->isSuperNode) {
                for (auto i: global->ip_tables) {
                    Connection::broadcastBlockToNode(block, i.first, i.second);
                    // todo 可选 处理返回结果
                }
                result(res, resValue);
            } else {
                result(res, resValue);
            }
        } else {
            error(res, "400", serviceRes.msg);
        }
    } else {
        error(res, "400", "请求参数异常");
    }
}

BroadcastBlockBySuperNodeController::BroadcastBlockBySuperNodeController() = default;

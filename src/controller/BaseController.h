#ifndef NEWS_BLOCK_CHAIN_BASE_CONTROLLER_H
#define NEWS_BLOCK_CHAIN_BASE_CONTROLLER_H

#include "httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class BaseController {
public:
    /**
     * @brief 构造器
     */
    BaseController();

     /**
     * @brief 构造返回内容
     * @param request 请求信息
     * @param response 待构造的返回信息
     */
     virtual void service(const httplib::Request &req, httplib::Response &res);

    /**
     * @brief 返回成功调用的Json结果
     * @param response HttpResponse对象
     * @param jsonResponse 待返回的Json数据
     */
    static void result(httplib::Response &res, const rapidjson::Value &value);

    /**
     * @brief 返回失败调用的Json结果
     * @param response HttpResponse对象
     * @param code 响应码
     * @param info 错误信息
     */
    static void error(httplib::Response &res, const std::string &code, const std::string &info);

    /**
     * @brief 返回Json结果
     * @param response HttpResponse对象
     * @param jsonResponse 待返回的Json数据
     */
    static void result(httplib::Response &res, const std::string& status, const rapidjson::Value &value);
};

#endif // NEWS_BLOCK_CHAIN_BASE_CONTROLLER_H

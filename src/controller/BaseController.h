#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include <QJsonObject>
#include <QJsonDocument>

using namespace stefanfrings;

/**
 * @brief 控制器公有基类，提供部分通用方法
 */
class BaseController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(BaseController)

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
    void service(HttpRequest &request, HttpResponse &response);

    /**
     * @brief 返回成功调用的Json结果
     * @param response HttpResponse对象
     * @param jsonResponse 待返回的Json数据
     */
    static void result(HttpResponse &response, const QJsonObject &jsonResponse);

    /**
     * @brief 返回失败调用的Json结果
     * @param response HttpResponse对象
     * @param code 响应码
     * @param info 错误信息
     */
    static void error(HttpResponse &response, const QString &code, const QString &info);

    /**
     * @brief 返回Json结果
     * @param response HttpResponse对象
     * @param jsonResponse 待返回的Json数据
     */
    static void result(HttpResponse &response, const QString &status, const QJsonObject &jsonResponse);

private:

    /**
     * @brief 增加通过Http响应头
     * @param response HttpResponse对象
     */
    static void appendCommonHeader(HttpResponse &response);
};

#endif // BASECONTROLLER_H

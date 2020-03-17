/**
  @file
  @author Stefan Frings
*/

#ifndef GLOBAL_H
#define GLOBAL_H

#include "templatecache.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "filelogger.h"

using namespace stefanfrings;

/**
 * 全局静态对象
 */

/**
 * @brief 模板文件缓存
 */
extern TemplateCache *templateCache;

/**
 * @brief 会话Cookie存储
 */
extern HttpSessionStore *sessionStore;

/**
 * @brief 静态资源控制器
 */
extern StaticFileController *staticFileController;

/**
 * @brief 全局Logger
 */
extern FileLogger *logger;

/**
 * @brief etc的真实路径
 */
extern QString ETC_PATH;

#endif // GLOBAL_H

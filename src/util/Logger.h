#ifndef NEWS_BLOCK_CHAIN_LOGGER_H
#define NEWS_BLOCK_CHAIN_LOGGER_H

#include <Windows.h>
#include <cstdio>
#include <string>

namespace LOGGER {

    // 日志提示信息级别
    static const char *fatalPrefix = "Fatal\t";
    static const char *errorPrefix = "Error\t";
    static const char *warningPrefix = "Warning\t";
    static const char *infoPrefix = "Info\t";

    // 日志提示信息级别级别枚举
    enum EnumLogLevel {
        LogLevel_Stop = 0,      // 什么都不记录
        LogLevel_Fatal,         // 只记录严重错误
        LogLevel_Error,         // 记录严重错误，普通错误
        LogLevel_Warning,       // 记录严重错误，普通错误，警告
        LogLevel_Info           // 记录严重错误，普通错误，警告，提示信息(也就是全部记录)
    };

    class CLogger {
    public:

        /**
         * 构造器
         * @param logLevel    日志记录的等级，可空
         * @param strLogPath   日志目录，可空
         * @param strLogName   日志名称，可空
         */
        explicit CLogger(EnumLogLevel logLevel = EnumLogLevel::LogLevel_Info, std::string logPath = "",
                         std::string logName = "");

        /**
         * 析构函数
         */
        virtual ~CLogger();

        /**
         * 写入严重错误级别信息
         * @param info
         * @param ...
         */
        void traceFatal(const char *info, ...);

        /**
         * 写入错误级别信息
         * @param info
         * @param ...
         */
        void traceError(const char *info, ...);

        /**
         * 写入警告级别信息
         * @param info
         * @param ...
         */
        void traceWarning(const char *info, ...);

        /**
         * 写入提示级别信息
         * @param info
         * @param ...
         */
        void traceInfo(const char *info, ...);

        //
        /**
         * 改变日志写入信息级别
         * @param level
         */
        void changeLogLevel(EnumLogLevel level);

        /**
         * 获取程序运行路径
         * @return
         */
        static std::string GetAppAbsolutePath();

        /**
         * 格式化字符串
         * @param raw
         * @param ...
         * @return
         */
        static std::string FormatString(const char *raw, ...);

    private:

        /**
         * 文件写入操作
         * @param logContent
         */
        void trace(const std::string &logContent);

        /**
         * 获取当前系统时间
         * @return
         */
        static std::string GetTime();

        /**
         * 从文件全路径获取文件名
         * @param path 文件全路径
         * @param splitter 分隔符
         * @return 得到文件名
         */
        static const char *fullPath2FileName(const char *path, char splitter);

    private:

        // 写入日志的文件流
        FILE *fileStream;
        // 写入日志的提示级别
        EnumLogLevel logLevel;
        // 日志的目录
        std::string logPath;
        // 日志的名称
        std::string logName;
        // 日志的文件全路径
        std::string logFullPath;
        // 线程同步的临界区变量
        CRITICAL_SECTION criticalSection{};
    };
}
#endif //NEWS_BLOCK_CHAIN_LOGGER_H
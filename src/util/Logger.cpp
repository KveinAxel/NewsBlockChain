#include "Logger.h"
#include <ctime>
#include <cstdarg>
#include <direct.h>
#include <utility>
#include <vector>
#include <Dbghelp.h>
using std::string;
using std::vector;

namespace LOGGER {
    CLogger::CLogger(EnumLogLevel logLevel, std::string  strLogPath, std::string  strLogName)
            : logLevel(logLevel),
              logPath(std::move(strLogPath)),
              logName(std::move(strLogName)) {

        // 初始化
        fileStream = nullptr;
        if (logPath.empty()) {
            logPath = GetAppAbsolutePath();
        }
        if (logPath[logPath.length() - 1] != '\\') {
            logPath.append("\\");
        }

        // 创建文件夹
        MakeSureDirectoryPathExists(logPath.c_str());

        // 创建日志文件
        if (logName.empty()) {
            time_t currentTime;
            time(&currentTime);
            tm tm1{};
            localtime_s(&tm1, &currentTime);
            // 日志的名称如：201601012130.log
            logName = FormatString("%04d%02d%02d_%02d%02d%02d.log", tm1.tm_year + 1900, tm1.tm_mon + 1,
                                   tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
        }
        logFullPath = logPath.append(logName);

        // 以追加的方式打开文件流
        fopen_s(&fileStream, logFullPath.c_str(), "a+");

        InitializeCriticalSection(&criticalSection);
    }

    // 析构函数
    CLogger::~CLogger() {
        // 释放临界区
        DeleteCriticalSection(&criticalSection);
        // 关闭文件流
        if (fileStream) {
            fclose(fileStream);
            fileStream = nullptr;
        }
    }

    // 从文件全路径获取文件名
    const char *CLogger::fullPath2FileName(const char *path, char splitter) {
        return strrchr(path, splitter) ? strrchr(path, splitter) + 1 : path;
    }

    // 写入严重错误级别信息
    void CLogger::traceFatal(const char *info, ...) {
        
        // 判断当前的写日志级别
        if (EnumLogLevel::LogLevel_Fatal > logLevel)
            return;
        string res;
        if (nullptr != info) {
            va_list marker = nullptr;
            va_start(marker, info); // 初始化变量参数
            size_t length = _vscprintf(info, marker) + 1; // 获取格式化字符串长度
            std::vector<char> buffer(length, '\0'); // 创建用于存储格式化字符串的字符数组
            int canWritten = _vsnprintf_s(&buffer[0], buffer.size(), length, info, marker);
            if (canWritten > 0) {
                res = &buffer[0];
            }
            va_end(marker); //重置变量参数
        }
        if (res.empty()) {
            return;
        }
        string logContent = fatalPrefix;
        logContent.append(GetTime()).append(res);

        //写日志文件
        trace(logContent);
    }

    // 写入错误级别信息
    void CLogger::traceError(const char *info, ...) {
        
        // 判断当前的写日志级别
        if (EnumLogLevel::LogLevel_Error > logLevel)
            return;
        string res;
        if (nullptr != info) {
            va_list marker = nullptr;
            va_start(marker, info); // 初始化变量参数
            size_t length = _vscprintf(info, marker) + 1; // 获取格式化字符串长度
            std::vector<char> buffer(length, '\0'); // 创建用于存储格式化字符串的字符数组
            int canWritten = _vsnprintf_s(&buffer[0], buffer.size(), length, info, marker);
            if (canWritten > 0) {
                res = &buffer[0];
            }
            va_end(marker); // 重置变量参数
        }
        if (res.empty()) {
            return;
        }
        string logContent = errorPrefix;
        logContent.append(GetTime()).append(res);

        // 写日志文件
        trace(logContent);
    }

    // 写入警告级别信息
    void CLogger::traceWarning(const char *info, ...) {
        // 判断当前的写日志级别
        if (EnumLogLevel::LogLevel_Warning > logLevel)
            return;
        string res;
        if (nullptr != info) {
            va_list marker = nullptr;
            va_start(marker, info); // 初始化变量参数
            size_t length = _vscprintf(info, marker) + 1; // 获取格式化字符串长度
            std::vector<char> buffer(length, '\0'); // 创建用于存储格式化字符串的字符数组
            int canWritten = _vsnprintf_s(&buffer[0], buffer.size(), length, info, marker);
            if (canWritten > 0) {
                res = &buffer[0];
            }
            va_end(marker); // 重置变量参数
        }
        if (res.empty()) {
            return;
        }
        string logContent = warningPrefix;
        logContent.append(GetTime()).append(res);

        // 写日志文件
        trace(logContent);
    }


    // 写入提示级别信息
    void CLogger::traceInfo(const char *info, ...) {
        // 判断当前的写日志级别
        if (EnumLogLevel::LogLevel_Info > logLevel)
            return;
        string res;
        if (nullptr != info) {
            va_list marker = nullptr;
            va_start(marker, info); // 初始化变量参数
            size_t length = _vscprintf(info, marker) + 1; // 获取格式化字符串长度
            std::vector<char> buffer(length, '\0'); // 创建用于存储格式化字符串的字符数组
            int canWritten = _vsnprintf_s(&buffer[0], buffer.size(), length, info, marker);
            if (canWritten > 0) {
                res = &buffer[0];
            }
            va_end(marker); // 重置变量参数
        }
        if (res.empty()) {
            return;
        }
        string logContent = infoPrefix;
        logContent.append(GetTime()).append(res);

        // 写日志文件
        trace(logContent);
    }

    // 获取系统当前时间
    string CLogger::GetTime() {
        time_t currentTime;
        time(&currentTime);
        tm tm1{};
        localtime_s(&tm1, &currentTime);
        // 2016-01-01 21:30:00
        string currentTimeStr = FormatString("%04d-%02d-%02d %02d:%02d:%02d ", tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
                                             tm1.tm_hour, tm1.tm_min, tm1.tm_sec);

        return currentTimeStr;
    }

    // 改变日志写入信息级别
    void CLogger::changeLogLevel(EnumLogLevel level) {
        logLevel = level;
    }

    // 文件写入操作
    void CLogger::trace(const string &logContent) {
        try {
            // 进入临界区
            EnterCriticalSection(&criticalSection);
            // 若文件流没有打开，则重新打开
            if (nullptr == fileStream) {
                fopen_s(&fileStream, logFullPath.c_str(), "a+");
                if (!fileStream) {
                    return;
                }
            }
            // 写日志信息到文件流
            fprintf(fileStream, "%s\n", logContent.c_str());
            fflush(fileStream);
            // 离开临界区
            LeaveCriticalSection(&criticalSection);
        }
            // 若发生异常，则先离开临界区，防止死锁
        catch (...) {
            LeaveCriticalSection(&criticalSection);
        }
    }

    string CLogger::GetAppAbsolutePath() {
        char szFilePath[MAX_PATH] = {0}, szDrive[MAX_PATH] = {0}, szDir[MAX_PATH] = {0}, szFileName[MAX_PATH] = {
                0}, szExt[MAX_PATH] = {0};
        GetModuleFileNameA(nullptr, szFilePath, sizeof(szFilePath));
        _splitpath_s(szFilePath, szDrive, szDir, szFileName, szExt);

        string str(szDrive);
        str.append(szDir);
        return str;
    }

    string CLogger::FormatString(const char *raw, ...) {
        string res;
        if (nullptr != raw) {
            va_list marker = nullptr;
            va_start(marker, raw); // 初始化变量参数
            size_t length = _vscprintf(raw, marker) + 1; // 获取格式化字符串长度
            std::vector<char> buffer(length, '\0'); // 创建用于存储格式化字符串的字符数组
            int canWritten = _vsnprintf_s(&buffer[0], buffer.size(), length, raw, marker);
            if (canWritten > 0) {
                res = &buffer[0];
            }
            va_end(marker); // 重置变量参数
        }
        return res;
    }
}
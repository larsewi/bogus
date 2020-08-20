//
// Created by larsewi on 19.08.2020.
//

#ifndef ACRYLIC_LOGGER_H
#define ACRYLIC_LOGGER_H

#include <cstdio>
#include <cstdarg>

#define CNRM            "\x1B[0m"
#define CRED            "\x1B[31m"
#define CYEL            "\x1B[33m"
#define CMAG            "\x1B[35m"
#define CCYN            "\x1B[36m"

#ifndef NDEBUG
#define LOGGER_LOG_ERROR 1
#define LOGGER_LOG_WARNING 1
#define LOGGER_LOG_INFO 1
#define LOGGER_LOG_DEBUG 1
#else
#define LOGGER_LOG_ERROR 1
#define LOGGER_LOG_WARNING 0
#define LOGGER_LOG_INFO 0
#define LOGGER_LOG_DEBUG 0
#endif

#if LOGGER_LOG_ERROR
#define LOG_ERROR(...) log_f(__FILE__, __func__, __LINE__, 0, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOGGER_LOG_WARNING
#define LOG_WARNING(...) log_f(__FILE__, __func__, __LINE__, 1, __VA_ARGS__)
#else
#define LOG_WARNING(...)
#endif

#if LOGGER_LOG_INFO
#define LOG_INFO(...) log_f(__FILE__, __func__, __LINE__, 2, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOGGER_LOG_DEBUG
#define LOG_DEBUG(...) log_f(__FILE__, __func__, __LINE__, 3, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

static void log_f(const char* file, const char* func, int line, int type, const char* fmt, ...) {
    va_list ap;
    const char *logType, *color;
    FILE *filePtr;

    switch (type) {
        case 0:  logType = "ERROR";   color = CRED; filePtr = stderr; break;
        case 1:  logType = "WARNING"; color = CYEL; filePtr = stdout; break;
        case 2:  logType = "INFO";    color = CMAG; filePtr = stdout; break;
        default: logType = "DEBUG";   color = CCYN; filePtr = stdout;
    }

    va_start(ap, fmt);
    fprintf(filePtr, "[%s%s%s][%s:%d in %s]: ", color, logType, CNRM, file, line, func);
    fprintf(filePtr, fmt, ap);
    fprintf(filePtr, "\n");
    va_end(ap);
}

#endif //ACRYLIC_LOGGER_H

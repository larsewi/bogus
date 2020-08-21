//
// Created by larsewi on 19.08.2020.
//

#ifndef ACRYLIC_LOGGER_H
#define ACRYLIC_LOGGER_H

#include <cstdio>
#include <cstdarg>

/**
 * Select desired logger types for debug and release.
 */
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
#define LOG_ERROR(...) logger::log_f(__FILE__, __func__, __LINE__, "ERROR", LOGGER_RED, stderr, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOGGER_LOG_WARNING
#define LOG_WARNING(...) logger::log_f(__FILE__, __func__, __LINE__, "WARNING", LOGGER_YEL, stdout, __VA_ARGS__)
#else
#define LOG_WARNING(...)
#endif

#if LOGGER_LOG_INFO
#define LOG_INFO(...) logger::log_f(__FILE__, __func__, __LINE__, "INFO", LOGGER_MAG, stdout, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOGGER_LOG_DEBUG
#define LOG_DEBUG(...) logger::log_f(__FILE__, __func__, __LINE__, "DEBUG", LOGGER_CYN, stdout, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

/**
 * Logger colors.
 */
#define LOGGER_NRM "\x1B[0m"
#define LOGGER_RED "\x1B[31m"
#define LOGGER_YEL "\x1B[33m"
#define LOGGER_MAG "\x1B[35m"
#define LOGGER_CYN "\x1B[36m"

namespace logger {
    namespace {
        void log_f(
                const char *file, const char *func, int line,
                const char *type, const char *color, FILE *filePtr,
                const char *format, ...
        ) {
            va_list ap;
            va_start(ap, format);

            fprintf(filePtr, "[%s%s%s][%s:%d in %s]: ", color, type, LOGGER_NRM, file, line, func);
            fprintf(filePtr, format, ap);
            fprintf(filePtr, "\n");

            va_end(ap);
        }
    }
}

#endif //ACRYLIC_LOGGER_H

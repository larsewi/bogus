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
#ifndef NDEBUG // DEBUG
#define LOGGER_LOG_ERROR 1
#define LOGGER_LOG_WARNING 1
#define LOGGER_LOG_INFO 1
#define LOGGER_LOG_DEBUG 1
#else // RELEASE
#define LOGGER_LOG_ERROR 1
#define LOGGER_LOG_WARNING 0
#define LOGGER_LOG_INFO 0
#define LOGGER_LOG_DEBUG 0
#endif

#if LOGGER_LOG_ERROR
#define LOG_ERROR(...) \
logger::log_f(__FILE__, __func__, __LINE__, "ERROR", LOGGER_ERROR_COLOR, stderr, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOGGER_LOG_WARNING
#define LOG_WARNING(...) \
logger::log_f(__FILE__, __func__, __LINE__, "WARNING", LOGGER_WARNING_COLOR, stdout, __VA_ARGS__)
#else
#define LOG_WARNING(...)
#endif

#if LOGGER_LOG_INFO
#define LOG_INFO(...) \
logger::log_f(__FILE__, __func__, __LINE__, "INFO", LOGGER_INFO_COLOR, stdout, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOGGER_LOG_DEBUG
#define LOG_DEBUG(...) \
logger::log_f(__FILE__, __func__, __LINE__, "DEBUG", LOGGER_DEBUG_COLOR, stdout, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif



/**
 * Logger colors.
 */
#define LOGGER_CLEAR_COLOR "\x1B[0m"  // Clear color
#define LOGGER_ERROR_COLOR "\x1B[31m" // Error color
#define LOGGER_WARNING_COLOR "\x1B[33m" // Warning color
#define LOGGER_INFO_COLOR "\x1B[35m" // Info color
#define LOGGER_DEBUG_COLOR "\x1B[36m" // Debug color

namespace logger {
        void log_f(
                const char *file, const char *func, int line,
                const char *type, const char *color, FILE *filePtr,
                const char *format, ...
        );
}

#endif //ACRYLIC_LOGGER_H

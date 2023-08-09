//
// Created by larsewi on 31.08.2020.
//

#include "logger.hpp"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

namespace Bogus {

    Logger *Logger::instance = nullptr;

    Logger::Logger() : logLevel(LOG_LEVEL_NONE) {

    }

    Logger::~Logger() = default;

    void Logger::logDebug(const std::string& tag, const char *format, ...) const {
        if (logLevel <= LOG_LEVEL_DEBUG) {
            va_list ap;
            va_start(ap, format);
            fprintf(stdout, "[%sDEBUG%s][%s]: ", ANSI_COLOR_MAGENTA, ANSI_COLOR_RESET, tag.c_str());
            vfprintf(stdout, format, ap);
            fprintf(stdout, "\n");
            va_end(ap);
        }
    }

    void Logger::logInfo(const std::string& tag , const char *format, ...) const {
        if (logLevel <= LOG_LEVEL_INFO) {
            va_list ap;
            va_start(ap, format);
            fprintf(stdout, "[%sINFO%s][%s]: ", ANSI_COLOR_CYAN, ANSI_COLOR_RESET, tag.c_str());
            vfprintf(stdout, format, ap);
            fprintf(stdout, "\n");
            va_end(ap);
        }
    }

    void Logger::logWarning(const std::string& tag, const char *format, ...) const {
        if (logLevel <= LOG_LEVEL_WARNING) {
            va_list ap;
            va_start(ap, format);
            fprintf(stdout, "[%sWARNING%s][%s]: ", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET, tag.c_str());
            vfprintf(stdout, format, ap);
            fprintf(stdout, "\n");
            va_end(ap);
        }
    }

    void Logger::logError(const std::string& tag, const char *format, ...) const {
        if (logLevel <= LOG_LEVEL_ERROR) {
            va_list ap;
            va_start(ap, format);
            fprintf(stderr, "[%sERROR%s][%s]: ", ANSI_COLOR_RED, ANSI_COLOR_RESET, tag.c_str());
            vfprintf(stderr, format, ap);
            fprintf(stderr, "\n");
            va_end(ap);
        }
    }

    Logger *Logger::getInstance() {
        if (instance == nullptr) {
            instance = new Logger;
        }
        return instance;
    }

}


//
// Created by larsewi on 19.08.2020.
//

#ifndef BOGUS_LOGGER_HPP
#define BOGUS_LOGGER_HPP

#include <cstdarg>
#include <cstdio>
#include <string>

namespace Bogus {

class Logger {
public:
  enum LOG_LEVEL {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_NONE = 4
  };

  ~Logger();

  static Logger *getInstance();

  void setLogLevel(int level) { logLevel = level; }

  void logDebug(const std::string &tag, const char *format, ...) const;
  void logInfo(const std::string &tag, const char *format, ...) const;
  void logWarning(const std::string &tag, const char *format, ...) const;
  void logError(const std::string &tag, const char *format, ...) const;

private:
  static Logger *instance;
  int logLevel;

  Logger();
};
} // namespace Bogus

#endif // BOGUS_LOGGER_HPP

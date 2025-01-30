#ifndef LOGGING_H
#define LOGGING_H

#include <format>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <utility>

class Logger {
   public:
    enum LogLevel { DEBUG, INFO, WARNING, ERROR };

    Logger() {};

    template <typename... Args>
    void debug(const std::string_view formatString, Args&&... args) {
        log(Logger::DEBUG, formatString, args...);
    }

    template <typename... Args>
    void info(const std::string_view formatString, Args&&... args) {
        log(Logger::INFO, formatString, args...);
    }

    template <typename... Args>
    void warning(const std::string_view formatString, Args&&... args) {
        log(Logger::WARNING, formatString, args...);
    }

    template <typename... Args>
    void error(const std::string_view formatString, Args&&... args) {
        log(Logger::ERROR, formatString, args...);
    }

   private:
    template <typename... Args>
    void log(Logger::LogLevel level, const std::string_view formatString,
             Args&&... args) {
        std::map<LogLevel, std::string> logLevelMap = {{DEBUG, "DEBUG"},
                                                       {INFO, "INFO"},
                                                       {WARNING, "WARNING"},
                                                       {ERROR, "ERROR"}};

        std::string logLevelTag = logLevelMap[level];

        std::cout << "[" << logLevelTag << "]: "
                  << std::vformat(formatString, std::make_format_args(args...))
                  << std::endl;
    }
};

#endif  // LOGGING_H

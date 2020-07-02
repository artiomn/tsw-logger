/**
  * @file logger.h
  * @author Artiom N.(cl)2020
  * @brief Logger class definition, LogLevel and logging macroses.
  *
  */

#pragma once

#include <memory>

#include <boost/current_function.hpp>

namespace tsw
{

enum class LogLevel
{
    Debug,
    Info,
    Notice,
    Warning,
    Error,
    Critical,
    Panic
};


#define SET_LOG_LEVEL(level) (tsw::Logger::get_logger("default").set_level(level))

#define LOG_TO_LOGGER(logger, level, ...) (logger.log_message(level, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, __VA_ARGS__))
#define LOG_TO(logger_name, level, ...) (LOG_TO_LOGGER(tsw::Logger::get_logger(logger_name), level, __VA_ARGS__))
#define LOG(level, ...) (LOG_TO("default", level, __VA_ARGS__))

#define LOG_MODULE_TO_LOGGER(logger, level, module_name, ...) (logger.log_module_message(level, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, module_name, __VA_ARGS__))
#define LOG_MODULE_TO(logger_name, level, module_name, ...) (LOG_MODULE_TO_LOGGER(tsw::Logger::get_logger(logger_name), level, module_name, __VA_ARGS__))
#define LOG_MODULE(level, module_name, ...) (LOG_MODULE_TO("default", level, module_name, __VA_ARGS__))


class Logger
{
public:
    Logger(const std::string &name);
    Logger(const std::string &name, const std::string &parameters);
    ~Logger();
    friend class std::default_delete<Logger>;

public:
    static Logger &get_logger(const std::string& name);
    static Logger &get_logger(const std::string& name, const std::string &parameters);

public:
    void set_level(LogLevel level) noexcept;
    void set_level(const std::string &module_name, LogLevel level) noexcept;
    LogLevel get_level(const std::string &module_name) const noexcept;
    void log_module_message(const LogLevel level, const char *file_name,
                            const uint32_t line_no, const char *function_name,
                            const char *module_name,
                            const char *format, ...) noexcept;
    void log_message(const LogLevel level, const char *file_name,
                     const uint32_t line_no, const char *function_name,
                     const char *format, ...) noexcept;
    void log_message(const LogLevel level, const char *file_name,
                     const uint32_t line_no, const char *function_name,
                     const std::string &message) noexcept;
    void enable() noexcept;
    void disable() noexcept;
    void flush() noexcept;

private:
   class                        LoggerImpl;
   std::string                  name_;
   bool                         enabled_;
   std::unique_ptr<LoggerImpl>  logger_;
};

}


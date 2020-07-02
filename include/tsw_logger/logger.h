/**
  * @file logger.h
  * @author Artiom N.(cl)2020
  * @brief Logger class definition, LogLevel and logging macroses.
  *
  */

#pragma once

#include <memory>

#include <boost/current_function.hpp>

#include "metadata.h"
#include "types.h"


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


#define LOG_TO_LOGGER(logger, level, ...) (logger.log_message(level, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, __VA_ARGS__))
#define LOG_TO(logger_name, level, ...) (LOG_TO_LOGGER(tsw::Logger::get_logger(logger_name), level, __VA_ARGS__))
#define LOG(level, ...) (LOG_TO("default", level, __VA_ARGS__))

#define LOG_MODULE_TO_LOGGER(logger, level, module_name, ...) (logger.log_module_message(level, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION, module_name, __VA_ARGS__))
#define LOG_MODULE_TO(logger_name, level, module_name, ...) (LOG_MODULE_TO_LOGGER(tsw::Logger::get_logger(logger_name), level, module_name, __VA_ARGS__))
#define LOG_MODULE(level, module_name, ...) (LOG_MODULE_TO("default", level, module_name, __VA_ARGS__))


class Logger
{
public:
    Logger(const String &name);
    Logger(const String &name, const String &parameters);
    ~Logger();
    friend class std::default_delete<Logger>;

public:
    static Logger &get_logger(const String& name);
    static Logger &get_logger(const String& name, const String &parameters);

public:
    void set_level(LogLevel level) noexcept;
    void set_level(const String &module_name, LogLevel level) noexcept;
    LogLevel get_level() const noexcept;
    void log_module_message(const LogLevel level, const char *file_name,
                            const uint32_t line_no, const char *function_name,
                            const char *module_name,
                            const char *format, ...) noexcept;
    void log_message(const LogLevel level, const char *file_name,
                     const uint32_t line_no, const char *function_name,
                     const char *format, ...) noexcept;
    void enable() noexcept;
    void disable() noexcept;
    void flush() noexcept;

private:
   class                        LoggerImpl;
   String                       name_;
   bool                         enabled_;
   std::unique_ptr<LoggerImpl>  logger_;
};

}


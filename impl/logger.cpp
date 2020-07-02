/**
  * @file logger.cpp
  * @author Artiom N.(cl)2017
  * @brief Logging implementation.
  *
  */

#include <map>

#include <P7_Client.h>
#include <P7_Trace.h>

#include <tsw/error.h>
#include <tsw/logger.h>
#include <tsw/types.h>


namespace tsw
{

#ifdef DEBUG
#define LOG_DEFAULT_VERBOSITY TM("0")
#else
#define LOG_DEFAULT_VERBOSITY TM("3")
#endif

namespace impl
{
std::map<String, std::unique_ptr<Logger>> loggers;
}

class Logger::LoggerImpl
{
public:
    LoggerImpl(const String &name,
               const String &parameters =
                    CLIENT_COMMAND_LINE_SINK CLIENT_SINK_CONSOLE
                    TM(" ")
                    CLIENT_COMMAND_LOG_VERBOSITY LOG_DEFAULT_VERBOSITY)
        : logger_client_(P7_Create_Client(parameters.c_str()))
    {
        if (!logger_client_) TSW_THROW(Exception, "P7 client can not be created");
        logger_trace_ = P7_Create_Trace(logger_client_, "Log channel");
        if (!logger_trace_)
        {
            logger_client_->Release();
            TSW_THROW(Exception, "P7 trace cant not be created");
        }

        logger_client_->Share(name.c_str());
    }

    ~LoggerImpl()
    {
        logger_trace_->Release();
        logger_client_->Release();
    }

public:
    inline void set_level(const char *module_name, LogLevel level) noexcept
    {
        logger_trace_->Set_Verbosity(get_module(module_name), translate_log_level(level));
    }

    inline LogLevel get_level() const noexcept
    {
        // todo: implement.
        return LogLevel::Critical;
    }

    inline void log_module_message(const LogLevel level, const char *file_name,
                            const uint32_t line_no, const char *function_name,
                            const char *module_name,
                            const char *format, ...) noexcept
    {
        va_list va;
        logger_trace_->Trace(0,
                             translate_log_level(level),
                             get_module(module_name),
                             line_no,
                             file_name,
                             function_name,
                             format,
                             va
                             );
    }

    inline void flush() noexcept
    {
        logger_client_->Flush();
    }

private:
    inline void *get_module(const char *name) noexcept
    {
        if (!name) return nullptr;

        IP7_Trace::hModule hm;

        logger_trace_->Register_Module(name, &hm);

        return hm;
    }

    inline const eP7Trace_Level translate_log_level(LogLevel level) noexcept
    {
        eP7Trace_Level result = EP7TRACE_LEVEL_CRITICAL;

        switch (level)
        {
            case LogLevel::Debug:
                result = EP7TRACE_LEVEL_DEBUG;
            break;
            case LogLevel::Info:
            case LogLevel::Notice:
                result = EP7TRACE_LEVEL_INFO;
            break;
            case LogLevel::Warning:
                result = EP7TRACE_LEVEL_WARNING;
            break;
            case LogLevel::Error:
                result = EP7TRACE_LEVEL_ERROR;
            break;
            case LogLevel::Critical:
            case LogLevel::Panic:
                result = EP7TRACE_LEVEL_CRITICAL;
            break;
        }

        return result;
    }

private:
    IP7_Client  *logger_client_;
    IP7_Trace   *logger_trace_;
};


Logger::Logger(const String &name) :
    name_(name), enabled_(true), logger_(new LoggerImpl(name))
{

}


Logger::Logger(const String &name, const String &parameters) :
    name_(name), enabled_(true), logger_(new LoggerImpl(name, parameters))
{

}


Logger::~Logger()
{
}


Logger &Logger::get_logger(const String& name)
{
    try
    {
        return *impl::loggers.at(name);
    }
    catch(const std::out_of_range&)
    {
        impl::loggers.emplace(std::make_pair(name, new Logger(name)));
        return *impl::loggers[name];
    }
}


Logger &Logger::get_logger(const String& name, const String &parameters)
{
    try
    {
        return *impl::loggers.at(name);
    }
    catch(const std::out_of_range&)
    {
        impl::loggers.emplace(std::make_pair(name, new Logger(name, parameters)));
        return *impl::loggers[name];
    }
}


void Logger::set_level(LogLevel level) noexcept
{
    logger_->set_level(nullptr, level);
}


void Logger::set_level(const String &module_name, LogLevel level) noexcept
{
    logger_->set_level(module_name.c_str(), level);
}


LogLevel Logger::get_level() const noexcept
{
    return logger_->get_level();
}


void Logger::log_module_message(const LogLevel level, const char *file_name,
                                const uint32_t line_no, const char *function_name,
                                const char *module_name,
                                const char *format, ...) noexcept
{
    if (!enabled_) return;

    va_list vl;
    logger_->log_module_message(level, file_name, line_no, function_name, module_name, format, vl);
}


void Logger::log_message(const LogLevel level, const char *file_name,
                         const uint32_t line_no, const char *function_name,
                         const char *format, ...) noexcept
{
    if (!enabled_) return;

    va_list vl;
    logger_->log_module_message(level, file_name, line_no, function_name, nullptr, format, vl);
}


void Logger::enable() noexcept
{
    enabled_ = true;
}


void Logger::disable() noexcept
{
    enabled_ = false;
}


void Logger::flush() noexcept
{
    logger_->flush();
}

// Наконец он добился своего - был там, куда так стремился.
// На западе над горизонтом, словно сине-зеленая Луна, поднималась Земля в последней четверти.
// Над головой среди черного звездного неба сияло Солнце, а под ним была настоящая Луна.

} // namespace tsw

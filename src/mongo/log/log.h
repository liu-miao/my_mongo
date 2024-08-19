#if defined(MONGO_UTIL_LOG_H_)
// 如果已经定义 这个宏 就报错
#error \ 
    "mongo/log/log.h connot be included multiple times ." \
#else // MONGO_UTIL_LOG_H_
#define MONGO_UTIL_LOG_H_

#include "mongo/base/status.h"
#include "mongo/bson/util/builder.h"
#include "mongo/log/log_component.h"
#include "mongo/log/log_component_settings.h"
#include "mongo/log/log_debug.h"
#include "mongo/log/log_detail.h"
#include "mongo/log/log_domain.h"
#include "mongo/log/log_options.h"
#include "mongo/log/log_severity.h"
#include "mongo/log/redaction.h"
#include "mongo/util/errno_util.h"

// 匿名命名空间  其内的变量和函数只在当前编译单元中可见。这在避免命名冲突和隐藏实现细节方面非常有用
namespace
{
#if defined(MONGO_LOG_DEFAULT_COMPONENT)
    const mongo::log::LogComponent MongoLogDefaultComponent_component =
        MONGO_LOG_DEFAULT_COMPONENT;
#else
#error \
    "mongo/log/log.h requires MONGO_LOGV2_DEFAULT_COMPONENT to be defined. " \
       "Please see https://github.com/mongodb/mongo/blob/master/src/mongo/logv2/README.md "
#endif // MONGO_LOG_DEFAULT_DEFAULT_COMPONENT
} // namespace

namespace mongo
{
    //  定义了一个宏 创建了 mongo::log::LogOptions 类型的 对象
    // 使用 auto options = MAKE_OPTION_ARG2(2, "File not found");
#define MAKE_OPTION_ARG2(ARG0, ARG1) \
    \ 
    ::mongo::log::LogOptions { ARG0, ARG1 }

/**
ID：日志消息的唯一标识符，可能用于区分不同日志条目。
SEVERITY：日志的严重性级别，比如 INFO、WARNING、ERROR 等。这里的严重性通过参数传递。
OPTIONS：日志选项，通常是与日志记录相关的一些配置，比如日志组件、额外选项等。
FMTSTR_MESSAGE：格式化的日志消息字符串，类似 printf 的格式化字符串。
__VA_ARGS__：可变参数，允许传递多个额外的参数，这些参数会替换格式化字符串中的占位符
*/
#define LOG_IMPL(ID, SEVERITY, OPTIONS, FMTSTR_MESSAGE, ...) \
    ::mongo::log::detail::doLog(ID, SEVERITY, OPTIONS, FMT_STRING(FMTSTR_MESSAGE), ##__VA_ARGS__)

#define LOG(ID, FMTSTR_MESSAGE, ...)                              \
    LOG_IMPL(ID,                                                \
    ::mongo::log::LogSeverity::Log(),                           \
    ::mongo::log::LogOptions{MongoLogDefaultComponent_component},\
    FMTSTR_MESSAGE,
    ##__VA_ARGS__)

#define LOG_OPTIONS(ID, OPTIONS, FMTSTR_MESSAGE, ...)          \
    LOG_IMPL(ID,                                               \
             ::mongo::log::LogSeverity::Log(),                 \
             ::mongo::log::LogOptions::ensureValidComponent(   \
                 OPTIONS, MongoLogDefaultComponent_component), \
             FMTSTR_MESSAGE,                                   \
             ##__VA_ARGS__)

#define LOG_INFO(ID, FMTSTR_MESSAGE, ...) \
    LOG_IMPL(ID,                          \
    // 开头的 :: 表示从全局命名空间开始查找 mongo 命名空间
    ::mongo::log::LogSeverity::Info(),                              \
    ::mongo::log::LogOptions{MongoLogDefaultComponent_component},   \
    FMTSTR_MESSAGE,  \ 
     ##__VA_ARGS__)

#define LOG_INFO_OPTIONS(ID, OPTIONS, FMTSTR_MESSAGE, ...)     \
    LOG_IMPL(ID,                                               \
             ::mongo::log::LogSeverity::Info(),                \
             ::mongo::log::LogOptions::ensureValidComponent(   \
                 OPTIONS, MongoLogDefaultComponent_component), \
             FMTSTR_MESSAGE,                                   \
             ##__VA__ARGS__)
#define LOG_WARNING(ID, FMTSTR_MESSAGE, ...)                               \
    LOG_IMPL(ID,                                                           \
             ::mongo::log::LogSeverity::Warning(),                         \
             ::mongo::log::LogOptions{MongoLogDefaultComponent_component}, \
             FMTSTR_MESSAGE,                                               \
             ##__VA_ARGS__)
#define LOG_WARNING_OPTIONS(ID, OPTIONS, FMTSTR_MESSAGE, ...)  \
    LOG_IMPL(ID,                                               \
             ::mongo::log::LogSeverity::Warning(),             \
             ::mongo::log::LogOptions::ensureValidComponent(   \
                 OPTIONS, MongoLogDefaultComponent_component), \
             FMTSTR_MESSAGE,                                   \
             ##__VA_ARGS__)

#define LOG_ERROR(ID, FMTSTR_MESSAGE, ...) \
        LOG_IMPL(ID,                                                               \
                   ::mongo::log::LogSeverity::Error(),                             \
                
                   ::mongo::log::LogOptions{MongoLogDefaultComponent_component}, \ //    构造器
                   FMTSTR_MESSAGE,                                                   \
                   ##__VA_ARGS__)

#define LOG_ERROR_OPTIONS(ID, OPTIONS, FMTSTR_MESSAGE, ...) \
        LOG_IMPL(ID,                                                 \
                   ::mongo::log::LogSeverity::Error(),               \
                   ::mongo::log::LogOptions::ensureValidComponent(   \   //调用方法
                       OPTIONS, MongoLogDefaultComponent_component), \
                   FMTSTR_MESSAGE,                                     \
                   ##__VA_ARGS__)

#define LOG_FATAL(ID, FMTSTR_MESSAGE, ...)                                       \
    do                                                                           \
    {                                                                            \
        LOGV2_IMPL(ID,                                                           \
                   ::mongo::log::LogSeverity::Severe(),                          \
                   ::mongo::log::LogOptions{MongoLogDefaultComponent_component}, \
                   FMTSTR_MESSAGE,                                               \
                   ##__VA_ARGS__);                                               \
        fassertFailed(ID);                                                       \
    } while (false)

#define LOG_FATAL_NOTRACE(ID, FMTSTR_MESSAGE, ...)                           \
    do                                                                       \
    {                                                                        \
        LOG_IMPL(ID,                                                         \
                 ::mongo::log::LogSeverity::Severe(),                        \
                 MAKE_OPTIONS_ARG2(MongoLogDefaultComponent_component,       \
                                   ::mongo::log::FatalMode::kAssertNoTrace), \
                 FMTSTR_MESSAGE,                                             \
                 ##__VA_ARGS__);                                             \
        fassertFailedNoTrace(ID);                                            \
    } while (false)

#define LOG_FATAL_CONTINUE(ID, FMTSTR_MESSAGE, ...)                   \
    LOGV2_IMPL(ID,                                                    \
               ::mongo::log::LogSeverity::Severe(),                   \
               MAKE_OPTIONS_ARG2(MongoLogDefaultComponent_component,  \
                                 ::mongo::log::FatalMode::kContinue), \
               FMTSTR_MESSAGE,                                        \
               ##__VA_ARGS__)

#define LOG_FATAL_OPTIONS(ID, OPTIONS, FMTSTR_MESSAGE, ...)                       \
    do                                                                            \
    {                                                                             \
        auto optionsMacroLocal_ = ::mongo::log::LogOptions::ensureValidComponent( \
            OPTIONS, MongoLogDefaultComponent_component);                         \
        LOG_IMPL(ID, ::mongo::log::LogSeverity::Severe(),                         \
                 optionsMacroLocal_, FMTSTR_MESSAGE, ##__VA_ARGS__);              \
        switch (optionsMacroLocal_.fataModel())                                   \
        {                                                                         \
        case ::mongo::log::FataMode::kAssert:                                     \
            fasserFailed(ID);                                                     \
        case ::mongo::log::FataMode::kAssertNoTrace:                              \
            fasserFailedNoTrace(ID);                                              \
        case ::mongo::log::FataMode::kContinue:                                   \
            break;                                                                \
        };                                                                        \
    } while (false)

#define LOG_DEBUG_OPTIONS(ID, DLEVEL, OPTIONS, FMTSTR_MESSAGE, ...)                          \
    do                                                                                       \
    {                                                                                        \
        auto severityMacroLocal_ = ::mongo::log::LogSeverity::Debug(DLEVEL);                 \
        auto optionsMacroLocal_ = ::mongo::log::LogOptions::ensureValidComponent(            \
            OPTIONS, MongoLogDefaultComponent_component);                                    \
        if (::mongo::log::LogManager::global().getGlobalSettings().shouldLog(                \
                optionsMacroLocal_.component(), severityMacroLocal_))                        \
        {                                                                                    \
            LOG_IMPL(                                                                      \
                ID, severityMacroLocal_, optionsMacroLocal_, FMTSTR_MESSAGE, ##__VA_ARGS__); \
        }                                                                                    \
    } while (false)

#define LOG_DEBUG(ID, DLEVEL, FMTSTR_MESSAGE, ...)                                  \
    LOG_DEBUG_OPTIONS(ID,                                                           \
                      DLEVEL,                                                       \
                      ::mongo::log::LogOptions{MongoLogDefaultComponent_component}, \
                      FMTSTR_MESSAGE,                                               \
                      ##__VA_ARGS__)

inline bool shouldLog(log::LogComponent logComponent, log::LogSeverity severity)
    {
        return log::LogManager::global().getGlobalSettings().shouldLog(logComponent, severity);
    }
} // namespace mongo

#endif // MONGO_UTIL_LOG_H_
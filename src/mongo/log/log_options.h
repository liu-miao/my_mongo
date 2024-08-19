#pragma once

#include "mongo/log/log_component.h"
#include "mongo/log/log_manager.h"
#include "mongo/log/log_tag.h"
#include "mongo/log/log_trucation.h"

namespace mongo::log
{
    class UserAssertAfterLog
    {
    public:
        // 构造器  创建时 会将errorCode 初始化 为constants::kUserAssertWithLogID  -1
        UserAssertAfterLog() : errorCode(constants::kUserAssertWithLogID) {}
        // 带参数的构造函数  explicit 防止在单参数构造函数的隐式转换
        explicit UserAssertAfterLog(ErrorCodes::Error code) : errorCode(code) {}
        // int32_t 各个平台统一
        int32_t errorCode;
    };
    // 枚举类
    enum class FatalMode
    {
        kAssert,
        kAssertNoTrace,
        kContinue
    };

    class LogOptions
    {
    public:
        // 静态方法 调用 LogOptions::ensureValidComponent()
        static LogOptions ensureValidComponent(LogOptions options, LogComponent component)
        {
            if (options._component == LogComponent::kAutomaticDetermination)
            {
                options._component = component;
            }
            return options;
        }
        // 构造器
        LogOptions(LogComponent component) : _component(component) {}
        LogOptions(LogComponent component, FatalMode mode) : _component(component), _fatalMode(mode) {}
        LogOptions(LogDomain *domain) : _domain(domain) {}
        LogOptions(LogTag tags) : _tags(tags) {}
        LogOptions(LogTruncation truncation) : _truncation(truncation) {}
        LogOptions(UserAssertAfterLog uassertAfterLog)
            : _userAssertErrorCode(uassertAfterLog.errorCode) {}
        LogOptions(FataMode mode) : _fatalMode(mode) {}
        LogOptions(FataMode mode, LogTruncation truncation)
            : _truncation(truncation), _fatalMode(mode) {}
        LogOptions(LogTag tags, LogTruncation truncation)
            : _tags(tags), _truncation(truncation) {}

        LogOptions(LogComponent coomponent, LogDomain *domain, LogTag tags)
            : _domain(domain), _tags(tags), _component(component) {}
        LogOptions(Logcomponent component, LogDomain *domain, LogTag tags, LogTruncation truncation, FatalMode fatalMode)
            : _domain(domain), _tags(tags), _component(component), _truncation(truncation), _fatalMode(fatalMode) {}

        LogComponent component() const
        {
            return _component;
        }
        LogDomain &domain() const
        {
            return *_domain;
        }
        LogTag tags() const { return _tags; }
        LogTruncation truncation() const { return _truncation; }
        int32_t uassertErrorCode() const { return _uassertErrorCode; }
        FatalMode fatalMode() const { return _fatalMode; }

    private:
        LogDomain *_domain = &LogMannager::global().getGlobalDomain();
        LogTag _tags;
        LogComponent _component = LogComponent::kAutomaticDetermination;
        LogTruncation _truncation = constants::kDefaultTruncation;
        int32_t _userAssertErrorCode = ErrorCodes::OK;
        FatalMode _fatalMode = FatalMode::kAssert;
    }
}
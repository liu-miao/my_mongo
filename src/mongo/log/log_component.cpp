#include "mongo/platform/basic.h"
#include "mongo/log/log_component.h"
#include "mongo/base/static_assert.h"
#include "mongo/util/assert_util.h"

namespace mongo::log
{
    namespace
    {
        struct
        {
            LogComponent value;
            StringData shortName;
            StringData logName;
            LogComponent parent;
        } constexpr kTable[] = {
#define X_(id, val, shartName, logName, parent) \
    {LogComponent::id, shortName##_sd, logName##_sd, LogComponent::parent},
            MONGO_EXPAND_LOG_COMPONENT(X_)
#undef X_
        };
        constexpr bool correctParentOrder(LogComponent id,LogComponent parent)
        {
            using V = LogComponent::Value;
            switch (V{id})
            {
            case LogComponent::kAutomticDetermination:
            case LogComponent::kDefault:
            case LogComponent::kNumLogComponents:
                /* code */
                break;
            
            default:
                break;
            }
        }
    }
}
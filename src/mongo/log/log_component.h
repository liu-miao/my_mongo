#pragma once
#include <iosfwd>
#include <string>

#include "mongo/base/sting_data.h"

namespace mongo::log
{
    // 一个参数化的宏，它通过传递参数 X 来展开生成特定的代码片段
#define MONGO_EXPAND_LOG_COMPONENT(X)                                                 \
    /*   (id, val                  , shortName               , logName   , parent) */ \
    X(kDefault, = 0, "default", "-", kNumLogComponents)                               \
    X(kAccessControl, , "accessControl", "ACCESS", kDefault)                          \
    X(kCommand, , "command", "COMMAND", kDefault)                                     \
    X(kControl, , "control", "CONTROL", kDefault)                                     \
    X(kExecutor, , "executor", "EXECUTOR", kDefault)                                  \
    X(kGeo, , "geo", "GEO", kDefault)                                                 \
    X(kIndex, , "index", "INDEX", kDefault)                                           \
    X(kNetwork, , "network", "NETWORK", kDefault)                                     \
    X(kProcessHealth, , "processHealth", "HEALTH", kDefault)                          \
    X(kQuery, , "query", "QUERY", kDefault)                                           \
    X(kReplication, , "replication", "REPL", kDefault)                                \
    X(kReplicationElection, , "election", "ELECTION", kReplication)                   \
    X(kReplicationHeartbeats, , "heartbeats", "REPL_HB", kReplication)                \
    X(kReplicationInitialSync, , "initialSync", "INITSYNC", kReplication)             \
    X(kReplicationRollback, , "rollback", "ROLLBACK", kReplication)                   \
    X(kSharding, , "sharding", "SHARDING", kDefault)                                  \
    X(kShardingRangeDeleter, , "rangeDeleter", "RDELETER", kSharding)                 \
    X(kShardingCatalogRefresh, , "shardingCatalogRefresh", "SH_REFR", kSharding)      \
    X(kShardingMigration, , "migration", "MIGRATE", kSharding)                        \
    X(kResharding, , "reshard", "RESHARD", kSharding)                                 \
    X(kShardMigrationPerf, , "migrationPerf", "MIG_PERF", kSharding)                  \
    X(kStorage, , "storage", "STORAGE", kDefault)                                     \
    X(kStorageRecovery, , "recovery", "RECOVERY", kStorage)                           \
    X(kJournal, , "journal", "JOURNAL", kStorage)                                     \
    X(kWrite, , "write", "WRITE", kDefault)                                           \
    X(kFTDC, , "ftdc", "FTDC", kDefault)                                              \
    X(kASIO, , "asio", "ASIO", kNetwork)                                              \
    X(kBridge, , "bridge", "BRIDGE", kNetwork)                                        \
    X(kTracking, , "tracking", "TRACKING", kDefault)                                  \
    X(kTransaction, , "transaction", "TXN", kDefault)                                 \
    X(kTenantMigration, , "tenantMigration", "TENANT_M", kDefault)                    \
    X(kConnectionPool, , "connectionPool", "CONNPOOL", kNetwork)                      \
    X(kTest, , "test", "TEST", kDefault)                                              \
    X(kNumLogComponents, , "total", "TOTAL", kNumLogComponents)

    class LogComponent
    {
    public:
        enum Value
        {
            kAutomaticDetermination = -1,
#define X_(id, val, shartName, logName, parent) id val,
            MONGO_EXPAND_LOG_COMPONENT(X_)
#undef X_
        };
        // 编译时常量  是在 编译时候就计算 不需要在运行时计算求值
        constexpr LogComponent(Value value) : _value(value) {}
        // operator 重载 C++ 
        constexpr operator Value() const { return _value; }

        LogComponent parent() const;
        StringData toStringData() const;
        std::string getShortName() const;
        std::string getDottedName() const;
        StringData getNameForLog() const;

    private:
        Value _value;
    };
    std::ostream& operator<<(std::ostream& os, LogComponent component);
}
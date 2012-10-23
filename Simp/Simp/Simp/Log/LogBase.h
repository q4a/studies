////////////////////////////////////////////////////////////////////////////////
// 文    件 : LogBase.h
// 功能说明 :
//   日志类基类
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

#include <Simp/Pattern/Uncopyable.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// 日志基类模板 LogBase
////////////////////////////////////////////////////////////////////////////////

// 日志级别类型
typedef int LOG_LEVEL;

// 日志级别值
namespace LOG_LVL {
enum LEVEL_VALUE {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_CRITICAL
};
}   // namespace LOG_LVL

template <typename CharT>
class LogBase : private Uncopyable {
public:
    LogBase(LOG_LEVEL baseLevel) : m_BaseLevel(baseLevel), m_LastLevel(baseLevel) {}

    virtual ~LogBase() {}

    virtual void Destroy() {}

    virtual void DoLog(const CharT* fmt, va_list args) = 0;

    void Log(LOG_LEVEL level, const CharT* fmt, ...) {
        if (level < m_BaseLevel)
            return;

        va_list args;
        va_start(args, fmt);
        this->DoLog(fmt, args);
        m_LastLevel = level;
        va_end(args);
    }

    void Log(const CharT* fmt, ...) {
        if (m_LastLevel < m_BaseLevel)
            return;

        va_list args;
        va_start(args, fmt);
        this->DoLog(fmt, args);
        va_end(args);
    }

public:
    void SetBaseLevel(LOG_LEVEL level) {
        m_BaseLevel = level;
    }

    LOG_LEVEL GetBaseLevel() const {
        return m_BaseLevel;
    }

private:
    LOG_LEVEL   m_BaseLevel;    // 基准日志级别
    LOG_LEVEL   m_LastLevel;    // 上一次记录日志的级别
};

SIMP_NS_END

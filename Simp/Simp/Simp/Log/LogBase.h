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
// 日志基类模板 LogBaseT
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
class LogBaseT : private Uncopyable {
public:
    LogBaseT(LOG_LEVEL baseLevel) : m_BaseLevel(baseLevel), m_LastLevel(baseLevel) {}

    virtual ~LogBaseT() {}

    virtual void Destroy() {}

    virtual void DoLog(const CharT* format, va_list args) = 0;

    void Log(LOG_LEVEL level, const CharT* format, ...) {
        if (level < m_BaseLevel)
            return;

        va_list args;
        va_start(args, format);
        this->DoLog(format, args);
        m_LastLevel = level;
        va_end(args);
    }

    void Log(const CharT* format, ...) {
        if (m_LastLevel < m_BaseLevel)
            return;

        va_list args;
        va_start(args, format);
        this->DoLog(format, args);
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

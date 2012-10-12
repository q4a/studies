////////////////////////////////////////////////////////////////////////////////
// 文    件 : LogDbg.h
// 功能说明 :
//   Windows 调试输出的日志设施
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

#include <Simp/Debug/DbgOut.h>
#include <Simp/String/StrHelper.h>
#include <Simp/Log/LogBase.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// Windows 调试输出日志的设施类模板 LogDebugOutT
////////////////////////////////////////////////////////////////////////////////

template <typename CharT>
class LogDebugOutT : public LogBaseT<CharT> {
public:
    explicit
    LogDebugOutT(size_t bufSize, LOG_LEVEL baseLevel) : LogBaseT<CharT>(baseLevel), m_Buf(NULL), m_BufSize(0) {
        SetBufSize(bufSize);
    }

    virtual ~LogDebugOutT() {
        Destroy();
    }

    virtual void Destroy() {
        delete[] m_Buf;
        m_Buf = NULL;
        m_BufSize = 0;
    }

public:
    virtual void DoLog(const CharT* format, va_list args) {
        vsprintf_t(m_Buf, m_BufSize, format, args);
        OutputDebug(m_Buf);
    }

public:
    size_t GetBufSize() const {
        return m_BufSize;
    }

    void SetBufSize(size_t bufSize) {
        CharT* oldBuf = m_Buf;
        m_Buf = new CharT[bufSize];
        delete oldBuf;
        m_BufSize = bufSize;
    }

private:
    size_t  m_BufSize;
    CharT*  m_Buf;
};

////////////////////////////////////////////////////////////////////////////////
// LogDebugOutT 的单件对象创建函数
////////////////////////////////////////////////////////////////////////////////

template <typename CharT>
inline
LogBaseT<CharT>* DebugOutLogT(LOG_LEVEL baseLevel, size_t sizeBuf) {
    static LogDebugOutT<CharT> log(sizeBuf, baseLevel);
    return &log;
}

inline
LogBaseT<_TCHAR>* DebugOutLog(LOG_LEVEL baseLevel, size_t sizeBuf) {
    return DebugOutLogT<_TCHAR>(baseLevel, sizeBuf);
}

SIMP_NS_END

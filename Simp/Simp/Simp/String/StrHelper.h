////////////////////////////////////////////////////////////////////////////////
// 文    件 : StrHelper.h
// 功能说明 :
//   字符串常用操作
//
// 版    本 : 1.0
// 作    者 : Breaker Zhao <breaker.zy_AT_gmail>
// 日    期 : 2011-10
// 授权许可 : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Simp/Depends.h>
#include <Simp/Defs.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// 类型定义
////////////////////////////////////////////////////////////////////////////////

typedef std::basic_string<_TCHAR> tstring;

////////////////////////////////////////////////////////////////////////////////
// 字符特征类 CharTraits
////////////////////////////////////////////////////////////////////////////////

template <typename CharT>
struct CharTraits {
    typedef CharT   CharType;
    typedef int     IntType;
    static const IntType XEOF = -1;
};

// char 特化
template <>
struct CharTraits<char> {
    typedef char    CharType;
    typedef int     IntType;
    static const IntType XEOF = EOF;
};

// wchar_t 特化
template <>
struct CharTraits<wchar_t> {
    typedef wchar_t CharType;
    typedef wint_t  IntType;
    static const IntType XEOF = WEOF;
};

////////////////////////////////////////////////////////////////////////////////
// char/wchar_t 的字符/字符串字面量的统一表示
// 用途:
//   在接受 CharT 的模板中保持字符/字符串字面量的写法统一
////////////////////////////////////////////////////////////////////////////////

// 无一般化定义
template <typename CharT>
const CharT* Str(const char* str, const wchar_t* wstr);
template <typename CharT>
const CharT Char(const char ch, const wchar_t wch);

// char 特化
template <>
inline const char* Str(const char* str, const wchar_t* wstr) {
    return str;
}
template <>
inline const char Char(const char ch, const wchar_t wch) {
    return ch;
}

// wchar_t 特化
template <>
inline const wchar_t* Str(const char* str, const wchar_t* wstr) {
    return wstr;
}
template <>
inline const wchar_t Char(const char ch, const wchar_t wch) {
    return wch;
}

#define SIMP_STR(type, str) Simp::Str<type>(str, SIMP_WIDE(str))
#define SIMP_CHAR(type, ch) Simp::Char<type>(ch, SIMP_WIDE(ch))

////////////////////////////////////////////////////////////////////////////////
// 字符串格式化函数
////////////////////////////////////////////////////////////////////////////////

// 转接 CRT vsprintf 的函数模板, 无一般化定义
template <typename CharT>
int vsprintf_t(CharT* buf, size_t charSize, const CharT* fmt, va_list args);

// vsprintf_t 的 char 特化
template <>
inline
int vsprintf_t(char* buf, size_t charSize, const char* fmt, va_list args) {
    return vsprintf_s(buf, charSize, fmt, args);
}

// vsprintf_t 的 wchar_t 特化
template <>
inline
int vsprintf_t(wchar_t* buf, size_t charSize, const wchar_t* fmt, va_list args) {
    return vswprintf_s(buf, charSize, fmt, args);
}

// 格式化构造 string
template <size_t Size, typename CharT>
inline
std::basic_string<CharT> MakeString(const CharT* fmt, ...) {
    CharT buf[Size];
    va_list args;
    va_start(args, fmt);
    vsprintf_t(buf, Size, fmt, args);
    va_end(args);
    return std::basic_string<CharT>(buf);
}

////////////////////////////////////////////////////////////////////////////////
// 用途:
//   利用临时对象的语句结束时销毁机制, 格式化产生临时 C 字符串
// 例子:
//   _putts(StringMaker<BUF_SIZE, _TCHAR>()(_T("%s %d"), _T("foo"), 42));
////////////////////////////////////////////////////////////////////////////////

#define SIMP_MAKESTRA(size, fmt, ...)   Simp::StringMaker<size, char>()(fmt, __VA_ARGS__)
#define SIMP_MAKESTRW(size, fmt, ...)   Simp::StringMaker<size, wchar_t>()(fmt, __VA_ARGS__)
#define SIMP_MAKESTR(size, fmt, ...)    Simp::StringMaker<size, _TCHAR>()(fmt, __VA_ARGS__)

template <size_t Size, typename CharT>
struct StringMaker {
    const _TCHAR* operator()(const CharT* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vsprintf_t(Str, Size, fmt, args);
        va_end(args);
        return Str;
    }

    CharT Str[Size];
};

////////////////////////////////////////////////////////////////////////////////
// CRT errno 错误消息
////////////////////////////////////////////////////////////////////////////////

// 转接 CRT strerror 的函数模板, 无一般化定义
template <typename CharT>
errno_t strerror_t(__out CharT* buf, size_t size, int errnum);

// char 特化
template <>
inline
errno_t strerror_t(__out char* buf, size_t size, int errnum) {
    return strerror_s(buf, size, errnum);
}

// wchar_t 特化
template <>
inline
errno_t strerror_t(__out wchar_t* buf, size_t size, int errnum) {
    return _wcserror_s(buf, size, errnum);
}

////////////////////////////////////////////////////////////////////////////////
// 类模板 CrtStrErr
// 用途:
//   利用临时对象的语句结束时销毁机制, 在获得 CRT errno 错误消息时 (strerror), 不用考虑分配和销毁缓冲区
// 例子:
//   _tprintf(_T("error %d: %s\n"), errno, CrtStrErr<BUF_SIZE, _TCHAR>()(errno));
////////////////////////////////////////////////////////////////////////////////

#define SIMP_CRTSTRERRA(size, errnum)   Simp::CrtStrErr<size, char>()(errnum)
#define SIMP_CRTSTRERRW(size, errnum)   Simp::CrtStrErr<size, wchar_t>()(errnum)
#define SIMP_CRTSTRERR(size, errnum)    Simp::CrtStrErr<size, _TCHAR>()(errnum)

template <size_t Size, typename CharT>
struct CrtStrErr {

    CharT* operator()(int errnum) {
        strerror_t(Msg, Size, errnum);
        return Msg;
    }

    CharT Msg[Size];
};

////////////////////////////////////////////////////////////////////////////////
// 字符串拷贝操作
////////////////////////////////////////////////////////////////////////////////


// 带目标缓冲区大小保护和超长源字符串截断功能
// CRT 的 _tcsncpy_s 仅当 count = _TRUNCATE ((size_t) -1) 时，进行源字符串截断
// 而 count != _TRUNCATE 时，_tcsncpy_s 和 _tcscpy_s 相似，产生 Assert
// 改进的 StrNCpy 中只要源字符串长度 count 超出目标缓冲区 bufSize 的大小就会截断，也可以使用 count 的最大值 _TRUNCATE
// 源字符串 src 的拷贝字符数，由其 \0 或 count 哪个条件先达到决定
// VC 2005 实测效率: StrNCpy 高于 CRT 的 _tcsncpy_s
// 模板参数:
//   AlertTruncated: 为 TRUE 时通过返回值 STRUNCATE 报告源字符截断错误
template <BOOL AlertTruncated, typename CharT>
inline
errno_t StrNCpyImpl(__out CharT* dst, size_t bufSize, const CharT* src, size_t count) {
    if (dst == NULL || bufSize == 0 || src == NULL)
        return EINVAL;

    CharT* p = dst;
    size_t i = 0;
    for (; i < count && i < bufSize - 1 && *src != 0; ++i)
        *p++ = *src++;
    *p = 0;

    // 只检测因为目标缓冲区太小导致的截断，不检测因为源字符串 count 比 \0 先达到引起的截断
    if (AlertTruncated && i < count && *src != 0)
        return STRUNCATE;

    return 0;
}

template <typename CharT>
inline
CharT* StrNCpy(__out CharT* dst, size_t bufSize, const CharT* src, size_t count) {
    if (StrNCpyImpl<FALSE>(dst, bufSize, src, count) != 0)
        return NULL;
    return dst;
}

template <typename CharT>
inline
errno_t StrNCpyAlert(__out CharT* dst, size_t bufSize, const CharT* src, size_t count) {
    return StrNCpyImpl<TRUE>(dst, bufSize, src, count);
}

////////////////////////////////////////////////////////////////////////////////
// 去除字符串两边空白字符
////////////////////////////////////////////////////////////////////////////////

template <BOOL InPlace, BOOL AlertTruncated, typename CharT>
inline
errno_t TrimLeftImpl(const CharT* src, __out CharT* dst, size_t dstSize) {
    if (InPlace)
        _ASSERTE(src == dst && dstSize != 0);

    if (src == NULL || dst == NULL || dstSize == 0)
        return EINVAL;

    while (_istspace(*src))
        src++;

    if (InPlace) {
#pragma warning(push)
#pragma warning(disable: 4996)
        _tcscpy(dst, src);
#pragma warning(pop)
    }
    else
        return StrNCpyImpl<AlertTruncated>(dst, dstSize, src, _TRUNCATE);

    return 0;
}

template <typename CharT>
inline
CharT* TrimLeft(const CharT* src, __out CharT* dst, size_t dstSize) {
    return (TrimLeftImpl<FALSE, FALSE>(src, dst, dstSize) != 0 ? NULL : dst);
}

template <typename CharT>
inline
errno_t TrimLeftAlert(const CharT* src, __out CharT* dst, size_t dstSize) {
    return TrimLeftImpl<FALSE, TRUE>(src, dst, dstSize);
}

template <typename CharT>
inline
CharT* TrimLeft(__inout CharT* src) {
    return (TrimLeftImpl<TRUE, FALSE>(src, src, _TRUNCATE) != 0 ? NULL : src);
}

template <typename CharT>
inline
errno_t TrimLeftAlert(__inout CharT* src) {
    return TrimLeftImpl<TRUE, TRUE>(src, src, _TRUNCATE);
}

// 另一种预先写入的算法：在下面判断 space 字符的 for 循环中，边判断边向目标缓冲区拷贝字符
// 最后将目标的 lastNonSpace 之后位置设为 \0 字符，以截断直到结尾的连续 space 字符序列
// 这种方法的优点是只需一次扫描源字符串（读操作少），但缺点是，在后缀 space 字符很多的情况下：
// 1. 有更多的无效的复制字符操作
//    而以下算法虽然两次扫描源字符串，但只复制必要的字符（写操作少）
// 2. 需要预留足够大的目标缓冲区，以存放预先写入但可能最后用 \0 截断丢弃的 space 字符序列
//    而以下算法只要目标缓冲区能容纳恰好 TrimRight 之后的字符数即可
template <BOOL InPlace, BOOL AlertTruncated, typename CharT>
inline
errno_t TrimRightImpl(const CharT* src, __out CharT* dst, size_t dstSize) {
    if (InPlace)
        _ASSERTE(src == dst && dstSize != 0);

    if (src == NULL || dst == NULL || dstSize == 0)
        return EINVAL;

    // 记录最后一个非 space 字符位置
    const CharT* lastNonSpace = NULL;
    for (const CharT* p = src; *p != 0; p++) {
        if (!_istspace(*p))
            lastNonSpace = p;
    }
    if (lastNonSpace == NULL)
        *dst = 0;
    else {
        _ASSERTE(*lastNonSpace != 0);
        if (InPlace)
            *(const_cast<CharT*>(lastNonSpace) + 1) = 0;
        else
            return StrNCpyImpl<AlertTruncated>(dst, dstSize, src, lastNonSpace - src + 1);
    }

    return 0;
}

template <typename CharT>
inline
CharT* TrimRight(const CharT* src, __out CharT* dst, size_t dstSize) {
    return (TrimRightImpl<FALSE, FALSE>(src, dst, dstSize) != 0 ? NULL : dst);
}

template <typename CharT>
inline
errno_t TrimRightAlert(const CharT* src, __out CharT* dst, size_t dstSize) {
    return TrimRightImpl<FALSE, TRUE>(src, dst, dstSize);
}

template <typename CharT>
inline
CharT* TrimRight(__inout CharT* src) {
    return (TrimRightImpl<TRUE, FALSE>(src, src, _TRUNCATE) != 0 ? NULL : src);
}

template <typename CharT>
inline
errno_t TrimRightAlert(__inout CharT* src) {
    return TrimRightImpl<TRUE, TRUE>(src, src, _TRUNCATE);
}

template <BOOL InPlace, BOOL AlertTruncated, typename CharT>
inline
errno_t TrimImpl(const CharT* src, __out CharT* dst, size_t dstSize) {
    if (InPlace)
        _ASSERTE(src == dst && dstSize != 0);

    if (src == NULL || dst == NULL || dstSize == 0)
        return EINVAL;

    while (_istspace(*src))
        src++;

    if (InPlace && src == dst)
        return TrimRightImpl<TRUE, AlertTruncated>(src, dst, dstSize);
    return TrimRightImpl<FALSE, AlertTruncated>(src, dst, dstSize);
}

template <typename CharT>
inline
CharT* Trim(const CharT* src, __out CharT* dst, size_t dstSize) {
    return (TrimImpl<FALSE, FALSE>(src, dst, dstSize) != 0 ? NULL : dst);
}

template <typename CharT>
inline
errno_t TrimAlert(const CharT* src, __out CharT* dst, size_t dstSize) {
    return TrimImpl<FALSE, TRUE>(src, dst, dstSize);
}

template <typename CharT>
inline
CharT* Trim(__inout CharT* src) {
    return (TrimImpl<TRUE, FALSE>(src, src, _TRUNCATE) != 0 ? NULL : src);
}

template <typename CharT>
inline
errno_t TrimAlert(__inout CharT* src) {
    return TrimImpl<TRUE, TRUE>(src, src, _TRUNCATE);
}

////////////////////////////////////////////////////////////////////////////////
// 转义字符串
////////////////////////////////////////////////////////////////////////////////

// n = 6E, \n = 0A
// t = 74, \t = 09
// v = 76, \v = 0B
// b = 62, \b = 08
// r = 72, \r = 0D
// f = 66, \f = 0C
// a = 61, \a = 07
// \ = 5C, \\ = 5C
// ? = 3F, \? = 3F
// ' = 27, \' = 27
// " = 2

template <typename CharT>
inline
CharT EscCharMap(CharT ch) {
    //  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
    static char charMap[256] = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 1
        0,   0,'\"',   0,   0,   0,   0,'\'',   0,   0,   0,   0,   0,   0,   0,   0,   // 2
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,'\?',   // 3
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 4
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,'\\',   0,   0,   0,   // 5
        0,'\a','\b',   0,   0,   0,'\f',   0,   0,   0,   0,   0,   0,   0,'\n',   0,   // 6
        0,   0,'\r',   0,'\t',   0,'\v',   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
        0
    };
    return (CharT) charMap[(unsigned char) ch];
}

template <typename CharT>
inline
int EscHex(const CharT*& src) {
    _ASSERTE(src != NULL);

    char ch = (char) *(++src);
    int val = 0;
    if (ch >= '0' && ch <= '9')
        val = ch - '0';
    else if (ch >= 'A' && ch <= 'F')
        val = 10 + ch - 'A';
    else if (ch >= 'a' && ch <= 'f')
        val = 10 + ch - 'a';
    else
        return -1;

    ch = (char) *(++src);
    if (ch >= '0' && ch <= '9')
        val = (val << 4) + (ch - '0');
    else if (ch >= 'A' && ch <= 'F')
        val = (val << 4) + (10 + ch - 'A');
    else if (ch >= 'a' && ch <= 'f')
        val = (val << 4) + (10 + ch - 'a');
    else
        --src;
    return val;
}

template <typename CharT>
inline
int EscUCS2(const CharT*& src) {
    _ASSERTE(src != NULL);

    int val = 0;
    for (int i = 0; i < 4; ++i) {
        char ch = (char) *(++src);
        val <<= 4;
        if (ch >= '0' && ch <= '9')
            val += (ch - '0');
        else if (ch >= 'A' && ch <= 'F')
            val += (10 + ch - 'A');
        else if (ch >= 'a' && ch <= 'f')
            val += (10 + ch - 'a');
        else
            return -1;
    }
    return val;
}

// 参数:
//   dstEnd: 目标缓冲区尾哨兵
// 返回值:
//   STRUNCATE: 输出缓冲区大小不够, 被截断
//   EILSEQ: 输入序列有问题, 转义变换失败
// 测试用例:
//   \xa\xdbc => \n \xdb c
//   \xa\xdhc => \n \r h c
//   \u4E2D => 中
template <BOOL InPlace, typename CharT>
inline
errno_t StrEscapeImpl(const CharT* src, __out CharT* dst, CharT* dstEnd) {
    if (InPlace)
        _ASSERTE(src == dst);

    if (src == NULL || dst == NULL || dstEnd == NULL)
        return EINVAL;

    enum ESC_STAT {
        STAT_NORMAL,
        STAT_ESCAPED
    } stat = STAT_NORMAL;

    CharT ch = *src;
    while (ch != 0) {
        switch (stat) {
        case STAT_NORMAL:
            if (ch == _T('\\')) {
                stat = STAT_ESCAPED;
                goto NEXT_CHAR;
            }
            break;

        case STAT_ESCAPED:
            if (ch == _T('x')) {
                int val = EscHex(src);
                if (val == -1)
                    return EILSEQ;
                ch = (CharT) val;
            }
            else if (ch == _T('u')) {
                if (sizeof(CharT) != sizeof(wchar_t))
                    return EILSEQ;
                int val = EscUCS2(src);
                if (val == -1)
                    return EILSEQ;
                ch = (CharT) val;
            }
            else {
                ch = EscCharMap<CharT>(ch);
                if (ch == 0)
                    return EILSEQ;
            }

            stat = STAT_NORMAL;
            break;
        }

        // 写入目标字符串缓冲区
        *dst = ch;
        if (++dst == dstEnd) {
            *(--dst) = 0;
            return STRUNCATE;
        }

NEXT_CHAR:
        // 读入源字符串中下一个字符
        ch = *(++src);
    }

    *dst = 0;
    // 离开时应为 STAT_NORMAL, 否则源序列错误
    if (stat != STAT_NORMAL)
        return EILSEQ;
    return 0;
}

template <typename CharT>
inline
errno_t StrEscape(const CharT* src, __out CharT* dst, size_t dstSize) {
    return StrEscapeImpl<FALSE>(src, dst, dst + dstSize);
}

template <typename CharT>
inline
errno_t StrEscape(__inout CharT* src) {
    return StrEscapeImpl<TRUE>(src, src, (CharT*) -1);
}

////////////////////////////////////////////////////////////////////////////////
// 字符串类模板 StringT
//
// 支持读入引号 "" '' 包围的字符串 (中间含有空格和 \" \' 转义字符)
////////////////////////////////////////////////////////////////////////////////

// CAUTION: 不要对 StringT, basic_string 使用动态绑定, basic_string 并不为动态绑定而设计 (非 virtual dtor)
template <typename CharT>
class StringT : public std::basic_string<CharT> {
public:
    StringT() : std::basic_string<CharT>() {}
    StringT(const CharT* str) : std::basic_string<CharT>(str) {}

    // 从流 is 读取转义字符串
    // 1. 如果流输入以 " 或 ' 打头, 则直到读取下一个成对的 " 或 ' 结束, 不保存起始和结束的 " 或 ', 忽略流中间的转义 \" 和 \'
    // 2. 如果流输入不以 " 或 ' 打头, 则直到读取第一个空白字符结束, 空白字符不保存到 estr 中
    // 3. 当流到达 EOF 状态时, 无论 1 或 2 情况都结束
    // 测试用例:
    //   "ab\" cd" => ab\" cd
    //   "ab'cd" => ab'cd
    std::basic_istream<CharT>& Input(std::basic_istream<CharT>& is) {
        std::basic_streambuf<CharT>* isBuf = is.rdbuf();
        const std::locale loc = is.getloc();

        _ASSERT(isBuf != NULL);
        if (isBuf == NULL) {
            is.setstate(std::ios_base::badbit);
            return is;
        }

        // \", \' 转义字符变换状态
        enum QUOTE_STAT {
            STAT_INIT,      // 初始状态
            STAT_QUOTED,    // 引号包围状态
            STAT_NOQUOTED,  // 非引号包围状态
            STAT_ESCAPED,   // 转义状态. 因为只关心引号包围状态下的 \", \' 转义, 所以实际是 STAT_QUOTED 的子状态, 但因为状态关系简单, 所以没用子状态变换的方法
            STAT_END        // 结束状态
        } stat = STAT_INIT;
        std::basic_streambuf<CharT>::int_type ch;
        std::basic_streambuf<CharT>::int_type closeQuote;

        this->clear();

        // 从流缓冲区读取字符, \" \' 转义
        while (stat != STAT_END) {
            ch = isBuf->sbumpc();

            // 流 buffer 已读完
            if (!std::basic_streambuf<CharT>::traits_type::not_eof(ch)) {
                is.setstate(std::ios_base::eofbit);
                break;
            }

            switch (stat) {
            case STAT_INIT:
                // 遇到 ' 或 ", 变为 引号包围状态
                if (ch == '\"' || ch == '\'') {
                    closeQuote = ch;            // 设置成对的关闭引号字符
                    stat = STAT_QUOTED;
                    continue;
                }
                else
                    stat = STAT_NOQUOTED;  // 变为非引号包围状态

            case STAT_NOQUOTED:
                // 非引号包围状态 不关心 \ 转义
                // 遇到 空白字符 时, 变为结束状态
                if (std::isspace(ch, loc)) {
                    stat = STAT_END;
                    continue;
                }
                break;

            case STAT_QUOTED:
                // 遇到 \ 时, 变为 转义状态
                if (ch == '\\')
                    stat = STAT_ESCAPED;
                // 遇到 成对的关闭引号字符, 变为 结束状态
                else if (ch == closeQuote) {
                    stat = STAT_END;
                    continue;
                }
                break;

            case STAT_ESCAPED:
                // 什么都不做, 变回引号包围状态
                stat = STAT_QUOTED;
                break;
            }

            this->push_back(std::basic_streambuf<CharT>::traits_type::to_char_type(ch));
        }

        is.width(0);
        return is;
    }


    std::basic_ostream<CharT>& Output(std::basic_ostream<CharT>& os) const {
        os << static_cast<std::basic_string<CharT> >(*this);    // NOTE: 需要转型, 否则引起递归
        return os;
    }
};

////////////////////////////////////////////////////////////////////////////////
// String 的 iostream 辅助函数
////////////////////////////////////////////////////////////////////////////////

template <typename CharT>
inline
std::basic_ostream<CharT>&
operator<<(std::basic_ostream<CharT>& os, const StringT<CharT>& str) {
    return str.Output(os);
}

template <typename CharT>
inline
std::basic_istream<CharT>&
operator>>(std::basic_istream<CharT>& is, __out StringT<CharT>& str) {
    return str.Input(is);
}

SIMP_NS_END

////////////////////////////////////////////////////////////////////////////////
// 文    件 : File.h
// 功能说明 :
//   文件操作
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
#include <Simp/String/StrHelper.h>

SIMP_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT fopen 的函数模板
////////////////////////////////////////////////////////////////////////////////

// 无一般化定义
template <typename CharT>
errno_t fopen_t(__out FILE** fs, const CharT* fname, const CharT* mode);

// fopen_t 的 char 特化
template <>
inline
errno_t fopen_t(__out FILE** fs, const char* fname, const char* mode) {
    return fopen_s(fs, fname, mode);
}

// fopen_t 的 wchar_t 特化
template <>
inline
errno_t fopen_t(__out FILE** fs, const wchar_t* fname, const wchar_t* mode) {
    return _wfopen_s(fs, fname, mode);
}

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT freopen 的函数模板
////////////////////////////////////////////////////////////////////////////////

// 无一般化定义
template <typename CharT>
errno_t freopen_t(__out FILE** fs, const CharT* fname, const CharT* mode, FILE* oldfs);

// freopen_t 的 char 特化
template <>
inline
errno_t freopen_t(__out FILE** fs, const char* fname, const char* mode, FILE* oldfs) {
    return freopen_s(fs, fname, mode, oldfs);
}

// freopen_t 的 wchar_t 特化
template <>
inline
errno_t freopen_t(__out FILE** fs, const wchar_t* fname, const wchar_t* mode, FILE* oldfs) {
    return _wfreopen_s(fs, fname, mode, oldfs);
}

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT vfprintf 的函数模板
////////////////////////////////////////////////////////////////////////////////

// 无一般化定义
template <typename CharT>
int vfprintf_t(FILE* fs, const CharT* format, va_list args);
template <typename CharT>
int vfprintf_l_t(FILE* fs, const CharT* format, _locale_t loc, va_list args);

// vfprintf_t 的 char 特化
template <>
inline
int vfprintf_t(FILE* fs, const char* format, va_list args) {
    return vfprintf(fs, format, args);
}
// vfprintf_l_t 的 char 特化
template <>
inline
int vfprintf_l_t(FILE* fs, const char* format, _locale_t loc, va_list args) {
    return _vfprintf_l(fs, format, loc, args);
}

// vfprintf_t 的 wchar_t 特化
template <>
inline
int vfprintf_t(FILE* fs, const wchar_t* format, va_list args) {
    return vfwprintf(fs, format, args);
}
// vfprintf_l_t 的 wchar_t 特化
template <>
inline
int vfprintf_l_t(FILE* fs, const wchar_t* format, _locale_t loc, va_list args) {
    return _vfwprintf_l(fs, format, loc, args);
}

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT fputs, fputc, fgets, fgetc 的函数模板
////////////////////////////////////////////////////////////////////////////////

// 无一般化定义
template <typename CharT>
int fputs_t(const CharT* str, FILE* fs);
template <typename CharT>
typename CharTraits<CharT>::IntType fputc_t(CharT c, FILE* fs);
template <typename CharT>
CharT* fgets_t(__out CharT* buf, int num, FILE* fs);
template <typename CharT>
typename CharTraits<CharT>::IntType fgetc_t(FILE* fs);

// fputs_t 的 char 特化
template <>
inline
int fputs_t(const char* str, FILE* fs) {
    return fputs(str, fs);
}
// fputc_t 的 char 特化
template <>
inline
typename CharTraits<char>::IntType fputc_t(char c, FILE* fs) {
    return fputc(c, fs);
}
// fgets_t 的 char 特化
template <>
inline
char* fgets_t(__out char* buf, int num, FILE* fs) {
    return fgets(buf, num, fs);
}
// fgetc_t 的 char 特化
template <>
inline
typename CharTraits<char>::IntType fgetc_t<char>(FILE* fs) {
    return fgetc(fs);
}

// fputs_t 的 wchar_t 特化
template <>
inline
int fputs_t(const wchar_t* str, FILE* fs) {
    return fputws(str, fs);
}
// fputc_t 的 wchar_t 特化
template <>
inline
typename CharTraits<wchar_t>::IntType fputc_t(wchar_t c, FILE* fs) {
    return fputwc(c, fs);
}
// fgets_t 的 wchar_t 特化
template <>
inline
wchar_t* fgets_t(__out wchar_t* buf, int num, FILE* fs) {
    return fgetws(buf, num, fs);
}
// fgetc_t 的 wchar_t 特化
template <>
inline
typename CharTraits<wchar_t>::IntType fgetc_t<wchar_t>(FILE* fs) {
    return fgetwc(fs);
}

// TODO:
inline
errno_t ReadLine(FILE* stream) {
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 标准文件流 FILE 操作类 StdioFile
////////////////////////////////////////////////////////////////////////////////

// NOTE:
// StdioFile 是 FILE 的浅封装, 转接 FILE 的操作函数, 保持原有的参数和返回值的语义

class StdioFile : private Uncopyable {
public:
    StdioFile() : m_Stream(NULL) {}

    ~StdioFile() {
        Close();
    }

    template <typename CharT>
    errno_t Open(const CharT* fname, const CharT* mode) {
        Close();
        return fopen_t(&m_Stream, fname, mode);
    }

    template <typename CharT>
    errno_t Reopen(FILE* fs, const CharT* fname, const CharT* mode) {
        if (fs == NULL)
            return EINVAL;
        else
            return freopen_t(&m_Stream, fname, mode, fs);
    }

    BOOL Attach(FILE* fs) {
        m_Stream = fs;
        return (fs == NULL);
    }

    int Close() {
        if (m_Stream == NULL)
            return 0;
        int ret = fclose(m_Stream);
        m_Stream = NULL;
        return ret;
    }

    // formatted IO

    template <typename CharT>
    int Printf(const CharT* format, ...) {
        va_list args;
        va_start(args, format);
        int ret = vfprintf_t(m_Stream, format, args);
        va_end(args);
        return ret;
    }

    template <typename CharT>
    int Printf(const CharT* format, _locale_t locale, ...) {
        va_list args;
        va_start(args, format);
        int ret = vfprintf_l_t(m_Stream, format, locale, args);
        va_end(args);
        return ret;
    }

    template <typename CharT>
    int Puts(const CharT* str) {
        return fputs_t(str, m_Stream);
    }

    template <typename CharT>
    typename CharTraits<CharT>::IntType Putc(CharT c) {
        return fputc_t(c, m_Stream);
    }

    template <typename CharT>
    CharT* Gets(__out CharT* buf, int num) {
        return fgets_t(buf, num, m_Stream);
    }

    template <typename CharT>
    typename CharTraits<CharT>::IntType Getc() {
        return fgetc_t<CharT>(m_Stream);
    }

    // binary IO

    size_t Write(const void* buf, size_t size, size_t count) {
        return fwrite(buf, size, count, m_Stream);
    }

    size_t Read(__out void* buf, size_t size, size_t count) {
        return fread(buf, size, count, m_Stream);
    }

    // file op error

    int Error() {
        return ferror(m_Stream);
    }

    int Eof() {
        return feof(m_Stream);
    }

    errno_t ClearErr() {
        return clearerr_s(m_Stream);
    }

    // file pointer op

    int Seek(long offset, int origin) {
        return fseek(m_Stream, offset, origin);
    }

    int Seek64(__int64 offset, int origin) {
        return _fseeki64(m_Stream, offset, origin);
    }

    long Tell() {
        return ftell(m_Stream);
    }

    __int64 Tell64() {
        return _ftelli64(m_Stream);
    }

    void Rewind() {
        rewind(m_Stream);
    }

    // buffer op

    // size 范围: 2 ~ INT_MAX
    int SetBuf(char* buf, int mode, size_t size) {
        return setvbuf(m_Stream, buf, mode, size);
    }

    int Flush() {
        return fflush(m_Stream);
    }

    // file stream & descriptor
    FILE* Stream() {
        return m_Stream;
    }

private:
    FILE* m_Stream;
};

////////////////////////////////////////////////////////////////////////////////
// File Mapping Object 类 FileMapping
////////////////////////////////////////////////////////////////////////////////

class FileMapping : private Uncopyable {
public:
    FileMapping() : m_hFileMapping(NULL) {}

    ~FileMapping() {
        Close();
    }

    DWORD Create(HANDLE hFile, LPSECURITY_ATTRIBUTES attr, DWORD protect, DWORD maxSizeHigh, DWORD maxSizeLow, LPCTSTR name) {
        Close();
        m_hFileMapping = CreateFileMapping(hFile, attr, protect, maxSizeHigh, maxSizeLow, name);
        if (m_hFileMapping != NULL)
            return (GetLastError() == ERROR_ALREADY_EXISTS ? ERROR_ALREADY_EXISTS : 0);
        else
            return GetLastError();
    }

    DWORD Open(DWORD access, BOOL inherited, LPCTSTR name) {
        Close();
        m_hFileMapping = OpenFileMapping(access, inherited, name);
        return (m_hFileMapping == NULL ? GetLastError() : 0);
    }

    void Close() {
        if (m_hFileMapping != NULL) {
            UnmapAllView();
            CloseHandle(m_hFileMapping);
            m_hFileMapping = NULL;
        }
    }

    LPVOID MapView(DWORD access, DWORD offsetHigh, DWORD offsetLow, SIZE_T bytes) {
        LPVOID addr = MapViewOfFile(m_hFileMapping, access, offsetHigh, offsetLow, bytes);
        m_MappedView.insert(addr);
        return addr;
    }

    BOOL UnmapView(LPVOID addr) {
        std::set<LPVOID>::iterator i = m_MappedView.find(addr);
        if (i != m_MappedView.end())
            m_MappedView.erase(i);
        return UnmapViewOfFile(addr);
    }

    void UnmapAllView() {
        std::set<LPVOID>::iterator i = m_MappedView.begin();
        for (; i != m_MappedView.end(); ++i)
            UnmapViewOfFile(*i);
        m_MappedView.clear();
    }

    HANDLE Handle() {
        return m_hFileMapping;
    }

    void Attach(HANDLE handle) {
        Close();
        m_hFileMapping = handle;
    }

    HANDLE Detach() {
        HANDLE handle = m_hFileMapping;
        m_hFileMapping = NULL;
        return handle;
    }

private:
    HANDLE m_hFileMapping;
    std::set<LPVOID> m_MappedView;
};

SIMP_NS_END

////////////////////////////////////////////////////////////////////////////////
// FILE         : stdfile.cpp
// DESCRIPTION  :
//   FILE 的浅封装 class File
//
// AUTHOR       : Breaker Zhao <breaker.zy_AT_gmail>
// DATE         : 2011-10
// LICENSE      : Microsoft Public License <http://www.microsoft.com/en-us/openness/licenses.aspx#MPL>
//
// DISCLAIMER   :
//   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
//   EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
//   WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT fopen 的函数模板, 无一般化定义
////////////////////////////////////////////////////////////////////////////////

template <class CharT>
errno_t fopen_t(__out FILE** fs, const CharT* fname, const CharT* mode);

// fopen_t 的 char 完全特化
template <>
inline
errno_t fopen_t(__out FILE** fs, const char* fname, const char* mode)
{
    return fopen_s(fs, fname, mode);
}

// fopen_t 的 wchar_t 完全特化
template <>
inline
errno_t fopen_t(__out FILE** fs, const wchar_t* fname, const wchar_t* mode)
{
    return _wfopen_s(fs, fname, mode);
}

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT freopen 的函数模板, 无一般化定义
////////////////////////////////////////////////////////////////////////////////

template <class CharT>
errno_t freopen_t(__out FILE** fs, const CharT* fname, const CharT* mode, FILE* oldfs);

// freopen_t 的 char 完全特化
template <>
inline
errno_t freopen_t(__out FILE** fs, const char* fname, const char* mode, FILE* oldfs)
{
    return freopen_s(fs, fname, mode, oldfs);
}

// freopen_t 的 wchar_t 完全特化
template <>
inline
errno_t freopen_t(__out FILE** fs, const wchar_t* fname, const wchar_t* mode, FILE* oldfs)
{
    return _wfreopen_s(fs, fname, mode, oldfs);
}

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT vfprintf 的函数模板, 无一般化定义
////////////////////////////////////////////////////////////////////////////////

template <class CharT>
int vfprintf_t(FILE* fs, const CharT* format, va_list args);
template <class CharT>
int vfprintf_l_t(FILE* fs, const CharT* format, _locale_t loc, va_list args);

// vfprintf_t 的 char 完全特化
template <>
inline
int vfprintf_t(FILE* fs, const char* format, va_list args)
{
    return vfprintf(fs, format, args);
}
// vfprintf_l_t 的 char 完全特化
template <>
inline
int vfprintf_l_t(FILE* fs, const char* format, _locale_t loc, va_list args)
{
    return _vfprintf_l(fs, format, loc, args);
}

// vfprintf_t 的 wchar_t 完全特化
template <>
inline
int vfprintf_t(FILE* fs, const wchar_t* format, va_list args)
{
    return vfwprintf(fs, format, args);
}
// vfprintf_l_t 的 wchar_t 完全特化
template <>
inline
int vfprintf_l_t(FILE* fs, const wchar_t* format, _locale_t loc, va_list args)
{
    return _vfwprintf_l(fs, format, loc, args);
}

////////////////////////////////////////////////////////////////////////////////
// 转接 CRT fputs, fputc, fgets, fgetc 的函数模板, 无一般化定义
////////////////////////////////////////////////////////////////////////////////

template <class CharT>
int fputs_t(const CharT* str, FILE* fs);
template <class CharT>
typename CharTraits<CharT>::IntType fputc_t(CharT c, FILE* fs);
template <class CharT>
CharT* fgets_t(__out CharT* buf, int num, FILE* fs);
template <class CharT>
typename CharTraits<CharT>::IntType fgetc_t(FILE* fs);

// fputs_t 的 char 完全特化
template <>
inline
int fputs_t(const char* str, FILE* fs)
{
    return fputs(str, fs);
}
// fputc_t 的 char 完全特化
template <>
inline
typename CharTraits<char>::IntType fputc_t(char c, FILE* fs)
{
    return fputc(c, fs);
}
// fgets_t 的 char 完全特化
template <>
inline
char* fgets_t(__out char* buf, int num, FILE* fs)
{
    return fgets(buf, num, fs);
}
// fgetc_t 的 char 完全特化
template <>
inline
typename CharTraits<char>::IntType fgetc_t<char>(FILE* fs)
{
    return fgetc(fs);
}

// fputs_t 的 wchar_t 完全特化
template <>
inline
int fputs_t(const wchar_t* str, FILE* fs)
{
    return fputws(str, fs);
}
// fputc_t 的 wchar_t 完全特化
template <>
inline
typename CharTraits<wchar_t>::IntType fputc_t(wchar_t c, FILE* fs)
{
    return fputwc(c, fs);
}
// fgets_t 的 wchar_t 完全特化
template <>
inline
wchar_t* fgets_t(__out wchar_t* buf, int num, FILE* fs)
{
    return fgetws(buf, num, fs);
}
// fgetc_t 的 wchar_t 完全特化
template <>
inline
typename CharTraits<wchar_t>::IntType fgetc_t<wchar_t>(FILE* fs)
{
    return fgetwc(fs);
}

////////////////////////////////////////////////////////////////////////////////
// 标准文件流 FILE 操作 class File
////////////////////////////////////////////////////////////////////////////////

// FILE 的浅封装 class File: 转接 FILE 的操作函数, 保持原有的参数和返回值的语义

class File : private Uncopyable {
public:
    File() : fs_(NULL) {}

    template <class CharT>
    File(const CharT* fname, const CharT* mode) {
        errno_t err = fopen_t(&fs_, fname, mode);
        if (err != 0)
            throw std::exception("fopen failed");
    }

    File(FILE* fs) {
        if (fs == NULL)
            throw std::exception("invalid FILE*");
        fs_ = fs;
    }

    template <class CharT>
    File(FILE* fs, const CharT* fname, const CharT* mode) {
        if (fs == NULL)
            throw std::exception("invalid FILE*");
        errno_t err = freopen_t(&fs_, fname, mode, fs);
        if (err != 0)
            throw std::exception("freopen failed");
    }

    ~File() {
        close();
    }

    template <class CharT>
    errno_t open(const CharT* fname, const CharT* mode) {
        close();
        return fopen_t(&fs_, fname, mode);
    }

    int close() {
        if (fs_ == NULL)
            return 0;
        int ret = fclose(fs_);
        fs_ = NULL;
        return ret;
    }

    // formatted IO

    template <class CharT>
    int printf(const CharT* format, ...) {
        va_list args;
        va_start(args, format);
        int ret = vfprintf_t(fs_, format, args);
        va_end(args);
        return ret;
    }

    template <class CharT>
    int printf(const CharT* format, _locale_t locale, ...) {
        va_list args;
        va_start(args, format);
        int ret = vfprintf_l_t(fs_, format, locale, args);
        va_end(args);
        return ret;
    }

    template <class CharT>
    int puts(const CharT* str) {
        return fputs_t(str, fs_);
    }

    template <class CharT>
    typename CharTraits<CharT>::IntType putc(CharT c) {
        return fputc_t(c, fs_);
    }

    template <class CharT>
    CharT* gets(__out CharT* buf, int num) {
        return fgets_t(buf, num, fs_);
    }

    template <class CharT>
    typename CharTraits<CharT>::IntType getc() {
        return fgetc_t<CharT>(fs_);
    }

    // binary IO

    size_t write(const void* buf, size_t size, size_t count) {
        return fwrite(buf, size, count, fs_);
    }

    size_t read(__out void* buf, size_t size, size_t count) {
        return fread(buf, size, count, fs_);
    }

    // file op error

    int error() {
        return ferror(fs_);
    }

    int eof() {
        return feof(fs_);
    }

    errno_t clearerr() {
        return clearerr_s(fs_);
    }

    // file pointer op

    int seek(long offset, int origin) {
        return fseek(fs_, offset, origin);
    }

    int seek64(__int64 offset, int origin) {
        return _fseeki64(fs_, offset, origin);
    }

    long tell() {
        return ftell(fs_);
    }

    __int64 tell64() {
        return _ftelli64(fs_);
    }

    void rewind() {
        ::rewind(fs_);
    }

    // buffer op

    // size 范围: 2 ~ INT_MAX
    int setbuf(char* buf, int mode, size_t size) {
        return setvbuf(fs_, buf, mode, size);
    }

    int flush() {
        return fflush(fs_);
    }

    // file stream & descriptor
    FILE* get_stream() {
        return fs_;
    }

private:
    FILE*   fs_;
};

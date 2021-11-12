////////////////////////////////////////////////////////////////////////////////
// FILE         : deleter.cpp
// DESCRIPTION  :
//   一组删除器 deleter
//   可配置 Check（检查是已释放）和 Zeroed（释放后置零）
//   释放操作包括 delete, delete[], free, Release (COM), CloseHandle, fclose
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
// 删除器 deleter
////////////////////////////////////////////////////////////////////////////////

// 标准 delete 释放内存
template <BOOL Check = FALSE, BOOL Zeroed = FALSE>
struct StdDel {
    template <class Type>
    void operator()(Type*& ptr) {
        if (!Check || ptr != NULL) {
            ::delete ptr;
            if (Zeroed)
                ptr = NULL;
        }
    }
};

const StdDel<FALSE, FALSE>  STDDEL;
const StdDel<FALSE, TRUE>   STDDEL_Z;
const StdDel<TRUE, FALSE>   STDDEL_C;
const StdDel<TRUE, TRUE>    STDDEL_CZ;

// 标准 delete[] 释放内存
template <BOOL Check = FALSE, BOOL Zeroed = FALSE>
struct StdDelArr {
    template <class Type>
    void operator()(Type*& ptr) {
        if (!Check || ptr != NULL) {
            ::delete[] ptr;
            if (Zeroed)
                ptr = NULL;
        }
    }
};

const StdDelArr<FALSE, FALSE>   STDDELARR;
const StdDelArr<FALSE, TRUE>    STDDELARR_Z;
const StdDelArr<TRUE, FALSE>    STDDELARR_C;
const StdDelArr<TRUE, TRUE>     STDDELARR_CZ;

// 标准 free 释放内存
template <BOOL Check = FALSE, BOOL Zeroed = FALSE>
struct StdFree {
    template <class Type>
    void operator()(Type*& ptr) {
        if (!Check || ptr != NULL) {
            ::free(ptr);
            if (Zeroed)
                ptr = NULL;
        }
    }
};

const StdFree<FALSE, FALSE> STDFREE;
const StdFree<FALSE, TRUE>  STDFREE_Z;
const StdFree<TRUE, FALSE>  STDFREE_C;
const StdFree<TRUE, TRUE>   STDFREE_CZ;

// 释放 COM 对象
template <BOOL Check = FALSE, BOOL Zeroed = FALSE>
struct COMRel {
    template <class Type>
    void operator()(Type*& ptr) {
        if (!Check || ptr != NULL) {
            ptr->Release();
            if (Zeroed)
                ptr = NULL;
        }
    }
};

const COMRel<FALSE, FALSE>  COMREL;
const COMRel<FALSE, TRUE>   COMREL_Z;
const COMRel<TRUE, FALSE>   COMREL_C;
const COMRel<TRUE, TRUE>    COMREL_CZ;

// 关闭 Windows 句柄
template <BOOL Check = FALSE, BOOL Zeroed = FALSE>
struct HClose {
    template <class Type>
    void operator()(Type& h) {
        if (!Check || h != NULL) {
            ::CloseHandle(h);
            if (Zeroed)
                h = NULL;
        }
    }
};

const HClose<FALSE, FALSE>  HCLOSE;
const HClose<FALSE, TRUE>   HCLOSE_Z;
const HClose<TRUE, FALSE>   HCLOSE_C;
const HClose<TRUE, TRUE>    HCLOSE_CZ;

// 关闭 FILE 指针
template <BOOL Check = FALSE, BOOL Zeroed = FALSE>
struct FClose {
    void operator()(FILE*& fp) {
        if (!Check || fp != NULL) {
            ::fclose(fp);
            if (Zeroed)
                fp = NULL;
        }
    }
};

const FClose<FALSE, FALSE>  FCLOSE;
const FClose<FALSE, TRUE>   FCLOSE_Z;
const FClose<TRUE, FALSE>   FCLOSE_C;
const FClose<TRUE, TRUE>    FCLOSE_CZ;

// 删除器函数
// 使用示例: Delete(obj, STDDEL_CZ)
template <class Type, class Del>
inline void Delete(Type& obj, Del del)
{
    del(obj);
}

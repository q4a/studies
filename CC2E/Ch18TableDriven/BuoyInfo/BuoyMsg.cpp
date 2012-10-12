// BuoyMsg.cpp
//

#include "StdAfx.h"
#include "BuoyInfo.h"

#include "BuoyMsg.h"

////////////////////////////////////////////////////////////////////////////////
// 名字空间
////////////////////////////////////////////////////////////////////////////////

using std::vector;
using std::map;

using Simp::tstring;

////////////////////////////////////////////////////////////////////////////////
// Helper
////////////////////////////////////////////////////////////////////////////////

// len 是不包括结尾 \0 的字符数. 本函数不适用于 MBCS
inline void StrToLower(__out _TCHAR* str, size_t len = 0)
{
    _ASSERTE(str != NULL);
    if (len == 0)
        len = _tcslen(str);
    for (size_t i = 0; i < len; ++i)
        str[i] = _totlower(str[i]);
}

// 字符串中的偏移位置
inline _TCHAR* StrOffset(_TCHAR* offset, const _TCHAR* str)
{
    return _tcsstr(offset, str) + _tcslen(str);
}

////////////////////////////////////////////////////////////////////////////////
// struct FieldType
////////////////////////////////////////////////////////////////////////////////

FieldType::NameTypeMapT FieldType::NameTypeMap;
const _TCHAR* FieldType::TypeNameMap[FIELD_MAX];

// 建立类型名和类型标识之间的双向映射
void FieldType::BindTypeName(FIELD_TYPE type, const _TCHAR* name)
{
    TypeNameMap[type] = name;
    NameTypeMap[name] = type;
}

void FieldType::Init()
{
    static BOOL inited = FALSE;
    if (inited)
        return;

    // 类型名全部用小写
    BindTypeName(FIELD_FLOAT, _T("float"));
    BindTypeName(FIELD_INT, _T("int"));
    BindTypeName(FIELD_STRING, _T("string"));
    BindTypeName(FIELD_TIME, _T("time"));
    BindTypeName(FIELD_BOOL, _T("bool"));

    inited = TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// struct Field
////////////////////////////////////////////////////////////////////////////////

Field::ToStrFunc Field::ToStrFuncMap[FIELD_MAX];
Field::MakeFunc Field::MakeFuncMap[FIELD_MAX];

errno_t Field::ToStrByInt(__out Simp::tstring* str, const Variant& val)
{
    _TCHAR buf[64];
    errno_t err = _itot_s(val.m_Int, buf, _countof(buf), 10);
    if (err == 0)
        *str = buf;
    return err;
}

errno_t Field::ToStrByFloat(__out Simp::tstring* str, const Variant& val)
{
    _TCHAR buf[_CVTBUFSIZE];
    errno = 0;
    _stprintf_s(buf, _countof(buf), _T("%.2f"), val.m_Double);
    if (errno == 0)
        *str = buf;
    return errno;
}

errno_t Field::ToStrByString(__out Simp::tstring* str, const Variant& val)
{
    *str = val.m_String;
    return 0;
}

errno_t Field::ToStrByTime(__out Simp::tstring* str, const Variant& val)
{
    tm t;
    errno_t err = localtime_s(&t, &val.m_Time);
    if (err != 0)
        return 0;

    errno = 0;
    _TCHAR buf[64];
    _tcsftime(buf, _countof(buf), _T("%Y-%m-%d %H:%M:%S"), &t);
    if (errno == 0)
        *str = buf;
    return errno;
}

errno_t Field::ToStrByBool(__out Simp::tstring* str, const Variant& val)
{
    *str = val.m_Bool ? _T("True") : _T("False");
    return 0;
}

errno_t Field::ToStr(__out Simp::tstring* str) const
{
    FIELD_TYPE type = m_FieldDesc->m_FieldType;
    if (type == FIELD_ERROR || type >= FIELD_MAX || str == NULL)
        return EINVAL;

    errno_t err = ToStrFuncMap[type](str, m_Val);
    if (err != 0)
        *str = _T("");
    return err;
}

errno_t Field::MakeInt(__out Variant* val, const _TCHAR* str)
{
    errno = 0;
    val->m_Int = _tstoi(str);
    return errno;
}

errno_t Field::MakeFloat(__out Variant* val, const _TCHAR* str)
{
    errno = 0;
    val->m_Double = _tstof(str);
    return errno;
}

errno_t Field::MakeString(__out Variant* val, const _TCHAR* str)
{
    errno = 0;
    val->m_String = _tcsdup(str);
    if (val->m_String == NULL)
        return ENOMEM;
    return errno;
}

errno_t Field::MakeTime(__out Variant* val, const _TCHAR* str)
{
    using namespace boost::gregorian;

    const char* str2;

#ifdef _UNICODE
    char buf[32];
    Simp::WcsToMbs(str, buf, _countof(buf));
    str2 = buf;
#else
    str2 = str;
#endif

    date d;
    try {
        d = from_string(str2);
    }
    catch (std::exception&) {
        return EINVAL;
    }

    time_t t = mktime(&to_tm(d));
    if (t == (time_t) -1)
        return ERANGE;
    val->m_Time = t;
    return errno;
}

errno_t Field::MakeBool(__out Variant* val, const _TCHAR* str)
{
    _TCHAR str2[10];
    _tcscpy_s(str2, _countof(str2), str);
    if (_tcsicmp(str2, _T("False")) == 0 || _tstoi(str2) == 0)
        val->m_Bool = FALSE;
    else if (_tcsicmp(str2, _T("True")) == 0 || _tstoi(str2) == 1)
        val->m_Bool = TRUE;
    else
        return EINVAL;
    return 0;
}

void Field::Init()
{
    static BOOL inited = FALSE;
    if (inited)
        return;

    // 建立类型标识到转换为变体值函数的映射
    MakeFuncMap[FIELD_FLOAT] = MakeFloat;
    MakeFuncMap[FIELD_INT] = MakeInt;
    MakeFuncMap[FIELD_STRING] = MakeString;
    MakeFuncMap[FIELD_TIME] = MakeTime;
    MakeFuncMap[FIELD_BOOL] = MakeBool;

    // 建立类型标识到转换为字符串函数的映射
    ToStrFuncMap[FIELD_FLOAT] = ToStrByFloat;
    ToStrFuncMap[FIELD_INT] = ToStrByInt;
    ToStrFuncMap[FIELD_STRING] = ToStrByString;
    ToStrFuncMap[FIELD_TIME] = ToStrByTime;
    ToStrFuncMap[FIELD_BOOL] = ToStrByBool;

    inited = TRUE;
}

errno_t Field::Assign(const _TCHAR* str)
{
    FIELD_TYPE type = m_FieldDesc->m_FieldType;
    if (type == FIELD_ERROR || type >= FIELD_MAX || str == NULL)
        return EINVAL;

    return MakeFuncMap[type](&m_Val, str);
}

////////////////////////////////////////////////////////////////////////////////
// struct FieldDesc
////////////////////////////////////////////////////////////////////////////////

const _TCHAR* FieldDesc::TypeSep = _T(" :\t";);

////////////////////////////////////////////////////////////////////////////////
// struct MsgDescTbl
////////////////////////////////////////////////////////////////////////////////

// 消息描述表文件格式 (每行): msgType fieldName1:fieldType1 ...
errno_t MsgDescTbl::LoadFile(const _TCHAR* fname)
{
    Simp::StdioFile descFile;
    errno_t ret = descFile.Open(fname, _T("r"));
    if (ret != 0)
        return ret;

    _TCHAR lineBuf[MsgDesc::MAX_MSGDESC];

    while (!descFile.Eof() && !descFile.Error()) {
        descFile.Gets(lineBuf, _countof(lineBuf));

        // 读取消息类型名
        _TCHAR msgType[MsgDesc::MAX_MSGTYPE];
        ret = _stscanf_s(lineBuf, _T("%s"), msgType, _countof(msgType));
        if (ret != 1)
            return ERR_DESC_FORMAT;
        MsgDesc msgDesc(msgType);
        _TCHAR* offset = StrOffset(lineBuf, msgType);

        // 读取字段名和字段类型
        FieldType::Init();
        _TCHAR fieldBuf[FieldDesc::MAX_FIELD + FieldType::MAX_TYPE];
        while (offset < lineBuf + _countof(lineBuf)) {
            ret = _stscanf_s(offset, _T("%s"), fieldBuf, _countof(fieldBuf));
            if (ret != 1)
                break;
            offset = StrOffset(offset, fieldBuf);   // 先计算 offset, 因为后面会改变 fieldBuf

            _TCHAR *fieldName, *fieldType, *nextToken;
            fieldName = _tcstok_s(fieldBuf, FieldDesc::TypeSep, &nextToken);
            if (fieldName == NULL)
                return ERR_DESC_FORMAT;
            fieldType = _tcstok_s(NULL, FieldDesc::TypeSep, &nextToken);
            if (fieldType == NULL)
                return ERR_DESC_FORMAT;

            StrToLower(fieldType);
            FIELD_TYPE type = FieldType::Type(fieldType);
            if (type == FIELD_ERROR)
                return ERR_DESC_FORMAT;

            msgDesc.AddFieldDesc(fieldName, type);
        }

        AddMsgDesc(msgDesc.m_MsgType, msgDesc);
    }

    return 0;
}

void MsgDescTbl::Print(FILE* stream)
{
    MsgDescMapT::const_iterator i = m_MsgDescMap.begin();
    for (; i != m_MsgDescMap.end(); ++i) {
        const tstring& msgType = i->first;
        const MsgDesc& msgDesc = i->second;

        _ASSERTE(msgDesc.m_MsgType == msgType);
        _ftprintf(stream, _T("Message Type: %s\n"), msgType.c_str());

        MsgDesc::FieldDescMapT::const_iterator j = msgDesc.m_FieldDescMap.begin();
        for (; j != msgDesc.m_FieldDescMap.end(); ++j) {
            const FieldDesc& field = j->second;
            _ftprintf(stream, _T("Field: %s, Type: %s\n"), field.m_FieldName.c_str(), FieldType::Name(field.m_FieldType));
        }
        _fputts(_T("\n"), stream);
    }
}

////////////////////////////////////////////////////////////////////////////////
// struct MsgTbl
////////////////////////////////////////////////////////////////////////////////

// 消息表文件格式 (每行): id msgType fieldName1:fieldVal1 ...
errno_t MsgTbl::LoadFile(const _TCHAR* fname)
{
    Simp::StdioFile msgFile;
    errno_t ret = msgFile.Open(fname, _T("r"));
    if (ret != 0)
        return ret;

    _TCHAR lineBuf[Msg::MAX_MSG];

    while (!msgFile.Eof() && !msgFile.Error()) {
        msgFile.Gets(lineBuf, _countof(lineBuf));

        // 读取浮标 id
        _TCHAR id[Msg::MAX_ID];
        ret = _stscanf_s(lineBuf, _T("%s"), id, _countof(id));
        if (ret != 1)
            return ERR_MSG_FORMAT;
        _TCHAR* offset = StrOffset(lineBuf, id);

        // 读取消息类型名
        _TCHAR msgType[MsgDesc::MAX_MSGTYPE];
        ret = _stscanf_s(offset, _T("%s"), msgType, _countof(msgType));
        if (ret != 1)
            return ERR_MSG_FORMAT;
        offset = StrOffset(offset, msgType);

        // 用消息类型名在消息描述表中查询
        MsgDesc& msgDesc = m_MsgDescTbl->m_MsgDescMap[msgType];
        if (msgDesc.IsEmpty())
            return ERR_MSG_FORMAT;
        Msg msg(id, &msgDesc);

        // 读取字段名和字段值
        Field::Init();
        _TCHAR fieldBuf[FieldDesc::MAX_FIELD + FieldType::MAX_TYPE];
        while (offset < lineBuf + _countof(lineBuf)) {
            ret = _stscanf_s(offset, _T("%s"), fieldBuf, _countof(fieldBuf));
            if (ret != 1)
                break;
            offset = StrOffset(offset, fieldBuf);

            _TCHAR *fieldName, *fieldValue, *nextToken;

            // NOTE: 尚不考虑重复字段和缺少字段问题. 重复字段会用最后一个
            // 读取字段名
            fieldName = _tcstok_s(fieldBuf, FieldDesc::TypeSep, &nextToken);
            if (fieldName == NULL)
                return ERR_MSG_FORMAT;
            FieldDesc& fieldDesc = msgDesc.m_FieldDescMap[fieldName];   // 在字段描述表中查询
            if (fieldDesc.IsEmpty())    // 在字段描述表中不存在该字段
                return ERR_MSG_FORMAT;
            Field field(&fieldDesc);

            // 读取字段值
            fieldValue = _tcstok_s(NULL, FieldDesc::TypeSep, &nextToken);
            if (fieldValue == NULL)
                return ERR_MSG_FORMAT;
            if (field.Assign(fieldValue) != 0)
                return ERR_MSG_FORMAT;
            msg.AddField(fieldDesc.m_FieldName, field);
        }

        AddMsg(msg.m_Id, msg);
    }

    return 0;
}

void MsgTbl::Print(FILE* stream)
{
    MsgMapT::const_iterator i = m_MsgMap.begin();
    tstring val;

    for (; i != m_MsgMap.end(); ++i) {
        const tstring& id = i->first;
        const Msg& msg = i->second;

        _ASSERTE(msg.m_Id == id);
        _ftprintf(stream, _T("Message Id: %s\n"), id.c_str());
        _ftprintf(stream, _T("Message Type: %s\n"), msg.m_MsgDesc->m_MsgType.c_str());

        Msg::FieldMapT::const_iterator j = msg.m_FieldMap.begin();
        for (; j != msg.m_FieldMap.end(); ++j) {
            const Field& field = j->second;
            const FieldDesc* fieldDesc = field.m_FieldDesc;
            field.ToStr(&val);
            _ftprintf(stream, _T("Field: %s, Type: %s, Value: %s\n"), fieldDesc->m_FieldName.c_str(), FieldType::Name(fieldDesc->m_FieldType), val.c_str());
        }
        _fputts(_T("\n"), stream);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Test Case
////////////////////////////////////////////////////////////////////////////////

void TestMsgDescTbl(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    const _TCHAR* fname = _T("msg_desc.txt");
    MsgDescTbl msgDescTbl;
    msgDescTbl.LoadFile(fname);
    msgDescTbl.Print(stdout);

    PRINT_FUNC_END;
}

void TestMsgTbl(BOOL turnOn)
{
    SIMP_OFF_DO(turnOn, return);
    PRINT_FUNC_BEGIN;

    const _TCHAR* desfname = _T("msg_desc.txt");
    MsgDescTbl msgDescTbl;
    msgDescTbl.LoadFile(desfname);
    _fputts(_T("---------- Message Description ----------\n"), stdout);
    msgDescTbl.Print(stdout);

    const _TCHAR* msgfname = _T("msg_1.txt");
    MsgTbl msgTbl(&msgDescTbl);
    msgTbl.LoadFile(msgfname);
    _fputts(_T("---------- Message Data ----------\n"), stdout);
    msgTbl.Print(stdout);

    PRINT_FUNC_END;
}

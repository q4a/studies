// BuoyMsg.h
//

// 说明:
//   浮标消息的读取, 解析和打印. 来自 "Code Complete, 2Ed" Ch18 表驱动法 的示例
//   使用表驱动方法解析消息的字段类型和处理打印格式:
//   1. 使用双向映射: 类型标识 (整数) <-> 类型名 (字符串), 可考虑用 boost.bimap
//   2. 使用消息描述文件: 消息格式的定义和消息本身分离, 即元数据 (FieldDesc, MsgDesc) 和数据 (Field, Msg) 的分离
//   3. 使用变体类型 (Variant) 保存多种类型的数据
//   4. 变体类型中使用转换函数表, 本质也是一种表驱动法
//   5. 用变体方法 (3, 4) 替代动态绑定 (virtual)
//   6. 当增加/更改字段类型时, 需要增加/更改以下部分:
//      1. 增加/更改 FIELD_TYPE, 并在 FieldType::Init 中调用 BindTypeName 建立 类型名<->FIELD_TYPE 映射
//      2.1 增加/更改 Field::Variant 变体联合体的成员 (字段类型)
//      2.2 增加/更改 Field::MakeFunc, 即字符串转换为变体值 (字段类型) 函数
//      2.3 增加/更改 Field::ToStrFunc, 变体值 (字段类型) 转换为字符串函数
//      2.4 在 Field::Init 中建立 FIELD_TYPE->Field::MakeFunc 和 FIELD_TYPE->Field::ToStrFunc 的映射
//
//   注意:
//   1. 在使用 std::map 时, 不要将指针值 char* 作为键, 而要用支持字符串值比较的 std::string
//   2. std::string 不要用 NULL 初始化
//

#ifndef __BUOYMSG_H__
#define __BUOYMSG_H__

////////////////////////////////////////////////////////////////////////////////
// 字段格式
////////////////////////////////////////////////////////////////////////////////

// 字段类型
enum FIELD_TYPE {
    FIELD_ERROR = 0,    // FIELD_ERROR 必须是 0, 以作为 NameTypeMap 的默认项
    FIELD_FLOAT,
    FIELD_INT,
    FIELD_STRING,
    FIELD_TIME,
    FIELD_BOOL,
    FIELD_MAX
};

struct FieldType {
    static void Init();
    static void BindTypeName(FIELD_TYPE type, const _TCHAR* name);

    static FIELD_TYPE Type(const _TCHAR* name) {
        return NameTypeMap[name];
    }

    static const _TCHAR* Name(FIELD_TYPE type) {
        return TypeNameMap[type];
    }

    // 类型名到类型标识的映射
    typedef std::map<const Simp::tstring, FIELD_TYPE> NameTypeMapT;
    static NameTypeMapT NameTypeMap;
    // 类型标识到类型名的映射
    static const _TCHAR* TypeNameMap[FIELD_MAX];

    static const int MAX_TYPE = 20; // 字段类型名的最大字符数
};

// 字段描述
struct FieldDesc {
    FieldDesc(const _TCHAR* name = _T(""), FIELD_TYPE type = FIELD_ERROR) : m_FieldType(type), m_FieldName(name) {
        _ASSERTE(name != NULL);
    }

    BOOL IsEmpty() {
        return m_FieldName.empty();
    }

    static const int MAX_FIELD = 100;   // 字段名的最大字符数
    static const _TCHAR* TypeSep;       // 字段名和字段类型之间的分隔符

    FIELD_TYPE      m_FieldType;
    Simp::tstring   m_FieldName;
};

////////////////////////////////////////////////////////////////////////////////
// 消息格式
////////////////////////////////////////////////////////////////////////////////

// 消息描述
struct MsgDesc {
    MsgDesc(const _TCHAR* msgType = _T("")) : m_MsgType(msgType) {
        _ASSERTE(msgType != NULL);
    }

    void AddFieldDesc(const _TCHAR* name, FIELD_TYPE type) {
        m_FieldDescMap[name] = FieldDesc(name, type);
    }

    BOOL IsEmpty() {
        return m_MsgType.empty();
    }

    static const int MAX_MSGTYPE = 100;     // 消息类型名的最大字符数
    static const int MAX_MSGDESC = 1024;    // 一行消息描述的最大字符数

    // 字段名到字段描述的映射
    typedef std::map<Simp::tstring, FieldDesc> FieldDescMapT;
    FieldDescMapT m_FieldDescMap;

    Simp::tstring m_MsgType;
};

// 消息描述表
struct MsgDescTbl {
    enum {
        ERR_DESC_FORMAT = ERR_USER + 1
    };

    errno_t LoadFile(const _TCHAR* fname);
    void Print(FILE* stream);

    void AddMsgDesc(const Simp::tstring& type, const MsgDesc& desc) {
        m_MsgDescMap[type] = desc;
    }

    // 消息类型名到消息描述的映射
    typedef std::map<Simp::tstring, MsgDesc> MsgDescMapT;
    MsgDescMapT m_MsgDescMap;
};

////////////////////////////////////////////////////////////////////////////////
// 字段
////////////////////////////////////////////////////////////////////////////////

struct Field {
    Field(FieldDesc* desc = NULL) : m_FieldDesc(desc) {
        ZeroMemory(&m_Val, sizeof(m_Val));
    }

    ~Field() {
        if (m_FieldDesc != NULL && m_FieldDesc->m_FieldType == FIELD_STRING)
            free(m_Val.m_String);
    }

    // 因为 Variant::m_String 使用手动管理动态内存, 所以要支持拷贝
    Field(const Field& right) : m_FieldDesc(right.m_FieldDesc) {
        if (m_FieldDesc != NULL && m_FieldDesc->m_FieldType == FIELD_STRING)
            m_Val.m_String = _tcsdup(right.m_Val.m_String);
        else
            m_Val = right.m_Val;
    }

    Field& operator=(const Field& right) {
        if (this == &right)
            return *this;
        m_FieldDesc = right.m_FieldDesc;
        if (m_FieldDesc != NULL && m_FieldDesc->m_FieldType == FIELD_STRING) {
            free(m_Val.m_String);
            m_Val.m_String = _tcsdup(right.m_Val.m_String);
        }
        else
            m_Val = right.m_Val;
        return *this;
    }

    static void Init();
    errno_t Assign(const _TCHAR* str);
    errno_t ToStr(__out Simp::tstring* str) const;

    union Variant {
        int     m_Int;
        double  m_Double;
        _TCHAR* m_String;
        time_t  m_Time;
        BOOL    m_Bool;
    };

    // 字符串转换为变体值函数
    typedef errno_t (*MakeFunc)(__out Variant* val, const _TCHAR* str);
    static errno_t MakeInt(__out Variant* val, const _TCHAR* str);
    static errno_t MakeFloat(__out Variant* val, const _TCHAR* str);
    static errno_t MakeString(__out Variant* val, const _TCHAR* str);
    static errno_t MakeTime(__out Variant* val, const _TCHAR* str);
    static errno_t MakeBool(__out Variant* val, const _TCHAR* str);

    static MakeFunc MakeFuncMap[FIELD_MAX]; // 类型标识到转换为变体值函数的映射

    // 变体值转换为字符串函数
    typedef errno_t (*ToStrFunc)(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByInt(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByFloat(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByString(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByTime(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByBool(__out Simp::tstring* str, const Variant& val);

    static ToStrFunc ToStrFuncMap[FIELD_MAX];  // 类型标识到转换为字符串函数的映射

    Variant     m_Val;
    FieldDesc*  m_FieldDesc;
};

////////////////////////////////////////////////////////////////////////////////
// 消息
////////////////////////////////////////////////////////////////////////////////

struct Msg {
    Msg(const _TCHAR* id = _T(""), MsgDesc* desc = NULL) : m_Id(id), m_MsgDesc(desc) {
        _ASSERTE(id != NULL);
    }

    void AddField(const Simp::tstring& name, const Field& field) {
        m_FieldMap[name] = field;
    }

    static const int MAX_ID = 10;       // 浮标 id 的最大字符数
    static const int MAX_MSG = 1024;    // 一行消息的最大字符数

    // 字段名到字段值的映射
    typedef std::map<Simp::tstring, Field> FieldMapT;
    FieldMapT m_FieldMap;

    Simp::tstring   m_Id;   // 浮标 id
    MsgDesc*        m_MsgDesc;
};

struct MsgTbl {
    enum {
        ERR_MSG_FORMAT = ERR_USER + 2
    };

    MsgTbl(MsgDescTbl* descTbl) : m_MsgDescTbl(descTbl) {
        _ASSERTE(descTbl != NULL);
    }

    void AddMsg(const Simp::tstring& id, const Msg& msg) {
        m_MsgMap[id] = msg;
    }

    errno_t LoadFile(const _TCHAR* fname);
    void Print(FILE* stream);

    // 消息 id 到消息的映射
    typedef std::map<Simp::tstring, Msg> MsgMapT;
    MsgMapT m_MsgMap;

    MsgDescTbl* m_MsgDescTbl;
};

////////////////////////////////////////////////////////////////////////////////
// Test Case
////////////////////////////////////////////////////////////////////////////////

void TestMsgDescTbl(BOOL turnOn);
void TestMsgTbl(BOOL turnOn);

#endif  // __BUOYMSG_H__

// BuoyMsg.h
//

// ˵��:
//   ������Ϣ�Ķ�ȡ, �����ʹ�ӡ. ���� "Code Complete, 2Ed" Ch18 �������� ��ʾ��
//   ʹ�ñ���������������Ϣ���ֶ����ͺʹ����ӡ��ʽ:
//   1. ʹ��˫��ӳ��: ���ͱ�ʶ (����) <-> ������ (�ַ���), �ɿ����� boost.bimap
//   2. ʹ����Ϣ�����ļ�: ��Ϣ��ʽ�Ķ������Ϣ�������, ��Ԫ���� (FieldDesc, MsgDesc) ������ (Field, Msg) �ķ���
//   3. ʹ�ñ������� (Variant) ����������͵�����
//   4. ����������ʹ��ת��������, ����Ҳ��һ�ֱ�������
//   5. �ñ��巽�� (3, 4) �����̬�� (virtual)
//   6. ������/�����ֶ�����ʱ, ��Ҫ����/�������²���:
//      1. ����/���� FIELD_TYPE, ���� FieldType::Init �е��� BindTypeName ���� ������<->FIELD_TYPE ӳ��
//      2.1 ����/���� Field::Variant ����������ĳ�Ա (�ֶ�����)
//      2.2 ����/���� Field::MakeFunc, ���ַ���ת��Ϊ����ֵ (�ֶ�����) ����
//      2.3 ����/���� Field::ToStrFunc, ����ֵ (�ֶ�����) ת��Ϊ�ַ�������
//      2.4 �� Field::Init �н��� FIELD_TYPE->Field::MakeFunc �� FIELD_TYPE->Field::ToStrFunc ��ӳ��
//
//   ע��:
//   1. ��ʹ�� std::map ʱ, ��Ҫ��ָ��ֵ char* ��Ϊ��, ��Ҫ��֧���ַ���ֵ�Ƚϵ� std::string
//   2. std::string ��Ҫ�� NULL ��ʼ��
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
// �ֶθ�ʽ
////////////////////////////////////////////////////////////////////////////////

// �ֶ�����
enum FIELD_TYPE {
    FIELD_ERROR = 0,    // FIELD_ERROR ������ 0, ����Ϊ NameTypeMap ��Ĭ����
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

    // �����������ͱ�ʶ��ӳ��
    typedef std::map<const Simp::tstring, FIELD_TYPE> NameTypeMapT;
    static NameTypeMapT NameTypeMap;
    // ���ͱ�ʶ����������ӳ��
    static const _TCHAR* TypeNameMap[FIELD_MAX];

    static const int MAX_TYPE = 20; // �ֶ�������������ַ���
};

// �ֶ�����
struct FieldDesc {
    FieldDesc(const _TCHAR* name = _T(""), FIELD_TYPE type = FIELD_ERROR) : m_FieldType(type), m_FieldName(name) {
        _ASSERTE(name != NULL);
    }

    BOOL IsEmpty() {
        return m_FieldName.empty();
    }

    static const int MAX_FIELD = 100;   // �ֶ���������ַ���
    static const _TCHAR* TypeSep;       // �ֶ������ֶ�����֮��ķָ���

    FIELD_TYPE      m_FieldType;
    Simp::tstring   m_FieldName;
};

////////////////////////////////////////////////////////////////////////////////
// ��Ϣ��ʽ
////////////////////////////////////////////////////////////////////////////////

// ��Ϣ����
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

    static const int MAX_MSGTYPE = 100;     // ��Ϣ������������ַ���
    static const int MAX_MSGDESC = 1024;    // һ����Ϣ����������ַ���

    // �ֶ������ֶ�������ӳ��
    typedef std::map<Simp::tstring, FieldDesc> FieldDescMapT;
    FieldDescMapT m_FieldDescMap;

    Simp::tstring m_MsgType;
};

// ��Ϣ������
struct MsgDescTbl {
    enum {
        ERR_DESC_FORMAT = ERR_USER + 1
    };

    errno_t LoadFile(const _TCHAR* fname);
    void Print(FILE* stream);

    void AddMsgDesc(const Simp::tstring& type, const MsgDesc& desc) {
        m_MsgDescMap[type] = desc;
    }

    // ��Ϣ����������Ϣ������ӳ��
    typedef std::map<Simp::tstring, MsgDesc> MsgDescMapT;
    MsgDescMapT m_MsgDescMap;
};

////////////////////////////////////////////////////////////////////////////////
// �ֶ�
////////////////////////////////////////////////////////////////////////////////

struct Field {
    Field(FieldDesc* desc = NULL) : m_FieldDesc(desc) {
        ZeroMemory(&m_Val, sizeof(m_Val));
    }

    ~Field() {
        if (m_FieldDesc != NULL && m_FieldDesc->m_FieldType == FIELD_STRING)
            free(m_Val.m_String);
    }

    // ��Ϊ Variant::m_String ʹ���ֶ�����̬�ڴ�, ����Ҫ֧�ֿ���
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

    // �ַ���ת��Ϊ����ֵ����
    typedef errno_t (*MakeFunc)(__out Variant* val, const _TCHAR* str);
    static errno_t MakeInt(__out Variant* val, const _TCHAR* str);
    static errno_t MakeFloat(__out Variant* val, const _TCHAR* str);
    static errno_t MakeString(__out Variant* val, const _TCHAR* str);
    static errno_t MakeTime(__out Variant* val, const _TCHAR* str);
    static errno_t MakeBool(__out Variant* val, const _TCHAR* str);

    static MakeFunc MakeFuncMap[FIELD_MAX]; // ���ͱ�ʶ��ת��Ϊ����ֵ������ӳ��

    // ����ֵת��Ϊ�ַ�������
    typedef errno_t (*ToStrFunc)(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByInt(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByFloat(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByString(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByTime(__out Simp::tstring* str, const Variant& val);
    static errno_t ToStrByBool(__out Simp::tstring* str, const Variant& val);

    static ToStrFunc ToStrFuncMap[FIELD_MAX];  // ���ͱ�ʶ��ת��Ϊ�ַ���������ӳ��

    Variant     m_Val;
    FieldDesc*  m_FieldDesc;
};

////////////////////////////////////////////////////////////////////////////////
// ��Ϣ
////////////////////////////////////////////////////////////////////////////////

struct Msg {
    Msg(const _TCHAR* id = _T(""), MsgDesc* desc = NULL) : m_Id(id), m_MsgDesc(desc) {
        _ASSERTE(id != NULL);
    }

    void AddField(const Simp::tstring& name, const Field& field) {
        m_FieldMap[name] = field;
    }

    static const int MAX_ID = 10;       // ���� id ������ַ���
    static const int MAX_MSG = 1024;    // һ����Ϣ������ַ���

    // �ֶ������ֶ�ֵ��ӳ��
    typedef std::map<Simp::tstring, Field> FieldMapT;
    FieldMapT m_FieldMap;

    Simp::tstring   m_Id;   // ���� id
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

    // ��Ϣ id ����Ϣ��ӳ��
    typedef std::map<Simp::tstring, Msg> MsgMapT;
    MsgMapT m_MsgMap;

    MsgDescTbl* m_MsgDescTbl;
};

////////////////////////////////////////////////////////////////////////////////
// Test Case
////////////////////////////////////////////////////////////////////////////////

void TestMsgDescTbl(BOOL turnOn);
void TestMsgTbl(BOOL turnOn);

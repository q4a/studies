#pragma once

// CStudent command target

class CStudent : public CObject {
    DECLARE_DYNAMIC(CStudent)

public:
    CStudent() : m_Grade(0) {}

    CStudent(LPCTSTR name, int grade) : m_Name(name), m_Grade(grade) {}

    virtual ~CStudent();

    BOOL operator==(const CStudent& right) const {
        return (m_Name == right.m_Name && m_Grade == right.m_Grade);
    }

    BOOL operator!=(const CStudent& right) const {
        return !(*this == right);
    }

    BOOL IsEmpty() const {
        return (m_Name.IsEmpty() && m_Grade == 0);
    }

    void SetEmpty() {
        m_Name = _T("");
        m_Grade = 0;
    }

#ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
#endif

public:
    CString m_Name;
    int     m_Grade;
};



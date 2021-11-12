#pragma once


// CUpperEdit

class CUpperEdit : public CWnd {
    DECLARE_DYNAMIC(CUpperEdit)

public:
    CUpperEdit();
    virtual ~CUpperEdit();

protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};



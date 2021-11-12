#pragma once


// CNonNumEdit

class CNonNumEdit : public CEdit {
    DECLARE_DYNAMIC(CNonNumEdit)

public:
    CNonNumEdit();
    virtual ~CNonNumEdit();

protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};



#pragma once

#include "NonNumEdit.h"
#include "UpperEdit.h"

// CMyDialog1 dialog

class CMyDialog1 : public CDialog {
    DECLARE_DYNAMIC(CMyDialog1)

public:
    CMyDialog1(CWnd* pParent = NULL);   // standard constructor
    virtual ~CMyDialog1();

// Dialog Data
    enum { IDD = IDD_DIALOG1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

private:
    CNonNumEdit m_NonNumEdit;
    CUpperEdit  m_UpperEdit;
};

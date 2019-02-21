#pragma once

#include "Ryg.h"
#include "RygCtrl.h"

// CRygDlg dialog

class CRygDlg : public CDialog {
    DECLARE_DYNAMIC(CRygDlg)

public:
    CRygDlg(CWnd* pParent = NULL);   // standard constructor
    virtual ~CRygDlg();

// Dialog Data
    enum { IDD = IDD_DIALOG2 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
    afx_msg void OnClickedRyg();

protected:
    DECLARE_MESSAGE_MAP()

private:
    RYG_STAT    m_RygState;
};

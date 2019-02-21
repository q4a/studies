#pragma once


// CEffectPage dialog

class CEffectPage : public CPropertyPage {
    DECLARE_DYNAMIC(CEffectPage)

public:
    CEffectPage();
    virtual ~CEffectPage();

// Dialog Data
    enum { IDD = IDD_PAGE_EFFECT };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

public:
    BOOL    m_Bold;
    BOOL    m_Italic;
    BOOL    m_Underline;
};

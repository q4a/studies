#pragma once

// CFontPage dialog

class CFontPage : public CPropertyPage {
    DECLARE_DYNAMIC(CFontPage)

public:
    CFontPage();
    virtual ~CFontPage();
    LPCTSTR GetFont();

// Dialog Data
    enum { IDD = IDD_PAGE_FONT };
    enum { WM_USERAPPLY = WM_USER + 1 };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnApply();
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

public:
    static LPCTSTR  FontTable[];
    int             m_Font;
};

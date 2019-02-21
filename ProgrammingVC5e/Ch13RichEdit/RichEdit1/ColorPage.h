#pragma once


// CColorPage dialog

class CColorPage : public CPropertyPage {
    DECLARE_DYNAMIC(CColorPage)

public:
    CColorPage();
    virtual ~CColorPage();

    COLORREF GetColor();

// Dialog Data
    enum { IDD = IDD_PAGE_COLOR };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()

public:
    static COLORREF ColorTable[];
    int             m_Color;
};

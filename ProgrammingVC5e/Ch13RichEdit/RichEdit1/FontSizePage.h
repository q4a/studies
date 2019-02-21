#pragma once


// CFontSizePage dialog

class CFontSizePage : public CPropertyPage {
    DECLARE_DYNAMIC(CFontSizePage)

public:
    CFontSizePage();
    virtual ~CFontSizePage();

// Dialog Data
    enum { IDD = IDD_PAGE_SIZE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:
    int     m_FontSize;
};

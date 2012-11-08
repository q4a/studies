#pragma once

// CFontSheet

class CFontSheet : public CPropertySheet {
    DECLARE_DYNAMIC(CFontSheet)

public:
    CFontSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CFontSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    virtual ~CFontSheet();

protected:
    DECLARE_MESSAGE_MAP()

public:
    CFontPage       m_FontPage;
    CEffectPage     m_EffectPage;
    CColorPage      m_ColorPage;
    CFontSizePage   m_FontSizePage;
};

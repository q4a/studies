#pragma once


// CRygCtrl

enum WM_RYG_TYPE {
    WM_RYG_SETSTATE     = WM_USER + 1,
    WM_RYG_GETSTATE     = WM_USER + 2
};

enum RYG_STAT {
    RYG_OFF,
    RYG_RED,
    RYG_YELLOW,
    RYG_GREEN
};

class CRygCtrl : public CWnd {
    DECLARE_DYNAMIC(CRygCtrl)

public:
    CRygCtrl();
    virtual ~CRygCtrl();

protected:
    virtual void PostNcDestroy();

public:
    static LRESULT CALLBACK AFX_EXPORT RygWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    static BOOL RegisterClass(HINSTANCE inst);

public:
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg LRESULT OnSetState(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT OnGetState(WPARAM wparam, LPARAM lparam);

protected:
    DECLARE_MESSAGE_MAP()

private:
    void SetMapping(CDC* dc);
    void UpdateColor(CDC* dc, int n);

public:
    static LPCTSTR  ClassName;

private:
    RYG_STAT    m_State;

    static  CRect   RectRnd;
    static  CPoint  Point;
    static  CRect   RectColor[3];
    static  CBrush  BrushColor[4];
};



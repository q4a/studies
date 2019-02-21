// UpperEdit.cpp : implementation file
//

#include "StdAfx.h"
#include "SubCtrl.h"
#include "UpperEdit.h"


// CUpperEdit

IMPLEMENT_DYNAMIC(CUpperEdit, CWnd)

CUpperEdit::CUpperEdit()
{

}

CUpperEdit::~CUpperEdit()
{
}


BEGIN_MESSAGE_MAP(CUpperEdit, CWnd)
    ON_WM_CHAR()
END_MESSAGE_MAP()



// CUpperEdit message handlers



void CUpperEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (_istlower(nChar))
        nChar = _totupper(nChar);

    this->DefWindowProc(WM_CHAR, (WPARAM) nChar, (LPARAM) (nRepCnt | (nFlags << 16)));
}

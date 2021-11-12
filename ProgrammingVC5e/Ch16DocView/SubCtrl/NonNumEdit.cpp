// NonNumEdit.cpp : implementation file
//

#include "StdAfx.h"
#include "SubCtrl.h"
#include "NonNumEdit.h"

// CNonNumEdit

IMPLEMENT_DYNAMIC(CNonNumEdit, CEdit)

CNonNumEdit::CNonNumEdit()
{
}

CNonNumEdit::~CNonNumEdit()
{
}

BEGIN_MESSAGE_MAP(CNonNumEdit, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()

// CNonNumEdit message handlers

void CNonNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (!_istdigit(nChar))
        CEdit::OnChar(nChar, nRepCnt, nFlags);
}

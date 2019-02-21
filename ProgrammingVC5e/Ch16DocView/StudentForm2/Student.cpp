// Student.cpp : implementation file
//

#include "StdAfx.h"
#include "StudentForm2.h"
#include "Student.h"

// CStudent

IMPLEMENT_DYNAMIC(CStudent, CObject)

CStudent::~CStudent()
{
}

// CStudent member functions

#ifdef _DEBUG
void CStudent::Dump(CDumpContext& dc) const
{
    CObject::Dump(dc);
    dc << _T("Name = ") << m_Name << _T(", Grade = ") << m_Grade;
}
#endif //_DEBUG

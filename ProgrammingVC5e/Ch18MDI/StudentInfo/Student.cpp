// Student.cpp : implementation file
//

#include "StdAfx.h"
#include "StudentInfo.h"
#include "Student.h"

// CStudent

IMPLEMENT_SERIAL(CStudent, CObject, 0)

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
#endif  // _DEBUG

void CStudent::Serialize(CArchive& ar)
{
    MYTRACE("Enter");
    if (ar.IsStoring())
        ar << m_Name << m_Grade;
    else
        ar >> m_Name >> m_Grade;
}

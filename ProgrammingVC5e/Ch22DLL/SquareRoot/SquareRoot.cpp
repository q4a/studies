// SquareRoot.cpp : Defines the initialization routines for the DLL.
//

#include "StdAfx.h"
#include "SquareRoot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


// CSquareRootApp

BEGIN_MESSAGE_MAP(CSquareRootApp, CWinApp)
END_MESSAGE_MAP()


// CSquareRootApp construction

CSquareRootApp::CSquareRootApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only CSquareRootApp object

CSquareRootApp theApp;


// CSquareRootApp initialization

BOOL CSquareRootApp::InitInstance()
{
    CWinApp::InitInstance();

    return TRUE;
}

SQUAREROOT_API double SquareRoot(double num)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    MYTRACE("Enter");
    if (num >= 0.0)
        return sqrt(num);
    DEBUG_ONLY(AfxMessageBox(_T("Can't take square root of a negative number.")));
    return 0.0;
}

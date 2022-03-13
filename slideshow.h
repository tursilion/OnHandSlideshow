// slideshow.h : main header file for the SLIDESHOW application
//

#if !defined(AFX_SLIDESHOW_H__BE5F443B_B82A_4804_9AED_FF6E726B0F64__INCLUDED_)
#define AFX_SLIDESHOW_H__BE5F443B_B82A_4804_9AED_FF6E726B0F64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSlideshowApp:
// See slideshow.cpp for the implementation of this class
//

class CSlideshowApp : public CWinApp
{
public:
	CSlideshowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlideshowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSlideshowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDESHOW_H__BE5F443B_B82A_4804_9AED_FF6E726B0F64__INCLUDED_)

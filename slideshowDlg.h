// slideshowDlg.h : header file
//

#if !defined(AFX_SLIDESHOWDLG_H__FE672BB6_6A30_4088_8E56_1FA95DE8652A__INCLUDED_)
#define AFX_SLIDESHOWDLG_H__FE672BB6_6A30_4088_8E56_1FA95DE8652A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSlideshowDlg dialog

class CSlideshowDlg : public CDialog
{
// Construction
public:
	unsigned char * pPath;
	unsigned char * pDelay;
	CSlideshowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSlideshowDlg)
	enum { IDD = IDD_SLIDESHOW_DIALOG };
	UINT	m_Delay;
	CString	m_Path;
	CString	m_Filename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlideshowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSlideshowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnWrite();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDESHOWDLG_H__FE672BB6_6A30_4088_8E56_1FA95DE8652A__INCLUDED_)

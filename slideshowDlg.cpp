// slideshowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "slideshow.h"
#include "slideshowDlg.h"
#include "slidshow.inc"    // Include file of the OnHand EXF file
#include "stdio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlideshowDlg dialog

CSlideshowDlg::CSlideshowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlideshowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSlideshowDlg)
	m_Delay = 0;
	m_Path = _T("");
	m_Filename = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlideshowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSlideshowDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Delay);
	DDV_MinMaxUInt(pDX, m_Delay, 1, 99);
	DDX_Text(pDX, IDC_EDIT2, m_Path);
	DDV_MaxChars(pDX, m_Path, 49);
	DDX_Text(pDX, IDC_EDIT3, m_Filename);
	DDV_MaxChars(pDX, m_Filename, 8);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSlideshowDlg, CDialog)
	//{{AFX_MSG_MAP(CSlideshowDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlideshowDlg message handlers

BOOL CSlideshowDlg::OnInitDialog()
{
	unsigned char *pTmp;

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	pDelay=NULL;
	pPath=NULL;

	// Find start of data area.
	pTmp=PROG+sizeof(PROG)-17;		// End of data - length of '---START DATA--\0'
	while (strncmp((const char*)pTmp, "---START DATA--", 15)) {
		pTmp--;
		if (pTmp <= PROG) {
			// can't find it - it can't be the first bytes!
			AfxMessageBox("Internal error - data is corrupted. File can not be written.", MB_ICONSTOP | MB_OK);
			EndDialog(IDCANCEL);
			return TRUE;
		}
	}
	pTmp+=16;
	// first is "Delay: (xxx) s" - we want that 'xxx', so we'll look for the '('
	while ((pTmp < PROG+sizeof(PROG)) && (*pTmp != '(')) pTmp++;
	if (*pTmp != '(') {
		AfxMessageBox("Internal error - data is corrupted. File can not be written.", MB_ICONSTOP | MB_OK);
		EndDialog(IDCANCEL);
		return TRUE;
	}
	pTmp++;
	pDelay=pTmp;
	m_Delay=(*pDelay-'0')*100+(*(pDelay+1)-'0')*10+(*(pDelay+2)-'0');

	while ((pTmp < PROG+sizeof(PROG)) && (*pTmp != '\0')) pTmp++;
	if (*pTmp != '\0') {
		AfxMessageBox("Internal error - data is corrupted. File can not be written.", MB_ICONSTOP | MB_OK);
		EndDialog(IDCANCEL);
		return TRUE;
	}

	// next is 'Path to pics:\0\0\0' - 16 chars long. We just have to assume here. We fix up the path
	// if it's missing a leading or trailing slash
	pTmp+=18;
	pPath=pTmp;
	m_Path=(const char*)pPath;

	m_Filename="SLIDSHOW";

	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSlideshowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlideshowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSlideshowDlg::OnWrite() 
{
	FILE *fp;
	CString csFile;

	if (!UpdateData()) return;

	csFile.Format("%s.EXF", m_Filename);

	fp=fopen(csFile, "rb");
	if (NULL != fp) {
		fclose(fp);
		if (IDNO == AfxMessageBox("File already exists -- Overwrite?", MB_ICONQUESTION | MB_YESNO)) {
			return;
		}
	}

	// Make the patches
	*(pDelay)=m_Delay/100+'0';
	*(pDelay+1)=(m_Delay%100)/10+'0';
	*(pDelay+2)=(m_Delay%10)+'0';

	if (m_Path[0]!='\\') {
		m_Path.Insert(0, '\\');
	}
	if (m_Path.Right(1) != '\\') {
		m_Path+='\\';
	}
	memset(pPath, 0, 50);	// path is 50 chars long
	strcpy((char*)pPath, m_Path);
	
	// Now write the file
	fp=fopen(csFile, "wb");
	if (NULL == fp) {
		AfxMessageBox("Error writing output file.", MB_ICONSTOP|MB_OK);
		return;
	}
	fwrite(PROG, 1, sizeof(PROG), fp);
	fclose(fp);

	AfxMessageBox("File written successfully! You may now upload the file to your watch with PC Filer.", MB_OK);
}

void CSlideshowDlg::OnOK() 
{
	EndDialog(IDCANCEL);	// Okay, this is cheap. Sorry - poor planning. :)
}

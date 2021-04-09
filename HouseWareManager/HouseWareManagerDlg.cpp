
// HouseWareManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HouseWareManager.h"
#include "HouseWareManagerDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "mainFrame.h"
#include "RegisterPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHouseWareManagerDlg dialog



CHouseWareManagerDlg::CHouseWareManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHouseWareManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHouseWareManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ID, id_val_);
	DDX_Control(pDX, IDC_PW, pw_val_);
}

BEGIN_MESSAGE_MAP(CHouseWareManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LGIN, &CHouseWareManagerDlg::OnBnClickedBtnLgin)
	ON_BN_CLICKED(IDC_BTN_RGT, &CHouseWareManagerDlg::OnBnClickedBtnRgt)
	ON_BN_CLICKED(ID_FILE_EXIT, &CHouseWareManagerDlg::OnbnClicedExt_cmd)
END_MESSAGE_MAP()


// CHouseWareManagerDlg message handlers

BOOL CHouseWareManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_NewMenu.LoadMenuW(IDR_MENUBAR);
	SetMenu(&m_NewMenu);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHouseWareManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHouseWareManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHouseWareManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHouseWareManagerDlg::OnBnClickedBtnLgin()
{
	// TODO: Add your control notification handler code here
	// Connect to SQL
	CDatabase Cnn;
	CString sDriver = L"ODBC Driver 13 for SQL Server";
	//CString strConnection = _T("ODBC; Driver = {ODBC Driver 13 for SQL Server};Server = SM101\\SQL2012; Trusted_Connection = yes; Database = HouseDataBase;");
	CString strConnect  = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
	CString strID, strName;
	//int strPw;
	CString str_id;
	CString str_pw;
	id_val_.GetWindowText(str_id);
	pw_val_.GetWindowText(str_pw);
	BOOL CheckedLogin = FALSE;
	//strPw = _ttoi(str_pw);
	/*TRY{*/
		// Open the database
		Cnn.Open(NULL, false, false, strConnect);
		CRecordset rcs(&Cnn);
		CString strSql = _T("select * from LoginUser");
		rcs.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
		while (!rcs.IsEOF()) {
			// Copy each column into a variable
			rcs.GetFieldValue(_T("ID"), strID);
			rcs.GetFieldValue(L"Password", strName);
			if (strID == str_id && strName == str_pw){
				CheckedLogin = TRUE;
				MessageBox(L"Dang nhap thanh cong");

				ShowWindow(SW_HIDE);
				mainFrame main;
				main.DoModal();
				//EndDialog(0);
				break;
			}
			rcs.MoveNext();
		}
		if (CheckedLogin == FALSE){
			MessageBox(L"Id or Password error");
		}
	
		// Close the database
		Cnn.Close();
	//}CATCH(CDBException, e) {
	//	// If a database exception occured, show error msg
	//	AfxMessageBox(L"Error");
	//}
	//END_CATCH;
	if (CheckedLogin){
		mainFrame main;
		main.DoModal();
		DestroyWindow();
	}
}

void CHouseWareManagerDlg::OnbnClicedExt_cmd(){
	DestroyWindow();
}

void CHouseWareManagerDlg::OnBnClickedBtnRgt()
{
	// TODO: Add your control notification handler code here
	RegisterPage rg;
	rg.DoModal();
	DestroyWindow();
	
}

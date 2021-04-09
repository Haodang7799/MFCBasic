// RegisterPage.cpp : implementation file
//

#include "stdafx.h"
#include "HouseWareManager.h"
#include "RegisterPage.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"


// RegisterPage dialog

IMPLEMENT_DYNAMIC(RegisterPage, CDialogEx)

RegisterPage::RegisterPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(RegisterPage::IDD, pParent)
{

}

RegisterPage::~RegisterPage()
{
}

void RegisterPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ID, input_id);
	DDX_Control(pDX, IDC_PW, input_pw);
	DDX_Control(pDX, IDC_PW2, input_pw2);
}


BEGIN_MESSAGE_MAP(RegisterPage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOGIN_RGP, &RegisterPage::OnBnClickedBtnLoginRgp)
	ON_BN_CLICKED(IDC_BTN_RGT_RGTP, &RegisterPage::OnBnClickedBtnRgtRgtp)
END_MESSAGE_MAP()


// RegisterPage message handlers


void RegisterPage::OnBnClickedBtnLoginRgp()
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	EndDialog(0);

	
}


void RegisterPage::OnBnClickedBtnRgtRgtp()
{
	// TODO: Add your control notification handler code here
	CString id_val_,strID;
	CString pw_val_;
	CString pw2_val_;
	input_id.GetWindowText(id_val_);
	input_pw.GetWindowText(pw_val_);
	input_pw2.GetWindowText(pw2_val_);
	if (id_val_.IsEmpty() | pw2_val_.IsEmpty() | pw_val_.IsEmpty()){
		MessageBox(L"Khong duoc de trong");
	}
	else if (pw_val_ != pw2_val_){
		MessageBox(L"Pass khong trung nhau");
	}
	else{
		CDatabase Cnn;
		CString sDriver = L"ODBC Driver 13 for SQL Server";
		CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
		BOOL Checked = TRUE;
		Cnn.Open(NULL, false, false, strConnect);
		CRecordset rcs(&Cnn);
		CString strSql = _T("select ID from LoginUser");
		rcs.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
		while (!rcs.IsEOF()) {
			rcs.GetFieldValue(_T("ID"), strID);
			if (strID == id_val_){
				MessageBox(L"Ten dang nhap da ton tai!");
				Checked = FALSE;
				break;
			}
			rcs.MoveNext();
		}
		if (Checked){
			strSql.Format(L"INSERT INTO LoginUser (ID,Password) VALUES ('%s','%s')", id_val_, pw_val_);
			Cnn.ExecuteSQL(strSql);
			MessageBox(L"Dang ky thanh cong");
			ShowWindow(SW_HIDE);
			EndDialog(0);
		}
	}

}

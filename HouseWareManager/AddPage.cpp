// AddPage.cpp : implementation file
//

#include "stdafx.h"
#include "HouseWareManager.h"
#include "AddPage.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "mainFrame.h"


// AddPage dialog

IMPLEMENT_DYNAMIC(AddPage, CDialogEx)

AddPage::AddPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddPage::IDD, pParent)
{

}

AddPage::~AddPage()
{
}

void AddPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID_PA, id_val_);
	DDX_Control(pDX, IDC_EDIT_NAME_PA, name_val_);
	DDX_Control(pDX, IDC_EDIT_NUMBER_PA, number_val_);
	DDX_Control(pDX, IDC_EDIT_PRICE_PA, price_val_);
	DDX_Control(pDX, IDC_EDIT_DATE_PA, date_val_);
	DDX_Control(pDX, IDC_CB_SELECT, cbb_select);

	BOOL Checked = FALSE;
	if (Checked == FALSE){
		CDatabase Cnn;
		CString sDriver = L"ODBC Driver 13 for SQL Server";
		CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
		Cnn.Open(NULL, false, false, strConnect);

		CRecordset rcs(&Cnn);
		CString strSql = _T("select * from DataHouseBase");
		rcs.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
		int line = 0;
		while (!rcs.IsEOF()) {
			rcs.GetFieldValue(_T("ID"), strID);
			cbb_select.AddString(strID);
			line++;
			rcs.MoveNext();
		}
		Cnn.Close();
		Checked = TRUE;
	}
}


BEGIN_MESSAGE_MAP(AddPage, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddPage::OnBnClickedOk)
	ON_CBN_SELENDOK(IDC_CB_SELECT, &AddPage::OnCbnSelendokCbSelect)
END_MESSAGE_MAP()


// AddPage message handlers


void AddPage::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	id_val_.GetWindowText(strID);
	name_val_.GetWindowText(strName);
	number_val_.GetWindowText(strNumber);
	price_val_.GetWindowText(strPrice);
	date_val_.GetWindowText(strDate);
	DestroyWindow();

}


void AddPage::OnCbnSelendokCbSelect()
{
	UpdateData();
	// TODO: Add your control notification handler code here
	CString lineslt = _T("");
	cbb_select.GetWindowText(lineslt);
	CDatabase Cnn;
	CString sDriver = L"ODBC Driver 13 for SQL Server";
	CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
	Cnn.Open(NULL, false, false, strConnect);

	CRecordset rcs(&Cnn);
	CString strSql = _T("select * from DataHouseBase Where ID = '%s'");
	strSql.Format(L"select * from DataHouseBase Where ID = '%s'", lineslt);
	rcs.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
	
	while (!rcs.IsEOF()) {
		rcs.GetFieldValue(_T("ID"), strID);
		rcs.GetFieldValue(_T("Name"), strName);
		rcs.GetFieldValue(_T("Number"), strNumber);
		rcs.GetFieldValue(_T("Price"), strPrice);
		rcs.GetFieldValue(_T("Date"), strDate);
		
		name_val_.SetWindowTextW(strName);
		id_val_.SetWindowTextW(strID);
		number_val_.SetWindowTextW(strNumber);
		price_val_.SetWindowTextW(strPrice);
		date_val_.SetWindowTextW(strDate);
		rcs.MoveNext();
	}
	Cnn.Close();

}

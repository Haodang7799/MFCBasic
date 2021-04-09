// mainFrame.cpp : implementation file
//

#include "stdafx.h"
#include "HouseWareManager.h"
#include "mainFrame.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "AddPage.h"




// mainFrame dialog

IMPLEMENT_DYNAMIC(mainFrame, CDialogEx)

mainFrame::mainFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(mainFrame::IDD, pParent)
{

}

mainFrame::~mainFrame()
{
	
}

void mainFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, list_data_);
	//DDX_Control(pDX, IDC_EDIT_ID, id_val_);
	//DDX_Control(pDX, IDC_EDIT_NAME, name_val_);
	//DDX_Control(pDX, IDC_EDIT_NUMBER, number_val_);
	//DDX_Control(pDX, IDC_EDIT_PRICE, price_val_);
	//DDX_Control(pDX, IDC_EDIT_DATE, date_val_);
	if (CheckCreateTable == FALSE){

		CheckCreateTable = TRUE;
		list_data_.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVIS_SELECTED);
		list_data_.InsertColumn(0, _T("ID"), LVS_ALIGNLEFT, 50);
		list_data_.InsertColumn(1, _T("Name"), LVS_ALIGNLEFT, 100);
		list_data_.InsertColumn(2, _T("Number"), LVS_ALIGNLEFT, 70);
		list_data_.InsertColumn(3, _T("Price"), LVS_ALIGNLEFT, 80);
		list_data_.InsertColumn(4, _T("Date"), LVS_ALIGNLEFT, 70);
		list_data_.InsertColumn(5, _T("Time Add"), LVS_ALIGNLEFT, 140);
	}

	UpdateValue();
	menu_bar.LoadMenu(IDR_MENUBAR);
	SetMenu(&menu_bar);
}


BEGIN_MESSAGE_MAP(mainFrame, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD, &mainFrame::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &mainFrame::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &mainFrame::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_FIND, &mainFrame::OnBnClickedBtnFind)
	ON_BN_CLICKED(IDC_BTN_SORT, &mainFrame::OnBnClickedBtnSort)
ON_NOTIFY(HDN_ITEMCLICK, 0, &mainFrame::OnHdnItemclickListData)
ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_DATA, &mainFrame::OnLvnBeginlabeleditListData)
END_MESSAGE_MAP()


// mainFrame message handlers

void mainFrame::UpdateValue(){
	list_data_.DeleteAllItems();
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
		rcs.GetFieldValue(_T("Name"), strName);
		rcs.GetFieldValue(_T("Number"), strNum);
		rcs.GetFieldValue(_T("Price"), strPrice);
		rcs.GetFieldValue(_T("Date"), strDate);
		rcs.GetFieldValue(_T("Time"), strTime);
		list_data_.InsertItem(line, strID);
		list_data_.SetItemText(line, 1, strName);
		list_data_.SetItemText(line, 2, strPrice);
		list_data_.SetItemText(line, 3, strNum);
		list_data_.SetItemText(line, 4, strDate);
		list_data_.SetItemText(line, 5, strTime);

		line++;
		rcs.MoveNext();
	}
	Cnn.Close();
}
void mainFrame::OnBnClickedBtnAdd()
{
	AddPage Dlg;

	TRY
	{
		if (Dlg.DoModal() == IDOK){
			if (Dlg.strID.IsEmpty() | Dlg.strName.IsEmpty() | Dlg.strNumber.IsEmpty() | Dlg.strDate.IsEmpty() | Dlg.strPrice.IsEmpty()){
				MessageBox(L"Khong duoc bo trong");
			}
			else
			{
				CDatabase Cnn;
				CString sDriver = L"ODBC Driver 13 for SQL Server";
				CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
				Cnn.Open(NULL, false, false, strConnect);

				CRecordset rcs(&Cnn);
				int count = 0;
				CString SQL = _T("");
				SQL.Format(L"SELECT * FROM DataHouseBase WHERE ID = '%s'", Dlg.strID);
				rcs.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);

				while (!rcs.IsEOF()) {
					count++;
					rcs.MoveNext();
				}

				if (count == 0){
					SQL.Format(L"INSERT INTO DataHouseBase (ID,Name,Number,Price,Date,Time) VALUES ('%s','%s','%s','%s','%s',GETDATE())", Dlg.strID, Dlg.strName, Dlg.strNumber, Dlg.strPrice, Dlg.strDate);
					Cnn.ExecuteSQL(SQL);
					MessageBox(L"Da them thanh cong");
					//UpdateData(TRUE);
				}
				else{
					MessageBox(L"ID da ton tai");
				}
				Cnn.Close();
			}
			
		}
	}
		CATCH(CDBException, e){
		MessageBox(L"Data Error : " + e->m_strError);
	}
	END_CATCH;
	UpdateValue();
}
	


void mainFrame::OnBnClickedBtnModify()
{
	AddPage Dlg;
	TRY
	{
		if (Dlg.DoModal() == IDOK){
			if (Dlg.strID.IsEmpty() | Dlg.strName.IsEmpty() | Dlg.strNumber.IsEmpty() | Dlg.strDate.IsEmpty() | Dlg.strPrice.IsEmpty()){
				MessageBox(L"Khong duoc bo trong");
			}
			else
			{
				CDatabase Cnn;
				CString sDriver = L"ODBC Driver 13 for SQL Server";
				CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
				Cnn.Open(NULL, false, false, strConnect);

				CRecordset rcs(&Cnn);
				int count = 0;
				CString SQL = _T("");
				SQL.Format(L"SELECT * FROM DataHouseBase WHERE ID = '%s'", strID);
				rcs.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);

				while (!rcs.IsEOF()) {
					count++;
					rcs.MoveNext();
				}

				if (count == 1){
					SQL.Format(L"UPDATE DataHouseBase SET Name = '%s', Number = '%s', Price= '%s', Date = '%s',Time = GETDATE() WHERE ID = '%s';", Dlg.strName, Dlg.strNumber, Dlg.strPrice, Dlg.strDate, Dlg.strID);
					Cnn.ExecuteSQL(SQL);
					MessageBox(L"Da sua thanh cong thanh cong");
				}
				else{
					MessageBox(L"ID khong ton tai");
				}
				Cnn.Close();
			}
			//UpdateData(TRUE);
		}
	}
		CATCH(CDBException, e){
		MessageBox(L"Data Error : " + e->m_strError);
	}
	END_CATCH;
	UpdateValue();
}

		
	//	// TODO: Add your control notification handler code here
	//	id_val_.GetWindowText(strID);
	//	name_val_.GetWindowText(strName);
	//	number_val_.GetWindowText(strNum);
	//	price_val_.GetWindowText(strPrice);
	//	date_val_.GetWindowText(strDate);
	//	if (strID.IsEmpty() | strName.IsEmpty() | strNum.IsEmpty() | strDate.IsEmpty() | strPrice.IsEmpty()){
	//		MessageBox(L"Khong duoc bo trong");
	//	}
	//	else
	//	{
	//		CDatabase Cnn;
	//		CString sDriver = L"ODBC Driver 13 for SQL Server";
	//		CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
	//		Cnn.Open(NULL, false, false, strConnect);

	//		CRecordset rcs(&Cnn);
	//		int count = 0;
	//		CString SQL = _T("");
	//		SQL.Format(L"SELECT * FROM DataHouseBase WHERE ID = '%s'", strID);
	//		rcs.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);

	//		while (!rcs.IsEOF()) {
	//			count++;
	//			rcs.MoveNext();
	//		}

	//		if (count == 1){
	//			SQL.Format(L"UPDATE DataHouseBase SET Name = '%s', Number = '%s', Price= '%s', Date = '%s',Time = GETDATE() WHERE ID = '%s';", strName, strNum, strPrice, strDate, strID);
	//			Cnn.ExecuteSQL(SQL);
	//			MessageBox(L"Da sua thanh cong thanh cong");
	//			UpdateData(TRUE);
	//		}
	//		else{
	//			MessageBox(L"ID khong da ton tai");
	//		}
	//		Cnn.Close();
	//	}

	//	"DELETE  FROM DataHouseBase WHERE ID = '%s'"



void mainFrame::OnBnClickedBtnDelete()
{
	AddPage Dlg;
	TRY
	{
		if (Dlg.DoModal() == IDOK){
			if (Dlg.strID.IsEmpty() | Dlg.strName.IsEmpty() | Dlg.strNumber.IsEmpty() | Dlg.strDate.IsEmpty() | Dlg.strPrice.IsEmpty()){
				MessageBox(L"Khong duoc bo trong");
			}
			else
			{
				CDatabase Cnn;
				CString sDriver = L"ODBC Driver 13 for SQL Server";
				CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
				Cnn.Open(NULL, false, false, strConnect);

				CRecordset rcs(&Cnn);
				int count = 0;
				CString SQL = _T("");
				SQL.Format(L"SELECT * FROM DataHouseBase WHERE ID = '%s'", strID);
				rcs.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);

				while (!rcs.IsEOF()) {
					count++;
					rcs.MoveNext();
				}

				if (count == 1){
					SQL.Format(L"DELETE  FROM DataHouseBase WHERE ID = '%s'", Dlg.strID);
					Cnn.ExecuteSQL(SQL);
					MessageBox(L"Da xoa thanh cong");
				}
				else{
					MessageBox(L"ID khong ton tai");
				}
				Cnn.Close();
			}
			//UpdateData(TRUE);
		}
	}
		CATCH(CDBException, e){
		MessageBox(L"Data Error : " + e->m_strError);
	}
	END_CATCH;
	UpdateValue();
}


	void mainFrame::OnBnClickedBtnFind(){
	// TODO: Add your control notification handler code here
		TRY
		{
			id_val_.GetWindowText(strID);
			if (strID.IsEmpty()){
				MessageBox(L"Nhap id de tim kiem !");
			}
			else
			{
				CDatabase Cnn;
				CString sDriver = L"ODBC Driver 13 for SQL Server";
				CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
				Cnn.Open(NULL, false, false, strConnect);
				CString SQL = _T("");
				
				SQL.Format(L"SELECT * FROM DataHouseBase WHERE ID = '%s'", strID);
				CRecordset rcs(&Cnn);
				rcs.Open(CRecordset::forwardOnly, SQL, CRecordset::readOnly);
				list_data_.DeleteAllItems();
				int line = 0;
				while (!rcs.IsEOF()) {
					rcs.GetFieldValue(_T("ID"), strID);
					rcs.GetFieldValue(_T("Name"), strName);
					rcs.GetFieldValue(_T("Number"), strNum);
					rcs.GetFieldValue(_T("Price"), strPrice);
					rcs.GetFieldValue(_T("Date"), strDate);
					rcs.GetFieldValue(_T("Time"), strTime);
					list_data_.InsertItem(line, strID);
					list_data_.SetItemText(line, 1, strName);
					list_data_.SetItemText(line, 2, strPrice);
					list_data_.SetItemText(line, 3, strNum);
					list_data_.SetItemText(line, 4, strDate);
					list_data_.SetItemText(line, 4, strTime);
					rcs.MoveNext();
				}
				Cnn.Close();
			}
			
		}CATCH(CDBException, e){
			MessageBox(L"Data Error" + e->m_strError);
		}
		END_CATCH;

}
	




	


	void mainFrame::OnBnClickedBtnSort()
	{
		// TODO: Add your control notification handler code here
		TRY{
			list_data_.DeleteAllItems();
			CDatabase Cnn;
			CString sDriver = L"ODBC Driver 13 for SQL Server";
			CString strConnect = _T("ODBC;Driver={ODBC Driver 13 for SQL Server};Server=SM101\\SQL2012;Trusted_Connection=yes;Database=HouseDataBase;");
			Cnn.Open(NULL, false, false, strConnect);

			CRecordset rcs(&Cnn);
			CString strSql = _T("select * from DataHouseBase");
			if (SORTBY == FALSE){
				strSql.Format(L"select * from DataHouseBase ORDER BY Date ASC");
				SORTBY == TRUE;
			}
			else{
				strSql.Format(L"select * from DataHouseBase ORDER BY Date DESC");
				SORTBY == FALSE;
			}
			rcs.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
			int line = 0;
			while (!rcs.IsEOF()) {
				rcs.GetFieldValue(_T("ID"), strID);
				rcs.GetFieldValue(_T("Name"), strName);
				rcs.GetFieldValue(_T("Number"), strNum);
				rcs.GetFieldValue(_T("Price"), strPrice);
				rcs.GetFieldValue(_T("Date"), strDate);
				rcs.GetFieldValue(_T("Time"), strTime);
				list_data_.InsertItem(line, strID);
				list_data_.SetItemText(line, 1, strName);
				list_data_.SetItemText(line, 2, strPrice);
				list_data_.SetItemText(line, 3, strNum);
				list_data_.SetItemText(line, 4, strDate);
				list_data_.SetItemText(line, 5, strTime);

				line++;
				rcs.MoveNext();
			}
			Cnn.Close();

		}CATCH(CDBException, e){
			MessageBox(L"Data Error:" + e->m_strError);
		}
		END_CATCH;
	}


	void mainFrame::OnHdnItemclickListData(NMHDR *pNMHDR, LRESULT *pResult)
	{
		LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
		// TODO: Add your control notification handler code here
		MessageBox(L"Error");
		*pResult = 0;
	}


	void mainFrame::OnLvnBeginlabeleditListData(NMHDR *pNMHDR, LRESULT *pResult)
	{
		NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
		// TODO: Add your control notification handler code here

		*pResult = 0;
	}

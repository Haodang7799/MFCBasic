#pragma once
#include "afxwin.h"


// AddPage dialog

class AddPage : public CDialogEx
{
	DECLARE_DYNAMIC(AddPage)

public:
	AddPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddPage();

// Dialog Data
	enum { IDD = IDD_ADDPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit id_val_;
	CEdit name_val_;
	CEdit number_val_;
	CEdit price_val_;
	CEdit date_val_;
	afx_msg void OnBnClickedOk();
	CString strID;
	CString strName;
	CString strNumber;
	CString strPrice;
	CString strDate;
	CComboBox cbb_select;
	afx_msg void OnCbnSelendokCbSelect();
};

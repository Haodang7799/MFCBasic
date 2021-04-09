#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// mainFrame dialog

class mainFrame : public CDialogEx
{
	DECLARE_DYNAMIC(mainFrame)

public:
	mainFrame(CWnd* pParent = NULL);   // standard constructor
	virtual ~mainFrame();

// Dialog Data
	enum { IDD = IDD_MAINFRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnFind();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void ResetFillBox();
	
	CString strID = _T("");
	CString strName = _T("");
	CString strPrice = _T("");
	CString strNum = _T("");
	CString strDate = _T("");
	CString strTime = _T("");
public:
	BOOL CheckCreateTable = FALSE;
	BOOL SORTBY = FALSE;
	CListCtrl list_data_;

	CEdit id_val_;
	CEdit name_val_;
	CEdit number_val_;
	CEdit price_val_;
	CEdit date_val_;
	CMenu menu_bar;

	afx_msg void OnBnClickedBtnSort();
	afx_msg void OnHdnItemclickListData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnBeginlabeleditListData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void UpdateValue();
};

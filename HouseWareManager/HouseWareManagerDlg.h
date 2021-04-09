
// HouseWareManagerDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CHouseWareManagerDlg dialog
class CHouseWareManagerDlg : public CDialogEx
{
// Construction
public:
	CHouseWareManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HOUSEWAREMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLgin();
	CEdit id_val_;
	CEdit pw_val_;
	afx_msg void OnBnClickedBtnRgt();
	CMenu m_NewMenu;
	afx_msg void OnbnClicedExt_cmd();
};

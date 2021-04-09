#pragma once
#include "afxwin.h"


// RegisterPage dialog

class RegisterPage : public CDialogEx
{
	DECLARE_DYNAMIC(RegisterPage)

public:
	RegisterPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RegisterPage();

// Dialog Data
	enum { IDD = IDD_RGT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLoginRgp();
	afx_msg void OnBnClickedBtnRgtRgtp();
	CEdit input_id;
	CEdit input_pw;
	CEdit input_pw2;
};

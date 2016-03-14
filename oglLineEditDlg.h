
// oglLineEditDlg.h : header file
//

#pragma once
#include "LineEdit.h"

// CoglLineEditDlg dialog
class CoglLineEditDlg : public CDialogEx
{
// Construction
public:
	CoglLineEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_OGLLINEEDIT_DIALOG };

private:
	CLineEditControl m_oglLineEditWin;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
	HICON m_hIcon;

// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

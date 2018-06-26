
// tool_handle_countDlg.h : header file
//

#pragma once


// Ctool_handle_countDlg dialog
class Ctool_handle_countDlg : public CDialogEx
{
// Construction
public:
	Ctool_handle_countDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TOOL_HANDLE_COUNT_DIALOG };

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
	int m_edit_handle0;
	int m_edit_count0;
	afx_msg void OnBnClickedButtonCheck0();
};

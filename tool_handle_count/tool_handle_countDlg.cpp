
// tool_handle_countDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tool_handle_count.h"
#include "tool_handle_countDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct _SYSTEM_HANDLE_STATE
{
	DWORD r1;
	DWORD GrantedAccess;
	DWORD HandleCount;
	DWORD ReferenceCount;
	DWORD r5;
	DWORD r6;
	DWORD r7;
	DWORD r8;
	DWORD r9;
	DWORD r10;
	DWORD r11;
	DWORD r12;
	DWORD r13;
	DWORD r14;
} SYSTEM_HANDLE_STATE, *PSYSTEM_HANDLE_STATE;

typedef long (__stdcall *NTQUERYOBJECT)(
	HANDLE ObjectHandle,
	ULONG ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);

enum
{
	INVALID_HANDLE = -2,
	CHECK_FAILED,
	CHECK_SUCCEED
};

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


// Ctool_handle_countDlg dialog




Ctool_handle_countDlg::Ctool_handle_countDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctool_handle_countDlg::IDD, pParent)
	, m_edit_handle0(0)
	, m_edit_count0(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctool_handle_countDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctool_handle_countDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK0, &Ctool_handle_countDlg::OnBnClickedButtonCheck0)
END_MESSAGE_MAP()


// Ctool_handle_countDlg message handlers

BOOL Ctool_handle_countDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ctool_handle_countDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctool_handle_countDlg::OnPaint()
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
HCURSOR Ctool_handle_countDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int check_handle_count(HANDLE handle, int &count)
{
	NTQUERYOBJECT pfnNtQueryObject =
		reinterpret_cast<NTQUERYOBJECT>(GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQueryObject"));
	if (NULL == pfnNtQueryObject)
	{
		return CHECK_FAILED;
	}

	SYSTEM_HANDLE_STATE shs = {0};
	ULONG len = 0;

	long ret = pfnNtQueryObject(handle, 0, &shs, sizeof(shs), &len);
	if (0xC0000008 == ret)
	{
		return INVALID_HANDLE;
	}

	count = shs.ReferenceCount - 1;
	return CHECK_SUCCEED;
}

void Ctool_handle_countDlg::OnBnClickedButtonCheck0()
{
	// TODO: Add your control notification handler code here

	HANDLE handle = (HANDLE)GetDlgItemInt(IDC_EDIT_HANDLE0);

	int count = 0;
	int ret = check_handle_count(handle, count);
	if (INVALID_HANDLE == ret)
	{
		SetDlgItemText(IDC_EDIT_COUNT0, L"Invalid handle");
	}
	else if (CHECK_FAILED == ret)
	{
		AfxMessageBox(L"Query failed");
	}
	else
	{
		SetDlgItemInt(IDC_EDIT_COUNT0, count);
	}
}


// SimpleScannerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SimpleScanner.h"
#include "SimpleScannerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>
#include<fstream>
#include<sstream>
#include <afxstr.h>

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimpleScannerDlg dialog



CSimpleScannerDlg::CSimpleScannerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIMPLESCANNER_DIALOG, pParent)
	, txt_directory(_T(""))
	, txt_hex(_T(""))
{
	mutex = 1;
	count = 0;
	mutex_count = 1;
	mutex_flag_terminated = 1;
	flag_terminated_count = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleScannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_TXT_DIRECTORY, txt_directory);
	DDX_Text(pDX, IDC_TXT_HEX, txt_hex);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Text(pDX, IDC_TXT_DIRECTORY, txt_directory);
}

BEGIN_MESSAGE_MAP(CSimpleScannerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CSimpleScannerDlg::OnBnClickedBtnStart)
	ON_MESSAGE(WM_COMPLETE, &CSimpleScannerDlg::OnComplete)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CSimpleScannerDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CSimpleScannerDlg message handlers

BOOL CSimpleScannerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	//txt_hex = _T("6D656F77");
	//txt_directory = _T("D:\\");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleScannerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleScannerDlg::OnPaint()
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
HCURSOR CSimpleScannerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//sub method
ULONGLONG GetFileSize(const CString& filePath) {
	CFileFind finder;
	if (finder.FindFile(filePath)) {
		finder.FindNextFile();
		ULONGLONG fileSize = finder.GetLength();
		finder.Close();
		return fileSize;
	}
	return 0;
}
void CSimpleScannerDlg::LockControls() {
	auto pEditBox_Hexa = GetDlgItem(IDC_TXT_HEX);
	auto pButton_Start = GetDlgItem(IDC_BTN_START);
	auto pText_Directory = GetDlgItem(IDC_TXT_DIRECTORY);
	pText_Directory->EnableWindow(FALSE);
	pEditBox_Hexa->EnableWindow(FALSE);
	pButton_Start->EnableWindow(FALSE);
}

void CSimpleScannerDlg::UnlockControls() {
	auto pEditBox_Hexa = GetDlgItem(IDC_TXT_HEX);
	auto pButton_Start = GetDlgItem(IDC_BTN_START);
	auto pText_Directory = GetDlgItem(IDC_TXT_DIRECTORY);
	pText_Directory->EnableWindow(TRUE);
	pEditBox_Hexa->EnableWindow(TRUE);
	pButton_Start->EnableWindow(TRUE);
}


std::string CSimpleScannerDlg::toBase(unsigned i, unsigned base)
{
	const std::string DIGITS = "0123456789ABCDEF";
	return i ? toBase(i / base, base) + DIGITS[i % base] : "";
}

void CSimpleScannerDlg::queue_Push(LPCTSTR pstr) {
	CFileFind finder;
	CString strWildcard(pstr);
	strWildcard += _T("\\*");
	BOOL bWorking = finder.FindFile(strWildcard);
	//if (!bWorking) {
	//	// something's wrong, print the current error message
	//	TCHAR buf[256] = { 0 };
	//	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	//		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	//		buf, sizeof(buf), NULL);
	//	AfxMessageBox(buf);
	//	
	//}
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
			continue;

		else if (finder.IsDirectory())
		{
			CString str = finder.GetFilePath();
			queue_Push(str);
		}
		else {
			CString cs = finder.GetFilePath();
			if (GetFileSize(cs) < 50000000) {
				q.push_back(cs);
			}
		}
	}
	finder.Close();
}



void CSimpleScannerDlg::queue_Pop() {
	while (1) {
		while (mutex == 0 || q.empty() == true) Sleep(20);
		if (q.front() != _T("AA@#$%!")) {
			mutex--;
			CString cs = q.front();
			q.pop_front();
			q.shrink_to_fit();
			mutex++;

			int length = cs.GetLength();
			char* str = (LPSTR)(LPCTSTR)cs;

			std::string filePath;
			for (int i = 0; i < length * 2; i += 2) {
				filePath = filePath + str[i];
			}

			std::ifstream file(filePath, std::ios::binary);
			std::string myhex;
			std::stringstream hexStream;
			int width = toBase(255, 16).size();
			char c;
			while (file.get(c))
			{
				hexStream << std::setw(width) << toBase((unsigned)c, 16);
			}
			myhex = hexStream.str();
			CString hexCode(myhex.c_str());
			int index = hexCode.Find(txt_hex);
			if (index != -1) {
				while (mutex_count == 0) Sleep(10);
				mutex_count--;
				count++;
				mutex_count++;
				list.AddString(_T("[+]") + cs);
				found.push(_T("[+]") + cs);
			}
			else {
				list.AddString(_T("[-]") + cs);
			}
		}
		else if (q.front() == _T("AA@#$%!")) {
			while (mutex_count == 0) Sleep(10);
			mutex_flag_terminated--;
			flag_terminated_count++;
			mutex_flag_terminated++;
			
			break;
		}
	}
}

UINT CSimpleScannerDlg::startProcessPop(LPVOID Param) {

	CSimpleScannerDlg* ourWnd = reinterpret_cast<CSimpleScannerDlg*>(Param);
	ourWnd->queue_Pop();
	return 0;
}


void CSimpleScannerDlg::real_Recurse(LPCTSTR pstr) {
	for (int i = 0; i < 5; i++) {
		AfxBeginThread(startProcessPop, this);
	}
	queue_Push(pstr);
	q.push_back(_T("AA@#$%!"));
	
	while (flag_terminated_count != 5) Sleep(100);
	
	PostMessageW(WM_COMPLETE, count);
	list.ResetContent();
	list.AddString(_T("Danh sách các file tìm được: "));
	while (found.empty() == false) {
		list.AddString(found.front());
		found.pop();
	}
}


UINT CSimpleScannerDlg::startProcessProc_multithread(LPVOID Param) {

	CSimpleScannerDlg* ourWnd = reinterpret_cast<CSimpleScannerDlg*>(Param);
	//ourWnd->LockControl();
	ourWnd->real_Recurse(ourWnd->txt_directory);

	//ourWnd->PostMessageW(WM_COMPLETE, ourWnd->count);
	return 0;
}

void CSimpleScannerDlg::Trace(const char* pszFileName) {
	TRACE("\n%s\n", pszFileName);
}

void CSimpleScannerDlg::OnBnClickedBtnStart()
{
	count = 0;
	mutex_count = 1;
	mutex = 1;
	flag_terminated_count = 0;
	while (q.empty() != true) {
		q.pop_front();
	}
	// TODO: Add your control notification handler code here
	//UpdateData(FALSE);
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	LockControls();
	list.ResetContent();
	CFileFind finder;

	//AfxBeginThread(startProcessProc, this);
	AfxBeginThread(startProcessProc_multithread, this);
	//UnlockControls();
}

afx_msg LRESULT CSimpleScannerDlg::OnComplete(WPARAM wParam, LPARAM lParam)
{
	CString res;
	res.Format(TEXT("Chương trình đã quét xong. Tìm thấy tất cả %d file chứa signature!"), wParam);
	AfxMessageBox(res, MB_OK);
	UnlockControls();
	return 0;
}

void CSimpleScannerDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	exit(0);
}


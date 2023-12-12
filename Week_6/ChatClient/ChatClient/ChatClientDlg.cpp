
// ChatClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include<string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>


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


// CChatClientDlg dialog



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)
	, m_sUserName(_T(""))
	, m_sMsg(_T(""))
{
	m_sIPAddress = _T("127.0.0.1");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Display);
	DDX_Text(pDX, IDC_EDIT1, m_sUserName);
	DDX_Text(pDX, IDC_EDIT2, m_sMsg);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CChatClientDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CChatClientDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatClientDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatClientDlg::OnPaint()
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnBnClickedButtonConnect()
{
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_sUserName == _T("")) {
		AfxMessageBox(_T("Name must not be left blank."));
		return;
	}
	HELP();
	if (AfxSocketInit() == FALSE)
	{
		AfxMessageBox(_T("Failed to Initialize Sockets"));
		return;
	}

	if (m_Client.Create() == FALSE)
	{
		MessageBox(_T("Failed to Create Socket"));
		return;

	}
	if (m_Client.Connect(m_sIPAddress, 1001) == FALSE)
	{
		MessageBox(_T("Failed to Connect"));
		return;

	}
	m_Client.pDlg = this;

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	userinfo uinf;
	CT2A ascii_1(m_sUserName);
	strcpy_s(uinf.cUserName, ascii_1);
	CT2A ascii_2(_T(" joins server."));
	strcpy_s(uinf.csMsg, ascii_2);
	char* buff = (char*)&uinf;
	m_Client.Send(buff, sizeof(userinfo));
}


void CChatClientDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	userinfo uinf;
	CT2A ascii_1(m_sUserName);
	strcpy_s(uinf.cUserName, ascii_1);
	CT2A ascii_2(_T(" exits server."));
	strcpy_s(uinf.csMsg, ascii_2);
	char* buff = (char*)&uinf;
	m_Client.Send(buff, sizeof(userinfo));
	m_Client.ShutDown(2);
	m_Client.Close();

	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
}


void CChatClientDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_sMsg == _T(":CLEAR")) {
		m_Display.ResetContent();
	}
	if (m_sMsg.GetLength() > 99) {
		AfxMessageBox(_T("The message is too long"));
		return;
	}
	userinfo uinf;
	CT2A ascii_1(m_sUserName);
	strcpy_s(uinf.cUserName, ascii_1);
	CT2A ascii_2(m_sMsg);
	strcpy_s(uinf.csMsg, ascii_2);
	char* buff = (char*)&uinf;
	m_Client.Send(buff, sizeof(userinfo));
	m_sMsg = _T("");
	UpdateData(FALSE);
}

void CChatClientDlg::AddMsg(userinfo* udata)
{
	char* second_str = "Admin_nick_!@#$";
	char* third_str = "Admin_quit_!@#$";
	char* fourth_str = "duplicated!@#$_nae";
	char* fifth_str = "Admin_help_!@#$";
	char* sixth_str = "Admin_error_!@#$";
	if (strcmp(udata->cUserName, second_str) == 0){
		size_t sz2;                          // save converted string's length + 1
		wchar_t output2[20] = L"";          // return data, result is CString data
		mbstowcs_s(&sz2, output2, 20, udata->csMsg, 20); // converting function
		CString cst2 = output2;
		AfxMessageBox(cst2);
		m_sUserName = cst2;
		UpdateData(FALSE);
	}
	else if (strcmp(udata->cUserName, third_str) == 0) {
		m_Display.ResetContent();
		m_Client.ShutDown(2);
		m_Client.Close();
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(true);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	}
	else if (strcmp(udata->cUserName, fourth_str) == 0) {
		AfxMessageBox(_T("Duplicate name."));
		m_Client.ShutDown(2);
		m_Client.Close();
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(true);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	}
	else if (strcmp(udata->cUserName, fifth_str) == 0) {
		HELP();
	}
	else if (strcmp(udata->cUserName, sixth_str) == 0) {
		AfxMessageBox(_T("ERR_UNKNOWNCOMMAND"));
	}
	else {
		CString sDisplay = _T("");
		size_t sz1;                          // save converted string's length + 1
		wchar_t output1[1000] = L"";          // return data, result is CString data
		mbstowcs_s(&sz1, output1, 1000, udata->cUserName, 1000); // converting function
		CString cst1 = output1;
		size_t sz2;                          // save converted string's length + 1
		wchar_t output2[1000] = L"";          // return data, result is CString data
		mbstowcs_s(&sz2, output2, 1000, udata->csMsg, 1000); // converting function
		CString cst2 = output2;
		sDisplay += output1;
		sDisplay += _T(":");
		sDisplay += output2;
		m_Display.AddString(sDisplay);
	}
}

void CChatClientDlg::HELP() {
	CString List_commands(_T(">>>List Commands: "));
	CString NICK(_T(">>>>>>NICK:       < : >NICK <SPACES> <NICKNAME>"));
	CString QUIT(_T(">>>>>>QUIT:       < : >QUIT <SPACES>"));
	CString PART(_T(">>>>>>PART : < : >PART"));
	CString LIST(_T(">>>>>>LIST : < : >LIST"));
	CString JOIN(_T(">>>>>>JOIN : < : >JOIN <SPACES> <CHANNEL_NAME>"));
	CString PRIVMSG(">>>>>>PRIVMSG : < : >PRIVMSG <SPACES> @<USERNAME> <SPACES> <MESSAGES>");
	CString WHO(">>>>>>WHO:       < : >WHO <SPACES> @<USERNAME>");
	CString HHELP(">>>>>>HELP : < : >HELP");
	CString CLEAR(_T(">>>>>>CLEAR : < : >CLEAR"));
	m_Display.AddString(List_commands);
	m_Display.AddString(NICK);
	m_Display.AddString(QUIT);
	m_Display.AddString(PART);
	m_Display.AddString(PRIVMSG);
	m_Display.AddString(JOIN);
	m_Display.AddString(LIST);
	m_Display.AddString(WHO);
	m_Display.AddString(HHELP);
	m_Display.AddString(CLEAR);
}




















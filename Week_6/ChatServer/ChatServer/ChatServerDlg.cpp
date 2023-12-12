// ChatServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CChatServerDlg dialog



CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
{
	flag_error = true;
	count = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Display);
	DDX_Text(pDX, IDC_EDIT1, m_Msg);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatServerDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_START, &CChatServerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CChatServerDlg::OnBnClickedButtonStop)
	ON_LBN_SELCHANGE(IDC_LIST1, &CChatServerDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CChatServerDlg message handlers

BOOL CChatServerDlg::OnInitDialog()
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

void CChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatServerDlg::OnPaint()
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatServerDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	userinfo uinf;

	strcpy_s(uinf.cUserName, "Server");
	CT2A ascii(m_Msg);
	strcpy_s(uinf.csMsg, ascii);

	char* buff = (char*)&uinf;
	int size = m_Server.m_Clients.size() - 1;
	m_Server.m_Clients.at(0)->Send(buff, sizeof(userinfo));
	m_Msg = _T("");
	UpdateData(FALSE);
}



void CChatServerDlg::AddMsg(userinfo* udata)
{
	char* str = " exits server.";
	if (strcmp(udata->csMsg, str)==0) {
		PART(udata);
		std::vector<CClientSocket*>::iterator it;
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (m_Server.m_Clients.at(i)->name == udata->cUserName) {
				CString mDisplay;
				mDisplay += _T("User ");
				CString temp(m_Server.m_Clients.at(i)->name.c_str());
				mDisplay += temp;
				mDisplay += _T(" left server.");
				m_Server.m_Clients.erase(m_Server.m_Clients.begin() + i);
				m_Display.AddString(mDisplay);
			}
		}
	}
	count = 0;
	//CString sDisplay;
	for (int i = 0; i < m_Server.m_Clients.size(); i++) {
		if (udata->cUserName == m_Server.m_Clients.at(i)->name) {
			count++;
			if (count == 2) {
				userinfo uinf;
				strcpy_s(uinf.cUserName, "duplicated!@#$_nae");
				strcpy_s(uinf.csMsg, "");
				char* buff = (char*)&uinf;
				m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
				m_Server.m_Clients.erase(m_Server.m_Clients.begin() + i);
				count--;
			}
		}
	}
	if (udata->csMsg[0] == ':') {
		flag_error = true;
		NICK(udata);
		QUIT(udata);
		JOIN(udata);
		PART(udata);
		LIST(udata);
		PRIVMSG_INDIVIDUAL(udata);
		WHO(udata);
		HELP(udata);
		PRIVMSG_CHANNEL(udata);
		if (udata->csMsg[1] != 'N' && udata->csMsg[1] != 'Q'
			&& udata->csMsg[1] != 'J' && udata->csMsg[1] != 'P'
			&& udata->csMsg[1] != 'L' && udata->csMsg[1] != 'W'
			&& udata->csMsg[1] != 'H' && udata->csMsg[1] != 'C') {
			sendError(udata);
		}
		  
	}
	else {
		channelSend(udata);
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


void CChatServerDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	if (AfxSocketInit() == FALSE)
	{
		AfxMessageBox(_T("Failed to Initialize Sockets"));
		return;
	}

	//m_Server.m_Client.pDlg = this;
	m_Server.pDlg = this;

	if (m_Server.Create(1001) == FALSE)
	{
		MessageBox(_T("Failed to create"));
		return;
	}

	if (m_Server.Listen(5) == FALSE)
	{
		MessageBox(_T("Failed"));
		return;
	}


	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
}


void CChatServerDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	int size = m_Server.m_Clients.size();
	for (int i = 0; i < size; i++) {
		m_Server.m_Clients.at(0)->ShutDown(2);
	}
	m_Server.Close();
	m_Server.m_Clients.clear();
	channels.clear();
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	m_Msg = _T("");
	UpdateData(FALSE);
}


void CChatServerDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CChatServerDlg::NICK(userinfo* udata) {
	//NICK
	flag_error = false;
	if (udata->csMsg[1] == 'N' && udata->csMsg[2] == 'I'
		&& udata->csMsg[3] == 'C' && udata->csMsg[4] == 'K'
		&& udata->csMsg[5] == ' ' && udata->csMsg[6] == '@') {
		std::string name;
		int count = 0;
		int idx = 7;
		while (1) {

			if (udata->csMsg[idx] == ' ' || udata->csMsg[idx] == '\0') {
				break;
			}
			name += udata->csMsg[idx];
			idx++;
		}
		idx++;
		std::string newName;
		while (udata->csMsg[idx] != '\0') {
			newName += udata->csMsg[idx];
			idx++;
		}
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (newName == m_Server.m_Clients.at(i)->name) {
				userinfo uinf;
				strcpy_s(uinf.cUserName, "Server");
				strcpy_s(uinf.csMsg, "Duplicate name");

				char* buff = (char*)&uinf;
				for (int j = 0; j < m_Server.m_Clients.size(); j++) {
					if (name == m_Server.m_Clients.at(j)->name) {
						m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
					}
				}
				return;
			}
		}
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (name == m_Server.m_Clients.at(i)->name) {
				m_Server.m_Clients.at(i)->name = newName;
				userinfo uinf;
				strcpy_s(uinf.cUserName, "Admin_nick_!@#$");
				//CT2A ascii(m_Msg);
				const char* cstr = newName.c_str();
				strcpy_s(uinf.csMsg, cstr);
				char* buff = (char*)&uinf;
				int size = m_Server.m_Clients.size();
				m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
			}
		}
	}
}

void CChatServerDlg::QUIT(userinfo* udata) {
	flag_error = false;
	std::string newName("");
	if (udata->csMsg[1] == 'Q' && udata->csMsg[2] == 'U'
		&& udata->csMsg[3] == 'I' && udata->csMsg[4] == 'T') {
		std::string name;
		int idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			name += udata->cUserName[idx];
			idx++;
		}
		std::vector<CClientSocket*> ::iterator it;
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (name == m_Server.m_Clients.at(i)->name) {
				userinfo uinf;
				strcpy_s(uinf.cUserName, "Admin_quit_!@#$");
				const char* cstr = newName.c_str();
				strcpy_s(uinf.csMsg, cstr);

				char* buff = (char*)&uinf;
				int size = m_Server.m_Clients.size() - 1;
				m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
				CString mDisplay;
				mDisplay += _T("User ");
				CString temp(m_Server.m_Clients.at(i)->name.c_str());
				mDisplay += temp;
				mDisplay += _T(" left server.");
				m_Display.AddString(mDisplay);
				it = m_Server.m_Clients.begin();
				m_Server.m_Clients.erase(it + i);

			}

		}
	}
}

void CChatServerDlg::JOIN(userinfo* udata) {
	flag_error = false;
	if (udata->csMsg[1] == 'J' && udata->csMsg[2] == 'O'
		&& udata->csMsg[3] == 'I' && udata->csMsg[4] == 'N'
		&& udata->csMsg[5] == ' ') {
		//lay ten
		std::string name;
		int idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			name += udata->cUserName[idx];
			idx++;
		}
		//lay ten channel
		std::string channel_name;
		idx = 6;
		while (1) {

			if (udata->csMsg[idx] == ' ' || udata->csMsg[idx] == '\0') {
				break;
			}
			channel_name += udata->csMsg[idx];
			idx++;
		}
		bool flag = false;

		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			//duyet tu dau den cuoi m_Clients
			if (name == m_Server.m_Clients.at(i)->name) {
				//tim thay name
				if (m_Server.m_Clients.at(i)->flag_in_channel == false) {
					for (int j = 0; j < channels.size(); j++) {
						if (channels.at(j).sName == channel_name) {
							flag = true;
							m_Server.m_Clients.at(i)->flag_in_channel = true;
							channels.at(j).channelClient.push_back(m_Server.m_Clients.at(i));
							CString mDisplay;
							mDisplay += _T("User ");
							CString temp(m_Server.m_Clients.at(i)->name.c_str());
							mDisplay += temp;
							mDisplay += _T(" join channel ");
							CString temp2(channel_name.c_str());
							mDisplay += temp2;
							mDisplay += _T(".");
							m_Display.AddString(mDisplay);
							break;
						}
					}
					if (flag == false) {
						channel c;
						m_Server.m_Clients.at(i)->flag_in_channel = true;
						c.sName = channel_name;
						c.channelClient.push_back(m_Server.m_Clients.at(i));
						channels.push_back(c);
						CString mDisplay;
						mDisplay += _T("User ");
						CString temp(m_Server.m_Clients.at(i)->name.c_str());
						mDisplay += temp;
						mDisplay += _T(" join channel ");
						CString temp2(channel_name.c_str());
						mDisplay += temp2;
						mDisplay += _T(".");
						m_Display.AddString(mDisplay);
					}
					
				}
				break;
			}

		}
	}
}

void CChatServerDlg::PART(userinfo* udata) {
	flag_error = false;
	if (udata->csMsg[1] == 'P' && udata->csMsg[2] == 'A'
		&& udata->csMsg[3] == 'R' && udata->csMsg[4] == 'T') {
		std::string name;
		int idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			name += udata->cUserName[idx];
			idx++;
		}
		std::vector<CClientSocket*> ::iterator it;
		int size1 = channels.size();
		
		for (int j = 0; j < size1; j++) {
			it = channels.at(j).channelClient.begin();
			int size2 = channels.at(j).channelClient.size();
			for (int k = 0; k < size2; k++) {
				if (channels.at(j).channelClient.at(k)->name == name) {
					it += k;
					channels.at(j).channelClient.at(k)->flag_in_channel = false;
					channels.at(j).channelClient.erase(it);
					break;
				}
			}
		}

		for (int i=0; i<channels.size();i++) {
			if (channels.at(i).channelClient.size() == 0) {
				channels.erase(channels.begin() + i);
				break;
			}
		}
	}

}
 
void CChatServerDlg::LIST(userinfo* udata) {
	flag_error = false;
	if (udata->csMsg[1] == 'L' && udata->csMsg[2] == 'I'
		&& udata->csMsg[3] == 'S' && udata->csMsg[4] == 'T') {
		std::string name;
		int idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			name += udata->cUserName[idx];
			idx++;
		}

		
		for (int i = 0; i < channels.size(); i++) {
			AfxMessageBox(_T("channel access"));
			std::string message;
			std::string channel_name = channels.at(i).sName;
			int size = channels.at(i).channelClient.size();
			std::string str_size = std::to_string(size);
			message = "";
			message += " Channel ";
			message += channel_name;
			message += ": ";
			message += str_size;
			message += " people.";
			userinfo uinf;
			strcpy_s(uinf.cUserName, "Server");
			//CT2A ascii(m_Msg);
			const char* cstr = message.c_str();
			strcpy_s(uinf.csMsg, cstr);
			char* buff = (char*)&uinf;
			for (int i = 0; i < m_Server.m_Clients.size(); i++) {
				if (m_Server.m_Clients.at(i)->name == name) {
					m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
				}
			}
		}			
		
	}
}
 
void CChatServerDlg::PRIVMSG_INDIVIDUAL(userinfo* udata) {
	flag_error = false;
	if (udata->csMsg[1] == 'P' && udata->csMsg[2] == 'R'
		&& udata->csMsg[3] == 'I' && udata->csMsg[4] == 'V'
		&& udata->csMsg[5] == 'M' && udata->csMsg[6] == 'S'
		&& udata->csMsg[7] == 'G' && udata->csMsg[8] == ' '
		&& udata->csMsg[9] == '@') {
		std::string received_name;
		int idx = 10;
		while (1) {

			if (udata->csMsg[idx] == ' ' || udata->csMsg[idx] == '\0') {
				break;
			}
			received_name += udata->csMsg[idx];
			idx++;
		}
		std::string message;
		idx++;
		while (1) {
			if (udata->csMsg[idx] == '\0') {
				break;
			}
			message += udata->csMsg[idx];
			idx++;
		}

		std::string sent_name;
		idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			sent_name += udata->cUserName[idx];
			idx++;
		}


		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (received_name == m_Server.m_Clients.at(i)->name) {
				userinfo uinf;
				const char* cstr1 = sent_name.c_str();
				strcpy_s(uinf.cUserName, cstr1);
				const char* cstr = message.c_str();
				strcpy_s(uinf.csMsg, cstr);

				char* buff = (char*)&uinf;
				int size = m_Server.m_Clients.size() - 1;
				m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
			}

		}

	}
}


void CChatServerDlg::WHO(userinfo* udata) {
	if (udata->csMsg[1] == 'W' && udata->csMsg[2] == 'H'
		&& udata->csMsg[3] == 'O' && udata->csMsg[4] == ' '
		&& udata->csMsg[5] == '@') {
		std::string name;
		int idx = 6;
		while (1) {

			if (udata->csMsg[idx] == ' ' || udata->csMsg[idx] == '\0') {
				break;
			}
			name += udata->csMsg[idx];
			idx++;
		}
		bool undefined = true;
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (m_Server.m_Clients.at(i)->name == name) {
				undefined = false;
				break;
			}
		}
		if (undefined == true) return;
		std::string send_name;
		int idx1 = 0;
		while (1) {
			if (udata->cUserName[idx1] == '\0') {
				break;
			}
			send_name += udata->cUserName[idx1];
			idx1++;
		}
		bool flag = false;
		std::string channel_name;
		for (int i = 0; i < channels.size(); i++) {
			for (int j = 0; j < channels.at(i).channelClient.size(); j++) {
				if (channels.at(i).channelClient.at(j)->name == name) {
					flag = true;
					channel_name = channels.at(i).sName;
				}
			}
		}
		if (flag == false) {
			channel_name = "none";
		}
		std::string message;
		message += "user name: ";
		message += name;
		message += "    ";
		message += "channel: ";
		message += channel_name;

		userinfo uinf;
		strcpy_s(uinf.cUserName, "Server");
		//CT2A ascii(m_Msg);
		const char* cstr = message.c_str();
		strcpy_s(uinf.csMsg, cstr);

		char* buff = (char*)&uinf;
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (m_Server.m_Clients.at(i)->name == send_name) {
				m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
			}
		}
		
	}
}

void CChatServerDlg::HELP(userinfo* udata) {
	flag_error = false;
	if (udata->csMsg[1] == 'H' && udata->csMsg[2] == 'E'
		&& udata->csMsg[3] == 'L' && udata->csMsg[4] == 'P') {

		std::string name;
		int idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			name += udata->cUserName[idx];
			idx++;
		}

		userinfo uinf;
		strcpy_s(uinf.cUserName, "Admin_help_!@#$");
		strcpy_s(uinf.csMsg, "");

		char* buff = (char*)&uinf;
		for (int i = 0; i < m_Server.m_Clients.size(); i++) {
			if (m_Server.m_Clients.at(i)->name == name) {
				m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
				
			}
		}
	}
}

void CChatServerDlg::channelSend(userinfo* udata) {
	for (int i = 0; i < channels.size(); i++) {
		for (int j = 0; j < channels.at(i).channelClient.size(); j++) {
			if (channels.at(i).channelClient.at(j)->name == udata->cUserName) {
				//no o trong channel channels.at(i)
				for (int k = 0; k < channels.at(i).channelClient.size(); k++) {
					for (int l = 0; l < m_Server.m_Clients.size(); l++) {
						if (channels.at(i).channelClient.at(k)==m_Server.m_Clients.at(l)) {
							userinfo uinf;
							strcpy_s(uinf.csMsg, udata->csMsg);
							strcpy_s(uinf.cUserName, udata->cUserName);
							char* buff = (char*)&uinf;
							m_Server.m_Clients.at(l)->Send(buff, sizeof(userinfo));
							break;
						}
					}
				}
				return;
			}
		}
	}
}

void CChatServerDlg::PRIVMSG_CHANNEL(userinfo* udata) {
	flag_error = false;
	if (udata->csMsg[1] == 'P' && udata->csMsg[2] == 'R'
		&& udata->csMsg[3] == 'I' && udata->csMsg[4] == 'V'
		&& udata->csMsg[5] == 'M' && udata->csMsg[6] == 'S'
		&& udata->csMsg[7] == 'G' && udata->csMsg[8] == ' '
		&& udata->csMsg[9] == '#') {
		std::string received_channel;
		int idx = 10;
		while (1) {

			if (udata->csMsg[idx] == ' ' || udata->csMsg[idx] == '\0') {
				break;
			}
			received_channel += udata->csMsg[idx];
			idx++;
		}
		idx++;
		std::string message;
		idx++;
		while (1) {
			if (udata->csMsg[idx] == '\0') {
				break;
			}
			message += udata->csMsg[idx];
			idx++;
		}
		std::string sent_name;
		idx = 0;
		while (1) {
			if (udata->cUserName[idx] == '\0') {
				break;
			}
			sent_name += udata->cUserName[idx];
			idx++;
		}

		for (int i = 0; i < channels.size(); i++) {
			if (channels.at(i).sName == received_channel) {
				for (int j = 0; j < channels.at(i).channelClient.size(); j++) {
					userinfo uinf;
					const char* cstr1 = sent_name.c_str();
					strcpy_s(uinf.cUserName, cstr1);
					const char* cstr = message.c_str();
					strcpy_s(uinf.csMsg, cstr);

					char* buff = (char*)&uinf;
					int size = m_Server.m_Clients.size() - 1;
					channels.at(i).channelClient.at(j)->Send(buff, sizeof(userinfo));
				}
			}
		}
	}
}

void CChatServerDlg::sendError(userinfo* udata) {
	std::string name;
	name = getName1(udata, 0);
	for (int i = 0; i < m_Server.m_Clients.size(); i++) {
		if (m_Server.m_Clients.at(i)->name == name) {
			userinfo uinf;
			strcpy_s(uinf.cUserName, "Admin_error_!@#$");
			strcpy_s(uinf.csMsg, "");

			char* buff = (char*)&uinf;
			m_Server.m_Clients.at(i)->Send(buff, sizeof(userinfo));
		}
	}
	
}

std::string CChatServerDlg::getName1(userinfo* udata, int idx) {
	std::string name;
	//int idx = 0;
	while (1) {
		if (udata->cUserName[idx] == '\0') {
			break;
		}
		name += udata->cUserName[idx];
		idx++;
	}
	return name;
}

std::string CChatServerDlg::getName2(userinfo* udata, int idx) {
	std::string name;
	while (1) {

		if (udata->csMsg[idx] == ' ' || udata->csMsg[idx] == '\0') {
			break;
		}
		name += udata->csMsg[idx];
		idx++;
	}
	return name;
}
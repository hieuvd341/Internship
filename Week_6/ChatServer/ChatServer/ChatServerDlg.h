
// ChatServerDlg.h : header file
//

#pragma once
#include "Userdata.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include<iostream>
#include<queue>
#include<vector>


// CChatServerDlg dialog
class CChatServerDlg : public CDialogEx
{
// Construction
public:
	void AddMsg(userinfo* udata);
	CServerSocket m_Server;
	std::vector<channel> channels;
	CChatServerDlg(CWnd* pParent = nullptr);	// standard constructor
	//void Accept();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER_DIALOG };
#endif

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
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	DECLARE_MESSAGE_MAP()
public:
	
	CListBox m_Display;
	CString m_Msg;
	afx_msg void OnLbnSelchangeList1();
public:
	void NICK(userinfo* udata);
	void QUIT(userinfo* udata);
	void JOIN(userinfo* udata);
	void PART(userinfo* udata);
	void LIST(userinfo* udata);
	void PRIVMSG_INDIVIDUAL(userinfo* udata);
	void PRIVMSG_CHANNEL(userinfo* udata);
	void WHO(userinfo* udata);
	void HELP(userinfo* udata);
	void channelSend(userinfo* udata);
	void sendError(userinfo* udata);
private:
	int count;
	bool flag_error;
	std::string getName1(userinfo* udata, int idx);
	std::string getName2(userinfo* udata, int idx);
};

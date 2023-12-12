#include "pch.h"
#include "ClientSocket.h"
#include "Userdata.h"
#include "ChatClientDlg.h"
CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	char buff[1000];
	int br = Receive(buff, 1000);
	buff[br] = '\0';


	userinfo* udata;
	udata = (userinfo*)buff;
	((CChatClientDlg*)pDlg)->AddMsg(udata);

	CSocket::OnReceive(nErrorCode);
}
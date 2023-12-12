#pragma once
#include "ClientSocket.h"
#include<vector>
class CServerSocket : public CSocket
{
public:
	CServerSocket();
	~CServerSocket();
public:

	CDialog* pDlg;
	 //CClientSocket m_Client;
	 std::vector<CClientSocket*>m_Clients;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
public:
	virtual void OnAccept(int nErrorCode);
};


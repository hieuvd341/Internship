#include "pch.h"
#include "ServerSocket.h"
//#include "stdafx.h"
#include "ChatServer.h"
#include "ServerSocket.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions

void CServerSocket::OnAccept(int nErrorCode)
{
    if (nErrorCode == 0) {
        // Successfully accepted an incoming connection

        // Create a new socket for the accepted client
        CClientSocket* pClientSocket = new CClientSocket;

        if (Accept(*pClientSocket)) {
            pClientSocket->pDlg = this->pDlg;
            
            // Handle the new client connection here.
            // Add pClientSocket to m_clients to manage multiple clients
            m_Clients.push_back(pClientSocket);
            (*pClientSocket).flag_in_channel = false;
            pClientSocket->pDlg->UpdateData(TRUE);
        }
        else {
            // Failed to accept the client connection, so clean up the socket.
            delete pClientSocket;
        }
    }
    CSocket::OnAccept(nErrorCode);

}

#pragma once
#if _MSC_VER > 1000
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//

#include "Afxsock.h"
class CClientSocket :public CSocket
{
	// Attributes
public:

	// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();

	// Overrides
public:

	CDialog* pDlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};


#pragma once
#include "Afxsock.h" 
#include <string>
#include<iostream>
class CClientSocket : public CSocket
{
	// Attributes
public:
	std::string name;
	bool flag_in_channel;
	// Operations
public:
	CClientSocket();
	~CClientSocket();
	CClientSocket::CClientSocket(const CClientSocket&) = delete;
	CClientSocket& operator=(const CClientSocket&) = delete;

	// Overrides
public:
	CDialog* pDlg;

public:
	virtual void OnReceive(int nErrorCode);

// Implementation
protected:
};

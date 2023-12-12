
// SimpleScannerDlg.h : header file
//

#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<mutex>
#include <afxstr.h>
#define WM_COMPLETE (WM_USER + 1)

// CSimpleScannerDlg dialog
class CSimpleScannerDlg : public CDialogEx
{
// Construction
public:
	CSimpleScannerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMPLESCANNER_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	static UINT startProcessProc_multithread(LPVOID);
	static UINT startProcessPop1(LPVOID);
	static UINT startProcessPop2(LPVOID);
	static UINT startProcessPop3(LPVOID);
	afx_msg void OnBnClickedBtnStart();
//	CString txt_directory;
	void queue_Pop();
	static UINT startProcessPop(LPVOID);


	CString txt_hex;
	CListBox list;
	void real_Recurse(LPCTSTR);
	void UnlockControls();
	void LockControls();
	static std::string toBase(unsigned, unsigned);
	afx_msg LRESULT OnComplete(WPARAM, LPARAM);
	std::deque<CString>q;
	std::queue<CString>found;
	void queue_Push(LPCTSTR);
	//int mutex;
	std::atomic_int mutex;
	std::atomic_int mutex_count;
	int count;
	std::atomic_int mutex_flag_terminated;
	std::atomic_int flag_terminated_count;
	CString txt_directory;
	afx_msg void OnBnClickedBtnExit();
	
	static void CSimpleScannerDlg::Trace(const char* pszFileName);
};

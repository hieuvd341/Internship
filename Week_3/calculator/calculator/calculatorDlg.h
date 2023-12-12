
// calculatorDlg.h : header file
//

#pragma once


// CcalculatorDlg dialog
class CcalculatorDlg : public CDialogEx
{
// Construction
public:
	CcalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
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
	afx_msg void OnBnClickedButton11();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	CString plus(CString, CString);
	CString sub(CString, CString);
	CString mul(CString, CString);
	CString div(CString, CString);
	CString pretty(CString);
	CString inout;
	CString history;
	CString result ;
	CString buffer;
	bool flag_number;
	bool flag_operator;
	bool flag_equal;
	bool flag_dot;
	int dot_count;
	int operator_count;
	char last_operator;
	int equal_count;
	int negate_count;
	int reciproc_count;
	bool exception;
	CString tmp_result;
	CString tmp_buffer;
	CString tmp_history;
	CString tmp_inout;
	bool tmp_flag_number;
	bool tmp_flag_operator;
	bool tmp_flag_equal;
	bool tmp_flag_dot;
	int tmp_dot_count;
	int tmp_operator_count;
	char tmp_last_operator;
	int tmp_equal_count;
	int tmp_negate_count;
	int tmp_reciproc_count;

	CString memory;
};
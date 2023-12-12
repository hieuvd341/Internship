
// calculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"
#include<sstream>

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


// CcalculatorDlg dialog



CcalculatorDlg::CcalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, inout(_T("0"))
	, history(_T(""))
	, result(_T("0"))
	,memory(_T("0"))
{
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	dot_count = 0;
	operator_count = 0;
	dot_count = 0;
	equal_count = 0;
	negate_count = 0;
	reciproc_count = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, inout);
	DDX_Text(pDX, IDC_EDIT2, history);
}

BEGIN_MESSAGE_MAP(CcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON11, &CcalculatorDlg::OnBnClickedButton11)
	ON_EN_CHANGE(IDC_EDIT2, &CcalculatorDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CcalculatorDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CcalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CcalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CcalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CcalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CcalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CcalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CcalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CcalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON12, &CcalculatorDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CcalculatorDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CcalculatorDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CcalculatorDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CcalculatorDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CcalculatorDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CcalculatorDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CcalculatorDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CcalculatorDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CcalculatorDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CcalculatorDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CcalculatorDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CcalculatorDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON28, &CcalculatorDlg::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON25, &CcalculatorDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CcalculatorDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CcalculatorDlg::OnBnClickedButton27)
END_MESSAGE_MAP()


// CcalculatorDlg message handlers

BOOL CcalculatorDlg::OnInitDialog()
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

void CcalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcalculatorDlg::OnPaint()
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
HCURSOR CcalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcalculatorDlg::OnBnClickedButton11()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("7");
			}
			else {

				inout += _T("7");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("7");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		tmp_buffer = buffer;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("7");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CcalculatorDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CcalculatorDlg::OnBnClickedButton1()
{
	memory = (_T("0"));
	//AfxMessageBox(memory);
	inout = pretty(inout);
	history = _T("");
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton2()
{
	inout = memory;
	//AfxMessageBox(memory);
	inout = pretty(inout);
	UpdateData(FALSE);
}

void CcalculatorDlg::OnBnClickedButton3()
{
	memory = inout;
	//AfxMessageBox(memory);
	inout = pretty(inout);
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton4()
{
	memory = plus(memory, inout);
	//AfxMessageBox(memory);
	inout = pretty(inout);
	UpdateData(FALSE);
}

void CcalculatorDlg::OnBnClickedButton5()
{
	memory = sub(memory, inout);
	//AfxMessageBox(memory);
	inout = pretty(inout);
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton6()
{

	if (flag_equal == false && flag_operator == false) {
		int length = inout.GetLength();
		if (length > 0) {
			inout.Delete(length - 1);
		}
		UpdateData(FALSE);
	}

}


void CcalculatorDlg::OnBnClickedButton7()
{
	inout = _T("0");
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton8()
{
	inout = _T("0");
	history = _T("");
	result = _T("0");
	operator_count = 0;
	equal_count = 0;
	negate_count = 0;
	reciproc_count = 0;
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	//buffer = _T("0");
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton9()
{
	if (flag_equal == false) {
		CString temp = _T("0");
		inout = sub(temp, inout);
	}
	else {
		if (negate_count == 0) {
			history = _T("negate(") + inout + _T(")");
			CString temp = _T("0");
			inout = sub(temp, inout);
			negate_count++;
		}
		else {
			history = _T("negate(") + history + _T(")");
			CString temp = _T("0");
			inout = sub(temp, inout);
		}

	}
	
	inout = pretty(inout);
	//AfxMessageBox(inout);
	//AfxMessageBox(result);
	UpdateData(FALSE);
	flag_number = true;
}


void CcalculatorDlg::OnBnClickedButton10()
{
	double x = _wtof(inout);
	if (x >= 0) {
		x = sqrt(x);
		CString str;
		str.Format(_T("%.16f"), x);
		history = _T("sqrt(") + inout + _T(")");
		inout = str;
		inout = pretty(inout);
		UpdateData(FALSE);
	}
	else {
		AfxMessageBox(_T("Invalid input."));
	}
}

void CcalculatorDlg::OnBnClickedButton12()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("8");
			}
			else {

				inout += _T("8");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("8");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		tmp_buffer = buffer;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("8");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton13()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("9");
			}
			else {

				inout += _T("9");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("9");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		tmp_buffer = buffer;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("9");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	inout = pretty(inout);
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton14()
{
	if (flag_operator == true) {
		int length = history.GetLength();
		if (length > 0) {
			history.Delete(length - 1);
		}
		history = history + _T("/");
		last_operator = '/';

		UpdateData(FALSE);
		flag_number = false;
		flag_operator = true;
		flag_equal = false;
		return;
	}
	if (flag_equal == true) {
		operator_count--;
		result = inout;
		buffer = inout;
	}
	//operator lan dau xuat hien
	if (operator_count == 0) {
		result = inout;
		history += result;
		history += _T("/");
	}

	//operator lan thu 2 xuat hien
	if (operator_count == 1) {
		buffer = inout;
		history += inout;
		history += _T("/");
		if (last_operator == '+') {
			result = plus(result, buffer);
		}
		if (last_operator == '-') {
			result = sub(result, buffer);
		}
		if (last_operator == '*') {
			result = mul(result, buffer);
		}
		if (last_operator == '/') {
			result = div(result, buffer);
		}
		inout = result;
		operator_count--;

	}
	inout = pretty(inout);
	UpdateData(FALSE);
	last_operator = '/';
	operator_count++;
	flag_number = false;
	flag_operator = true;
	flag_equal = false;
	flag_dot = false;
	dot_count = 0;
	exception = false;
}


void CcalculatorDlg::OnBnClickedButton15()
{
	double d_result = _wtof(result);
	d_result = fabs(d_result);
	double d_inout = _wtof(inout);
	double x = d_result * d_inout / 100.00 ;
	CString str;
	str.Format(_T("%.16f"), x);
	inout = str;

	inout= pretty(inout);
	tmp_history = history;
	history += inout;
	UpdateData(FALSE);
	history = tmp_history;
}


void CcalculatorDlg::OnBnClickedButton16()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("4");
			}
			else {

				inout += _T("4");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("4");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_buffer = buffer;
		tmp_operator_count = operator_count;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("4");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton17()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("5");
			}
			else {

				inout += _T("5");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("5");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		tmp_buffer = buffer;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("5");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton18()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("6");
			}
			else {

				inout += _T("6");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("6");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		tmp_buffer = buffer;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("6");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton19()
{
	if (flag_operator == true) {
		int length = history.GetLength();
		if (length > 0) {
			history.Delete(length - 1);
		}
		history = history + _T("*");
		last_operator = '*';

		UpdateData(FALSE);
		flag_number = false;
		flag_operator = true;
		flag_equal = false;
		return;
	}
	if (flag_equal == true) {
		operator_count--;
		result = inout;
		buffer = inout;
	}

	//operator lan dau xuat hien
	if (operator_count == 0) {
		result = inout;
		history += result;
		history += _T("*");
	}

	//operator lan thu 2 xuat hien
	if (operator_count == 1) {
		buffer = inout;
		history += inout;
		history += _T("*");
		if (last_operator == '+') {
			result = plus(result, buffer);
		}
		if (last_operator == '-') {
			result = sub(result, buffer);
		}
		if (last_operator == '*') {
			result = mul(result, buffer);
		}
		if (last_operator == '/') {
			result = div(result, buffer);
		}
		inout = result;
		operator_count--;
	}
	inout = pretty(inout);
	UpdateData(FALSE);
	last_operator = '*';
	operator_count++;
	flag_number = false;
	flag_operator = true;
	flag_equal = false;
	flag_dot = false;
	dot_count = 0;
	exception = false;
}


void CcalculatorDlg::OnBnClickedButton20()
{
	double x = _wtof(inout);
	if (x == 0) {
		AfxMessageBox(_T("Cannot divide by zero."));
	}
	else {
		x = 1 / x;
		CString str;
		str.Format(_T("%.100f"), x);
		if (negate_count == 0) {
			history = _T("reciproc(") + inout + _T(")");
			inout = str;
			negate_count++;
		}
		else {
			history = _T("reciproc(") + history + _T(")");
			inout = str;
		}
		inout = pretty(inout);
		UpdateData(FALSE);
		dot_count = 1;
	}
}


void CcalculatorDlg::OnBnClickedButton21()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("1");
			}
			else {

				inout += _T("1");
			}
		}
		if (flag_operator == true) {
			
			//neu vua nhap vao dau thi reset inout
			inout = _T("1");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_buffer = buffer;
		tmp_operator_count = operator_count;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("1");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton22()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("2");
			}
			else {

				inout += _T("2");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("2");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("2");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton23()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("3");
			}
			else {

				inout += _T("3");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("3");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_operator_count = operator_count;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
		inout = _T("3");
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton24()
{
	if (flag_operator == true) {
		int length = history.GetLength();
		if (length > 0) {
			history.Delete(length - 1);
		}
		history = history + _T("-");
		last_operator = '-';

		UpdateData(FALSE);
		flag_number = false;
		flag_operator = true;
		flag_equal = false;
		return;
	}
	if (flag_equal == true) {
		operator_count--;
		result = inout;
		buffer = inout;
	}


	//operator lan dau xuat hien
	if (operator_count == 0) {
		result = inout;
		history += result;
		history += _T("-");
	}

	//operator lan thu 2 xuat hien
	if (operator_count == 1) {
		buffer = inout;
		history += inout;
		history += _T("-");
		switch (last_operator) {
		case '+':
			result = plus(result, buffer);
			break;
		case '-':
			result = sub(result, buffer);
			break;
		case '*':
			result = mul(result, buffer);
			break;
		case '/':
			result = div(result, buffer);
			break;
		}
		inout = result;
		operator_count--;
	}

	inout = pretty(inout);
	UpdateData(FALSE);
	last_operator = '-';
	operator_count++;
	flag_number = false;
	flag_operator = true;
	flag_equal = false;
	flag_dot = false;
	dot_count = 0;
	exception = false;
}


void CcalculatorDlg::OnBnClickedButton28()
{

	if (flag_number == true) {
		if (exception == false) {
			if (operator_count == 0) {
				result = inout;
				history = _T("");
			}
			else if (operator_count == 1) {
				buffer = inout;
				//AfxMessageBox(buffer);
				switch (last_operator) {
				case '+':
					result = plus(result, buffer);
					break;
				case '-':
					result = sub(result, buffer);
					break;
				case '*':
					result = mul(result, buffer);
					break;
				case '/':
					result = div(result, buffer);
					break;
				}
				history = _T("");
				inout = result;
			}
		}
		else {
			result = inout;
			operator_count = tmp_operator_count;
			switch (tmp_last_operator) {
			case '+':
				result = plus(result, buffer);
				break;
			case '-':
				result = sub(result, buffer);
				break;
			case '*':
				result = mul(result, buffer);
				break;
			case '/':
				result = div(result, buffer);
				break;
			}
			history = _T("");
			inout = result;
		}
	}
	
	
	if (flag_operator == true && buffer != _T("")) {
		result = inout;
		switch (last_operator) {
		case '+':
			result = plus(result, result);
			break;
		case '-':
			result = _T("0");
			break;
		case '*':
			result = mul(result, result);
			break;
		case '/':
			result = _T("1");
			break;
		}
		history = _T("");
		inout = result;
	}
	if (flag_operator == true && buffer == _T("")) {
		buffer = inout;
		result = inout;
		switch (last_operator) {
		case '+':
			result = plus(result, buffer);
			break;
		case '-':
			result = sub(result, buffer);
			break;
		case '*':
			result = mul(result, buffer);
			break;
		case '/':
			result = div(result, buffer);
			break;
		}
		history = _T("");
		inout = result;
	}
	if (flag_equal == true) {
		result = inout;
		switch (last_operator) {
		case '+':
			result = plus(result, buffer);
			break;
		case '-':
			result = sub(result, buffer);
			break;
		case '*':
			result = mul(result, buffer);
			break;
		case '/':
			result = div(result, buffer);
			break;
		}
		history = _T("");
		inout = result;
	}
	exception = false;
	flag_equal = true;
	flag_operator = false;
	flag_number = false;
	flag_dot = false;
	dot_count = 0;
	inout = pretty(inout);
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton25()
{
	if (flag_equal == false) {
		if (flag_number == true) {
			//neu vua nhap vao so thi nhap tiep
			if (inout == "0") {
				//xoa so 0 o dau
				inout = _T("0");
			}
			else {

				inout += _T("0");
			}
		}
		if (flag_operator == true) {
			//neu vua nhap vao dau thi reset inout
			inout = _T("0");

		}
	}
	if (flag_equal == true) {
		exception = true;
		tmp_inout = inout;
		tmp_last_operator = last_operator;
		tmp_buffer = buffer;
		//khoi phuc cai dat goc:v
		OnBnClickedButton8();
	}
	flag_number = true;
	flag_operator = false;
	flag_equal = false;
	flag_dot = false;
	UpdateData(FALSE);
}


void CcalculatorDlg::OnBnClickedButton26()
{
	if (dot_count == 0) {
		if (flag_dot == true) {
			int length = inout.GetLength();
			if (length > 0) {
				inout.Delete(length - 1);
			}
			inout = inout + _T(".");
			flag_dot = false;
		}
		if (flag_operator == true) {
			inout = _T("0");
			inout += _T(".");

		}
		if (flag_number == true) {
			inout += _T(".");
		}
		if (flag_equal == true) {
			OnBnClickedButton8();
			inout += _T(".");
		}
	}



	flag_dot = true;
	flag_equal = false;
	flag_number = true;
	flag_operator = false;
	dot_count = 1;

	UpdateData(FALSE);
}

void CcalculatorDlg::OnBnClickedButton27()
{
	if (flag_operator == true) {
		int length = history.GetLength();
		if (length > 0) {
			history.Delete(length - 1);
		}
		history = history + _T("+");
		last_operator = '+';

		UpdateData(FALSE);
		flag_number = false;
		flag_operator = true;
		flag_equal = false;
		return;
	}
	if (flag_equal == true) {
		operator_count--;
		result = inout;
		buffer = inout;
	}


	//operator lan dau xuat hien
	if (operator_count == 0) {
		result = inout;
		history += result;
		history += _T("+");
	}

	//operator lan thu 2 xuat hien
	if (operator_count == 1) {
		buffer = inout;
		history += inout;
		history += _T("+");
		switch (last_operator) {
		case '+':
			result = plus(result, buffer);
			break;
		case '-':
			result = sub(result, buffer);
			break;
		case '*':
			result = mul(result, buffer);
			break;
		case '/':
			result = div(result, buffer);
			break;
		}
		inout = result;
		operator_count--;
	}

	inout = pretty(inout);
	UpdateData(FALSE);
	last_operator = '+';
	operator_count++;
	flag_number = false;
	flag_operator = true;
	flag_equal = false;
	flag_dot = false;
	dot_count = 0;
	exception = false;
}

CString CcalculatorDlg::plus(CString number1, CString number2) {
	double num1 = _wtof(number1);
	double num2 = _wtof(number2);
	double result = num1 + num2;
	CString strResult;
	strResult.Format(_T("%.12f"), result);
	return strResult;
}
CString CcalculatorDlg::mul(CString number1, CString number2) {
	double num1 = _wtof(number1);
	double num2 = _wtof(number2);
	double result = num1 * num2;
	CString strResult;
	strResult.Format(_T("%.12f"), result);
	return strResult;
}
CString CcalculatorDlg::sub(CString number1, CString number2) {
	double num1 = _wtof(number1);
	double num2 = _wtof(number2);
	double result = num1 - num2;
	CString strResult;
	strResult.Format(_T("%.12f"), result);
	return strResult;
}
CString CcalculatorDlg::div(CString number1, CString number2) {
	double num1 = _wtof(number1);
	double num2 = _wtof(number2);
	if (num2 == 0) {
		AfxMessageBox(_T("Cannot divide by zero."));
		return _T("");
	}
	double result = num1 / num2;
	CString strResult;
	strResult.Format(_T("%.12f"), result);
	return strResult;
}
CString CcalculatorDlg::pretty(CString lgl) {
	int decimalPos = lgl.Find(L'.');

	if (decimalPos == -1 || lgl.IsEmpty())
	{
		return lgl;
	}


	int length = lgl.GetLength();
	int endIndex = length - 1;
	while (endIndex > decimalPos && lgl[endIndex] == L'0')
	{
		endIndex--;
	}

	if (lgl[endIndex] == L'.')
	{
		endIndex--;
	}

	CString result = lgl.Left(endIndex + 1);

	return result;
}


﻿
// CalculatorView.cpp: CCalculatorView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CDescribeStat.h"
#include "CMatrixManip.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Calculator.h"
#endif

#include "CalculatorDoc.h"
#include "CalculatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorView

IMPLEMENT_DYNCREATE(CCalculatorView, CFormView)

BEGIN_MESSAGE_MAP(CCalculatorView, CFormView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCalculatorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorView::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorView::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorView::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorView::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorView::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_E, &CCalculatorView::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_Pi, &CCalculatorView::OnBnClickedButtonPi)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorView::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorView::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_TIMES, &CCalculatorView::OnBnClickedButtonTimes)
	ON_BN_CLICKED(IDC_BUTTON_DIVISION, &CCalculatorView::OnBnClickedButtonDivision)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorView::OnBnClickedButtonEqual)
	ON_EN_CHANGE(IDC_EDIT, &CCalculatorView::OnEnChangeEdit)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CCalculatorView::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CCalculatorView::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_AC, &CCalculatorView::OnBnClickedButtonAc)
	ON_BN_CLICKED(IDC_BUTTON_slash, &CCalculatorView::OnBnClickedButtonslash)
	ON_BN_CLICKED(IDC_BUTTON_ADVANCE, &CCalculatorView::OnBnClickedButtonAdvance)
	ON_BN_CLICKED(IDC_CHECK_FRACTION, &CCalculatorView::OnBnClickedCheckFraction)
	ON_COMMAND(ID_STAT_DESCRIBE, &CCalculatorView::OnStatDescribe)
	ON_COMMAND(ID_STAT_MATRIX, &CCalculatorView::OnStatMatrix)
	ON_BN_CLICKED(IDC_BUTTON_RIGHTP, &CCalculatorView::OnBnClickedButtonRightp)
	ON_BN_CLICKED(IDC_BUTTON_LEFTP, &CCalculatorView::OnBnClickedButtonLeftp)
	ON_BN_CLICKED(IDC_BUTTON_F, &CCalculatorView::OnBnClickedButtonF)
	ON_BN_CLICKED(IDC_BUTTON_Pow, &CCalculatorView::OnBnClickedButtonPow)
	ON_BN_CLICKED(IDC_BUTTON_Ln, &CCalculatorView::OnBnClickedButtonLn)
	ON_BN_CLICKED(IDC_BUTTON_Lg, &CCalculatorView::OnBnClickedButtonLg)
	ON_BN_CLICKED(IDC_BUTTON_Sin, &CCalculatorView::OnBnClickedButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_Cos, &CCalculatorView::OnBnClickedButtonCos)
	ON_BN_CLICKED(IDC_BUTTON_Tan, &CCalculatorView::OnBnClickedButtonTan)
END_MESSAGE_MAP()

// CCalculatorView 构造/析构

CCalculatorView::CCalculatorView() noexcept
	: CFormView(IDD_CALCULATOR_FORM)
{
	m_input = _T("");
}

CCalculatorView::~CCalculatorView()
{
}

void CCalculatorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT, m_input);
	DDX_Control(pDX, IDC_BUTTON_TIMES, markTimes);
	DDX_Control(pDX, IDC_BUTTON_DIVISION, markDivision);
	DDX_Control(pDX, IDC_CHECK_FRACTION, m_FractionMode);
}

BOOL CCalculatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CCalculatorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	// 创建字体
	CFont font;
	font.CreatePointFont(100, _T("Segoe UI Symbol")); // 10号字体，使用 Segoe UI Symbol

	// 设置控件使用新字体
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_BUTTON_TIMES);
	pEdit->SetFont(&font);

	markTimes.SetWindowText(_T("\u00D7"));
	markDivision.SetWindowTextW(_T("\u00F7"));
	GetDlgItem(IDC_BUTTON_slash)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Sin)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Cos)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Tan)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Ln)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Pow)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_F)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Pi)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_E)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_LEFTP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_RIGHTP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_Lg)->ShowWindow(SW_HIDE);
}


// CCalculatorView 打印


void CCalculatorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCalculatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCalculatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCalculatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCalculatorView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 在此处添加自定义打印代码
}

void CCalculatorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCalculatorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCalculatorView 诊断

#ifdef _DEBUG
void CCalculatorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCalculatorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCalculatorDoc* CCalculatorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCalculatorDoc)));
	return (CCalculatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CCalculatorView 消息处理程序



void CCalculatorView::OnBnClickedButton0()
{
	m_input += _T("0");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton1()
{
	m_input += _T("1");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton2()
{
	m_input += _T("2");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton3()
{
	m_input += _T("3");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton4()
{
	m_input += _T("4");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton5()
{
	m_input += _T("5");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton6()
{
	m_input += _T("6");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButton7()
{
	m_input += _T("7");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton8()
{
	m_input += _T("8");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButton9()
{
	m_input += _T("9");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButtonPoint()
{
	m_input += _T(".");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButtonslash()
{
	m_input += _T("/");
	UpdateData(FALSE);
}



void CCalculatorView::OnBnClickedButtonPlus()
{
	m_input += _T("+");
	OnEnChangeEdit();
}


void CCalculatorView::OnBnClickedButtonMinus()
{
	m_input += _T("-");
	OnEnChangeEdit();
}


void CCalculatorView::OnBnClickedButtonTimes()
{
	m_input += _T("\u00D7");
	OnEnChangeEdit();
}


void CCalculatorView::OnBnClickedButtonDivision()
{
	m_input += _T("\u00F7");
	OnEnChangeEdit();
}


void CCalculatorView::OnBnClickedButtonEqual()
{
	if (m_FractionMode.GetCheck() == BST_UNCHECKED) {
		evaluate(m_input, 1);
	}
	else {
		evaluate(m_input, 2);
	}
	UpdateData(FALSE);
}


void CCalculatorView::OnEnChangeEdit()
{
	int length = m_input.GetLength();
	if (length >= 2) {
		wchar_t last = m_input[length - 1], second = m_input[length - 2];
		if (second == L'+' || second == L'\u00D7' || second == L'\u00F7') {
			if (last == L'+' || last == L'\u00D7' || last == L'\u00F7') {
				m_input.Delete(length - 2);
			}
			else if (last == L'-') {
				m_input.Insert(length - 1, L'(');
			}
		}
		else if (second == L'-') {
			if (last == L'-' || last == L'+' || last == L'\u00D7' || last == L'\u00F7') {
				m_input.Delete(length - 2);
			}
		}
	}
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonBack()
{
	if (!m_input.IsEmpty()) {
		m_input.Delete(m_input.GetLength() - 1);
	}
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonAc()
{
	m_input = _T("");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButtonRightp()
{
	m_input += _T(")");
	UpdateData(FALSE);
}

void CCalculatorView::OnBnClickedButtonLeftp()
{
	m_input += _T("(");
	UpdateData(FALSE);
}

void CCalculatorView::checkVisibility(int ID)
{
	// 检查控件当前是否可见
	CWnd* pControl = GetDlgItem(ID);
	if (pControl && pControl->IsWindowVisible())
	{
		pControl->ShowWindow(SW_HIDE);  // 当前可见则隐藏
	}
	else
	{
		pControl->ShowWindow(SW_SHOW);  // 当前隐藏则显示
	}
}

void CCalculatorView::OnBnClickedButtonAdvance()
{
	checkVisibility(IDC_BUTTON_Sin);
	checkVisibility(IDC_BUTTON_Cos);
	checkVisibility(IDC_BUTTON_Tan);
	checkVisibility(IDC_BUTTON_Ln);
	checkVisibility(IDC_BUTTON_Pow);
	checkVisibility(IDC_BUTTON_F);
	checkVisibility(IDC_BUTTON_Pi);
	checkVisibility(IDC_BUTTON_E);
	checkVisibility(IDC_BUTTON_LEFTP);
	checkVisibility(IDC_BUTTON_RIGHTP);
	checkVisibility(IDC_BUTTON_Lg);
}


void CCalculatorView::OnBnClickedCheckFraction()
{
	checkVisibility(IDC_BUTTON_slash);
}


void CCalculatorView::OnStatDescribe()
{
	CDescribeStat ds;
	ds.DoModal();
		
}

void CCalculatorView::OnStatMatrix()
{
	CMatrixManip mm;
	if (mm.DoModal() == IDOK) {
		// 用户点击了OK，处理数据
	}
}

void CCalculatorView::OnBnClickedButtonE()
{
	m_input += _T("e");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonPi()
{
	m_input += _T("π");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonF()
{
	m_input += _T("!");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonPow()
{
	m_input += _T("^");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonLn()
{
	m_input += _T("ln");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonLg()
{
	m_input += _T("lg");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonSin()
{
	m_input += _T("sin");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonCos()
{
	m_input += _T("cos");
	UpdateData(FALSE);
}


void CCalculatorView::OnBnClickedButtonTan()
{
	m_input += _T("tan");
	UpdateData(FALSE);
}







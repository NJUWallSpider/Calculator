﻿#pragma once
#include "afxdialogex.h"
#include <afxdb.h>


// CDescribeStat 对话框

class CDescribeStat : public CDialogEx
{
	DECLARE_DYNAMIC(CDescribeStat)

public:
	CDescribeStat(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDescribeStat();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DESCRIBE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CDatabase db;
	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonFile();
	
	CListCtrl m_ListData;
	CListBox m_listBoxTables;
	afx_msg void OnEnChangeEdit1();
	
	CString m_dbLink;
	afx_msg void OnBnClickedButtonBegin();
	CString m_sheetName;
};

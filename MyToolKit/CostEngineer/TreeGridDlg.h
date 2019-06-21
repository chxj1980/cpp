#pragma once
#include "afxcmn.h"
#include "./GridCtrl_src/GridCtrl.h"
#include "./GridCtrl_src/TreeGridCtrl.h"


// CTreeGridDlg �Ի���

class CTreeGridDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreeGridDlg)

public:
	CTreeGridDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTreeGridDlg();

// �Ի�������
	enum { IDD = IDD_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CTreeGridCtrl m_Grid;
	
	vector<int>		m_vecCode;
	vector<string>	m_vecContent;
	vector<int>		m_vecParentCode;

	virtual BOOL OnInitDialog();
};

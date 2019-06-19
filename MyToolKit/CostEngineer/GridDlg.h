#pragma once
#include "afxcmn.h"
#include "../GridCtrl_src/GridCtrl.h"
#include "../GridCtrl_src/TreeGridCtrl.h"


// CPDFStructureDlg �Ի���

class CGridDlg : public CDialog
{
	DECLARE_DYNAMIC(CGridDlg)

public:
	CGridDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGridDlg();

// �Ի�������
	enum { IDD = IDD_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CTreeGridCtrl m_Grid;
	
	CString					m_strTitle;
	vector<string>			m_vecHeader;
	vector<vector<string>>	m_vecData;

	virtual BOOL OnInitDialog();
};

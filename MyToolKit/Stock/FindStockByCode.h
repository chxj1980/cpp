#pragma once
#include "afxwin.h"


// CFindStockByCode �Ի���

class CFindStockByCode : public CDialog
{
	DECLARE_DYNAMIC(CFindStockByCode)

public:
	CFindStockByCode(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindStockByCode();

// �Ի�������
	enum { IDD = IDD_FIND_BY_CODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	void SetStockInfo(CStockInfo * pStockInfo){ m_pStockInfo = pStockInfo; }
public:
	CStockInfo * m_pStockInfo;

	CComboBoxExt	m_Combo1;
	CString			m_strCode;
	CString			m_strCaption;
};

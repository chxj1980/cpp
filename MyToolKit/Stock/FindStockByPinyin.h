#pragma once
#include "afxwin.h"


// CFindStockByPinyin �Ի���

class CFindStockByPinyin : public CDialog
{
	DECLARE_DYNAMIC(CFindStockByPinyin)

public:
	CFindStockByPinyin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFindStockByPinyin();

// �Ի�������
	enum { IDD = IDD_FIND_BY_PINYIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBoxExt m_Combo1;
	CString m_strPinyin;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};

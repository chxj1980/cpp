#pragma once
#include "afxcmn.h"


// CStockRangeSet �Ի���

class CStockRangeSet : public CDialog
{
	DECLARE_DYNAMIC(CStockRangeSet)

public:
	CStockRangeSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStockRangeSet();

// �Ի�������
	enum { IDD = IDD_STOCKRANGESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_StartDate;
	COleDateTime m_End_Date;
	CListCtrl m_listViewType;
	string		m_strViewType;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};

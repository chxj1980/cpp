#pragma once
#include "afxcmn.h"


// CStockGroupDlg �Ի���

class CStockGroupDlg : public CDialog
{
	DECLARE_DYNAMIC(CStockGroupDlg)

public:
	CStockGroupDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStockGroupDlg();

// �Ի�������
	enum { IDD = IDD_STOCK_GROUP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	void DisplayCheckBoxByRadio(HTREEITEM hitem, int nRadio);
	void UpdateCheckBoxByRadio(HTREEITEM hitem, int nRadio);
	void GetSelectedHitemByRadio(HTREEITEM hitem, int nRadio, vector<string> & vecItem);

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioReg();
	afx_msg void OnNMClickTreeReg(NMHDR *pNMHDR, LRESULT *pResult);
	
	vector<string>	m_vecSelectedItemReg;	//	ѡ�е��������
	vector<string>	m_vecSelectedItemCsrcGate;	//	ѡ�е�֤�����ҵ �������
	vector<string>	m_vecSelectedItemCsrcBig;	//	ѡ�е�֤�����ҵ �������
protected:
	virtual void OnOK();

public:
	int m_RadioCsrc;
	int m_RadioReg;
	CTreeCtrl m_TreeCsrc;
	CTreeCtrl m_TreeReg;
	afx_msg void OnBnClickedRadioCsrc();
	afx_msg void OnNMClickTreeCsrc(NMHDR *pNMHDR, LRESULT *pResult);
};

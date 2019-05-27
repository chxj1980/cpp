#pragma once
#include "afxcmn.h"


// CPlateSelectDlg �Ի���

class CPlateSelectDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlateSelectDlg)

public:
	CPlateSelectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlateSelectDlg();

// �Ի�������
	enum { IDD = IDD_PLATE_SELECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	void updateCheckBox(HTREEITEM hitem, bool newStatus);
	void checkToTree(HTREEITEM hitem);
	map<string, string>	GetPlateCodes(int & is_stock);
public:
	//	���� չʾ�����ṩѡ��İ����Ϣ
	string	m_nCode;
	int		m_nPlateType;

	//	����Ի���ѡ��Ľ��
	vector<string>	m_vec_code;
	string	m_strGraphOrTable;	//	ͼ�� ���� ���չʾ
	int		m_nIs_Stock;		//	����б���� �������� �� 0 ���  1 ����

public:
	CTreeCtrl m_Tree;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnGraph();
	afx_msg void OnBnClickedBtnTable();
	afx_msg void OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult);
};

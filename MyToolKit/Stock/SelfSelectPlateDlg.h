#pragma once
#include "afxcmn.h"


// CSelfSelectPlateDlg �Ի���

class CSelfSelectPlateDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelfSelectPlateDlg)

public:
	CSelfSelectPlateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelfSelectPlateDlg();

// �Ի�������
	enum { IDD = IDD_SELFSELECTPLATEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_Tree;
	int		m_nPlateCode;
	string	m_sPlateName;

	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};

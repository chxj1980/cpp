
// CninfoPDFDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CCninfoPDFDlg �Ի���
class CCninfoPDFDlg : public CMyDialog
{
// ����
public:
	CCninfoPDFDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CNINFOPDF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
	virtual BOOL OnInitDialog();

	virtual void ProcessMessage(string strMsg);


// ʵ��
protected:

	DECLARE_MESSAGE_MAP()

	
public:
	CRichEditCtrl m_ctlEdit;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};

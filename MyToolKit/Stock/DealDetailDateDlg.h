#pragma once

// CDealDetailDateDlg �Ի���

class CDealDetailDateDlg : public CDialog
{
	DECLARE_DYNAMIC(CDealDetailDateDlg)

public:
	CDealDetailDateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDealDetailDateDlg();

// �Ի�������
	enum { IDD = IDD_DEAL_DETAIL_DATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_Grid;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();

public:
	string	m_strDealDetailDate;
};

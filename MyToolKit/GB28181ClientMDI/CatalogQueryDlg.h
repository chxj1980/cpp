#pragma once


// CCatalogQueryDlg �Ի���

class CCatalogQueryDlg : public CDialog
{
	DECLARE_DYNAMIC(CCatalogQueryDlg)

public:
	CCatalogQueryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCatalogQueryDlg();

// �Ի�������
	enum { IDD = IDD_CATALOGQUERYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

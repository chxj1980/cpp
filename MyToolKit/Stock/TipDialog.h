#pragma once



// CTipDialog �Ի���

class CTipDialog : public CDialog
{
	DECLARE_DYNAMIC(CTipDialog)

public:
	CTipDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTipDialog();

// �Ի�������
	enum { IDD = IDD_TIP_BOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_Grid;
	list<CTipRecord>	m_lstTip;
	virtual BOOL OnInitDialog();
};

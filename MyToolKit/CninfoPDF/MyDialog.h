#pragma once


// CMyDialog �Ի���

class CMyDialog : public CDialog
{
public:
	CMyDialog(UINT id, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDialog();

	virtual void ProcessMessage(string strMsg);
};

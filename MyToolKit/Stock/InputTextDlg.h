#pragma once


// CInputTextDlg �Ի���

class CInputTextDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputTextDlg)

public:
	CInputTextDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputTextDlg();

// �Ի�������
	enum { IDD = IDD_INPUTTEXTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strInputText;
};

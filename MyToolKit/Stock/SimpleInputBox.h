#pragma once
#include "afxwin.h"


// CSimpleInputBox �Ի���

class CSimpleInputBox : public CDialog
{
	DECLARE_DYNAMIC(CSimpleInputBox)

public:
	CSimpleInputBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSimpleInputBox();

// �Ի�������
	enum { IDD = IDD_SIMPLE_INPUT_BOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCaption;
	virtual BOOL OnInitDialog();
	CComboBox m_ComboBox;
	CString m_strInput;

	vector<string>	m_ComboString;
};

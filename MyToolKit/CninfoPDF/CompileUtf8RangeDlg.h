#pragma once


// CCompileUtf8RangeDlg �Ի���

class CCompileUtf8RangeDlg : public CMyDialog
{
	DECLARE_DYNAMIC(CCompileUtf8RangeDlg)

public:
	CCompileUtf8RangeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCompileUtf8RangeDlg();

// �Ի�������
	enum { IDD = IDD_COMPILE_UTF8_RANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strStart;
	CString m_strEnd;
	CString m_strResult;
	afx_msg void OnBnClickedBtnCaculate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

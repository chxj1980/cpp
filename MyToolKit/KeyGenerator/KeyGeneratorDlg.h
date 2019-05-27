
// KeyGeneratorDlg.h : ͷ�ļ�
//

#pragma once

#include "Step1.h"
#include "Step2.h"
#include "Step3.h"

// CKeyGeneratorDlg �Ի���
class CKeyGeneratorDlg : public CDialog
{
// ����
public:
	CKeyGeneratorDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CStep1 step1;
	CStep2 step2;
	CStep3 step3;

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	CString	m_str1;
	CString	m_str2;
	CString	m_str3;
	CString	m_key;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg HRESULT OnShowStepWnd(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT OnCloseWindow(WPARAM wParam, LPARAM lParam);
	afx_msg HRESULT OnGetSLC(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	void ShowStepWnd(int nStep);
};

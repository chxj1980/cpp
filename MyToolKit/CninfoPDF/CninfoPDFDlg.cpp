
// CninfoPDFDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CninfoPDF.h"
#include "CninfoPDFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCninfoPDFDlg �Ի���


CCninfoPDFDlg::CCninfoPDFDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CCninfoPDFDlg::IDD, pParent)
{
	
}

void CCninfoPDFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_ctlEdit);
}

BEGIN_MESSAGE_MAP(CCninfoPDFDlg, CMyDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CCninfoPDFDlg ��Ϣ�������

BOOL CCninfoPDFDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}




void CCninfoPDFDlg::ProcessMessage(string strMsg)
{
	m_ctlEdit.SetSel(-1, -1);
	m_ctlEdit.ReplaceSel( (LPCTSTR)strMsg.c_str() ); 

}

void CCninfoPDFDlg::OnSize(UINT nType, int cx, int cy)
{
	CMyDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if(::IsWindow(m_ctlEdit.m_hWnd))
	{
		CRect rect;
		GetClientRect(&rect);
		m_ctlEdit.MoveWindow(rect);
	}

}
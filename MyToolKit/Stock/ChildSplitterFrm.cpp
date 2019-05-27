
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "Stock.h"

#include "ChildSplitterFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildSplitterFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildSplitterFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildSplitterFrame::CChildSplitterFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildSplitterFrame::~CChildSplitterFrame()
{
}

BOOL CChildSplitterFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	return m_wndSplitter.Create(this,
		2, 2,			// TODO: ��������������
		CSize(10, 10),	// TODO: ������С�����С
		pContext);

}


BOOL CChildSplitterFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ

	 cs.style &= ~WS_MAXIMIZEBOX; 

	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildSplitterFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildSplitterFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������

void CChildSplitterFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CIndividualShareDoc *  pDoc =  (CIndividualShareDoc *)GetActiveView()->GetDocument();

	CString strTitle = pDoc->GetTitle();
	if(string(strTitle.GetBuffer()).find("�Զ�����")!=string::npos)
	{
		if(pDoc->m_vecCommandCode.size()>0)
			AfxMessageBox("��ҳ��������ɺ��Զ��ر�");
		else
			CMDIChildWndEx::OnClose();
	}
	else
		CMDIChildWndEx::OnClose();
}

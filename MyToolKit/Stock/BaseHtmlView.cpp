// BaseHtmlView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "BaseHtmlView.h"


// CBaseHtmlView

IMPLEMENT_DYNCREATE(CBaseHtmlView, CHtmlView)

CBaseHtmlView::CBaseHtmlView()
{

}

CBaseHtmlView::~CBaseHtmlView()
{
}

void CBaseHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseHtmlView, CHtmlView)
END_MESSAGE_MAP()


// CBaseHtmlView ���

#ifdef _DEBUG
void CBaseHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CBaseHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CBaseHtmlView ��Ϣ�������

void CBaseHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	Navigate2("http://q.stock.sohu.com/cn/bk.shtml");
}

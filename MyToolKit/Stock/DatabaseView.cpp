// DatabaseView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "DatabaseView.h"


// CDatabaseView

IMPLEMENT_DYNCREATE(CDatabaseView, CFormView)

CDatabaseView::CDatabaseView()
	: CFormView(CDatabaseView::IDD)
{

}

CDatabaseView::~CDatabaseView()
{
}

void CDatabaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDatabaseView, CFormView)
END_MESSAGE_MAP()


// CDatabaseView ���

#ifdef _DEBUG
void CDatabaseView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDatabaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDatabaseView ��Ϣ�������

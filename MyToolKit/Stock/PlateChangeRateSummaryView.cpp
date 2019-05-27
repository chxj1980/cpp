// PlateChangeRateSummaryView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "CalcMarketValueSimple.h"
#include "PlateChangeRateSummaryView.h"


// CPlateChangeRateSummaryView

IMPLEMENT_DYNCREATE(CPlateChangeRateSummaryView, CBaseGridCtlView)

CPlateChangeRateSummaryView::CPlateChangeRateSummaryView()
{

}

CPlateChangeRateSummaryView::~CPlateChangeRateSummaryView()
{
}

BEGIN_MESSAGE_MAP(CPlateChangeRateSummaryView, CBaseGridCtlView)
END_MESSAGE_MAP()


// CPlateChangeRateSummaryView ��ͼ

void CPlateChangeRateSummaryView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPlateChangeRateSummaryView ���

#ifdef _DEBUG
void CPlateChangeRateSummaryView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlateChangeRateSummaryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlateChangeRateSummaryView ��Ϣ�������


void CPlateChangeRateSummaryView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalcMarketValueSimple * cse =  new CCalcMarketValueSimple(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcMarketValueSimple::Execute1);
}

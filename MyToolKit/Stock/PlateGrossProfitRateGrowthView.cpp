// PlateChangeRateSummaryView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "CalcGrossProfit.h"
#include "PlateGrossProfitRateGrowthView.h"


// CPlateChangeRateSummaryView

IMPLEMENT_DYNCREATE(CPlateGrossProfitRateGrowthView, CBaseGridCtlView)

CPlateGrossProfitRateGrowthView::CPlateGrossProfitRateGrowthView()
{

}

CPlateGrossProfitRateGrowthView::~CPlateGrossProfitRateGrowthView()
{
}

BEGIN_MESSAGE_MAP(CPlateGrossProfitRateGrowthView, CBaseGridCtlView)
END_MESSAGE_MAP()


// CPlateChangeRateSummaryView ��ͼ

void CPlateGrossProfitRateGrowthView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPlateChangeRateSummaryView ���

#ifdef _DEBUG
void CPlateGrossProfitRateGrowthView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlateGrossProfitRateGrowthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlateChangeRateSummaryView ��Ϣ�������


void CPlateGrossProfitRateGrowthView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalcGrossProfit * cse =  new CCalcGrossProfit(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->m_str_request_zb_code = pDoc->m_strInput;			//	 "profit_rate_quarter"

	cse->ScheduleTask(&CCalcGrossProfit::Execute1);
}

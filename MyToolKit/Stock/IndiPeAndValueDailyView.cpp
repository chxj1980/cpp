// IndiCsindexView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndiPeAndValueDailyView.h"
#include "CalcPeAndValueDaily.h"

#include "ChildSplitterFrm.h"
#include "StockInfoView.h"

// CIndiCsindexView

IMPLEMENT_DYNCREATE(CIndiPeAndValueDailyView, CBaseChartCtlView)

CIndiPeAndValueDailyView::CIndiPeAndValueDailyView()
{

}

CIndiPeAndValueDailyView::~CIndiPeAndValueDailyView()
{
}

BEGIN_MESSAGE_MAP(CIndiPeAndValueDailyView, CBaseChartCtlView)
	ON_COMMAND(ID_INDI_PE_AND_VALUE_DAILY, &CIndiPeAndValueDailyView::OnIndiPeAndValueDaily)
END_MESSAGE_MAP()


// CIndiCsindexView ��ͼ

void CIndiPeAndValueDailyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndiCsindexView ���

#ifdef _DEBUG
void CIndiPeAndValueDailyView::AssertValid() const
{
	CBaseChartCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndiPeAndValueDailyView::Dump(CDumpContext& dc) const
{
	CBaseChartCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndiPeAndValueDailyView ��Ϣ�������



void CIndiPeAndValueDailyView::OnInitialUpdate()
{
	CBaseChartCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_pChartCtrl->GetLegend()->SetVisible(true);

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	m_LocalDoc.m_nCode = pDoc->m_nCode;	
	RedrawDmGraph();
}


void CIndiPeAndValueDailyView::OnIndiPeAndValueDaily()
{
	// TODO: �ڴ���������������

	m_LocalDoc.m_nCode = CStockInfoView::m_strSelectedCode;
	RedrawDmGraph();
}

void CIndiPeAndValueDailyView::RedrawDmGraph()
{

	CCalcPeAndValueDaily * cse =  new CCalcPeAndValueDaily(m_hWnd, WM_USER_LOG_1);

	cse->m_vec_request_code.push_back(m_LocalDoc.m_nCode);
	cse->m_vec_request_is_stock.push_back(1);
	cse->m_StartDate = m_StartDate;
	cse->m_EndDate = m_EndDate;
	cse->ScheduleTask(&CCalcPeAndValueDaily::Execute1);
} 

void CIndiPeAndValueDailyView::PostFocusChanged()
{
	((CChildSplitterFrame*)GetParentFrame())->m_wndSplitter.RefreshSplitBars();
}

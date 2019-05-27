// PlateTurnoverRateView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "PlateTurnoverRateView.h"
#include "CalcSohuTradingDaily.h"

// CPlateTurnoverRateView

IMPLEMENT_DYNCREATE(CPlateTurnoverRateView, CBaseChartCtlView)

CPlateTurnoverRateView::CPlateTurnoverRateView()
{

}

CPlateTurnoverRateView::~CPlateTurnoverRateView()
{
}

BEGIN_MESSAGE_MAP(CPlateTurnoverRateView, CBaseChartCtlView)
END_MESSAGE_MAP()


// CPlateTurnoverRateView ��ͼ

void CPlateTurnoverRateView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPlateTurnoverRateView ���

#ifdef _DEBUG
void CPlateTurnoverRateView::AssertValid() const
{
	CBaseChartCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlateTurnoverRateView::Dump(CDumpContext& dc) const
{
	CBaseChartCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlateTurnoverRateView ��Ϣ�������




void CPlateTurnoverRateView::OnInitialUpdate()
{
	CBaseMessageView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	RedrawDmGraph();
}

void CPlateTurnoverRateView::RedrawDmGraph()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalcSohuTradingDaily * cse =  new CCalcSohuTradingDaily(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcSohuTradingDaily::Execute1);
}

void CPlateTurnoverRateView::ProcessXmlWParam(string msgType,string code,string model,\
													  string param1,string param2,string param3)
{
	if(msgType=="TaskFinished")
	{
		stringstream ss;
		ss << "����" << (param1) << "�� �������. ";

		CCalculateTask * cse = CCalculateTask::FetchTask(atol(param1.c_str()));
		RedrawDmGraph(cse);
		if(cse!=NULL)
			delete cse;
		sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);
	}
}


void CPlateTurnoverRateView::RedrawDmGraph(CCalculateTask * cse)
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CStockApp * pApp = (CStockApp *)AfxGetApp();

	ASSERT_VALID(pDoc);	

	m_pChartCtrl->EnableRefresh(false);

	CRect rect = m_pChartCtrl->GetPlottingRect();

	CCalcSohuTradingDaily * pCse =  (CCalcSohuTradingDaily *)cse;
	m_pChartCtrl->RemoveAllSeries();

	CChartDateTimeAxis* pBottomAxis = m_pChartCtrl->CreateDateTimeAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetTickLabelFormat(false, "%Y%m%d");
	CChartStandardAxis* pLeftAxis = m_pChartCtrl->CreateStandardAxis(CChartCtrl::LeftAxis);

	double xmin, xmax, ymin, ymax;
	xmax = 0; xmin = 99999.0;
	ymin = 99999.0; ymax = 0.0;

	//	���� ���۳����̺����ֵָ��������
	int nLastCode = -1;
	CChartLineSerie* pSeries = NULL;
	for(int m=0; m< pCse->m_vec_code.size(); m++)
	{	
		if(nLastCode!=pCse->m_vec_code[m])
		{
			nLastCode = pCse->m_vec_code[m];

			pSeries = m_pChartCtrl->CreateLineSerie();
			pSeries->SetWidth(1);
			char tmp[32];
			sprintf_s(tmp, 32, "%06d", pCse->m_vec_code[m]);

			pSeries->SetName( tmp /* abbreviation.c_str()*/);

			pSeries->EnableMouseNotifications(true,false);
			pSeries->RegisterMouseListener(new CBaseChartCtlViewMouseListener(this));
		}

		string report_date = pCse->m_vec_trade_date[m];
		COleDateTime odt ;
		odt.ParseDateTime(report_date.c_str());
		if(m_StartDate> 0 && m_EndDate> m_StartDate)
		{
			if(odt.m_dt < m_StartDate || odt.m_dt > m_EndDate)
				continue;
		}

		double ratio = pCse->m_vec_turnover_rate[m] ;
		if(odt.m_dt> xmax) xmax = odt.m_dt;
		if(odt.m_dt< xmin) xmin = odt.m_dt;

		if(ratio > ymax) ymax = ratio;
		if(ratio < ymin) ymin = ratio;

		pSeries->AddPoint(odt.m_dt, ratio);
	}

	if(ymax>0 && xmax > xmin)
	{
		pBottomAxis->SetMinMax(xmin, xmax);
		pLeftAxis->SetMinMax(0, ymax);

		m_pChartCtrl->GetLegend()->SetVisible(true);
		m_pChartCtrl->RefreshCtrl();
	}

	m_pChartCtrl->EnableRefresh(true);
}

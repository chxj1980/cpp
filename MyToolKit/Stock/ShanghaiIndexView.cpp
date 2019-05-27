// ShanghaiIndexView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
//#include "StShanghaiIndex.h"
#include "StockMatlab.h"
#include "ShanghaiIndexView.h"

#include "MatlabShanghaiIndex.h"

#include "StockRangeSet.h"


// CShanghaiIndexView

IMPLEMENT_DYNCREATE(CShanghaiIndexView, CBaseMatlabView)

CShanghaiIndexView::CShanghaiIndexView()
{

}

CShanghaiIndexView::~CShanghaiIndexView()
{
}

BEGIN_MESSAGE_MAP(CShanghaiIndexView, CBaseMatlabView)
	ON_COMMAND(ID_SET_STOCK_RANGE, &CShanghaiIndexView::OnSetStockRange)
	ON_UPDATE_COMMAND_UI(ID_SHANGHAI_INDEX, &CShanghaiIndexView::OnUpdateShanghaiIndex)
END_MESSAGE_MAP()


// CShanghaiIndexView ��ͼ

void CShanghaiIndexView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CShanghaiIndexView ���

#ifdef _DEBUG
void CShanghaiIndexView::AssertValid() const
{
	CBaseMatlabView::AssertValid();
}

#ifndef _WIN32_WCE
void CShanghaiIndexView::Dump(CDumpContext& dc) const
{
	CBaseMatlabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShanghaiIndexView ��Ϣ�������


void CShanghaiIndexView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CMatlabShanghaiIndex * cse =  new CMatlabShanghaiIndex(m_hWnd, WM_USER_LOG_1);
	cse->m_windowInMatlab = m_windowInMatlab;
	cse->m_strIndexCode = pDoc->m_nCode;

	cse->ScheduleTask(&CMatlabShanghaiIndex::Execute1);
	m_bCalculating = true;
}

void CShanghaiIndexView::OnSetStockRange()
{
	// TODO: �ڴ���������������

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CStockRangeSet aboutDlg;
	
	if(aboutDlg.DoModal()==IDOK)
	{
		CMatlabShanghaiIndex * cse =  new CMatlabShanghaiIndex(m_hWnd, WM_USER_LOG_1);
		//	������ǰ�򿪵Ĵ��ڣ��Ա���йر�
		cse->m_windowInMatlab = m_windowInMatlab;
		cse->m_strIndexCode = pDoc->m_nCode;

		cse->m_StartDate = aboutDlg.m_StartDate;
		cse->m_EndDate = aboutDlg.m_End_Date;
		cse->ScheduleTask(&CMatlabShanghaiIndex::Execute1);

		m_bCalculating = true;
	}
}

void CShanghaiIndexView::OnUpdateShanghaiIndex(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_bCalculating==FALSE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

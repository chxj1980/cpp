// ShanghaiIndexView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"

#include "PlateShanghaiIndexView.h"

#include "MatlabShanghaiSohuPlateIndex.h"

#include "StockRangeSet.h"

//#include "StCloseWindow.h"
#include "StockMatlab.h"

// CShanghaiIndexView

IMPLEMENT_DYNCREATE(CPlateShanghaiIndexView, CBaseMatlabView)

CPlateShanghaiIndexView::CPlateShanghaiIndexView()
{

}

CPlateShanghaiIndexView::~CPlateShanghaiIndexView()
{
}

BEGIN_MESSAGE_MAP(CPlateShanghaiIndexView, CBaseMatlabView)
	ON_COMMAND(ID_SET_STOCK_RANGE, &CPlateShanghaiIndexView::OnSetStockRange)
	ON_UPDATE_COMMAND_UI(ID_SHANGHAI_INDEX, &CPlateShanghaiIndexView::OnUpdateShanghaiIndex)
END_MESSAGE_MAP()


// CShanghaiIndexView ��ͼ

void CPlateShanghaiIndexView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CShanghaiIndexView ���

#ifdef _DEBUG
void CPlateShanghaiIndexView::AssertValid() const
{
	CBaseMatlabView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlateShanghaiIndexView::Dump(CDumpContext& dc) const
{
	CBaseMatlabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShanghaiIndexView ��Ϣ�������


void CPlateShanghaiIndexView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CMatlabShanghaiSohuPlateIndex * cse =  new CMatlabShanghaiSohuPlateIndex(m_hWnd, WM_USER_LOG_1);
	cse->m_windowInMatlab = m_windowInMatlab;
	cse->m_vec_request_code = pDoc->m_vec_request_code;
	cse->m_strGraphOrTable = pDoc->m_strInput;
	cse->m_windowInMatlab = m_windowInMatlab;

	//	���뱾�� ���/���� ������־
	cse->m_vec_request_is_stock.push_back(pDoc->m_nIs_Stock);	
	cse->ScheduleTask(&CMatlabShanghaiSohuPlateIndex::Execute1);
	m_bCalculating = true;
}

void CPlateShanghaiIndexView::OnSetStockRange()
{
	// TODO: �ڴ���������������

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	/*mwArray mwOut(1, 1, mxINT32_CLASS);*/

	CStockRangeSet aboutDlg;
	aboutDlg.m_StartDate = pDoc->m_StartDate;
	aboutDlg.m_End_Date = pDoc->m_EndDate;
	
	if(aboutDlg.DoModal()==IDOK)
	{
		CMatlabShanghaiSohuPlateIndex * cse =  new CMatlabShanghaiSohuPlateIndex(m_hWnd, WM_USER_LOG_1);
		//	������ǰ�򿪵Ĵ��ڣ��Ա���йر�
		
		pDoc->m_StartDate = aboutDlg.m_StartDate;
		pDoc->m_EndDate = aboutDlg.m_End_Date;

		cse->m_windowInMatlab = m_windowInMatlab;

		cse->m_StartDate = aboutDlg.m_StartDate;
		cse->m_EndDate = aboutDlg.m_End_Date;
		cse->m_vec_request_code = pDoc->m_vec_request_code;
		cse->m_strGraphOrTable = pDoc->m_strInput;

		//	���뱾�� ���/���� ������־
		cse->m_vec_request_is_stock.push_back(pDoc->m_nIs_Stock);	
		cse->ScheduleTask(&CMatlabShanghaiSohuPlateIndex::Execute1);

		m_bCalculating = true;
	}
}

void CPlateShanghaiIndexView::OnUpdateShanghaiIndex(CCmdUI *pCmdUI)
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

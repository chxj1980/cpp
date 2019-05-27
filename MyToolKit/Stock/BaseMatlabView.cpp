// BaseMatlabView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "BaseMatlabView.h"

#include "CalcCninfoAnnouncePDFQuery.h"
//#include "stocktest.h"
//#include "StOpenWindow.h"
//#include "StCloseWindow.h"

#include "StockMatlab.h"

// CBaseMatlabView

int CBaseMatlabView::g_windowInMatlab = 1;

IMPLEMENT_DYNCREATE(CBaseMatlabView, CBaseMessageView)

CBaseMatlabView::CBaseMatlabView()
{
	//bool res = stocktestInitialize();
	m_plotH = NULL;
	m_windowInMatlab = -1;
	m_bCalculating = false;

}

CBaseMatlabView::~CBaseMatlabView()
{
	if(m_windowInMatlab >=0 )
	{
		try{
			// yangbin matlab
			mwArray mwOut(1, 1, mxINT32_CLASS);

			char wndName[32] = { 0 };
			sprintf_s(wndName, 32, "%d", m_windowInMatlab);
			StCloseWindow(1, mwOut, wndName);
		}
		catch(CException & e)
		{
			stringstream ss;
			;
			string ttt = ss.str();
			int k = 1;
		}
		
	}
	
}

BEGIN_MESSAGE_MAP(CBaseMatlabView, CBaseMessageView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBaseMatlabView ��ͼ

void CBaseMatlabView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CBaseMatlabView ���

#ifdef _DEBUG
void CBaseMatlabView::AssertValid() const
{
	CBaseMessageView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseMatlabView::Dump(CDumpContext& dc) const
{
	CBaseMessageView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseMatlabView ��Ϣ�������

void CBaseMatlabView::OnInitialUpdate()
{
	CBaseMessageView::OnInitialUpdate();

	g_windowInMatlab++;
	m_windowInMatlab = g_windowInMatlab;

	char wndName[32] = { 0 };
	sprintf_s(wndName, 32, "%d", m_windowInMatlab);

	// yangbin matlab
	StOpenWindow(wndName);

	do{
		char wndName[32] = { 0 };
		sprintf_s(wndName, 32, "Stock%d", m_windowInMatlab);

		m_plotH = ::FindWindow(NULL, wndName);
		if(::IsWindow(m_plotH))
		{
			//	���� View ����Ϊ Matlab ���ڵĸ�����
			::SetParent(m_plotH, this->GetSafeHwnd());
			CWnd * pWnd = NULL;
			pWnd = FromHandle(m_plotH);

			CRect rect;
			GetClientRect(&rect);
			pWnd->MoveWindow(&rect, false);
			pWnd->ModifyStyle(WS_CAPTION|WS_BORDER, WS_MAXIMIZE, 0);
			Invalidate(TRUE);
			break;
		}
		else
			Sleep(100);
	}while(1);
	

	// TODO: �ڴ����ר�ô����/����û���
	Startup();
}



void CBaseMatlabView::ProcessXmlWParam(string msgType,string code,string model,\
										string param1,string param2,string param3)
{
	if(msgType=="TaskFinished")
	{
		stringstream ss;
		ss << "����" << (param1) << "�� �������. ";

		CCalculateTask * cse = CCalculateTask::FetchTask(atol(param1.c_str()));

		// ��ס����ͼ�� Matlab �д򿪵Ĵ���
		if(m_windowInMatlab == cse->m_windowInMatlab)
			ss << "���ڱ�ʶ OK";
		else
			ss << "���ڱ�ʶ Fail";

		RedrawGridCtrl(cse);
		if(cse!=NULL)
			delete cse;
		sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);
		m_bCalculating = false;
	}
	//RedrawGridCtrl();
}

/*
void CBaseMatlabView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CCalcCninfoAnnouncePDFQuery * cse =  new CCalcCninfoAnnouncePDFQuery(m_hWnd, WM_USER_LOG_1);
	cse->m_request_like = "";
	cse->m_page_no = 0;

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcCninfoAnnouncePDFQuery::Execute1);
}
*/


void CBaseMatlabView::RedrawGridCtrl(CCalculateTask * cse)
{

	CCalculateTask * pCse = (CCalculateTask *)cse;
}


void CBaseMatlabView::OnSize(UINT nType, int cx, int cy)
{
	CBaseMessageView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if(::IsWindow(m_plotH))
	{
		::MoveWindow(m_plotH, 0, 0, cx, cy, true);
	}
}


void CBaseMatlabView::PostFocusChanged()
{
	if(::IsWindow(m_plotH))
	{
		//	���� View ����Ϊ Matlab ���ڵĸ�����
		CWnd * pWnd = NULL;
		pWnd = FromHandle(m_plotH);

		CRect rect;
		GetClientRect(&rect);
		pWnd->MoveWindow(&rect, false);
	}
}
void CBaseMatlabView::OnDestroy()
{
	CBaseMessageView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	if(m_windowInMatlab >=0 && ::IsWindow(m_plotH))
	{
		// yangbin matlab
		try{
			mwArray mwOut(1, 1, mxINT32_CLASS);

			char wndName[32] = { 0 };
			sprintf_s(wndName, 32, "%d", m_windowInMatlab);
			StCloseWindow(1, mwOut, wndName);
		}
		catch(mwException & e)
		{
			stringstream ss;
			ss << e.what();
			string ttt = ss.str();
			int k = 1;
		}
		m_windowInMatlab = -1;
	}
}

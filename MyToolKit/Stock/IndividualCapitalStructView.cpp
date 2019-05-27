// IndividualCapitalStructView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualCapitalStructView.h"
#include "IndividualShareDoc.h"


// CIndividualCapitalStructView

IMPLEMENT_DYNCREATE(CIndividualCapitalStructView, CBaseGridCtlView)

CIndividualCapitalStructView::CIndividualCapitalStructView()
{

}

CIndividualCapitalStructView::~CIndividualCapitalStructView()
{
}

BEGIN_MESSAGE_MAP(CIndividualCapitalStructView, CBaseGridCtlView)
END_MESSAGE_MAP()


// CIndividualCapitalStructView ��ͼ

void CIndividualCapitalStructView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualCapitalStructView ���

#ifdef _DEBUG
void CIndividualCapitalStructView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualCapitalStructView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndividualCapitalStructView ��Ϣ�������

void CIndividualCapitalStructView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CStockApp * pApp = (CStockApp *)AfxGetApp();
	//JMutexAutoLock lock(pApp->m_mutexStockinfo);
	StockInfo_Reqeust req;
	req.code = atoi(pDoc->m_nCode.c_str());
	req.hwnd = m_hWnd;
	pApp->m_listStockinfoReq.push_front(req);

}


void CIndividualCapitalStructView::ProcessXmlWParam(string msgType, string code,string model, \
													string param1,string param2,string param3)
{
	RedrawGridCtrl();
}


void CIndividualCapitalStructView::RedrawGridCtrl()
{

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		CCapitalStructOf10jqka capital ;
		CBussinessUtils::GetCapitalStruct(atoi(pDoc->m_nCode.c_str()), capital);
		if(capital.m_vec_real_date.size()>0)
		{
			m_pGridCtrl->SetRowCount(capital.m_vec_real_date.size() + 1);
			m_pGridCtrl->SetColumnCount(5);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(0);

			SetGridCell(0,0, true, "��Ʊ����");
			SetGridCell(0,1, true, "�䶯����");
			SetGridCell(0,2, true, "�䶯ԭ��");
			SetGridCell(0,3, true, "��ͨA��������ɣ�");
			SetGridCell(0,4, true, "��A��������ɣ�");
			
			for(int i=0, k =capital.m_vec_real_date.size() - 1; k>=0 ; i++, k--)
			{
				CString str;
				str.Format("%06d", capital.m_nCode);
				SetGridCell(i + 1, 0, false, str.GetBuffer());
				SetGridCell(i + 1, 1, false, capital.m_vec_real_date[k]);
				SetGridCell(i + 1, 2, false, capital.m_vec_change_reason_desc[k]);
				str.Format("%12.2f", capital.m_vec_ashares[k]);
				SetGridCell(i + 1, 3, false, str.GetBuffer());
				str.Format("%12.2f", capital.m_vec_a_total_shares[k]);
				SetGridCell(i + 1, 4, false, str.GetBuffer());
			}

		}
		
		m_pGridCtrl->AutoSize();
	}

}
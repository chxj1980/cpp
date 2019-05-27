// PlateGrossProfitListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "MainFrm.h"
#include "IndividualShareDoc.h"
#include "PlateGrossProfitListView.h"
#include "CalculateStockInfoEx.h"


// CPlateGrossProfitListView

IMPLEMENT_DYNCREATE(CPlateGrossProfitListView, CBaseGridCtlView)

CPlateGrossProfitListView::CPlateGrossProfitListView()
{

}

CPlateGrossProfitListView::~CPlateGrossProfitListView()
{
}

BEGIN_MESSAGE_MAP(CPlateGrossProfitListView, CBaseGridCtlView)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
END_MESSAGE_MAP()


// CPlateGrossProfitListView ��ͼ

void CPlateGrossProfitListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CPlateGrossProfitListView ���

#ifdef _DEBUG
void CPlateGrossProfitListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlateGrossProfitListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPlateGrossProfitListView ��Ϣ�������


void CPlateGrossProfitListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalculateStockInfoEx * cse =  new CCalculateStockInfoEx(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalculateStockInfoEx::RecentMainIncomeComposition1);
}


void CPlateGrossProfitListView::ProcessXmlWParam(string msgType,string code,string model,\
										   string param1,string param2,string param3)
{
	if(msgType=="TaskFinished")
	{
		stringstream ss;
		ss << "����" << (param1) << "�� �������. ";

		CCalculateTask * cse = CCalculateTask::FetchTask(atol(param1.c_str()));
		RedrawGridCtrl(cse);
		if(cse!=NULL)
			delete cse;
		sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);
	}
}



void CPlateGrossProfitListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(str);
	//////////////////////////////////////////////////////////////////////////
	//	��Ʊͣ������ʾ��ǰѡ��� ��Ʊ

	if(pItem->iRow>0)
	{
		CString str = m_pGridCtrl->GetItemText(pItem->iRow, 1);
		m_MessageCtrl.FocusStockOnLeftPane(str.GetBuffer());
	}
}

void CPlateGrossProfitListView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	if (pWnd->GetSafeHwnd() == m_pGridCtrl->GetSafeHwnd())
	{
		m_pGridCtrl->ScreenToClient(&point);
		CCellID cell = m_pGridCtrl->GetCellFromPt(point);
		CString str;
		str.Format(_T("Context menu called on row %d, col %d\n"), cell.row, cell.col);
		//AfxMessageBox(str);

	}
}

void CPlateGrossProfitListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalculateStockInfoEx * pStockInfoEx = (CCalculateStockInfoEx *)cse;
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_pGridCtrl->SetRowCount(pStockInfoEx->m_vec_code.size()+1);
			m_pGridCtrl->SetColumnCount(6);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(2);
			m_pGridCtrl->SetHeaderSort(TRUE);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
		{
			for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT;
				Item.row = row;
				Item.col = col;
				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					string val;
					if(col==0)		val = "���";
					else if(col==1)	val = "����";
					else if(col==2)	val = "����";
					else if(col==3) val = "����";
					else if(col==4) val = "�ɱ�";
					else if(col==5) val = "ë����";
					
					Item.strText.Format(_T("%s"), val.c_str());
				} 
				else 
				{
					if(col==0)
						Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
					else
						Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;

					if( col==0 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}

					if(col==3 || col==4 || col==5 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2)	val = Utf8_GBK(pStockInfoEx->m_vec_composition_name[row-1]);
					else if(col==3) val = Double2String(pStockInfoEx->m_vec_income[row-1]);
					else if(col==4) val = Double2String(pStockInfoEx->m_vec_cost[row-1]);
					else if(col==5) val = Double2String(pStockInfoEx->m_vec_gross_profit_rate[row-1]);
					
					Item.strText.Format(_T("%s"), val.c_str());

					if(col==5 )
					{
						Item.mask    |= (GVIF_FGCLR);
						if(pStockInfoEx->m_vec_gross_profit_rate[row-1]>0)
							Item.crFgClr = RGB(255, 64, 64);
						else
							Item.crFgClr = RGB(0, 163, 0);
					}

				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->AutoSize();
	}
}



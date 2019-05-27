#include "StdAfx.h"

#include "Stock.h"
#include "MainFrm.h"
#include "IndividualShareDoc.h"
#include "PlateStockListView.h"
#include "CalcRecentStockSummary.h"

IMPLEMENT_DYNCREATE(CPlateStockListView, CBaseGridCtlView)

CPlateStockListView::CPlateStockListView(void)
{
}

CPlateStockListView::~CPlateStockListView(void)
{
}


BEGIN_MESSAGE_MAP(CPlateStockListView, CBaseGridCtlView)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
END_MESSAGE_MAP()


// CIndividualCsvFileView ��ͼ

void CPlateStockListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualCsvFileView ���

#ifdef _DEBUG
void CPlateStockListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlateStockListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


void CPlateStockListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalcRecentStockSummary * cse =  new CCalcRecentStockSummary(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcRecentStockSummary::Execute1);
}


void CPlateStockListView::ProcessXmlWParam(string msgType,string code,string model,\
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


void CPlateStockListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalcRecentStockSummary * pStockInfoEx = (CCalcRecentStockSummary *)cse;
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_pGridCtrl->SetRowCount(pStockInfoEx->m_vec_code.size()+1);
			m_pGridCtrl->SetColumnCount(14);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(3);
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
					else if(col==3) val = "A���ܹ�������ɣ�";
					else if(col==4) val = "�꾻�����㣨��Ԫ��";
					else if(col==5) val = "�����������";
					else if(col==6) val = "���̼ۣ�Ԫ��";
					else if(col==7) val = "��ӯ�ʣ�PE��";
					else if(col==8) val = "����ֵ���ڣ�";
					else if(col==9) val = "��ͨ��ֵ���ڣ�";

					else if(col==10) val = "���Ԥ������";
					else if(col==11) val = "ҵ��Ԥ�棨%��";
					else if(col==12) val = "A����������";
					else if(col==13) val = "����Ʊ�����";
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

					if(col==3 || col==4 || col==6 || col==7 || col==8 || col==11)
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}

					if(col==5 || col == 10 || col == 12 || col ==13)
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellDateTime)))
							return;
					}

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2)	val = pStockInfoEx->m_vec_abbreviation[row-1];
					else if(col==3) val = Double2String(pStockInfoEx->m_vec_a_total_share[row -1]);
					else if(col==4) val = Double2String(pStockInfoEx->m_vec_earning_per_year[row-1]/10000.0);
					else if(col==5) val = pStockInfoEx->m_vec_recent_trade_date[row-1];
					else if(col==6) val = Double2String(pStockInfoEx->m_vec_close[row-1]);
					else if(col==7) val = Double2String(pStockInfoEx->m_vec_pe[row-1]);
					else if(col==8) val = Double2String(pStockInfoEx->m_vec_a_total_value[row-1]);
					else if(col==9) val = Double2String(pStockInfoEx->m_vec_a_circulating_value[row-1]);
					else if(col==10) val = pStockInfoEx->m_vec_recent_forecast_date[row-1];
					else if(col==11) val = Double2String(pStockInfoEx->m_vec_recent_forecast_rate[row-1]);
					else if(col==12) val = pStockInfoEx->m_vec_a_time_to_market[row-1];
					else if(col==13) val = pStockInfoEx->m_vec_recent_finance_date[row-1];
					Item.strText.Format(_T("%s"), val.c_str());

					if(col==11 )
					{
						Item.mask    |= (GVIF_FGCLR);
						if(pStockInfoEx->m_vec_recent_forecast_rate[row-1]>0)
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
		m_pGridCtrl->SetColumnWidth(2, 80);
	}
}


void CPlateStockListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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

void CPlateStockListView::OnContextMenu(CWnd* pWnd, CPoint point)
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
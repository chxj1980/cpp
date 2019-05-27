// AllMcstStockListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "AllMcstStockListView.h"
#include "CalcMcstListData.h"

// CAllMcstStockListView

IMPLEMENT_DYNCREATE(CAllMcstStockListView, CBaseGridCtlView)

CAllMcstStockListView::CAllMcstStockListView()
{

}

CAllMcstStockListView::~CAllMcstStockListView()
{
}

BEGIN_MESSAGE_MAP(CAllMcstStockListView, CBaseGridCtlView)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CAllMcstStockListView::OnTableAddToSelfSelect)
END_MESSAGE_MAP()


// CAllMcstStockListView ��ͼ

void CAllMcstStockListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CAllMcstStockListView ���

#ifdef _DEBUG
void CAllMcstStockListView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CAllMcstStockListView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAllMcstStockListView ��Ϣ�������



void CAllMcstStockListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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
void CAllMcstStockListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	Startup();	
}



void CAllMcstStockListView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalcMcstListData * cse =  new CCalcMcstListData(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcMcstListData::Execute1);
	m_bCalculating = true;
}


void CAllMcstStockListView::ProcessXmlWParam(string msgType,string code,string model,\
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
		m_bCalculating = false;
	}
	//RedrawGridCtrl();
}


void CAllMcstStockListView::RedrawGridCtrl(CCalculateTask * cse)
{

	CCalcMcstListData * pStockInfoEx = (CCalcMcstListData *)cse;
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_pGridCtrl->SetRowCount(pStockInfoEx->m_vec_code.size()+1);
			m_pGridCtrl->SetColumnCount(11);
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
					else if(col==2) val = "��Ʊ���";
					else if(col==3) val = "���������";
					else if(col==4) val = "�ɽ�����Ԫ��";
					else if(col==5) val = "�����ʣ�%��";
					else if(col==6) val = "���̼ۣ�Ԫ��";
					else if(col==7) val = "�ǵ�����%��";
					else if(col==8) val = "ƽ���ɱ��ۣ�Ԫ��";
					else if(col==9) val = "ƽ���ɱ����ǵ�����%��";

					else if(col==10) val = "ƫ����ȣ�%��";

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


					if( col>=4 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}

					

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2) val = pStockInfoEx->m_vec_abbreviation[row-1];
					else if(col==3)	val =  pStockInfoEx->m_vec_trade_date[row-1];
					else if(col==4)	val =  Double2String(pStockInfoEx->m_vec_turnover[row-1]);
					else if(col==5) val =  Double2String(pStockInfoEx->m_vec_turnover_rate[row-1]);
					else if(col==6) val =  Double2String(pStockInfoEx->m_vec_price[row-1]);
					else if(col==7)
					{
						Item.mask    |= (GVIF_FGCLR);
						val = Double2String(pStockInfoEx->m_vec_change_rate[row-1]);

						if(pStockInfoEx->m_vec_change_rate[row-1] >0)
							Item.crFgClr = RGB(255, 64, 64);
						else
							Item.crFgClr = RGB(0, 163, 0);
					}

					else if(col==8) val =  Double2String(pStockInfoEx->m_vec_mcst_price[row-1]);
					else if(col==9)
					{
						Item.mask    |= (GVIF_FGCLR);
						val = Double2String(pStockInfoEx->m_vec_mcst_price_change_rate[row-1]);

						if(pStockInfoEx->m_vec_mcst_price_change_rate[row-1] >0)
							Item.crFgClr = RGB(255, 64, 64);
						else
							Item.crFgClr = RGB(0, 163, 0);
					}

					else if(col==10)
					{
						Item.mask    |= (GVIF_FGCLR);
						val = Double2String(pStockInfoEx->m_vec_mcst_percent[row-1]);

						if(pStockInfoEx->m_vec_mcst_percent[row-1] >0)
							Item.crFgClr = RGB(255, 64, 64);
						else
							Item.crFgClr = RGB(0, 163, 0);
					}
					
					Item.strText.Format(_T("%s"), val.c_str());

				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetColumnWidth(2, 80);
	}

}



void CAllMcstStockListView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	TableAddToSelfSelect();
}

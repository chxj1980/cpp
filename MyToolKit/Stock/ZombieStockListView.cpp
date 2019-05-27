// ZombieStockList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "ZombieStockListView.h"
#include "CalculateStockInfoEx.h"


// CZombieStockList

IMPLEMENT_DYNCREATE(CZombieStockListView, CBaseGridCtlView)

CZombieStockListView::CZombieStockListView()
{

}

CZombieStockListView::~CZombieStockListView()
{
}

BEGIN_MESSAGE_MAP(CZombieStockListView, CBaseGridCtlView)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
END_MESSAGE_MAP()


// CZombieStockList ��ͼ

void CZombieStockListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CZombieStockList ���

#ifdef _DEBUG
void CZombieStockListView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CZombieStockListView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CZombieStockList ��Ϣ�������

void CZombieStockListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalculateStockInfoEx * cse =  new CCalculateStockInfoEx(m_hWnd, WM_USER_LOG_1);

	CStockApp * pApp = (CStockApp *)AfxGetApp();

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalculateStockInfoEx::ZombieStockList1);
}



void CZombieStockListView::ProcessXmlWParam(string msgType,string code,string model,\
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


void CZombieStockListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalculateStockInfoEx * pStockInfoEx = (CCalculateStockInfoEx *)cse;
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
					else if(col==3) val = "���ݲƱ�ʱ��";
					else if(col==4)	val = "�ɱ�";
					else if(col==5) val = "ĸ��˾���ʲ���Ԫ��";
					else if(col==6) val = "�ʲ��ܼƣ�Ԫ��";
					else if(col==7) val = "�����ʲ���������Ԫ��";
					else if(col==8) val = "ÿ�����棨Ԫ��";
					else if(col==9) val = "ÿ�ɾ��ʲ���Ԫ��";
					else if(col==10) val = "ÿ��δ��������Ԫ��";
					Item.strText.Format(_T("%s"), val.c_str());
				} 
				else 
				{
					if(col==0)
						Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
					else
						Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;

					if( col==4 || col==5 || col==6 || col==7 || col==8 || col==9 || col==10)
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}

					if(col==3 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellDateTime)))
							return;
					}

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2) val = pStockInfoEx->m_vec_abbreviation[row-1];
					else if(col==3)	val =  ReplaceChar(pStockInfoEx->m_vec_report_date[row-1], '-',"");
					else if(col==4) val = Double2Currency(pStockInfoEx->m_vec_registered_capital[row-1], true);
					else if(col==5) 
					{
						//	����ĸ��˾���ʲ�
						double tmp = pStockInfoEx->m_vec_total_owners_equity_belongs_to_parent_company[row-1];
						val = Double2Currency(tmp, true);
					}
					else if(col==6) val = Double2Currency(pStockInfoEx->m_vec_total_assets[row-1], true);
					else if(col==7)
					{
						//	�����ʲ�������
						double tmp = pStockInfoEx->m_vec_intangibel_assets[row-1];
						tmp += pStockInfoEx->m_vec_goodwill[row-1];
						val = Double2Currency(tmp, true);
					}
					else if(col==8)
					{
						//	ÿ�ɾ�����
						double net_profits = pStockInfoEx->m_vec_net_profit_belonging_to_parent_company[row-1];
						net_profits = net_profits/pStockInfoEx->m_vec_registered_capital[row-1];
						val = Double2String(net_profits);
						val = String2Currency(val);
					}
					else if(col==9) 
					{
						// ÿ�ɾ��ʲ�
						double net_assets = pStockInfoEx->m_vec_total_owners_equity_belongs_to_parent_company[row-1];
						net_assets /= pStockInfoEx->m_vec_registered_capital[row-1]; 
						val = Double2String(net_assets);
						val = String2Currency(val);

					}
					else if(col==10)
					{
						double undistributed = pStockInfoEx->m_vec_undistributed_profits[row-1];
						undistributed /= pStockInfoEx->m_vec_registered_capital[row-1];
						val = Double2String(undistributed);
						val = String2Currency(val);
					}
					
					Item.strText.Format(_T("%s"), val.c_str());

			
					if(col==10 )
					{
						Item.mask    |= (GVIF_FGCLR);
						if(pStockInfoEx->m_vec_undistributed_profits[row-1]>0)
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



void CZombieStockListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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

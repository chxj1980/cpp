// AllThisYearBonusListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "AllThisYearBonusListView.h"
#include "CalcThisYearBonusSummary.h"

// CAllThisYearBonusListView

IMPLEMENT_DYNCREATE(CAllThisYearBonusListView, CBaseGridCtlView)

CAllThisYearBonusListView::CAllThisYearBonusListView()
{

}

CAllThisYearBonusListView::~CAllThisYearBonusListView()
{
}

BEGIN_MESSAGE_MAP(CAllThisYearBonusListView, CBaseGridCtlView)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CAllThisYearBonusListView::OnTableAddToSelfSelect)
END_MESSAGE_MAP()


// CAllThisYearBonusListView ��ͼ

void CAllThisYearBonusListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CAllThisYearBonusListView ���

#ifdef _DEBUG
void CAllThisYearBonusListView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CAllThisYearBonusListView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAllThisYearBonusListView ��Ϣ�������




void CAllThisYearBonusListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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

void CAllThisYearBonusListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	Startup();	
}



void CAllThisYearBonusListView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CCalcThisYearBonusSummary * cse =  new CCalcThisYearBonusSummary(m_hWnd, WM_USER_LOG_1);

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcThisYearBonusSummary::Execute1);
	m_bCalculating = true;
}


void CAllThisYearBonusListView::ProcessXmlWParam(string msgType,string code,string model,\
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


void CAllThisYearBonusListView::RedrawGridCtrl(CCalculateTask * cse)
{

	CCalcThisYearBonusSummary * pStockInfoEx = (CCalcThisYearBonusSummary *)cse;
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_pGridCtrl->SetRowCount(pStockInfoEx->m_vec_code.size()+1);
			m_pGridCtrl->SetColumnCount(11 + 1);
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
					else if(col==3) val = "�ֺ����";
					else if(col==4) val = "�͹�(��)";
					else if(col==5) val = "ת���ɣ��ɣ�";
					else if(col==6) val = "�ֽ�ֺ죨Ԫ��";
					else if(col==7) val = "����ɼۣ�Ԫ��";
					else if(col==8) val = "�������(%)";
					else if(col==9) val = "��Ȩ�Ǽ���";
					else if(col==10) val = "��Ȩ��Ϣ��";
					else if(col==11) val = "������չ";

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

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2)	val = pStockInfoEx->m_vec_abbreviation[row-1];
					else if(col==3) val = pStockInfoEx->m_vec_bonus_year[row-1];
					else if(col==4) val = Double2String(pStockInfoEx->m_vec_bonus_share[row-1]);
					else if(col==5) val = Double2String(pStockInfoEx->m_vec_reserve_to_common_share[row-1]);
					else if(col==6) val = Double2String(pStockInfoEx->m_vec_bonus_cash[row-1]);
					else if(col==7) val = Double2String(pStockInfoEx->m_vec_recent_close[row-1]);
					else if(col==8)
					{
						val = Double2String(pStockInfoEx->m_vec_earning_percent[row-1]*100);
						Item.mask    |= (GVIF_FGCLR);
						Item.crFgClr = RGB(255, 64, 64);
					}
					else if(col==9) val = pStockInfoEx->m_vec_right_record_date[row-1];
					else if(col==10) val = pStockInfoEx->m_vec_exit_right_date[row-1];
					else if(col==11) val = pStockInfoEx->m_vec_event_state[row-1];

					/*�����Ѿ�������Ȩ�Ǽ��յģ����б���ɫ�䰵*/
					string strRightRecordDate = pStockInfoEx->m_vec_right_record_date[row-1];
					if(strRightRecordDate!="0000-00-00")
					{
						COleDateTime odt ;
						odt.ParseDateTime(strRightRecordDate.c_str());

						COleDateTime t = COleDateTime::GetCurrentTime();
						if(odt.m_dt< t.m_dt)
						{
							Item.mask    |= (GVIF_BKCLR);
							Item.crFgClr = RGB(64, 64, 64);
						}
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



void CAllThisYearBonusListView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	TableAddToSelfSelect();
}

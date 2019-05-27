// HexunResearchPaperListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "CninfoShareHoldingStatisticsView.h"
#include "CalcCninfoShareHoldingStatistics.h"

#include "SimpleInputBox.h"
#include "SelfSelectPlateDlg.h"

#include "PDFStructureDlg.h"


// CHexunResearchPaperListView

IMPLEMENT_DYNCREATE(CCninfoShareHoldingStatisticsView, CBaseGridCtlView)

CCninfoShareHoldingStatisticsView::CCninfoShareHoldingStatisticsView()
{
	/*��ʾ��ҳ��*/
	m_bPagination = true;
	
}

CCninfoShareHoldingStatisticsView::~CCninfoShareHoldingStatisticsView()
{
}

BEGIN_MESSAGE_MAP(CCninfoShareHoldingStatisticsView, CBaseGridCtlView)
	ON_COMMAND(ID_TABLE_ADVANCED_QUERY, &CCninfoShareHoldingStatisticsView::OnTableAdvancedQuery)
	ON_UPDATE_COMMAND_UI(ID_TABLE_ADVANCED_QUERY, &CCninfoShareHoldingStatisticsView::OnUpdateTableAdvancedQuery)
END_MESSAGE_MAP()


// CCninfoShareHoldingListView ��ͼ

void CCninfoShareHoldingStatisticsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CCninfoShareHoldingListView ���

#ifdef _DEBUG
void CCninfoShareHoldingStatisticsView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CCninfoShareHoldingStatisticsView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCninfoShareHoldingListView ��Ϣ�������



void CCninfoShareHoldingStatisticsView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("����(�� 2016��4����)"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP, false , _T("") };
		m_vecFindItem.insert(m_vecFindItem.end(), it);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("�ɶ�����"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP, false , _T("") };
		m_vecFindItem.insert(m_vecFindItem.end(), it);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("�ɶ�����"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP, false , _T("") };
		m_vecFindItem.insert(m_vecFindItem.end(), it);
	}


	m_strLike = "";
	Startup();
}


void CCninfoShareHoldingStatisticsView::OnTableAdvancedQuery()
{
	// TODO: �ڴ���������������

	CDyncItemFindDlg infd(m_vecFindItem);

	infd.Init( _T("��ѯ����"), _T("��ѯ����"));
	if(infd.DoModal()==IDOK)
	{
		m_strLike = "";
		/*m_strLike = dlg.m_strInput.GetBuffer();*/
		string strValue = string(m_vecFindItem[0].strValue);
		if(strValue.empty()==false)
		{
			m_strLike += " and year_quarter like \'";
			m_strLike += strValue + "\' ";
		}
		
		strValue = string(m_vecFindItem[1].strValue);
		if(strValue.empty()==false)
		{
			m_strLike += " and share_holder like \'";
			m_strLike += strValue + "\' ";
		}
		
		strValue = string(m_vecFindItem[2].strValue);
		if(strValue.empty()==false)
		{
			m_strLike += " and holder_character like \'";
			m_strLike += strValue + "\' ";
		}
		m_nPageNo = 1;
		Startup();
	}
}

void CCninfoShareHoldingStatisticsView::ProcessXmlWParam(string msgType,string code,string model,\
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
}


void CCninfoShareHoldingStatisticsView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalcCninfoShareHoldingStatistics * pStockInfoEx = (CCalcCninfoShareHoldingStatistics *)cse;
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	m_nPageNo = pStockInfoEx->m_page_no;
	m_nMaxPage = pStockInfoEx->m_max_page;
	CString str1;
	str1.Format("�� %d ҳ  �� %d ҳ", m_nPageNo, m_nMaxPage);
	m_pStaticShowPage->SetWindowText(str1);

	stringstream ss;
	if(m_strLike.empty()==false)
	{
		if(ss.str().empty()==false)
			ss << ",";
		ss << "�ؼ��֣�" << m_strLike;
	}
	if(m_sPlateName.empty()==false)
	{
		if(ss.str().empty()==false)
			ss << ",";
		ss << "��ѡ��飺" << m_sPlateName;
	}

	if(ss.str().empty()==false)
	{
		m_pStaticTip->SetWindowText(ss.str().c_str());
	}

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_pGridCtrl->SetRowCount(pStockInfoEx->m_vec_year_quarter.size()+1);
			m_pGridCtrl->SetColumnCount(5);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
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
						
			string str_area_of_structure = "";

			for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
			{ 
				GV_ITEM Item;
				Item.mask = GVIF_TEXT|GVIF_FORMAT ;
				Item.row = row;
				Item.col = col;
				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;
					string val;
					if(col==0)		val = "���";
					else if(col==1)	val = "����";
					else if(col==2)	val = "�ɶ�����";
					else if(col==3)	val = "�ɶ�����";
					else if(col==4)	val = "��˾����";
					
					Item.strText.Format(_T("%s"), val.c_str());
				} 
				else 
				{
										
					if(col==0)
						Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
					else
						Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;

					if( col==4 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}
				

					string val ;
					
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = pStockInfoEx->m_vec_year_quarter[row-1];
					else if(col==2) val = pStockInfoEx->m_vec_share_holder[row-1];
					
					else if(col==3)	val = pStockInfoEx->m_vec_holder_character[row-1];
					else if(col==4)	val = Int2String(pStockInfoEx->m_vec_company_number[row-1]);
					

					Item.strText.Format(_T("%s"), val.c_str());

				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->EnableTitleTips(TRUE);		//	�ر�ÿ����Ԫ����ı������� ������ʾ
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetColumnWidth(2, 300);


		//	ȷ���еĸ߶�
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++)
		{
			CString strrr = m_pGridCtrl->GetItemText(row,2);
			CGridCellBase* pCell = m_pGridCtrl->GetCell(row,2);
			if(pCell)
			{
				CSize si = pCell->GetTextExtentByWidth(strrr, 300);
				m_pGridCtrl->SetRowHeight(row, si.cy);
			}

		}
	}
}




void CCninfoShareHoldingStatisticsView::OnPageUpdate()
{
	Startup();
}

void CCninfoShareHoldingStatisticsView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CCalcCninfoShareHoldingStatistics * cse =  new CCalcCninfoShareHoldingStatistics(m_hWnd, WM_USER_LOG_1);
	cse->m_request_like = m_strLike;
	cse->m_page_no = m_nPageNo;

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcCninfoShareHoldingStatistics::Execute1);
	m_bCalculating = true;
}

void CCninfoShareHoldingStatisticsView::OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_bCalculating)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
	}
}


void CCninfoShareHoldingStatisticsView::PostGridDblClick(int nRow)
{
	// ���� ���޸� ���� ɾ���� �Ի���

	
}
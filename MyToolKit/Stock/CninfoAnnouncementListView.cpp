// HexunResearchPaperListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "CninfoAnnouncementListView.h"
#include "CalcCninfoAnnouncementQuery.h"

#include "SimpleInputBox.h"
#include "SelfSelectPlateDlg.h"

#include "PDFStructureDlg.h"

// CHexunResearchPaperListView

IMPLEMENT_DYNCREATE(CCninfoAnnouncementListView, CBaseGridCtlView)

CCninfoAnnouncementListView::CCninfoAnnouncementListView()
{
	/*��ʾ��ҳ��*/
	m_bPagination = true;
	
}

CCninfoAnnouncementListView::~CCninfoAnnouncementListView()
{
}

BEGIN_MESSAGE_MAP(CCninfoAnnouncementListView, CBaseGridCtlView)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
	ON_COMMAND(ID_TABLE_ADVANCED_QUERY, &CCninfoAnnouncementListView::OnTableAdvancedQuery)
	ON_UPDATE_COMMAND_UI(ID_TABLE_ADVANCED_QUERY, &CCninfoAnnouncementListView::OnUpdateTableAdvancedQuery)
	
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CCninfoAnnouncementListView::OnTableAddToSelfSelect)
END_MESSAGE_MAP()


// CHexunResearchPaperListView ��ͼ

void CCninfoAnnouncementListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CHexunResearchPaperListView ���

#ifdef _DEBUG
void CCninfoAnnouncementListView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CCninfoAnnouncementListView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHexunResearchPaperListView ��Ϣ�������



void CCninfoAnnouncementListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_strLike = "";
	Startup();
}



void CCninfoAnnouncementListView::ProcessXmlWParam(string msgType,string code,string model,\
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


void CCninfoAnnouncementListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalcCninfoAnnouncementQuery * pStockInfoEx = (CCalcCninfoAnnouncementQuery *)cse;
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
			m_pGridCtrl->SetRowCount(pStockInfoEx->m_vec_code.size()+1);
			m_pGridCtrl->SetColumnCount(8);
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
					else if(col==3) val = "����";
					else if(col==4) val = "URL";
					else if(col==5)	val = "����";
					else if(col==6) val = "����";
					else if(col==7)	val = "�ṹ����";
					
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
				

					if(col==3 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellDateTime)))
							return;
					}
					
					if(col==4 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridURLCell)))
							return;
					}

					if(col==5)
					{
						Item.nFormat = DT_RIGHT|DT_WORDBREAK|DT_EDITCONTROL|DT_NOPREFIX|DT_END_ELLIPSIS;
					}

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2) val = pStockInfoEx->m_vec_abbreviation[row-1];
					else if(col==3)	val =  pStockInfoEx->m_vec_report_date[row-1];

					else if(col==4)	val =  "http://www.cninfo.com.cn/" + pStockInfoEx->m_vec_url[row-1];

					else if(col==5)	val =  pStockInfoEx->m_vec_title[row-1];
					else if(col==6)	val =  pStockInfoEx->m_vec_type[row-1];
					else if(col==7)	
					{
						if(pStockInfoEx->m_vec_analyzed[row-1]>0)
							val =  pStockInfoEx->m_vec_announcementId[row-1];
						else
							val = "0";
					}
					Item.strText.Format(_T("%s"), val.c_str());

				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->EnableTitleTips(FALSE);		//	�ر�ÿ����Ԫ����ı������� ������ʾ
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetColumnWidth(2, 80);
		m_pGridCtrl->SetColumnWidth(4, 60);
		m_pGridCtrl->SetColumnWidth(5, 500);

		//	ȷ���еĸ߶�
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++)
		{
			CString strrr = m_pGridCtrl->GetItemText(row,5);
			CGridCellBase* pCell = m_pGridCtrl->GetCell(row,5);
			if(pCell)
			{
				CSize si = pCell->GetTextExtentByWidth(strrr, 500);
				m_pGridCtrl->SetRowHeight(row, si.cy);
			}

		}
	}
}



void CCninfoAnnouncementListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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

	//////////////////////////////////////////////////////////////////////////
	//	�������ĵ��ṹ�������Ի���

	if(pItem->iColumn==7 && pItem->iRow>0)
	{

		CString strrr = m_pGridCtrl->GetItemText(pItem->iRow, 7);
		int idx = atoi(strrr.GetBuffer());
		if(idx > 0)
		{
			CPDFStructureDlg  dlg;
			dlg.m_announcementId = strrr.GetBuffer();
			dlg.DoModal();
		}
		
	}
}

void CCninfoAnnouncementListView::OnTableAdvancedQuery()
{
	// TODO: �ڴ���������������

	CSimpleInputBox dlg;
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "��Ȩ����");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "��Ʊ�����ƻ����ݰ���");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "ͣ�ƹ���");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "ͣ�ƽ�չ����");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "���ƹ���");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "��ƱԤ��");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "�޶���");


	dlg.m_strCaption = _T("�����ѯ�ؼ��ַ�");
	if(IDOK==dlg.DoModal())
	{
		m_strLike = dlg.m_strInput.GetBuffer();
		m_nPageNo = 1;
		Startup();
	}
}

void CCninfoAnnouncementListView::OnPageUpdate()
{
	Startup();
}

void CCninfoAnnouncementListView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CCalcCninfoAnnouncementQuery * cse =  new CCalcCninfoAnnouncementQuery(m_hWnd, WM_USER_LOG_1);
	cse->m_request_like = m_strLike;
	cse->m_page_no = m_nPageNo;

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcCninfoAnnouncementQuery::Execute1);
	m_bCalculating = true;
}

void CCninfoAnnouncementListView::OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI)
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

void CCninfoAnnouncementListView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	TableAddToSelfSelect();
}

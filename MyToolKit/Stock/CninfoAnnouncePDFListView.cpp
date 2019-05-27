// HexunResearchPaperListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "CninfoAnnouncePDFListView.h"
#include "CalcCninfoAnnouncePDFQuery.h"

#include "SimpleInputBox.h"
#include "SelfSelectPlateDlg.h"

// CHexunResearchPaperListView

IMPLEMENT_DYNCREATE(CCninfoAnnouncePDFListView, CBaseRichEditFormView)

CCninfoAnnouncePDFListView::CCninfoAnnouncePDFListView()
{
	/*��ʾ��ҳ��*/
	m_bPagination = true;
	
}

CCninfoAnnouncePDFListView::~CCninfoAnnouncePDFListView()
{
}

BEGIN_MESSAGE_MAP(CCninfoAnnouncePDFListView, CBaseRichEditFormView)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
	ON_COMMAND(ID_TABLE_ADVANCED_QUERY, &CCninfoAnnouncePDFListView::OnTableAdvancedQuery)
	ON_UPDATE_COMMAND_UI(ID_TABLE_ADVANCED_QUERY, &CCninfoAnnouncePDFListView::OnUpdateTableAdvancedQuery)
	
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CCninfoAnnouncePDFListView::OnTableAddToSelfSelect)

	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID, OnGridEndSelChange)
END_MESSAGE_MAP()


// CHexunResearchPaperListView ��ͼ

void CCninfoAnnouncePDFListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CHexunResearchPaperListView ���

#ifdef _DEBUG
void CCninfoAnnouncePDFListView::AssertValid() const
{
	CBaseRichEditFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCninfoAnnouncePDFListView::Dump(CDumpContext& dc) const
{
	CBaseRichEditFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHexunResearchPaperListView ��Ϣ�������


void CCninfoAnnouncePDFListView::OnInitialUpdate()
{
	CBaseRichEditFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_strLike = "";
	Startup();
}

void CCninfoAnnouncePDFListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalcCninfoAnnouncePDFQuery * pStockInfoEx = (CCalcCninfoAnnouncePDFQuery *)cse;
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	m_bCalculating = false;
	m_nPageNo = pStockInfoEx->m_page_no;
	m_nMaxPage = pStockInfoEx->m_max_page;
	CString str1;
	str1.Format("�� %d ҳ  �� %d ҳ   �ؼ��� : %s", m_nPageNo, m_nMaxPage, m_strLike.c_str());
	//m_pStaticShowPage->SetWindowText(str1);
	GetDlgItem(IDC_STATIC)->SetWindowText(str1);

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
		//m_pStaticTip->SetWindowText(ss.str().c_str());
	}

	m_vec_catalogContent = pStockInfoEx->m_vec_catalogContent;


	if(m_GridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_GridCtrl.SetRowCount(pStockInfoEx->m_vec_code.size()+1);
			m_GridCtrl.SetColumnCount(7);
			m_GridCtrl.SetFixedRowCount(1);
			m_GridCtrl.SetFixedColumnCount(3);
			m_GridCtrl.SetHeaderSort(TRUE);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		for (int row = 0; row < m_GridCtrl.GetRowCount(); row++)
		{
			for (int col = 0; col < m_GridCtrl.GetColumnCount(); col++)
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
					else if(col==5)	val = "�������";
					else if(col==6) val = "Ŀ¼";
					
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
						if (!m_GridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}
				

					if(col==3 )
					{
						if (!m_GridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridCellDateTime)))
							return;
					}
					
					if(col==4 )
					{
						if (!m_GridCtrl.SetCellType(row, col, RUNTIME_CLASS(CGridURLCell)))
							return;
					}

					string val ;
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2) val = pStockInfoEx->m_vec_abbreviation[row-1];
					else if(col==3)	val =  pStockInfoEx->m_vec_report_date[row-1];

					else if(col==4)	val =  "http://www.cninfo.com.cn/"  + pStockInfoEx->m_vec_url[row-1];

					else if(col==5)	val =  pStockInfoEx->m_vec_title[row-1];
					else if(col==6)	val =  pStockInfoEx->m_vec_catalogName[row-1];

					Item.strText.Format(_T("%s"), val.c_str());

				}
				m_GridCtrl.SetItem(&Item);
			}
			int k = 1;
		}

		m_GridCtrl.AutoSize();
		m_GridCtrl.SetColumnWidth(2, 80);
		m_GridCtrl.SetColumnWidth(4, 60);
		m_GridCtrl.SetColumnWidth(5, 200);
		m_GridCtrl.SetColumnWidth(6, 400);
	}
}



void CCninfoAnnouncePDFListView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
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
		CString str = m_GridCtrl.GetItemText(pItem->iRow, 1);
		m_MessageCtrl.FocusStockOnLeftPane(str.GetBuffer());
	}
}

void CCninfoAnnouncePDFListView::OnTableAdvancedQuery()
{
	// TODO: �ڴ���������������

	CSimpleInputBox dlg;

	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "�������");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "��˾����Ȩ");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "����۸�");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "��������");
	

	dlg.m_strCaption = _T("�����ѯ�ؼ��ַ�");
	if(IDOK==dlg.DoModal())
	{
		m_strLike = dlg.m_strInput.GetBuffer();
		m_nPageNo = 1;
		Startup();
	}
}

void CCninfoAnnouncePDFListView::OnPageUpdate()
{
	Startup();
}

void CCninfoAnnouncePDFListView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CCalcCninfoAnnouncePDFQuery * cse =  new CCalcCninfoAnnouncePDFQuery(m_hWnd, WM_USER_LOG_1);
	cse->m_request_like = m_strLike;
	cse->m_page_no = m_nPageNo;

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcCninfoAnnouncePDFQuery::Execute1);
	m_bCalculating = true;
}

void CCninfoAnnouncePDFListView::OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI)
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

void CCninfoAnnouncePDFListView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	//TableAddToSelfSelect();
}


// GVN_SELCHANGING
void CCninfoAnnouncePDFListView::OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	/*Trace(_T("Start Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, m_Grid.GetSelectedCount());*/
}

// GVN_SELCHANGED
void CCninfoAnnouncePDFListView::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	/*Trace(_T("End Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, m_Grid.GetSelectedCount());*/

	if(pItem->iRow >0 && pItem->iRow <= m_vec_catalogContent.size())
	{
		
		m_RichEdit.SetWindowText(m_vec_catalogContent[pItem->iRow - 1].c_str());
		m_RichEdit.HideSelection(false, true);	//	ѡ������� ������ʾ

		vector<string>	vecTarget;
		vecTarget.insert(vecTarget.end(), "ҵ������Ŀ��");
		vecTarget.insert(vecTarget.end(), "�����¹�˾");
		vecTarget.insert(vecTarget.end(), "���ᵼ�¹�˾");
		vecTarget.insert(vecTarget.end(), "���ᵼ�±���˾");
		vecTarget.insert(vecTarget.end(), "δ���¹�˾");
		vecTarget.insert(vecTarget.end(), "���ᵼ�·�����");
		vecTarget.insert(vecTarget.end(), "��Ϊ��˾");
		vecTarget.insert(vecTarget.end(), "ҵ������Ҫ��");
		vecTarget.insert(vecTarget.end(), "ҵ�����˵�ָ��");
		vecTarget.insert(vecTarget.end(), "����ҵ������");

		for(int i=0; i<vecTarget.size(); i++)
		{

			FINDTEXTEX ft;
			ft.chrg.cpMin = 0;
			ft.chrg.cpMax = m_RichEdit.GetWindowTextLength();
			ft.lpstrText = vecTarget[i].c_str();

			long lPos = m_RichEdit.FindText(FR_DOWN , &ft);
			if(lPos!=-1)
			{
				m_RichEdit.SetSel(lPos, lPos + strlen(ft.lpstrText));
			}
		}
		
	}
}
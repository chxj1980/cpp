// HexunResearchPaperListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "BollListView.h"
#include "CalcBollQuery.h"

#include "SimpleInputBox.h"
#include "SelfSelectPlateDlg.h"

#include "PDFStructureDlg.h"

#include "DyncItemEditDlg.h"

// CHexunResearchPaperListView

IMPLEMENT_DYNCREATE(CBollListView, CBaseGridCtlView)

CBollListView::CBollListView()
{
	/*��ʾ��ҳ��*/
	m_bPagination = true;
	
}

CBollListView::~CBollListView()
{
}

BEGIN_MESSAGE_MAP(CBollListView, CBaseGridCtlView)
	ON_COMMAND(ID_TABLE_ADVANCED_QUERY, &CBollListView::OnTableAdvancedQuery)
	ON_UPDATE_COMMAND_UI(ID_TABLE_ADVANCED_QUERY, &CBollListView::OnUpdateTableAdvancedQuery)
	
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CBollListView::OnTableAddToSelfSelect)
END_MESSAGE_MAP()


// CCninfoGetLandListView ��ͼ

void CBollListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CCninfoGetLandListView ���

#ifdef _DEBUG
void CBollListView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CBollListView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCninfoGetLandListView ��Ϣ�������



void CBollListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_strLike = "";
	Startup();
}



void CBollListView::ProcessXmlWParam(string msgType,string code,string model,\
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


void CBollListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalcBollQuery * pStockInfoEx = (CCalcBollQuery *)cse;
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
			m_pGridCtrl->SetColumnCount(7);
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
					else if(col==2) val = "��Ʊ���";
					else if(col==3) val = "����";

					else if(col==4)	val = "����ͼ��";
					else if(col==5) val = "�����ǵ�";
					else if(col==6)	val = "��ǰͼ��";
					
					Item.strText.Format(_T("%s"), val.c_str());
				} 
				else 
				{

					if(col==0)
						Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
					else
						Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;

					if( col==0 || col == 5)
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
					else if(col==3)	val = pStockInfoEx->m_vec_report_date[row-1];

					else if(col==4)	val =  pStockInfoEx->m_vec_basic_desc[row-1];
					else if(col==5)	val =  Double2String(pStockInfoEx->m_vec_percent[row-1]);
					else if(col==6) val =  pStockInfoEx->m_vec_extra_desc[row-1];

					Item.strText.Format(_T("%s"), val.c_str());
				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->EnableTitleTips(TRUE);		//	�ر�ÿ����Ԫ����ı������� ������ʾ
		m_pGridCtrl->AutoSize();

	}
}



void CBollListView::OnTableAdvancedQuery()
{
	// TODO: �ڴ���������������

	CSimpleInputBox dlg;
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "�˳�");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "����");


	dlg.m_strCaption = _T("�����ѯ�ؼ��ַ�");
	if(IDOK==dlg.DoModal())
	{
		m_strLike = dlg.m_strInput.GetBuffer();
		m_nPageNo = 1;
		Startup();
	}
}

void CBollListView::OnPageUpdate()
{
	Startup();
}

void CBollListView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CCalcBollQuery * cse =  new CCalcBollQuery(m_hWnd, WM_USER_LOG_1);
	cse->m_request_like = m_strLike;
	cse->m_page_no = m_nPageNo;

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcBollQuery::Execute1);
	m_bCalculating = true;
}

void CBollListView::OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI)
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

void CBollListView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	TableAddToSelfSelect();
}


void CBollListView::PostGridDblClick(int nRow)
{
	// ���� ���޸� ���� ɾ���� �Ի���

}
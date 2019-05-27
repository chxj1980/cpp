// HexunResearchPaperListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "CninfoGetLandListView.h"
#include "CalcCninfoGetLandQuery.h"

#include "SimpleInputBox.h"
#include "SelfSelectPlateDlg.h"

#include "PDFStructureDlg.h"

#include "DyncItemEditDlg.h"

// CHexunResearchPaperListView

IMPLEMENT_DYNCREATE(CCninfoGetLandListView, CBaseGridCtlView)

CCninfoGetLandListView::CCninfoGetLandListView()
{
	/*��ʾ��ҳ��*/
	m_bPagination = true;
	
}

CCninfoGetLandListView::~CCninfoGetLandListView()
{
}

BEGIN_MESSAGE_MAP(CCninfoGetLandListView, CBaseGridCtlView)
	ON_COMMAND(ID_TABLE_ADVANCED_QUERY, &CCninfoGetLandListView::OnTableAdvancedQuery)
	ON_UPDATE_COMMAND_UI(ID_TABLE_ADVANCED_QUERY, &CCninfoGetLandListView::OnUpdateTableAdvancedQuery)
	
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CCninfoGetLandListView::OnTableAddToSelfSelect)
END_MESSAGE_MAP()


// CCninfoGetLandListView ��ͼ

void CCninfoGetLandListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CCninfoGetLandListView ���

#ifdef _DEBUG
void CCninfoGetLandListView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CCninfoGetLandListView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCninfoGetLandListView ��Ϣ�������



void CCninfoGetLandListView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_strLike = "";
	Startup();
}



void CCninfoGetLandListView::ProcessXmlWParam(string msgType,string code,string model,\
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

double money_unit_convert(string deal_money)
{
	//	����� ��Ԫ����λ
	double factor = 1.0;
	string::size_type npos = deal_money.find("��Ԫ");
	if(npos!=string::npos)
		factor =  10000.0;
	else
	{
		npos = deal_money.find("��Ԫ");
		if(npos!=string::npos)
			factor = 10000.0 * 10000.0;
	}

	if(npos!=string::npos)
		deal_money = deal_money.substr(0, npos);

	return  String2Double(deal_money) * factor;
}

double area_unit_convert(string land_area)
{
	//	����� ��ƽ���ס���λ
	double factor = 1.0;
	string::size_type npos = land_area.find("��ƽ����");
	if(npos!=string::npos)
		factor =  10000.0;
	else
	{
		npos = land_area.find("ƽ����");
		if(npos!=string::npos)
			factor = 1.0;
		else
		{
			npos = land_area.find("��ƽ��");
			if(npos!=string::npos)
				factor = 10000.0;
			else
			{
				npos = land_area.find("ƽ��");
				if(npos!=string::npos)
					factor = 1.0;
				else
				{
					npos = land_area.find("����");
					if(npos!=string::npos)
						factor = 10000.0;
					else
					{
						npos = land_area.find("Ķ");
						if(npos!=string::npos)
							factor = 666.67;
					}
				}
			}

		}

	}

	if(npos!=string::npos)
		land_area = land_area.substr(0, npos);

	return  String2Double(land_area) * factor;
}

void CCninfoGetLandListView::RedrawGridCtrl(CCalculateTask * cse)
{
	CCalcCninfoGetLandQuery * pStockInfoEx = (CCalcCninfoGetLandQuery *)cse;
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

		// ����ͬһ������ļ�¼��ʾ��ͬ�� ����ɫ
		int		bgColor = 0;
		string	last_report_date = "";

		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
		{
			if(row >=1)
			{
				if(pStockInfoEx->m_vec_announcementId[row-1]!=last_report_date)
				{
					last_report_date = pStockInfoEx->m_vec_announcementId[row-1];
					if(bgColor==0) bgColor = 1;
					else bgColor = 0;
				}
			}
			
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

					else if(col==3) val = "�����ʶ";
					else if(col==4) val = "��Ŀ���";
					else if(col==5) val = "����";
					else if(col==6) val = "URL";
					else if(col==7)	val = "����";
					else if(col==8) val = "���׽��";
					else if(col==9) val = "�ݻ���";
					else if(col==10)	val = "�������";
					else if(col==11)	val = "������;";

					else if(col==12)	val = "�������";
					else if(col==13)	val = "¥�浥��";
					
					Item.strText.Format(_T("%s"), val.c_str());
				} 
				else 
				{
					// ����ͬһ������ļ�¼��ʾ��ͬ�� ����ɫ
					if(col >=3)
					{
						Item.mask = GVIF_TEXT|GVIF_FORMAT | GVIF_BKCLR;
						if(bgColor==0)
							Item.crBkClr = RGB(196, 236, 196);
						else 
							Item.crBkClr = RGB(255, 255, 255);
					}
					

					if(col==0)
						Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
					else
						Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;

					if( col==0 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}
				

					if(col==5 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellDateTime)))
							return;
					}
					
					if(col==6 )
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridURLCell)))
							return;
					}

					if(col==7)
					{
						Item.nFormat = DT_RIGHT|DT_WORDBREAK|DT_EDITCONTROL|DT_NOPREFIX|DT_END_ELLIPSIS;
					}

					string val ;
					
					if(col==0)		val = Int2String(row);
					else if(col==1)	val = Int2String(pStockInfoEx->m_vec_code[row-1], "%06d");
					else if(col==2) val = pStockInfoEx->m_vec_abbreviation[row-1];
					
					else if(col==3)	val = pStockInfoEx->m_vec_announcementId[row-1];
					else if(col==4)	val = pStockInfoEx->m_vec_land_num[row-1];
					else if(col==5)	val = pStockInfoEx->m_vec_report_date[row-1];

					else if(col==6)	val =  /*"http://www.cninfo.com.cn/" +*/ pStockInfoEx->m_vec_url[row-1];

					else if(col==7)	val =  pStockInfoEx->m_vec_land_name[row-1];
					else if(col==8)	val =  pStockInfoEx->m_vec_deal_money[row-1];
					else if(col==9) val =  pStockInfoEx->m_vec_rate_of_capacity[row-1];
					else if(col==10)	
					{
						val = pStockInfoEx->m_vec_land_area[row-1];
					}
					else if(col==11)	
					{
						val = pStockInfoEx->m_vec_land_purpose[row-1];
					}

					else if(col==12)	
					{
						val = pStockInfoEx->m_vec_area_of_structure[row-1];
						if(val.empty())
						{
							//	ͨ�� �ݻ��������� �������
							vector<string> vecWords;
							friso_split_chinese(pStockInfoEx->m_vec_rate_of_capacity[row-1], vecWords);
							double rate_of_capacity = 1.0;
							for(int j =0; j<vecWords.size(); j++)
							{
								double tmp = String2Double(vecWords[j]);
								if(tmp> rate_of_capacity)
									rate_of_capacity = tmp;
							}

							string land_area = pStockInfoEx->m_vec_land_area[row-1];
							
							double area_of_structure = area_unit_convert(land_area) * rate_of_capacity ;

							if(area_of_structure >0)
							{
								val = Double2String(area_of_structure);
								val += "ƽ����(��)";
							}
						}

						str_area_of_structure = val;
					}
					else if(col==13)	
					{
						double area_of_structure = area_unit_convert(str_area_of_structure);
						double deal_money = money_unit_convert(pStockInfoEx->m_vec_deal_money[row-1]);
						if(area_of_structure >0)
						{
							double price = deal_money/area_of_structure;
							val = Double2String(price);
						}
					}

					Item.strText.Format(_T("%s"), val.c_str());

				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->EnableTitleTips(TRUE);		//	�ر�ÿ����Ԫ����ı������� ������ʾ
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetColumnWidth(2, 80);
		m_pGridCtrl->SetColumnWidth(6, 40);
		m_pGridCtrl->SetColumnWidth(7, 1);

		m_pGridCtrl->SetColumnWidth(8, 120);
		m_pGridCtrl->SetColumnWidth(9, 120);
		m_pGridCtrl->SetColumnWidth(10, 140);
		m_pGridCtrl->SetColumnWidth(11, 120);

		m_pGridCtrl->SetColumnWidth(12, 100);
		m_pGridCtrl->SetColumnWidth(13, 100);

		//	ȷ���еĸ߶�
		/*for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++)
		{
			CString strrr = m_pGridCtrl->GetItemText(row,5);
			CGridCellBase* pCell = m_pGridCtrl->GetCell(row,5);
			if(pCell)
			{
				CSize si = pCell->GetTextExtentByWidth(strrr, 400);
				m_pGridCtrl->SetRowHeight(row, si.cy);
			}

		}*/
	}
}



void CCninfoGetLandListView::OnTableAdvancedQuery()
{
	// TODO: �ڴ���������������

	CSimpleInputBox dlg;
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "������");
	dlg.m_ComboString.insert(dlg.m_ComboString.end(), "Ӫҵ����");


	dlg.m_strCaption = _T("�����ѯ�ؼ��ַ�");
	if(IDOK==dlg.DoModal())
	{
		m_strLike = dlg.m_strInput.GetBuffer();
		m_nPageNo = 1;
		Startup();
	}
}

void CCninfoGetLandListView::OnPageUpdate()
{
	Startup();
}

void CCninfoGetLandListView::Startup()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	CCalcCninfoGetLandQuery * cse =  new CCalcCninfoGetLandQuery(m_hWnd, WM_USER_LOG_1);
	cse->m_request_like = m_strLike;
	cse->m_page_no = m_nPageNo;

	m_MessageCtrl.SetStockRangeForCalculateTask(pDoc, cse);

	cse->ScheduleTask(&CCalcCninfoGetLandQuery::Execute1);
	m_bCalculating = true;
}

void CCninfoGetLandListView::OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI)
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

void CCninfoGetLandListView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	TableAddToSelfSelect();
}


void CCninfoGetLandListView::PostGridDblClick(int nRow)
{
	// ���� ���޸� ���� ɾ���� �Ի���

	CDyncItemEditDlg infd;
	vector<item_info>  vec;
	
	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("��Ʊ����"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP | ES_READONLY, false};
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 1);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("��Ʊ���"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP | ES_READONLY, false};
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 2);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("����ID"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP | ES_READONLY, true};
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 3);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("��Ŀ���"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP | ES_READONLY, true};
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 4);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("��������"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP | ES_READONLY, false};
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 5);
	}

	{	// 5
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("���׽��"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP };
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 8);
	}

	{	// 6
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("�ݻ���"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP, false };
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 9);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("�������"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP, false };
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 10);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("������;"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP , false};
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 11);
	}

	{
		item_info it =  { CDlgTemplateBuilder::EDIT, _T("�������"), 
			WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL|WS_TABSTOP, false };
		vec.insert(vec.end(), it);
		infd.m_strItem[vec.size()-1]  = m_pGridCtrl->GetItemText(nRow, 12);
	}

	infd.Init("�޸ġ�ɾ������������Ŀ","����������Ϣ:" , vec);
	if(infd.DoModal()==IDOK)
	{
		try{
			stringstream ss;
			string strOper = infd.m_strComb.GetBuffer();
			if(strOper.find("Delete")!=string::npos)
			{
				ss << "delete from cninfo_get_land " 
					<< " where announcementId=\'" << infd.m_strItem[2] << "\' " 
					<< " and land_num=" << infd.m_strItem[3] ;

				string sqlStr = ss.str();

				session sql(g_MysqlPool);
				sql << sqlStr; 
			}
			else if(strOper.find("Update")!=string::npos)
			{
				ss << "update cninfo_get_land set rate_of_capacity = \'" << infd.m_strItem[6] << "\', "
					<< " land_area = \'" << infd.m_strItem[7] << "\', "
					<< " deal_money = \'" << infd.m_strItem[5] << "\', "
					<< " area_of_structure = \'" << infd.m_strItem[9] << "\', "
					<< " land_purpose = \'" << infd.m_strItem[8] << "\' "
					<< " where announcementId=\'" << infd.m_strItem[2] << "\' " 
					<< " and land_num=" << infd.m_strItem[3] ;

				string sqlStr = ss.str();

				session sql(g_MysqlPool);
				sql << sqlStr; 
			}

			else if(strOper.find("Insert")!=string::npos)
			{
				ss << "insert into cninfo_get_land() set rate_of_capacity = \'" << infd.m_strItem[6] << "\', "
					<< " land_area = \'" << infd.m_strItem[7] << "\', "
					<< " deal_money = \'" << infd.m_strItem[5] << "\', "
					<< " land_purpose = \'" << infd.m_strItem[8] << "\' "
					<< " where announcementId=\'" << infd.m_strItem[2] << "\' " 
					<< " and land_num=" << infd.m_strItem[3] ;

				string sqlStr = ss.str();

				session sql(g_MysqlPool);
				sql << sqlStr; 
			}

			//	�޸���ɺ����¶���
			m_nPageNo = 1;
			Startup();
		}
		catch(...)
		{
			AfxMessageBox("����ʧ�ܣ���������");
		}
		
	}
}
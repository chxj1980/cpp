// BaseGridCtlView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "BaseGridCtlView.h"
#include "SelfSelectPlateDlg.h"


#include "BasicExcel.hpp"
using namespace YExcel;


// CBaseGridCtlView

IMPLEMENT_DYNCREATE(CBaseGridCtlView, CBaseMessageView)

CBaseGridCtlView::CBaseGridCtlView()
{
	m_pGridCtrl = NULL;
	m_pButtonFirst = NULL;
	m_pButtonLast = NULL;
	m_pButtonPageDown = NULL;
	m_pButtonPageUp =  NULL;
	m_pStaticShowPage = NULL;
	m_pStaticTip = NULL;

	m_pButtonSaveAsExcel = NULL;

	m_bPagination = false;
}

CBaseGridCtlView::~CBaseGridCtlView()
{
	if (m_pGridCtrl)
		delete m_pGridCtrl;

	if (m_pButtonFirst)
		delete m_pButtonFirst;
	if (m_pButtonLast)
		delete m_pButtonLast;
	if (m_pButtonPageDown)
		delete m_pButtonPageDown;
	if (m_pButtonPageUp)
		delete m_pButtonPageUp;
	if(m_pStaticShowPage)
		delete m_pStaticShowPage;

	if(m_pStaticTip)
		delete m_pStaticTip;

	if(m_pButtonSaveAsExcel)
		delete m_pButtonSaveAsExcel;

	m_nPageNo = 1;
	m_nMaxPage = 1;


}

BEGIN_MESSAGE_MAP(CBaseGridCtlView, CBaseMessageView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_PAGE_FIRST, OnBtnFirst)
	ON_BN_CLICKED(IDC_BTN_PAGEUP, OnBtnPageup)
	ON_BN_CLICKED(IDC_BTN_PAGEDOWN, OnBtnPagedown)
	ON_BN_CLICKED(IDC_BTN_PAGE_LAST, OnBtnLast)
	ON_BN_CLICKED(IDC_BTN_SAVE_AS_EXCEL, OnBtnSaveAsExcel)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
	ON_COMMAND(ID_TABLE_ADD_TO_SELF_SELECT, &CBaseGridCtlView::OnTableAddToSelfSelect)
END_MESSAGE_MAP()


// CBaseGridCtlView ��ͼ

void CBaseGridCtlView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CBaseGridCtlView ���

#ifdef _DEBUG
void CBaseGridCtlView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseGridCtlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseGridCtlView ��Ϣ�������

int CALLBACK CBaseGridCtlView::pfnCellCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	UNUSED_ALWAYS(lParamSort);

	CGridCellBase* pCell1 = (CGridCellBase*) lParam1;
	CGridCellBase* pCell2 = (CGridCellBase*) lParam2;
	if (!pCell1 || !pCell2) return 0;

	if(pCell1->IsKindOf(RUNTIME_CLASS(CGridCellNumeric)))
	{
		double nValue1 = String2Double(pCell1->GetText());
		double nValue2 = String2Double(pCell2->GetText());

		if (nValue1 < nValue2)
			return -1;
		else if (nValue1 == nValue2)
			return 0;
		else
			return 1;
	}
	else
		return CGridCtrl::pfnCellTextCompare(lParam1, lParam2, lParamSort);
}


void CBaseGridCtlView::OnInitialUpdate()
{
	CBaseMessageView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	//	��ʼ�����
	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		rect.top += m_bPagination ? 30 : 0;
		m_pGridCtrl->Create(rect, this, IDC_GRID);

		// fill it up with stuff
		m_pGridCtrl->SetEditable(FALSE);
		m_pGridCtrl->EnableDragAndDrop(FALSE);
		m_pGridCtrl->SetCompareFunction(CBaseGridCtlView::pfnCellCompare);
	
		m_pGridCtrl->EnableSelection(TRUE);
		m_pGridCtrl->SetFixedRowSelection(TRUE);

		try {
			m_pGridCtrl->SetRowCount(20);
			m_pGridCtrl->SetColumnCount(7);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}
	}

	if(m_bPagination)
	{
		LOGFONT   logfont;   
		lstrcpy((LPSTR)logfont.lfFaceName,(LPSTR)"����_GB2312");   
		logfont.lfWeight=FW_THIN;   
		logfont.lfWidth=6;   
		logfont.lfHeight=12;   
		logfont.lfEscapement=0;   
		logfont.lfUnderline=FALSE;   
		logfont.lfItalic=FALSE;   
		logfont.lfStrikeOut=FALSE;   
		logfont.lfCharSet=GB2312_CHARSET;       //���ϲ�������һ����������
		m_editFont.CreateFontIndirect(&logfont); 
	}


	int left = 0;
	short	shBtnColor = 30;
	if(m_pStaticShowPage==NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 2; 
		m_pStaticShowPage = new CStatic();
		m_pStaticShowPage->Create("�� 1 ҳ  �� 1 ҳ", WS_CHILD | SS_CENTERIMAGE | ES_CENTER ,
			CRect(left,2, left + 140,28),this,IDC_STATIC_PAGE_SHOW);

		m_pStaticShowPage->SetFont(&m_editFont); // ����������
		m_pStaticShowPage->ShowWindow(SW_SHOWNORMAL);
	}

	
	left +=141;
	if(m_pButtonFirst == NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 4; 
		m_pButtonFirst = new CButtonST();
		m_pButtonFirst->Create("��һҳ", WS_CHILD | BS_DEFPUSHBUTTON,CRect(left,2, left + 70,28),this,IDC_BTN_PAGE_FIRST);
		m_pButtonFirst->OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
		m_pButtonFirst->SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
		m_pButtonFirst->SetTooltipText(_T("��һҳ"));

		m_pButtonFirst->SetFont(&m_editFont); // ����������
		m_pButtonFirst->ShowWindow(SW_SHOWNORMAL);
	}

	left +=71;
	if(m_pButtonPageUp == NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 5; 
		m_pButtonPageUp = new CButtonST();
		m_pButtonPageUp->Create("��һҳ", WS_CHILD | BS_DEFPUSHBUTTON,CRect(left,2, left + 70,28),this,IDC_BTN_PAGEUP);
		m_pButtonPageUp->OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
		m_pButtonPageUp->SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

		m_pButtonPageUp->SetFont(&m_editFont); // ����������
		m_pButtonPageUp->ShowWindow(SW_SHOWNORMAL);
	}

	left +=71;
	if(m_pButtonPageDown == NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 6; 
		m_pButtonPageDown = new CButtonST();
		m_pButtonPageDown->Create("��һҳ", WS_CHILD | BS_DEFPUSHBUTTON,CRect(left,2, left + 70,28),this,IDC_BTN_PAGEDOWN);
		m_pButtonPageDown->OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
		m_pButtonPageDown->SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

		m_pButtonPageDown->SetFont(&m_editFont); // ����������
		m_pButtonPageDown->ShowWindow(SW_SHOWNORMAL);
	}

	left +=71;
	if(m_pButtonLast == NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 7; 
		m_pButtonLast = new CButtonST();
		m_pButtonLast->Create("���һҳ", WS_CHILD | BS_DEFPUSHBUTTON,CRect(left,2, left + 70,28),this,IDC_BTN_PAGE_LAST);
		m_pButtonLast->OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
		m_pButtonLast->SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

		m_pButtonLast->SetFont(&m_editFont); // ����������
		m_pButtonLast->ShowWindow(SW_SHOWNORMAL);
	}

	left +=71;
	if(m_pButtonSaveAsExcel == NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 7; 
		m_pButtonSaveAsExcel = new CButtonST();
		m_pButtonSaveAsExcel->Create("���Ϊ", WS_CHILD | BS_DEFPUSHBUTTON,CRect(left,2, left + 70,28),this,IDC_BTN_SAVE_AS_EXCEL);
		m_pButtonSaveAsExcel->OffsetColor(CButtonST::BTNST_COLOR_BK_IN, shBtnColor);
		m_pButtonSaveAsExcel->SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

		m_pButtonSaveAsExcel->SetFont(&m_editFont); // ����������
		m_pButtonSaveAsExcel->ShowWindow(SW_SHOWNORMAL);
	}

	left +=71;
	if(m_pStaticTip==NULL && m_bPagination)
	{
		CRect rect;
		GetClientRect(rect);
		//int left = (rect.right - rect.left)/8 * 2; 
		m_pStaticTip = new CStatic();
		m_pStaticTip->Create("", WS_CHILD | SS_CENTERIMAGE | ES_CENTER, CRect(left,2, rect.right, 28),this,IDC_STATIC_PAGE_TIP);
		
		m_pStaticTip->SetFont(&m_editFont); // ����������
		m_pStaticTip->ShowWindow(SW_SHOWNORMAL);
	}
	
	
}

void CBaseGridCtlView::OnSize(UINT nType, int cx, int cy)
{
	CBaseMessageView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		rect.top += m_bPagination ? 30 : 0;
		m_pGridCtrl->MoveWindow(rect);
	}

	if (m_bPagination && m_pStaticTip->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		int left = 141 + 5 * 71; 
		rect.left = left;
		rect.right = rect.right;
		rect.top = 2;
		rect.bottom = 28;
		m_pStaticTip->MoveWindow(rect);
	}

	/*if (m_bPagination && m_pStaticShowPage->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		int left = (rect.right - rect.left)/8 * 2; 
		rect.left = left;
		rect.right = left + 140;
		rect.top = 2;
		rect.bottom = 28;
		m_pStaticShowPage->MoveWindow(rect);
	}

	if ( m_bPagination && m_pButtonFirst->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		int left = (rect.right - rect.left)/8 * 4; 
		rect.left = left;
		rect.right = left + 70;
		rect.top = 2;
		rect.bottom = 28;
		m_pButtonFirst->MoveWindow(rect);
	}

	if (m_bPagination && m_pButtonPageUp->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		int left = (rect.right - rect.left)/8 * 5; 
		rect.left = left;
		rect.right = left + 70;
		rect.top = 2;
		rect.bottom = 28;
		m_pButtonPageUp->MoveWindow(rect);
	}

	if (m_bPagination && m_pButtonPageDown->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		int left = (rect.right - rect.left)/8 * 6; 
		rect.left = left;
		rect.right = left + 70;
		rect.top = 2;
		rect.bottom = 28;
		m_pButtonPageDown->MoveWindow(rect);
	}

	if (m_bPagination && m_pButtonLast->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		int left = (rect.right - rect.left)/8 * 7; 
		rect.left = left;
		rect.right = left + 70;
		rect.top = 2;
		rect.bottom = 28;
		m_pButtonLast->MoveWindow(rect);
	}*/

}


void CBaseGridCtlView::SetGridCell(int row, int col, bool isHeader,  string text)
{
	GV_ITEM Item;
	if(isHeader)
	{
		Item.crBkClr = RGB(150,150,150);    // or - m_Grid.SetItemBkColour(row, col, clr);
		Item.crFgClr = RGB(255,255,255);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));	
		Item.nFormat = DT_RIGHT|DT_WORDBREAK;
	}
	else
	{
		Item.crBkClr = RGB(255,255,255);
		Item.crFgClr = RGB(0,0,0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));	
		Item.nFormat = DT_LEFT|DT_WORDBREAK;
	}
	Item.mask = GVIF_TEXT|GVIF_FORMAT |(GVIF_BKCLR|GVIF_FGCLR)/*| GVIS_READONLY*/;
	Item.row = row;
	Item.col = col;
	Item.strText.Format(text.c_str());
	m_pGridCtrl->SetItem(&Item);
}


void CBaseGridCtlView::SetGridCell(int row, int col, bool isHeader,  string text, COLORREF crFgClr)
{
	GV_ITEM Item;
	if(isHeader)
	{
		Item.crBkClr = RGB(150,150,150);    // or - m_Grid.SetItemBkColour(row, col, clr);
		Item.crFgClr = crFgClr;    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));	
		Item.nFormat = DT_RIGHT|DT_WORDBREAK;
	}
	else
	{
		Item.crBkClr = RGB(255,255,255);
		Item.crFgClr =crFgClr;    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));	
		Item.nFormat = DT_LEFT|DT_WORDBREAK;
	}
	Item.mask = GVIF_TEXT|GVIF_FORMAT |(GVIF_BKCLR|GVIF_FGCLR)/*| GVIS_READONLY*/;
	Item.row = row;
	Item.col = col;
	Item.strText.Format(text.c_str());
	m_pGridCtrl->SetItem(&Item);
}



void CBaseGridCtlView::OnBtnFirst() // ��һҳ
{
	if (m_nPageNo == 1)
	{
		AfxMessageBox(_T("���ǵ�һҳ"));
	}
	else
	{
		m_nPageNo = 1;
		OnPageUpdate();
	}
}

void CBaseGridCtlView::OnBtnPageup() // ��һҳ
{
	if(m_nPageNo==1)
	{
		AfxMessageBox(_T("���ǵ�һҳ"));
	}
	if(m_nPageNo>1)
	{
		m_nPageNo--;
		OnPageUpdate();
	}
}

void CBaseGridCtlView::OnBtnPagedown() // ��һҳ
{
	m_nPageNo++;	
	if (m_nPageNo > m_nMaxPage)
	{			
		m_nPageNo--;
		AfxMessageBox("�������һҳ");
		return;
	}
	OnPageUpdate();
}

void CBaseGridCtlView::OnBtnLast() // ���һҳ
{
	if (m_nPageNo == m_nMaxPage)
	{
		AfxMessageBox("�������һҳ");
		return;
	}
	else
	{
		m_nPageNo = m_nMaxPage;
		OnPageUpdate();
	}	
}


void CBaseGridCtlView::TableAddToSelfSelect()
{
	int selected = m_pGridCtrl->GetSelectedCount();
	if(selected>0)
	{
		map<int ,string >  codes;
		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
		{
			for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
			{
				if(m_pGridCtrl->IsCellSelected(row, col))
				{
					CString str = m_pGridCtrl->GetItemText(row, 1);
					int code = atoi(str.GetBuffer());
					str = m_pGridCtrl->GetItemText(row, 2);
					codes[code] = str.GetBuffer();
				}
			}
		}

		CSelfSelectPlateDlg dlg;
		dlg.DoModal();

		if(dlg.m_nPlateCode> 0)
		{
			JMutexAutoLock lock(((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_mutex);
			map<int ,string >::iterator it = codes.begin();
			for(; it!=codes.end(); it++)
			{
				int code = it->first;

				CStockPlateData treeNode;
				treeNode.code = Int2String(code, "%06d");
				treeNode.name = it->second;
				treeNode.company_number = 1;
				treeNode.is_stock = 1;

				CStockPlateData treeNodeParent;
				treeNodeParent.code =  Int2String(dlg.m_nPlateCode, "%08d");;
				treeNodeParent.is_stock = 0;


				CStockPlateTree * pPlates = ((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_pTree;
				CStockPlateTree * pNode  = pPlates->SearchSpecialNode(treeNodeParent);
				if(pNode)
				{
					pNode->insert((const CStockPlateData&)treeNode);
				}

			}
			((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->ImportToDatabase();

			StockInfo_Reqeust req;
			req.code = -ID_READ_STOCKPLATE_SELF_SELECT;
			req.hwnd = NULL;
			((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_front(req);
		}
	}
}



void CBaseGridCtlView::ProcessXmlWParam(string msgType,string code,string model,\
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
		//m_bCalculating = false;
	}
	//RedrawGridCtrl();
}


void CBaseGridCtlView::RedrawGridCtrl(CCalculateTask * cse)
{

	CCalculateTask * pCse = (CCalculateTask *)cse;

	//	���������ݽ��л��ܣ��Ա�����ʾ
	map<string , map<string, double>>	map_Cell;
	map<string, string>		map_Row;
	vector<string>		vec_Col;
	vector<string>		vec_Col_Unit;
	vector<string>		vec_Row;
	vector<string>		vec_Row_Code;
	for(int i=0; i< pCse->zb_name.size(); i++)
	{
		map_Cell[pCse->zb_name[i]][pCse->sj_code[i]] = pCse->data[i];
		//map_Col[pCse->sj_code[i]] = pCse->sj_code[i];
		map_Row[pCse->zb_code[i]] = pCse->zb_name[i];

		vector<string>::iterator it = vec_Col.begin();
		for(; it!=vec_Col.end(); it++)
		{
			if(*it==pCse->sj_code[i])
				break;
		}
		if(it==vec_Col.end())
		{
			vec_Col.insert(vec_Col.end(), pCse->sj_code[i]);

			if(pCse->unit[i].empty())
				vec_Col_Unit.insert(vec_Col_Unit.end(), pCse->sj_code[i]);
			else
				vec_Col_Unit.insert(vec_Col_Unit.end(), pCse->sj_code[i] + "(" + pCse->unit[i] + ")");
		}
	}

	/* ���������ơ� ��������, �Ա���ʾʱ�����ʱ��������� */
	std::stable_sort(vec_Col.begin(), vec_Col.end()); 
	std::stable_sort(vec_Col_Unit.begin(), vec_Col_Unit.end()); 
	std::reverse(vec_Col.begin(), vec_Col.end());
	std::reverse(vec_Col_Unit.begin(), vec_Col_Unit.end()); 
	
	map<string,string>::iterator it = map_Row.begin();
	for(; it!=map_Row.end(); it++)
	{
		vec_Row.push_back(it->second);
		vec_Row_Code.push_back(it->first);
	}

	if(m_pGridCtrl && map_Cell.size()>0)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		try {
			m_pGridCtrl->SetRowCount(vec_Row.size() + 1);
			m_pGridCtrl->SetColumnCount(vec_Col.size() + 3);		//	������������ �� ���/����/����
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
				string val;

				if (row < 1) {
					Item.nFormat = DT_LEFT|DT_WORDBREAK;

					if(col==0)		
						val = pCse->title_name;
					else if(col==1)
					{
						val = "����";
					}
					else if(col==2)
					{
						val = "����";
					}
					else
					{
						val = vec_Col_Unit[col-3];
						/*if(vec_Col_Unit[col-3].empty()==false)
							val += "(" + vec_Col_Unit[col-3] + ")";*/
					}
					Item.strText.Format(_T("%s"), val.c_str());
				} 
				else 
				{
					if(col <= 2 )
						Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
					else
						Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;

					if( col> 2  || col==0)
					{
						if (!m_pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
							return;
					}

					if(col==0)
					{
						val = Int2String(row);
					}
					else if(col==1)
					{
						val = vec_Row_Code[row-1];
					}
					else if(col==2)
					{
						val = vec_Row[row-1];
					}
					else
					{
						string zb_name = vec_Row[row-1];
						string sj_code = vec_Col[col-3];

						if(map_Cell[zb_name].count(sj_code) >0)
						{
							double db = map_Cell[zb_name][sj_code];
							if(_isnan(db)) val = "";
							else
							{
								val = Double2String(db);
								Item.mask    |= (GVIF_FGCLR);
								if(db >0)
								{
									//Item.crFgClr = RGB(255, 64, 64);
									Item.crFgClr = RGB(0, 0, 0);
								}
								else
									Item.crFgClr = RGB(0, 163, 0);
							}
						}
						else 
							val = "";
					}

					Item.strText.Format(_T("%s"), val.c_str());

				}
				m_pGridCtrl->SetItem(&Item);
			}
			int k = 1;
		}

		m_pGridCtrl->AutoSize();
		//m_pGridCtrl->SetColumnWidth(2, 80);
	}
}


void CBaseGridCtlView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(str);

	//////////////////////////////////////////////////////////////////////////
	//	��ѡ�еĵ�Ԫ������ ������ ������

	CString source = m_pGridCtrl->GetItemText(pItem->iRow, pItem->iColumn);
	if( OpenClipboard() )
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}


	//////////////////////////////////////////////////////////////////////////
	//	��Ʊͣ������ʾ��ǰѡ��� ��Ʊ

	if(pItem->iRow>0)
	{
		CString str = m_pGridCtrl->GetItemText(pItem->iRow, 1);
		m_MessageCtrl.FocusStockOnLeftPane(str.GetBuffer());
	}

	//////////////////////////////////////////////////////////////////////////
	//	���λ��ÿ�е�ǰ���У�����

	if(pItem->iRow>0 && pItem->iColumn <3)
		PostGridDblClick(pItem->iRow);
}


void CBaseGridCtlView::OnTableAddToSelfSelect()
{
	// TODO: �ڴ���������������
	TableAddToSelfSelect();
}



// MBCS ת����Unicode����
int MbcsToUnicode(const char * lpMbcsStr, wchar_t * lpUnicodeStr,int nUnicodeStrLen)
{
	int nRetLen = 0;
	if(!lpMbcsStr) //���MBCS �ַ���ΪNULL������˳�
	{
		return 0;
	}

	//��ȡת����Unicode���������Ҫ���ַ��ռ䳤��
	nRetLen = ::MultiByteToWideChar(CP_UTF8,0,(char *)lpMbcsStr, -1, NULL, NULL); 
	if(nRetLen >= nUnicodeStrLen)
		return 0;

	nRetLen = ::MultiByteToWideChar(CP_UTF8,0,(char *)lpMbcsStr, -1, lpUnicodeStr,nRetLen); //ת����Unicode����
	return nRetLen;
}


void CBaseGridCtlView::OnBtnSaveAsExcel() // ������ݱ���Ϊ excel 
{
	CFileDialog cfd(FALSE, _T("xls"));
	if(cfd.DoModal()==IDOK)
	{
		CString filepath = cfd.GetPathName();

		BasicExcel e;
		e.New(1);		//	with 1 sheet

		e.RenameWorksheet("Sheet1", "Test1");
		BasicExcelWorksheet* sheet = e.GetWorksheet("Test1");
		BasicExcelCell* cell;
		if (sheet)
		{

			for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
			{
				for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
				{
					CString strItem = m_pGridCtrl->GetItemText(row, col);
					//sheet->Cell(row, col)->SetString(strItem.GetBuffer());
					string strUtf8 =  Gbk2Utf8( strItem.GetBuffer());

					WCHAR tmp[512];
					if(MbcsToUnicode(strUtf8.c_str(), tmp, 512)>0)
						sheet->Cell(row, col)->SetWString(tmp);
				}
			}
	
		}

		e.SaveAs(filepath.GetBuffer());
		AfxMessageBox("Excel �ļ�����ɹ�");
	}
}
// EntrepreneurView.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "TechAnalysisEvent.h"

#include "Stock.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "StockDoc.h"
#include "StockView.h"

#include "CsvDocument.h"
#include "CsvView.h"

#include "DatabaseDoc.h"
#include "DatabaseView.h"

#include "AutoDownloadDoc.h"
#include "AutoDownloadView.h"

#include "StockInfoView.h"

#include "IndividualShareDoc.h"
#include "IndividualShareView.h"
#include "IndividualSummaryView.h"
#include "IndividualCostView.h"
#include "IndividualSzsePeView.h"
#include "IndividualVolumeView.h"
#include "IndividualYahooPeView.h"
#include "IndividualNetProfitsView.h"
#include "IndividualCurrentAssetView.h"
#include "IndividualNonCurrentAssetView.h"
#include "IndividualCapitalStructView.h"
#include "IndividualCsvFileView.h"
#include "IndividualCapitalFlowView.h"
#include "IndiCashFlowSummaryView.h"
#include "IndiZombieAnalysisView.h"
#include "IndiFundHoldValueView.h"
#include "IndiMacdView.h"
#include "IndiMainIncomeGrowthView.h"
#include "IndiMcstView.h"
#include "Indi10jqkaBonusView.h"
#include "IndiHexunResearchPapaerView.h"
#include "IndiMarketIndexAnalysisView.h"
#include "IndiCsindexView.h"
#include "IndiGrossProfitRateView.h"
#include "IndiCninfoAnnouncementRoadView.h"
#include "IndiPeAndValueDailyView.h"
#include "IndiIncomestatementForecastView.h"
#include "IndiDmiView.h"
#include "IndiTechnicalAnalysisRoadView.h"
#include "SimulatedAccountListView.h"

#include "BaseChartCtlView.h"

#include "AutoDownloadView.h"

#include "SelfSelectPlateDlg.h"
#include "FindStockByCode.h"
#include "FindStockByPinyin.h"

class CStockInfoViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CStockInfoViewMenuButton)

public:
	CStockInfoViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CStockInfoViewMenuButton, CMFCToolBarMenuButton, 1)

// CStockInfoView

IMPLEMENT_DYNAMIC(CStockInfoView, CDockablePane)

string CStockInfoView::m_strSelectedCode = "";
string CStockInfoView::m_strSelectedItemText = "";

CStockInfoView::CStockInfoView()
{
}

CStockInfoView::~CStockInfoView()
{
}


BEGIN_MESSAGE_MAP(CStockInfoView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_COMMAND(ID_STOCKINFO_OPEN, &CStockInfoView::OnStockinfoOpen)
	ON_COMMAND(ID_INDIVIDUAL_SUMMARY, &CStockInfoView::OnIndividualSummary)
	ON_COMMAND(ID_OVERALL_COST, &CStockInfoView::OnOverallCost)
	ON_COMMAND(ID_INDIVIDUAL_SZSE_PE, &CStockInfoView::OnIndividualSzsePe)
	ON_COMMAND(ID_INDIVIDUAL_VOLUME, &CStockInfoView::OnIndividualVolume)
	ON_COMMAND(ID_INDIVIDUAL_NET_PROFITS, &CStockInfoView::OnIndividualNetProfits)
	ON_COMMAND(ID_BALANCE_CURRENT_ASSET, &CStockInfoView::OnBalanceCurrentAsset)
	ON_COMMAND(ID_BALANCE_NON_CURRENT_ASSET, &CStockInfoView::OnBalanceNonCurrentAsset)
	ON_COMMAND(ID_DOWNLOAD_INDIVIDUAL, &CStockInfoView::OnDownloadIndividual)
	ON_COMMAND(ID_INDIVIDUAL_CAPITAL_STRUCT, &CStockInfoView::OnIndividualCapitalStruct)
	ON_COMMAND(ID_INDIVIDUAL_CSV_INCOME, &CStockInfoView::OnIndividualCsvIncome)
	ON_COMMAND(ID_INDIVIDUAL_CSV_TRADING, &CStockInfoView::OnIndividualCsvTrading)
	ON_COMMAND(ID_INDIVIDUAL_CSV_BALANCE, &CStockInfoView::OnIndividualCsvBalance)
	ON_COMMAND(ID_INDIVIDUAL_CAPITAL_FLOW, &CStockInfoView::OnIndividualCapitalFlow)
	ON_COMMAND(ID_INDIVIDUAL_CAPITALFLOW_VALUE, &CStockInfoView::OnIndividualCapitalflowValue)
	ON_COMMAND(ID_CASHFLOW_SUMMARY, &CStockInfoView::OnCashflowSummary)
	ON_COMMAND(ID_INDIVIDUAL_CSV_CASHFLOWS, &CStockInfoView::OnIndividualCsvCashflows)
	ON_COMMAND(ID_INDIVIDUAL_ADD_TO_SELF_SELECT, &CStockInfoView::OnIndividualAddToSelfSelect)
	ON_COMMAND(ID_INDIVIDUAL_CSV_FUND_HOLD, &CStockInfoView::OnIndividualCsvFundHold)
	ON_COMMAND(ID_FIND_STOCK_BY_CODE, &CStockInfoView::OnFindStockByCode)
	ON_COMMAND(ID_INDIVIDUAL_ZOMBIE_ANALYSIS, &CStockInfoView::OnIndividualZombieAnalysis)
	ON_COMMAND(ID_INDIVIDUAL_FUND_HOLD_VALUE_ANALYSIS, &CStockInfoView::OnIndividualFundHoldValueAnalysis)
	ON_COMMAND(ID_INDIVIDUAL_MACD, &CStockInfoView::OnIndividualMacd)
	ON_COMMAND(ID_INDI_MAIN_INCOME_GROWTH, &CStockInfoView::OnIndiMainIncomeGrowth)
	ON_COMMAND(ID_INDIVIDUAL_MCST, &CStockInfoView::OnIndividualMcst)
	ON_COMMAND(ID_INDI_10JQKA_BONUS, &CStockInfoView::OnIndi10jqkaBonus)
	ON_COMMAND(ID_INDI_HEXUN_RESEARCH_PAPER_EPS, &CStockInfoView::OnIndiHexunResearchPaperEps)
	ON_COMMAND(ID_INDI_MARKET_VALUE_INDEX_ANALYSIS, &CStockInfoView::OnIndiMarketValueIndexAnalysis)
	ON_COMMAND(ID_INDI_CSINDEX_ANALYSIS, &CStockInfoView::OnIndiCsindexAnalysis)
	ON_COMMAND(ID_INDI_GROSS_PROFIT_RATE, &CStockInfoView::OnIndiGrossProfitRate)
	ON_COMMAND(ID_INDI_ADD_INSURANCE_ROADMAP, &CStockInfoView::OnIndiAddInsuranceRoadmap)
	ON_COMMAND(ID_INDI_IMPORTANT_EVENT_ROADMAP, &CStockInfoView::OnIndiImportantEventRoadmap)
	ON_COMMAND(ID_INDI_QUARTER_REPORT_ROADMAP, &CStockInfoView::OnIndiQuarterReportRoadmap)
	ON_COMMAND(ID_INDI_TRADE_ROADMAP, &CStockInfoView::OnIndiTradeRoadmap)
	ON_COMMAND(ID_INDI_SPECIAL_DISPOSAL_ROADMAP, &CStockInfoView::OnIndiSpecialDisposalRoadmap)
	ON_COMMAND(ID_INDI_SUPPLEMENT_CORRECTION_ROADMAP, &CStockInfoView::OnIndiSupplementCorrectionRoadmap)
	ON_COMMAND(ID_INDI_PE_AND_VALUE_DAILY, &CStockInfoView::OnIndiPeAndValueDaily)
	ON_COMMAND(ID_INDI_ORIGINAL_ISSUE_ROADMAP, &CStockInfoView::OnIndiOriginalIssueRoadmap)
	ON_COMMAND(ID_INDI_INCOMESTATEMENT_FORECAST, &CStockInfoView::OnIndiIncomestatementForecast)
	ON_COMMAND(ID_INDI_DMI, &CStockInfoView::OnIndiDmi)
	ON_COMMAND(ID_INDI_TECH_ANALYSIS_ROADMAP, &CStockInfoView::OnIndiTechAnalysisRoadmap)
	ON_COMMAND(ID_INDI_SIMULATED_ACCOUNT_QUERY, &CStockInfoView::OnIndiSimulatedAccountQuery)
END_MESSAGE_MAP()



// CStockInfoView ��Ϣ�������


BOOL CStockInfoView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: �ڴ����ר�ô����/����û���

	m_strSelectedCode = "";
	m_strSelectedItemText = "";
	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )>0)
		{
			string::size_type pos1 = firstMatch[0].find(")");
			m_strSelectedCode = firstMatch[0].substr(1, pos1-1);
			m_strSelectedItemText = text.GetBuffer();
		}
	}

	/*�Ȼ�ȡ��ǰ�򿪵� MDI ��ͼ������������������Ϣ*/
	if(((CMainFrame*)(AfxGetApp()->m_pMainWnd))->MDIGetActive())
	{
		CView* pCurView=((CMainFrame*)(AfxGetApp()->m_pMainWnd))->MDIGetActive()->GetActiveView();//<--This Line
		if(pCurView && m_strSelectedCode.empty()==FALSE )
		{
			/*if(pCurView->GetDocument()->IsKindOf(RUNTIME_CLASS(CIndividualShareDoc)))
				((CIndividualShareDoc *)pCurView->GetDocument())->m_nCode = m_strSelectedCode;*/

			if(pCurView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo)==TRUE)
				return TRUE;

		}

	}
	
	return CDockablePane::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


int CStockInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS \
		| WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_SHOWSELALWAYS  /*��ʧȥ����ʱҲ��ʾ��ǰѡ�еĽ��*/;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����ҵ����ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ����ͼ��:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_STOCKINFO);
	m_wndToolBar.LoadToolBar(IDR_STOCKINFO, 0, 0, TRUE /* ������*/);

	// OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_STOCKINFO);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CStockInfoViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CStockInfoViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CStockInfoViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		// pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}
	return 0;
}

void CStockInfoView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	//FillClassView();
	AdjustLayout();
}

void CStockInfoView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������

	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_STOCKINFO);

	CMenu* pSumMenu = menu.GetSubMenu(0);
	
	//	ɾ��ĳЩ��ʱ�����ŵĲ˵�
	/*pSumMenu->RemoveMenu(ID_INDI_PE_AND_VALUE_DAILY, MF_BYCOMMAND); */

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}


bool CStockInfoView::FocusOn(int nCode)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);
	
	bool bFind = false;
	char tmp[10];
	sprintf_s(tmp,10,"(%06d)", nCode);
	string strCode = tmp;
	HTREEITEM hTreeItem =  pWndTree->GetRootItem();
	HTREEITEM hSelectItem = hTreeItem;
	HTREEITEM hFirstItem = hTreeItem;
	int nSelectedPos = pWndTree->GetCount();
	
	//hTreeItem = pWndTree->GetChildItem(hTreeItem);
	for(int i=0; i<nSelectedPos; i++)
	{
		string str = pWndTree->GetItemText(hTreeItem).GetBuffer();
		if(str.find(strCode)!=string::npos)
		{
			if(i+3<nSelectedPos)
				nSelectedPos = i+3;
			hSelectItem = hTreeItem;
			bFind = true;
		}
		hTreeItem = pWndTree->GetNextSiblingItem(hTreeItem);
	}
	
	if(bFind)
	{
		//	���ѡ���Ա����ʵ����ת��ʾ
		if(hFirstItem!=NULL)
			pWndTree->SelectItem(hFirstItem);
		if(hTreeItem!=NULL)
			pWndTree->SelectItem(hTreeItem);
		if(hSelectItem!=NULL)
			pWndTree->SelectItem(hSelectItem);
	}
	return bFind;
	//pWndTree->SetScrollTime();
}

BOOL CStockInfoView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(pMsg->message==WM_CHAR )
	{
		TCHAR ch = pMsg->wParam;

		if(/*(ch >='A' && ch <='Z') ||*/ (ch >='a' && ch <='z'))
		{
			CFindStockByPinyin dlg;
			dlg.m_strPinyin = ch; 
			dlg.DoModal();

			if(dlg.m_strPinyin.GetLength()>6)
			{
				CString strCode = dlg.m_strPinyin.Mid(5).Left(6);
				CBaseMessageControl::FocusStockOnLeftPane(strCode.GetBuffer());
			}
			return TRUE;
		}

	}

	return CDockablePane::PreTranslateMessage(pMsg);
}

void CStockInfoView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDockablePane::OnPaint()

	CRect rectTree;
	m_wndClassView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


void CStockInfoView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}



void CStockInfoView::FillClassView()
{
	/*HTREEITEM hRoot = m_wndClassView.InsertItem(_T("FakeApp ��"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);*/

	m_wndClassView.DeleteAllItems();

	for(int i=0; i< m_pStockInfo->m_nRowNum; i++)
	{
		CString str;
		str.Format("%s(%06d)",m_pStockInfo->m_vec_abbreviation[i].c_str(),m_pStockInfo->m_vec_a_code[i] );
		HTREEITEM hClass = m_wndClassView.InsertItem(str, 1, 1/*, hRoot*/);
	}
	
	//m_wndClassView.Expand(hRoot, TVE_EXPAND);

}

void CStockInfoView::OnStockinfoOpen()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());
		
		CIndividualYahooPeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);	
		CString title;
		title.Format("ÿ�չ�Ʊ����̬PE-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualSummary()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualSummaryView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);	
		pNewDoc->SetTitle(text);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}



void CStockInfoView::OnOverallCost()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCostView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("Ӫҵ�ܳɱ�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualSzsePe()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualSzsePeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("���й�ƱPE-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualVolume()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualVolumeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("ÿ�ճɽ���-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualNetProfits()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualNetProfitsView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("�����󹹳�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnBalanceCurrentAsset()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCurrentAssetView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("�����ʲ�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnBalanceNonCurrentAsset()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualNonCurrentAssetView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("�������ʲ�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnDownloadIndividual()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAutoDownloadView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("������������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCapitalStruct()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCapitalStructView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format("�ɱ��ṹ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCsvIncome()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCsvFileView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_INCOME); //strCarMunber);
		CString title;
		title.Format(" �����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCsvTrading()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		AfxMessageBox("��ͣ�ù���");		
		return ;

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCsvFileView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_TRADING); //strCarMunber);
		CString title;
		title.Format(" ���ڽ�������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCsvBalance()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCsvFileView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_BALANCE); //strCarMunber);
		CString title;
		title.Format(" �ʲ���ծ��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCapitalFlow()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCapitalFlowView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format(" �ʽ�����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCapitalflowValue()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCapitalFlowView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format(" �ʽ���������ͨ��ֵ-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnCashflowSummary()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiCashFlowSummaryView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr); //strCarMunber);
		CString title;
		title.Format(" �ֽ�����С��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualCsvCashflows()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCsvFileView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_CASHFLOWS); //strCarMunber);
		CString title;
		title.Format(" �ֽ�������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualAddToSelfSelect()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string  stockName = text.GetBuffer();
		string::size_type pos = stockName.find(firstMatch[0]);
		stockName = stockName.substr(0,pos);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CSelfSelectPlateDlg dlg;
		dlg.DoModal();

		if(dlg.m_nPlateCode> 0)
		{
			CStockPlateData treeNode;
			treeNode.code = Int2String(code, "%06d");
			treeNode.name = stockName;
			treeNode.company_number = 1;
			treeNode.is_stock = 1;

			CStockPlateData treeNodeParent;
			treeNodeParent.code = Int2String(dlg.m_nPlateCode, "%08d");
			treeNodeParent.is_stock = 0;

			JMutexAutoLock lock(((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_mutex);
			CStockPlateTree * pPlates = ((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_pTree;
			CStockPlateTree * pNode = pPlates->SearchSpecialNode(treeNodeParent);
			if(pNode)
			{
				pNode->insert(treeNode);
			}
			((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->ImportToDatabase();

			StockInfo_Reqeust req;
			req.code = -ID_READ_STOCKPLATE_SELF_SELECT;
			req.hwnd = NULL;
			((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_front(req);
		}
	}
}

void CStockInfoView::OnIndividualCsvFundHold()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndividualCsvFileView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_FUND_HOLD); //strCarMunber);
		CString title;
		title.Format(" �������CSV-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnFindStockByCode()
{
	// TODO: �ڴ���������������
	CFindStockByCode dlg;
	dlg.SetStockInfo(m_pStockInfo);

	CStockApp * pApp = (CStockApp *)AfxGetApp();
	if(m_pStockInfo==&pApp->m_CEntrepreneurship)
		dlg.m_strCaption = "����ҵ�塿��Ʊ�����ѯ";
	if(m_pStockInfo==&pApp->m_CSmallMidEnterprise)
		dlg.m_strCaption = "����С�塿��Ʊ�����ѯ";
	if(m_pStockInfo==&pApp->m_CShenzhenAshares)
		dlg.m_strCaption = "������A�ɡ���Ʊ�����ѯ";
	if(m_pStockInfo==&pApp->m_CShanghaiStock)
		dlg.m_strCaption = "���Ϻ�A�ɡ���Ʊ�����ѯ";

	dlg.DoModal();

	if(dlg.m_strCode.GetLength()>6)
	{
		int code = atoi(dlg.m_strCode.Left(6));
		if(((CMainFrame *)AfxGetMainWnd())->m_wndEntrepreneurView.FocusOn(code)==true)
			((CMainFrame *)AfxGetMainWnd())->m_wndEntrepreneurView.ShowPane(TRUE, FALSE, TRUE);

		else if(((CMainFrame *)AfxGetMainWnd())->m_wndSmallMidEnterpriseView.FocusOn(code)==true)
			((CMainFrame *)AfxGetMainWnd())->m_wndSmallMidEnterpriseView.ShowPane(TRUE, FALSE, TRUE);

		else if(((CMainFrame *)AfxGetMainWnd())->m_wndShenzhenAsharesView.FocusOn(code)==true)
			((CMainFrame *)AfxGetMainWnd())->m_wndShenzhenAsharesView.ShowPane(TRUE, FALSE, TRUE);

		else if(((CMainFrame *)AfxGetMainWnd())->m_wndShanghaiStockView.FocusOn(code)==true)
			((CMainFrame *)AfxGetMainWnd())->m_wndShanghaiStockView.ShowPane(TRUE, FALSE, TRUE);
	}
}

void CStockInfoView::OnIndividualZombieAnalysis()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiZombieAnalysisView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_FUND_HOLD); //strCarMunber);
		CString title;
		title.Format("��ʬָ�����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualFundHoldValueAnalysis()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiFundHoldValueView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, ID_INDIVIDUAL_CSV_FUND_HOLD); //strCarMunber);
		CString title;
		title.Format(" ���������ֵ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualMacd()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiMacdView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("MACD����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiMainIncomeGrowth()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiMainIncomeGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("��Ӫ����ɳ�����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndividualMcst()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiMcstView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("MCST �ɱ��۷���-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndi10jqkaBonus()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndi10jqkaBonusView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("����ֺ��͹�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiHexunResearchPaperEps()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiHexunResearchPapaerView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("��Ѷ�б�EPS�ֲ�ͼ-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiMarketValueIndexAnalysis()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiMarketIndexAnalysisView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("ָ������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiCsindexAnalysis()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	
	if (m_strSelectedCode.empty() == FALSE)
	{
		
		CIndiCsindexView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		CString title;
		title.Format("��֤��˾���ݷ���-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}



void CStockInfoView::OnIndiGrossProfitRate()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;


	if (m_strSelectedCode.empty() == FALSE)
	{

		CIndiGrossProfitRateView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		CString title;
		title.Format("����ë���ʷ���-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiAddInsuranceRoadmap()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "����";
		CString title;
		title.Format("��������·��ͼ-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiImportantEventRoadmap()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "�����ش�����";
		CString title;
		title.Format("�����ش�����-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiQuarterReportRoadmap()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "�ȱ���";
		CString title;
		title.Format("���ȣ��룩��ȱ���-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiTradeRoadmap()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "����";
		CString title;
		title.Format("����-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiSpecialDisposalRoadmap()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "�ر�������";
		CString title;
		title.Format("�ر�������-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiSupplementCorrectionRoadmap()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "���估����";
		CString title;
		title.Format("���估����-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiPeAndValueDaily()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiPeAndValueDailyView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		CString title;
		title.Format("ÿ������ֵ����̬PE-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiOriginalIssueRoadmap()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiCninfoAnnouncementRoadView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "�״ι������м�����";
		CString title;
		title.Format("�״ι������м�����-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiIncomestatementForecast()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	if (m_strSelectedCode.empty() == FALSE)
	{
		CIndiIncomestatementForecastView  /*CIndiCninfoAnnouncementRoadView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(m_strSelectedCode, -1); //strCarMunber);
		pNewDoc->m_strInput = "��������ҵ��Ԥ��";
		CString title;
		title.Format("��������ҵ��Ԥ��-%s", m_strSelectedItemText.c_str());
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiDmi()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiDmiView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("DMI ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiTechAnalysisRoadmap()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CIndiTechnicalAnalysisRoadView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1); //strCarMunber);
		CString title;
		title.Format("���������¼�ͼ-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockInfoView::OnIndiSimulatedAccountQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CSimulatedAccountListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, -1, 1); //strCarMunber);
		CString title;
		title.Format("ģ�⽻��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

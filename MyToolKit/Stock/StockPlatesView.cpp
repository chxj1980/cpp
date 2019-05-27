// StockPlatesView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "StockPlatesView.h"

#include "IndividualShareDoc.h"
//#include "PlateStockListView.h"
#include "AllStockListView.h"
#include "HexunResearchPaperListView.h"
#include "ZombieStockListView.h"
#include "PeStockListView.h"
#include "AllMainIncomeYearGrowthStockListView.h"
#include "AllMainProfitYearGrowthStockListView.h"
#include "AllThisYearBonusListView.h"
#include "AllMcstStockListView.h"
#include "AllAddIssuanceListView.h"
#include "AllCsiDynamicPeStockListView.h"
#include "CninfoAnnouncementListView.h"
#include "CninfoAnnouncePDFListView.h"
#include "CninfoGetLandListView.h"
#include "CninfoIncentivePlanListView.h"
#include "CninfoShareHoldingListView.h"

#include "PlateGrossProfitListView.h"
#include "PlateLiquidityRatioView.h"
#include "PlateNetProfitsRatioView.h"
#include "PlateTotalAssetsTurnoverRatioView.h"
#include "PlateDebtToAssetsRatioView.h"
#include "PlateInventoryTurnoverRatioView.h"
#include "PlateDebtToCapitalRatioView.h"
#include "PlateCurrentAssetsTurnoverRatioView.h"
#include "PlateFixedAssetsTurnoverRatioView.h"
#include "PlateFundHoldView.h"
#include "PlateTotalAssetsGrowthView.h"
#include "PlateNetFixedAssestsGrowthView.h"
#include "PlateMainIncomeGrowthView.h"
#include "PlateCorrectedMarketValueView.h"
#include "PlateCsindexDynamicPeView.h"
#include "PlateDealDetailDailyView.h"
#include "PlateTurnoverRateView.h"
#include "PlateChangeRateSummaryView.h"
#include "PlateGrossProfitRateGrowthView.h"
#include "PlateShanghaiIndexView.h"


#include "BaseMatlabView.h"

#include "InputTextDlg.h"
#include "DealDetailDateDlg.h"
#include "FindStockByPinyin.h"
#include "PlateSelectDlg.h"

//////////////////////////////////////////////////////////////////////////
// CStockPlatesView

IMPLEMENT_DYNAMIC(CStockPlatesView, CDockablePane)

CStockPlatesView::CStockPlatesView()
{
	
}

CStockPlatesView::~CStockPlatesView()
{
}


BEGIN_MESSAGE_MAP(CStockPlatesView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_COMMAND(ID_PLATE_STOCK_LIST, &CStockPlatesView::OnPlateStockList)
	ON_COMMAND(ID_PLATE_GROSS_PROFIT, &CStockPlatesView::OnPlateGrossProfit)
	ON_COMMAND(ID_PLATE_ADD_STOCK, &CStockPlatesView::OnPlateAddStock)
	ON_COMMAND(ID_PLATE_DEL_STOCK, &CStockPlatesView::OnPlateDelStock)
	ON_UPDATE_COMMAND_UI(ID_PLATE_ADD_STOCK, &CStockPlatesView::OnUpdatePlateAddStock)
	ON_UPDATE_COMMAND_UI(ID_PLATE_DEL_STOCK, &CStockPlatesView::OnUpdatePlateDelStock)
	ON_COMMAND(ID_PLATE_LIQUIDITY_RATIO, &CStockPlatesView::OnPlateLiquidityRatio)
	ON_COMMAND(ID_PLATE_NETPROFITS_RATIO, &CStockPlatesView::OnPlateNetprofitsRatio)
	ON_COMMAND(ID_TOTAL_ASSETS_TURNOVER_RATIO, &CStockPlatesView::OnTotalAssetsTurnoverRatio)
	ON_COMMAND(ID_FIXED_ASSETS_TURNOVER_RATIO, &CStockPlatesView::OnFixedAssetsTurnoverRatio)
	ON_COMMAND(ID_CURRENT_ASSETS_TURNOVER_RATIO, &CStockPlatesView::OnCurrentAssetsTurnoverRatio)
	ON_COMMAND(ID_INVENTORY_TURNOVER_RATIO, &CStockPlatesView::OnInventoryTurnoverRatio)
	ON_COMMAND(ID_DEBT_TO_ASSETS_RATIO, &CStockPlatesView::OnDebtToAssetsRatio)
	ON_COMMAND(ID_DEBT_TO_CAPITAL_RATIO, &CStockPlatesView::OnDebtToCapitalRatio)
	ON_COMMAND(ID_FUND_HOLD_RATIO, &CStockPlatesView::OnFundHoldRatio)
	ON_COMMAND(ID_TOTAL_ASSETS_GROWTH, &CStockPlatesView::OnTotalAssetsGrowth)
	ON_COMMAND(ID_NET_FIXED_ASSETS_GROWTH, &CStockPlatesView::OnNetFixedAssetsGrowth)
	ON_COMMAND(ID_MAIN_INCOME_GROWTH, &CStockPlatesView::OnMainIncomeGrowth)
	ON_COMMAND(ID_PLATE_MAIN_INCOME_YEAR_GROWTH, &CStockPlatesView::OnPlateMainIncomeYearGrowth)
	ON_COMMAND(ID_PLATE_RESEARCH_PAPER_QUERY, &CStockPlatesView::OnPlateResearchPaperQuery)
	ON_COMMAND(ID_PLATE_ZOMBIE_STOCK_LIST, &CStockPlatesView::OnPlateZombieStockList)
	ON_COMMAND(ID_PLATE_PE_STOCK_LIST, &CStockPlatesView::OnPlatePeStockList)
	ON_COMMAND(ID_PLATE_MAIN_PROFIT_YEAR_GROWTH, &CStockPlatesView::OnPlateMainProfitYearGrowth)
	ON_COMMAND(ID_PLATE_CLEAR_STOCK, &CStockPlatesView::OnPlateClearStock)
	ON_UPDATE_COMMAND_UI(ID_PLATE_CLEAR_STOCK, &CStockPlatesView::OnUpdatePlateClearStock)
	ON_COMMAND(ID_PLATE_BONUS_PLAN_QUERY, &CStockPlatesView::OnPlateBonusPlanQuery)
	ON_COMMAND(ID_PLATE_MCST_STOCK_LIST, &CStockPlatesView::OnPlateMcstStockList)
	ON_COMMAND(ID_PLATE_ADD_ISSUANCE_STOCK_LIST, &CStockPlatesView::OnPlateAddIssuanceStockList)
	ON_COMMAND(ID_PLATE_CORRECTED_MARKET_VALUE, &CStockPlatesView::OnPlateCorrectedMarketValue)
	ON_COMMAND(ID_PLATE_INDUSTRY_DYNAMIC_PE, &CStockPlatesView::OnPlateIndustryDynamicPe)
	ON_COMMAND(ID_PLATE_INDUSTRY_STATIC_PE, &CStockPlatesView::OnPlateIndustryStaticPe)
	ON_COMMAND(ID_PLATE_INDUSTRY_PB, &CStockPlatesView::OnPlateIndustryPb)
	ON_COMMAND(ID_PLATE_INDUSTRY_COMPANY_NUMBER, &CStockPlatesView::OnPlateIndustryCompanyNumber)
	ON_COMMAND(ID_PLATE_DIVIDEND_YIELD_RATIO, &CStockPlatesView::OnPlateDividendYieldRatio)
	ON_COMMAND(ID_PLATE_CSI_DYNAMIC_PE_STOCK_LIST, &CStockPlatesView::OnPlateCsiDynamicPeStockList)
	ON_COMMAND(ID_PLATE_DEAL_DETAIL_DAILY, &CStockPlatesView::OnPlateDealDetailDaily)
	ON_COMMAND(ID_PLATE_TURNOVER_RATE_DAILY, &CStockPlatesView::OnPlateTurnoverRateDaily)
	ON_COMMAND(ID_FOCUS_NEXT_ON_PLATE, &CStockPlatesView::OnFocusNextOnPlate)
	ON_COMMAND(ID_PLATE_CHANGE_RATE_SUMMARY, &CStockPlatesView::OnPlateChangeRateSummary)
	ON_COMMAND(ID_PLATE_GROSS_PROFIT_RATE_QUARTER_GROWTH, &CStockPlatesView::OnPlateGrossProfitRateQuarterGrowth)
	ON_COMMAND(ID_PLATE_GROSS_PROFIT_RATE_CHANGE_FOR_LAST, &CStockPlatesView::OnPlateGrossProfitRateChangeForLast)
	ON_COMMAND(ID_PLATE_GROSS_PROFIT_CHANGE_FOR_AVERAGE, &CStockPlatesView::OnPlateGrossProfitChangeForAverage)
	ON_COMMAND(ID_PLATE_GROSS_PROFIT_RATE_4_QUARTER_GROWTH, &CStockPlatesView::OnPlateGrossProfitRate4QuarterGrowth)
	ON_COMMAND(ID_PLATE_CNINFO_ANNOUNCEMENT_QUERY, &CStockPlatesView::OnPlateCninfoAnnouncementQuery)
	ON_COMMAND(ID_PLATE_CSI_STATIC_PE_STOCK_LIST, &CStockPlatesView::OnPlateCsiStaticPeStockList)
	ON_COMMAND(ID_PLATE_CNINFO_PDF_QUERY, &CStockPlatesView::OnPlateCninfoPdfQuery)
	ON_COMMAND(ID_PLATE_SHANGHAI_INDEX, &CStockPlatesView::OnPlateShanghaiIndex)
	ON_COMMAND(ID_PLATE_CNINFO_GET_LAND_QUERY, &CStockPlatesView::OnPlateCninfoGetLandQuery)
	ON_COMMAND(ID_PLATE_CNINFO_INCENTIVE_PLAN_QUERY, &CStockPlatesView::OnPlateCninfoIncentivePlanQuery)
	ON_COMMAND(ID_PLATE_CNINFO_SHARE_HOLDING_QUERY, &CStockPlatesView::OnPlateCninfoShareHoldingQuery)
END_MESSAGE_MAP()



// CStockPlatesView ��Ϣ�������


HTREEITEM CStockPlatesView::TreeTravesal(HTREEITEM hStart, string strCode) 
{ 
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;

	string str = pWndTree->GetItemText(hStart).GetBuffer();
	if(str.find(strCode)!=string::npos)
	{
		return hStart;
	}

	HTREEITEM hChildItem = NULL; 
	if (pWndTree->ItemHasChildren(hStart)) 
	{ 
		hChildItem = pWndTree->GetChildItem(hStart); 
		while(hChildItem!=NULL) 
		{ 
			//�ݹ�������ӽڵ� 
			HTREEITEM hTempItem = TreeTravesal(hChildItem, strCode);
			if(hTempItem)
				return hTempItem;	
			hChildItem =pWndTree->GetNextItem(hChildItem, TVGN_NEXT);    
		}    
	} 
	return NULL; 
}


void CStockPlatesView::TreeTravesal(HTREEITEM hStart, string strCode, vector<HTREEITEM> & vecHtreeitem)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;

	string str = pWndTree->GetItemText(hStart).GetBuffer();
	if(str.find(strCode)!=string::npos)
	{
		vecHtreeitem.push_back(hStart);
	}

	HTREEITEM hChildItem = NULL; 
	if (pWndTree->ItemHasChildren(hStart)) 
	{ 
		hChildItem = pWndTree->GetChildItem(hStart); 
		while(hChildItem!=NULL) 
		{ 
			//�ݹ�������ӽڵ� 
			TreeTravesal(hChildItem, strCode, vecHtreeitem);
			
			hChildItem =pWndTree->GetNextItem(hChildItem, TVGN_NEXT);    
		}    
	} 
}


bool CStockPlatesView::FocusOn(int nCode, int is_stock)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	bool bFind = false;
	char tmp[12];
	if(is_stock)
		sprintf_s(tmp,12,"(%06d)", nCode);
	else
		sprintf_s(tmp,12,"(%08d)", nCode);

	string strCode = tmp;
	HTREEITEM hTreeItem =  pWndTree->GetRootItem();
	HTREEITEM hSelectItem = hTreeItem;
	HTREEITEM hFirstItem = hTreeItem;

	//hTreeItem = pWndTree->GetChildItem(hTreeItem);
	hSelectItem = TreeTravesal(hTreeItem, strCode);

	if(hSelectItem)
	{
		//	���ѡ���Ա����ʵ����ת��ʾ
		if(hFirstItem!=NULL)
			pWndTree->SelectItem(hFirstItem);
		if(hTreeItem!=NULL)
			pWndTree->SelectItem(hTreeItem);
		if(hSelectItem!=NULL)
			pWndTree->SelectItem(hSelectItem);
		return true;
	}
	return false;
	//pWndTree->SetScrollTime();
}


void CStockPlatesView::FindAllOnTree(int nCode, int is_stock)
{
	m_vecFound.clear();

	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	bool bFind = false;
	char tmp[128] = {0} ;
	if(is_stock)
		sprintf_s(tmp,128,"(%06d)", nCode);
	else
		sprintf_s(tmp,128,"(%08d)", nCode);

	string strCode = tmp;
	HTREEITEM hTreeItem =  pWndTree->GetRootItem();

	TreeTravesal(hTreeItem, strCode, m_vecFound);

	m_nNextFound = 0;
}


bool CStockPlatesView::FocusOnNext()
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if(m_nNextFound<0)
	{
		/* ���ҽ����δ���� */
		FindAllOnTree(m_nCodeFound, m_nIsStockFound);
	}

	HTREEITEM hTreeItem =  pWndTree->GetRootItem();
	HTREEITEM hSelectItem = hTreeItem;
	HTREEITEM hFirstItem = hTreeItem;

	if(m_nNextFound>=0 && m_vecFound.size()> m_nNextFound)
	{
		hSelectItem = m_vecFound[m_nNextFound];

		//	���ѡ���Ա����ʵ����ת��ʾ
		if(hFirstItem!=NULL)
			pWndTree->SelectItem(hFirstItem);
		if(hTreeItem!=NULL)
			pWndTree->SelectItem(hTreeItem);
		if(hSelectItem!=NULL)
			pWndTree->SelectItem(hSelectItem);

		m_nNextFound++;
		if(m_nNextFound>=m_vecFound.size())
			m_nNextFound = 0;
		return true;
	}
	return false;
}


void CStockPlatesView::FillClassView()
{
	m_wndClassView.DeleteAllItems();

	vector<CStockPlateData> vecStockPlateData;

	AcquireReadLock(&g_RWlock);
	CStockPlateTree * pPlates = NULL;
	if(m_nPlateType==ID_PLATE_TYPE_SOHU)
	{
		//pPlates = ((CStockApp *)AfxGetApp())->m_pCSouhuStockPlates;
		if(m_nPlateCode==1632)
			vecStockPlateData = ((CStockApp *)AfxGetApp())->m_vecStockPlateArea;
		if(m_nPlateCode==1630)
			vecStockPlateData = ((CStockApp *)AfxGetApp())->m_vecStockPlateConcept;
		if(m_nPlateCode==1631)
			vecStockPlateData = ((CStockApp *)AfxGetApp())->m_vecStockPlateIndustry;
	}
	if(m_nPlateType==ID_PLATE_TYPE_SELF_SELECT)
		pPlates = ((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_pTree;
	if(m_nPlateType==ID_PLATE_TYPE_CSINDEX)
		pPlates = ((CStockApp *)AfxGetApp())->m_pCsindexStockPlates;
	if(m_nPlateType==ID_PLATE_TYPE_CSINDEX_CSRC)
		pPlates = ((CStockApp *)AfxGetApp())->m_pCsindexCsrcStockPlates;
	if(m_nPlateType==ID_PLATE_TYPE_SHENZHEN_INDEXINFO)
		pPlates = ((CStockApp *)AfxGetApp())->m_ShenzhenIndexList.m_pTree;
	
	if(pPlates)
	{	
		//	��ĳ���ڵ�Ϊ������������������
		CStockPlateData treeNode;
		treeNode.code = Int2String(m_nPlateCode, "%08d");
		treeNode.is_stock = 0;

		CStockPlateTree * pNode = pPlates->SearchSpecialNode(treeNode);
		if(pNode==NULL)
			pNode = pPlates;
		if(pNode)
		{
			//	�ýڵ�Ϊ���ڵ�
			CStockPlateData spd = *pNode->get();
			spd.code = Int2String(m_nPlateCode, "%08d");
			spd.parent_code = "-1";
			spd.is_stock = 0;
			if(spd.name.empty())
				spd.name = "��Ŀ¼";
			vecStockPlateData.push_back(spd);

			CStockPlateTree::pre_order_iterator pre_order_it = pNode->pre_order_begin();
			while(pre_order_it!=pNode->pre_order_end())
			{
				CStockPlateData spd = *pre_order_it;
				if(pre_order_it.node()->parent()->is_root()==false)
				{
					spd.parent_code = pre_order_it.node()->parent()->get()->code;
				}
				else
				{
					spd.parent_code = Int2String(m_nPlateCode, "%08d");
				}
				vecStockPlateData.push_back(spd);
				pre_order_it++;
			}

		}
	}
	ReleaseReadLock(&g_RWlock);

	HTREEITEM hRoot;
	map<string, HTREEITEM> mapHTree;
	for(int i =0 ; i<vecStockPlateData.size(); i++)
	{
		CString str;
		if(vecStockPlateData[i].is_stock==1)
		{
			str.Format("%s-%d(%s)",vecStockPlateData[i].name.c_str(),\
				vecStockPlateData[i].company_number, vecStockPlateData[i].code.c_str());
		}
		else
		{
			str.Format("%s-%d(%s)",vecStockPlateData[i].name.c_str(),\
				vecStockPlateData[i].company_number, vecStockPlateData[i].code.c_str());
		}
		
		if(vecStockPlateData[i].parent_code== "-1")
		{
			HTREEITEM hClass = m_wndClassView.InsertItem(str, 1, 1);
			hRoot = hClass;
			
			CString key;
			if(vecStockPlateData[i].is_stock==1)
				key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
			else
				key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
			mapHTree.insert(make_pair(string(key.GetBuffer()), hClass));

			m_wndClassView.SetItemData(hClass, (DWORD_PTR)vecStockPlateData[i].is_stock);
		}
		else
		{
			CString key;
			key.Format("%s-%d", vecStockPlateData[i].parent_code.c_str(), 0);
			HTREEITEM hParent = mapHTree[string(key.GetBuffer())];
			HTREEITEM hClass = m_wndClassView.InsertItem(str, hParent, TVI_LAST);
			
			if(vecStockPlateData[i].is_stock==1)
				key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
			else
				key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
			mapHTree.insert(make_pair(string(key.GetBuffer()), hClass));

			m_wndClassView.SetItemData(hClass, (DWORD_PTR)vecStockPlateData[i].is_stock);
		}
		

		/*CStockPlateData treeNode;
		treeNode.code = m_nPlateCode;
		treeNode.is_stock = 0;
		if(pPlates->Find(pPlates->Root(), treeNode))
		{
			if(pPlates->FirstChild())
			{
				do 
				{
					CString str;
					str.Format("%s-%d(%06d)",pPlates->GetData().name.c_str(),\
						pPlates->GetData().company_number, pPlates->GetData().code);
					HTREEITEM hClass = m_wndClassView.InsertItem(str, 1, 1);
				} 
				while(pPlates->NextSibling());
			}
		}*/
	}

	//	չ�����ڵ�
	if(vecStockPlateData.size()>0)
		m_wndClassView.Expand(hRoot, TVE_EXPAND /*TVE_COLLAPSE*/);
	
}

int CStockPlatesView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_PLATEINFO, 0, 0, TRUE /* ������*/);

	// OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_STOCKINFO);

	//m_wndToolBar.ReplaceButton(ID_SORT_MENU, CStockInfoViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	return 0;
}

void CStockPlatesView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AdjustLayout();
}

void CStockPlatesView::OnContextMenu(CWnd* pWnd, CPoint point)
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
	menu.LoadMenu(IDR_POPUP_STOCK_PLATE);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CStockPlatesView::OnPaint()
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

void CStockPlatesView::AdjustLayout()
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


void CStockPlatesView::OnPlateStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllStockListView /*CPlateStockListView*/	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ʊ�б�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateGrossProfit()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateGrossProfitListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("ë�����б�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateAddStock()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());
		
		if(is_stock==0 /*&& code==0*/)
		{
			//	��� ������
			CInputTextDlg dlg;
			if(dlg.DoModal()!=IDOK)
				return;
			string strName = string(dlg.m_strInputText.GetBuffer());
			if(strName.empty())
				return;

			{
				JMutexAutoLock lock(((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_mutex);

				CStockPlateTree * pPlates = ((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_pTree;

				//	Ѱ�ҿ��õ� �������ʶ
				CStockPlateData treeNode;

				int i = 2000;
				while(1)
				{
					treeNode.code = Int2String(i, "%08d");
					treeNode.is_stock = 0;
					if(pPlates->SearchSpecialNode(treeNode)==NULL)
						break;
					i++;
				}
				treeNode.name = strName;
				treeNode.company_number = 1;
				
				CStockPlateData treeNodeParent;
				treeNodeParent.code = Int2String(code, "%08d");
				treeNodeParent.is_stock = 0;
				
				CStockPlateTree * pNode = pPlates->SearchSpecialNode(treeNodeParent);
				if(pNode)
				{
					CStockPlateData spd = *pNode->get();
					pNode->insert(treeNode);
				}
				((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->ImportToDatabase();
			}
			

			StockInfo_Reqeust req;
			req.code = -ID_READ_STOCKPLATE_SELF_SELECT;
			req.hwnd = NULL;
			((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_front(req);
		}
		else /*if(is_stock==0 && code>0)*/
		{
			AfxMessageBox("�뵽����ҵ�塿������С�塿��������A�ɡ������Ϻ���Ʊ���Ȱ���Ҽ����");	
		}
		
	}

	
}

void CStockPlatesView::OnPlateDelStock()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		if(code>0)
		{
			//	ɾ�� ������ ���� ����
			CStockPlateData treeNode;
			if(is_stock)
				treeNode.code = Int2String(code, "%06d");
			else
				treeNode.code = Int2String(code, "%08d");
			treeNode.is_stock = is_stock;

			JMutexAutoLock lock(((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_mutex);

			CStockPlateTree * pPlates = ((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_pTree;
			CStockPlateTree * pNode = pPlates->SearchSpecialNode(treeNode);
			if(pNode)
			{
				//	������е�����ڵ�
				pNode->clear();
				//	�������
				pNode->parent()->erase(treeNode);

				((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->ImportToDatabase();
			}

			StockInfo_Reqeust req;
			req.code = -ID_READ_STOCKPLATE_SELF_SELECT;
			req.hwnd = NULL;
			((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_front(req);
		}
	}
}




void CStockPlatesView::OnPlateClearStock()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		/*���԰��������*/
		if(code>0 && is_stock == 0)
		{
			//	ɾ�� ������ ���� ����
			CStockPlateData treeNode;
			if(is_stock)
				treeNode.code = Int2String(code, "%06d");
			else
				treeNode.code = Int2String(code, "%08d");
			treeNode.is_stock = is_stock;

			JMutexAutoLock lock(((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_mutex);
			CStockPlateTree * pPlates = ((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->m_pTree;
			CStockPlateTree * pNode = pPlates->SearchSpecialNode(treeNode);
			if(pNode)
			{
				pNode->clear();
				((CStockApp *)AfxGetApp())->m_pCSelfSelectStockPlates->ImportToDatabase();
			}

			StockInfo_Reqeust req;
			req.code = -ID_READ_STOCKPLATE_SELF_SELECT;
			req.hwnd = NULL;
			((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_front(req);
		}
	}
}


void CStockPlatesView::OnUpdatePlateAddStock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	if(m_nPlateType==ID_PLATE_TYPE_SELF_SELECT)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CStockPlatesView::OnUpdatePlateDelStock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	if(m_nPlateType==ID_PLATE_TYPE_SELF_SELECT)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}



void CStockPlatesView::OnUpdatePlateClearStock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	if(m_nPlateType==ID_PLATE_TYPE_SELF_SELECT)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}



void CStockPlatesView::OnPlateLiquidityRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateLiquidityRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateNetprofitsRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateNetProfitsRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�������ʹ���ʽ𾻶�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnTotalAssetsTurnoverRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateTotalAssetsTurnoverRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("���ʲ���ת��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnFixedAssetsTurnoverRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateFixedAssetsTurnoverRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�̶��ʲ���ת��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnCurrentAssetsTurnoverRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCurrentAssetsTurnoverRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�����ʲ���ת��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnInventoryTurnoverRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateInventoryTurnoverRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�����ת��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnDebtToAssetsRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateDebtToAssetsRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�ʲ���ծ��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnDebtToCapitalRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateDebtToCapitalRatioView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("������Ȩ�渺ծ��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnFundHoldRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateFundHoldView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("���������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnTotalAssetsGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateTotalAssetsGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("���ʲ���������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}


void CStockPlatesView::OnNetFixedAssetsGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateNetFixedAssestsGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�̶��ʲ���������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnMainIncomeGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateMainIncomeGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ӫ������������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateMainIncomeYearGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllMainIncomeYearGrowthStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ӫ������������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateResearchPaperQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CHexunResearchPaperListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ѷ�б���ѯ-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateZombieStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CZombieStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��ʬ��ҵ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlatePeStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPeStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "pe";
		CString title;
		title.Format("��̬PEֵ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateMainProfitYearGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllMainProfitYearGrowthStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ӫ������������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateBonusPlanQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllThisYearBonusListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("����ֺ�Ԥ����ѯ-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateMcstStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllMcstStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ʊ�ɱ�������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateAddIssuanceStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllAddIssuanceListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ʊ����ӯ������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateCorrectedMarketValue()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCorrectedMarketValueView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("����ֵ���۳����̲���������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateIndustryDynamicPe()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCsindexDynamicPeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		((CIndividualShareDoc *)pNewDoc)->m_strInput = "DynamicPe";

		CString title;
		title.Format("��֤��ҵ��̬PE-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateIndustryStaticPe()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCsindexDynamicPeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		((CIndividualShareDoc *)pNewDoc)->m_strInput = "StaticPe";

		CString title;
		title.Format("��֤��ҵ��̬PE-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateIndustryPb()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCsindexDynamicPeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		((CIndividualShareDoc *)pNewDoc)->m_strInput = "Pb";

		CString title;
		title.Format("��֤��ҵ�о���PB-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateIndustryCompanyNumber()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCsindexDynamicPeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		((CIndividualShareDoc *)pNewDoc)->m_strInput = "Company_Number";

		CString title;
		title.Format("��֤��ҵ��˾��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateDividendYieldRatio()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateCsindexDynamicPeView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		((CIndividualShareDoc *)pNewDoc)->m_strInput = "Dividend_Yield_Ratio";

		CString title;
		title.Format("��֤��ҵ��Ϣ��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateCsiDynamicPeStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllCsiDynamicPeStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "dynamic_pe";

		CString title;
		title.Format("��֤����PEֵ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateDealDetailDaily()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());


		CDealDetailDateDlg dlg;
		
		if(dlg.DoModal()==IDOK && dlg.m_strDealDetailDate.empty() ==false)
		{
			CPlateDealDetailDailyView	MonitorListView;

			pView = &MonitorListView;				
			pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

			pView = NULL;
			ASSERT_VALID(pDocTemplate);
			CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
			((CIndividualShareDoc *)pNewDoc)->m_strInput = dlg.m_strDealDetailDate;
			CString title;
			title.Format("�ɽ���ϸ-%s-%s",dlg.m_strDealDetailDate.c_str(), text);
			pNewDoc->SetTitle(title);
			CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
			wnd->ShowWindow(SW_SHOWMAXIMIZED);
			pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
			pDocTemplate->AddDocument(pNewDoc);	
		}
				
	}
}

void CStockPlatesView::OnPlateTurnoverRateDaily()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateTurnoverRateView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�ջ����ʣ��г���Ծ�ȣ�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnFocusNextOnPlate()
{
	// TODO: �ڴ���������������
	int k = 1;

	FocusOnNext();
}

void CStockPlatesView::OnPlateChangeRateSummary()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateChangeRateSummaryView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�����ǵ�����������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateGrossProfitRateQuarterGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateGrossProfitRateGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "profit_rate_quarter";
		CString title;
		title.Format("ë���ʼ��ȱ仯����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateGrossProfitRateChangeForLast()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateGrossProfitRateGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "profit_rate_change_for_last";
		CString title;
		title.Format("ͬ��һ���ȵ�������������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateGrossProfitChangeForAverage()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateGrossProfitRateGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "profit_rate_change_for_average";
		CString title;
		title.Format("ͬǰ4���ȵ�ƽ��������������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateGrossProfitRate4QuarterGrowth()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CPlateGrossProfitRateGrowthView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "profit_rate_4_quarter";
		CString title;
		title.Format("ǰ4���ȣ���������ƽ��ë��������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateCninfoAnnouncementQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CCninfoAnnouncementListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�޳��������ѯ-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

BOOL CStockPlatesView::PreTranslateMessage(MSG* pMsg)
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

void CStockPlatesView::OnPlateCsiStaticPeStockList()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CAllCsiDynamicPeStockListView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		pNewDoc->m_strInput = "static_pe";

		CString title;
		title.Format("��֤��̬PEֵ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateCninfoPdfQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CCninfoAnnouncePDFListView	 MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�޳��� PDF ����-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateShanghaiIndex()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		if(is_stock==0)
		{
			//	��ǰ ��� ���е� ��Ҷ�ӽڵ�
			//	���� ���Ѻ���顱 ����ͳ������
			if(m_nPlateType ==ID_PLATE_TYPE_SOHU ||  m_nPlateType ==ID_PLATE_TYPE_SHENZHEN_INDEXINFO)
			{
				CPlateSelectDlg dlg;
				dlg.m_nCode = codeStr;
				dlg.m_nPlateType = m_nPlateType;
				if(IDOK ==dlg.DoModal())
				{
					CPlateShanghaiIndexView	 MonitorListView;

					pView = &MonitorListView;				
					pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

					pView = NULL;
					ASSERT_VALID(pDocTemplate);
					CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
					pNewDoc->m_vec_request_code = dlg.m_vec_code;

					pNewDoc->m_nIs_Stock = dlg.m_nIs_Stock;
					//	������β�ѯ���� ��� ���� ָ������ ����������
					if(dlg.m_nIs_Stock==0)
						pNewDoc->m_nIs_Stock = m_nPlateType;

					pNewDoc->m_strInput = dlg.m_strGraphOrTable;
					CString title;
					title.Format("����ָ������-%s", text);
					pNewDoc->SetTitle(title);
					CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
					wnd->ShowWindow(SW_SHOWMAXIMIZED);
					pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
					pDocTemplate->AddDocument(pNewDoc);	
				}
			}
			else
			{
				AfxMessageBox("Ŀǰ�����Ѻ���� �� ���ڹ�ָ�����ͳ�����ݣ�");
			}
		}
		else
		{
			//	��ǰ ��� ���е� Ҷ�ӽڵ� ��leaf node��
			CPlateShanghaiIndexView	 MonitorListView;

			pView = &MonitorListView;				
			pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

			pView = NULL;
			ASSERT_VALID(pDocTemplate);
			CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
			pNewDoc->m_vec_request_code.push_back(codeStr);
			pNewDoc->m_nIs_Stock = 1;

			int nResult = AfxMessageBox("Yes��ͼ��չʾ��No�����չʾ ��",MB_YESNO);
			if (nResult == IDYES)
				pNewDoc->m_strInput = "Graph";
			else
				pNewDoc->m_strInput = "Table";

			CString title;
			title.Format("����ָ������-%s", text);
			pNewDoc->SetTitle(title);
			CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
			wnd->ShowWindow(SW_SHOWMAXIMIZED);
			pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
			pDocTemplate->AddDocument(pNewDoc);	
		}
		
	}
}

void CStockPlatesView::OnPlateCninfoGetLandQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CCninfoGetLandListView	 MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("�������ع������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateCninfoIncentivePlanQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CCninfoIncentivePlanListView	 MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("��Ʊ����Ԥ������-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CStockPlatesView::OnPlateCninfoShareHoldingQuery()
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

		int is_stock = (int)m_wndClassView.GetItemData(hTreeItem);

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());

		CCninfoShareHoldingListView	 MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CIndividualShareDoc(codeStr, m_nPlateType, is_stock); //strCarMunber);
		CString title;
		title.Format("ǰ10���ɶ��ֹ�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

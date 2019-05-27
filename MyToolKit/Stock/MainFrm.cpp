
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Stock.h"

#include "MainFrm.h"
#include "BaseMessageElementsParser.h"
#include "CalculateStockInfoEx.h"
#include "FindStockByPinyin.h"

#include "IndividualShareDoc.h"
#include "BaseHtmlView.h"
#include "AllStockListView.h"
#include "ZombieStockListView.h"
#include "AutoDownloadView.h"
#include "MainProductQueryView.h"
#include "PeStockListView.h"
#include "MacdStockListView.h"
#include "HexunResearchPaperListView.h"
#include "AllMainIncomeYearGrowthStockListView.h"
#include "AllMainProfitYearGrowthStockListView.h"
#include "AllRecentBonusCashStockListView.h"
#include "AllThisYearBonusListView.h"
#include "AllMcstStockListView.h"
#include "AllAddIssuanceListView.h"
#include "CninfoAnnouncementListView.h"
#include "CninfoAnnouncePDFListView.h"
#include "CninfoIncentivePlanListView.h"
#include "CninfoGetLandListView.h"
#include "CninfoShareHoldingListView.h"
#include "CninfoShareHoldingStatisticsView.h"
#include "PlateShanghaiIndexView.h"

#include "MarketExchageFundView.h"
#include "MarketMarginGuaranteeFundView.h"
#include "MarketCffexHs300FutureView.h"
#include "MarketSohuIndexView.h"
#include "MarketCsdcInvestorStatView.h"

#include "StockHomePageView.h"
#include "StatsGovCnChartView.h"
#include "StatsGovCnGridView.h"

#include "ShanghaiIndexView.h"

#include "Newmat11TestView.h"

#include "SimpleInputBox.h"
#include "StatsGovMenuDlg.h"
#include "StockGroupDlg.h"

#include "CalcFinanceDownload.h"
#include "CalcForecastDownload.h"
#include "CalcCapiStructDownload.h"
#include "CalcPeStockList.h"
#include "CalcMacdListData.h"
#include "CalcHexunResearchPaperQuery.h"
#include "CalcSohuMainIncomeCompoDownload.h"
#include "CalcCsiPeDailyDownload.h"
#include "CalcCsiCsrcPeDailyDownload.h"
#include "CalcSipfSettlementFundDownload.h"
#include "CalcSseMarginTradingDownload.h"
#include "CalcSzseMarginTradingDownload.h"
#include "CalcCsdcInvestorStatDownload.h"
#include "CalcCsdcSecurityIssueStatDownload.h"
#include "CalcUpdateStockInfo.h"
#include "CalcSzseIndexDailyDownload.h"

#include "CandlesticksJapanListView.h"
#include "MacdListView.h"
#include "BollListView.h"

#include "AutoDownloadDoc.h"
#include "AutoDownloadView.h"


extern UINT InitialReadStockInfoThreadFunc(LPVOID param);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)

	ON_MESSAGE(WM_USER_LOG_1, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_2, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_3, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_CapitalFlow163, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_FinanceReport, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_Forecast, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_CapitalStruct, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_ResearchPaper, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_Income_Composition, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_Cfi_Bonus, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_Cninfo, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_StatsGovCn, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_CSDC, OnUserLogWParam_1)

	ON_MESSAGE(WM_NOTIFY_FROM_TRAY,OnNotifyIcon)

	ON_MESSAGE(WM_USER_XML,	OnUserXmlWParam)
	ON_COMMAND(ID_SOUHU_PLATE, &CMainFrame::OnSouhuPlate)
	ON_COMMAND(ID_ALL_STOCK_LIST, &CMainFrame::OnAllStockList)
	/*ON_COMMAND(ID_SHANGHAI_STOCK_LIST, &CMainFrame::OnShanghaiStockList)
	ON_COMMAND(ID_SHENZHEN_A_STOCK_LIST, &CMainFrame::OnShenzhenAStockList)
	ON_COMMAND(ID_SMALL_MID_STOCK_LIST, &CMainFrame::OnSmallMidStockList)
	ON_COMMAND(ID_ENTREPR_STOCK_LIST, &CMainFrame::OnEntreprStockList)*/
	ON_COMMAND(ID_ALL_STOCK_DOWNLOAD, &CMainFrame::OnAllStockDownload)
	ON_COMMAND(ID_ZOMBIE_STOCK_LIST, &CMainFrame::OnZombieStockList)
	ON_COMMAND(ID_MAIN_PRODUCT_QUERY, &CMainFrame::OnMainProductQuery)
	ON_COMMAND(ID_PE_STOCK_LIST, &CMainFrame::OnPeStockList)
	ON_COMMAND(ID_MACD_STOCK_LIST, &CMainFrame::OnMacdStockList)
	ON_COMMAND(ID_HEXUN_RESEARCH_PAPER_QUERY, &CMainFrame::OnHexunResearchPaperQuery)
	ON_COMMAND(ID_MAIN_INCOME_YEAR_GROWTH_QUERY, &CMainFrame::OnMainIncomeYearGrowthQuery)
	ON_COMMAND(ID_MAIN_PROFIT_YEAR_GROWTH_QUERY, &CMainFrame::OnMainProfitYearGrowthQuery)
	ON_COMMAND(ID_RECENT_BONUS_CASH_QUERY, &CMainFrame::OnRecentBonusCashQuery)
	ON_COMMAND(ID_THIS_YEAR_BONUS_PLAN_QUERY, &CMainFrame::OnThisYearBonusPlanQuery)
	ON_COMMAND(ID_MCST_STOCK_LIST, &CMainFrame::OnMcstStockList)
	ON_COMMAND(ID_ADD_ISSUANCE_STOCK_LIST, &CMainFrame::OnAddIssuanceStockList)
	ON_COMMAND(ID_NEWMAT11_TEST, &CMainFrame::OnNewmat11Test)
	ON_COMMAND(ID_MARKET_EXCHANGE_FUND_IN_SETTLEMENT, &CMainFrame::OnMarketExchangeFundInSettlement)
	ON_COMMAND(ID_MARKET_MARGIN_GUARANTEE_FUND, &CMainFrame::OnMarketMarginGuaranteeFund)
	ON_COMMAND(ID_MARKET_CFFEX_HS300_FUTURE, &CMainFrame::OnMarketCffexHs300Future)
	ON_COMMAND(ID_MARKET_INDEX, &CMainFrame::OnMarketIndex)
	ON_COMMAND(ID_MARKET_INVESTOR_STAT, &CMainFrame::OnMarketInvestorStat)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(ID_STATSGOV_HGYD_MENU, ID_STATSGOV_HGYD_MENU, &CMainFrame::OnStatsgovHgydMenu)
	ON_COMMAND_RANGE(ID_STATSGOV_HGJD_MENU, ID_STATSGOV_HGJD_MENU, &CMainFrame::OnStatsgovHgydMenu)
	ON_COMMAND_RANGE(ID_STATSGOV_HGND_MENU, ID_STATSGOV_HGND_MENU, &CMainFrame::OnStatsgovHgydMenu)
	ON_COMMAND_RANGE(ID_STATSGOV_FSND_MENU, ID_STATSGOV_FSND_MENU, &CMainFrame::OnStatsgovHgydMenu)
	ON_COMMAND_RANGE(ID_STATSGOV_FSYD_MENU, ID_STATSGOV_FSYD_MENU, &CMainFrame::OnStatsgovHgydMenu)
	ON_COMMAND_RANGE(ID_STATSGOV_FSJD_MENU, ID_STATSGOV_FSJD_MENU, &CMainFrame::OnStatsgovHgydMenu)

	/*ON_COMMAND(ID_STATSGOV_HGJD_MENU, &CMainFrame::OnStatsgovHgjdMenu)
	ON_COMMAND(ID_STATSGOV_HGND_MENU, &CMainFrame::OnStatsgovHgndMenu)
	ON_COMMAND(ID_STATSGOV_FSND_MENU, &CMainFrame::OnStatsgovFsndMenu)
	ON_COMMAND(ID_STATSGOV_FSYD_MENU, &CMainFrame::OnStatsgovFsydMenu)
	ON_COMMAND(ID_STATSGOV_FSJD_MENU, &CMainFrame::OnStatsgovFsjdMenu)*/
	ON_COMMAND_RANGE(ID_FINANCE_SALES_FROM_OPERATIONS, ID_FINANCE_SALES_FROM_OPERATIONS, &CMainFrame::OnFinanceSalesFromOperations)
	ON_COMMAND_RANGE(ID_FINANCE_COST_OF_OPERATIONS, ID_FINANCE_COST_OF_OPERATIONS, &CMainFrame::OnFinanceSalesFromOperations)

	ON_COMMAND(ID_CNINFO_ANNOUNCEMENT_QUERY, &CMainFrame::OnCninfoAnnouncementQuery)
	ON_COMMAND(ID_PE_GROSS_LIST, &CMainFrame::OnPeGrossList)
	ON_COMMAND(ID_CNINFO_PDF_QUERY, &CMainFrame::OnCninfoPdfQuery)
	ON_COMMAND(ID_SHANGHAI_INDEX, &CMainFrame::OnShanghaiIndex)
	ON_COMMAND(ID_CNINFO_INCENTIVE_PLAN_QUERY, &CMainFrame::OnCninfoIncentivePlanQuery)
	ON_COMMAND(ID_HUSHEN_CHANGE_RATE_QUERY, &CMainFrame::OnHushenChangeRateQuery)
	ON_COMMAND(ID_SMALL_MIDDLE_INDEX, &CMainFrame::OnSmallMiddleIndex)
	ON_COMMAND(ID_CNINFO_GET_PLAN_QUERY, &CMainFrame::OnCninfoGetPlanQuery)
	ON_COMMAND(ID_ENTERPRENUER_INDEX, &CMainFrame::OnEnterprenuerIndex)
	ON_COMMAND(ID_CNINFO_SHARE_HOLDING_QUERY, &CMainFrame::OnCninfoShareHoldingQuery)
	ON_COMMAND(ID_CNINFO_SHARE_HOLDING_STATISTICS, &CMainFrame::OnCninfoShareHoldingStatistics)
	ON_COMMAND(ID_CANDLESTICKS_JAPAN_QUERY, &CMainFrame::OnCandlesticksJapanQuery)
	ON_COMMAND(ID_MACD_QUERY, &CMainFrame::OnMacdQuery)
	ON_COMMAND(ID_BOLL_QUERY, &CMainFrame::OnBollQuery)
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2005);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	/*��ʾ�������棬���ҿ�ʼ���ع�Ʊ��������*/
	m_pWndSplashScreen = new CSplashScreenEx();
	m_pWndSplashScreen->Create(this,"A �ɷ���ϵͳ��ӭ��",0,CSS_FADE | CSS_CENTERSCREEN | CSS_SHADOW);
	m_pWndSplashScreen->SetBitmap(IDB_SPLASH,255,0,255);
	m_pWndSplashScreen->SetTextFont("Impact",100,CSS_TEXT_NORMAL);
	m_pWndSplashScreen->SetTextRect(CRect(125,60,291,104));
	m_pWndSplashScreen->SetTextColor(RGB(255,255,255));
	m_pWndSplashScreen->SetTextFormat(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	m_pWndSplashScreen->Show();

	/*Sleep(1000);
	pSplash->SetText("You can display infos");

	pSplash->Hide();*/

	

	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // ����������ʽ...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // ����Ϊ FALSE �Ὣ�رհ�ť������ѡ�������Ҳ�
	mdiTabParams.m_bTabIcons = FALSE;    // ����Ϊ TRUE ���� MDI ѡ��������ĵ�ͼ��
	mdiTabParams.m_bAutoColor = TRUE;    // ����Ϊ FALSE ������ MDI ѡ����Զ���ɫ
	mdiTabParams.m_bDocumentMenu = TRUE; // ��ѡ�������ұ�Ե�����ĵ��˵�
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	//	��Ʊ
	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndEntrepreneurView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndSmallMidEnterpriseView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndShenzhenAsharesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndShanghaiStockView.EnableDocking(CBRS_ALIGN_ANY);
	//	���
	m_wndHangyePlatesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDiyuPlatesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndGainianPlatesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndSelfSelectPlatesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCsindexPlatesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCsindexCsrcPlatesView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndShenzhenIndexPlatesView.EnableDocking(CBRS_ALIGN_ANY);

	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	//m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndEntrepreneurView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndSmallMidEnterpriseView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndShenzhenAsharesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndShanghaiStockView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);

	m_wndHangyePlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndDiyuPlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndGainianPlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndSelfSelectPlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndCsindexPlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndCsindexCsrcPlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndShenzhenIndexPlatesView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	/*m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);*/


	// ������ǿ�Ĵ��ڹ���Ի���
	EnableWindowsDialog(ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);

	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// �����û�����Ĺ�����ͼ��
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	//	ȡ���˵��۵�
	//CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ������ҵ����ͼ
	m_wndEntrepreneurView.SetStockInfo(&((CStockApp *)AfxGetApp())->m_CEntrepreneurship);
	CString strEntrepreneurView;
	bNameValid = strEntrepreneurView.LoadString(IDS_ENTREPRENEUR_VIEW);
	ASSERT(bNameValid);
	if (!m_wndEntrepreneurView.Create(strEntrepreneurView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_ENTREPRENEUR, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ�������ҵ����ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// ������С����ͼ
	m_wndSmallMidEnterpriseView.SetStockInfo(&((CStockApp *)AfxGetApp())->m_CSmallMidEnterprise);
	CString strSmallMidEnterpriseView;
	bNameValid = strSmallMidEnterpriseView.LoadString(IDS_SMALLANDMID_VIEW);
	ASSERT(bNameValid);
	if (!m_wndSmallMidEnterpriseView.Create(strSmallMidEnterpriseView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SMALLMIDENTERPRISE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ�������С����ͼ������\n");
		return FALSE; 
	}

	// ��������A����ͼ
	m_wndShenzhenAsharesView.SetStockInfo(&((CStockApp *)AfxGetApp())->m_CShenzhenAshares);
	CString strShenzhenAsharesView;
	bNameValid = strShenzhenAsharesView.LoadString(IDS_SHENZHENASHARE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndShenzhenAsharesView.Create(strShenzhenAsharesView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SHENZHENASHARES, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������A����ͼ������\n");
		return FALSE; 
	}

	// �����Ϻ�֤ȯ��������Ʊ��ͼ
	m_wndShanghaiStockView.SetStockInfo(&((CStockApp *)AfxGetApp())->m_CShanghaiStock);
	CString strShanghaiStockView;
	bNameValid = strShanghaiStockView.LoadString(IDS_SHANGHAISTOCK_VIEW);
	ASSERT(bNameValid);
	if (!m_wndShanghaiStockView.Create(strShanghaiStockView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SHANGHAISTOCK, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}

	// ���������ͼ
	m_wndHangyePlatesView.SetPlateCode(ID_PLATE_TYPE_SOHU, 1631);
	CString strHangyePlatesView;
	bNameValid = strHangyePlatesView.LoadString(IDS_SOUHU_HANGYE_PLATE);
	ASSERT(bNameValid);
	if (!m_wndHangyePlatesView.Create(strHangyePlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_HANGYE_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}

	m_wndDiyuPlatesView.SetPlateCode(ID_PLATE_TYPE_SOHU,1632);
	CString strDiyuPlatesView;
	bNameValid = strDiyuPlatesView.LoadString(IDS_SOUHU_DIYU_PLATE);
	ASSERT(bNameValid);
	if (!m_wndDiyuPlatesView.Create(strDiyuPlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_DIYU_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}

	m_wndGainianPlatesView.SetPlateCode(ID_PLATE_TYPE_SOHU,1630);
	CString strGainianPlatesView;
	bNameValid = strGainianPlatesView.LoadString(IDS_SOUHU_GAINIAN_PLATE);
	ASSERT(bNameValid);
	if (!m_wndGainianPlatesView.Create(strGainianPlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_GAINIAN_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}

	m_wndCsindexPlatesView.SetPlateCode(ID_PLATE_TYPE_CSINDEX,0);
	CString strCsindexPlatesView;
	bNameValid = strCsindexPlatesView.LoadString(IDS_CSINDEX_PLATE);
	ASSERT(bNameValid);
	if (!m_wndCsindexPlatesView.Create(strCsindexPlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_CSINDEX_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}

	m_wndCsindexCsrcPlatesView.SetPlateCode(ID_PLATE_TYPE_CSINDEX_CSRC,0);
	CString strCsindexCsrcPlatesView;
	bNameValid = strCsindexCsrcPlatesView.LoadString(IDS_CSINDEX_CSRC_PLATE);
	ASSERT(bNameValid);
	if (!m_wndCsindexCsrcPlatesView.Create(strCsindexCsrcPlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_CSINDEX_CSRC_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}


	m_wndShenzhenIndexPlatesView.SetPlateCode(ID_PLATE_TYPE_SHENZHEN_INDEXINFO,0);
	CString strShenzhenIndexPlatesView;
	bNameValid = strShenzhenIndexPlatesView.LoadString(IDS_SHENZHEN_INDEXINFO_PLATE);
	ASSERT(bNameValid);
	if (!m_wndShenzhenIndexPlatesView.Create(strShenzhenIndexPlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_CSINDEX_CSRC_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}

	//	�г� root ��Ŀ¼�µ����� ��ѡ�����
	m_wndSelfSelectPlatesView.SetPlateCode(ID_PLATE_TYPE_SELF_SELECT, 0);
	CString strSelfSelectPlatesView;
	bNameValid = strSelfSelectPlatesView.LoadString(IDS_SELF_SELECT_PLATE);
	ASSERT(bNameValid);
	if (!m_wndSelfSelectPlatesView.Create(strSelfSelectPlatesView, this, CRect(0, 0, 200, 200), TRUE,\
		ID_VIEW_SELF_SELECT_PLATE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������Ϻ�֤ȯ��������Ʊ��ͼ������\n");
		return FALSE; 
	}


	// ��������ͼ
	/*CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������ͼ������\n");
		return FALSE; 
	}*/

	// �����ļ���ͼ
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	/*CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; 
	}*/

	SetDockingWindowIcons(theApp.m_bHiColorIcons);

	ToTray();
	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	/*HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);*/

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	/*HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);*/

	HICON hEntrepreneurViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndEntrepreneurView.SetIcon(hEntrepreneurViewIcon, FALSE);

	HICON hSmallMidEnterpriseViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndSmallMidEnterpriseView.SetIcon(hSmallMidEnterpriseViewIcon, FALSE);

	HICON hShenzhenAShareViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndShenzhenAsharesView.SetIcon(hShenzhenAShareViewIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
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

	return CMDIFrameWndEx::PreTranslateMessage(pMsg);
}

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// ���ཫִ�������Ĺ���

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}



LRESULT CMainFrame::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;
	int		logType = (int)lParam;

	if (CMessageString::IsStringValid(pString))
	{
		m_wndOutput.AppendLog(pString->GetBuffer(), logType);
		delete pString;
	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}



LRESULT CMainFrame::OnUserXmlWParam(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;

	stringstream ss;
	// make sure passed string is valid (this is important to prevent unexpected
	// results if an invalid string is passed)
	if (CMessageString::IsStringValid(pString))
	{
		CBaseMessageElementsParser parser(this);
		if(parser.Parse(pString->GetBuffer(), pString->GetLength())==false)
		{
			ss.str("");
			ss << "CMainFrame::OnUserXmlWParam, xml parser ��������";
			sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);			
		}

		delete pString;
		
		if(parser.msg_type=="ReadFinished")
		{
			if(atoi(parser.param1.c_str())==-ID_READ_STOCKINFO_ENTERPRENUER)
			{
				//	��Ʊ��Ϣ�����ݿ������ϣ��յ�֪ͨ����ʼ����չʾ��
				m_wndEntrepreneurView.FillClassView();

				//////////////////////////////////////////////////////////////////////////
				// �����������ڹ�Ʊÿ��������Ϣ

				/*CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = 60000;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_3;
				pThread = AfxBeginThread(AutoDownloadThreadFunc, req);*/

				//////////////////////////////////////////////////////////////////////////
				// �������� Souhu ��Ʊÿ��������Ϣ (��ҵ��)
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_TRADINGDAILY_ENTERPRENUER;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_3;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
				
				//////////////////////////////////////////////////////////////////////////
				// �������� 163 ���� ��Ʊÿ���ʽ����� (��ҵ��)
				CDownloadRequest * req1 = new CDownloadRequest;
				req1->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_ENTERPRENUER;
				req1->m_hwnd = NULL;
				req1->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				

				//////////////////////////////////////////////////////////////////////////
				//	�������롾��ҵ�塿�������ڵĲ��񱨱�
				/*time_t curtime = time (NULL);
				struct tm * tm1;
				tm1 = gmtime (&curtime);
				char tmp[256] = { 0 };
				snprintf (tmp, 255, "%4d-%02d-%02d", 1900 + tm1->tm_year -1, tm1->tm_mon+1, tm1->tm_mday);	

				CEntrepreneurship entrepreneur;
				CBussinessUtils::GetEntrepreneurship(entrepreneur);
				for(int k=0; k<entrepreneur.m_vec_code.size(); k++)
				{
					StockInfo_Reqeust req;
					req.code = entrepreneur.m_vec_code[k];
					req.hwnd = NULL;
					req.logType = WM_USER_LOG_2;
					req.strAfterDate = string(tmp);
					((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req);
				}*/
				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���صĲ��񱨱��Ʊ
				{
					CCalcFinanceDownload * cse =  new CCalcFinanceDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcFinanceDownload::NeedDownloadFinanceReport1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص�ҵ��Ԥ���Ʊ
				{
					CCalcForecastDownload * cse =  new CCalcForecastDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcForecastDownload::NeedDownloadPerformanceForecast1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���صĹ�Ʊ�ṹ��Ʊ
				{
					CCalcCapiStructDownload * cse =  new CCalcCapiStructDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcCapiStructDownload::NeedDownload1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص���Ӫҵ�񹹳ɵĹ�Ʊ
				{
					CCalcSohuMainIncomeCompoDownload * cse =  new CCalcSohuMainIncomeCompoDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcSohuMainIncomeCompoDownload::Execute1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص��й�Ͷ���߱����������֤���׽����ݵĽ�������
				{
					CCalcSipfSettlementFundDownload * cse =  new CCalcSipfSettlementFundDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcSipfSettlementFundDownload::NeedDownload1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص��Ϻ�֤ȯ��������������ȯ���ݵĽ�������
				{
					CCalcSseMarginTradingDownload * cse =  new CCalcSseMarginTradingDownload(m_hWnd, WM_USER_LOG_Cfi_Bonus);
					cse->ScheduleTask(&CCalcSseMarginTradingDownload::NeedDownload1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص�����֤ȯ��������������ȯ���ݵĽ�������
				{
					CCalcSzseMarginTradingDownload * cse =  new CCalcSzseMarginTradingDownload(m_hWnd, WM_USER_LOG_Cfi_Bonus);
					cse->ScheduleTask(&CCalcSzseMarginTradingDownload::NeedDownload1);
				}

				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص��й��������ݵ�����
				{
					CCalcCsdcInvestorStatDownload * cse =  new CCalcCsdcInvestorStatDownload(m_hWnd, WM_USER_LOG_CSDC);
					cse->ScheduleTask(&CCalcCsdcInvestorStatDownload::NeedDownload1);
				}

				{
					CCalcCsdcSecurityIssueStatDownload * cse =  new CCalcCsdcSecurityIssueStatDownload(m_hWnd, WM_USER_LOG_CSDC);
					cse->ScheduleTask(&CCalcCsdcSecurityIssueStatDownload::NeedDownload1);
				}
			}
			else if(atoi(parser.param1.c_str())==-ID_READ_STOCKINFO_SMALLMID)
			{
				m_wndSmallMidEnterpriseView.FillClassView();

				//////////////////////////////////////////////////////////////////////////
				// �������� 163 ���� ��Ʊÿ���ʽ����� (��С��)
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_SMALL_AND_MID;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);

				
			}
			else if(atoi(parser.param1.c_str())==-ID_READ_STOCKINFO_SHENZHENA)
			{
				m_wndShenzhenAsharesView.FillClassView();

				//////////////////////////////////////////////////////////////////////////
				// �������� 163 ���� ��Ʊÿ���ʽ����� (���� A �ɰ�)
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_SHENZHEN_ASHARE;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);

				
			}
			else if(atoi(parser.param1.c_str())==-ID_READ_STOCKINFO_SHANGHAISTOCK)
			{
				m_wndShanghaiStockView.FillClassView();

				//////////////////////////////////////////////////////////////////////////
				// �������� 163 ���� ��Ʊÿ���ʽ����� ���Ϻ���Ʊ��
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_SHANGHAISTOCK;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);

				//////////////////////////////////////////////////////////////////////////
				// �������� �Ѻ� ��Ʊҵ��Ԥ�� (���й�Ʊ)  ,��Ϊ���������������������ѡ��������
				/*{
					CDownloadRequest * req2 = new CDownloadRequest;
					req2->m_nDownloadType = ID_DOWNLOAD_PERFORMANCE_FORECAST;
					req2->m_hwnd = NULL;
					req2->m_nLogType = WM_USER_LOG_Forecast;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req2);
				}*/
								

				//////////////////////////////////////////////////////////////////////////
				// �������� ��Ѷ �о����� (���й�Ʊ)
				CDownloadRequest * req3 = new CDownloadRequest;
				req3->m_nDownloadType = ID_DOWNLOAD_HEXUN_RESEARCH_PAPER;
				req3->m_hwnd = NULL;
				req3->m_nLogType = WM_USER_LOG_ResearchPaper;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req3);
				
				//////////////////////////////////////////////////////////////////////////
				// �������� �в��� �ֺ졢���۹�Ʊ (���й�Ʊ)
				/*{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CFI_BONUS_SHARE;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cfi_Bonus;
					//req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);	
				}*/

				//////////////////////////////////////////////////////////////////////////
				// �������� �޳��� �ֺ졢���۹�Ʊ (���й�Ʊ)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CNINFO_BONUS_SHARE;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cfi_Bonus;
					//req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);	
				}

				//////////////////////////////////////////////////////////////////////////
				// �������� ͬ��˳ �ֺ����� (���й�Ʊ)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_10JQKA_BONUS_SHARE;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_CapitalStruct;
					//req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}

				//////////////////////////////////////////////////////////////////////////
				// �������� �޳������� (���й�Ʊ)
				/*{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CNINFO_ANNOUNCEMENT;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cninfo;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}*/

				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CNINFO_ANNOUNCEMENT_SHANGHAI;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cninfo;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}

				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CNINFO_ANNOUNCEMENT_SHENZHEN_ASHARE;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cninfo;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}

				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CNINFO_ANNOUNCEMENT_SMALLANDMID;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cninfo;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}

				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CNINFO_ANNOUNCEMENT_ENTERPRENEUR;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cninfo;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}


				//////////////////////////////////////////////////////////////////////////
				// �������� ����ͳ�ƾ����� "��ʡ���"
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_STATSGOV_FSND;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_StatsGovCn;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}

				//////////////////////////////////////////////////////////////////////////
				// �������� ���ڽ������� ָ����������Ϣ
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_SHENZHEN_INDEX_YANGBEN;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_1;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
				}


			}
			else if(atoi(parser.param1.c_str()) == -ID_READ_STOCKPLATE_SOHU)
			{

				//////////////////////////////////////////////////////////////////////////
				//	���� ���� stockinfo �е� ������Ϣ
				{
					CCalcUpdateStockInfo * cse =  new CCalcUpdateStockInfo(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcUpdateStockInfo::Execute1);
				}


				// �����Ϣ �������ṹ OK�� չʾͣ����
				m_wndHangyePlatesView.FillClassView();
				m_wndDiyuPlatesView.FillClassView();
				m_wndGainianPlatesView.FillClassView();

				//	���������Ѻ������Ϣ��Ϊ����������׼��
				if(1)
				{
					CDocTemplate * pDocTemplate = NULL;
					CView * pView = NULL;
					CAutoDownloadView	MonitorListView;

					pView = &MonitorListView;				
					pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

					pView = NULL;
					ASSERT_VALID(pDocTemplate);
					CIndividualShareDoc * pNewDoc = new CIndividualShareDoc("-1"); //strCarMunber);
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_CFFEX_FUTURE_DAILY);
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_SOUHU_STOCK_PLATE);
					//pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_CNINFO_ANNOUNCEMENT);
					
					CString title;
					title.Format("�Զ�����-%s", "��ָ�ڻ����Ѻ����");
					pNewDoc->SetTitle(title);
					CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
					wnd->ShowWindow( SW_SHOWMAXIMIZED);
					pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
					pDocTemplate->AddDocument(pNewDoc);	
				}

				//	���������й�����ͳ�ƾ�����
				/*if(1)
				{
					CDocTemplate * pDocTemplate = NULL;
					CView * pView = NULL;
					CAutoDownloadView	MonitorListView;

					pView = &MonitorListView;				
					pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

					pView = NULL;
					ASSERT_VALID(pDocTemplate);
					CIndividualShareDoc * pNewDoc = new CIndividualShareDoc("-1");
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_STATSGOV_FSND);
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_STATSGOV_FSJD);
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_STATSGOV_FSYD);

					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_STATSGOV_HGYD);
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_STATSGOV_HGJD);
					pNewDoc->m_vecCommandCode.push_back(ID_DOWNLOAD_STATSGOV_HGND);

					

					CString title;
					title.Format("�Զ�����-%s", "����ͳ�ƾ�");
					pNewDoc->SetTitle(title);
					CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);
					wnd->ShowWindow(SW_SHOWNORMAL);
					pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
					pDocTemplate->AddDocument(pNewDoc);	
				}*/
				
			}
			else if(atoi(parser.param1.c_str()) == -ID_READ_STOCKPLATE_SELF_SELECT)
			{
				// ��ѡ�����Ϣ �������ṹ OK�� չʾͣ����
				m_wndSelfSelectPlatesView.FillClassView();
			}
			else if(atoi(parser.param1.c_str()) == -ID_READ_STOCKPLATE_CSINDEX)
			{
				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص���ָ֤����˾��ӯ�ʵ����ݵĽ�������
				{
					CCalcCsiPeDailyDownload * cse =  new CCalcCsiPeDailyDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcCsiPeDailyDownload::NeedDownload1);
				}

				// ��ѡ�����Ϣ �������ṹ OK�� չʾͣ����
				m_wndCsindexPlatesView.FillClassView();

				
			}
			else if(atoi(parser.param1.c_str()) == -ID_READ_STOCKPLATE_CSINDEX_CSRC)
			{
				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص���ָ֤����˾��ӯ�ʵ����ݵĽ�������
				{
					CCalcCsiCsrcPeDailyDownload * cse =  new CCalcCsiCsrcPeDailyDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcCsiCsrcPeDailyDownload::NeedDownload1);
				}

				// ��ѡ�����Ϣ �������ṹ OK�� չʾͣ����
				m_wndCsindexCsrcPlatesView.FillClassView();
			}
			else if(atoi(parser.param1.c_str()) == -ID_READ_SHENZHEN_INDEXINFO)
			{
				//////////////////////////////////////////////////////////////////////////
				//	����������Ҫ���ص����ڽ������� ��Ʊָ�� �����ݵĽ�������
				{
					CCalcSzseIndexDailyDownload * cse =  new CCalcSzseIndexDailyDownload(m_hWnd, WM_USER_LOG_1);
					cse->ScheduleTask(&CCalcSzseIndexDailyDownload::NeedDownload1);
				}

				// ��ѡ�����Ϣ �������ṹ OK�� չʾͣ����
				m_wndShenzhenIndexPlatesView.FillClassView();
			}
		}
		
		if(parser.msg_type=="DownloadFinished")
		{
			
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_SHANGHAI_COMPOSITE_INDEX)
			{
				m_pWndSplashScreen->SetText("����300ָ��������...");

				// �������� ����300ָ��
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_HUSHENG300_INDEX;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			else if(atoi(parser.param1.c_str())==ID_DOWNLOAD_HUSHENG300_INDEX)
			{
				m_pWndSplashScreen->SetText("��С���ۺ�ָ��������...");

				// �������� ��С���ۺ�ָ��
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_SMALL_MIDDLE_INDEX;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			else if(atoi(parser.param1.c_str())==ID_DOWNLOAD_SMALL_MIDDLE_INDEX)
			{
				m_pWndSplashScreen->SetText("��ҵ���ۺ�ָ��������...");

				// �������� ��ҵ���ۺ�ָ��
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_ENTERPRENUER_INDEX;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			else if(atoi(parser.param1.c_str())==ID_DOWNLOAD_ENTERPRENUER_INDEX)
			{
				m_pWndSplashScreen->SetText("��֤��ָ������...");

				// �������� ��֤��ָ
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_SHENZHENG_COMPOSITE_INDEX;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			else if(atoi(parser.param1.c_str())==ID_DOWNLOAD_SHENZHENG_COMPOSITE_INDEX)
			{
				m_pWndSplashScreen->SetText("����A��������...");

				// �������� ����A�� ��Ʊ��������
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STOCKINFO_SHENZHEN_ASHARE;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			else if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STOCKINFO_SHENZHEN_ASHARE)
			{
				m_pWndSplashScreen->SetText("������С��������...");

				// �������� ��С�� ��Ʊ��������
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STOCKINFO_SMALLANDMID;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STOCKINFO_SMALLANDMID)
			{
				m_pWndSplashScreen->SetText("���ڴ�ҵ��������...");

				// �������� ��ҵ�� ��Ʊ��������
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STOCKINFO_ENTERPRENEUR;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
				
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STOCKINFO_ENTERPRENEUR)
			{
				m_pWndSplashScreen->SetText("�Ϻ�A��������...");

				// �������� �Ϻ� A �� ��Ʊ��������
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STOCKINFO_SHANGHAI;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_1;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
				
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STOCKINFO_SHANGHAI)
			{
				if(parser.param2=="NewData")
				{
					m_pWndSplashScreen->SetText("�޳�����������������...");

					// �������� �޳��� ��Ʊ��������
					CDownloadRequest * req = new CDownloadRequest;
					req->m_nDownloadType = ID_DOWNLOAD_CNINFO_STOCKINFO;
					req->m_hwnd = NULL;
					req->m_nLogType = WM_USER_LOG_1;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
				}
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_CNINFO_STOCKINFO ||
				(atoi(parser.param1.c_str())==ID_DOWNLOAD_STOCKINFO_SHANGHAI && parser.param2=="NoMoreData" ))
			{

				m_pWndSplashScreen->SetText("��Ʊ�������϶�����...");

				//	���������������,�������� ������־
				((CStockApp *)AfxGetApp())->m_StockDataLog.FetchFromDB();

				// ������A�ɡ���Ϣ������ɣ�����Ҫ����룬��ˢ�°��չʾ��
				StockInfo_Reqeust req_read;
				req_read.code = -ID_READ_STOCKINFO_SHENZHENA;
				req_read.hwnd = NULL;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				// ����С�塿��Ϣ������ɣ�����Ҫ����룬��ˢ�°��չʾ��
				req_read.code = -ID_READ_STOCKINFO_SMALLMID;
				req_read.hwnd = NULL;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				// ����ҵ�塿��Ϣ������ɣ�����Ҫ����룬��ˢ�°��չʾ��
				req_read.code = -ID_READ_STOCKINFO_ENTERPRENUER;
				req_read.hwnd = NULL;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				// ���Ϻ���Ʊ����Ϣ������ɣ�����Ҫ����룬��ˢ�°��չʾ��
				req_read.code = -ID_READ_STOCKINFO_SHANGHAISTOCK;
				req_read.hwnd = NULL;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				// ���� ���̶߳��� ���Ϲ�Ʊ��Ϣ
				InitialReadStockInfoThreadFunc(false);

				m_pWndSplashScreen->SetText("���������϶�����...");

				//	�������� ��Ʊ��Ϣ�������Ϣ����ѡ��飬 ��֤��ҵ������, ���ڹ�Ʊָ����� 
				req_read.code = -ID_READ_STOCKPLATE_SELF_SELECT;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STOCKPLATE_CSINDEX;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STOCKPLATE_CSINDEX_CSRC;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STOCKPLATE_SOHU;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				// ���� ���̶߳��� ���Ϲ�Ʊ��Ϣ
				InitialReadStockInfoThreadFunc(false);

				m_pWndSplashScreen->SetText("��֤��ָ��������...");

				req_read.code = -ID_READ_SHENZHEN_INDEXINFO;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				// ���� ���̶߳��� ���ϰ����Ϣ
				InitialReadStockInfoThreadFunc(false);

				// �����������߳�
				((CStockApp *)AfxGetApp())->StartWorkerThread(InitialReadStockInfoThreadFunc,(LPVOID)TRUE);

				//	���ؿ�����ʾ��
				m_pWndSplashScreen->Hide();
				m_pWndSplashScreen = NULL;

				// �������ѳ�ʼ���������ʾ����������и���
				ShowWindow(SW_SHOWMAXIMIZED);
				UpdateWindow();

				//	�������� ����ͳ�ƾֲ˵�
				
				req_read.code = -ID_READ_STATSGOV_HGYD;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STATSGOV_HGJD;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STATSGOV_HGND;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STATSGOV_FSND;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STATSGOV_FSYD;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);

				req_read.code = -ID_READ_STATSGOV_FSJD;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_back(req_read);


				//	������ϵͳ��ҳ�� 
				CDocTemplate * pDocTemplate = NULL;
				CView * pView = NULL;
				CStockHomePageView	MonitorListView;

				pView = &MonitorListView;				
				pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

				pView = NULL;
				ASSERT_VALID(pDocTemplate);
				CIndividualShareDoc * pNewDoc = new CIndividualShareDoc("-1"); //strCarMunber);
			
				CString title;
				title.Format("��ҳ��HomePage��%s", "");
				pNewDoc->SetTitle(title);
				CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
				wnd->ShowWindow(SW_SHOWMAXIMIZED);
				pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
				pDocTemplate->AddDocument(pNewDoc);	
			}

			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_TRADINGDAILY_ENTERPRENUER)
			{
				// �������� Yahoo ��Ʊÿ��������Ϣ (��С��)
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_TRADINGDAILY_SMALL_AND_MID;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_3;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_TRADINGDAILY_SMALL_AND_MID)
			{
				// �������� Yahoo ��Ʊÿ��������Ϣ (���� A �ɰ�)
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_TRADINGDAILY_SHENZHEN_ASHARE;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_3;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_TRADINGDAILY_SHENZHEN_ASHARE)
			{
				// �������� Yahoo ��Ʊÿ��������Ϣ ���Ϻ���Ʊ��
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_TRADINGDAILY_SHANGHAISTOCK;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_3;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}


			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_CAPITALFLOW_ENTERPRENUER)
			{
				// �������� 163 ���� ��Ʊÿ���ʽ����� (��С��)
				/*CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_SMALL_AND_MID;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);*/
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_CAPITALFLOW_SMALL_AND_MID)
			{
				// �������� 163 ���� ��Ʊÿ���ʽ����� (���� A �ɰ�)
				/*CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_SHENZHEN_ASHARE;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);*/
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_CAPITALFLOW_SHENZHEN_ASHARE)
			{
				// �������� 163 ���� ��Ʊÿ���ʽ����� ���Ϻ���Ʊ��
				/*CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_CAPITALFLOW_SHANGHAISTOCK;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_CapitalFlow163;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);*/
			}

			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_SOUHU_STOCK_PLATE)
			{
				// �Ѻ������Ϣ������ɣ�����Ҫ����룬��ˢ�°��չʾ��
				StockInfo_Reqeust req;
				req.code = -ID_READ_STOCKPLATE_SOHU;
				req.hwnd = NULL;
				((CStockApp *)AfxGetApp())->m_listStockinfoReq.push_front(req);
			}

			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STATSGOV_FSND)
			{
				// �������� ����ͳ�ƾ� "��ʡ�¶�"
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STATSGOV_FSYD;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_StatsGovCn;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STATSGOV_FSYD)
			{
				// �������� ����ͳ�ƾ� "��ʡ����"
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STATSGOV_FSJD;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_StatsGovCn;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STATSGOV_FSJD)
			{
				// �������� ����ͳ�ƾ� "ȫ���¶�"
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STATSGOV_HGYD;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_StatsGovCn;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STATSGOV_HGYD)
			{
				// �������� ����ͳ�ƾ� "ȫ������"
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STATSGOV_HGJD;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_StatsGovCn;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			if(atoi(parser.param1.c_str())==ID_DOWNLOAD_STATSGOV_HGJD)
			{
				// �������� ����ͳ�ƾ� "ȫ�����"
				CDownloadRequest * req = new CDownloadRequest;
				req->m_nDownloadType = ID_DOWNLOAD_STATSGOV_HGND;
				req->m_hwnd = NULL;
				req->m_nLogType = WM_USER_LOG_StatsGovCn;
				((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
			}
			
		}
		if(parser.msg_type=="DatabaseImported")
		{
			if(parser.model=="CSouhuTradingDaily")
			{
				/*CCalculateStockInfoEx * cse =  new CCalculateStockInfoEx(NULL, WM_USER_LOG_1);
				cse->m_vec_code[0] = atoi(parser.code.c_str());
				cse->m_vec_calculate_date[0] = parser.param1;
				cse->m_vec_close[0] = String2Double(parser.param2);
				cse->ScheduleTask(&CCalculateStockInfoEx::ImportToDatabase1);*/

				/*CStockApp * pApp = (CStockApp *)AfxGetApp();
				if(pApp->m_mapClosePrice.count(atoi(parser.code.c_str()))==0)
					pApp->m_mapClosePrice[atoi(parser.code.c_str())]= String2Double(parser.param2);*/
			}

		}

		if(parser.msg_type=="TaskFinished")
		{
			stringstream ss;
			ss << parser.model << "��" << (parser.param1) << "�� ����������. ";

			if(parser.model=="CCalcForecastDownload")
			{
				CCalcForecastDownload * cse = (CCalcForecastDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{

					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_PERFORMANCE_FORECAST_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Forecast;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}
			}
			else if(parser.model=="CCalcFinanceDownload")
			{
				CCalcFinanceDownload * cse = (CCalcFinanceDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_FINANCE_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_FinanceReport;

					CDownloadRequest * req2 = new CDownloadRequest;
					req2->m_nDownloadType = ID_DOWNLOAD_FINANCE_SELECTED;
					req2->m_hwnd = NULL;
					req2->m_nLogType = WM_USER_LOG_FinanceReport;

					CDownloadRequest * req3 = new CDownloadRequest;
					req3->m_nDownloadType = ID_DOWNLOAD_FINANCE_SELECTED;
					req3->m_hwnd = NULL;
					req3->m_nLogType = WM_USER_LOG_FinanceReport;

					for(int i=0; i< cse->m_vec_code.size(); i++)
					{
						CDownloadRequest * req = NULL;
						if(i%3==0)	req = req1;
						else if(i%3==1) req = req2;
						else  req = req3;

						req->m_vecCode.push_back(cse->m_vec_code[i]);
						req->m_vec_cninfo_orgid.push_back(cse->m_vec_cninfo_orgid[i]);
					}
					
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req2);
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req3);

					delete cse;
				}
			}
			else if(parser.model=="CCalcCapiStructDownload")
			{
				CCalcCapiStructDownload * cse = (CCalcCapiStructDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					//	ͬ��˳�ɱ��ṹ �ֳ� 5 ���߳�ͬʱ����
					CDownloadRequest * req1 = new CDownloadRequest;
					CDownloadRequest * req2 = new CDownloadRequest;
					CDownloadRequest * req3 = new CDownloadRequest;
					CDownloadRequest * req4 = new CDownloadRequest;
					CDownloadRequest * req5 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CAPITIALSTRUCT_SELECTED;
					req2->m_nDownloadType = ID_DOWNLOAD_CAPITIALSTRUCT_SELECTED;
					req3->m_nDownloadType = ID_DOWNLOAD_CAPITIALSTRUCT_SELECTED;
					req4->m_nDownloadType = ID_DOWNLOAD_CAPITIALSTRUCT_SELECTED;
					req5->m_nDownloadType = ID_DOWNLOAD_CAPITIALSTRUCT_SELECTED;

					req1->m_hwnd = NULL;
					req2->m_hwnd = NULL;
					req3->m_hwnd = NULL;
					req4->m_hwnd = NULL;
					req5->m_hwnd = NULL;

					req1->m_nLogType = WM_USER_LOG_CapitalStruct;
					req2->m_nLogType = WM_USER_LOG_CapitalStruct;
					req3->m_nLogType = WM_USER_LOG_CapitalStruct;
					req4->m_nLogType = WM_USER_LOG_CapitalStruct;
					req5->m_nLogType = WM_USER_LOG_CapitalStruct;

					for(int k = 0; k< cse->m_vec_code.size(); k++)
					{
						if(k%5==0)	req1->m_vecCode.insert(req1->m_vecCode.end(), cse->m_vec_code[k]);
						if(k%5==1)	req2->m_vecCode.insert(req2->m_vecCode.end(), cse->m_vec_code[k]);
						if(k%5==2)	req3->m_vecCode.insert(req3->m_vecCode.end(), cse->m_vec_code[k]);
						if(k%5==3)	req4->m_vecCode.insert(req4->m_vecCode.end(), cse->m_vec_code[k]);
						if(k%5==4)	req5->m_vecCode.insert(req5->m_vecCode.end(), cse->m_vec_code[k]);
					}
					//req1->m_vecCode = cse->m_vec_code;

					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req2);
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req3);
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req4);
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req5);

					delete cse;
				}
			}
			else if(parser.model=="CCalcSohuMainIncomeCompoDownload")
			{
				CCalcSohuMainIncomeCompoDownload * cse = (CCalcSohuMainIncomeCompoDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_INCOME_COMPOSITION_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Income_Composition;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}

				
			}
			else if(parser.model=="CCalcCsiPeDailyDownload")
			{
				CCalcCsiPeDailyDownload * cse = (CCalcCsiPeDailyDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CSINDEX_PE_DAILY_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_2;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}
			}
			else if(parser.model=="CCalcCsiCsrcPeDailyDownload")
			{
				CCalcCsiCsrcPeDailyDownload * cse = (CCalcCsiCsrcPeDailyDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CSINDEX_CSRC_PE_DAILY_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_2;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}
			}
			else if(parser.model=="CCalcSipfSettlementFundDownload")
			{
				CCalcSipfSettlementFundDownload * cse = (CCalcSipfSettlementFundDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_SIPF_SETTLEMENT_FUND_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cfi_Bonus;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}

			}
			else if(parser.model=="CCalcSseMarginTradingDownload")
			{
				CCalcSseMarginTradingDownload * cse = (CCalcSseMarginTradingDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_SSE_MARGIN_TRADING_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cfi_Bonus;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);	

					delete cse;
				}

			}
			else if(parser.model=="CCalcSzseMarginTradingDownload")
			{
				CCalcSzseMarginTradingDownload * cse = (CCalcSzseMarginTradingDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_SZSE_MARGIN_TRADING_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_Cfi_Bonus;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}

			}
			else if(parser.model=="CCalcCsdcInvestorStatDownload")
			{
				CCalcCsdcInvestorStatDownload * cse = (CCalcCsdcInvestorStatDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CSDC_INVESTOR_STAT_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_CSDC;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}

			}
			else if(parser.model=="CCalcCsdcSecurityIssueStatDownload")
			{
				CCalcCsdcSecurityIssueStatDownload * cse = (CCalcCsdcSecurityIssueStatDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_CSDC_SECURITY_ISSUE_STAT_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_CSDC;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);	

					delete cse;
				}

			}
			else if(parser.model=="CCalcSzseIndexDailyDownload")
			{
				CCalcSzseIndexDailyDownload * cse = (CCalcSzseIndexDailyDownload *)CCalculateTask::FetchTask(atol(parser.param1.c_str()));
				if(cse!=NULL)
				{
					CDownloadRequest * req1 = new CDownloadRequest;
					req1->m_nDownloadType = ID_DOWNLOAD_SZSE_INDEX_DAILY_SELECTED;
					req1->m_hwnd = NULL;
					req1->m_nLogType = WM_USER_LOG_2;
					req1->m_vecCode = cse->m_vec_code;
					((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req1);

					delete cse;
				}
			}
			
			sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);
		}

	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//	��С�������̴���

void CMainFrame::ToTray()
{ 
	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(NOTIFYICONDATA);
	nid.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nid.uID = IDR_MAINFRAME;
	nid.hWnd=m_hWnd;
	lstrcpy(nid.szTip,_T("A�ɷ���"));
	nid.uCallbackMessage= WM_NOTIFY_FROM_TRAY;
	nid.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD,&nid);
}

LRESULT CMainFrame::OnNotifyIcon(WPARAM wParam,LPARAM IParam)
{
	if ((IParam == WM_LBUTTONDOWN) || (IParam == WM_RBUTTONDOWN))
	{ 
		//ModifyStyleEx( WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
		ModifyStyleEx(0,WS_EX_TOPMOST);
		ShowWindow(SW_SHOW);
		this->UpdateWindow();
		//Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//��������ͼ��
	}
	return 0;
}

void CMainFrame::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage= WM_NOTIFY_FROM_TRAY;			//�Զ������Ϣ����
	nid.hIcon= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(nid.szTip,"A�ɷ���");				//��Ϣ��ʾ��Ϊ���ƻ��������ѡ�
	Shell_NotifyIcon(NIM_DELETE,&nid);			//��������ɾ��ͼ��
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch(nID)
	{
	case SC_MINIMIZE:
		ShowWindow(SW_HIDE);
		break;
	default:
		CMDIFrameWndEx::OnSysCommand(nID, lParam);
		break;
	}

}

void CMainFrame::OnDestroy()
{
	CMDIFrameWndEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	DeleteTray();
}



//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnSouhuPlate()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CBaseHtmlView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc(); //strCarMunber);
	CString title;
	title.Format("������-%s", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnAllStockList()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("���й�Ʊ�б�-%s", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}


void CMainFrame::OnAllStockDownload()
{
	// TODO: �ڴ���������������
	
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAutoDownloadView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CIndividualShareDoc * pNewDoc = new CIndividualShareDoc(); //strCarMunber);
	pNewDoc->m_nCommandCode = -1;
	pNewDoc->m_nCode = "-1";
	pNewDoc->m_vecCommandCode.clear();

	CString title;
	title.Format("��������-%s", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnZombieStockList()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CZombieStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("��ʬ��Ʊ����-%s", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMainProductQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMainProductQueryView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CSimpleInputBox dlg;
	dlg.m_strCaption = _T("������Ӫ��Ʒģ������");
	if(IDOK==dlg.DoModal() && dlg.m_strInput.IsEmpty()==false )
	{
		CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
		((CIndividualShareDoc *)pNewDoc)->m_strInput = dlg.m_strInput.GetBuffer();
		CString title;
		title.Format("��Ӫ��Ʒ��ѯ-%s",  dlg.m_strInput);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	

	}

	
}

void CMainFrame::OnPeStockList()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CPeStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CIndividualShareDoc * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	pNewDoc->m_strInput = "pe";
	CString title;
	title.Format("PE���� - 2012�꿪ʼ����");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	

}

void CMainFrame::OnMacdStockList()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMacdStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("MACD ��������");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnHexunResearchPaperQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CHexunResearchPaperListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("��Ѷ�б���ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMainIncomeYearGrowthQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllMainIncomeYearGrowthStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("��Ӫ����������������", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMainProfitYearGrowthQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllMainProfitYearGrowthStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("��Ӫ����������������", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnRecentBonusCashQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllRecentBonusCashStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("���ڷֺ���������", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnThisYearBonusPlanQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllThisYearBonusListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("����ֺ�Ԥ����ѯ", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMcstStockList()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllMcstStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("��Ʊ�ɱ��� MCST ����", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnAddIssuanceStockList()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CAllAddIssuanceListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("��Ʊ����ӯ������", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnNewmat11Test()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CNewmat11TestView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("Newmat11 ����", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMarketExchangeFundInSettlement()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMarketExchageFundView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("֤ȯ���׽����ʽ�", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMarketMarginGuaranteeFund()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMarketMarginGuaranteeFundView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("������ȯ�����ʽ�", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMarketCffexHs300Future()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMarketCffexHs300FutureView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("����300ָ������ָ�ڻ�", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMarketIndex()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMarketSohuIndexView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("����ָ��", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnMarketInvestorStat()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMarketCsdcInvestorStatView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("Ͷ�������ͳ��", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnStatsgovHgydMenu(UINT nID)
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CStatsGovMenuDlg dlg;
	if(nID==ID_STATSGOV_HGYD_MENU)		dlg.m_str_db_code = "hgyd";
	if(nID==ID_STATSGOV_HGJD_MENU)		dlg.m_str_db_code = "hgjd";
	if(nID==ID_STATSGOV_HGND_MENU)		dlg.m_str_db_code = "hgnd";
	if(nID==ID_STATSGOV_FSYD_MENU)		dlg.m_str_db_code = "fsyd";
	if(nID==ID_STATSGOV_FSJD_MENU)		dlg.m_str_db_code = "fsjd";
	if(nID==ID_STATSGOV_FSND_MENU)		dlg.m_str_db_code = "fsnd";
		
	if(IDOK==dlg.DoModal() && dlg.m_vec_zb_code.size() > 0)
	{
		if(dlg.m_nOutput==0)
		{
			CStatsGovCnGridView /*CStatsGovCnChartView*/	MonitorListView;
			pView = &MonitorListView;				
			pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);
		}
		else
		{
			CStatsGovCnChartView	MonitorListView;
			pView = &MonitorListView;				
			pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);
		}

		CDocument * pNewDoc = new CStatsGovCnDoc(); //strCarMunber);
		((CStatsGovCnDoc *)pNewDoc)->m_str_db_code = dlg.m_str_db_code;
		((CStatsGovCnDoc *)pNewDoc)->m_vec_zb_code = dlg.m_vec_zb_code;
		((CStatsGovCnDoc *)pNewDoc)->m_vec_reg_code = dlg.m_vec_reg_code;
		((CStatsGovCnDoc *)pNewDoc)->m_nOutput = dlg.m_nOutput;

		CString title;
		title.Format("���÷���",  "");
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	

	}

}


void CMainFrame::OnFinanceSalesFromOperations(UINT nID)
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;


	CStockGroupDlg dlg;
	if(IDOK==dlg.DoModal())
	{
		CStatsGovCnChartView	MonitorListView;
		pView = &MonitorListView;				
		pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		CStatsGovCnDoc * pNewDoc = new CStatsGovCnDoc(); //strCarMunber);


		if(nID==ID_FINANCE_SALES_FROM_OPERATIONS)		
		{
			pNewDoc->m_str_db_code = "incomestatement";
		}
		if(nID==ID_FINANCE_COST_OF_OPERATIONS)
		{
			pNewDoc->m_str_db_code = "incomestatement";
		}
	
		pNewDoc->m_vec_zb_code.clear();
		if(nID==ID_FINANCE_SALES_FROM_OPERATIONS)
			pNewDoc->m_vec_zb_code.push_back("colume_2");
		if(nID==ID_FINANCE_COST_OF_OPERATIONS)
			pNewDoc->m_vec_zb_code.push_back("colume_9");

		pNewDoc->m_vec_csrc_gate_code.clear();
		for(int i = 0 ; i<dlg.m_vecSelectedItemCsrcGate.size(); i++)
		{
			vector<string> firstMatch;
			string strPattern = string("\\([A-Za-z\\d]+\\)");
			if(Pcre2Grep(strPattern.c_str(), dlg.m_vecSelectedItemCsrcGate[i].c_str(), firstMatch )>0)
			{
				string::size_type pos1 = firstMatch[0].find(")");
				string codeStr = firstMatch[0].substr(1, pos1-1);
				pNewDoc->m_vec_csrc_gate_code.push_back(codeStr);
			}
		}
		
		pNewDoc->m_vec_csrc_big_code.clear();
		for(int i = 0 ; i<dlg.m_vecSelectedItemCsrcBig.size(); i++)
		{
			vector<string> firstMatch;
			string strPattern = string("\\([A-Za-z\\d]+\\)");
			if(Pcre2Grep(strPattern.c_str(), dlg.m_vecSelectedItemCsrcBig[i].c_str(), firstMatch )>0)
			{
				string::size_type pos1 = firstMatch[0].find(")");
				string codeStr = firstMatch[0].substr(1, pos1-1);
				pNewDoc->m_vec_csrc_big_code.push_back(codeStr);
			}
		}

		pNewDoc->m_vec_reg_code.clear();
		for(int i = 0 ; i<dlg.m_vecSelectedItemReg.size(); i++)
		{
			vector<string> firstMatch;
			string strPattern = string("\\([A-Za-z\\d]+\\)");
			if(Pcre2Grep(strPattern.c_str(), dlg.m_vecSelectedItemReg[i].c_str(), firstMatch )>0)
			{
				string::size_type pos1 = firstMatch[0].find(")");
				string codeStr = firstMatch[0].substr(1, pos1-1);
				pNewDoc->m_vec_reg_code.push_back(codeStr);
			}
		}

		CString title;
		title.Format("���÷���",  "");
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	

	}
}

void CMainFrame::OnCninfoAnnouncementQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCninfoAnnouncementListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("�޳��������ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}


void CMainFrame::OnPeGrossList()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CPeStockListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CIndividualShareDoc * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	pNewDoc->m_strInput = "pe_gross";
	CString title;
	title.Format("ë���� PE���� - 2012�꿪ʼ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	

}

void CMainFrame::OnCninfoPdfQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCninfoAnnouncePDFListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("�޳��� PDF ����");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnShanghaiIndex()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CShanghaiIndexView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("1", ID_SHANGHAI_INDEX); //strCarMunber);
	CString title;
	title.Format("��ָ֤��");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnCninfoIncentivePlanQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCninfoIncentivePlanListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("�޳�����Ȩ������ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnHushenChangeRateQuery()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CPlateShanghaiIndexView	 MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);
	CIndividualShareDoc * pNewDoc = new CIndividualShareDoc("", 1, 1); //strCarMunber);

	/*���й�Ʊ�ĸſ��б�*/
	CEntrepreneurship Entrepreneurship ;
	CBussinessUtils::GetEntrepreneurship(Entrepreneurship);
	for(int i=0; i< Entrepreneurship.m_nRowNum; i++)
	{
		pNewDoc->m_vec_request_code.push_back(Int2String(Entrepreneurship.m_vec_code[i], "%06d"));
	}

	CSmallMidEnterprise midsmall ;
	CBussinessUtils::GetSmallMidEnterprise(midsmall);
	for(int i=0; i< midsmall.m_nRowNum; i++)
	{
		pNewDoc->m_vec_request_code.push_back(Int2String(midsmall.m_vec_code[i], "%06d"));
	}

	CShenzhenAshares shenzhenA ;
	CBussinessUtils::GetShenzhenAshares(shenzhenA);
	for(int i=0; i< shenzhenA.m_nRowNum; i++)
	{
		pNewDoc->m_vec_request_code.push_back(Int2String(shenzhenA.m_vec_code[i], "%06d"));
	}

	CShanghaiStockInfo shanghai ;
	CBussinessUtils::GetShanghaiStockInfo(shanghai);
	for(int i=0; i< shanghai.m_nRowNum; i++)
	{
		pNewDoc->m_vec_request_code.push_back(Int2String(shanghai.m_vec_code[i], "%06d"));
	}

	pNewDoc->m_nIs_Stock = 1;
	pNewDoc->m_strInput = "Table";
	CString title;
	title.Format("��������ǵ���ѯ-%s", "");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnSmallMiddleIndex()
{

	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CShanghaiIndexView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("399101", ID_SMALL_MIDDLE_INDEX); //strCarMunber);
	CString title;
	title.Format("��С����ָ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnCninfoGetPlanQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCninfoGetLandListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("�޳����������ز�ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnEnterprenuerIndex()
{
	// TODO: �ڴ���������������
	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CShanghaiIndexView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("399102", ID_ENTERPRENUER_INDEX); //strCarMunber);
	CString title;
	title.Format("��ҵ����ָ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnCninfoShareHoldingQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCninfoShareHoldingListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("ǰ10���ɶ��ֹɲ�ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnCninfoShareHoldingStatistics()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCninfoShareHoldingStatisticsView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("ǰ10���ɶ��ֹ�ͳ��");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);	
}

void CMainFrame::OnCandlesticksJapanQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CCandlesticksJapanListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("����ͼ��ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);
}

void CMainFrame::OnMacdQuery()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CMacdListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("MACD��ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);
}

void CMainFrame::OnBollQuery()
{
	// TODO: �ڴ���������������


	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	CBollListView	MonitorListView;

	pView = &MonitorListView;				
	pDocTemplate = ((CStockApp *)AfxGetApp())->GetCurrDocTemplate(pView);

	pView = NULL;
	ASSERT_VALID(pDocTemplate);

	CDocument * pNewDoc = new CIndividualShareDoc("-1", ID_ALL_STOCK_LIST); //strCarMunber);
	CString title;
	title.Format("BOLL��ѯ");
	pNewDoc->SetTitle(title);
	CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
	wnd->ShowWindow(SW_SHOWMAXIMIZED);
	pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
	pDocTemplate->AddDocument(pNewDoc);
}

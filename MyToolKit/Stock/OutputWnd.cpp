
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ����ѡ�����:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ������ѡ�����\n");
		return -1;      // δ�ܴ���
	}

	// �����������:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL /*| LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS*/;

	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputTradingDaily.Create(dwStyle, rectDummy, &m_wndTabs, 4) || 
		!m_wndOutputFinanceReport.Create(dwStyle, rectDummy, &m_wndTabs, 5) ||
		!m_wndOutputCapitalFlow163.Create(dwStyle, rectDummy, &m_wndTabs, 6) ||
		!m_wndOutputForecast.Create(dwStyle, rectDummy, &m_wndTabs, 7)||
		!m_wndOutputCapitalStruct.Create(dwStyle, rectDummy, &m_wndTabs, 8)||
		!m_wndOutputResearchPaper.Create(dwStyle, rectDummy, &m_wndTabs, 9)||
		!m_wndOutputIncomeComposition.Create(dwStyle, rectDummy, &m_wndTabs, 10)||
		!m_wndOutputCfiBonus.Create(dwStyle, rectDummy, &m_wndTabs, 11)||
		!m_wndOutputCninfo.Create(dwStyle, rectDummy, &m_wndTabs, 12)||
		!m_wndOutputStatsGovCn.Create(dwStyle, rectDummy, &m_wndTabs, 13) ||
		!m_wndOutputCSDC.Create(dwStyle, rectDummy, &m_wndTabs, 14))
	{
		TRACE0("δ�ܴ����������\n");
		return -1;      // δ�ܴ���
	}

	m_wndOutputBuild.SetFont(&m_Font);
	m_wndOutputDebug.SetFont(&m_Font);
	m_wndOutputTradingDaily.SetFont(&m_Font);
	m_wndOutputFinanceReport.SetFont(&m_Font);
	m_wndOutputCapitalFlow163.SetFont(&m_Font);
	m_wndOutputForecast.SetFont(&m_Font);
	m_wndOutputCapitalStruct.SetFont(&m_Font);
	m_wndOutputResearchPaper.SetFont(&m_Font);
	m_wndOutputIncomeComposition.SetFont(&m_Font);
	m_wndOutputCfiBonus.SetFont(&m_Font);
	m_wndOutputCninfo.SetFont(&m_Font);
	m_wndOutputStatsGovCn.SetFont(&m_Font);
	m_wndOutputCSDC.SetFont(&m_Font);

	CString strTabName;
	BOOL bNameValid;

	// ���б��ڸ��ӵ�ѡ�:
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	strTabName = _T("ÿ����֤��ӯ�ʵ�");
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	strTabName = _T("ÿ�ս�������");
	m_wndTabs.AddTab(&m_wndOutputTradingDaily, strTabName, (UINT)2);

	strTabName = _T("���񱨱�");
	m_wndTabs.AddTab(&m_wndOutputFinanceReport, strTabName, (UINT)3);
	strTabName = _T("ÿ���ʽ�����");
	m_wndTabs.AddTab(&m_wndOutputCapitalFlow163, strTabName, (UINT)4);
	strTabName = _T("ҵ��Ԥ��");
	m_wndTabs.AddTab(&m_wndOutputForecast, strTabName, (UINT)5);
	strTabName = _T("ͬ��˳�ɱ����ֺ�");
	m_wndTabs.AddTab(&m_wndOutputCapitalStruct, strTabName, (UINT)6);
	strTabName = _T("��Ѷ�б�");
	m_wndTabs.AddTab(&m_wndOutputResearchPaper, strTabName, (UINT)7);
	strTabName = _T("�Ѻ���Ӫҵ�񹹳�");
	m_wndTabs.AddTab(&m_wndOutputIncomeComposition, strTabName, (UINT)8);

	strTabName = _T("�޳����������");
	m_wndTabs.AddTab(&m_wndOutputCfiBonus, strTabName, (UINT)9);

	strTabName = _T("�޳���");
	m_wndTabs.AddTab(&m_wndOutputCninfo, strTabName, (UINT)10);
	strTabName = _T("����ͳ�ƾ�");
	m_wndTabs.AddTab(&m_wndOutputStatsGovCn, strTabName, (UINT)11);

	strTabName = _T("�й�����");
	m_wndTabs.AddTab(&m_wndOutputCSDC, strTabName, (UINT)12);

	// ʹ��һЩ�����ı���д���ѡ�(���踴������)
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// ѡ��ؼ�Ӧ��������������:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&m_Font);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::FillBuildWindow()
{
	/*m_wndOutputBuild.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputBuild.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputBuild.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));*/
}

void COutputWnd::FillDebugWindow()
{
	m_wndOutputDebug.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputDebug.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputDebug.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
}

void COutputWnd::FillFindWindow()
{
	m_wndOutputTradingDaily.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputTradingDaily.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputTradingDaily.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
}

void COutputWnd::AppendLog(LPCTSTR lpszItem, int logLevel)
{
	if(logLevel==WM_USER_LOG_1)
	{
		/*�ճ�������־*/
		//m_wndOutputBuild.AppendString(lpszItem, RGB(128, 0, 0), RGB( 255,255,255));
		m_wndOutputBuild.AddString(lpszItem);
		m_wndOutputBuild.SetTopIndex(m_wndOutputBuild.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_2)
	{
		/*��̨������־*/
		if(m_wndOutputDebug.GetCount()>100)		m_wndOutputDebug.ResetContent();
		m_wndOutputDebug.AddString(lpszItem);
		m_wndOutputDebug.SetTopIndex(m_wndOutputDebug.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_3)
	{
		/*��̨ÿ����������*/
		if(m_wndOutputTradingDaily.GetCount()>100)		m_wndOutputTradingDaily.ResetContent();

		m_wndOutputTradingDaily.AddString(lpszItem);
		m_wndOutputTradingDaily.SetTopIndex(m_wndOutputTradingDaily.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_FinanceReport)
	{
		/*��̨���񱨱�����*/
		if(m_wndOutputFinanceReport.GetCount()>100)		m_wndOutputFinanceReport.ResetContent();

		m_wndOutputFinanceReport.AddString(lpszItem);
		m_wndOutputFinanceReport.SetTopIndex(m_wndOutputFinanceReport.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_CapitalFlow163)
	{
		/*��̨ÿ���ʽ���������*/
		if(m_wndOutputCapitalFlow163.GetCount()>100)		m_wndOutputCapitalFlow163.ResetContent();

		m_wndOutputCapitalFlow163.AddString(lpszItem);
		m_wndOutputCapitalFlow163.SetTopIndex(m_wndOutputCapitalFlow163.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_Forecast)
	{
		/*��̨ҵ��Ԥ������*/
		if(m_wndOutputForecast.GetCount()>100)		m_wndOutputForecast.ResetContent();

		m_wndOutputForecast.AddString(lpszItem);
		m_wndOutputForecast.SetTopIndex(m_wndOutputForecast.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_CapitalStruct)
	{
		/*��̨ͬ��˳�ɱ��ṹ����*/
		if(m_wndOutputCapitalStruct.GetCount()>100)		m_wndOutputCapitalStruct.ResetContent();

		m_wndOutputCapitalStruct.AddString(lpszItem);
		m_wndOutputCapitalStruct.SetTopIndex(m_wndOutputCapitalStruct.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_ResearchPaper)
	{
		/*��̨��Ѷ�б�����*/
		if(m_wndOutputResearchPaper.GetCount()>100)		m_wndOutputResearchPaper.ResetContent();

		m_wndOutputResearchPaper.AddString(lpszItem);
		m_wndOutputResearchPaper.SetTopIndex(m_wndOutputResearchPaper.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_Income_Composition)
	{
		/*��̨�Ѻ���Ӫҵ�񹹳�����*/
		if(m_wndOutputIncomeComposition.GetCount()>100)		m_wndOutputIncomeComposition.ResetContent();

		m_wndOutputIncomeComposition.AddString(lpszItem);
		m_wndOutputIncomeComposition.SetTopIndex(m_wndOutputIncomeComposition.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_Cfi_Bonus)
	{
		/*��̨�в����ֺ���������*/
		/*��̨�й�Ͷ���߱��������ÿ����֤���׽�����*/
		/*��̨������ȯ����*/
		if(m_wndOutputCfiBonus.GetCount()>100)		m_wndOutputCfiBonus.ResetContent();

		m_wndOutputCfiBonus.AddString(lpszItem);
		m_wndOutputCfiBonus.SetTopIndex(m_wndOutputCfiBonus.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_Cninfo)
	{
		/*��̨�޳�����������*/
		if(m_wndOutputCninfo.GetCount()>100)		m_wndOutputCninfo.ResetContent();

		m_wndOutputCninfo.AddString(lpszItem);
		m_wndOutputCninfo.SetTopIndex(m_wndOutputCninfo.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_StatsGovCn)
	{
		/*��̨����ͳ�ƾ�����*/
		if(m_wndOutputStatsGovCn.GetCount()>100)		m_wndOutputStatsGovCn.ResetContent();

		m_wndOutputStatsGovCn.AddString(lpszItem);
		m_wndOutputStatsGovCn.SetTopIndex(m_wndOutputStatsGovCn.GetCount()-1);
	}
	else if(logLevel==WM_USER_LOG_CSDC)
	{
		/*��̨�й�������������*/
		if(m_wndOutputCSDC.GetCount()>100)		m_wndOutputCSDC.ResetContent();

		m_wndOutputCSDC.AddString(lpszItem);
		m_wndOutputCSDC.SetTopIndex(m_wndOutputCSDC.GetCount()-1);
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList ��Ϣ�������

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}

void COutputList::OnEditCopy()
{
	MessageBox(_T("�������"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("������"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}



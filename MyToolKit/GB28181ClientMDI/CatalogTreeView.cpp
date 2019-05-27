// CatalogTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GB28181ClientMDI.h"
#include "GB28181ClientMDIDoc.h"
#include "CatalogTreeView.h"

#include "PlaybackView.h"

#include "RealplayView.h"

class CCatalogTreeViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CCatalogTreeViewMenuButton)

public:
	CCatalogTreeViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
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

IMPLEMENT_SERIAL(CCatalogTreeViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////////
// CCatalogTreeView

IMPLEMENT_DYNAMIC(CCatalogTreeView, CDockablePane)

CCatalogTreeView::CCatalogTreeView()
{

}

CCatalogTreeView::~CCatalogTreeView()
{
}


BEGIN_MESSAGE_MAP(CCatalogTreeView, CDockablePane)
	ON_MESSAGE(WM_USER_CATALOG_COMM, OnUserCatalogComm)
	ON_MESSAGE(WM_USER_CATALOG_DATA, OnUserCatalogData)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_REALPLAY, &CCatalogTreeView::OnRealplay)
	ON_COMMAND(ID_PROPERTIES, &CCatalogTreeView::OnProperties)
	ON_COMMAND(ID_PLAYBACK, &CCatalogTreeView::OnPlayback)
	ON_COMMAND(ID_Alarm_Subscribe, &CCatalogTreeView::OnAlarmSubscribe)
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CCatalogTreeView ��Ϣ�������



int CCatalogTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
		return -1;      // δ�ܴ���
	}


	// ����ͼ��:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	//OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_CHANNEL);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CCatalogTreeViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CCatalogTreeViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CCatalogTreeViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		// pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	FillClassView();
	AdjustLayout();

	return 0;
}

void CCatalogTreeView::AdjustLayout()
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

void CCatalogTreeView::FillClassView()
{
	
}

void CCatalogTreeView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDockablePane::OnPaint()
}

void CCatalogTreeView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AdjustLayout();
}

void CCatalogTreeView::OnContextMenu(CWnd* pWnd, CPoint point)
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
	menu.LoadMenu(IDR_POPUP_CHANNEL);

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

void CCatalogTreeView::OnRealplay()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		/*vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());*/

		CRealplayView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CGB28181ClientMDIApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CGB28181ClientMDIDoc(text.GetBuffer()); //strCarMunber);
		CString title;
		title.Format("Ԥ��-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CCatalogTreeView::CleanupTree()
{
	map<string, HTREEITEM>::iterator it = m_mapTree.begin();
	for(; it!=m_mapTree.end(); it++)
	{
		sipd_catalog_item * pItem = (sipd_catalog_item *)m_wndClassView.GetItemData(it->second);
		if(pItem)
		{
			int nLen = strlen(pItem->device_id);
			if(nLen < 12)
			{
				int kk = 1;
			}
			delete pItem;
		}
	}
	m_mapTree.clear();
	m_wndClassView.DeleteAllItems();
}

void CCatalogTreeView::OnProperties()
{
	// TODO: �ڴ���������������

	// AfxMessageBox("OK");

	//	������еĽڵ㣬�ͷŽڵ��а���������
	CleanupTree();

	sipd_catalog_req  catalog;
	memset(&catalog, 0, sizeof(sipd_catalog_req));
	stringstream ss;
	ss << "sip:" << LOCAL_DOMAIN_ID << "@" << LOCAL_IP << ":" << LOCAL_PORT; 
	strncpy(catalog.from_uri, ss.str().c_str(), MAX_SIPD_URI);

	ss.str("");
	ss << "sip:" << REMOTE_DOMAIN_ID << "@" << REMOTE_IP << ":" << REMOTE_PORT; 
	strncpy(catalog.to_uri, ss.str().c_str(), MAX_SIPD_URI);
	/*34020000002020000002   35000100491327000000  35000100491187000006  35000100491187000193  */
	strncpy(catalog.device_id, REMOTE_DOMAIN_ID, MAX_SIPD_DEVICE_ID_LEN);    

	

	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("Ŀ¼��111"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	m_mapTree["00"] = hRoot;

	sipd_catalog_item* pItem = new sipd_catalog_item;
	memset(pItem, 0, sizeof(sipd_catalog_item));
	sprintf_s(pItem->device_id ,"31111111");
	sprintf_s(pItem->Name ,"31111111");
	sprintf_s(pItem->CivilCode ,"31111111");
	sprintf_s(pItem->ParentID ,"31111111");
	m_wndClassView.SetItemData(hRoot, (DWORD_PTR)pItem);

	int net_port = Dll_cataloginfo_request(&catalog);

	if(net_port>=0)
	{
		m_vec_net_port.push_back(net_port);

		JMutexAutoLock lock(g_mtxNet);
		g_mapNet2Hwnd[net_port] = GetSafeHwnd();
	}
}

LRESULT CCatalogTreeView::OnUserCatalogComm(WPARAM wParam, LPARAM lParam)
{
	
	return 0;
}

LRESULT CCatalogTreeView::OnUserCatalogData(WPARAM wParam, LPARAM lParam)
{
	sipd_catalog_rsp_basic_info* pCataBasicInfo = (sipd_catalog_rsp_basic_info *)wParam;
	sipd_catalog_item* pCataItem = (sipd_catalog_item *)lParam;

	// 
	for(int i=0; i< pCataBasicInfo->DeviceList_Num; i++)
	{
		//	���Ҹ��ڵ�
		HTREEITEM hParent= m_mapTree["00"];
		string strParentId = pCataItem[i].ParentID;
		if(m_mapTree.count(strParentId)>0)
		{
			hParent = m_mapTree[strParentId];
		}

		string  strDeviceId = pCataItem[i].device_id;
		if(m_mapTree.count(strDeviceId)==0)
		{
			HTREEITEM hSrc = m_wndClassView.InsertItem(strDeviceId.c_str(), 0, 0, hParent);
			m_mapTree[strDeviceId] = hSrc;

			//	��ÿ��Ŀ¼���Ϊ ���ڵ�
			sipd_catalog_item* pItem = new sipd_catalog_item;
			memcpy(pItem, pCataItem + i, sizeof(sipd_catalog_item));
			m_wndClassView.SetItemData(hSrc, (DWORD_PTR)pItem);
		}
		
	}
	
	if(pCataBasicInfo)
		delete pCataBasicInfo;
	if(pCataItem)
		delete[] pCataItem;

	return 0;
}
void CCatalogTreeView::OnPlayback()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		/*vector<string> firstMatch;
		string strPattern = string("\\([A-Za-z\\d]+\\)");
		if(Pcre2Grep(strPattern.c_str(), text.GetBuffer(),firstMatch )<=0)
		{
			AfxMessageBox("��ȡ�������");		
			return ;
		}

		string::size_type pos1 = firstMatch[0].find(")");
		string codeStr = firstMatch[0].substr(1, pos1-1);
		int code = atoi(codeStr.c_str());*/

		CPlaybackView	MonitorListView;

		pView = &MonitorListView;				
		pDocTemplate = ((CGB28181ClientMDIApp *)AfxGetApp())->GetCurrDocTemplate(pView);

		pView = NULL;
		ASSERT_VALID(pDocTemplate);
		CDocument * pNewDoc = new CGB28181ClientMDIDoc(text.GetBuffer()); //strCarMunber);
		CString title;
		title.Format("�ط�-%s", text);
		pNewDoc->SetTitle(title);
		CFrameWnd * wnd= pDocTemplate->CreateNewFrame(pNewDoc,NULL);//create view
		wnd->ShowWindow(SW_SHOWMAXIMIZED);
		pDocTemplate->InitialUpdateFrame(wnd,pNewDoc,TRUE);
		pDocTemplate->AddDocument(pNewDoc);	
	}
}

void CCatalogTreeView::OnAlarmSubscribe()
{
	// TODO: �ڴ���������������

	CDocTemplate * pDocTemplate = NULL;
	CView * pView = NULL;

	HTREEITEM hTreeItem = m_wndClassView.GetSelectedItem();
	if (hTreeItem != NULL)
	{
		CString text = m_wndClassView.GetItemText(hTreeItem);
		//AfxMessageBox(text);

		text.Format("35000100491347000191");

		sipd_alarm_req alarmReq;
		memset(&alarmReq, 0, sizeof(sipd_alarm_req));

		stringstream ss;
		ss << "sip:" << LOCAL_DOMAIN_ID << "@" << LOCAL_IP << ":" << LOCAL_PORT; 
		strncpy(alarmReq.from_uri, ss.str().c_str(), MAX_SIPD_URI);

		ss.str("");
		ss << "sip:" << string(text.GetBuffer()) << "@" << REMOTE_IP << ":" << REMOTE_PORT;
		strncpy(alarmReq.to_uri, ss.str().c_str(), MAX_SIPD_URI);

		strncpy(alarmReq.device_id, text.GetBuffer(), MAX_SIPD_DEVICE_ID_LEN);

		alarmReq.AlarmMethod = sipd_alarm_condition_all;
		alarmReq.StartAlarmPriority = 0;
		alarmReq.EndAlarmPriority  = 4;
		strncpy(alarmReq.StartTime, "2017-09-11T01:05:09", MAX_SIPD_TIME_LEN);
		strncpy(alarmReq.EndTime, "2017-12-11T23:05:09", MAX_SIPD_TIME_LEN);

		int ret = Dll_alarm_subscribe_request(&alarmReq);

		if(ret>=0)
		{
			//	�յ��Ļظ� ���͵� �ָ��е�С����
			JMutexAutoLock lock(g_mtxNet);
			g_mapNet2Hwnd[ret] =  GetSafeHwnd();
		}
	}
}

void CCatalogTreeView::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	CleanupTree();

}

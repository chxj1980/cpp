// PlayWnd.cpp : implementation file
//

#include "stdafx.h"
#include "GB28181ClientMDI.h"
#include "PlaybackWnd.h"
#include "PlaybackPannel.h"
#include "PlaybackView.h"

//#include "NetVidiconRealPlayerPropPage.h"
#define NAME_MENU_FULLSCREEN				"ȫ����ʾ"
#define NAME_MENU_MULTISCREEN				"������ʾ"
#define NAME_MENU_AUTOADJUST				"�Զ�����"
#define NAME_MENU_CLOSESOUND                "�ر���Ƶ"
#define NAME_MENU_OPENSOUND                 "����Ƶ"
#define NAME_MENU_CLOSEVIDEO                "�ر���Ƶ"
#define NAME_MENU_CAPTUREPIC                "ץ    ͼ"
#define NAME_MENU_RECORDVIDEO               "¼    ��"
#define NAME_MENU_ZPOOMDVIDEO               "����Ŵ�"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// extern HWND g_PlayBackPropPageHwnd;     //��ǰ����ڵľ��
/////////////////////////////////////////////////////////////////////////////
// CPlaybackWnd dialog


CPlaybackWnd::CPlaybackWnd()
	:m_nWndID(0)
{
	m_nPreSplit = 0;
    m_bMouseMove=FALSE;	//����ƶ�
	g_bZoom=FALSE;
	m_bPlaying=FALSE;
	m_bZoomView=FALSE;
	m_GetPicFlag=FALSE;  //Ĭ��Ϊ��ȡͼ���С
	m_dragsum=0;
	m_width=0;
	m_height=0;
	memset(&g_rcLast,0x00,sizeof(g_rcLast));

	m_strToolTip = " ";
	m_bActivateToolTip = FALSE;

	m_play_port = -1;
	m_net_port = -1;

	bOnebyone = FALSE;
	m_bPause = FALSE;

	//{{AFX_DATA_INIT(CPlaybackWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CPlaybackWnd, CWnd)
	//{{AFX_MSG_MAP(CPlaybackWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(VIDEO_MENU_BASE, VIDEO_MENU_END, OnVideoMenu)
	ON_MESSAGE(WM_USER_RECORDFILE_COMM, OnUserRecordFileComm)
	ON_MESSAGE(WM_USER_RECORDFILE_DATA, OnUserRecordFileData)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int CPlaybackWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTooltipText(m_strToolTip);
	return 0;
}
BOOL CPlaybackWnd::PreTranslateMessage(MSG* pMsg) 
{
	if ( pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST )
	{
		if(m_ToolTipWnd.GetSafeHwnd() != NULL)
		{
			//m_ToolTipWnd.RelayEvent(pMsg);
		}		
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CPlaybackWnd::OnPaint()
{
	CPaintDC dc(this);
	DebugTrace("OnPaint ---- playback.ocx -- CPlaybackWnd");
}

void CPlaybackWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_bMouseMove && m_ToolTipWnd.GetSafeHwnd() != NULL)
	{
		//MSG msg; 
		//msg.hwnd = GetSafeHwnd(); 
		//msg.message = WM_MOUSEMOVE; 
		//msg.wParam = WPARAM(nFlags); 
		//msg.time = 0; 
		//msg.pt.x = point.x; 
		//msg.pt.y = point.y; 
		//msg.lParam = MAKELPARAM(LOWORD(point.x), LOWORD(point.y)); 

		//m_ToolTipWnd.RelayEvent(&msg);

		CString strText = _T("");
		strText.Format(_T("����%d %s"),m_nWndID+1,m_strToolTip);
		m_ToolTipWnd.UpdateTipText( (LPCTSTR)strText, this);
		m_ToolTipWnd.Update();
		//m_ToolTipWnd.Pop();
		//m_ToolTipWnd.Popup();
	}

//	CWnd *pWnd;
//	pWnd=GetParent();
//	pWnd->SendMessage(WM_MOUSEMOVE);
	if(m_bMouseMove && m_bZoomView)
	{
		//CString m_str,m_str2;
		CClientDC dc(this); 
		//m_str.Format(L"M����λ���� %d,%d",point.x,point.y);//�����������ʽ�����ַ����С� 
		//m_str2.Format(L"B����λ���� %d,%d",g_rcLast.left,g_rcLast.top);//�����������ʽ�����ַ����С�
		//dc.TextOut(0,0,m_str); 
		//dc.TextOut(0,10,m_str2);
		RECT rect;
		rect.left=g_rcLast.left;
		rect.top=g_rcLast.top;
		rect.right=point.x;
		rect.bottom=point.y;
		//����
		//InvertShape(&dc,rect,true);		
		//�ػ�
		//InvertShape(&dc,rect,false);		
		
		//dc.Rectangle(&rect);
		CPen   pen(PS_SOLID |PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, RGB(0,0,255)); 
		dc.SelectObject(&pen); 
		LOGBRUSH   lb; 
		lb.lbStyle   =   BS_HOLLOW; 
		CBrush   brush; 
		brush.CreateBrushIndirect(&lb); 
		dc.SelectObject(&brush); 
		dc.Rectangle(&rect);
		g_rcLast.right=point.x;
		g_rcLast.bottom=point.y;
	}
	// Do not call CWnd::OnPaint() for painting messages
	CWnd::OnMouseMove(nFlags,point);
}

void CPlaybackWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bZoomView)
	{
		m_bMouseMove=TRUE;
		g_rcLast.left=point.x;
		g_rcLast.top=point.y;
	}

	CWnd::OnLButtonDown(nFlags,point);
}

void CPlaybackWnd::OnLButtonUp(UINT nFlags, CPoint point)
{	
	int t_width,t_height;
	//DebugTrace("m_bMouseMove=%d && m_bZoomView=%d",m_bMouseMove , m_bZoomView);
	if(m_bMouseMove && m_bZoomView)
	{		
		
	}	
	// Do not call CWnd::OnPaint() for painting messages
	CWnd::OnLButtonUp(nFlags,point);
}
/////////////////////////////////////////////////////////////////////////////
// CPlaybackWnd message handlers
BOOL CPlaybackWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rt;
	GetClientRect(&rt);
	CBrush br;
	br.CreateSolidBrush(VIDEO_BACK_COLOR);
	pDC->FillRect(&rt,&br);
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

LRESULT CPlaybackWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	CPlaybackPannel *pContainer = (CPlaybackPannel *)GetParent();
	if(pContainer)
	{
		switch(message)
		{
		case WM_MOUSEMOVE:
			{
				//if(m_bMouseMove)
				//   pContainer->SetZoomRect(g_rcLast); //���������ˣ������ƺ��ٷų�
			}
			break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			{
				::SendMessage(pContainer->GetParent()->GetSafeHwnd(), WM_EVENT_SEL_WND, m_nWndID, NULL);	
			}
			break;
		case WM_LBUTTONDBLCLK:
			{
				BOOL bMulti = pContainer->GetMultiScreen();
				pContainer->SetMultiScreen(!bMulti);
				::SendMessage(pContainer->GetParent()->GetSafeHwnd(), WM_EVENT_SEL_WND, m_nWndID, NULL);	
			}
			break;
		default:
			break;
		}
	}
	return CWnd::DefWindowProc(message, wParam, lParam);
}

void CPlaybackWnd::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CPlaybackPannel *pContainer = (CPlaybackPannel *)GetParent();
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING | pContainer->GetFullScreen()    ? MF_CHECKED   : MF_UNCHECKED, VIDEO_MENU_FULLSCREEN,    NAME_MENU_FULLSCREEN);
	menu.AppendMenu(MF_STRING | pContainer->GetMultiScreen()   ? MF_CHECKED   : MF_UNCHECKED, VIDEO_MENU_MULTISCREEN,   NAME_MENU_MULTISCREEN);
	menu.AppendMenu(MF_STRING | pContainer->GetAutoAdjustPos() ? MF_CHECKED   : MF_UNCHECKED, VIDEO_MENU_AUTOADJUST,    NAME_MENU_AUTOADJUST);

	TrackPopupMenu( 
		menu.m_hMenu, 
		TPM_LEFTALIGN, 
		point.x, 
		point.y,
		0,
		m_hWnd,
		NULL);
}

void CPlaybackWnd::OnVideoMenu(UINT nID)
{
	CPlaybackPannel *pContainer = (CPlaybackPannel *)GetParent();
	switch(nID)
	{
	case VIDEO_MENU_FULLSCREEN:
		pContainer->SetFullScreen(!pContainer->GetFullScreen());
		break;
	case VIDEO_MENU_MULTISCREEN:
		{
			BOOL bMulti = pContainer->GetMultiScreen();
			pContainer->SetMultiScreen(!bMulti);
			break;
		}		
	case VIDEO_MENU_AUTOADJUST:
		pContainer->SetAutoAdjustPos(!pContainer->GetAutoAdjustPos());
		break;
	case VIDEO_MENU_PRINTSCREEN:
		break;
	case VIDEO_MENU_RECORDVIDEO:
		break;
	case VIDEO_MENU_EXITDECODE:
		break;
	case VIDEO_MENU_CAPTUREPIC:
		break;
	case VIDEO_MENU_TRECORDVIDEO:
		break;
	case VIDEO_MENU_ZOOMVIEW:
		break;
	default:
		break;
	}
}

BOOL CPlaybackWnd::DestroyWindow() 
{
	return CWnd::DestroyWindow();

}
void CPlaybackWnd::ReSetPenBrush(CDC *pDC)
{	
	m_pBrushOld=(CBrush *)pDC->SelectObject(m_pBrushOld);
	m_pBrushOld=NULL;
}

void CPlaybackWnd::SetPenBrush(CDC *pDC,bool bTransparent)
{
	ASSERT(pDC != NULL);
	
	if(bTransparent)
		m_pBrushOld=(CBrush *)pDC->SelectStockObject(NULL_BRUSH);
	else
		m_pBrushOld=(CBrush *)pDC->SelectStockObject(WHITE_BRUSH);
}

void CPlaybackWnd::InvertShape(CDC *pDC,RECT rect, bool bInvert)
{
	ASSERT(pDC!=NULL);
	bool m_bTransparent=TRUE;
	int nModeOld;
	if(bInvert)//true---����
	{
		nModeOld = pDC->SetROP2(R2_NOT);
	}
	//Invalidate();
	SetPenBrush(pDC,m_bTransparent);
	
	pDC->Rectangle(&rect);

	if(bInvert)
	{
		pDC->SetROP2(nModeOld);
	}
	ReSetPenBrush(pDC);
}


void CPlaybackWnd::InitToolTip()
{
	if(m_ToolTipWnd.GetSafeHwnd() != NULL)
	{
		return;
	}
	EnableToolTips(TRUE);
	m_ToolTipWnd.Create(this);
	m_ToolTipWnd.Activate(TRUE);
	m_ToolTipWnd.AddTool(this, LPSTR_TEXTCALLBACK);
	m_ToolTipWnd.SetDelayTime(100);	
}

void CPlaybackWnd::SetTooltipText(CString strText)
{
	InitToolTip();

	m_strToolTip = strText;
}


LRESULT CPlaybackWnd::OnUserRecordFileComm(WPARAM wParam, LPARAM lParam)
{

	return 0;
}

LRESULT CPlaybackWnd::OnUserRecordFileData(WPARAM wParam, LPARAM lParam)
{
	CPlaybackView * pView = NULL;
	CPlaybackPannel *pContainer = (CPlaybackPannel *)GetParent();
	if(pContainer)
		pView = (CPlaybackView *)pContainer->GetParent();

	sipd_recordinfo_rsp_basic_info* pBasicInfo = (sipd_recordinfo_rsp_basic_info *)wParam;
	sipd_file_item* pItem = (sipd_file_item *)lParam;

	if(pView)
	{
		//	��ʱ������չʾ
		RETSEARCH * rs = new RETSEARCH[pBasicInfo->RecordListNum];

		for(int i=0; i< pBasicInfo->RecordListNum; i++)
		{
			memset(&rs[i], 0, sizeof(RETSEARCH));
			sprintf_s(rs[i].createtime, pItem[i].StartTime);
			sprintf_s(rs[i].finishtime, pItem[i].EndTime);

			m_listFiles.push_back(rs[i]);
		}
		pView->m_CtrlPlayTime.AddWndData(m_nWndID, 2017, 9, 11, rs, pBasicInfo->RecordListNum );
		delete[] rs;
	}
	

	if(pBasicInfo)
		delete pBasicInfo;
	if(pItem)
		delete[] pItem;

	return 0;
}



void CPlaybackWnd::OnPlay() 
{
	if(m_listFiles.size()==0)
	{
		// g_pPlayBackCtrl->ShowHyperLinkDlg("���Ų���","δ�ҵ���صĲ�����Ϣ",FALSE);
		AfxMessageBox(_T("δ�ҵ���صĲ�����Ϣ"));
		return;
	}

	// ԭ�����ǲ���״̬,����.
	if(m_net_port< 0  || m_play_port < 0)
	{
		// ������Ű�ť���Ǵӵ�һ��ʱ��㿪ʼ����.

		StartPlay();
	}
	//	��ͣ �� ��֡ ������ ����״̬
	else if(m_bPause)
	{
		//	��ͣ����ȡ�����ָ�����.	
		//it->second.nSpeed = 4;
		
		sipd_playback_mans_rtsp_ind rtspDesc={0};

		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 2\r\nScale: 1.0\r\nRange: npt=3.141593-\r\n");
		rtspDesc.len = strlen(rtspDesc.rtsp_des);
		int iCmdId = Dll_Call_media_control(m_net_port, SIPD_TO_CMS_CMD_TYPE_PLAYBACK_CONTROL_RTSP,&rtspDesc);

		m_bPause = FALSE;
	}
	else if(bOnebyone)
	{	
		// ��֡->��������.
		//PlayNormFromOnebyOne(it->second);
		// ���ٶȵ��������ٶ�
		// 2012-5-22
		nSpeed = 4;
		//PlayNormFormSpeed(it->second);
	}
}



void CPlaybackWnd::OnStop() 
{
	StopPlay();
	
}

void CPlaybackWnd::OnPause()
{
	if(m_play_port>=0 && m_net_port>=0)
	{
		sipd_playback_mans_rtsp_ind rtspDesc={0};

		sprintf(rtspDesc.rtsp_des,"PAUSE RTSP/1.0\r\nCSeq: 1\r\nPauseTime: %d\r\n",0);
		rtspDesc.len = strlen(rtspDesc.rtsp_des);
		int iCmdId = Dll_Call_media_control(m_net_port, SIPD_TO_CMS_CMD_TYPE_PLAYBACK_CONTROL_RTSP,&rtspDesc);

		m_bPause = TRUE;
	}
}


void CPlaybackWnd::StartPlay()
{
	if(m_play_port< 0)
	{
		stream_media_format media_format;
		media_format.media_type = /*SIPD_MEDIA_TYPE_VIDEO*/ PLAYER_MEDIA_TYPE_MIX;
		media_format.video_type = PLAYER_MEDIA_F_VIDEO_TYPE_H264 /*PLAYER_MEDIA_F_VIDEO_TYPE_MPEG2*/;
		media_format.audio_type = PLAYER_MEDIA_F_AUDIO_TYPE_G711;

		m_play_port = player_stream_open(&media_format, GetSafeHwnd());
	}

	//	
	if(m_play_port>=0 && m_net_port<0)
	{
		char startUtc[32] = { 0 };
		char endUtc[32] = { 0 };
		convert_to_utc(m_listFiles[0].createtime, startUtc);
		convert_to_utc(m_listFiles[0].finishtime, endUtc);

		sipd_media_session catalog;
		memset(&catalog, 0, sizeof(sipd_media_session));

		stringstream ss;
		ss << "sip:" << LOCAL_DOMAIN_ID << "@" << LOCAL_IP << ":" << LOCAL_PORT; 
		strncpy(catalog.from_uri, ss.str().c_str(), MAX_SIPD_URI);

		ss.str("");
		ss << "sip:" << string(m_catalog_item.device_id) << "@" << REMOTE_IP << ":" << REMOTE_PORT;
		strncpy(catalog.to_uri, ss.str().c_str(), MAX_SIPD_URI);

		strncpy(catalog.channel_id, m_catalog_item.device_id, MAX_SIPD_DEVICE_ID_LEN);    // 35000100491327000249:3
		strncpy(catalog.o_id, m_catalog_item.device_id, MAX_SIPD_DEVICE_ID_LEN);  

		catalog.stream_type = SIPD_STREAM_TYPE_PLAYBACK /* SIPD_STREAM_TYPE_PLAY    SIPD_STREAM_TYPE_PLAYBACK */;

		//	��Ӧ�㲥 ������Ҫ�� 0 
		strncpy(catalog.t_start_time, startUtc, MAX_SIPD_NORMAL_LEN);		// 1492358400
		strncpy(catalog.t_end_time,   endUtc, MAX_SIPD_NORMAL_LEN);			// 1492430400   1492358415

		m_net_port = Dll_Call_play_playback_download(&catalog);
	}

	if(m_net_port>=0 && m_play_port >=0)
	{
		JMutexAutoLock lock(g_mtxNet);
		g_mapNet2Player[m_net_port] = m_play_port;
		g_mapNet2Hwnd[m_net_port] = GetSafeHwnd();

	}
}

void CPlaybackWnd::StopPlay()
{

	if(m_net_port>=0)
	{
		Dll_Call_Bye(m_net_port);
	}

	if(m_play_port>=0)
	{
		player_stream_close(m_play_port);
	}

	{
		JMutexAutoLock lock(g_mtxNet);
		if(g_mapNet2Player.count(m_net_port)>0)
		{
			g_mapNet2Player.erase(m_net_port);
		}

		if(g_mapNet2Hwnd.count(m_net_port)>0)
		{
			g_mapNet2Hwnd.erase(m_net_port);
		}
	}

	m_play_port = -1;
	m_net_port = -1;

}



void CPlaybackWnd::SearchFile(sipd_catalog_item *  pItem)
{
	m_catalog_item = *pItem;

	sipd_recordinfo_req RecordFileReq;
	memset(&RecordFileReq, 0, sizeof(sipd_recordinfo_req));

	stringstream ss;
	ss << "sip:" << LOCAL_DOMAIN_ID << "@" << LOCAL_IP << ":" << LOCAL_PORT; 
	strncpy(RecordFileReq.from_uri, ss.str().c_str(), MAX_SIPD_URI);

	ss.str("");
	ss << "sip:" << string(pItem->device_id) << "@" << REMOTE_IP << ":" << REMOTE_PORT;
	strncpy(RecordFileReq.to_uri, ss.str().c_str(), MAX_SIPD_URI);

	strncpy(RecordFileReq.device_id, pItem->device_id, MAX_SIPD_DEVICE_ID_LEN);

	RecordFileReq.Type = SIPD_RECORD_INFO_TYPE_TIME;
	strncpy(RecordFileReq.StartTime, "2017-09-11T01:05:09", MAX_SIPD_TIME_LEN);
	strncpy(RecordFileReq.EndTime, "2017-09-11T23:05:09", MAX_SIPD_TIME_LEN);

	int ret = Dll_search_recordfile_request (&RecordFileReq);

	if(ret>=0)
	{
		//	�յ��Ļظ� ���͵� �ָ��е�С����
		JMutexAutoLock lock(g_mtxNet);
		g_mapNet2Hwnd[ret] =  GetSafeHwnd();
	}
}


void CPlaybackWnd::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	StopPlay();
}

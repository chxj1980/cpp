// PlaybackView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GB28181ClientMDI.h"
#include "PlaybackView.h"


// CPlaybackView

IMPLEMENT_DYNCREATE(CPlaybackView, CFormView)

CPlaybackView::CPlaybackView()
	: CFormView(CPlaybackView::IDD)
{
	m_nCtrlPalyTimeH	= 140;
	m_nSkinBtnsH		= 50;
	m_nCurWndIndex		= 0;		// ��ǰ���ں�.


	m_bShowCtrlPlay = TRUE;
}

CPlaybackView::~CPlaybackView()
{
	m_SkinBtns.FreeAll();
}

void CPlaybackView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlaybackView, CFormView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_MESSAGE(WM_EVENT_SEL_WND, OnEventSelWnd)			// ���ѡ�񴰿�
	ON_MESSAGE(WM_BITMAPSLIDER_MOVED,OnBitmapSliderMoved)
END_MESSAGE_MAP()


// CPlaybackView ���

#ifdef _DEBUG
void CPlaybackView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlaybackView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ������ť��.
void CPlaybackView::CreateSkinBtns()
{
	CBitmap bmp;
	if(!bmp.LoadBitmap(IDB_BTNS_BACKGROUND))
	{
		return ;
	}

	BITMAP hbmp;
	bmp.GetBitmap(&hbmp);
	bmp.DeleteObject();

	m_nSkinBtnsH = hbmp.bmHeight;	// ��ť��߶�.

	m_SkinBtns.Create(WS_VISIBLE | WS_CHILD, CRect(0,0,0,0), this,IDC_CTRLBTNS);
	m_SkinBtns.ShowWindow(SW_SHOW);
	m_SkinBtns.LoadDlgBitmap(IDB_BTNS_BACKGROUND,IDB_BTNS_BACKGROUND,IDB_BTNS_BACKGROUND);

	CString strTip;
	CRect rect(0,0,40,40);
	strTip = "������";
	m_SkinBtns.AddButton(IDC_PLAY_VOICE,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_VOICE,IDB_VOICE_N,IDB_VOICE_M,IDB_VOICE_N,IDB_VOICE_N);

	strTip = "�ر�����";
	m_SkinBtns.AddButton(IDC_PLAY_VOICE_CLOSE,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_VOICE_CLOSE,IDB_VOICECLOSE_N,IDB_VOICECLOSE_M,IDB_VOICECLOSE_N,IDB_VOICECLOSE_N);
	m_SkinBtns.GetButton(IDC_PLAY_VOICE_CLOSE)->ShowWindow(SW_HIDE);

	m_SkinBtns.AddSepBmp(IDC_PLAY_SEPBMP1,IDB_BTNS_SEP,rect);

	strTip = "����";
	m_SkinBtns.AddButton(IDC_PLAY_PLAY,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_PLAY,IDB_PLAY_N,IDB_PLAY_M,IDB_PLAY_D,IDB_PLAY_N);

	// ��ͣ.
	strTip = "��ͣ";
	m_SkinBtns.AddButton(IDC_PLAY_PAUSE,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_PAUSE,IDB_PAUSE_N,IDB_PAUSE_M,IDB_PAUSE_D,IDB_PAUSE_N);
	m_SkinBtns.GetButton(IDC_PLAY_PAUSE)->ShowWindow(SW_HIDE);

	strTip = "ֹͣ";
	m_SkinBtns.AddButton(IDC_PLAY_STOP,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_STOP,IDB_STOP_N,IDB_STOP_M,IDB_STOP_D,IDB_STOP_N);

	strTip = "��֡";
	m_SkinBtns.AddButton(IDC_PLAY_FRAME,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_FRAME,IDB_ONEBYONE_N,IDB_ONEBYONE_M,IDB_ONEBYONE_D,IDB_ONEBYONE_N);

	// �ٶȻ���.
	m_SkinBtns.AddSlider(IDC_SLIDER_SPEED,rect,_T("�����ٶ�"));
	CBitmapSlider *pSlider = m_SkinBtns.GetSlider(IDC_SLIDER_SPEED);
	if(pSlider != NULL)
	{
		pSlider->SetBitmapChannel(IDB_SPEED_BK_N, IDB_SPEED_BK_N);
		pSlider->SetBitmapThumb(IDB_SPEED_THUMB_N, IDB_SPEED_THUMB_N, FALSE);
		pSlider->DrawFocusRect(FALSE);

		pSlider->SetRange(0,8);	
		pSlider->SetMargin(8,0,8,0);
		pSlider->SetPageSize(1);
		pSlider->SetPos(4);
	}

	// �����·�����.
	m_SkinBtns.AddSepBmp(IDC_SLIDER_SPEED_TEXT,IDB_SPEED_TEXT,rect);

	m_SkinBtns.AddSepBmp(IDC_PLAY_SEPBMP2,IDB_BTNS_SEP,rect);

	// ��ͼ.
	strTip = "��ͼ";
	m_SkinBtns.AddButton(IDC_PLAY_PIC,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_PIC,IDB_CAPTURE_N,IDB_CAPTURE_M,IDB_CAPTURE_D,IDB_CAPTURE_N);

	// ¼��.
	strTip = "��ʼ¼��";
	m_SkinBtns.AddButton(IDC_PLAY_REC,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_REC,IDB_RECORD_N,IDB_RECORD_M,IDB_RECORD_D,IDB_RECORD_N);

	// ֹͣ¼��.
	strTip = "ֹͣ¼��";
	m_SkinBtns.AddButton(IDC_PLAY_REC_STOP,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_REC_STOP,IDB_STOP_RECORD_N,IDB_STOP_RECORD_M,IDB_STOP_RECORD_D,IDB_STOP_RECORD_N);
	m_SkinBtns.GetButton(IDC_PLAY_REC_STOP)->ShowWindow(SW_HIDE);

	// ����.
	strTip = "����";
	m_SkinBtns.AddButton(IDC_PLAY_DOWN,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_PLAY_DOWN,IDB_DOWN_N,IDB_DOWN_M,IDB_DOWN_D,IDB_DOWN_N);

	m_SkinBtns.AddSepBmp(IDC_PLAY_SEPBMP3,IDB_BTNS_SEP,rect);

	// ������.
	strTip = "������";
	m_SkinBtns.AddButton(IDC_ONEPAN,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_ONEPAN,IDB_ONE_N,IDB_ONE_M,IDB_ONE_D,IDB_ONE_N);

	// �Ļ���.
	strTip = "�Ļ���";
	m_SkinBtns.AddButton(IDC_FOURPAN,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_FOURPAN,IDB_FOUR_N,IDB_FOUR_M,IDB_FOUR_D,IDB_FOUR_N);

	// ȫ��.
	strTip = "ȫ��";
	m_SkinBtns.AddButton(IDC_FULLPAN,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_FULLPAN,IDB_FULLSCREEN_N,IDB_FULLSCREEN_M,IDB_FULLSCREEN_D,IDB_FULLSCREEN_N);

	// ����ʱ����.
	strTip = "����ʱ����";
	m_SkinBtns.AddButton(IDC_HIDE_PLAYCTRL,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_HIDE_PLAYCTRL,IDB_HIDE_N,IDB_HIDE_M,IDB_HIDE_D,IDB_HIDE_N);

	// ��ʾʱ����.
	strTip = "��ʾʱ����";
	m_SkinBtns.AddButton(IDC_SHOW_PLAYCTRL,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_SHOW_PLAYCTRL,IDB_SHOW_N,IDB_SHOW_M,IDB_SHOW_D,IDB_SHOW_N);
	m_SkinBtns.GetButton(IDC_SHOW_PLAYCTRL)->ShowWindow(SW_HIDE);
	// 


	strTip = "����¼���ļ�";
	m_SkinBtns.AddButton(IDC_FIND,rect,strTip);
	m_SkinBtns.CopyFrom(IDC_FIND,IDB_FIND_N,IDB_FIND_D,IDB_FIND_N,IDB_FIND_N);
	m_SkinBtns.GetButton(IDC_FIND)->ShowWindow(SW_HIDE);


	strTip = "¼�����ʱ��";
	// ʱ��.
	m_SkinBtns.AddDateTimeCtrl(IDC_DATATIME,rect);
	m_SkinBtns.GetDateTimeCtrl(IDC_DATATIME)->ShowWindow(SW_HIDE);	

	// �豸����.
	m_SkinBtns.AddComboBox(IDC_DEVICE_TYPE,rect);
	m_SkinBtns.AddComboboxString(IDC_DEVICE_TYPE,_T("�洢¼��"),NVRTYPE);
	m_SkinBtns.AddComboboxString(IDC_DEVICE_TYPE,_T("DVR¼��"),DVRTYPE);
	m_SkinBtns.AddComboboxString(IDC_DEVICE_TYPE,_T("����¼��"),LOCALTYPE);
	//	m_SkinBtns.AddComboboxString(IDC_DEVICE_TYPE,_T("��ŵ¼��"),BRSTYPE);
	m_SkinBtns.SetComboboxCurSel(IDC_DEVICE_TYPE,NVRTYPE);
	m_SkinBtns.GetComboBox(IDC_DEVICE_TYPE)->ShowWindow(SW_HIDE);	

}

// CPlaybackView ��Ϣ�������

void CPlaybackView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	m_screenPannel.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,CRect(0,0,0,0),this,IDC_SCREENPANNEL);
	m_screenPannel.ShowWindow(SW_SHOW);

	// ����ʱ����.
	m_CtrlPlayTime.Create(WS_VISIBLE | WS_CHILD, CRect(0,0,0,0), this,IDC_CTRLWNDTIME);
	m_CtrlPlayTime.InvalidateCtrl();
	if(m_bShowCtrlPlay)
	{
		m_CtrlPlayTime.ShowWindow(SW_SHOW);
	}
	else
	{
		m_CtrlPlayTime.ShowWindow(SW_HIDE);
	}

	CreateSkinBtns();

	// �������ضԻ���.
	for(int i = 0; i < MAX_WINDOW; i ++)
	{
		CString strText;
		strText.Format("���ش���%d",i+1);
		/*m_showfile[i].Create(IDD_SHOWFILEINFO,this);
		m_showfile[i].SetDownLoadWindowText(strText);
		m_showfile[i].ShowWindow(SW_HIDE);*/
	}

	OnFourPannel();

	RecalcDlg();
}


// ������.
void CPlaybackView::OnOnePannel() 
{
	m_screenPannel.SetMultiScreen(TRUE,FALSE);
	m_screenPannel.SetShowPlayWin(SPLIT1);
	SetCurrentWnd(0);
}

// �Ĵ���
void CPlaybackView::OnFourPannel() 
{
	m_screenPannel.SetMultiScreen(TRUE,FALSE);
	m_screenPannel.SetShowPlayWin(SPLIT4);
	SetCurrentWnd(0);
}

// ȫ��.
void CPlaybackView::OnFullScreenPannel() 
{
	m_screenPannel.SetMultiScreen(TRUE,FALSE);
	m_screenPannel.SetFullScreen(TRUE);
}


void CPlaybackView::SetCurrentWnd(int nWndIndex)
{
	m_nCurWndIndex = nWndIndex;
	m_screenPannel.SetCurrentWnd(nWndIndex);
	SetCurWndBtns(nWndIndex);
	m_CtrlPlayTime.SetCurWndText(m_screenPannel.GetWndToolTip(nWndIndex));
}



int  CPlaybackView::GetCurrentWnd()
{
	return m_nCurWndIndex;
}


// �Զ�������ť���С.
void CPlaybackView::AutoRecalcLayout()
{
	if(m_SkinBtns.GetSafeHwnd() == NULL)
	{
		return ;
	}

	CBitmap bmp;
	if(!bmp.LoadBitmap(IDB_PLAY_N))
	{
		return ;
	}

	BITMAP hbmp;
	bmp.GetBitmap(&hbmp);
	bmp.DeleteObject();

	// ����λͼ���.
	int nBmpWidth	= hbmp.bmWidth;
	int nBmpHeight	= hbmp.bmHeight;
	int nOffset	= 4;
	int nSepW	= 2; // �ָ������.

	CRect rectParent;
	m_SkinBtns.GetClientRect(&rectParent);

	CRect rect;
	rect.top = rectParent.top + rectParent.Height()/2 - nBmpHeight/2;
	rect.bottom = rect.top + nBmpHeight;

	// ����/�ر�����.
	rect.left = nOffset;
	rect.right = rect.left + 22;
	m_SkinBtns.GetButton(IDC_PLAY_VOICE)->MoveWindow(rect);
	m_SkinBtns.GetButton(IDC_PLAY_VOICE_CLOSE)->MoveWindow(rect);

	// �ָ���.
	CRect rectSep;
	rectSep.left = rect.right + nOffset;
	rectSep.right = rectSep.left + nSepW;
	rectSep.top = rectParent.top;
	rectSep.bottom = rectParent.bottom;
	rect.right = rectSep.right;
	m_SkinBtns.EditSepBmpRect(IDC_PLAY_SEPBMP1,rectSep);

	// ֹͣ.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_PLAY_STOP)->MoveWindow(rect);

	// ����/ ��ͣ.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_PLAY_PLAY)->MoveWindow(rect);	
	m_SkinBtns.GetButton(IDC_PLAY_PAUSE)->MoveWindow(rect);

	// ��֡.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_PLAY_FRAME)->MoveWindow(rect);

	// �ٶȻ���.
	CRect rectSlider;
	CBitmap bmpSlider;
	if(bmpSlider.LoadBitmap(IDB_SPEED_BK_N))
	{
		bmpSlider.GetBitmap(&hbmp);
		bmpSlider.DeleteObject();
	}

	rectSlider.top = rectParent.top + 8;
	rectSlider.bottom = rectSlider.top + hbmp.bmHeight;
	rectSlider.left = rect.right + nOffset * 2;
	rectSlider.right = rectSlider.left + hbmp.bmWidth;
	rect.right = rectSlider.right;

	CBitmapSlider *pSlider = m_SkinBtns.GetSlider(IDC_SLIDER_SPEED);
	if(pSlider != NULL)
	{
		pSlider->MoveWindow(rectSlider);
	}

	// �����ı�����.
	if(bmpSlider.LoadBitmap(IDB_SPEED_TEXT))
	{
		bmpSlider.GetBitmap(&hbmp);
		bmpSlider.DeleteObject();
	}

	rectSlider.top = rectSlider.bottom + nOffset;
	rectSlider.bottom = rectSlider.top + hbmp.bmHeight;
	m_SkinBtns.EditSepBmpRect(IDC_SLIDER_SPEED_TEXT,rectSlider);

	rectSep.left = rect.right + nOffset;
	rectSep.right = rectSep.left + nSepW;
	rect.right = rectSep.right;
	m_SkinBtns.EditSepBmpRect(IDC_PLAY_SEPBMP2,rectSep);

	// ��ͼ.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_PLAY_PIC)->MoveWindow(rect);

	// ¼��/ֹͣ¼��.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_PLAY_REC)->MoveWindow(rect);
	m_SkinBtns.GetButton(IDC_PLAY_REC_STOP)->MoveWindow(rect);

	// ����/ֹͣ����.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_PLAY_DOWN)->MoveWindow(rect);

	// �ָ���.
	rectSep.left = rect.right + nOffset * 2;
	rectSep.right = rectSep.left + nSepW;
	rect.right = rectSep.right;
	m_SkinBtns.EditSepBmpRect(IDC_PLAY_SEPBMP3,rectSep);

	// ������.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_ONEPAN)->MoveWindow(rect);

	// �Ļ���.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_FOURPAN)->MoveWindow(rect);

	// ȫ��.
	rect.left = rect.right + nOffset;
	rect.right = rect.left + nBmpWidth;
	m_SkinBtns.GetButton(IDC_FULLPAN)->MoveWindow(rect);

	if(m_nSearchTimeMod>0)
	{
		// �ָ���.
		rectSep.left = rect.right + nOffset * 2;
		rectSep.right = rectSep.left + nSepW;
		rect.right = rectSep.right;
		m_SkinBtns.EditSepBmpRect(IDC_PLAY_SEPBMP3,rectSep);		

		int nDateTime = 24;
		int nTop = 0;
		int nBottom = 0;
		CRect rectTime;
		nTop = rectParent.top + rectParent.Height()/2 - nDateTime/2;
		nBottom = nTop + nDateTime;

		// ��ȡ��ǰѡ����豸����.

		if(m_nSearchTimeMod==1)
		{
			// ʱ��,�߶��ó�30.		
			rect.left = rect.right + nOffset;
			rect.right = rect.left + 100;
			m_SkinBtns.GetDateTimeCtrl(IDC_DATATIME)->MoveWindow(CRect(rect.left,nTop,rect.right,nBottom));
			m_SkinBtns.GetDateTimeCtrl(IDC_DATATIME)->ShowWindow(SW_SHOW);
		}

		if(m_nSearchTimeMod>1)
		{		
			// ��ȡ��ǰѡ����豸����.
			rect.left = rect.right + nOffset;
			rect.right = rect.left + 80;						
			m_SkinBtns.GetComboBox(IDC_DEVICE_TYPE)->MoveWindow(CRect(rect.left,nTop,rect.right,300));
			m_SkinBtns.GetComboBox(IDC_DEVICE_TYPE)->ShowWindow(SW_SHOW);

			// ʱ��,�߶��ó�30.		
			rect.left = rect.right + nOffset;
			rect.right = rect.left + 100;
			m_SkinBtns.GetDateTimeCtrl(IDC_DATATIME)->MoveWindow(CRect(rect.left,nTop,rect.right,nBottom));
			m_SkinBtns.GetDateTimeCtrl(IDC_DATATIME)->ShowWindow(SW_SHOW);

			// ����.
			rect.right = rectParent.right- 20;			
			rect.left = rect.right - 55;
			rect.top+=2;
			m_SkinBtns.GetButton(IDC_FIND)->MoveWindow(rect);
			m_SkinBtns.GetButton(IDC_FIND)->ShowWindow(SW_SHOW);
		}
	}
	// ��ʾ/����ʱ����.
	rect.right = rectParent.right;
	rect.left = rect.right - 18;
	m_SkinBtns.GetButton(IDC_HIDE_PLAYCTRL)->MoveWindow(rect);
	m_SkinBtns.GetButton(IDC_SHOW_PLAYCTRL)->MoveWindow(rect);

	m_SkinBtns.RecalcLayout();
}

// �����޲�����ť״̬.
void CPlaybackView::SetNormBtns()
{
	SetBtnsPlay(TRUE);
	SetBtnsRecord(FALSE);
	SetBtnsSound(FALSE);
	SetBtnSpeed(4);
}


// ���õ�ǰ���ڵİ�ť״̬.
void CPlaybackView::SetCurWndBtns(int nWndIndex)
{
	
	if(m_screenPannel.m_wndVideo[nWndIndex].m_listFiles.size()==0)
	{
		SetNormBtns();
		return ;
	}

	BOOL bEnableRecord = TRUE;
	int  nSpeed		= m_screenPannel.m_wndVideo[nWndIndex].nSpeed;
	BOOL bVoice		= m_screenPannel.m_wndVideo[nWndIndex].bVoice;
	BOOL bRecord	= m_screenPannel.m_wndVideo[nWndIndex].bRecordfile;
	BOOL bShowPlay	= FALSE;

	// û�в���.��ʾ���Ű�ť.
	if(m_screenPannel.m_wndVideo[nWndIndex].m_play_port < 0 || m_screenPannel.m_wndVideo[nWndIndex].m_net_port < 0 )
	{
		bShowPlay	= TRUE;
		bVoice		= FALSE;
		bRecord		= FALSE;
		nSpeed		= 4;
	}
	else
	{	
		// ��֡. ��ʾ���Ű�ť.
		if(m_screenPannel.m_wndVideo[nWndIndex].bOnebyone)
		{
			bShowPlay = TRUE;
		}	
		else if(m_screenPannel.m_wndVideo[nWndIndex].m_bPause)
		{	
			// ��ͣ״̬��ʾ���Ű�ť.
			bShowPlay = TRUE;
		}
	}

	SetBtnsPlay(bShowPlay);
	SetBtnsSound(bVoice);
	SetBtnsRecord(bRecord,bEnableRecord);
	SetBtnSpeed(nSpeed);
}


// ���ý��滬��λ��.
void CPlaybackView::SetBtnSpeed(int nPos)
{
	CBitmapSlider *pSlider = m_SkinBtns.GetSlider(IDC_SLIDER_SPEED);
	if(pSlider != NULL)
		pSlider->SetPos(nPos); 
}

// ���ý��水ť״̬.
// TRUE ���� / FALSE ��ͣ.
void CPlaybackView::SetBtnsPlay(BOOL bPlay)
{
	CSkinButton *pBtnPlay = m_SkinBtns.GetButton(IDC_PLAY_PLAY);
	CSkinButton *pBtnPause = m_SkinBtns.GetButton(IDC_PLAY_PAUSE);
	if(pBtnPause == NULL || pBtnPlay == NULL)
	{
		return;
	}

	if(bPlay)
	{		
		pBtnPlay->ShowWindow(SW_SHOW);
		pBtnPause->ShowWindow(SW_HIDE);
	}
	else
	{
		pBtnPlay->ShowWindow(SW_HIDE);
		pBtnPause->ShowWindow(SW_SHOW);
	}
}

// ���ý��水ť״̬.
// FALSE ¼�� / TRUE ֹͣ¼��.
void CPlaybackView::SetBtnsRecord(BOOL bRecord,BOOL bEnable)
{
	CSkinButton *pBtn1 = m_SkinBtns.GetButton(IDC_PLAY_REC);
	CSkinButton *pBtn2 = m_SkinBtns.GetButton(IDC_PLAY_REC_STOP);
	if(pBtn1 == NULL || pBtn2 == NULL)
	{
		return;
	}

	if(bRecord)
	{		
		pBtn1->ShowWindow(SW_HIDE);
		pBtn2->ShowWindow(SW_SHOW);
	}
	else
	{
		pBtn1->ShowWindow(SW_SHOW);
		pBtn2->ShowWindow(SW_HIDE);
	}

	pBtn1->EnableWindow(bEnable);
	pBtn2->EnableWindow(bEnable);
}

// ���ý��水ť״̬.
// TRUE �ر����� / FALSE ������.
void CPlaybackView::SetBtnsSound(BOOL bSound)
{
	CSkinButton *pBtn1 = m_SkinBtns.GetButton(IDC_PLAY_VOICE);
	CSkinButton *pBtn2 = m_SkinBtns.GetButton(IDC_PLAY_VOICE_CLOSE);
	if(pBtn1 == NULL || pBtn2 == NULL)
	{
		return;
	}

	if(bSound)
	{		
		pBtn1->ShowWindow(SW_HIDE);
		pBtn2->ShowWindow(SW_SHOW);
	}
	else
	{
		pBtn1->ShowWindow(SW_SHOW);
		pBtn2->ShowWindow(SW_HIDE);
	}
}

// ��ʾ/����ʱ����.
BOOL CPlaybackView::ShowPlayCtrlTime(BOOL bShow)
{
	CSkinButton *pBtn1 = m_SkinBtns.GetButton(IDC_HIDE_PLAYCTRL);
	CSkinButton *pBtn2 = m_SkinBtns.GetButton(IDC_SHOW_PLAYCTRL);
	if(pBtn1 == NULL || pBtn2 == NULL)
	{
		return FALSE;
	}

	m_bShowCtrlPlay = bShow;
	if(m_bShowCtrlPlay)
	{
		m_CtrlPlayTime.ShowWindow(SW_SHOW);
		pBtn1->ShowWindow(SW_SHOW);
		pBtn2->ShowWindow(SW_HIDE);
	}
	else
	{
		m_CtrlPlayTime.ShowWindow(SW_HIDE);
		pBtn1->ShowWindow(SW_HIDE);
		pBtn2->ShowWindow(SW_SHOW);
	}

	RecalcDlg();

	return TRUE;
}

BOOL CPlaybackView::RecalcDlg()
{
	if( m_screenPannel.GetSafeHwnd() == NULL  ||
		m_CtrlPlayTime.GetSafeHwnd() == NULL ||
		m_SkinBtns.GetSafeHwnd() == NULL)
	{
		return FALSE;
	}

	int nCtrlPalyTimeH = 0;
	if(m_bShowCtrlPlay)
	{
		nCtrlPalyTimeH = m_nCtrlPalyTimeH;
	}

	CRect rcMain,rectWnd;
	GetWindowRect(&rectWnd);
	ScreenToClient(&rectWnd);

	rcMain.top		= rectWnd.top;
	rcMain.bottom	= rectWnd.bottom- nCtrlPalyTimeH - m_nSkinBtnsH;
	rcMain.left		= rectWnd.left;
	rcMain.right	= rectWnd.right;
	m_screenPannel.MoveWindow(&rcMain);

	CRect rect;	
	rect.left = rcMain.left;
	rect.right = rcMain.right;

	// ʱ����.
	if(m_bShowCtrlPlay)
	{
		rect.bottom = rectWnd.bottom;
		rect.top = rect.bottom - m_nCtrlPalyTimeH;
		m_CtrlPlayTime.MoveWindow(rect);
		m_CtrlPlayTime.RecalcLayout();
	}
	else
	{
		rect.top = rectWnd.bottom;
	}

	// ��ť��.
	rect.bottom = rect.top;
	rect.top = rect.bottom - m_nSkinBtnsH;
	m_SkinBtns.MoveWindow(rect);
	AutoRecalcLayout();

	//����
	CWnd *pWnd = GetDlgItem(IDC_TITLE);
	if(pWnd != NULL)
	{
		rect.top	= 8;
		rect.bottom = 28;
		pWnd->MoveWindow(rect);
	}

	return TRUE;
}

void CPlaybackView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	ShowScrollBar(SB_BOTH,FALSE);//��ֱˮƽ����Ĺ�����������ʾ��

	RecalcDlg();
}

BOOL CPlaybackView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	if(lParam != BN_CLICKED)
	{
		return CFormView::OnCommand(wParam,lParam);
	}

	UINT uID = (UINT)wParam;
	switch (uID)
	{
	case IDC_HIDE_PLAYCTRL:
		{
			ShowPlayCtrlTime(FALSE);
			break;
		}
	case IDC_SHOW_PLAYCTRL:
		{
			ShowPlayCtrlTime(TRUE);
			break;
		}
	case IDC_PLAY_VOICE:
	case IDC_PLAY_VOICE_CLOSE:
		{			
			//OnPlayVoice();// �򿪻�ر�����.
			break;
		}
	case IDC_PLAY_PLAY:
		{			
			//OnPlay();// ����.
			int nWndIndex = GetCurrentWnd();
			m_screenPannel.m_wndVideo[nWndIndex].OnPlay();
			break;
		}
	case IDC_PLAY_PAUSE:
		{
			// ��ͣ����.
			int nWndIndex = GetCurrentWnd();
			m_screenPannel.m_wndVideo[nWndIndex].OnPause();
			
			break;
		}
	case IDC_PLAY_STOP:
		{			
			int nWndIndex = GetCurrentWnd();
			m_screenPannel.m_wndVideo[nWndIndex].OnStop();	// ֹͣ����.
			break;
		}
	case IDC_PLAY_FRAME:
		{			
			//OnPlayFrame();// ��֡����.
			break;
		}
	case IDC_PLAY_PIC:
		{
			//OnPlayPicture();	// ��ͼ.
			break;
		}
	case IDC_PLAY_REC:
	case IDC_PLAY_REC_STOP:
		{
			//OnPlayRecord();	// ��/�ر�¼��.
			break;
		}
	case IDC_PLAY_DOWN:
		{
			//OnPlayDown();	// ����.
			break;
		}
	case IDC_ONEPAN:
		{
			OnOnePannel();	// ������.
			break;
		}
	case IDC_FOURPAN:
		{
			OnFourPannel();// �Ļ���.
			break;
		}
	case IDC_FULLPAN:
		{
			OnFullScreenPannel();// ȫ��.
			break;
		}
	case IDC_FIND:				// ����.
		{
			//OnFind();
			break;
		}
	}

	int nWndIndex = GetCurrentWnd();
	SetCurWndBtns(nWndIndex);

	return CFormView::OnCommand(wParam, lParam);
}

void CPlaybackView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// ֹͣ����.
	for(int i = 0; i < MAX_WINDOW; i ++)
	{
		//m_showfile[i].DestroyWindow();
	}

	
}

HBRUSH CPlaybackView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC ) 
	{
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SetTextColor(RGB(150,150,150));

		return (HBRUSH)GetStockObject (HOLLOW_BRUSH); 
	}

	//�趨�ؼ��ı���ɫ��ǰ��ɫ�Լ�����ȵȣ������ϢҲ��������
	return hbr;
}


LRESULT CPlaybackView::OnEventSelWnd(WPARAM wParam,LPARAM lParam)
{
	SetCurrentWnd((int)wParam);

	m_screenPannel.Invalidate();

	return 0;		 
}

// ��������.
LRESULT CPlaybackView::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
{
	UINT uID = (UINT)wParam;
	int nPos = (int)lParam;

	if(uID != IDC_SLIDER_SPEED)
	{
		return 0;
	}

	int nWndIndex = GetCurrentWnd();
	// �ٶȻ���.
	if(m_screenPannel.m_wndVideo[nWndIndex].m_net_port< 0 || m_screenPannel.m_wndVideo[nWndIndex].m_play_port< 0)
	{
		//g_pPlayBackCtrl->ShowHyperLinkDlg("���Ų���","������Ƶδ��������֧�ֱ��ٲ���",FALSE);
		return 0;
	}

	// ��֡��֧�ֿ��\���Ų���.
	if (m_screenPannel.m_wndVideo[nWndIndex].bOnebyone)
	{
		return 0;
	}

	DebugTrace("nPos=%d",nPos);
	// û�б仯,������.
	if(m_screenPannel.m_wndVideo[nWndIndex].nSpeed == nPos)
	{
		//g_pPlayBackCtrl->ShowHyperLinkDlg("���Ų���","�����ٶ�δ�ı�",FALSE);
		return 0;
	}
	else
		m_screenPannel.m_wndVideo[nWndIndex].nSpeed=nPos;

	sipd_playback_mans_rtsp_ind rtspDesc={0};
	if(nPos==4)
	{
		//	��������
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 1.0\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 1.0);
	}
	// ����
	else if(nPos==3)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 0.5\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 0.5);
	}
	else if(nPos==2)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 0.25\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 0.25);
	}
	else if(nPos==1)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 0.125\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 0.125);
	}
	else if(nPos==0)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 0.0625\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 0.0625);
	}
	//	���
	else if(nPos==5)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 2.0\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 2.0);
	}
	else if(nPos==6)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 4.0\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 4.0);
	}
	else if(nPos==7)
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale: 8.0\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 8.0);
	}
	else 
	{
		sprintf(rtspDesc.rtsp_des,"PLAY RTSP/1.0\r\nCSeq: 1\r\nScale:16.0\r\n");

		player_stream_speed(m_screenPannel.m_wndVideo[nWndIndex].m_play_port, 16.0);
	}
	
	rtspDesc.len = strlen(rtspDesc.rtsp_des);
	int iCmdId = Dll_Call_media_control(m_screenPannel.m_wndVideo[nWndIndex].m_net_port, SIPD_TO_CMS_CMD_TYPE_PLAYBACK_CONTROL_RTSP,&rtspDesc);


	// ���ð�ť��λͼ״̬.
	SetCurWndBtns(nWndIndex);

	return 0;
}
DROPEFFECT CPlaybackView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���

	return DROPEFFECT_COPY;

	return CFormView::OnDragEnter(pDataObject, dwKeyState, point);
}

void CPlaybackView::OnDragLeave()
{
	// TODO: �ڴ����ר�ô����/����û���

	CFormView::OnDragLeave();
}

DROPEFFECT CPlaybackView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���

	return DROPEFFECT_COPY;

	return CFormView::OnDragOver(pDataObject, dwKeyState, point);
}

BOOL CPlaybackView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���
	HGLOBAL hgMem = NULL; 
	if (pDataObject->IsDataAvailable(CF_TEXT))
	{
		hgMem = pDataObject->GetGlobalData(CF_TEXT);
		sipd_catalog_item * pItem = (sipd_catalog_item *)GlobalLock(hgMem);
		if (pItem != NULL)
		{
			int nHit = m_screenPannel.HitTest(point);
			if(nHit>=0)
			{
				SetCurrentWnd(nHit);
				m_CtrlPlayTime.ClearWnd(nHit);

				m_screenPannel.m_wndVideo[nHit].OnStop();

				// �����޲�����ť״̬.
				SetNormBtns();
				m_screenPannel.m_wndVideo[nHit].SearchFile(pItem);
			}
			else
				AfxMessageBox("δ�ҵ�����");
		}

		if(hgMem)
		{
			// �ռ�Ľ������ͷ�
			GlobalUnlock(hgMem);
			GlobalFree((HGLOBAL)hgMem);
		}
	}

	return CFormView::OnDrop(pDataObject, dropEffect, point);
}

int CPlaybackView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_CTreeDropTarget.Register(this);
	return 0;
}


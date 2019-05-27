#include "stdafx.h"
#include "PlayTimeCtrl.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_BTN_DAY		1001	// ����.
#define IDC_BTN_HOUR2	1002	// ��Сʱ.
#define IDC_BTN_HOUR1	1003	// һСʱ.
#define IDC_BTN_MIN30	1004	// 30��.
#define IDC_BTN_NEXT	1005	// ��һ��ʱ���.
#define IDC_BTN_PRE		1006	// ��һ��ʱ���.

// CPlayTimeCtrl

CPlayTimeCtrl::CPlayTimeCtrl()
{
	m_nTimeOffset	= 0;
	m_nType			= _TIME_DAY;	// Ĭ��һ��.
	m_nEachWndH		= 10;
	m_nGapOffset	= 2;
	m_nWndCnt		= MAX_WINDOW;		// Ĭ���Ĵ���.
	m_nLeftW		= 90;
	m_nEachHourW	= 10;
	
	m_clrText		= RGB(128,128,128);
	m_clrGapUp		= RGB(0,0,0);
	m_clrGapDown	= RGB(146,146,146);
	m_clrBackGround = RGB(22,22,22);
	m_clrFile		= RGB(6,211,255);
	m_clrBtnNorm	= RGB(202,202,202);
	m_clrBtnSelect	= RGB(6,211,255);

	m_MapWnds.clear();
	m_MapBtns.clear();

	m_strCurWndText = "";
	m_strMouseMoveTm = "";

	m_TipFlag = false;
}

CPlayTimeCtrl::~CPlayTimeCtrl()
{	
	ClearBtns();
	m_MapWnds.clear();

	if(m_Bitmap.GetSafeHandle())		{	DeleteObject(m_Bitmap);	 }
	if(m_MemDC.GetSafeHdc() != NULL)	{   DeleteObject(m_MemDC);	 }
}

BEGIN_MESSAGE_MAP(CPlayTimeCtrl, CWnd)
	//{{AFX_MSG_MAP(CPlayTimeCtrl)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPlayTimeCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

BOOL CPlayTimeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW |CS_DBLCLKS );

	return  CWnd::CreateEx(NULL, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

BOOL CPlayTimeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	//if(pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
	//{
	//	if(::IsWindow(pMsg->hwnd))
	//	{
	//		m_ToolTip.RelayEvent(pMsg);
	//	}
	//}
	
	return CWnd::PreTranslateMessage(pMsg);
}

void CPlayTimeCtrl::OnPaint() 
{
	CPaintDC dc(this);

	if(!m_MemDC.GetSafeHdc())
	{
		return;
	}	
	
	CRect rcClient;
	GetClientRect(rcClient);
	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_MemDC, 0, 0, SRCCOPY);
}

void CPlayTimeCtrl::InvalidateCtrl()
{
	// ��ʼ����ʾ��Ϣ.
	InitToolTips();

	CClientDC dc(this);
	CRect rcClient;

	GetClientRect(rcClient);

	if(!m_MemDC.GetSafeHdc())
	{
		m_MemDC.CreateCompatibleDC(&dc);
		m_Bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
		m_MemDC.SelectObject(m_Bitmap);	

		m_MemDC.SetBkColor(m_clrBackGround);

		DrawTicks(&m_MemDC);
	}

	InvalidateRect(rcClient);
}

void CPlayTimeCtrl::InitToolTips()
{
	if(m_ToolTip.GetSafeHwnd() == NULL)
	{
		m_ToolTip.Create(this);
		m_ToolTip.Activate(TRUE);
		m_ToolTip.AddTool(this, LPSTR_TEXTCALLBACK);
		m_ToolTip.SetDelayTime(100);
	}
}

void CPlayTimeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);

	if(m_ToolTip.GetSafeHwnd() != NULL)
	{
		MSG msg; 
		msg.hwnd = GetSafeHwnd(); 
		msg.message = WM_MOUSEMOVE; 
		msg.wParam = WPARAM(nFlags); 
		msg.time = 0; 
		msg.pt.x = point.x; 
		msg.pt.y = point.y; 
		msg.lParam = MAKELPARAM(LOWORD(point.x), LOWORD(point.y)); 

		m_ToolTip.RelayEvent(&msg);
	}

	CString strToolTip = _T("");
	// �ж�����Ƿ��ڰ�ť��.
	int nBtnID = PtInBtns(point,strToolTip);
	if(nBtnID != -1 && false == m_TipFlag)
	{
		m_TipFlag = true;
		m_ToolTip.UpdateTipText( (LPCTSTR)strToolTip, this );
		m_ToolTip.Update();
		return;
	} 
	else
	{
		m_TipFlag = false;
	}

	int nWndIndex = -1;
	GetCurrentPointTime(point,nWndIndex,strToolTip);
	if(nWndIndex >= 0)
	{
		// ȥ��������.
		int nPos = strToolTip.Find(" ");
		if(nPos != -1)
		{
			m_strMouseMoveTm = strToolTip.Right(strToolTip.GetLength() - nPos);
		}
		else
		{
			m_strMouseMoveTm = strToolTip;
		}
	}
	else
	{
		m_strMouseMoveTm = "";
	}

	RecalcLayout();
}

void CPlayTimeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDblClk(nFlags,point);

	CString strToolTip = _T("");
	int nWndIndex = -1;
	if(GetCurrentPointTime(point,nWndIndex,strToolTip))
	{
		// ȥ�������е�':',' ','-'����.
		strToolTip.Replace(":","");
		strToolTip.Replace("-","");
		strToolTip.Replace(" ","");
		OutputDebugString(strToolTip);
		GetParent()->SendMessage(WM_PLAYTIME_LBUTTONDBLCLK, nWndIndex,(LPARAM)strToolTip.GetBuffer(0));
		strToolTip.ReleaseBuffer();
	}
}

void CPlayTimeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags,point);
}

void CPlayTimeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{	
	CWnd::OnLButtonUp(nFlags,point);

	// �ж��Ƿ�˫����ť.
	CString strToolTip = _T("");
	// �ж�����Ƿ��ڰ�ť��.
	int nBtnID = PtInBtns(point,strToolTip);
	if(nBtnID == -1)
	{
		return ;
	}

	// ��ͬ,������һҳ����һҳ.
	switch(nBtnID)
	{
	case IDC_BTN_PRE:
		{
			m_nTimeOffset --;
			m_nTimeOffset = max(m_nTimeOffset,0);
			break;
		}
	case IDC_BTN_NEXT:
		{
			m_nTimeOffset ++;
			m_nTimeOffset = min(m_nTimeOffset,GetTimeOffsetSupportCnt(m_nType));
			break;
		}
	default:
		{
			// ���㵱ǰ��ʾ��ʱ���,ת��������������Ӧ��ƫ��ֵ.
			if(m_nType != nBtnID)
			{
				long lOldTimeLength = GetTimeLength(m_nType);
				long lNewTimeLength = GetTimeLength(nBtnID);
				if(lOldTimeLength == -1 || lNewTimeLength == -1 || nBtnID == _TIME_DAY)
				{
					m_nTimeOffset = 0;
				}
				else
				{
					m_nTimeOffset = m_nTimeOffset * lOldTimeLength/lNewTimeLength;
					m_nTimeOffset = min(m_nTimeOffset,GetTimeOffsetSupportCnt(nBtnID));
				}
			}

			m_nType = nBtnID;
		}
	}

	RecalcLayout();
}

// ����������ڴ����±�. 
// ��0��ʼ,ʧ�� -1.������Ҳ����-1.
int  CPlayTimeCtrl::PtInWnd(CPoint point)
{
	CRect rcClient;
	GetClientRect(rcClient);
	
	CRect rect;
	rect.left = m_nLeftW + m_nGapOffset;
	rect.right = rcClient.right;
	rect.top   = m_nGapOffset/2 + m_nEachWndH;	// �����߶�.
	
	for(int i = 0; i < m_nWndCnt; i ++)
	{
		rect.top = rect.top + m_nGapOffset;
		rect.bottom = rect.top + m_nEachWndH;

		if(rect.PtInRect(point))
		{
			return i;
		}

		rect.top = rect.bottom;
	}

	return -1;
}

// ��������Ƿ��ڰ�ťλ����.
int CPlayTimeCtrl::PtInBtns(CPoint point,CString &strToolTip)
{
	BtnsMapIt it;
	for(it = m_MapBtns.begin(); it != m_MapBtns.end(); it ++)
	{
		if(PtInRegion(it->second.hRgn,point.x,point.y))
		{
			strToolTip = it->second.strToolTip;
			return it->second.uBtnID;
		}
	}

	return -1;
}

// �����ť��Դ.
void CPlayTimeCtrl::ClearBtns()
{
	BtnsMapIt it;
	for(it = m_MapBtns.begin(); it != m_MapBtns.end(); it ++)
	{
		if(it->second.hRgn != NULL)
		{
			DeleteObject(it->second.hRgn);
			it->second.hRgn = NULL;
		}
	}

	m_MapBtns.clear();
}

// ��ȡ��ǰ����֧�ֵ�ʱ�䳤��.��ȷ����.
// ����ֵ -1 ��֧��.
// ����0.
long CPlayTimeCtrl::GetTimeLength(int nType,BOOL bCalcSec)
{
	long lTimeLength = -1;	// ��ǰʱ��η�Χ.
	switch(nType)
	{
	case _TIME_DAY:// ����.
		{
			lTimeLength = 60 * 24;
			break;
		}
	case _TIME_HOUR1:
		{
			lTimeLength = 60;
			break;
		}
	case _TIME_HOUR2:
		{
			lTimeLength = 60 * 2;
			break;
		}
	case _TIME_MIN30:
		{
			lTimeLength = 30;		
			break;
		}
	}

	if(lTimeLength == -1)
	{
		return -1;
	}

	if(bCalcSec)
	{
		lTimeLength = lTimeLength * 60;
	}

	return lTimeLength;
}

// ��ȡһ������ܲ�ֳɶ��ٸ�ʱ���.
int CPlayTimeCtrl::GetTimeOffsetSupportCnt(int nType)
{
	long lTimeLength = GetTimeLength(nType,FALSE);
	if(lTimeLength <= 0)
	{
		return 0;
	}
	
	int nMin = 24* 60/lTimeLength - 1;		// ��0��ʼ ��1.
	nMin = max(nMin,0);

	return nMin;
}

// ���ݵ�ǰ��ʾ����,������Ӧ�Ĳ�ָ���.
// ��ʾȫ����������ҵ�һ����ʱ��ε��������,
int CPlayTimeCtrl::GetSplitCnt(int nType)
{
	switch(m_nType)
	{
	case _TIME_DAY:	// ����.
		{
			return 12;
			break;
		}
	case _TIME_HOUR1:	// 1Сʱ.
		{
			return 12;
			break;
		}
	case _TIME_HOUR2:	// 2Сʱ.
		{
			return 12;
			break;
		}
	case _TIME_MIN30:	// 30����.
		{
			return 15;
			break;
		}
	}

	return 12;
}

void CPlayTimeCtrl::DrawTicks(CDC* pDC)
{
	if(m_nWndCnt <= 0)
	{
		return ;
	}

	int nSplitCnt = GetSplitCnt(m_nType);

	CRect rcClient;
    GetClientRect(&rcClient);
	
	COLORREF OldColor = pDC->SetTextColor(m_clrText);
	int nOldMode = pDC->SetBkMode(TRANSPARENT);

    m_nEachHourW = (int)(rcClient.Width()-m_nLeftW - m_nGapOffset)/nSplitCnt;
	m_nEachWndW = m_nEachHourW * nSplitCnt;
	// ���¼�����߿��.
	m_nLeftW = rcClient.Width() - m_nEachWndW - m_nGapOffset;

	// ����ÿ�ݴ��ڸ߶�. �ײ��͵ײ���ֻ�а�������������һ��,�ټ��ϸ�������һ�����.
	// �ܹ������ռ�߶� = (���ڸ��� + 1) * ����߶�.
	m_nEachWndH = rcClient.Height()/(m_nWndCnt+2) - m_nGapOffset;
	
	// �����������.
	pDC->FillSolidRect(rcClient,m_clrBackGround);

	CRect rect;
	// ����������.
	rect.left = rcClient.left;
	rect.top = rcClient.top;
	rect.right = rcClient.right;
	rect.bottom = rcClient.top + m_nGapOffset/2;
	pDC->FillSolidRect(rect, m_clrGapUp);

	int i = 0;
	// ������д��ڶ������.
	for(i = 0; i < m_nWndCnt; i ++)
	{
		// �ϲ����.
		rect.top = rect.bottom + m_nEachWndH;
		rect.bottom = rect.top + m_nGapOffset/2;
		pDC->FillSolidRect(rect, m_clrGapUp);

		// �²����.
		rect.top = rect.bottom;
		rect.bottom = rect.top + m_nGapOffset/2;
		pDC->FillSolidRect(rect, m_clrGapDown);

		// ��д������������.
		CString strText = _T("");
		strText.Format(_T("����%d"),i+1);

		// ����������ռ�ռ�.
		CSize size = pDC->GetTextExtent(strText);
		int nTextLeft = (m_nLeftW - size.cx)/2;
		int nTexttop  = rect.bottom + (m_nEachWndH - size.cy)/2;
		pDC->TextOut(nTextLeft,nTexttop, strText); 
	}

	// ������һ�����ڵĵײ�����.
	// �ϲ����.
	rect.top = rect.bottom + m_nEachWndH;
	rect.bottom = rect.top + m_nGapOffset/2;
	pDC->FillSolidRect(rect, m_clrGapUp);

	// �²����.
	rect.top = rect.bottom;
	rect.bottom = rect.top + m_nGapOffset/2;
	pDC->FillSolidRect(rect, m_clrGapDown);

	// ���ײ����.
	rect.CopyRect(rcClient);
	rect.top = rect.bottom - m_nGapOffset/2;
	pDC->FillSolidRect(rect, m_clrGapUp);

	// ������(���ϵ���).
	rect.CopyRect(rcClient);
	rect.left = m_nLeftW;
	rect.right = rect.left + m_nGapOffset/2;
	pDC->FillSolidRect(rect, m_clrGapUp);

	rect.left = rect.right;
	rect.right = rect.left + m_nGapOffset/2;
	pDC->FillSolidRect(rect, m_clrGapDown);

	// ���ײ��Ŀ��ư�ť.
	CRect rectBottom;
	rectBottom.bottom = rect.bottom - m_nGapOffset;
	rectBottom.top = rectBottom.bottom - m_nEachWndH;
	rectBottom.left = m_nLeftW + m_nGapOffset;
	rectBottom.right = rcClient.right;
	DrawBottomBtn(pDC,rectBottom);

	LONG lTimeLength = GetTimeLength(m_nType,FALSE);
	int nEachTimeLength = lTimeLength/nSplitCnt;	// ÿ��ʱ��.

	CSize size;
	int nTextLeft = 0;
	int nTexttop = 0;
	// ��д����ʱ��.
	for ( i = 1; i <= nSplitCnt; i ++)
	{
		long lTimeCnt = m_nTimeOffset *lTimeLength + nEachTimeLength * i;
		CString strText = _T("");
		strText.Format(_T("%02d:%02d"),lTimeCnt/60,lTimeCnt%60);	
		// ����������ռ�ռ�.
		size = pDC->GetTextExtent(strText);
		nTextLeft = m_nLeftW + m_nGapOffset + m_nEachHourW*i- size.cx;
		nTexttop  = (m_nGapOffset/2 + m_nEachWndH - size.cy)/2 + 3;
		pDC->TextOut(nTextLeft,nTexttop, strText); 
	}	
	// ���Ƶ�ǰ������ڵ�ʱ���ı�.	
	size = pDC->GetTextExtent(m_strMouseMoveTm);
	nTextLeft = m_nLeftW/2 + m_nGapOffset - size.cx/2;
	nTexttop  = (m_nGapOffset/2 + m_nEachWndH - size.cy)/2 + 3;
	pDC->TextOut(nTextLeft,nTexttop, m_strMouseMoveTm);

	// ���Ƶ�ǰ�����ı�.
	// ����������ռ�ռ�.
	size = pDC->GetTextExtent(m_strCurWndText);
	nTextLeft = m_nLeftW + m_nGapOffset +3;
	nTexttop  = rect.bottom - m_nGapOffset - m_nEachWndH + size.cy/2;
	
//����ʾͨ����
	//2012-5-22
	pDC->TextOut(nTextLeft,nTexttop, m_strCurWndText);

	pDC->SetBkMode(nOldMode);
}

// ���Ƶײ����ư�ť��.
void CPlayTimeCtrl::DrawBottomBtn(CDC *pDC,CRect rect)
{
	ClearBtns();

	int nOffset = 2;
	HDC hDC = pDC->GetSafeHdc();
	CSize size;	
	CBrush brNorm(m_clrBtnNorm);
	CBrush brSelect(m_clrBtnSelect);
	CRgn rgn;

	STRUBTN struData;

	// 30min
	struData.uBtnID = _TIME_MIN30;
	struData.strText = _T("30Min");
	struData.strToolTip = _T("����ǰҪ�鿴��ʱ��ֳ�30����");
	size = pDC->GetTextExtent(struData.strText);
	int nRight = rect.right - nOffset * 2;
	int nLeft = nRight - size.cx - nOffset * 2;
	int nTop = rect.top + rect.Height()/2 - size.cy/2;
	int nBottom = nTop + size.cy + nOffset;
	
	BeginPath(hDC);
	Rectangle(hDC,nLeft,nTop,nRight,nBottom);
	EndPath(hDC);
	struData.hRgn = PathToRegion(hDC);
	m_MapBtns.insert(BtnsMapValueType(IDC_BTN_MIN30,struData));
	
	if(struData.uBtnID == m_nType)
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brSelect);
	}
	else
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brNorm);
	}
	
	pDC->DrawText(struData.strText,CRect(nLeft,nTop,nRight,nBottom), DT_CENTER);

	// 1hour
	struData.uBtnID = _TIME_HOUR1;
	struData.strText = _T("1Hour");
	struData.strToolTip = _T("����ǰҪ�鿴��ʱ��ֳ�1Сʱ");
	size = pDC->GetTextExtent(struData.strText);
	nRight = nLeft - nOffset * 2;
	nLeft = nRight - size.cx - nOffset * 2;
	BeginPath(hDC);
	Rectangle(hDC,nLeft,nTop,nRight,nBottom);
	EndPath(hDC);
	struData.hRgn = PathToRegion(hDC);
	m_MapBtns.insert(BtnsMapValueType(IDC_BTN_HOUR1,struData));

	if(struData.uBtnID == m_nType)
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brSelect);
	}
	else
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brNorm);
	}
	pDC->DrawText(struData.strText,CRect(nLeft,nTop,nRight,nBottom), DT_CENTER);

	// 2hour
	struData.uBtnID = _TIME_HOUR2;
	struData.strText = _T("2Hour");
	struData.strToolTip = _T("����ǰҪ�鿴��ʱ��ֳ�2Сʱ");
	size = pDC->GetTextExtent(struData.strText);
	nRight = nLeft - nOffset * 2;
	nLeft = nRight - size.cx - nOffset * 2;
	BeginPath(hDC);
	Rectangle(hDC,nLeft,nTop,nRight,nBottom);
	EndPath(hDC);
	struData.hRgn = PathToRegion(hDC);
	m_MapBtns.insert(BtnsMapValueType(IDC_BTN_HOUR2,struData));

	if(struData.uBtnID == m_nType)
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brSelect);
	}
	else
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brNorm);
	}
	pDC->DrawText(struData.strText,CRect(nLeft,nTop,nRight,nBottom), DT_CENTER);

	// 1day
	struData.uBtnID = _TIME_DAY;
	struData.strText = _T("1Day");
	struData.strToolTip = _T("����ǰҪ�鿴��ʱ��ֳ�1��");
	size = pDC->GetTextExtent(struData.strText);
	nRight = nLeft - nOffset * 2;
	nLeft = nRight - size.cx - nOffset * 2;
	BeginPath(hDC);
	Rectangle(hDC,nLeft,nTop,nRight,nBottom);
	EndPath(hDC);
	struData.hRgn = PathToRegion(hDC);
	m_MapBtns.insert(BtnsMapValueType(IDC_BTN_DAY,struData));

	if(struData.uBtnID == m_nType)
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brSelect);
	}
	else
	{
		::FillRgn(hDC,struData.hRgn,(HBRUSH)brNorm);
	}
	pDC->DrawText(struData.strText,CRect(nLeft,nTop,nRight,nBottom), DT_CENTER);

	// ��һ��ʱ���.
	struData.uBtnID = IDC_BTN_NEXT;
	struData.strText = _T("");
	struData.strToolTip = _T("�鿴��һ��ʱ��ν��");

	nRight = nLeft - nOffset * 3;
	nLeft = nRight - 10;
	BeginPath(hDC);
	MoveToEx(hDC,nRight , nTop + (nBottom-nTop)/2, NULL);
	LineTo(hDC, nLeft,nBottom);
	LineTo(hDC,nLeft,nTop);
	LineTo(hDC,nRight , nTop + (nBottom-nTop)/2);	
	EndPath(hDC);
	struData.hRgn = PathToRegion(hDC);
	m_MapBtns.insert(BtnsMapValueType(IDC_BTN_NEXT,struData));

	::FillRgn(hDC,struData.hRgn,(HBRUSH)brNorm);

	// ��һ��ʱ���.
	struData.uBtnID = IDC_BTN_PRE;
	struData.strText = _T("");
	struData.strToolTip = _T("�鿴��һ��ʱ��ν��");

	nRight = nLeft - nOffset * 3;
	nLeft = nRight - 10;
	BeginPath(hDC);
	MoveToEx(hDC,nLeft , nTop + (nBottom-nTop)/2, NULL);
	LineTo(hDC, nRight,nBottom);
	LineTo(hDC,nRight,nTop);
	LineTo(hDC,nLeft , nTop + (nBottom-nTop)/2);	
	EndPath(hDC);
	struData.hRgn = PathToRegion(hDC);
	m_MapBtns.insert(BtnsMapValueType(IDC_BTN_PRE,struData));

	::FillRgn(hDC,struData.hRgn,(HBRUSH)brNorm);
}

// ���ָ�����ڵ�ʱ��.[����ڲ�ʱ��]
void CPlayTimeCtrl::ClearWnd(int nWndIndex)
{
	WndDataMapIt it = m_MapWnds.find(nWndIndex);
	if(it == m_MapWnds.end())
	{
		return ;
	}

	m_MapWnds.erase(it);
}

void CPlayTimeCtrl::SetCurWndText(CString strCurWndText)
{ 
	m_strCurWndText = strCurWndText; 
	RecalcLayout();
}

void CPlayTimeCtrl::AddWndData(int nWndIndex,DWORD dwYear,DWORD dwMonth,DWORD dwDay,RETSEARCH *pstruFileInfo,int nFileCnt)
{
	if(pstruFileInfo == NULL || nFileCnt == 0)
	{
		return;
	}

	STRU_DAY struDay;
	struDay.struDate.dwYear		= dwYear;
	struDay.struDate.dwMonth	= dwMonth;
	struDay.struDate.dwDay		= dwDay;

	LONGLONG llTimeCnt = 24 * 60 * 60;	// һ��ʱ��.
	CTime ctStart,ctEnd;
	// �õ�ʱ�䷶Χ.
	for(int i = 0; i < nFileCnt; i ++)
	{
		if(strlen(pstruFileInfo[i].createtime) == 0 || pstruFileInfo[i].createtime[0] == 0)
		{
			continue;
		}
		//		DebugTrace("SetWndData %d", nFileCnt);
		// ת����ʼ�ͽ���ʱ��.
		ctStart = StrToTime(pstruFileInfo[i].createtime);
		ctEnd = StrToTime(pstruFileInfo[i].finishtime);

		if(ctStart > ctEnd)
		{
			CTime ctTemp = ctStart;
			ctStart = ctEnd;
			ctEnd = ctTemp;
		}

		// ʱ���.
		CTimeSpan tmSpan = ctEnd - ctStart;
		// ����ʱ�䳬����ʼʱ��,��Чʱ��.
		LONGLONG llOffsetSec = tmSpan.GetTotalSeconds();
		if(llOffsetSec < 0)
		{
			continue;;
		}

		// ����ʱ�䳬����ʼʱ��1��,��Ч.
		if(llOffsetSec > llTimeCnt)
		{
			continue;
		}

		// �ж������Ƿ�һ��,��һ��Ϊ����.
		if(ctStart.GetDay() == ctEnd.GetDay())
		{
			STRU_DATETIME struData;
			struData.struDate.dwYear = ctStart.GetYear();
			struData.struDate.dwMonth = ctStart.GetMonth();
			struData.struDate.dwDay = ctStart.GetDay();
			struData.struTimeStart.nHour = ctStart.GetHour();
			struData.struTimeStart.nMin = ctStart.GetMinute();
			struData.struTimeStart.nSec = ctStart.GetSecond();

			struData.struTimeEnd.nHour = ctEnd.GetHour();
			struData.struTimeEnd.nMin = ctEnd.GetMinute();
			struData.struTimeEnd.nSec = ctEnd.GetSecond();
			struDay.listDate.push_back(struData);
		}
		else
		{	
			// ����.��ֳ�����ʱ���.
			STRU_DATETIME struData;		
			struData.struDate.dwYear = ctStart.GetYear();
			struData.struDate.dwMonth = ctStart.GetMonth();
			struData.struDate.dwDay = ctStart.GetDay();
			struData.struTimeStart.nHour = ctStart.GetHour();
			struData.struTimeStart.nMin = ctStart.GetMinute();
			struData.struTimeStart.nSec = ctStart.GetSecond();

			struData.struTimeEnd.nHour = 23;
			struData.struTimeEnd.nMin = 59;
			struData.struTimeEnd.nSec = 59;
			struDay.listDate.push_back(struData);

			struData.struDate.dwYear = ctEnd.GetYear();
			struData.struDate.dwMonth = ctEnd.GetMonth();
			struData.struDate.dwDay = ctEnd.GetDay();
			struData.struTimeStart.nHour = 0;
			struData.struTimeStart.nMin = 0;
			struData.struTimeStart.nSec = 0;

			struData.struTimeEnd.nHour = ctEnd.GetHour();
			struData.struTimeEnd.nMin = ctEnd.GetMinute();
			struData.struTimeEnd.nSec = ctEnd.GetSecond();
			struDay.listDate.push_back(struData);			
		}				 			
	}

	// û������.
	if(struDay.listDate.size() == 0)
	{
		return;
	}

	// ��������.
	//DebugTrace("m_MapWnds. insert ");
	WndDataMapIt it = m_MapWnds.find(nWndIndex);
	if(it != m_MapWnds.end())
	{
		it->second.listDate.insert(it->second.listDate.end(), struDay.listDate.begin(), struDay.listDate.end());
	}
	else
	{
		m_MapWnds.insert(WndDataMapValueType(nWndIndex,struDay));
	}

	RecalcLayout();
}

void CPlayTimeCtrl::SetWndData(int nWndIndex,DWORD dwYear,DWORD dwMonth,DWORD dwDay,RETSEARCH *pstruFileInfo,int nFileCnt)
{
	// ɾ��ԭ���Ѿ����ڵļ�¼.
	WndDataMapIt it = m_MapWnds.find(nWndIndex);
	if(it != m_MapWnds.end())
	{
		m_MapWnds.erase(it);
		m_nTimeOffset = 0;
	}	

	if(pstruFileInfo == NULL || nFileCnt == 0)
	{
		RecalcLayout();
		return;
	}
	
	STRU_DAY struDay;
	struDay.struDate.dwYear		= dwYear;
	struDay.struDate.dwMonth	= dwMonth;
	struDay.struDate.dwDay		= dwDay;

	LONGLONG llTimeCnt = 24 * 60 * 60;	// һ��ʱ��.
	CTime ctStart,ctEnd;
	// �õ�ʱ�䷶Χ.
	for(int i = 0; i < nFileCnt; i ++)
	{
		if(strlen(pstruFileInfo[i].createtime) == 0 || pstruFileInfo[i].createtime[0] == 0)
		{
			continue;
		}
//		DebugTrace("SetWndData %d", nFileCnt);
		// ת����ʼ�ͽ���ʱ��.
		ctStart = StrToTime(pstruFileInfo[i].createtime);
		ctEnd = StrToTime(pstruFileInfo[i].finishtime);
		
		if(ctStart > ctEnd)
		{
			CTime ctTemp = ctStart;
			ctStart = ctEnd;
			ctEnd = ctTemp;
		}

		// ʱ���.
		CTimeSpan tmSpan = ctEnd - ctStart;
		// ����ʱ�䳬����ʼʱ��,��Чʱ��.
		LONGLONG llOffsetSec = tmSpan.GetTotalSeconds();
		if(llOffsetSec < 0)
		{
			continue;;
		}

		// ����ʱ�䳬����ʼʱ��1��,��Ч.
		if(llOffsetSec > llTimeCnt)
		{
			continue;
		}

		// �ж������Ƿ�һ��,��һ��Ϊ����.
		if(ctStart.GetDay() == ctEnd.GetDay())
		{
			STRU_DATETIME struData;
			struData.struDate.dwYear = ctStart.GetYear();
			struData.struDate.dwMonth = ctStart.GetMonth();
			struData.struDate.dwDay = ctStart.GetDay();
			struData.struTimeStart.nHour = ctStart.GetHour();
			struData.struTimeStart.nMin = ctStart.GetMinute();
			struData.struTimeStart.nSec = ctStart.GetSecond();

			struData.struTimeEnd.nHour = ctEnd.GetHour();
			struData.struTimeEnd.nMin = ctEnd.GetMinute();
			struData.struTimeEnd.nSec = ctEnd.GetSecond();
			struDay.listDate.push_back(struData);
		}
		else
		{	
			// ����.��ֳ�����ʱ���.
			STRU_DATETIME struData;		
			struData.struDate.dwYear = ctStart.GetYear();
			struData.struDate.dwMonth = ctStart.GetMonth();
			struData.struDate.dwDay = ctStart.GetDay();
			struData.struTimeStart.nHour = ctStart.GetHour();
			struData.struTimeStart.nMin = ctStart.GetMinute();
			struData.struTimeStart.nSec = ctStart.GetSecond();

			struData.struTimeEnd.nHour = 23;
			struData.struTimeEnd.nMin = 59;
			struData.struTimeEnd.nSec = 59;
			struDay.listDate.push_back(struData);

			struData.struDate.dwYear = ctEnd.GetYear();
			struData.struDate.dwMonth = ctEnd.GetMonth();
			struData.struDate.dwDay = ctEnd.GetDay();
			struData.struTimeStart.nHour = 0;
			struData.struTimeStart.nMin = 0;
			struData.struTimeStart.nSec = 0;

			struData.struTimeEnd.nHour = ctEnd.GetHour();
			struData.struTimeEnd.nMin = ctEnd.GetMinute();
			struData.struTimeEnd.nSec = ctEnd.GetSecond();
			struDay.listDate.push_back(struData);			
		}				 			
	}

	// û������.
	if(struDay.listDate.size() == 0)
	{
		DebugTrace("struDay.listDate.size() == 0");
		RecalcLayout();
		return;
	}

	// ��������.
	//DebugTrace("m_MapWnds. insert ");
	m_MapWnds.insert(WndDataMapValueType(nWndIndex,struDay));

	RecalcLayout();
}

// ���ҽ���ļ�������,�������»���.
void CPlayTimeCtrl::RecalcLayout()
{
	//DebugTrace("RecalcLayout");
	CClientDC dc(this);
	CRect rcClient;

	GetClientRect(rcClient);

	if(m_Bitmap.GetSafeHandle())
	{
		m_Bitmap.DeleteObject();
	}

	if (m_MemDC.GetSafeHdc() != NULL)
	{
		m_MemDC.DeleteDC();		
	}

	m_MemDC.CreateCompatibleDC(&dc);
	m_Bitmap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	m_MemDC.SelectObject(m_Bitmap);	

	m_MemDC.SetBkColor(m_clrBackGround);

	DrawTicks(&m_MemDC);
	
	// �������ļ���ʱ���.
	CTime ctStart,ctEnd;
	WndDataMapIt it;
	for(it = m_MapWnds.begin(); it != m_MapWnds.end(); it ++)
	{
		// ���ں�.
		int nWndIndex = it->first;
		list<STRU_DATETIME>::iterator FileIt;
		for(FileIt = it->second.listDate.begin(); FileIt != it->second.listDate.end(); FileIt ++)
		{
			int nStartX = 0;
			int nEndX	= 0;

			int nRet = CalcTimePos(it->second.struDate,*FileIt,nStartX,nEndX);
			if(nRet == 1)
			{
				// ����ʱ�䷶Χ,�����ʱ�䲻�ٴ���.
				//DebugTrace("����ʱ�䷶Χ,�����ʱ�䲻�ٴ���.");
				break;
			}
			else if(nRet == -1)
			{
				// С��ʱ�䷶Χ,����.
				//DebugTrace("С��ʱ�䷶Χ,����");
				continue;
			}
	
			CRect rcWite;
			rcWite.left = nStartX;
			rcWite.top = rcClient.top + m_nGapOffset/2 + m_nEachWndH + m_nGapOffset + (m_nGapOffset+m_nEachWndH)*nWndIndex;
			rcWite.right = nEndX;
			rcWite.bottom = rcWite.top + m_nEachWndH;
			m_MemDC.FillSolidRect(rcWite,m_clrFile);
		}		
	}

	Invalidate();
}

// ���ݵ�ǰ����,���㴫���ʱ������Ӧ��λ��.
// -1: �����ʱ���С�ڵ�ǰ���ڵ�ʱ��η�Χ.
// 0 : �����ʱ����ڵ�ǰ���ڵ�ʱ��η�Χ.
// 1: �����ʱ�����ڵ�ǰ���ڵ�ʱ��η�Χ.
int CPlayTimeCtrl::CalcTimePos(const STRU_DATE &struCurDate,
							   const STRU_DATETIME &struDateTime,
							   int &nStartPos,int &nEndPos)
{
	// ���ǵ����¼�񲻴���.
	if(struDateTime.struDate.dwDay < struCurDate.dwDay)
	{
		return -1;
	}

	if(GetYearDay(struDateTime.struDate.dwYear,struDateTime.struDate.dwMonth, struDateTime.struDate.dwDay) > GetYearDay(struCurDate.dwYear,struCurDate.dwMonth, struCurDate.dwDay))
	{
		return 1;
	}

	// ǰһ���ʱ��,ʱ����ó�00:00:00.
	long lTimeLength = GetTimeLength(m_nType);	// ��ǰʱ���ʱ��.
	if(lTimeLength == -1)
	{
		return -1;
	}
	
	// ����ʱ��.
	long lStart = struDateTime.struTimeStart.nHour * 3600 + struDateTime.struTimeStart.nMin * 60 + struDateTime.struTimeStart.nSec - m_nTimeOffset * lTimeLength;
	long lEnd = struDateTime.struTimeEnd.nHour * 3600 + struDateTime.struTimeEnd.nMin * 60 + struDateTime.struTimeEnd.nSec - m_nTimeOffset * lTimeLength;

	// ��ʼʱ��С�ڽ���ʱ��,��ʼʱ����ڷ�Χ����Сֵ,С�ڷ�Χ�����ֵ.
	if(lStart > lEnd )
	{
		return -1;
	}

	if(lStart <= 0 && lEnd <= 0)
	{
		return -1;
	}

	if(lStart > lTimeLength && lEnd > lTimeLength)
	{
		DebugTrace("TimeLength = %d-%d-%d",lStart ,lEnd ,lTimeLength);
		return 1;
	}

	lStart = max(0,lStart);
	lEnd = min(lEnd,lTimeLength);

	// ���㿪ʼ�ͽ���λ��,�벻����.
	nStartPos = m_nLeftW + m_nGapOffset + m_nEachWndW * lStart/lTimeLength;			
	nEndPos = m_nLeftW + m_nGapOffset + m_nEachWndW * lEnd/lTimeLength;
	// ���,����ƫ��1��λ.
	if(nStartPos == nEndPos)
	{
		nEndPos = nStartPos + 1;
	}

	return 0;
}
int CPlayTimeCtrl::GetYearDay(int y,int m,int d)
{
    const static int dsys[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i=0, re=0;
    for (;i<m-1; i++)
    {
        re+= dsys[i];
    }
    re+=d;
    if(m >2 && (y%4==0 && y%100!=0||y%400==0) )
    {
        re+=1;
    }
    return re;
}


// ��ȡ��ǰλ�ö�Ӧ��ʱ���.
BOOL CPlayTimeCtrl::GetCurrentPointTime(CPoint point,int &nWndIndex,CString &strTime)
{
	nWndIndex = PtInWnd(point);
	if(nWndIndex == -1)
	{
		return FALSE;
	}

	long lTimeLength = GetTimeLength(m_nType);	// ��ǰʱ���ʱ��.
	if(lTimeLength == -1)
	{
		return FALSE;
	}

	int nLength = point.x - m_nLeftW - m_nGapOffset;
	// ���㵱ǰʱ��.
	long lCurrentMinCnt = nLength * lTimeLength /m_nEachWndW;
	if(lCurrentMinCnt > lTimeLength)
	{
		return FALSE;
	}

	// ��ʱ��.
	long lMinCnt = m_nTimeOffset * lTimeLength + lCurrentMinCnt;

	int nHour = lMinCnt / 3600;
	int nMin = lMinCnt % 3600/60;
	int nSec = lMinCnt % 3600%60;

	WndDataMapIt it = m_MapWnds.find(nWndIndex);
	if(it != m_MapWnds.end())
	{
		strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),\
			it->second.struDate.dwYear,it->second.struDate.dwMonth,it->second.struDate.dwDay,\
			nHour,nMin,nSec);

		return TRUE;
	}
	else
	{
		strTime.Format(_T("%02d:%02d:%02d"),nHour,nMin,nSec);

	}

	return FALSE;
}
#if !defined(AFX_PLAYBACK_PANNEL_H__F79F0D7D_1068_4E35_8380_22AE3E322707__INCLUDED_)
#define AFX_PLAYBACK_PANNEL_H__F79F0D7D_1068_4E35_8380_22AE3E322707__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PlaybackWnd.h"

class CPlaybackPannel:public CWnd
{
// Construction
public:
	CPlaybackPannel();

// Implementation
public:
	virtual ~CPlaybackPannel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlaybackPannel)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// ��������(Container)
	BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

public:
	//����nSubû����,������
	int SetShowPlayWin(int nMain);
	CWnd * GetPage(int nIndex);
    int   SetCurrentWnd(int nWndIndex);

	void   SetWndToolTip(int nWndIndex,CString strToolTip);
	CString  GetWndToolTip(int nWndIndex);

	// ˢ��ָ������.
	void InvalidateWnd(int nWndIndex);

public:
	// ���ü����
	void SetActivePage(CWnd *pWnd, BOOL bRepaint = TRUE);	

	///////////////////////////////////////////////////
	//	ȫ����ʾ
	void SetFullScreen(BOOL bFlag);
	BOOL GetFullScreen();

	///////////////////////////////////////////////////
	//	������ʾ
	void SetMultiScreen(BOOL bFlag,BOOL bReSplitWnd = TRUE);
	BOOL GetMultiScreen();

	//////////////////////////////////////////////////
	//	�Զ����ڳߴ�
	void SetAutoAdjustPos(BOOL bFlag);
	BOOL GetAutoAdjustPos();

	void SetPlayPort(int port,int playtype,int windowID) ; //���Ŷ˿ں�

	///////////////////////////////////////////////////
	//	�����Ӵ��ڵ���� �� ��ʾ��Χ ,�õ����ڵ�λ��
	virtual void CalcPageRect(LPRECT lpRect,int nIndex,int nPageCount);

	///////////////////////////////////////////////////
	//	����Ԥ����ı����õ���ʾ����(11/8)
	void AdjustRect(LPRECT lpRect);

	//////////////////////////////////////////////////////////////////////////
	//
	int HitTest(CPoint pt);

public:
	CPlaybackWnd m_wndVideo[MAX_WINDOW];

private:	
	int		m_nLastSplit;
	int		m_nCurPannelIndex;//��ǰ���ں�

	// �����ָ��
	CWnd *m_pActivePage;
	// ȫ�����
	BOOL m_bFullScreen;
	// �������
	BOOL m_bMultiScreen;	
	// �Զ��������
	BOOL m_bAutoAdjustPos;

	CPen m_penSelect;	// ѡ�д��ڻ���.
	CPen m_penNorm;		// δѡ�д��ڻ���.

private:
	//	ȫ��ʱ����ԭ������Ϣ,�����ָ�����
	WINDOWPLACEMENT _temppl;		//window's placement
	CWnd *			_tempparent;	//window's parent
};

#endif 
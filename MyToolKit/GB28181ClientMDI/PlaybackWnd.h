#if !defined(AFX_PLAYBACKWND_H__E6AAF690_8D19_43AC_AE4E_E64F2412D706__INCLUDED_)
#define AFX_PLAYBACKWND_H__E6AAF690_8D19_43AC_AE4E_E64F2412D706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayWnd.h : header file
//

/////////////////////////
//	POPUP MENU ID DEFINE

#define		VIDEO_MENU_BASE				WM_USER + 1979
#define		VIDEO_MENU_END				WM_USER + 1988
#define		VIDEO_MENU_FULLSCREEN		WM_USER + 1979
#define		VIDEO_MENU_MULTISCREEN		WM_USER + 1980
#define		VIDEO_MENU_AUTOADJUST		WM_USER + 1981
#define		VIDEO_MENU_RECORDVIDEO		WM_USER + 1982
#define		VIDEO_MENU_PRINTSCREEN		WM_USER + 1983
#define		VIDEO_MENU_EXITDECODE		WM_USER + 1984
#define		VIDEO_MENU_EXITCYCLE		WM_USER + 1985
#define		VIDEO_MENU_CAPTUREPIC		WM_USER + 1986
#define		VIDEO_MENU_TRECORDVIDEO		WM_USER + 1987
#define		VIDEO_MENU_ZOOMVIEW  		WM_USER + 1988

//	KeyColor

//#define		VIDEO_BACK_COLOR	RGB(111,104,160)
#define		VIDEO_BACK_COLOR	RGB(10,10,10)

/////////////////////////////////////////////////////////////////////////////
// CPlaybackWnd dialog

class CPlaybackWnd : public CWnd
{
// Construction
public:
	CPlaybackWnd();   // standard constructor


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaybackWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	afx_msg void OnVideoMenu(UINT nID);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlaybackWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	afx_msg LRESULT OnUserRecordFileComm(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserRecordFileData(WPARAM wParam, LPARAM lParam);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetWinID(int ID) {m_nWndID = ID;}
	int  GetWinID(void){return m_nWndID;}
	short m_playport,m_playtype,m_playwindowID;
	BOOL m_bPlaying;
     ////
	void SetPenBrush(CDC *pDC,bool bTransparent);
	void ReSetPenBrush(CDC *pDC);
	void InvertShape(CDC *pDC,RECT rect,bool bInvert);

	void SetTooltipText(CString strText);
	CString GetTooltipText() { return m_strToolTip; }

	void OnPlay();
	void OnStop();
	void OnPause();

	void StartPlay();
	void StopPlay();

	void SearchFile(sipd_catalog_item *  pItem);

	CString			m_strToolTip;		// ��ʾ��Ϣ.
protected:
	void InitToolTip();

public:
	BOOL		    m_bPause;			// ��ͣ �� ��֡������ ����״̬
	BOOL            bOnebyone;			// ��֡����.
	BOOL            bRecordfile;		// �Ƿ���¼��״̬
	BOOL            bVoice;				// �Ƿ����Ƶ
	short           nSpeed;				// �ط��ٶȿ���

	sipd_catalog_item m_catalog_item;	

	vector<RETSEARCH> m_listFiles;		// ����Ӧ���ļ���Ϣ

	int		m_play_port;		//	���������
	int		m_net_port;			//	���������
	

private:
	BOOL m_bFullScreen;
	int m_nWndID;
	int m_nPreSplit;

	CPoint	g_ptDown;	//�����λ��
	CPoint  g_ptUp;		//�����λ��
	RECT    g_rcMove;
	CRect   g_rcLast,ChangeRect;
	BOOL	m_bMouseMove;	//����ƶ�
	BOOL    m_GetPicFlag;   //ȡͼ���С��ʶ
	BOOL	g_bZoom;	//�����Ѿ��Ŵ�
	RECT    m_rcOldZoom;//����ǰһ�εĵ�λ��Ϣ
	LONG    m_width,m_height;//���ش�С
	BYTE    m_dragsum;       //�Ŵ����ͳ��

	///// 
	CBrush *m_pBrushOld;
	BOOL m_bZoomView;

	CToolTipCtrl	m_ToolTipWnd;
	
	BOOL			m_bActivateToolTip;	// .

public:
	afx_msg void OnDestroy();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYWND_H__E6AAF690_8D19_43AC_AE4E_E64F2412D706__INCLUDED_)

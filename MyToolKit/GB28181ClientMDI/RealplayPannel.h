#if !defined(AFX_REALPLAY_PANNEL_H__F79F0D7D_1068_4E35_8380_22AE3E322707__INCLUDED_)
#define AFX_REALPLAY_PANNEL_H__F79F0D7D_1068_4E35_8380_22AE3E322707__INCLUDED_

#include "RealplayWnd.h"

class CRealplayPannel : public CWnd
{
// Construction
public:
	CRealplayPannel();

// Implementation
public:
	virtual ~CRealplayPannel();
	// Generated message map functions
protected:
	//{{AFX_MSG(CRealplayPannel)
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetWndPos(int npos);
	BOOL SetShowPlayWin(int nMain);

	// ���ü����
	void SetActiveWnd(CRealplayWnd *pWnd,BOOL bRePaint = FALSE);

public:
	// ��������(Container)
	BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

	//	ȫ����ʾ
	void SetFullScreen(BOOL bFlag);
	BOOL GetFullScreen();

	//	������ʾ
	void SetMultiScreen(BOOL bFlag);
	BOOL GetMultiScreen();

	//	�����Ӵ��ڵ���� �� ��ʾ��Χ ,�õ����ڵ�λ��
	void CalcPageRect(LPRECT lpRect,int nIndex,int nPageCount);

	int HitTest(CPoint pt);

public:
	CRealplayWnd m_wndVideo[MAX_WNDNUM];
	int nLastSplit;
	int m_nCurWnd;
	int m_nWindowNum;

	

	// ȫ�����
	BOOL m_bFullScreen;
	///////////////////////////////////////////////////
	// �����ָ��
	CRealplayWnd *m_pActivePage;
	///////////////////////////////////////////////////
	// �������
	BOOL m_bMultiScreen;
	//	ȫ��ʱ����ԭ������Ϣ,�����ָ�����
	WINDOWPLACEMENT _temppl;		//window's placement
	CWnd *			_tempparent;	//window's parent
};

#endif
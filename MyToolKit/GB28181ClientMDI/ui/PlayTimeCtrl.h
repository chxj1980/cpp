#ifndef __PLAYTIMECTRL__
#define __PLAYTIMECTRL__

/////////////////////////////////////////////////////////////////////////////
// CPlayTimeCtrl window
#include <map>
#include <list>
using namespace std;


#define WM_PLAYTIME_LBUTTONDBLCLK		WM_USER + 9423

// ��ǰʱ���Ҫ��ʾ������.
enum
{
	_TIME_DAY	= 0,	// ����.
	_TIME_HOUR2,		// ��Сʱ.
	_TIME_HOUR1,		// 1Сʱ.
	_TIME_MIN30			// 30��.
};

// ������.
typedef struct _STRU_DATE
{
	DWORD dwYear;
	DWORD dwMonth;
	DWORD dwDay;

	_STRU_DATE()
	{
		dwYear = 1970;
		dwMonth = 1;
		dwDay = 1;
	}
}STRU_DATE,*LPSTRU_DATE;

// ʱ����.
typedef struct _STRU_TIME
{
	short nHour;
	short nMin;
	short nSec;

	_STRU_TIME()
	{
		nHour = 0;
		nMin = 0;
		nSec = 0;
	}
}STRU_TIME,*LPSTRU_TIME;

//������ʱ����.
typedef struct _STRU_DATETIME
{	
	STRU_DATE struDate;
	STRU_TIME struTimeStart;	// ��ʼʱ��.
	STRU_TIME struTimeEnd;		// ����ʱ��.

}STRU_DATETIME,*LPSTRU_DATETIME;

typedef struct _STRU_DAY
{
	STRU_DATE struDate;

	list<STRU_DATETIME> listDate;	// ������Чʱ��.

	_STRU_DAY()
	{
		listDate.clear();
	}

}STRU_DAY,*LPSTRU_DAY;

enum
{
	_TYPE_BTN_ = 0,	// ��ť.
	_TYPE_TEXT_,	// �ı�.
};

// ��ť��Ϣ.
typedef struct _STRUBTN{
	UINT    uBtnID;		// ��ťID.
	HRGN	hRgn;		// ��ť����.
	CString strText;	// �ı�.
	CString strToolTip;	// ��ť��ʾ�ı�.
	int		nType;		// ����.

	_STRUBTN()
	{
		nType		= _TYPE_BTN_;
		uBtnID		= -1;
		hRgn		= NULL;
		strText		= _T("");
		strToolTip	= _T("");
	}
}STRUBTN,*LPSTRUBTN;

// �������ڶ�Ӧ������.
typedef std::map<int,STRU_DAY> WndDataMap;
typedef WndDataMap::iterator WndDataMapIt;
typedef WndDataMap::value_type WndDataMapValueType;

// ��ť�ľ�����Ϣ.
typedef std::map<UINT,STRUBTN> BtnsMap;
typedef BtnsMap::iterator BtnsMapIt;
typedef BtnsMap::value_type BtnsMapValueType;

class CPlayTimeCtrl : public CWnd
{
public:
	CPlayTimeCtrl();
	virtual ~CPlayTimeCtrl();

	//{{AFX_VIRTUAL(CPlayTimeCtrl)
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

public:	
	void InvalidateCtrl();
	void RecalcLayout();

	// ���ָ�����ڵ�ʱ��.[����ڲ�ʱ��]
	void ClearWnd(int nWndIndex);

	// ���ö�Ӧ���ڵ��ļ�ʱ��.
	void SetWndData(int nWndIndex ,DWORD dwYear,DWORD dwMonth,DWORD dwDay,RETSEARCH *pstruFileInfo ,int nFileCnt);
	void AddWndData(int nWndIndex ,DWORD dwYear,DWORD dwMonth,DWORD dwDay,RETSEARCH *pstruFileInfo ,int nFileCnt);

	void SetCurWndText(CString strCurWndText);
protected:	
	void DrawTicks(CDC* pDC);
	// ���Ƶײ����ư�ť��.
	void DrawBottomBtn(CDC *pDC,CRect rect);

protected:
	void InitToolTips();

	// ����������ڴ����±�. 
	// ��0��ʼ,ʧ�� -1.������Ҳ����-1.
	int  PtInWnd(CPoint point);

	// ��������Ƿ��ڰ�ťλ����.
	int PtInBtns(CPoint point,CString &strToolTip);

	// �����ť��Դ.
	void ClearBtns();

	// ��ȡ֧�ֵ�ʱ�䳤��.��ȷ����.
	// bCalcSec TRUE ���㵽��,FALSE ���㵽��.
	// ����ֵ -1 ��֧��.
	// ����0.
	long GetTimeLength(int nType,BOOL bCalcSec = TRUE);

	// ��ȡһ������ܲ�ֳɶ��ٸ�ʱ���.
	int GetTimeOffsetSupportCnt(int nType);

	// ��ȡһ��ʱ���Ҫ��ֵĸ���.
	// ��ʾȫ����������ҵ�һ����ʱ��ε��������,
	int GetSplitCnt(int nType);

	// ���ݵ�ǰ����,���㴫���ʱ������Ӧ��λ��.
	// -1: �����ʱ���С�ڵ�ǰ���ڵ�ʱ��η�Χ.
	// 0 : �����ʱ����ڵ�ǰ���ڵ�ʱ��η�Χ.
	// 1: �����ʱ�����ڵ�ǰ���ڵ�ʱ��η�Χ.
	int CalcTimePos(
		const STRU_DATE &struCurDate,
		const STRU_DATETIME &struDateTime,
		int &nStartPos,int &nEndPos);

	int GetYearDay(int y,int m,int d);//��ȡĳ����һ���еĵڻ���
	// ��ȡ��ǰλ�ö�Ӧ��ʱ���.
	// ����������ڴ���λ��,�Լ���Ӧʱ�����Ϣ.
	// point ���λ��.
	// strTime ��Ӧ��ʱ���.
	BOOL GetCurrentPointTime(CPoint point,int &nWndIndex,CString &strTime);
	
protected:
	//{{AFX_MSG(CPlayTimeCtrl)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CToolTipCtrl	m_ToolTip;

	CDC				m_MemDC;
	CBitmap			m_Bitmap;

protected:
	BtnsMap			m_MapBtns;		// ���а�ť��Ϣ.
	WndDataMap		m_MapWnds;		// ���д��ڵ��ļ�����..

protected:
	int			m_nType;			// ��ǰ��ʾ������.
	int			m_nTimeOffset;		// ʱ��ƫ��.
	int			m_nCtrlType;		// ���ư�ť����.

protected:
	COLORREF	m_clrGapUp;			// �ϰ벿�����ɫ.
	COLORREF	m_clrGapDown;		// �°벿�����ɫ.
	COLORREF	m_clrBackGround;	// ������ɫ.

	COLORREF	m_clrFile;			// �ļ���ɫ.

	COLORREF	m_clrText;			// �ı���ɫ.

	COLORREF    m_clrBtnNorm;		// ��ť������ɫ.
	COLORREF	m_clrBtnSelect;		// ��ťѡ����ɫ.

	int			m_nWndCnt;			// ���ڸ���.
	int			m_nLeftW;			// ���Ԥ����.
	int			m_nEachWndH;		// ÿ�����ڸ߶�.
	int			m_nEachWndW;		// ÿ�����ڵĿ��.
	int			m_nGapOffset;		// �����С.

	int			m_nEachHourW;		// ������λռ�Ŀ��.	

	CString		m_strCurWndText;	// ��ǰ����Ҫ��ʾ���ı�.
	CString     m_strMouseMoveTm;	// �����ʱ�����ϵ��ı�.

private:
	BOOL        m_TipFlag;
};

/////////////////////////////////////////////////////////////////////////////
#endif

#pragma once

#include "PlayTimeCtrl.h"
#include "SkinWnd.h"
#include "PlaybackPannel.h"

#define IDC_SCREENPANNEL	    1015	// ���Ŵ���.
#define IDC_CTRLWNDTIME         1016	// ʱ����ؼ�ID.
#define IDC_CTRLBTNS			1017	// ��ť������ID.
#define IDC_PLAY_VOICE          1021	// ������.
#define IDC_PLAY_VOICE_CLOSE    1022	// �ر�����.
#define IDC_PLAY_PLAY           1023	// ����.
#define IDC_PLAY_PAUSE          1024	// ��ͣ.
#define IDC_PLAY_STOP           1025	// ֹͣ.
#define IDC_PLAY_FRAME          1026	// ��֡.
#define IDC_PLAY_PIC            1027	// ��ͼ.
#define IDC_PLAY_REC            1028	// ¼��.
#define IDC_PLAY_REC_STOP       1029	// ֹͣ¼��.
#define IDC_PLAY_DOWN           1030	// ����.
#define IDC_ONEPAN              1032	// ������.
#define IDC_FOURPAN             1033	// �Ļ���.
#define IDC_FULLPAN             1034	// ȫ��.
#define IDC_SLIDER_SPEED        1036	// �ٶȻ���.
#define IDC_SLIDER_SPEED_TEXT   1037	// �ٶ��ı�����.
#define IDC_HIDE_PLAYCTRL       1038	// ����ʱ����.
#define IDC_SHOW_PLAYCTRL       1039	// ��ʾʱ����.
#define IDC_FIND				1040	// ����.
#define IDC_DEVICE_TYPE			1041	// �豸����.
#define IDC_DATATIME			1042	// ʱ��.

#define IDC_PLAY_SEPBMP1        1050	// �ָ�ͼƬ.
#define IDC_PLAY_SEPBMP2        1051	// �ָ�ͼƬ.
#define IDC_PLAY_SEPBMP3        1052	// �ָ�ͼƬ.

#define BUFFER_SIZE  1024*1024
#define FILESTREAM   1



// CPlaybackView ������ͼ

class CPlaybackView : public CFormView
{
	DECLARE_DYNCREATE(CPlaybackView)

	friend class CPlaybackWnd;
protected:
public:
	CPlaybackView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPlaybackView();

public:
	enum { IDD = IDD_PLAYBACKVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	int		m_nCurWndIndex;		// ��ǰ���ں�
	int		m_nSearchTimeMod;

protected:
	void CreateSkinBtns();		// ������ť��.

	void AutoRecalcLayout();	// �Զ�������ť���С.	


	BOOL ShowPlayCtrlTime(BOOL bShow);// ��ʾ/����ʱ����.

	// �����޲�����ť״̬.
	void SetNormBtns();
	// ���õ�ǰ���ڵİ�ť״̬.
	void SetCurWndBtns(int nWndIndex);	

	// ���ý��水ť״̬.
	// TRUE ���� / FALSE ��ͣ.
	void SetBtnsPlay(BOOL bPlay);
	// ���ý��水ť״̬.
	// FALSE ¼�� / TRUE ֹͣ¼��.
	void SetBtnsRecord(BOOL bRecord,BOOL bEnable = TRUE);
	// ���ý��水ť״̬.
	// TRUE �ر����� / FALSE ������.
	void SetBtnsSound(BOOL bSound);
	// ���ý��滬��λ��.
	void SetBtnSpeed(int nPos);

	void OnOnePannel();
	void OnFourPannel();
	void OnFullScreenPannel();

	void SetCurrentWnd(int nWndIndex);	// ���õ�ǰ���ں�.
	int  GetCurrentWnd();				// ��ȡ��ǰ���ں�.

	BOOL RecalcDlg();			// ���²��ֵ�ǰ�Ի���.


private:
	CPlaybackPannel	m_screenPannel;		//������Ļ�װ壭�Ӵ���

	CPlayTimeCtrl	m_CtrlPlayTime;		// ʱ����.
	CSkinWnd		m_SkinBtns;			// ��ť��.

	int				m_nSkinBtnsH;		// ��ť��߶�.
	int				m_nCtrlPalyTimeH;	// ʱ����߶�.

	BOOL			m_bShowCtrlPlay;	// �Ƿ���ʾʱ����.

	COleDropTarget	m_CTreeDropTarget;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg LRESULT OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEventSelWnd(WPARAM wParam,LPARAM lParam);//�޸������ò���	
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
};



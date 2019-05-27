#pragma once

#include "BaseMessageView.h"

// CBaseMatlabView ��ͼ

class CBaseMatlabView : public CBaseMessageView
{
	DECLARE_DYNCREATE(CBaseMatlabView)

protected:
public:
	CBaseMatlabView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBaseMatlabView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

protected:
	HWND	m_plotH;
	int		m_windowInMatlab;				//	matlab �д��ڵı�ʶ;	
	bool	m_bCalculating;	
	static int g_windowInMatlab;			//	��������matlab �д��ڵ�Ψһ��ʶ
public:
	virtual void OnInitialUpdate();

	virtual void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual void Startup(){};
	virtual void PostFocusChanged();
	afx_msg void OnDestroy();
};




// GB28181ClientMDI.h : GB28181ClientMDI Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CGB28181ClientMDIApp:
// �йش����ʵ�֣������ GB28181ClientMDI.cpp
//

class CMvDocTemplate : public CMultiDocTemplate
{
public:
	CMvDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

	virtual ~CMvDocTemplate(){}

	CRuntimeClass * GetCurrView(){return m_pViewClass;}
};

class CGB28181ClientMDIApp : public CWinAppEx
{
public:
	CGB28181ClientMDIApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	CDocTemplate* GetCurrDocTemplate(CView * pView);

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGB28181ClientMDIApp theApp;

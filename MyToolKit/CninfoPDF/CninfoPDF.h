
// CninfoPDF.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCninfoPDFApp:
// �йش����ʵ�֣������ CninfoPDF.cpp
//

class CCninfoPDFApp : public CWinAppEx
{
public:
	CCninfoPDFApp();

// ��д
	public:
	virtual BOOL InitInstance();

	CWinThread * StartWorkerThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

// ʵ��

	DECLARE_MESSAGE_MAP()



};

extern CCninfoPDFApp theApp;

// KeyGenerator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKeyGeneratorApp:
// �йش����ʵ�֣������ KeyGenerator.cpp
//

class CKeyGeneratorApp : public CWinAppEx
{
public:
	CKeyGeneratorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKeyGeneratorApp theApp;
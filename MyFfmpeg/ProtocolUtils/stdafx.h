// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif


#include <stdio.h>
#include <tchar.h>



#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

#include <atlbase.h>
#include <atlutil.h>				//	���� CString

#include "StandardInc.hpp"
#include "Log4cplusInc.hpp"

#include "../FfplaySdl2Pure/media_def.h"


#include "ProtocolUtils.h"

extern BufferManager g_BufferMgr;
extern UsageEnvironment * g_pUsageEnvironment;

extern string	g_strDevsn;
extern int		g_nChannel;
extern string	g_strServerIP;
extern int		g_nServerPort;

// TODO: reference additional headers your program requires here

extern int SearchTag2(unsigned char * pBuffer, int begin, int dwBufSize, int & next);
extern char* strDup(char const* str);
extern int gettimeofday(struct timeval* tp, int* /*tz*/);

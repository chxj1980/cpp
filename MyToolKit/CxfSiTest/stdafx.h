
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include "sipd_def.h"

#include "StandardInc.hpp"

#include "mxml.h"

#pragma warning(disable : 4996)

#include "CatalogTree.h"
#include "Log4cplusInc.hpp"
#include "UsageEnvironment.h"

typedef bool Boolean;

#define False false
#define True true

#ifdef WIN32
#define snprintf _snprintf
#endif

extern	string	g_strLocalIP;
extern	string	g_strLocalDomainID;

class sipd_sdp_info
{
public:
	int did; /*��ʵʱ/�ط�/�������ӵĻỰ��ʶ*/
	int tid; /*��Ӧ���ӵ�sip����id*/
	int cid;	/* call id */

	/*ý�巢�����豸ID��ţ���IPC��DVR�豸���*/
	string  media_sender_or_receiver_id;

	/*ý����������IP��ַ����*/
	enum SIPD_IPType media_send_or_receive_ip_type;

	/*ý����������IP��ַ*/
	string media_send_or_receive_ip;

	/*ý����������RTP�˿ں�*/
	int  media_send_or_receive_port;

	string ssrc;
};

extern char* strDup(char const* str) ;
extern Logger  getDynamicLogger(string strLoggerName);
extern int Pcre2Grep(string patternStr,string subjectStr, vector<string> & vecMatch);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



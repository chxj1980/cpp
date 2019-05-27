
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


#include <vector>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std; 

#include "jmutex.h"
#include "jmutexautolock.h"

#include <iconv.h>

//	���ݿ��ȡ
#include "soci.h"
#include "soci-mysql.h"
#include "test/common-tests.h"

using namespace soci;
using namespace soci::tests;

// xml ����
#include "expat.h"
#include "XmlParser.h"


//	��������
#define PCRE2_CODE_UNIT_WIDTH 8
#define PCRE2_STATIC

#include "pcre2.h"

#include "MessageString.h"
#include "MyDialog.h"

#include "podofo\podofo.h"
#include <cstdio>

using namespace PoDoFo;


//#include "friso_API.h"
#include "friso.h"



class CPdfCatalog
{
public:
	string	strName;	//	Ŀ¼����
	int		nPage;		//	ҳ��
	string	strContent;	//	
};



class CLineOrCell{
public:
	double	x;
	double	y;
	double	font_size;
	string	font_name;
	double	trender;

	PdfRect rect;
	string	content;

	int		parent;			//	�����
	double	max_right_x;	//	����Ƕ��䣬�򱣴������ұ� x ����
	double	last_right_x;	//	����Ƕ��䣬�򱣴���ĩ���ұ� x ����
	double	last_x;			//	����Ƕ��䣬�򱣴���ĩ����� x ����

	CLineOrCell()
	{
		rect.SetBottom(0);
		rect.SetLeft(0);
		rect.SetWidth(0);
		rect.SetHeight(0);

		parent = -1;	
		trender = 0.0;
	}


	bool operator == (const CLineOrCell &otherData)
	{
		return false;
	}

	bool operator <  (const CLineOrCell & otherData) const
	{
		return false;
	}
};


#define MYSQL_POOL_SIZE		1
#define WM_USER_LOG_1		WM_USER + 1



extern connection_pool g_MysqlPool;


extern friso_t		g_friso;
extern friso_config_t g_config;

//////////////////////////////////////////////////////////////////////////

extern BOOL sendToOutput(LPCTSTR lpch,  HWND hwnd = NULL, int logType = WM_USER_LOG_1);

extern int gettimeofday(struct timeval*, int*);

extern double String2Double(string str);
extern string String2Currency(string val);
string Double2Currency(double val, bool isInteger=false);
extern string Double2String(double db, string strFormat="");
extern string Int2String(int num, string strFormat="");
extern string Gbk2Utf8(string strGBK);
extern string Utf8_GBK(string strUtf8);
extern string Utf8_GBK_(char * strUtf8);
extern int Pcre2Grep(string patternStr,string subjectStr, vector<string> & vecMatch, vector<int> & vecOffset);
extern int Pcre2Split(string patternStr,string subjectStr, vector<string> & vecSplit);
extern bool  Pcre2Find(string strSrc, string strPattern);

extern UINT AutoDownloadThreadFunc(LPVOID param);
extern string ReplaceChar(string src, char target_char, string replce_char);
extern string FindLastString(string src, string target_string, int & nLastPosition);
extern string trimString(string  str );
extern string ReplaceString(string src, string target_string, string replace_string);
extern void splitString(string s, string dim, vector<string>& resultVector);
extern int RandomFromRange(int nMin, int nMax);
extern int CheckProcessOnlyOne(const char *name);

extern int UTF8ToGBK(unsigned char * lpUTF8Str,unsigned char * lpGBKStr,int nGBKStrLen);
extern int UnicodeToGBK(wchar_t * lpUnicodeStr, unsigned char * lpGBKStr,int nGBKStrLen);

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



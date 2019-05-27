
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


#include "StandardInc.hpp"
#include "Log4cplusInc.hpp"

#include "jmutex.h"
#include "jmutexautolock.h"

#include "FfplaySdl2Pure.h"
#include "Dll28181_Layer.h"

#include "ToolPic.h"
#include "Label.h"

typedef unsigned char  uint8_t;
typedef signed __int64   int64_t;
typedef unsigned __int64 uint64_t;

typedef struct H264_PARAM
{
	uint8_t head[8];	//��ͷ8���ַ�A       8 
	int  version;		//�汾				 4	 ����Ϊ1��Ϊ��֡�ʲ��ţ��汾��Ϊ2��Ϊ��ʱ�������	
	int64_t idx;		//����				 8
	int  knd;			//0=H264��Ƶ��1=G711.A(1ch,8k,16bit)	 2=unsigned pcm(1ch,8k,8bit)  3=G711 ulaw(1ch,8k,16bit)				
	int  fbs;			//֡�ʻ������		 4			
	time_t curtime;		//������ʱ��		 8
	int ptsSetup;		//pts����ֵ			 4	
	int dtsSetup;		//dtsSetup			 4
	u_int64 pts;        //pts��Ϣ            8
	int64_t dts;        //dts��Ϣ			 8	
	int  nal_len;		//����������		 4	

	H264_PARAM(){
		version=1;
		for(int i=0;i<8;i++) head[i]=0x41;
		pts = -1;
		dts = -1;
		knd =-1;
	}

}H264_PARAM;

//  "172.26.84.182"

#define LOCAL_DOMAIN_ID			"34020000002020000001"
#define LOCAL_IP				"10.18.72.35"
#define	LOCAL_PORT				7100

#define REMOTE_DOMAIN_ID		"340200000020200002"
//#define REMOTE_IP				"10.18.73.120"
//#define REMOTE_IP				"10.18.72.201"
#define REMOTE_IP				"10.18.72.231"
#define	REMOTE_PORT				5062


#define WM_USER_CATALOG_COMM	WM_USER + 1
#define WM_USER_CATALOG_DATA	WM_USER + 2
#define WM_USER_CALL_RESP		WM_USER + 3	

#define WM_USER_RECORDFILE_COMM	WM_USER + 4
#define WM_USER_RECORDFILE_DATA	WM_USER + 5


//////////////////////////////////////////////////////////////////////////
//	���� playback ���� client �ؼ� 

#define MAX_WINDOW 4		// �ط���ͼʹ��
#define MAX_WNDNUM 25		// Ԥ����ͼʹ��
#define MAX_FILECNT 1024	// ���֧���ļ����ҵ�����.

#define NVRTYPE     1	//Զ�̲��ţ���ý����ǰ忨Զ�̲��ŵ�ʱ������ã�
#define DVRTYPE     2	//DVRԶ�̲����ļ�
#define LOCALTYPE   3	//�����ļ�����
#define BRSTYPE     4	//��ŵԶ�̲���

#define PARA_STEP			26	// ע��Ŀǰֻ����,����/25.5 ��ȡ������+1����������ԭ��ֵ.
#define VOLUME_STEP			1320

//����ָ�����
enum{
	SPLIT1 = 0,
	SPLIT4,
	SPLIT9,
	SPLIT16,
	SPLIT25,	
	SPLIT36,	
	SPLIT49,	
	SPLIT64,	
	SPLIT_TOTAL
};


#define  WM_EVENT_START	  		    WM_USER+100
#define  WM_EVENT_CHANGE_PARA		WM_EVENT_START+1	//�޸Ŀ�ʼ������ʱ��,���Ͱ��Ĵ�С
#define  WM_EVENT_RUN_CMD		    WM_EVENT_START+2	//ִ������
#define  WM_EVENT_SEL_WND		    WM_EVENT_START+3	//���ѡ�񴰿�
#define  WM_USER_NOTIFY_PLAYSTATUS  WM_EVENT_START + 4	// ֪ͨ��ҳ����״̬�ı�.

struct  DOWNLOADPARA
{
	CTime  BeginTime;   //��ʼʱ��
	CTime  EndTime;     //����ʱ��
	LONG   FileTotleSize;//�ļ�����Ĵ�С
};

// �ط�״̬.
enum
{
	_STATUS_STOP = 0,
	_STATUS_PLAY,
	_STATUS_PAUSE,
};


/*���ڸ�ʽ*/
struct  LDATETIME
{
	short dwYear;		//��
	BYTE dwMonth;		//��
	BYTE dwDay;			//��
	BYTE dwHour;		//ʱ
	BYTE dwMinute;		//��
	BYTE dwSecond;		//��
};

//�ļ���Ϣ�ṹ��
struct   RETSEARCH	{
	char  createtime[20];//�ļ�����ʱ�� 16
	char  finishtime[20];//�ļ�����ʱ�� 16
	char  fileName[256];  //�ļ�����
	long  totalsize; //�ļ���С
};



BOOL DebugTrace(char * lpszFormat,...);
void CTimeToLDateTime(const CTime &ctTm,LDATETIME &struTm);
CTime StrToTime(char *str);
void convert_to_utc(const char *cSource,char *cDest);

//////////////////////////////////////////////////////////////////////////

extern JMutex			g_mtxNet;
extern map<int, HWND>	g_mapNet2Hwnd;
extern map<int, int>	g_mapNet2Player;
extern Logger  g_Logger;



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



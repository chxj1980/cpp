// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#define WIN32_LEAN_AND_MEAN

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "sipd_def.h"

#include "StandardInc.hpp"

#include "mxml.h"

#pragma warning(disable : 4996)


#include "Log4cplusInc.hpp"
#include "UsageEnvironment.h"

#include "./jthread/jmutexautolock.h"

using namespace jthread;

class sipd_sdp_info
{
public:
	int did; /*��ʵʱ/�ط�/�������ӵĻỰ��ʶ*/
	int tid; /*��Ӧ���ӵ�sip����id*/
	int	cid;

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

typedef bool Boolean;

#define False false
#define True true

#ifdef WIN32
#define snprintf _snprintf
#endif


extern	string	g_strLocalIP;
extern	string	g_strDBAddr;
extern	int		g_iRtpPort;
extern	string	g_strLocalDomainID;

extern	Logger	g_logger;
extern	string	g_strCurrentDir;

extern char* strDup(char const* str) ;
extern bool ReadCfg(string fullpath);
extern Logger  getDynamicLogger(string strLoggerName);
extern int Pcre2Grep(string patternStr,string subjectStr, vector<string> & vecMatch);



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

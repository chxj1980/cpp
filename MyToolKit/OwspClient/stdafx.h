// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once


#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "StandardInc.hpp"
#include "Log4cplusInc.hpp"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

#include <atlbase.h>
#include <atlutil.h>				//	���� CString

#include "jmutexautolock.h"

#include "owsp_def.h"


typedef bool Boolean;
typedef long int64_t;

#define False false
#define True true

enum IOType 
{
	IOInitialize, // The client just connected
	IORead, // Read from the client. 
	IOReadCompleted, // Read completed
	IOWrite, // Write to the Client
	IOWriteCompleted, // Write Completed.
	IOZeroByteRead, // Read zero Byte from client (dummy for avoiding The System Blocking error) 
	IOZeroReadCompleted, // Read Zero Byte  completed. (se IOZeroByteRead)
	IOTransmitFileCompleted, //TransmitFileCompleted.
	IOPostedPackage, // Used to post Packages into IOCP port. 

	IOCommand,		//	��Ӧ AbstractCommand ����
};

// Determines the size of the first bytes who tells you how big the message are. (pakage heap)  
#define MINIMUMPACKAGESIZE sizeof(UINT)
#define MAXIMUMPACKAGESIZE 65536 /*14600*/ /*512*/
#define MAXIMUMSEQUENSENUMBER 5001

#include "IOCPBuffer.h"
#include "BufferManager.h"

#include "AbstractCommand.h"
#include "DelayQueue.h"
#include "UsageEnvironment.h"
#include "Medium.h"
#include "BaseClient.h"

#include <json/json.h>

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

enum {
	RESULT_CODE_SERVER_PRIMARY = 2,
	RESULT_CODE_SERVER_SLAVE = 1,
	RESULT_CODE_OK = 0,
	RESULT_LOGON_ALREADY = -1,				//	�û��ѵ�½
	RESULT_LOGON_DOG_EXPIRED = -2,			//	���ܹ�����
	RESULT_LOGON_DOG_CHECK_FAIL = -3,		//	���ܹ����ʧ��
	RESULT_LOGON_DOG_USER_EXCEEDING = -4,		//	�û���������

	RESULT_CODE_SERVER_CONNECTION_ERR = -5,	//	����ʧ��
	RESULT_CODE_LOCAL_PARAMETER_ERR = -6,	//	��¼��������
	RESULT_CODE_SERVER_NOT_FOUND = -7,		//	��������δ�ҵ�
	RESULT_CODE_SERVER_NOT_LOGON = -8,		//	δ��¼
	RESULT_CODE_SERVER_UNKOWN = -9,			//	δ֪����
	RESULT_CODE_SERVER_ERR = -10,
	RESULT_CODE_SERVER_TIMEOUT = -11,		//	��ʱ
	RESULT_CODE_MEMORY_ERR = -12,
	RESULT_CODE_SERVER_ALREADY_LOGON = -13,	//	�Ѿ���¼����
	RESULT_CODE_LOCAL_ERR = -14

};



extern BufferManager g_BufferMgr;
extern UsageEnvironment * g_pUsageEnvironment;

extern string	g_strDevsn;
extern int		g_nChannel;
extern string	g_strServerIP;
extern int		g_nServerPort;

extern Logger	g_Logger;

extern char* strDup(char const* str);
extern Logger  getDynamicLogger(string strLoggerName);
extern int gettimeofday(struct timeval* tp, int* /*tz*/);
extern bool ReadCfg();
extern void splitString(string s, string dim, vector<string>& resultVector);
extern string NowTime();
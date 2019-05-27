#include "MyException.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include  <dbghelp.h>


#pragma comment(lib,  "dbghelp.lib")

///����Dump�ļ�
void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)  
{  
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  

	// Dump��Ϣ  
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;  
	dumpInfo.ExceptionPointers = pException;  
	dumpInfo.ThreadId = GetCurrentThreadId();  
	dumpInfo.ClientPointers = TRUE;  

	// д��Dump�ļ�����  
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);  

	CloseHandle(hDumpFile);  
}  

LONG WINAPI CrashHandler(EXCEPTION_POINTERS *pException)
{
	char cPath[256]={0};
	sprintf(cPath,"./crash.dmp");

	CreateDumpFile(cPath, pException);

	//MessageBox(NULL, _T("������Ҫ�����ˣ�ʬ���ڣ�deathbody.dmp"), _T("̯�ϴ�����"), MB_OK);

	return EXCEPTION_CONTINUE_SEARCH;
}

void SetMyException()
{
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashHandler);// ����δ�����쳣�Ĵ�����
}
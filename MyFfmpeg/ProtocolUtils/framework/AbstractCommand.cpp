#include "StdAfx.h"
#include "AbstractCommand.h"

AbstractCommand::AbstractCommand(void)
{
	hSempaphore = CreateSemaphore(NULL, 0, 1, NULL );
}

AbstractCommand::~AbstractCommand(void)
{
	CloseHandle(hSempaphore);
}


void AbstractCommand::CommandExecute(UsageEnvironment* pThis)
{
	Execute(pThis);
	//	����ִ����ɺ󣬷���֪ͨ
	ReleaseSemaphore(hSempaphore, 1, NULL);
}

void AbstractCommand::CommandWaitingForEnd()
{
	WaitForSingleObject(hSempaphore, INFINITE);
}
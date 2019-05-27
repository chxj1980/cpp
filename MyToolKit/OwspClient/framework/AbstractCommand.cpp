#include "StdAfx.h"
#include "AbstractCommand.h"

AbstractCommand::AbstractCommand(UsageEnvironment * pEnvir)
{
	m_pEnvir = pEnvir;
	hSempaphore = CreateSemaphore(NULL, 0, 1, NULL );
	hSempaphoreRsp = CreateSemaphore(NULL, 0, 1, NULL );

	m_pRecvBuffer = NULL;
	m_nRecvLength = 0;
}

AbstractCommand::~AbstractCommand(void)
{
	CloseHandle(hSempaphore);
	CloseHandle(hSempaphoreRsp);

	if(m_pRecvBuffer)
	{
		delete[] m_pRecvBuffer;
	}
}


void AbstractCommand::CommandExecute(UsageEnvironment* pThis)
{
	m_nSendResult = Execute(pThis);

	//	����ִ����ɺ󣬷���֪ͨ
	ReleaseSemaphore(hSempaphore, 1, NULL);
}

void AbstractCommand::ResponseHandler1(void * pUserContext, int nResult, unsigned char * pData , int length)
{
	if(pUserContext)
	{
		AbstractCommand * pCommand = (AbstractCommand *)pUserContext;
		pCommand->ResponseHandler(nResult, pData, length);
	}
}

void AbstractCommand::ResponseHandler(int nResult, unsigned char * pData , int length)
{
	m_nRecvResult = nResult;
	if(length>0)
	{
		m_pRecvBuffer = new unsigned char[length];
		if(m_pRecvBuffer)
		{
			memcpy(m_pRecvBuffer, pData, length);
		}
		m_nRecvLength = length;
	}

	//	�յ��������Ļظ��󣬷���֪ͨ
	ReleaseSemaphore(hSempaphoreRsp, 1, NULL);
}


int AbstractCommand::SyncCall()
{
	/*�ϲ���õ�����ʽִ��*/

	stringstream ss;
	int nResult = RESULT_CODE_LOCAL_ERR;
	CIOCPBuffer * pBuffer = NULL;
	do 
	{
		pBuffer = g_BufferMgr.AllocateBuffer(IOCommand);
		if(pBuffer==NULL)	
			break;
		
		BOOL bSuccess = m_pEnvir->PostQueuedCompletionStatus((BaseClient *)this, pBuffer);
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
			break;
		
		ss << "����Ͷ�����, result( bSuccess ) = " << bSuccess;
		LOG4CPLUS_DEBUG(g_Logger, ss.str().c_str());

		/*����Ͷ�ݽ���*/
		WaitForSingleObject(hSempaphore, INFINITE);

		if(pBuffer)
			g_BufferMgr.ReleaseBuffer(pBuffer);

		nResult = m_nSendResult;
		ss << "��������, result( CSeq ) = " << nResult;
		LOG4CPLUS_DEBUG(g_Logger, ss.str().c_str());

		if(m_nSendResult<0)
			break;
		
		/*���ˣ�������ѳɹ����ȴ����������ؽ��*/
		WaitForSingleObject(hSempaphoreRsp, INFINITE);
		
		ParseResponse();

		ss.str("");
		ss << "�ظ��������, result = " << m_nRecvResult;
		 LOG4CPLUS_DEBUG(g_Logger, ss.str().c_str());

		
		nResult = m_nRecvResult;

	} while (0);

	return nResult;
}
#pragma once

class UsageEnvironment;

class AbstractCommand
{
public:
	AbstractCommand(UsageEnvironment * pEnvir);

	virtual ~AbstractCommand(void);

	int SyncCall();

	void CommandExecute(UsageEnvironment* pThis); 

	static void ResponseHandler1(void * pUserContext, int nResult, unsigned char * pData , int length);
	void ResponseHandler(int nResult, unsigned char * pData , int length);

	virtual int Execute(UsageEnvironment* pThis) = 0;
	virtual void ParseResponse() {}

public:
	int		m_nSendResult;			//	����͵Ľ��

	int		m_nRecvResult;
	unsigned char * m_pRecvBuffer;	//  ���������صĽ��
	int		m_nRecvLength;

protected:
	UsageEnvironment * m_pEnvir;
public:
	HANDLE hSempaphore;

	HANDLE hSempaphoreRsp;
	
};

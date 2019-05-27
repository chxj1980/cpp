#include "StdAfx.h"
#include "DllRegisterResponse.h"

CDllRegisterResponse::CDllRegisterResponse(int commandport, int isOk )
:AbstractCommand(false)
{
	m_commandport = commandport;
	m_isOk = isOk;
}

CDllRegisterResponse::~CDllRegisterResponse(void)
{
}


string CDllRegisterResponse::CommandType() 
{ 
	stringstream ss;
	ss << "CDllRegisterResponse";
	ss << "( " << m_isOk << " )";

	return ss.str(); 
}


int CDllRegisterResponse::Execute(UsageEnvironment* pEnviron)
{
	int nResult = -1;

	CDllRegisterSession * pSession = (CDllRegisterSession *)pEnviron->SearchSession("CDllRegisterSession", -1 * m_commandport);
	
	if(pSession)
	{
		nResult = pSession->SerailNumber();

		Sip_Register_Responce(pSession->m_RegisterReq.tid, m_isOk);
		
		if(m_isOk==0)
		{
			//	��ֹ���¼����¼

			//	����ֳ�
			delete pSession;
		}
	}

	return nResult;
}
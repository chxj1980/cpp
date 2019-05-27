#include "StdAfx.h"
#include "SipdRegisterRequest.h"

CSipdRegisterRequest::CSipdRegisterRequest(sipd_register_req * pRegisterReq)
:AbstractCommand(false)
{
	m_RegisterReq = *pRegisterReq;
}

CSipdRegisterRequest::~CSipdRegisterRequest(void)
{
}


int CSipdRegisterRequest::Execute(UsageEnvironment* pEnviron)
{

	int nResult = -1;
	stringstream ss;

	//	yangbin �˴�����Ҫ��Ϊ ���� from_url ���бȶ�
	CDllRegisterSession * pSession = (CDllRegisterSession *)pEnviron->SearchSession("CDllRegisterSession", m_RegisterReq.rid);
	

	if(pSession)
	{
		pSession->m_RegisterReq = m_RegisterReq;
		nResult =  pSession->SerailNumber();
		if(m_RegisterReq.expires >0)
		{
			//	����ע��Ϊ Heartbeat 
			gettimeofday(&(pSession->m_HeartbeatTime), NULL);

			Sip_Register_Responce(pSession->m_RegisterReq.tid, 1);

			ss << "CDllRegisterSession ��" << pSession->SerailNumber() << "����Heartbeat " ;
			LOG4CPLUS_DEBUG(pEnviron->m_Logger, ss.str());
		}
		else
		{
			// ����Ϊ logout , CDllRegisterSession ���������� ���� ����֪ͨ
			ss << "CDllRegisterSession ��" << pSession->SerailNumber() << "����Logout " ;
			LOG4CPLUS_DEBUG(pEnviron->m_Logger, ss.str());

			//	��������֪ͨ
			/*if(g_Dll_Unregister_Request_func)
				g_Dll_Unregister_Request_func(pSession->SerailNumber());*/

			CCallbackDllUnregisterRequest * pCb = new CCallbackDllUnregisterRequest(pSession->SerailNumber());
			pEnviron->PostCallBack(pCb);

			delete pSession;
		}
	}
	else
	{
		if(m_RegisterReq.expires>0)
		{
			//	�µ��¼���ע��
			pSession = new CDllRegisterSession(*pEnviron, m_nSerialNumber);
			pSession->m_RegisterReq = m_RegisterReq;
			gettimeofday(&(pSession->m_HeartbeatTime), NULL);
			pSession->m_KeepaliveTime = GetTickCount();

			ss << "CDllRegisterSession ��" << pSession->SerailNumber() << "����Login " ;
			ss << ", username = " << m_RegisterReq.username;
			ss << ", from_uri = " << string(m_RegisterReq.from_uri);
			ss << ", to_uri = " << string(m_RegisterReq.to_uri);
			LOG4CPLUS_DEBUG(pEnviron->m_Logger, ss.str());

			nResult = pSession->SerailNumber();
			/*if(g_Dll_Register_Request_func)
				g_Dll_Register_Request_func(pSession->SerailNumber(),  &m_RegisterReq);*/
			CCallbackDllRegisterRequest * pCb = new CCallbackDllRegisterRequest(pSession->SerailNumber(),  &m_RegisterReq);
			pEnviron->PostCallBack(pCb);
		}
		
	}

	return nResult;
}
#include "StdAfx.h"
#include "AbstractCommand.h"

AbstractCommand::AbstractCommand(bool bSnyc)
{
	m_bSnyc = bSnyc;
	if(m_bSnyc)
		hSempaphore = CreateSemaphore(NULL, 0, 1, NULL );
}

AbstractCommand::~AbstractCommand(void)
{
	if(m_bSnyc)
		CloseHandle(hSempaphore);
	
}


void AbstractCommand::CommandExecute(UsageEnvironment* pThis)
{
	m_nResult = Execute(pThis);

	stringstream ss;
	char tmp[32];
	sprintf_s(tmp, 32, "%08d", m_nResult);
	ss <<  CommandType() << ", ִ����ɣ� ���Ϊ[" << string(tmp) << "]";

	bool bLog = true;
	if(CommandType()=="CSipdCataloginfoResponse")
		bLog = false;

	if(bLog)
		LOG4CPLUS_DEBUG(pThis->m_Logger, ss.str());

	if(m_bSnyc==true)
	{
		//	����ִ����ɺ󣬷���֪ͨ
		ReleaseSemaphore(hSempaphore, 1, NULL);
	}
	else
	{
		//  �첽���ִ�����ֱ��ɾ��
		delete this;
	}
}



int AbstractCommand::Call(UsageEnvironment & environ )
{
	stringstream ss;
	int nResult ;
	do 
	{
		nResult = environ.PostCommand(this);
		

		if(nResult < 0)
		{
			/* �����������룬��Ͷ��ʧ�� */
			nResult = -2;
			break;
		}		

		break;
		// ���²���


		/*����Ͷ�ݽ���*/
		if(m_bSnyc)
		{
			/*�ϲ���õ�����ʽִ��*/
			WaitForSingleObject(hSempaphore, INFINITE);

			nResult = m_nResult;
		}
		/*else
		{
			nResult = 0;
		}*/

	} while (0);

	if( 0 /*m_bSnyc*/)
	{
		//	ͬ���������û��ĵ����߳��� delete 
		delete this;
	}

	return nResult;
}
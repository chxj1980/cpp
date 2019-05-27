#pragma once
#include "abstractcommand.h"

class COwspLoginCommand :public AbstractCommand
{
public:
	COwspLoginCommand(UsageEnvironment* pUsageEnvir, string strIPAddr, int nPort);
	~COwspLoginCommand(void);

	virtual int Execute(UsageEnvironment* pUsageEnvir);

	string	m_strIpAddr;
	int		m_nPort;
	
	string	m_strClientName;		//	��Ϊ����ִ�еĽ�����з���
};

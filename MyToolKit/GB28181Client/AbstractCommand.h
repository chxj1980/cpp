#pragma once

class UsageEnvironment;

class AbstractCommand
{
public:
	AbstractCommand(bool bSnyc);

	virtual ~AbstractCommand(void);

	int Call(UsageEnvironment & environ);

	void CommandExecute(UsageEnvironment* pThis); 

	virtual int Execute(UsageEnvironment* pThis) = 0;

	bool IsSnyc(){ return m_bSnyc; }

	virtual string CommandType() = 0;

public:
	HANDLE hSempaphore;

	int	 m_nResult;

	int	 m_nSerialNumber;	//	�� UsageEnvironment ��ǰ����� �������к�

protected:
	bool m_bSnyc;		//	�첽 ���� ͬ������ flag

};

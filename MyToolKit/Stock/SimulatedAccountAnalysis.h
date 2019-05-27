#pragma once

#include "AbstractIndex.h"


class CSimulatedAccountAnalysis
{
public:
	CSimulatedAccountAnalysis(void);
	~CSimulatedAccountAnalysis(void);

	void FetchInit();
	int  FetchNext();

	void SaveDetail(string strTradedate);

	static DWORD WINAPI CommandHandler1(void *data);
	DWORD  CommandHandler();

	
	static CSimulatedAccountAnalysis& getInstance();

private:
	static CSimulatedAccountAnalysis * instance;

public:

	//	ÿ�ս����� ��Ӧ���Ѿ����еĹ�˾���� �� �����Ϣ
	vector<string>		m_vecCode;
	vector<string>		m_vecPlate;

	//	�������н�����
	vector<string>		m_vecTradedate;

	//	��¼�Ѿ�������������ݵ� ���н����� ���±�
	int								m_nLateset;
	
	//	��¼��ǰ���еĹ�Ʊ�˻�
	map<string, CSimulatedAccount *>	m_mapSimulatedAccount;

	//	key Ϊ���ID
	map<string, CStockPlateData>			m_mapPlate;

};

#pragma once

#include "AbstractIndex.h"


class CTechnicalAnalysis
{
public:
	CTechnicalAnalysis(void);
	~CTechnicalAnalysis(void);

	void FetchInit(string beginTradedate);
	bool FetchNext();

	
	static DWORD WINAPI CommandHandler1(void *data);
	DWORD  CommandHandler();

	static CTechnicalAnalysis& getInstance();

private:
	static CTechnicalAnalysis * instance;

public:

	//	ÿ�������� �� ÿֻ��Ʊ ��Ӧ�Ľ�����Ϣ
	map<string, CTechnicalAnalysisData>		m_mapTechnicalAnalysisData;

	//	ÿ�ս����� ��Ӧ���Ѿ����еĹ�˾���� �� �����Ϣ
	vector<string>		m_vecCode;
	vector<string>		m_vecPlate;

	//	�������н�����
	vector<string>		m_vecTradedate;

	//	��¼�Ѿ�������������ݵ� ���н����� ���±�
	int								m_nLateset;
	int								m_nEarliest;

	//	��¼Ҫ���������ָ��
	vector<CAbstractIndex *>		m_vecIndex;

};

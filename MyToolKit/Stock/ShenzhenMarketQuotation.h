#pragma once

#include "stockdatamodel.h"

class CShenzhenMarketQuotation  :
	public CStockDataModel
{
public:
	CShenzhenMarketQuotation(void);
	~CShenzhenMarketQuotation(void);

public:
	map<int, string>	m_vec_report_date;				//	�� ExportFromDatabaseByCode ʱʹ��

	string				m_str_report_date;
	map<int, int>		m_vec_code;
	map<int, string>	m_vec_name;						//	֤ȯ���
	map<int, double>	m_vec_yesterday_close;			//	����
	map<int, double>	m_vec_today_close;				//	����
	map<int, double>	m_vec_up_down;					//	����(%)
	map<int, double>	m_vec_turnover_amount;			//	�ɽ����(Ԫ)
	map<int, double>	m_vec_price_earnings_ratio;		//	��ӯ��

	string ModelType(){ return "CShenzhenMarketQuotation" /*"�������й�Ʊÿ�������"*/; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	bool ParseCsvFileName(string szFileName);
	void ParseXmlElement(void);
	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	void ExportFromDatabaseByCode();

	CStockDataModel * NewCopy();

	string GetDownloadUrl();
	string SaveAsCsv();
	string SqlScript();

	string GetCsvFileName();
};

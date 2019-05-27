#pragma once
#include "stockdatamodel.h"

//	��Ʊ�Ļ������״��

class CSohuFundHold :
	public CStockDataModel
{
public:
	CSohuFundHold(void);
	~CSohuFundHold(void);

public:
	map<int,string>	m_vec_report_date;		//	������
	map<int,int>	m_vec_fund_code;		//	�������
	map<int,string>	m_vec_fund_name;		//	������
	map<int,double>	m_vec_value_hold;		//	�ֲ���ֵ(Ԫ)
	map<int,double>	m_vec_number_hold;		//	�ֲ�����(��)
	map<int,double>	m_vec_percent;			//	ռ����ֵ����(%)

	string ModelType(){ return  "CSohuFundHold" /*"�Ѻ� ������й�Ʊ"*/; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	bool ParseCsvFileName(string szFileName);
	void ParseXmlElement(void){}
	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	CStockDataModel * NewCopy(){ return NULL; };

	string GetDownloadUrl(){return "" ; };
	string SaveAsCsv();
	string SqlScript();

	string GetCsvFileName();
	void NotifyDatabaseImportedToWindow(){} ;
};

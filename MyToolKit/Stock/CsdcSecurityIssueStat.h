#pragma once
#include "stockdatamodel.h"

class CCsdcSecurityIssueStat: public CStockDataModel
{
public:
	CCsdcSecurityIssueStat(void);
	~CCsdcSecurityIssueStat(void);

	string ModelType(){ return  "CCsdcSecurityIssueStat" /* �й������ÿ��֤ȯ���м��Ǽ�ͳ�Ʊ� */; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){ return 0;};
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){};
	bool ParseCsvFileName(string szFileName){ return true; };
	void ParseXmlElement(void){};
	CStockDataModel * NewCopy() { return NULL; }
	string GetCsvFileName(){ return ""; };
	void NotifyDatabaseImportedToWindow(){};
	string GetDownloadUrl(){ return ""; };
	void ExportFromDatabase(double startTime = 0, double endTime = 0){};

	void ImportToDatabase(void);
	string SaveAsCsv();
	string SqlScript();


public:
	vector<string>	m_vec_begin_date;
	vector<string>	m_vec_end_date;
	vector<int>		m_vec_new_stock_num;
	vector<double>	m_vec_new_stock_capital;
	vector<double>	m_vec_new_stock_circulation_capital;
	vector<int>		m_vec_new_bond_num;
	vector<double>	m_vec_new_bond_denomination;
	vector<int>		m_vec_new_fundation_num;
	vector<double>	m_vec_new_fundation_denomination;
};

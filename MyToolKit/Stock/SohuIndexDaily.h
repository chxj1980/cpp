#pragma once

#include "stockdatamodel.h"

class CSohuIndexDaily : public CStockDataModel
{
public:
	CSohuIndexDaily(void);
	~CSohuIndexDaily(void);

public:
	vector<string>	m_vec_report_date;
	vector<double>	m_vec_open;
	vector<double>	m_vec_high;
	vector<double>	m_vec_low;
	vector<double>	m_vec_close;
	vector<double>	m_vec_volume;		//	�ɽ������֣�

	vector<double>	m_vec_change;			//	�ǵ���
	vector<double>	m_vec_change_rate;		//	�ǵ���
	vector<double>	m_vec_turnover;			//	�ɽ���
	// map<int, double>	m_vec_turnover_rate;	//	������

	string ModelType(){ return  "CSohuIndexDaily" /*"ÿ��ָ����"*/; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){ return 0;};
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){};
	bool ParseCsvFileName(string szFileName){ return true; };
	void ParseXmlElement(void){};
	CStockDataModel * NewCopy() { return NULL; }

	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	string GetDownloadUrl(){ return ""; };
	string SaveAsCsv();
	string SqlScript();

	string GetCsvFileName(){ return ""; };
	void NotifyDatabaseImportedToWindow();


private:
	string LastTradeDateFromDatabase();

};

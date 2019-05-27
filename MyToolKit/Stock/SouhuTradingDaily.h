#pragma once
#include "stockdatamodel.h"


class CSouhuTradingDailyData
{
public:
	double  open;
	double	high;
	double	low;
	double	close;
	double	volume;
	double	change;
	double	change_rate;
	double	turnover;
	double	turnover_rate;
};

class CSouhuTradingDaily :
	public CStockDataModel
{
public:
	CSouhuTradingDaily(void);
	~CSouhuTradingDaily(void);

public:
	map<int, string>	m_vec_report_date;
	map<int, double>	m_vec_open;
	map<int, double>	m_vec_high;
	map<int, double>	m_vec_low;
	map<int, double>	m_vec_close;
	map<int, double>	m_vec_volume;		//	�ɽ������֣�
	
	map<int, double>	m_vec_change;			//	�ǵ���
	map<int, double>	m_vec_change_rate;		//	�ǵ���
	map<int, double>	m_vec_turnover;			//	�ɽ���
	map<int, double>	m_vec_turnover_rate;	//	������

	map<string, CSouhuTradingDailyData>	m_vec_reorganize;
	
	string ModelType(){ return  "CSouhuTradingDaily" /*"ÿ�ս��ױ��۱�"*/; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	bool ParseCsvFileName(string szFileName);
	void ParseXmlElement(void);
	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	CStockDataModel * NewCopy();

	string GetDownloadUrl();
	string SaveAsCsv();
	string SaveAsCsv_Old();
	string SqlScript();

	string GetCsvFileName();
	void NotifyDatabaseImportedToWindow();

	//	�����������������֯������֯�� m_vec_reorganize
	void Reorganize();

private:
	string LastTradeDateFromDatabase();
};

#pragma once
#include "stockdatamodel.h"


class CNetEaseTradeDailyData
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

	double	total_value;
	double	circulating_value;
	double  lclose;
};

class CNetEaseTradeDaily :
	public CStockDataModel
{
public:
	CNetEaseTradeDaily(void);
	~CNetEaseTradeDaily(void);

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
	vector<double>	m_vec_turnover_rate;	//	������

	vector<double>	m_vec_lclose;			//	ǰ���̼�
	vector<double>	m_vec_total_value;		//	����ֵ
	vector<double>	m_vec_circulating_value;//	��ͨ��ֵ

	map<string, CNetEaseTradeDailyData>	m_vec_reorganize;
	
	string ModelType(){ return  "CNetEaseTradeDailyData" /*"ÿ�ս��ױ��۱�"*/; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	bool ParseCsvFileName(string szFileName);
	void ParseXmlElement(void);
	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	CStockDataModel * NewCopy();

	string GetDownloadUrl();
	string SaveAsCsv();
	string SqlScript();

	string GetCsvFileName();
	void NotifyDatabaseImportedToWindow();

	//	�����������������֯������֯�� m_vec_reorganize
	void Reorganize();

private:
	string LastTradeDateFromDatabase();
};

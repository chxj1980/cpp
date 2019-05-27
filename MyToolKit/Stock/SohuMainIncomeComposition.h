#pragma once

class CSohuMainIncomeComposition  : public CStockDataModel
{
public:
	CSohuMainIncomeComposition(void);
	~CSohuMainIncomeComposition(void);

public:
	map<int,string>	m_vec_report_date;
	map<int,string>	m_vec_composition_type;					//	����
	map<int,string>	m_vec_composition_name;
	map<int,double>	m_vec_proportion_of_total_income;		//	ռ���������
	map<int,double>	m_vec_income;
	map<int,double>	m_vec_income_change_year_on_year;		//	ͬ�ȱ仯
	map<int,double>	m_vec_cost;								//	�ɱ�
	map<int,double>	m_vec_gross_profit_rate;				//	ë����
	map<int,double>	m_vec_gross_profit_rate_change_year_on_year;	//	ͬ�ȱ仯
	

	string ModelType(){ return  "CSohuMainIncomeComposition" /*"�Ѻ� ��Ҫ���빹��"*/; }

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

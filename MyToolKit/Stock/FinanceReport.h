#pragma once
#include "stockdatamodel.h"

class CFinanceReport :
	public CStockDataModel
{
public:
	CFinanceReport(void);
	~CFinanceReport(void);

	string ModelType(){ return m_strEnglishName; }

	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	bool ParseCsvFileName(string szFileName);
	void ParseXmlElement(void);
	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	string  SaveAsCsv();
	string SqlScript();
	string GetCsvFileName();

	void ExportFromDatabaseByTime(string afterDate);
	string GetFirstReportDate();
	void ReleaseVector();

protected:
	void ConvertXlsToCsv(CStdioFile & srcFile, CStdioFile & targetFile);

protected:
	string	m_strEnglishName;
	string  m_strChineseName;

	// m_vec_index �������±� �����ݿ����ֶ� colume_x �е� x ���Ӧ
	map<int, vector<double> * >	m_vec_index;
	map<string , int>			m_row_name_2_index;

public:
	vector<string>	m_vec_report_date;
	string	m_initial_report_date;	//	������ڲƱ�������
};

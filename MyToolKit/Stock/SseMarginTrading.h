#pragma once
#include "stockdatamodel.h"

class CSseMarginTrading  : public CStockDataModel
{
public:
	CSseMarginTrading(void);
	~CSseMarginTrading(void);

	string ModelType(){ return  "CSseMarginTrading" /*""*/; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){ return 0;};
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){};
	bool ParseCsvFileName(string szFileName){ return true; };
	void ParseXmlElement(void){};
	CStockDataModel * NewCopy() { return NULL; }

	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0){};

	string GetDownloadUrl(){ return ""; };
	string SaveAsCsv();
	string SqlScript();

	string GetCsvFileName(){ return ""; };
	void NotifyDatabaseImportedToWindow();

	bool Unzip(string zipfilename, string & xlsfilename);
	bool ParseXls(string  xlsfilename);

public:

	vector<int>		m_vec_code;			//  ��ҵ���� ���� ֤ȯ����
	vector<string>	m_vec_name;			//	��ҵ���� ���� ֤ȯ����

	vector<double>	m_vec_financing_buying;		//	���������
	vector<double>	m_vec_financing_balance;	//	�������
	vector<double>	m_vec_financing_payback;	//	���ʳ�����

	vector<double>	m_vec_stock_loan_selling;	//	��ȯ������
	vector<double>	m_vec_stock_loan_remaider;	//	��ȯ����
	vector<double>	m_vec_stock_loan_payback;	//	������ȯ������
};

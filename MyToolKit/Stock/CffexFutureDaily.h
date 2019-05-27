#pragma once
#include "stockdatamodel.h"

class CCffexFutureDaily  : public CStockDataModel
{
public:
	CCffexFutureDaily(void);
	~CCffexFutureDaily(void);

	string ModelType(){ return  "CCffexFutureDaily" /* �й������ڻ��������� ÿ������ */; }

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

	vector<string>	NeedDownload();


public:
	vector<string>	m_vec_agreement_code;		// ��Լ����
	vector<double>	m_vec_open;					// ���̼�
	vector<double>	m_vec_high;					// ��߼�
	vector<double>	m_vec_low;					// ��ͼ�
	vector<int>		m_vec_volume;				// �ɽ���
	vector<double>	m_vec_turnover;				// �ɽ����
	vector<int>		m_vec_holding;				// �ֲ���
	vector<double>	m_vec_close;				// ���̼�
	vector<double>	m_vec_settlement;			// �����
	vector<double>	m_vec_change1;				// �ǵ�1
	vector<double>	m_vec_change2;				// �ǵ�2

	string	m_request_trade_date;				//	�������صĽ�������
};

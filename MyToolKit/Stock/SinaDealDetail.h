#pragma once
#include "stockdatamodel.h"


class CSinaDealDetail  : public CStockDataModel
{
public:
	CSinaDealDetail(void);
	~CSinaDealDetail(void);

	string ModelType(){ return  "CSinaDealDetail" /* ��������ÿ�����й�Ʊ�ĳɽ���ϸ */; }

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

	vector<int>	NeedDownload();


public:
	vector<string>	m_vec_deal_time;			// �ɽ�ʱ��
	vector<string>	m_vec_deal_type;			// ����(����/����)
	vector<double>	m_vec_deal_price;			// �ɽ���
	vector<long>	m_vec_deal_volume;			// �ɽ���(��)
	vector<double>	m_vec_deal_turnover;		// �ɽ���(Ԫ)

	string	m_request_trade_date;				//	�������صĽ�������
};

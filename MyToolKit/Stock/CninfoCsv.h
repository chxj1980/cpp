#pragma once
#include "stockdatamodel.h"

class CCninfoCsv : public CStockDataModel
{
public:
	CCninfoCsv(void);
	~CCninfoCsv(void);

public:
	virtual string ModelType(){ return  "CCninfoCsv" /* ����  */; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){ return 0;};
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){};
	bool ParseCsvFileName(string szFileName){ return true; };
	void ParseXmlElement(void){};
	CStockDataModel * NewCopy() { return NULL; }

	void ImportToDatabase(void);
	string Yield2Key(string strYield);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	string GetDownloadUrl(){ return ""; };
	string SaveAsCsv();
	string SqlScript();
	virtual string GetZipUrl() = 0;

	string GetCsvFileName(){ return ""; };
	void NotifyDatabaseImportedToWindow(){};

	bool Unzip(string zipfilename );
	void KaptchaAsJpeg();
	void Kaptcha();

public:
	vector<pair<string, string>>	m_vec_yield;	//	������֤ ����ͷ�ܹ����� ����˳������
	map<string, string>		m_map_yield;	//	���� �ļ�����ͷ �� ���ݿ� ���ӳ���ϵ

	vector<map<string, string>>	m_vec_row;

	string	m_strEnglishName;
};

//////////////////////////////////////////////////////////////////////////

class CCninfoIncomeStatement : public CCninfoCsv
{
public:
	CCninfoIncomeStatement();

	virtual string ModelType(){ return  "CCninfoIncomeStatement" /* �����  */; }
	string GetZipUrl();

	//	����ȫ�������
	double EstimateYearProfits();

	//	ĳ�չ���ĸ��˾�����ߵľ�����
	double NetProfitBelongingToParentCompany(string currDate, string & baseDate, bool & isLast);
};


class CCninfoBalance : public CCninfoCsv
{
public:
	CCninfoBalance();

	virtual string ModelType(){ return  "CCninfoBalance" /* �ʲ���ծ��  */; }
	string GetZipUrl();
};


class CCninfoCashFlows : public CCninfoCsv
{
public:
	CCninfoCashFlows();

	virtual string ModelType(){ return  "CCninfoCashFlows" /* �ֽ�������  */; }
	string GetZipUrl();
};
#pragma once

#include "lotterydatamodel.h"

class CLottoMxn : public CLotteryDataModel
{
public:
	CLottoMxn(void);
	~CLottoMxn(void);
	
	string ModelType(){ return  "CLottoMxn" /* ͬ��˳�ֺ���ת */; }

	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){ return 0;};
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData){};
	bool ParseCsvFileName(string szFileName){ return true; };
	void ParseXmlElement(void){};
	CLotteryDataModel * NewCopy() { return NULL; }

	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0){};

	string GetDownloadUrl(){ return ""; };
	string SaveAsCsv();
	string SqlScript();

	string GetCsvFileName(){ return ""; };
	void NotifyDatabaseImportedToWindow();

public:
	string	m_lottery_name;
	string	m_lottery_code;
	int		m_regular_num;	//	��ѡλ��
	int		m_special_num;	//	�ر����λ��
	int		m_lottery_cpqx;	//	ָ�����ص�ʱ��
	vector<LotteryNumber>	m_vec_lottery;
};

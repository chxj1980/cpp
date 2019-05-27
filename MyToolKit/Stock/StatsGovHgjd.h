#pragma once

class CStatsGovHgjd : public CStatsGovCn
{
public:
	CStatsGovHgjd(void);
	~CStatsGovHgjd(void);

	string ModelType(){ return  "CStatsGovHgjd" /* �й�����ͳ�ƾ� �������� */; }

	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);

	string SaveAsCsv();
	string SqlScript();

	void NotifyDatabaseImportedToWindow();

	string LastSjCodeFromDatabase();

	vector<string>	NeedDownload();
	

public:
	//	�������صġ�ָ�ꡱ�������
	string	m_request_zb_code;

	vector<string>	zb_code;
	vector<string>	sj_code;
	vector<string>	zb_name;
	vector<double>	data;
	vector<string>	unit;

};

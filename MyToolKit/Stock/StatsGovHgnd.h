#pragma once

class CStatsGovHgnd : public CStatsGovCn
{
public:
	CStatsGovHgnd(void);
	~CStatsGovHgnd(void);

	string ModelType(){ return  "CStatsGovHgnd" /* �й�����ͳ�ƾ� ������� */; }

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

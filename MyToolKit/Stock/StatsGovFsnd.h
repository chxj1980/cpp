#pragma once

class CStatsGovFsnd : public CStatsGovCn
{
public:
	CStatsGovFsnd(void);
	~CStatsGovFsnd(void);

	string ModelType(){ return  "CStatsGovFsnd" /* �й�����ͳ�ƾ� ��ʡ������� */; }

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

	vector<string>	reg_code;
	vector<string>	reg_name;
};

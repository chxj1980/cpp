#pragma once

#define	VOLUME_SMOOTHING_DAY_1 5
#define	VOLUME_SMOOTHING_DAY_2 10
#define	VOLUME_SMOOTHING_DAY_3 20


class CVolumeData
{
public:
	string	tradedate;
	double	volume[20];

	double	volume_index1, volume_index2, volume_index3;

	//	���շ������¼� 
	string	remark;
	double  close;

	CVolumeData()
	{
		for(int i =0; i< 20; i++)
			volume[i] = 0;
		volume_index1 = volume_index2 = volume_index3 = 0;

		remark = "";
	}
};


class CVolume : public CAbstractIndex
{
public:
	CVolume(bool bAnalysisUsed = false);
	~CVolume(void);

	virtual void   BeginCalculate();
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate);
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   EndCalculate();

	virtual string  IndexName(){  return "VOL �ɽ���ָ��"; }

	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);

	//	key Ϊ��Ʊ����
	map<string, CVolumeData>		m_mapIndex;

	//	���� ExportFromDatabase �Ľ��, ���ս���������
	vector<CVolumeData>		m_vec_index;

};

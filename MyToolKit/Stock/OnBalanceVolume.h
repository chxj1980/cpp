#pragma once

#define	OBV_SMOOTHING_DAY 12


class COnBalanceVolumeData
{
public:
	string	tradedate;
	double	obv[12];
	double	vol[12];

	//	���շ������¼� 
	string	remark;
	double  close;

	COnBalanceVolumeData()
	{
		for(int i =0; i< 12; i++)
			obv[i] = 0;
		for(int i =0; i< 12; i++)
			vol[i] = 0;
		close = 0;

		remark = "";
	}
};


class COnBalanceVolume : public CAbstractIndex
{
public:
	COnBalanceVolume(bool bAnalysisUsed = false);
	~COnBalanceVolume(void);

	virtual void   BeginCalculate();
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate);
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   EndCalculate();

	virtual string  IndexName(){  return "OBV ƽ�⽻����ָ��"; }

	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);

	//	key Ϊ��Ʊ����
	map<string, COnBalanceVolumeData>		m_mapIndex;

	//	���� ExportFromDatabase �Ľ��, ���ս���������
	vector<COnBalanceVolumeData>		m_vec_index;

};

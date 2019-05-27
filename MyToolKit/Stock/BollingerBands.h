#pragma once


#define	RELATIVE_STRENGTH_INDEX_SMOOTHING_DAY 5

class CBollingerBandsData
{
public:
	string	tradedate;
	double	close[20];

	double	middle, up, down, standard;

	//	���շ������¼� 
	string	remark;
	double  bonus_share, bonus_cash, reserve_to_common_share;

	CBollingerBandsData()
	{
		for(int i =0; i< 20; i++)
			close[i] = 0;
		standard = middle = up = down = 0;

		remark = "";

		bonus_share = bonus_cash = reserve_to_common_share = 0;
	}
};


class CBollingerBands : public CAbstractIndex
{
public:
	CBollingerBands(bool bAnalysisUsed = false);
	~CBollingerBands(void);

	virtual void   BeginCalculate();
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate);
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   EndCalculate();

	virtual string  IndexName(){  return "BOLL ����ͨ��"; }

	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);

	//	key Ϊ��Ʊ����
	map<string, CBollingerBandsData>		m_mapIndex;

	//	���� ExportFromDatabase �Ľ��, ���ս���������
	vector<CBollingerBandsData>		m_vec_index;

};

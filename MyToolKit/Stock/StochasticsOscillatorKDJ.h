#pragma once

#define	KDJ_DAY 9

class CStochasticsOscillatorKDJData
{
public:
	int		serial_num;
	string	tradedate, good_tradedate, bad_tradedate, good_desc, bad_desc;
	double	close, high[9], low[9];
	double	k_value, d_value, j_value;

	//	���շ������¼� 
	string	remark;
	
	CStochasticsOscillatorKDJData()
	{
		close = 0;
		k_value = d_value = j_value = 50;

		for(int i=0; i< 9; i++)
		{
			high[i] = low[i] = 0;
		}

		remark = "";
	}
};


class CStochasticsOscillatorKDJ : public CAbstractIndex
{
public:
	CStochasticsOscillatorKDJ(bool bAnalysisUsed = false);
	~CStochasticsOscillatorKDJ(void);

	virtual void   BeginCalculate();
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate);
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   EndCalculate();

	virtual string  IndexName(){  return "KDJ ָ��"; }

	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);


	map<string, CStochasticsOscillatorKDJData>		m_mapIndex;

	//	���� ExportFromDatabase �Ľ��, ���ս���������
	vector<CStochasticsOscillatorKDJData>		m_vec_index;

};

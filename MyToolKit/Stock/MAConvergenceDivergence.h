#pragma once

#define	RELATIVE_STRENGTH_INDEX_SMOOTHING_DAY 5

class CMAConvergenceDivergenceData
{
public:
	int		serial_num;
	string	tradedate;
	double	ema12, ema26, dif, dea;
	double	close, high, low;

	string	peak_date[10];
	double	peak_dif[10];
	double	peak_high[10];
	double	peak_low[10];
	int		peak_sign[10];		//	< 0 : ����  > 0 : ����  =0 ��δ֪

	string	cross_date[10];
	double	cross_dif[10];
	int		cross_sign[10];		//	< 0 : ����  > 0 : ���  =0 : δ֪

	string  remark;

	CMAConvergenceDivergenceData()
	{
		ema12 = ema26 = dif = dea = 0;
		close = high = low = 0;
		remark = "";

		for(int i=0; i< 10; i++)
		{
			peak_date[i] = "";
			peak_dif[i] = 0;
			peak_high[i] = 0;
			peak_low[i] = 0;
			peak_sign[i] = 0;

			cross_date[i] = "";
			cross_dif[i] = 0;
			cross_sign[i] = 0;
		}
	}
};


class CMAConvergenceDivergence : public CAbstractIndex
{
public:
	CMAConvergenceDivergence(bool bAnalysisUsed = false);
	~CMAConvergenceDivergence(void);

	virtual void   BeginCalculate();
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate);
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   EndCalculate();

	virtual string  IndexName(){  return "MACD ƽ����ͬƽ��ָ��"; }


	map<string, CMAConvergenceDivergenceData>		m_mapIndex;

};

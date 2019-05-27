#pragma once


class CTechAnalysisEventData
{
public:
	
	string	tradedate;
	string	index_name;
	string	basic_desc, extra_desc;
	double  percent;

	//	�¼������յľ���ϵͳ
	double	ma5, ma10, ma20, ma60;
	string	ma;

	//	����Ϊ��Ȩ��ʱ�� ת������ɡ��ֺ������
	double	bonus_share, bonus_cash, reserve_to_common_share;

	//	macd
	double	ema12, ema26, dif, dea;
	string	macd;

	//	dmi
	double	positive_di, negative_di, ema_dx;
	string	dmi;

	//	kdj
	double	k_value, d_value, j_value;
	string	kdj;

	//	rsi
	double	rsi1, rsi2, rsi3;

	//	boll
	double	middle, up, down, standard;
	string	boll;

	//	candlesticks
	string	candlesticks;

	//	pe
	double static_pe, dynamic_pe , pb, dividend_yield_ratio, parent_dynamic_pe;

	//	obv
	string	obv;

	// ���� ����ÿ�ս�������
	double circulating_value;
	double change_rate;
	double close;
	double lclose;

	CTechAnalysisEventData()
	{
		tradedate = "";
		index_name = "";
		basic_desc = extra_desc = "";

		bonus_share = bonus_cash = reserve_to_common_share = 0;
	}
};


class CTechAnalysisEvent 
{
public:
	CTechAnalysisEvent();
	~CTechAnalysisEvent(void);

	
	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);


	//	���� ExportFromDatabase �Ľ��, ���ս���������
	vector<CTechAnalysisEventData>		m_vec_index;

};

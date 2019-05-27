#pragma once
#include "calculatetask.h"

class CCalcRecentStockSummary :
	public CCalculateTask
{
public:
	CCalcRecentStockSummary(HWND hwnd, int logType);
	~CCalcRecentStockSummary(void);

	string ClassName(){ return "CCalcRecentStockSummary"; }

	void Execute();
	static void Execute1(void* firstArg);

public:
	
	string			m_after_report_date;
	string			m_request_like;

	vector<int>		m_vec_code			;			//	"��˾����",
	vector<string>	m_vec_abbreviation;
	vector<string>	m_vec_a_time_to_market;			//	����ʱ��
	vector<string>	m_vec_recent_forecast_date;		//	ҵ��Ԥ������
	vector<string>	m_vec_recent_finance_date;
	vector<string>	m_vec_recent_trade_date;		//	�������

	vector<double>	m_vec_a_total_share;			//	�ܹɱ�	
	vector<double>	m_vec_estimate_profit;
	vector<double>	m_vec_earning_per_year;
	vector<double>	m_vec_pe;
	vector<double>	m_vec_a_total_value;			//	����ֵ
	vector<double>	m_vec_a_circulating_value;
	vector<double>	m_vec_recent_forecast_rate;
	vector<double>	m_vec_close;
	vector<double>	m_vec_change_rate;				//	�ǵ���
	vector<double>	m_vec_turnover_rate;			//	������

	vector<double>	m_vec_static_pe;
	vector<double>	m_vec_dynamic_pe;
	vector<double>	m_vec_pb;
	vector<double>	m_vec_dividend_yield_ratio;
};

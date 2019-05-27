#pragma once

class CCalcDealDetailDaily  : public CCalculateTask
{
public:
	CCalcDealDetailDaily(HWND hwnd, int logType);
	~CCalcDealDetailDaily(void);

	string ClassName(){ return "CCalcDealDetailDaily"; }

	void Execute();
	static void Execute1(void* firstArg);

public:
	vector<int>		m_vec_code			;	//	"��˾���� ���� ��ҵ����",
	vector<string>	m_vec_deal_type;
	vector<string>	m_vec_deal_time;

	vector<double>	m_vec_deal_price;
	vector<double>	m_vec_deal_volume;
	vector<double>  m_vec_deal_turnover;

	int		m_nRequestDealDate;
};

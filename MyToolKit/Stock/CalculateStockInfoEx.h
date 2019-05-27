#pragma once


//////////////////////////////////////////////////////////////////////////
//	�������� ��ѯ�����򡢷��ࡢ���˵ȹ���

class CCalculateStockInfoEx : public CCalculateTask 
{
public:
	CCalculateStockInfoEx(HWND hwnd, int logType);
	~CCalculateStockInfoEx(void);

	string ClassName(){ return "CCalculateStockInfoEx"; }

	string SqlScript();
	void ImportToDatabase();
	void RecentStockSummary();
	void RecentMainIncomeComposition();
	void RecentLiquidityRatio();
	void RecentNetProfitsRatio();
	void RecentBalanceAndIncomestatement();
	void RecentFundHold();
	void ZombieStockList();
	void MainProductQueryList();

	static void ImportToDatabase1(void* firstArg);
	static void RecentStockSummary1(void* firstArg);
	static void RecentMainIncomeComposition1(void* firstArg);
	static void RecentLiquidityRatio1(void* firstArg);
	static void RecentNetProfitsRatio1(void* firstArg);
	static void RecentBalanceAndIncomestatement1(void* firstArg);
	static void RecentFundHold1(void* firstArg);
	static void ZombieStockList1(void* firstArg);
	static void MainProductQueryList1(void* firstArg);
	
	

private:
	void Calculate();

public :
	vector<CStockInfoSummary>  m_vec_StockSummary;	//	�������Ľ��

public:
	map<int, int>		m_vec_code			;	//	"��˾����",
	map<int, string>	m_vec_calculate_date;	//	������Ľ�����
	map<int, double>	m_vec_a_total_shares;	//	A �ɹ���
	map<int, double>	m_vec_a_total_value;		//	����ֵ
	map<int, double>	m_vec_earnings_per_share;	//	ÿ������
	map<int, double>	m_vec_pe;				//	��ӯ��


	map<int, string>	m_vec_abbreviation;		//	"��˾���",
	map<int, string>	m_vec_province;			//	"ʡ��
	map<int, string>	m_vec_belong_to_industry;	//	 "������ҵ"
	map<int, string>	m_vec_stock_plate;		//	��Ʊ��飺 ��ҵ�桢��С��

public:
	map<int, double>	m_vec_open;
	map<int, double>	m_vec_high;
	map<int, double>	m_vec_low;
	map<int, double>	m_vec_close;		//	���̼�
	map<int, double>	m_vec_volume;		//	�ɽ������֣�

	map<int, double>	m_vec_change;			//	�ǵ���
	map<int, double>	m_vec_change_rate;		//	�ǵ���
	map<int, double>	m_vec_turnover;			//	�ɽ���
	map<int, double>	m_vec_turnover_rate;	//	������

public:
	map<int, string>	m_vec_composition_name;
	map<int, double>	m_vec_income;
	map<int, double>	m_vec_cost;
	map<int, double>	m_vec_gross_profit_rate;

public:
	map<int, string>	m_vec_report_date;
	map<int, double>	m_vec_liquidity_ratio;
public:
	map<int, double>	m_vec_net_profits_ratio;

public:
	map<int, double>	m_vec_sales_from_operations;		//	Ӫҵ����
	map<int, double>	m_vec_cost_of_operations;			//	Ӫҵ�ɱ�
	map<int, double>	m_vec_net_profit_belonging_to_parent_company;		//	������ĸ��˾�����ߵľ�����

	map<int, double>	m_vec_inventories;				//		"���"
	map<int, double>	m_vec_fixed_assets_net_value;	//		"�̶��ʲ���ֵ"
	map<int, double>	m_vec_total_current_assets;		//		"�����ʲ��ϼ�"
	map<int, double>	m_vec_total_non_current_assets;  //		"�������ʲ��ϼ�"
	map<int, double>	m_vec_total_current_liabilities;  //		"������ծ�ϼ�"
	map<int, double>	m_vec_total_non_current_liabilities;	 //		"��������ծ�ϼ�"

public:
	map<int, double>	m_vec_number_fund_hold;			//	���������
	map<int, double>	m_vec_number_AShares;			//	��ͨ����
	map<int, double>	m_vec_number_A_total_shares;	//	����ͨ����

public:
	map<int, double>	m_vec_registered_capital;		//	ʵ���ʱ�
	map<int, double>	m_vec_total_owners_equity_belongs_to_parent_company;	//	������ĸ��˾�ɶ�Ȩ��ϼ�
	map<int ,double>	m_vec_undistributed_profits;	//	δ��������
	map<int ,double>	m_vec_total_liability;			//	��ծ�ܼ�
	map<int ,double>	m_vec_total_assets;				//	�ʲ��ܼ�
	map<int ,double>	m_vec_intangibel_assets;		//	�����ʲ�
	map<int, double>	m_vec_goodwill;					//	����

public:
	string		m_main_product_query;					//	��Ӫ��Ʒ��ѯ


};

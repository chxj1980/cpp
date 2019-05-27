#pragma once

//////////////////////////////////////////////////////////////////////////
//	�����

class CIncomeStatement :public CFinanceReport
{
public:
	CIncomeStatement(void);
	//	��Ϊ m_vec_index �а�����ָ�룬����д ��ֵ�����Ϳ������캯��
	CIncomeStatement(const CIncomeStatement& rhs);
	CIncomeStatement& operator=(const CIncomeStatement& rhs);

	~CIncomeStatement(void);


	CStockDataModel * NewCopy();
	string GetDownloadUrl();
	int CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);

	//	����ȫ�������
	double EstimateYearProfits();

	//	ĳ�չ���ĸ��˾�����ߵľ�����
	double NetProfitBelongingToParentCompany(string currDate, string & baseDate, bool & isLast);

private:
	void Initialize();

public:
	//map<int, string>	m_vec_report_date;
	vector<double>	m_vec_overall_sales;		//	Ӫҵ������
	vector<double>	m_vec_sales_from_operations;		//	Ӫҵ����
	vector<double>	m_vec_interest_income;						//	��Ϣ����
	vector<double>	m_vec_insurance_premiums_earned;						//	��׬����
	vector<double>	m_vec_handling_charges_and_commissions_income;			//	�����Ѽ�Ӷ������
	vector<double>	m_vec_real_estate_sales_revenue;						//	���ز���������
	vector<double>	m_vec_income_from_other_operations;						//	����ҵ������
	vector<double>	m_vec_overall_costs;						//	����Ӫҵ�ܳɱ�
	vector<double>	m_vec_cost_of_operations;					//	Ӫҵ�ɱ�
	vector<double>	m_vec_interest_expenses;						//	��Ϣ֧��
	vector<double>	m_vec_handling_charges_and_commissions_expenses;						//	�����Ѽ�Ӷ��֧��
	vector<double>	m_vec_real_estate_sales_cost;						//	���ز����۳ɱ�
	vector<double>	m_vec_research_and_development_expenses;			//	�з�����
	vector<double>	m_vec_refund_of_insurance_premiums;						//	�˱���
	vector<double>	m_vec_net_payments_for_insurance_claims;						//	�⸶֧������
	vector<double>	m_vec_net_provision_for_insurance_contracts;			//	��ȡ���պ�ͬ׼���𾻶�
	vector<double>	m_vec_commissions_on_insurance_policies;						//	��������֧��
	vector<double>	m_vec_cession_charges;						//	�ֱ�����
	vector<double>	m_vec_cost_of_other_operations;						//	����ҵ��ɱ�
	vector<double>	m_vec_sales_tax_and_additions;						//	Ӫҵ˰�𼰸���
	vector<double>	m_vec_selling_and_distribution_expenses;						//	���۷���
	vector<double>	m_vec_general_and_administrative_expenses;						//	�������
	vector<double>	m_vec_financial_expenses;						//	�������
	vector<double>	m_vec_impairment_loss_on_assets;						//	�ʲ���ֵ��ʧ
	vector<double>	m_vec_gain_or_loss_from_changes_in_fair_values;						//	���ʼ�ֵ�䶯����
	vector<double>	m_vec_investment_income;						//	Ͷ������
	vector<double>	m_vec_investment_income_from_joint_ventures_and_affiliates;			//	����Ӫ��ҵ�ͺ�Ӫ��ҵ��Ͷ������
	vector<double>	m_vec_gain_or_loss_on_foreign_exchange_transactions;						//	�������
	vector<double>	m_vec_futures_gains_and_losses;						//	�ڻ�����
	vector<double>	m_vec_managed_revenue;						//	�й�����
	vector<double>	m_vec_subsidy_income;						//	��������
	vector<double>	m_vec_other_business_profits;						//	����ҵ������
	vector<double>	m_vec_profit_from_operations;						//	����Ӫҵ����
	vector<double>	m_vec_non_operating_profit;						//	Ӫҵ������
	vector<double>	m_vec_non_operating_expenses;						//	Ӫҵ��֧��
	vector<double>	m_vec_losses_from_disposal_of_non_current_assets;			//	�������ʲ�������ʧ
	vector<double>	m_vec_profit_before_tax;						//	�����ܶ�
	vector<double>	m_vec_income_tax_expenses;						//	����˰����
	vector<double>	m_vec_unrecognized_investment_losses;						//	δȷ��Ͷ����ʧ
	vector<double>	m_vec_net_profit;						//	�ġ�������
	vector<double>	m_vec_net_profit_belonging_to_parent_company;						//	������ĸ��˾�����ߵľ�����
	vector<double>	m_vec_minority_interest;						//	�����ɶ�����
	vector<double>	m_vec_earnings_per_share;						//	�塢ÿ������
	vector<double>	m_vec_basic_earnings_per_share;					//	����ÿ������
	vector<double>	m_vec_diluted_earnings_per_share;						//	ϡ��ÿ������
	vector<double>	m_vec_other_consolidated_income;						//	���������ۺ�����
	vector<double>	m_vec_total_consolidated_income;						//	�ߡ��ۺ������ܶ�
	vector<double>	m_vec_consolidated_income_belonging_to_parent_company;	//	������ĸ��˾�����ߵ��ۺ������ܶ�
	vector<double>	m_vec_consolidated_income_belonging_to_minority_shareholders;	//	�����������ɶ����ۺ������ܶ�

};

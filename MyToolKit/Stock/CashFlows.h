#pragma once
#include "stockdatamodel.h"

class CCashFlows :
	public CFinanceReport
{
public:
	CCashFlows(void);
	//	��Ϊ m_vec_index �а�����ָ�룬����д ��ֵ�����Ϳ������캯��
	CCashFlows(const CCashFlows& rhs);
	CCashFlows& operator=(const CCashFlows& rhs);

	~CCashFlows(void);


	CStockDataModel * NewCopy();
	string GetDownloadUrl();
	int CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);

private:
	void Initialize();

public:
	// map<int, string>	m_vec_report_date;
	vector<double> m_vec_cash_flows_from_operating_activities ;		//		"һ����Ӫ��������ֽ�����",
	vector<double> m_vec_cash_received_from_sales_of_goods_or_rending_of_services ;		//		"������Ʒ���ṩ�����յ����ֽ�",
	vector<double> m_vec_net_increase_of_customers_deposit_and_deposit_taking_of_interbank ;		//		"�ͻ�����ͬҵ��ſ�����Ӷ�",
	vector<double> m_vec_net_increase_borrowings_from_central_bank  ;		//		"���������н����Ӷ�",
	vector<double> m_vec_net_increase_borrowing_funds_to_other_financing_institution  ;		//		"���������ڻ��������ʽ����Ӷ�",
	vector<double> m_vec_cash_from_original_insurance_contract_premium ;		//		"�յ�ԭ���պ�ͬ����ȡ�õ��ֽ�",
	vector<double> m_vec_net_cash_from_reinsurance_business  ;		//		"�յ��ٱ���ҵ���ֽ𾻶�",
	vector<double> m_vec_net_increase_of_insured_deposit_and_investment  ;		//		"��������Ͷ�ʿ���Ӷ�",
	vector<double> m_vec_net_increase_in_disposal_of_financial_assets ;		//		"���ý����Խ����ʲ������Ӷ�",
	vector<double> m_vec_interest_handling_charges_and_commissions_received  ;		//		"��ȡ��Ϣ�������Ѽ�Ӷ����ֽ�",
	vector<double> m_vec_net_increase_of_loans  ;		//		"�����ʽ����Ӷ�",
	vector<double> m_vec_net_increase_of_repurchasing_business_funds  ;		//		"�ع�ҵ���ʽ����Ӷ�",
	vector<double> m_vec_refund_of_tax_and_levies  ;		//		"�յ���˰�ѷ���",
	vector<double> m_vec_cash_relating_to_other_business_activities  ;		//		"�յ��������뾭Ӫ��йص��ֽ�",
	vector<double> m_vec_cash_inflow_from_business_activities  ;		//		"��Ӫ��ֽ�����С��",
	vector<double> m_vec_cash_from_purchasement_and_receiving_service_payments  ;		//		"������Ʒ����������֧�����ֽ�",
	vector<double> m_vec_net_increase_of_customer_loans_and_advances  ;		//		"�ͻ���������Ӷ�",
	vector<double> m_vec_net_increase_depositing_in_central_bank_and_other_banks  ;		//		"����������к�ͬҵ������Ӷ�",
	vector<double> m_vec_cash_paid_for_original_insurance_contract_compensation_payment  ;		//		"֧��ԭ���պ�ͬ�⸶������ֽ�",
	vector<double> m_vec_interests_handling_charges_and_commissions_paid  ;		//		"֧����Ϣ�������Ѽ�Ӷ����ֽ�",
	vector<double> m_vec_cash_paid_for_policy_dividend ;		//		"֧�������������ֽ�",
	vector<double> m_vec_cash_paid_to_employee_and_for_employee  ;		//		"֧����ְ���Լ�Ϊְ��֧�����ֽ�",
	vector<double> m_vec_payments_of_all_types_of_taxes  ;		//		"֧���ĸ���˰��",
	vector<double> m_vec_cash_paid_for_others_relating_to_business_activities  ;		//		"֧���������뾭Ӫ��йص��ֽ�",
	vector<double> m_vec_sub_total_of_cash_outflows_relating_to_business_activities ;		//		"��Ӫ��ֽ�����С��",
	vector<double> m_vec_net_cash_flow_from_business_activities  ;		//		"��Ӫ��������ֽ���������",

	vector<double> m_vec_cash_flows_from_investing_activities ;		//		"����Ͷ�ʻ�������ֽ�������",
	vector<double> m_vec_cash_received_from_return_of_investment ;		//		"�ջ�Ͷ�����յ����ֽ�",
	vector<double> m_vec_cash_received_from_investments ;		//		"ȡ��Ͷ���������յ����ֽ�",
	vector<double> m_vec_net_cash_received_from_disposal_of_fixed_assets_intangible_assets_and_other_long_term_assets ;		//		"���ù̶��ʲ��������ʲ������������ʲ����ջص��ֽ𾻶�",
	vector<double> m_vec_net_cash_received_from_disposals_of_subsidiaries_and_other_business_units ;		//		"�����ӹ�˾������Ӫҵ��λ�յ����ֽ𾻶�",
	vector<double> m_vec_other_cash_received_relating_to_operating_activities ;		//		"�յ���������Ͷ�ʻ�йص��ֽ�",
	vector<double> m_vec_unknown_1 ;		//		"������Ѻ�Ͷ��ڴ�����յ����ֽ�",
	vector<double> m_vec_sub_total_of_cash_inflows_relating_to_investment_activities ;		//		"Ͷ�ʻ�ֽ�����С��",
	vector<double> m_vec_cash_paid_to_acquire_fixed_assets_intangible_assets_and_other_long_term_assents ;		//		"�����̶��ʲ��������ʲ������������ʲ���֧�����ֽ�",
	vector<double> m_vec_cash_paid_for_investments ;		//		"Ͷ����֧�����ֽ�",
	vector<double> m_vec_net_increase_of_hypothecated_loan  ;		//		"��Ѻ������Ӷ�",
	vector<double> m_vec_net_cash_from_subsidiary_corporation_and_other_business_entity  ;		//		"ȡ���ӹ�˾������Ӫҵ��λ֧�����ֽ𾻶�",
	vector<double> m_vec_other_cash_paid_relating_to_operating_activities ;		//		"֧����������Ͷ�ʻ�йص��ֽ�",
	vector<double> m_vec_unknown_2 ;		//		"������Ѻ�Ͷ��ڴ����֧�����ֽ�",
	vector<double> m_vec_sub_total_of_cash_outflows_relating_to_investment_activities ;		//		"Ͷ�ʻ�ֽ�����С��",
	vector<double> m_vec_net_cash_flows_from_investing_activities ;		//		"Ͷ�ʻ�������ֽ���������",

	vector<double> m_vec_cash_flows_from_financing_activities  ;		//		"�������ʻ�������ֽ�������",
	vector<double> m_vec_cash_received_from_investors ;		//		"����Ͷ���յ����ֽ�",
	vector<double> m_vec_cash_from_minority_stockholders_by_subsidiary_corporation  ;		//		"���У��ӹ�˾���������ɶ�Ͷ���յ����ֽ�",
	vector<double> m_vec_cash_from_borrowings ;		//		"ȡ�ý���յ����ֽ�",
	vector<double> m_vec_proceeds_from_issuance_of_bonds  ;		//		"����ծȯ�յ����ֽ�",
	vector<double> m_vec_cash_from_other_relevant_financing_activities  ;		//		"�յ���������ʻ�йص��ֽ�",
	vector<double> m_vec_sub_total_of_cash_inflows ;		//		"���ʻ�ֽ�����С��",
	vector<double> m_vec_cash_repayments_of_amount_borrowed ;		//		"����ծ��֧�����ֽ�",
	vector<double> m_vec_cash_payments_for_distrbution_of_dividends_or_profits ;		//		"�������������򳥸���Ϣ��֧�����ֽ�",
	vector<double> m_vec_other_cash_payment_relating_to_financing_activities ;		//		"֧����������ʻ�йص��ֽ�",
	vector<double> m_vec_sub_total_of_cash_outflows_relating_to_financing_activities ;	//		"���ʻ�ֽ�����С��",
	vector<double> m_vec_net_cash_flows_from_financing_activities ;		//		"���ʻ�������ֽ���������",

	vector<double> m_vec_supplemental_information ;		//		"��ע",
	vector<double> m_vec_effect_of_foreign_exchang_rate_changes_on_cash ;		//		"���ʱ䶯���ֽ��ֽ�ȼ����Ӱ��",
	vector<double> m_vec_net_increase_in_cash_and_cash_equivalents ;		//		"�ֽ��ֽ�ȼ��ﾻ���Ӷ�",
	vector<double> m_vec_cash_and_cash_equivalents_at_beginning_of_period  ;		//		"�ڳ��ֽ��ֽ�ȼ������",
	vector<double> m_vec_cash_and_cash_equivalents_at_end_of_period  ;		//		"��ĩ�ֽ��ֽ�ȼ������",
	vector<double> m_vec_net_profit ;		//		"������",
	vector<double> m_vec_minority_stockholders_interest  ;		//		"�����ɶ�Ȩ��",
	vector<double> m_vec_unaffirmed_investment_loss  ;		//		"δȷ�ϵ�Ͷ����ʧ",
	vector<double> m_vec_provision_for_assets ;		//		"�ʲ���ֵ׼��",
	vector<double> m_vec_depreciation_for_fixed_assets_and_so_on ;		//		"�̶��ʲ��۾ɡ������ʲ��ۺġ������������۾�",
	vector<double> m_vec_amortisation_of_intangible_assets ;		//		"�����ʲ�̯��",
	vector<double> m_vec_amortisation_of_long_term_deffered_expenses ;		//		"���ڴ�̯����̯��",
	vector<double> m_vec_decrease_of_deffered_expenses ;		//		"��̯���õļ���",
	vector<double> m_vec_addition_of_accued_expense ;		//		"Ԥ����õ�����",
	vector<double> m_vec_losses_on_disposal_of_fixed_assets_intangible_assets_and_other_long_term_assets ;		//		"���ù̶��ʲ��������ʲ������������ʲ�����ʧ",
	vector<double> m_vec_losses_on_scrapping_of_fixed_assets ;		//		"�̶��ʲ�������ʧ",
	vector<double> m_vec_losses_on_fair_value ;		//		"���ʼ�ֵ�䶯��ʧ",
	vector<double> m_vec_unknown_3 ;		//		"�����������ӣ��������٣�",
	vector<double> m_vec_anticipation_liabilities  ;		//		"Ԥ�Ƹ�ծ",
	vector<double> m_vec_finance_expense ;		//		"�������",
	vector<double> m_vec_losses_arsing_from_investment ;		//		"Ͷ����ʧ",
	vector<double> m_vec_unknown_4 ;		//		"��������˰�ʲ�����",
	vector<double> m_vec_unknown_5 ;		//		"��������˰��ծ����",
	vector<double> m_vec_decrease_in_inventories ;		//		"����ļ���",
	vector<double> m_vec_decrease_in_operating_receivables ;		//		"��Ӫ��Ӧ����Ŀ�ļ���",
	vector<double> m_vec_increase_in_operating_receivables ;		//		"��Ӫ��Ӧ����Ŀ������",
	vector<double> m_vec_unknown_6 ;		//		"���깤��δ�����ļ���(��:����)",
	vector<double> m_vec_unknown_7 ;		//		"�ѽ�����δ�깤�������(��:����)",
	vector<double> m_vec_others ;		//		"����",
	vector<double> m_vec_net_cash_flows_from_operating_activities ;		//		"��Ӫ������ֽ���������",
	vector<double> m_vec_debts_transfer_to_capital ;		//		"ծ��תΪ�ʱ�",
	vector<double> m_vec_one_year_due_convertible_bonds ;		//		"һ���ڵ��ڵĿ�ת����˾ծȯ",
	vector<double> m_vec_financing_rent_to_the_fixed_asset ;		//		"��������̶��ʲ�",
	vector<double> m_vec_cash_at_the_end_of_period ;		//		"�ֽ����ĩ���",
	vector<double> m_vec_cash_at_the_beginning_of_the_period ;		//		"�ֽ���ڳ����",
	vector<double> m_vec_cash_equivalents_at_the_end_of_the_period ;		//		"�ֽ�ȼ������ĩ���",
	vector<double> m_vec_cash_equivalents_at_the_beginning_of_the_period ;		//		"�ֽ�ȼ�����ڳ����",
	vector<double> m_vec_net_increase_in_cash_and_cash_equivalents_1 ;		//		"�ֽ��ֽ�ȼ���ľ����Ӷ�"

};

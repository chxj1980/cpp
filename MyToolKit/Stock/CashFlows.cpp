#include "StdAfx.h"
#include "CashFlows.h"
#include "UrlUtils.h"

void CCashFlows::Initialize(void)
{
	m_strChineseName = _T("�ֽ�������");
	m_strEnglishName = "CashFlows";

	m_vec_index[1] = &m_vec_cash_flows_from_operating_activities ;		//		"һ����Ӫ��������ֽ�����",
	m_vec_index[2] = &m_vec_cash_received_from_sales_of_goods_or_rending_of_services ;		//		"������Ʒ���ṩ�����յ����ֽ�",
	m_vec_index[3] = &m_vec_net_increase_of_customers_deposit_and_deposit_taking_of_interbank ;		//		"�ͻ�����ͬҵ��ſ�����Ӷ�",
	m_vec_index[4] = &m_vec_net_increase_borrowings_from_central_bank  ;		//		"���������н����Ӷ�",
	m_vec_index[5] = &m_vec_net_increase_borrowing_funds_to_other_financing_institution  ;		//		"���������ڻ��������ʽ����Ӷ�",
	m_vec_index[6] = &m_vec_cash_from_original_insurance_contract_premium ;		//		"�յ�ԭ���պ�ͬ����ȡ�õ��ֽ�",
	m_vec_index[7] = &m_vec_net_cash_from_reinsurance_business  ;		//		"�յ��ٱ���ҵ���ֽ𾻶�",
	m_vec_index[8] = &m_vec_net_increase_of_insured_deposit_and_investment  ;		//		"��������Ͷ�ʿ���Ӷ�",
	m_vec_index[9] = &m_vec_net_increase_in_disposal_of_financial_assets ;		//		"���ý����Խ����ʲ������Ӷ�",
	m_vec_index[10] = &m_vec_interest_handling_charges_and_commissions_received  ;		//		"��ȡ��Ϣ�������Ѽ�Ӷ����ֽ�",
	m_vec_index[11] = &m_vec_net_increase_of_loans  ;		//		"�����ʽ����Ӷ�",
	m_vec_index[12] = &m_vec_net_increase_of_repurchasing_business_funds  ;		//		"�ع�ҵ���ʽ����Ӷ�",
	m_vec_index[13] = &m_vec_refund_of_tax_and_levies  ;		//		"�յ���˰�ѷ���",
	m_vec_index[14] = &m_vec_cash_relating_to_other_business_activities  ;		//		"�յ��������뾭Ӫ��йص��ֽ�",
	m_vec_index[15] = &m_vec_cash_inflow_from_business_activities  ;		//		"��Ӫ��ֽ�����С��",
	m_vec_index[16] = &m_vec_cash_from_purchasement_and_receiving_service_payments  ;		//		"������Ʒ����������֧�����ֽ�",
	m_vec_index[17] = &m_vec_net_increase_of_customer_loans_and_advances  ;		//		"�ͻ���������Ӷ�",
	m_vec_index[18] = &m_vec_net_increase_depositing_in_central_bank_and_other_banks  ;		//		"����������к�ͬҵ������Ӷ�",
	m_vec_index[19] = &m_vec_cash_paid_for_original_insurance_contract_compensation_payment  ;		//		"֧��ԭ���պ�ͬ�⸶������ֽ�",
	m_vec_index[20] = &m_vec_interests_handling_charges_and_commissions_paid  ;		//		"֧����Ϣ�������Ѽ�Ӷ����ֽ�",
	m_vec_index[21] = &m_vec_cash_paid_for_policy_dividend ;		//		"֧�������������ֽ�",
	m_vec_index[22] = &m_vec_cash_paid_to_employee_and_for_employee  ;		//		"֧����ְ���Լ�Ϊְ��֧�����ֽ�",
	m_vec_index[23] = &m_vec_payments_of_all_types_of_taxes  ;		//		"֧���ĸ���˰��",
	m_vec_index[24] = &m_vec_cash_paid_for_others_relating_to_business_activities  ;		//		"֧���������뾭Ӫ��йص��ֽ�",
	m_vec_index[25] = &m_vec_sub_total_of_cash_outflows_relating_to_business_activities ;		//		"��Ӫ��ֽ�����С��",
	m_vec_index[26] = &m_vec_net_cash_flow_from_business_activities  ;		//		"��Ӫ��������ֽ���������",
	m_vec_index[27] = &m_vec_cash_flows_from_investing_activities ;		//		"����Ͷ�ʻ�������ֽ�������",
	m_vec_index[28] = &m_vec_cash_received_from_return_of_investment ;		//		"�ջ�Ͷ�����յ����ֽ�",
	m_vec_index[29] = &m_vec_cash_received_from_investments ;		//		"ȡ��Ͷ���������յ����ֽ�",
	m_vec_index[30] = &m_vec_net_cash_received_from_disposal_of_fixed_assets_intangible_assets_and_other_long_term_assets ;		//		"���ù̶��ʲ��������ʲ������������ʲ����ջص��ֽ𾻶�",
	m_vec_index[31] = &m_vec_net_cash_received_from_disposals_of_subsidiaries_and_other_business_units ;		//		"�����ӹ�˾������Ӫҵ��λ�յ����ֽ𾻶�",
	m_vec_index[32] = &m_vec_other_cash_received_relating_to_operating_activities ;		//		"�յ���������Ͷ�ʻ�йص��ֽ�",
	m_vec_index[33] = &m_vec_unknown_1 ;		//		"������Ѻ�Ͷ��ڴ�����յ����ֽ�",
	m_vec_index[34] = &m_vec_sub_total_of_cash_inflows_relating_to_investment_activities ;		//		"Ͷ�ʻ�ֽ�����С��",
	m_vec_index[35] = &m_vec_cash_paid_to_acquire_fixed_assets_intangible_assets_and_other_long_term_assents ;		//		"�����̶��ʲ��������ʲ������������ʲ���֧�����ֽ�",
	m_vec_index[36] = &m_vec_cash_paid_for_investments ;		//		"Ͷ����֧�����ֽ�",
	m_vec_index[37] = &m_vec_net_increase_of_hypothecated_loan  ;		//		"��Ѻ������Ӷ�",
	m_vec_index[38] = &m_vec_net_cash_from_subsidiary_corporation_and_other_business_entity  ;		//		"ȡ���ӹ�˾������Ӫҵ��λ֧�����ֽ𾻶�",
	m_vec_index[39] = &m_vec_other_cash_paid_relating_to_operating_activities ;		//		"֧����������Ͷ�ʻ�йص��ֽ�",
	m_vec_index[40] = &m_vec_unknown_2 ;		//		"������Ѻ�Ͷ��ڴ����֧�����ֽ�",
	m_vec_index[41] = &m_vec_sub_total_of_cash_outflows_relating_to_investment_activities ;		//		"Ͷ�ʻ�ֽ�����С��",
	m_vec_index[42] = &m_vec_net_cash_flows_from_investing_activities ;		//		"Ͷ�ʻ�������ֽ���������",
	m_vec_index[43] = &m_vec_cash_flows_from_financing_activities  ;		//		"�������ʻ�������ֽ�������",
	m_vec_index[44] = &m_vec_cash_received_from_investors ;		//		"����Ͷ���յ����ֽ�",
	m_vec_index[45] = &m_vec_cash_from_minority_stockholders_by_subsidiary_corporation  ;		//		"���У��ӹ�˾���������ɶ�Ͷ���յ����ֽ�",
	m_vec_index[46] = &m_vec_cash_from_borrowings ;		//		"ȡ�ý���յ����ֽ�",
	m_vec_index[47] = &m_vec_proceeds_from_issuance_of_bonds  ;		//		"����ծȯ�յ����ֽ�",
	m_vec_index[48] = &m_vec_cash_from_other_relevant_financing_activities  ;		//		"�յ���������ʻ�йص��ֽ�",
	m_vec_index[49] = &m_vec_sub_total_of_cash_inflows ;		//		"���ʻ�ֽ�����С��",
	m_vec_index[50] = &m_vec_cash_repayments_of_amount_borrowed ;		//		"����ծ��֧�����ֽ�",
	m_vec_index[51] = &m_vec_cash_payments_for_distrbution_of_dividends_or_profits ;		//		"�������������򳥸���Ϣ��֧�����ֽ�",
	m_vec_index[52] = &m_vec_other_cash_payment_relating_to_financing_activities ;		//		"֧����������ʻ�йص��ֽ�",
	m_vec_index[53] = &m_vec_sub_total_of_cash_outflows_relating_to_financing_activities ;	//		"���ʻ�ֽ�����С��",
	m_vec_index[54] = &m_vec_net_cash_flows_from_financing_activities ;		//		"���ʻ�������ֽ���������",
	m_vec_index[55] = &m_vec_supplemental_information ;		//		"��ע",
	m_vec_index[56] = &m_vec_effect_of_foreign_exchang_rate_changes_on_cash ;		//		"���ʱ䶯���ֽ��ֽ�ȼ����Ӱ��",
	m_vec_index[57] = &m_vec_net_increase_in_cash_and_cash_equivalents ;		//		"�ֽ��ֽ�ȼ��ﾻ���Ӷ�",
	m_vec_index[58] = &m_vec_cash_and_cash_equivalents_at_beginning_of_period  ;		//		"�ڳ��ֽ��ֽ�ȼ������",
	m_vec_index[59] = &m_vec_cash_and_cash_equivalents_at_end_of_period  ;		//		"��ĩ�ֽ��ֽ�ȼ������",
	m_vec_index[60] = &m_vec_net_profit ;		//		"������",
	m_vec_index[61] = &m_vec_minority_stockholders_interest  ;		//		"�����ɶ�Ȩ��",
	m_vec_index[62] = &m_vec_unaffirmed_investment_loss  ;		//		"δȷ�ϵ�Ͷ����ʧ",
	m_vec_index[63] = &m_vec_provision_for_assets ;		//		"�ʲ���ֵ׼��",
	m_vec_index[64] = &m_vec_depreciation_for_fixed_assets_and_so_on ;		//		"�̶��ʲ��۾ɡ������ʲ��ۺġ������������۾�",
	m_vec_index[65] = &m_vec_amortisation_of_intangible_assets ;		//		"�����ʲ�̯��",
	m_vec_index[66] = &m_vec_amortisation_of_long_term_deffered_expenses ;		//		"���ڴ�̯����̯��",
	m_vec_index[67] = &m_vec_decrease_of_deffered_expenses ;		//		"��̯���õļ���",
	m_vec_index[68] = &m_vec_addition_of_accued_expense ;		//		"Ԥ����õ�����",
	m_vec_index[69] = &m_vec_losses_on_disposal_of_fixed_assets_intangible_assets_and_other_long_term_assets ;		//		"���ù̶��ʲ��������ʲ������������ʲ�����ʧ",
	m_vec_index[70] = &m_vec_losses_on_scrapping_of_fixed_assets ;		//		"�̶��ʲ�������ʧ",
	m_vec_index[71] = &m_vec_losses_on_fair_value ;		//		"���ʼ�ֵ�䶯��ʧ",
	m_vec_index[72] = &m_vec_unknown_3 ;		//		"�����������ӣ��������٣�",
	m_vec_index[73] = &m_vec_anticipation_liabilities  ;		//		"Ԥ�Ƹ�ծ",
	m_vec_index[74] = &m_vec_finance_expense ;		//		"�������",
	m_vec_index[75] = &m_vec_losses_arsing_from_investment ;		//		"Ͷ����ʧ",
	m_vec_index[76] = &m_vec_unknown_4 ;		//		"��������˰�ʲ�����",
	m_vec_index[77] = &m_vec_unknown_5 ;		//		"��������˰��ծ����",
	m_vec_index[78] = &m_vec_decrease_in_inventories ;		//		"����ļ���",
	m_vec_index[79] = &m_vec_decrease_in_operating_receivables ;		//		"��Ӫ��Ӧ����Ŀ�ļ���",
	m_vec_index[80] = &m_vec_increase_in_operating_receivables ;		//		"��Ӫ��Ӧ����Ŀ������",
	m_vec_index[81] = &m_vec_unknown_6 ;		//		"���깤��δ�����ļ���(��:����)",
	m_vec_index[82] = &m_vec_unknown_7 ;		//		"�ѽ�����δ�깤�������(��:����)",
	m_vec_index[83] = &m_vec_others ;		//		"����",
	m_vec_index[84] = &m_vec_net_cash_flows_from_operating_activities ;		//		"��Ӫ������ֽ���������",
	m_vec_index[85] = &m_vec_debts_transfer_to_capital ;		//		"ծ��תΪ�ʱ�",
	m_vec_index[86] = &m_vec_one_year_due_convertible_bonds ;		//		"һ���ڵ��ڵĿ�ת����˾ծȯ",
	m_vec_index[87] = &m_vec_financing_rent_to_the_fixed_asset ;		//		"��������̶��ʲ�",
	m_vec_index[88] = &m_vec_cash_at_the_end_of_period ;		//		"�ֽ����ĩ���",
	m_vec_index[89] = &m_vec_cash_at_the_beginning_of_the_period ;		//		"�ֽ���ڳ����",
	m_vec_index[90] = &m_vec_cash_equivalents_at_the_end_of_the_period ;		//		"�ֽ�ȼ������ĩ���",
	m_vec_index[91] = &m_vec_cash_equivalents_at_the_beginning_of_the_period ;		//		"�ֽ�ȼ�����ڳ����",
	m_vec_index[92] = &m_vec_net_increase_in_cash_and_cash_equivalents_1 ;		//		"�ֽ��ֽ�ȼ���ľ����Ӷ�"

	/*m_vec_report_date.clear();
	for(int row=1; row<= m_vec_index.size(); row++)
		m_vec_index[row]->clear();*/

	string header[] = {
		"��λ",
		"һ����Ӫ��������ֽ�����",
		"������Ʒ���ṩ�����յ����ֽ�",
		"�ͻ�����ͬҵ��ſ�����Ӷ�",
		"���������н����Ӷ�",
		"���������ڻ��������ʽ����Ӷ�",
		"�յ�ԭ���պ�ͬ����ȡ�õ��ֽ�",
		"�յ��ٱ���ҵ���ֽ𾻶�",
		"��������Ͷ�ʿ���Ӷ�",
		"���ý����Խ����ʲ������Ӷ�",
		"��ȡ��Ϣ�������Ѽ�Ӷ����ֽ�",
		"�����ʽ����Ӷ�",
		"�ع�ҵ���ʽ����Ӷ�",
		"�յ���˰�ѷ���",
		"�յ��������뾭Ӫ��йص��ֽ�",
		"��Ӫ��ֽ�����С��",
		"������Ʒ����������֧�����ֽ�",
		"�ͻ���������Ӷ�",
		"����������к�ͬҵ������Ӷ�",
		"֧��ԭ���պ�ͬ�⸶������ֽ�",
		"֧����Ϣ�������Ѽ�Ӷ����ֽ�",
		"֧�������������ֽ�",
		"֧����ְ���Լ�Ϊְ��֧�����ֽ�",
		"֧���ĸ���˰��",
		"֧���������뾭Ӫ��йص��ֽ�",
		"��Ӫ��ֽ�����С��",
		"��Ӫ��������ֽ���������",
		"����Ͷ�ʻ�������ֽ�����",
		"�ջ�Ͷ�����յ����ֽ�",
		"ȡ��Ͷ���������յ����ֽ�",
		"���ù̶��ʲ��������ʲ������������ʲ����ջص��ֽ𾻶�",
		"�����ӹ�˾������Ӫҵ��λ�յ����ֽ𾻶�",
		"�յ���������Ͷ�ʻ�йص��ֽ�",
		"������Ѻ�Ͷ��ڴ�����յ����ֽ�",
		"Ͷ�ʻ�ֽ�����С��",
		"�����̶��ʲ��������ʲ������������ʲ���֧�����ֽ�",
		"Ͷ����֧�����ֽ�",
		"��Ѻ������Ӷ�",
		"ȡ���ӹ�˾������Ӫҵ��λ֧�����ֽ𾻶�",
		"֧����������Ͷ�ʻ�йص��ֽ�",
		"������Ѻ�Ͷ��ڴ����֧�����ֽ�",
		"Ͷ�ʻ�ֽ�����С��",
		"Ͷ�ʻ�������ֽ���������",
		"�������ʻ�������ֽ�����",
		"����Ͷ���յ����ֽ�",
		"���У��ӹ�˾���������ɶ�Ͷ���յ����ֽ�",
		"ȡ�ý���յ����ֽ�",
		"����ծȯ�յ����ֽ�",
		"�յ���������ʻ�йص��ֽ�",
		"���ʻ�ֽ�����С��",
		"����ծ��֧�����ֽ�",
		"�������������򳥸���Ϣ��֧�����ֽ�",
		"֧����������ʻ�йص��ֽ�",
		"���ʻ�ֽ�����С��",
		"���ʻ�������ֽ���������",
		"��ע",
		"�ġ����ʱ䶯���ֽ��ֽ�ȼ����Ӱ��",
		"�塢�ֽ��ֽ�ȼ��ﾻ���Ӷ�",
		"��:�ڳ��ֽ��ֽ�ȼ������",
		"������ĩ�ֽ��ֽ�ȼ������",
		"������",
		"�����ɶ�Ȩ��",
		"δȷ�ϵ�Ͷ����ʧ",
		"�ʲ���ֵ׼��",
		"�̶��ʲ��۾ɡ������ʲ��ۺġ������������۾�",
		"�����ʲ�̯��",
		"���ڴ�̯����̯��",
		"��̯���õļ���",
		"Ԥ����õ�����",
		"���ù̶��ʲ��������ʲ������������ʲ�����ʧ",
		"�̶��ʲ�������ʧ",
		"���ʼ�ֵ�䶯��ʧ",
		"�����������ӣ��������٣�",
		"Ԥ�Ƹ�ծ",
		"�������",
		"Ͷ����ʧ",
		"��������˰�ʲ�����",
		"��������˰��ծ����",
		"����ļ���",
		"��Ӫ��Ӧ����Ŀ�ļ���",
		"��Ӫ��Ӧ����Ŀ������",
		"���깤��δ�����ļ���(��:����)",
		"�ѽ�����δ�깤�������(��:����)",
		"����",
		"��Ӫ������ֽ���������",
		"ծ��תΪ�ʱ�",
		"һ���ڵ��ڵĿ�ת����˾ծȯ",
		"��������̶��ʲ�",
		"�ֽ����ĩ���",
		"�ֽ���ڳ����",
		"�ֽ�ȼ������ĩ���",
		"�ֽ�ȼ�����ڳ����",
		"�ֽ��ֽ�ȼ���ľ����Ӷ�"
	};

	for(int i=0; i< 93; i++)
	{
		m_row_name_2_index[header[i]] = i;
	}
}


CCashFlows::CCashFlows(void)
{
	Initialize();
}

CCashFlows::CCashFlows(const CCashFlows& rhs)
{
	if (this != &rhs)
	{
		Initialize();
		ReleaseVector();

		m_vec_report_date = rhs.m_vec_report_date;
		m_nRowNum = rhs.m_nRowNum;
		m_nCode = rhs.m_nCode;
		m_ConnectString = rhs.m_ConnectString;
		m_initial_report_date = rhs.m_initial_report_date;

		for(int row=1; row<= m_vec_index.size(); row++)
		{
			if(rhs.m_vec_index.count(row)>0)
			{
				vector<double> * pMap = rhs.m_vec_index.find(row)->second;
				vector<double>::iterator it = pMap->begin();
				vector<double>::iterator it_end = pMap->end();
				for(; it!=it_end; it++)
				{
					//m_vec_index[row]->insert(*it);
					m_vec_index[row]->insert(m_vec_index[row]->end(),*it);
				}
			}

		}
	}

}

CCashFlows::~CCashFlows(void)
{
	Initialize();
	ReleaseVector();
}

CCashFlows& CCashFlows::operator=(const CCashFlows& rhs)
{
	if (this != &rhs)
	{
		Initialize();
		ReleaseVector();

		m_vec_report_date = rhs.m_vec_report_date;
		m_nRowNum = rhs.m_nRowNum;
		m_nCode = rhs.m_nCode;
		m_ConnectString = rhs.m_ConnectString;
		m_initial_report_date = rhs.m_initial_report_date;

		for(int row=1; row<= m_vec_index.size(); row++)
		{
			if(rhs.m_vec_index.count(row)>0)
			{
				vector<double> * pMap = rhs.m_vec_index.find(row)->second;
				vector<double>::iterator it = pMap->begin();
				vector<double>::iterator it_end = pMap->end();
				for(; it!=it_end; it++)
				{
					//m_vec_index[row]->insert(*it);
					m_vec_index[row]->insert(m_vec_index[row]->end(),*it);
				}
			}

		}
	}
	return *this;
}


int CCashFlows::CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	
	string strRet;
	for(int row = 0; row < arrayData.size(); row++)
	{
		//	���� ��һ�е� ���������ƣ�ƥ��������
		string  indexName = arrayData[row][0];
		if(m_row_name_2_index.count(indexName)==0)
		{
			//return CSV_CHECK_FORMAT_ERROR;
			if(!strRet.empty())
				strRet += ",";
			strRet += indexName;
		}
	}

	if(!strRet.empty())
	{
		if(strRet != "���У��ӹ�˾֧���������ɶ��Ĺ���������")
		{
			stringstream ss;
			ss << "�ֽ������� Format Error�� code = " << m_nCode << ", " << strRet;
			LOG4CPLUS_DEBUG(g_logger, ss.str());

			return CSV_CHECK_FORMAT_ERROR;
		}
	}
	return CSV_CHECK_NO_ERROR;
}


CStockDataModel * CCashFlows::NewCopy()
{
	CCashFlows * pTrading = new CCashFlows();
	pTrading->m_nRowNum = m_nRowNum;
	
	pTrading->m_vec_report_date = m_vec_report_date;

	return pTrading;
}

string CCashFlows::GetDownloadUrl()
{
	string url ="";
	char cmdline[512]; 
	CString tmp;

	
	string::size_type pos = GetCsvFileName().find(".csv");
	string xlsFileName = GetCsvFileName().substr(0, pos);
	xlsFileName += ".xls";

	/*tmp.Format("http://money.finance.sina.com.cn/corp/go.php/vDOWN_CashFlow/displaytype/4/stockid/%06d/ctrl/all.phtml", \
		m_nCode);  
	string  strTmp = tmp.GetBuffer();
	string  strGBK1 =CUrlUtils::PostUrlOfSouhu(tmp.GetBuffer(),NULL);

	CStdioFile  targetFile(xlsFileName.c_str(), CFile::modeWrite|CFile::shareDenyWrite|CFile::modeCreate|CFile::typeText);
	targetFile.WriteString(strGBK1.c_str());
	targetFile.Close();*/

	/*ֹͣʹ�� wget.exe ��������*/
	//return "";

	//////////////////////////////////////////////////////////////////////////
	//	���ڱ����Ѿ��ɹ����ص� �����Ը�����

	if(CheckDownloadFileInfo(xlsFileName)>0)
		return url;

	tmp.Format("wget.exe http://money.finance.sina.com.cn/corp/go.php/vDOWN_CashFlow/displaytype/4/stockid/%06d/ctrl/all.phtml -O %s", \
		m_nCode, xlsFileName.c_str());    

	sprintf(cmdline,"%s",tmp);    
	url = string(cmdline);
	return url;
}

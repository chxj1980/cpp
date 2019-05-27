#include "StdAfx.h"
#include "Balance.h"
#include "UrlUtils.h"

void CBalance::Initialize(void)
{
	m_strChineseName = _T("�ʲ���ծ��");
	m_strEnglishName = "Balance";

	// m_vec_index �������±� �����ݿ����ֶ� colume_x �е� x ���Ӧ
	m_vec_index[1] =	&m_vec_current_assets		;  //		"�����ʲ�",                                                 
	m_vec_index[2] =	&m_vec_cash		;  //		"�����ʽ�",                                                           
	m_vec_index[3] =	&m_vec_provision_of_settlement_fund		;  //		"���㱸����",                                 
	m_vec_index[4] =	&m_vec_funds_lent		;  //		"����ʽ�",                                                     
	m_vec_index[5] =	&m_vec_financial_assets_held_for_trading		;  //		"�����Խ����ʲ�",                       
	m_vec_index[6] =	&m_vec_derivative_financial_assets		;  //		"���������ʲ�",                               
	m_vec_index[07] =	&m_vec_notes_receivable		;  //		"Ӧ��Ʊ��",                                               
	m_vec_index[8] =	&m_vec_accounts_receivable		;  //		"Ӧ���˿�",                                           
	m_vec_index[9] =	&m_vec_advances_to_suppliers		;  //		"Ԥ������",                                         
	m_vec_index[10] =	&m_vec_insurance_premiums_receivable		;  //		"Ӧ�ձ���",                                 
	m_vec_index[11] =	&m_vec_cession_premiums_receivable		;  //		"Ӧ�շֱ��˿�",                               
	m_vec_index[12] =	&m_vec_provision_of_cession_receivable		;  //		"Ӧ�շֱ���ͬ׼����",                     
	m_vec_index[13] =	&m_vec_interests_receivable		;  //		"Ӧ����Ϣ",                                           
	m_vec_index[14] =	&m_vec_dividends_receivable		;  //		"Ӧ�չ���",                                           
	m_vec_index[15] =	&m_vec_other_receivable		;  //		"����Ӧ�տ�",                                             
	m_vec_index[16] =	&m_vec_export_tax_rebate		;  //		"Ӧ�ճ�����˰",                                         
	m_vec_index[17] =	&m_vec_subsidy_receivable		;  //		"Ӧ�ղ�����",                                           
	m_vec_index[18] =	&m_vec_receivable_deposit		;  //		"Ӧ�ձ�֤��",                                           
	m_vec_index[19] =	&m_vec_internal_receivables		;  //		"�ڲ�Ӧ�տ�",                                         
	m_vec_index[20] =	&m_vec_buying_and_selling_financial_assets		;  //		"���뷵�۽����ʲ�",                   
	m_vec_index[21] =	&m_vec_inventories		;  //		"���",                                                       
	m_vec_index[22] =	&m_vec_deferred_expenses 		;  //		"��̯����",                                             
	m_vec_index[23] =	&m_vec_profit_and_loss_to_be_treated		;  //		"�����������ʲ�����",                       
	m_vec_index[24] =	&m_vec_non_current_assets_maturing_within_one_year		;  //		"һ���ڵ��ڵķ������ʲ�",     
	m_vec_index[25] =	&m_vec_other_current_assets		;  //		"���������ʲ�",                                       
	m_vec_index[26] =	&m_vec_total_current_assets		;  //		"�����ʲ��ϼ�",                                       
	m_vec_index[27] =	&m_vec_non_current_assets		;  //		"�������ʲ�",                                           
	m_vec_index[28] =	&m_vec_loans_and_payments_on_behalf 		;  //		"���Ŵ�����",                           
	m_vec_index[29] =	&m_vec_available_for_sale_financial_assets		;  //		"�ɹ����۽����ʲ�",                   
	m_vec_index[30] =	&m_vec_held_to_maturity_investments		;  //		"����������Ͷ��",                             
	m_vec_index[31] =	&m_vec_long_term_receivables		;  //		"����Ӧ�տ�",                                       
	m_vec_index[32] =	&m_vec_long_term_equity_investments		;  //		"���ڹ�ȨͶ��",                               
	m_vec_index[33] =	&m_vec_other_long_term_investments		;  //		"��������Ͷ��",                               
	m_vec_index[34] =	&m_vec_investment_real_estates		;  //		"Ͷ���Է��ز�",                                   
	m_vec_index[35] =	&m_vec_original_value_of_fixed_assets 		;  //		"�̶��ʲ�ԭֵ",                           
	m_vec_index[36] =	&m_vec_accumulated_depreciation		;  //		"�ۼ��۾�",                                       
	m_vec_index[37] =	&m_vec_fixed_assets_net_value		;  //		"�̶��ʲ���ֵ",                                     
	m_vec_index[38] =	&m_vec_fixed_assets_impairment_provision		;  //		"�̶��ʲ���ֵ׼��",                     
	m_vec_index[39] =	&m_vec_fixed_assets_net_book_value		;  //		"�̶��ʲ�����",                               
	m_vec_index[40] =	&m_vec_construction_in_progress		;  //		"�ڽ�����",                                       
	m_vec_index[41] =	&m_vec_construction_supplies		;  //		"��������",                                         
	m_vec_index[42] =	&m_vec_fixed_assets_pending_disposal		;  //		"�̶��ʲ�����",                             
	m_vec_index[43] =	&m_vec_bearer_biological_assets		;  //		"�����������ʲ�",                                 
	m_vec_index[44] =	&m_vec_public_welfare_biological_assets		;  //		"�����������ʲ�",                         
	m_vec_index[45] =	&m_vec_oil_and_natural_gas_assets		;  //		"�����ʲ�",                                     
	m_vec_index[46] =	&m_vec_intangibel_assets		;  //		"�����ʲ�",                                             
	m_vec_index[47] =	&m_vec_research_and_development_costs		;  //		"����֧��",                                 
	m_vec_index[48] =	&m_vec_goodwill		;  //		"����",                                                           
	m_vec_index[49] =	&m_vec_long_term_deferred_expenses		;  //		"���ڴ�̯����",                               
	m_vec_index[50] =	&m_vec_circulation_right_for_equity_separation 		;  //		"��Ȩ������ͨȨ",                 
	m_vec_index[51] =	&m_vec_deferred_tax_assets		;  //		"��������˰�ʲ�",                                     
	m_vec_index[52] =	&m_vec_other_non_current_assets		;  //		"�����������ʲ�",                                 
	m_vec_index[53] =	&m_vec_total_non_current_assets		;  //		"�������ʲ��ϼ�",                                 
	m_vec_index[54] =	&m_vec_total_assets		;  //		"�ʲ��ܼ�",                                                   
	m_vec_index[55] =	&m_vec_current_debt		;  //		"������ծ",                                                   
	m_vec_index[56] =	&m_vec_short_term_borrowings		;  //		"���ڽ��",                                         
	m_vec_index[57] =	&m_vec_borrowings_from_central_bank		;  //		"���������н��",                             
	m_vec_index[58] =	&m_vec_deposits_from_customers_and_interbank		;  //		"���մ�ͬҵ���",               
	m_vec_index[59] =	&m_vec_deposit_funds		;  //		"�����ʽ�",                                                 
	m_vec_index[60] =	&m_vec_financial_assets_held_for_liabilities		;  //		"�����Խ��ڸ�ծ",                   
	m_vec_index[61] =	&m_vec_derivative_financial_liabilities		;  //		"�������ڸ�ծ",                           
	m_vec_index[62] =	&m_vec_notes_payable		;  //		"Ӧ��Ʊ��",                                                 
	m_vec_index[63] =	&m_vec_accounts_payable		;  //		"Ӧ���˿�",                                               
	m_vec_index[64] =	&m_vec_advances_from_customers		;  //		"Ԥ�տ���",                                       
	m_vec_index[65] =	&m_vec_funds_from_sales_of_financial_assets_with_repurchasement_agreement		;  //		"�����ع������ʲ���",
	m_vec_index[66] =	&m_vec_handling_charges_and_commissions_payable		;  //		"Ӧ�������Ѽ�Ӷ��",               
	m_vec_index[67] =	&m_vec_employee_benefits_payable		;  //		"Ӧ��ְ��н��",                                 
	m_vec_index[68] =	&m_vec_taxes_and_surcharges_payable		;  //		"Ӧ��˰��",                                   
	m_vec_index[69] =	&m_vec_interests_payable		;  //		"Ӧ����Ϣ",                                             
	m_vec_index[70] =	&m_vec_dividends_payable		;  //		"Ӧ������",                                             
	m_vec_index[71] =	&m_vec_other_accounts_payable		;  //		"����Ӧ����",                                       
	m_vec_index[72] =	&m_vec_margin_payable		;  //		"Ӧ����֤��",                                               
	m_vec_index[73] =	&m_vec_internal_accounts_payable		;  //		"�ڲ�Ӧ����",                                   
	m_vec_index[74] =	&m_vec_other_payables		;  //		"����Ӧ����",                                               
	m_vec_index[75] =	&m_vec_accrued_expenses 		;  //		"Ԥ�����",                                             
	m_vec_index[76] =	&m_vec_expected_current_liabilities		;  //		"Ԥ��������ծ",                               
	m_vec_index[77] =	&m_vec_cession_insurance_premiums_payable		;  //		"Ӧ���ֱ��˿�",                         
	m_vec_index[78] =	&m_vec_provision_for_insurance_contracts		;  //		"���պ�ͬ׼����",                       
	m_vec_index[79] =	&m_vec_funds_received_as_agent_of_stock_exchange 		;  //		"��������֤ȯ��",               
	m_vec_index[80] =	&m_vec_funds_received_as_stock_underwrite		;  //		"�������֤ȯ��",                       
	m_vec_index[81] =	&m_vec_international_ticket_clearing		;  //		"����Ʊ֤����",                             
	m_vec_index[82] =	&m_vec_domestic_ticket_clearing		;  //		"����Ʊ֤����",                                   
	m_vec_index[83] =	&m_vec_deferred_income		;  //		"��������",                                               
	m_vec_index[84] =	&m_vec_short_term_bonds_payable		;  //		"Ӧ������ծȯ",                                   
	m_vec_index[85] =	&m_vec_non_current_liabilities_maturing_within_one_year		;  //		"һ���ڵ��ڵķ�������ծ", 
	m_vec_index[86] =	&m_vec_other_current_liablities		;  //		"����������ծ",                                   
	m_vec_index[87] =	&m_vec_total_current_liabilities		;  //		"������ծ�ϼ�",                                 
	m_vec_index[88] =	&m_vec_non_current_liabilities		;  //		"��������ծ",                                     
	m_vec_index[89] =	&m_vec_long_term_loans		;  //		"���ڽ��",                                               
	m_vec_index[90] =	&m_vec_debentures_payable		;  //		"Ӧ��ծȯ",                                             
	m_vec_index[91] =	&m_vec_long_term_payables		;  //		"����Ӧ����",                                           
	m_vec_index[92] =	&m_vec_specific_payable		;  //		"ר��Ӧ����",                                             
	m_vec_index[93] =	&m_vec_expected_non_current_liabilities		;  //		"Ԥ�Ʒ�������ծ",                         
	m_vec_index[94] =	&m_vec_deferred_tax_liabilities		;  //		"��������˰��ծ",                                 
	m_vec_index[95] =	&m_vec_other_non_current_liablities		;  //		"������������ծ",                             
	m_vec_index[96] =	&m_vec_total_non_current_liabilities		;  //		"��������ծ�ϼ�",                           
	m_vec_index[97] =	&m_vec_total_liability		;  //		"��ծ�ϼ�",                                               
	m_vec_index[98] =	&m_vec_owners_equity		;  //		"������Ȩ��",                                               
	m_vec_index[99] =	&m_vec_registered_capital		;  //		"ʵ���ʱ�(��ɱ�)"                                      
	m_vec_index[100] =	&m_vec_capital_surplus		;  //		"�ʱ�����"                                                
	m_vec_index[101] =	&m_vec_treasury_stock		;  //		"����"                                                  
	m_vec_index[102] =	&m_vec_special_reserve		;  //		"ר���"                                                
	m_vec_index[103] =	&m_vec_surplus_reserve		;  //		"ӯ�๫��",                                               
	m_vec_index[104] =	&m_vec_provision_for_normal_risks		;  //		"һ�����׼��",                               
	m_vec_index[105] =	&m_vec_not_sure_investment_losses		;  //		"δȷ����Ͷ����ʧ",                           
	m_vec_index[106] =	&m_vec_undistributed_profits		;  //		"δ��������",                                       
	m_vec_index[107] =	&m_vec_quasi_cash_dividend		;  //		"������ֽ����",                                     
	m_vec_index[108] =	&m_vec_exchange_differences_on_translating_foreign_operations 		;  //		"��ұ���������"
	m_vec_index[109] =	&m_vec_total_owners_equity_belongs_to_parent_company		;  //		"������ĸ��˾�ɶ�Ȩ��ϼ�", 
	m_vec_index[110] =	&m_vec_minority_interest		;  //		"�����ɶ�Ȩ��",                                         
	m_vec_index[111] =	&m_vec_total_owners_equity		;  //		"������Ȩ��(��ɶ�Ȩ��)�ϼ�",                         
	m_vec_index[112] =	&m_vec_total_liabilities_and_owners_equity		;  //		"��ծ��������Ȩ��(��ɶ�Ȩ��)�ܼ�"    

	/*m_vec_report_date.clear();
	for(int row=1; row<= m_vec_index.size(); row++)
		m_vec_index[row]->clear();*/

	string header[] = {
		"��λ",
		"�����ʲ�",
		"�����ʽ�",
		"���㱸����",
		"����ʽ�",
		"�����Խ����ʲ�",
		"���������ʲ�",
		"Ӧ��Ʊ��",
		"Ӧ���˿�",
		"Ԥ������",
		"Ӧ�ձ���",
		"Ӧ�շֱ��˿�",
		"Ӧ�շֱ���ͬ׼����",
		"Ӧ����Ϣ",
		"Ӧ�չ���",
		"����Ӧ�տ�",
		"Ӧ�ճ�����˰",
		"Ӧ�ղ�����",
		"Ӧ�ձ�֤��",
		"�ڲ�Ӧ�տ�",
		"���뷵�۽����ʲ�",
		"���",
		"��̯����",
		"�����������ʲ�����",
		"һ���ڵ��ڵķ������ʲ�",
		"���������ʲ�",
		"�����ʲ��ϼ�",
		"�������ʲ�",
		"���Ŵ�����",
		"�ɹ����۽����ʲ�",
		"����������Ͷ��",
		"����Ӧ�տ�",
		"���ڹ�ȨͶ��",
		"��������Ͷ��",
		"Ͷ���Է��ز�",
		"�̶��ʲ�ԭֵ",
		"�ۼ��۾�",
		"�̶��ʲ���ֵ",
		"�̶��ʲ���ֵ׼��",
		"�̶��ʲ�����",
		"�ڽ�����",
		"��������",
		"�̶��ʲ�����",
		"�����������ʲ�",
		"�����������ʲ�",
		"�����ʲ�",
		"�����ʲ�",
		"����֧��",
		"����",
		"���ڴ�̯����",
		"��Ȩ������ͨȨ",
		"��������˰�ʲ�",
		"�����������ʲ�",
		"�������ʲ��ϼ�",
		"�ʲ��ܼ�",
		"������ծ",
		"���ڽ��",
		"���������н��",
		"���մ�ͬҵ���",
		"�����ʽ�",
		"�����Խ��ڸ�ծ",
		"�������ڸ�ծ",
		"Ӧ��Ʊ��",
		"Ӧ���˿�",
		"Ԥ�տ���",
		"�����ع������ʲ���",
		"Ӧ�������Ѽ�Ӷ��",
		"Ӧ��ְ��н��",
		"Ӧ��˰��",
		"Ӧ����Ϣ",
		"Ӧ������",
		"����Ӧ����",
		"Ӧ����֤��",
		"�ڲ�Ӧ����",
		"����Ӧ����",
		"Ԥ�����",
		"Ԥ��������ծ",
		"Ӧ���ֱ��˿�",
		"���պ�ͬ׼����",
		"��������֤ȯ��",
		"�������֤ȯ��",
		"����Ʊ֤����",
		"����Ʊ֤����",
		"��������",
		"Ӧ������ծȯ",
		"һ���ڵ��ڵķ�������ծ",
		"����������ծ",
		"������ծ�ϼ�",
		"��������ծ",
		"���ڽ��",
		"Ӧ��ծȯ",
		"����Ӧ����",
		"ר��Ӧ����",
		"Ԥ�Ʒ�������ծ",
		"��������˰��ծ",
		"������������ծ",
		"��������ծ�ϼ�",
		"��ծ�ϼ�",
		"������Ȩ��",
		"ʵ���ʱ�(��ɱ�)",
		"�ʱ�����",
		"��������",
		"ר���",
		"ӯ�๫��",
		"һ�����׼��",
		"δȷ����Ͷ����ʧ",
		"δ��������",
		"������ֽ����",
		"��ұ���������",
		"������ĸ��˾�ɶ�Ȩ��ϼ�",
		"�����ɶ�Ȩ��",
		"������Ȩ��(��ɶ�Ȩ��)�ϼ�",
		"��ծ��������Ȩ��(��ɶ�Ȩ��)�ܼ�"
	};

	for(int i=0; i< 113; i++)
	{
		m_row_name_2_index[header[i]] = i;
	}
}


CBalance::CBalance(void)
{
	Initialize();
}

CBalance::CBalance(const CBalance& rhs)
{
	if (this != &rhs)
	{
		Initialize();
		ReleaseVector();

		m_vec_report_date = rhs.m_vec_report_date;
		m_nRowNum = rhs.m_nRowNum;
		m_nCode = rhs.m_nCode;
		m_initial_report_date = rhs.m_initial_report_date;
		m_ConnectString = rhs.m_ConnectString;
		for(int row=1; row<= m_vec_index.size(); row++)
		{
			if(rhs.m_vec_index.count(row)>0)
			{
				vector<double> * pMap = rhs.m_vec_index.find(row)->second;
				vector<double>::iterator it = pMap->begin();
				vector<double>::iterator it_end = pMap->end();
				for(; it!=it_end; it++)
				{
					m_vec_index[row]->insert(m_vec_index[row]->end(),*it);
				}
			}

		}
	}

}


CBalance& CBalance::operator=(const CBalance& rhs)
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


CBalance::~CBalance(void)
{
	Initialize();
	ReleaseVector();

}



int CBalance::CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
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
				strRet += "|";
			strRet += indexName;
		}
	}

	if(!strRet.empty())
	{
		if(strRet!="����Ϊ���д��۵��ʲ�|һ���ڵĵ�������|����Ӧ��ְ��н��|���ڵ�������|�����ۺ�����")
		{
			stringstream ss;
			ss << "�ʲ���ծ�� Format Error�� code = " << m_nCode << ", " << strRet;
			LOG4CPLUS_DEBUG(g_logger, ss.str());

			return CSV_CHECK_FORMAT_ERROR;
		}
	}
	return CSV_CHECK_NO_ERROR;
}

string CBalance::GetDownloadUrl()
{
	string url = "";
	char cmdline[512]; 
	CString tmp;     

	string::size_type pos = GetCsvFileName().find(".csv");
	string xlsFileName = GetCsvFileName().substr(0, pos);
	xlsFileName += ".xls";

	/*tmp.Format("http://money.finance.sina.com.cn/corp/go.php/vDOWN_BalanceSheet/displaytype/4/stockid/%06d/ctrl/all.phtml", \
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

	tmp.Format("wget.exe http://money.finance.sina.com.cn/corp/go.php/vDOWN_BalanceSheet/displaytype/4/stockid/%06d/ctrl/all.phtml -O %s", \
		m_nCode, xlsFileName.c_str());    

	sprintf(cmdline,"%s",tmp);    
	url = string(cmdline);
	return url;
}


CStockDataModel * CBalance::NewCopy()
{
	CBalance * pTrading = new CBalance();
	pTrading->m_nRowNum = m_nRowNum;

	pTrading->m_vec_report_date = m_vec_report_date;

	return pTrading;
}
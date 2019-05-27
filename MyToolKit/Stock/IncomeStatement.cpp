#include "StdAfx.h"
#include "IncomeStatement.h"
#include "UrlUtils.h"


void CIncomeStatement::Initialize(void)
{
	m_strChineseName = _T("�����");
	m_strEnglishName = "IncomeStatement";

	// m_vec_index[0] = m_vec_report_date;
	m_vec_index[1] = &m_vec_overall_sales;		//	Ӫҵ������
	m_vec_index[2] = &m_vec_sales_from_operations;		//	Ӫҵ����
	m_vec_index[3] = &m_vec_interest_income;						//	��Ϣ����
	m_vec_index[4] = &m_vec_insurance_premiums_earned;						//	��׬����
	m_vec_index[5] = &m_vec_handling_charges_and_commissions_income;			//	�����Ѽ�Ӷ������
	m_vec_index[6] = &m_vec_real_estate_sales_revenue;						//	���ز���������
	m_vec_index[7] = &m_vec_income_from_other_operations;						//	����ҵ������
	m_vec_index[8] = &m_vec_overall_costs;						//	����Ӫҵ�ܳɱ�
	m_vec_index[9] = &m_vec_cost_of_operations;					//	Ӫҵ�ɱ�
	m_vec_index[10] = &m_vec_interest_expenses;						//	��Ϣ֧��
	m_vec_index[11] = &m_vec_handling_charges_and_commissions_expenses;						//	�����Ѽ�Ӷ��֧��
	m_vec_index[12] = &m_vec_real_estate_sales_cost;						//	���ز����۳ɱ�
	m_vec_index[13] = &m_vec_research_and_development_expenses;			//	�з�����
	m_vec_index[14] = &m_vec_refund_of_insurance_premiums;						//	�˱���
	m_vec_index[15] = &m_vec_net_payments_for_insurance_claims;						//	�⸶֧������
	m_vec_index[16] = &m_vec_net_provision_for_insurance_contracts;			//	��ȡ���պ�ͬ׼���𾻶�
	m_vec_index[17] = &m_vec_commissions_on_insurance_policies;						//	��������֧��
	m_vec_index[18] = &m_vec_cession_charges;						//	�ֱ�����
	m_vec_index[19] = &m_vec_cost_of_other_operations;						//	����ҵ��ɱ�
	m_vec_index[20] = &m_vec_sales_tax_and_additions;						//	Ӫҵ˰�𼰸���
	m_vec_index[21] = &m_vec_selling_and_distribution_expenses;						//	���۷���
	m_vec_index[22] = &m_vec_general_and_administrative_expenses;						//	�������
	m_vec_index[23] = &m_vec_financial_expenses;						//	�������
	m_vec_index[24] = &m_vec_impairment_loss_on_assets;						//	�ʲ���ֵ��ʧ
	m_vec_index[25] = &m_vec_gain_or_loss_from_changes_in_fair_values;						//	���ʼ�ֵ�䶯����
	m_vec_index[26] = &m_vec_investment_income;						//	Ͷ������
	m_vec_index[27] = &m_vec_investment_income_from_joint_ventures_and_affiliates;			//	����Ӫ��ҵ�ͺ�Ӫ��ҵ��Ͷ������
	m_vec_index[28] = &m_vec_gain_or_loss_on_foreign_exchange_transactions;						//	�������
	m_vec_index[29] = &m_vec_futures_gains_and_losses;						//	�ڻ�����
	m_vec_index[30] = &m_vec_managed_revenue;						//	�й�����
	m_vec_index[31] = &m_vec_subsidy_income;						//	��������
	m_vec_index[32] = &m_vec_other_business_profits;						//	����ҵ������
	m_vec_index[33] = &m_vec_profit_from_operations;						//	����Ӫҵ����
	m_vec_index[34] = &m_vec_non_operating_profit;						//	Ӫҵ������
	m_vec_index[35] = &m_vec_non_operating_expenses;						//	Ӫҵ��֧��
	m_vec_index[36] = &m_vec_losses_from_disposal_of_non_current_assets;			//	�������ʲ�������ʧ
	m_vec_index[37] = &m_vec_profit_before_tax;						//	�����ܶ�
	m_vec_index[38] = &m_vec_income_tax_expenses;						//	����˰����
	m_vec_index[39] = &m_vec_unrecognized_investment_losses;						//	δȷ��Ͷ����ʧ
	m_vec_index[40] = &m_vec_net_profit;						//	�ġ�������
	m_vec_index[41] = &m_vec_net_profit_belonging_to_parent_company;						//	������ĸ��˾�����ߵľ�����
	m_vec_index[42] = &m_vec_minority_interest;						//	�����ɶ�����
	m_vec_index[43] = &m_vec_earnings_per_share;						//	�塢ÿ������
	m_vec_index[44] = &m_vec_basic_earnings_per_share;					//	����ÿ������
	m_vec_index[45] = &m_vec_diluted_earnings_per_share;						//	ϡ��ÿ������
	m_vec_index[46] = &m_vec_other_consolidated_income;						//	���������ۺ�����
	m_vec_index[47] = &m_vec_total_consolidated_income;						//	�ߡ��ۺ������ܶ�
	m_vec_index[48] = &m_vec_consolidated_income_belonging_to_parent_company;	//	������ĸ��˾�����ߵ��ۺ������ܶ�
	m_vec_index[49] = &m_vec_consolidated_income_belonging_to_minority_shareholders;	//	�����������ɶ����ۺ������ܶ�


	string header[] = {
		"��λ",
		"һ��Ӫҵ������",
		"Ӫҵ����",
		"��Ϣ����",
		"��׬����",
		"�����Ѽ�Ӷ������",
		"���ز���������",
		"����ҵ������",
		"����Ӫҵ�ܳɱ�",
		"Ӫҵ�ɱ�",
		"��Ϣ֧��",
		"�����Ѽ�Ӷ��֧��",
		"���ز����۳ɱ�",
		"�з�����",
		"�˱���",
		"�⸶֧������",
		"��ȡ���պ�ͬ׼���𾻶�",
		"��������֧��",
		"�ֱ�����",
		"����ҵ��ɱ�",
		"Ӫҵ˰�𼰸���",
		"���۷���",
		"�������",
		"�������",
		"�ʲ���ֵ��ʧ",
		"���ʼ�ֵ�䶯����",
		"Ͷ������",
		"����:����Ӫ��ҵ�ͺ�Ӫ��ҵ��Ͷ������",
		"�������",
		"�ڻ�����",
		"�й�����",
		"��������",
		"����ҵ������",
		"����Ӫҵ����",
		"��:Ӫҵ������",
		"����Ӫҵ��֧��",
		"���У��������ʲ�������ʧ",
		"�ġ������ܶ�",
		"��������˰����",
		"δȷ��Ͷ����ʧ",
		"�塢������",
		"������ĸ��˾�����ߵľ�����",
		"�����ɶ�����",
		"����ÿ������",
		"����ÿ������(Ԫ/��)",
		"ϡ��ÿ������(Ԫ/��)",
		"�ߡ������ۺ�����",
		"�ˡ��ۺ������ܶ�",
		"������ĸ��˾�����ߵ��ۺ������ܶ�",
		"�����������ɶ����ۺ������ܶ�"
	};

	for(int i=0; i< 50; i++)
	{
		m_row_name_2_index[header[i]] = i;
	}

	
}


CIncomeStatement::CIncomeStatement(void)
{
	Initialize();
}

CIncomeStatement::CIncomeStatement(const CIncomeStatement& rhs)
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


CIncomeStatement& CIncomeStatement::operator=(const CIncomeStatement& rhs)
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


CIncomeStatement::~CIncomeStatement(void)
{
	Initialize();
	ReleaseVector();
}


int CIncomeStatement::CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
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
		stringstream ss;
		ss << "����� Format Error�� code = " << m_nCode << ", " << strRet;
		LOG4CPLUS_DEBUG(g_logger, ss.str());
		return CSV_CHECK_FORMAT_ERROR;
	}
	return CSV_CHECK_NO_ERROR;
}

CStockDataModel * CIncomeStatement::NewCopy()
{
	CIncomeStatement * pTrading = new CIncomeStatement();
	pTrading->m_nRowNum = m_nRowNum;
	
	pTrading->m_vec_report_date = m_vec_report_date;

	return pTrading;
}

string CIncomeStatement::GetDownloadUrl()
{
	string url="";
	char cmdline[512]; 
	CString tmp;  

	string::size_type pos = GetCsvFileName().find(".csv");
	string xlsFileName = GetCsvFileName().substr(0, pos);
	xlsFileName += ".xls";

	/*tmp.Format("http://money.finance.sina.com.cn/corp/go.php/vDOWN_ProfitStatement/displaytype/4/stockid/%06d/ctrl/all.phtml", \
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

	tmp.Format("wget.exe http://money.finance.sina.com.cn/corp/go.php/vDOWN_ProfitStatement/displaytype/4/stockid/%06d/ctrl/all.phtml -O %s", \
		m_nCode, xlsFileName.c_str());    

	sprintf(cmdline,"%s",tmp);    
	url = string(cmdline);

	return url;
}

double CIncomeStatement::EstimateYearProfits()
{
	double nProfit = -1;
	if(m_vec_report_date.size()>0)
	{
		COleDateTime odt_in ;
		odt_in.ParseDateTime( m_vec_report_date[m_vec_report_date.size()-1].c_str());
		int mon = odt_in.GetMonth();
		int day = odt_in.GetDay();

		nProfit = m_vec_net_profit_belonging_to_parent_company[m_vec_report_date.size()-1];  //  m_vec_net_profit
		if(mon==3)
			nProfit = 4 * nProfit;
		else if(mon==6)
			nProfit = 2 * nProfit;
		else if(mon==9)
			nProfit = 4 * nProfit / 3;
	}
	
	return nProfit;
}

double CIncomeStatement::NetProfitBelongingToParentCompany(string currDate, string & baseDate, bool & isLast)
{
	double nProfit = -1;
	COleDateTime odt;
	int k = m_vec_report_date.size() - 1;
	odt.ParseDateTime(currDate.c_str());
	for(; k>=0; k--)
	{
		COleDateTime odt_in ;
		
		odt_in.ParseDateTime( m_vec_report_date[k].c_str());
		if(odt_in.m_dt <= odt.m_dt)
		{
			nProfit = m_vec_net_profit_belonging_to_parent_company[k];
			baseDate = m_vec_report_date[k];
			isLast = k==m_vec_report_date.size()-1 ? true : false;
			break;
		}
	}
	
	return nProfit;
}
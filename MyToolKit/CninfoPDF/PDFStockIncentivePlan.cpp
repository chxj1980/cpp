#include "StdAfx.h"
#include "PDFStockIncentivePlan.h"

#include "UrlUtils.h"
#include "TextExtractorEx.h"

CPDFStockIncentivePlan::CPDFStockIncentivePlan(void)
{
}

CPDFStockIncentivePlan::~CPDFStockIncentivePlan(void)
{
}



list<CCninfoAnnouncePDF *> CPDFStockIncentivePlan::CreatePDF()
{
	list<string>	announcementId;
	list<string>	adjunctUrl;
	list<string>	announcementTitle;

	list<string>	announcementTime;
	list<string>	secCode;
	list<string>	secName;

	stringstream ss;
	try
	{

		session sql(g_MysqlPool);

		//////////////////////////////////////////////////////////////////////////

		sql << SqlScript();

		ss.str("");
		ss << "select announcementId, secCode, secName, adjunctUrl, announcementTitle, " 
			"DATE_FORMAT(announcementTime, '%Y-%m-%d') as announcementTime from cninfoannouncement b "
			"where announcementTime > '2014-1-1' and adjunctType = 'PDF'  " 
			"and ( announcementTitle like '%��Ʊ�����ƻ����ݰ���'  ) "
			"and announcementId not in "
			"( select DISTINCT announcementId from cninfo_incentive_plan where net_profit > 0 or downloadTime = CURDATE() ) "
			"order by announcementTime desc ";

		string tttt = ss.str();

		row r;
		statement st = (sql.prepare << /*Gbk2Utf8*/ ss.str(), into(r)) ;
		st.execute();

		while (st.fetch())
		{
			announcementId.push_back( r.get<string>("announcementId"));			
			adjunctUrl.push_back(  r.get<string>("adjunctUrl"));
			announcementTitle.push_back( r.get<string>("announcementTitle"));

			announcementTime.push_back( r.get<string>("announcementTime"));
			secCode.push_back( r.get<string>("secCode"));
			secName.push_back( r.get<string>("secName"));
		}

		//////////////////////////////////////////////////////////////////////////
		//	���ع�Ȩ�䶯

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), NULL);
	}

	list<CCninfoAnnouncePDF *>  lst;

	int nPDF = 1;
	while(adjunctUrl.size()>0)
	{
		ss.str("");
		ss << "��" << nPDF << "��PDF" << "(" <<  *announcementTitle.begin() << ")���ؿ�ʼ.\r\n";
		sendToOutput(ss.str().c_str(), NULL );

		CCninfoAnnouncePDF *  pdf = new CPDFStockIncentivePlan;
		pdf->announcementId = *announcementId.begin();
		pdf->adjunctUrl = *adjunctUrl.begin();
		pdf->announcementTitle = *announcementTitle.begin();

		pdf->announcementTime = *announcementTime.begin();
		pdf->secCode = *secCode.begin();
		pdf->secName = *secName.begin();
		pdf->m_hWnd = NULL;

		lst.push_back(pdf);

		announcementId.pop_front();
		adjunctUrl.pop_front();
		announcementTitle.pop_front();
		announcementTime.pop_front();
		secCode.pop_front();
		secName.pop_front();

		nPDF++;
	}

	return lst;
}

bool CPDFStockIncentivePlan::AnalysisSentence(string sentence)
{
	sentence = ReplaceString(sentence, "                                            ", "");
	sentence = ReplaceString(sentence, "          ", "");
	sentence = ReplaceString(sentence, "%", _T("��"));
	sentence = ReplaceString(sentence, " ", _T(""));

	vector<string> firstMatch;
	vector<int>		firstOffset;
	int base_from_year = 0;
	int base_to_year = 0;
	int incentive_year = 0;
	int increase_percent = 0;
	double net_profit = 0;

	if(Pcre2Grep(_T("[\\d]+��(.*)������(������)?(�����)?[\\d\\.\\,]+��Ԫ"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+��(.*)������(������)?"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("������(������)?(�����)?[\\d\\.\\,]+"), vecSplit[i] ,firstMatch, firstOffset) > 0)
			{
				string tmp = firstMatch[0];
				if(Pcre2Grep(_T("������(������)?(�����)?"), tmp ,firstMatch, firstOffset) > 0)
					net_profit  = String2Double(tmp.substr(firstOffset[0] + firstMatch[0].length()));
			}

		}
	}
	else if(Pcre2Grep(_T("[\\d]+��(.*)������(������)?(�����)?[\\d\\.\\,]+��Ԫ"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+��(.*)������(������)?"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("������(������)?(�����)?[\\d\\.\\,]+"), vecSplit[i] ,firstMatch, firstOffset) > 0)
			{
				string tmp = firstMatch[0];
				if(Pcre2Grep(_T("������(������)?(�����)?"), tmp ,firstMatch, firstOffset) > 0)
					net_profit  = String2Double(tmp.substr(firstOffset[0] + firstMatch[0].length())) * 10000;
			}

		}
	}
	else if(Pcre2Grep(_T("[\\d]+(��)?[\\-]+[\\d]+(��)?(.*)Ϊ����(.*)[\\d]+��(.*)������(.*)����(��)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+(��)?[\\-]+[\\d]+(��)?(.*)Ϊ����"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("[\\-]+[\\d]+(��)?(.*)Ϊ����"), vecSplit[i] ,firstMatch, firstOffset) > 0)
			{
				string tmp = firstMatch[0];
				if(Pcre2Grep(_T("[\\-]+"), tmp ,firstMatch, firstOffset) > 0)
					base_to_year  = atoi(tmp.substr(firstOffset[0] + firstMatch[0].length(), 4).c_str());
			}

			if(Pcre2Grep(_T("[\\d]+��(.*)������(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("������(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
	}
	else if(Pcre2Grep(_T("[\\d]+��(.*)Ϊ(�̶�)?��(��|׼|��)(.*)[\\d]+��(.*)������(.*)����(��|����)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);
		
		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+��(.*)Ϊ(�̶�)?��(��|׼|��)"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("[\\d]+��(.*)������(.*)����(��|����)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("������(.*)����(��|����)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
	}
	else if(Pcre2Grep(_T("[\\d]+��(.*)������(��)?(��|��)[\\d]+��(.*)����(��)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("(��|��)[\\d]+��(.*)����(��)?������[\\d\\.]+��"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0] + 2, 4).c_str());

			if(Pcre2Grep(_T("[\\d]+��(.*)������(��)?(��|��)[\\d]+��(.*)����(��)?������[\\d\\.]+��"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("������(��)?(��|��)[\\d]+��(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
		int kkk = 1;
	}
	else if(Pcre2Grep(_T("(��|��)��[\\d]+��(.*)[\\d]+��(.*)������(.*)����(��)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("��[\\d]+��"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0] + 2, 4).c_str());

			if(Pcre2Grep(_T("[\\d]+��(.*)������(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("������(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
		int kkk = 1;
	}
	else if(Pcre2Grep(_T("��[\\d]+��(.*)����Ϊ����(.*)[\\d]+��(.*)���������ʲ�����[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{

	}
	else
	{
		int kkk = 1;
	}
	
	//	����ҵ��������ݵ� ������
	
	bool bResult = false;
	stringstream ss;
	if(incentive_year >2000)
	{
		if(net_profit>0)
		{
			//	�Ѿ�ֱ�ӻ�ȡ�� ������

			int idx = m_sentences.size();
			m_incentive_year[idx] = incentive_year;
			m_net_profit[idx] = net_profit;
			m_sentences.insert(m_sentences.end(), sentence);

			bResult = true;
		}
		else if(base_from_year > 2000)
		{
			if(base_to_year ==0)
			{
				//	��ȡ���ڵľ�����
				session sql(g_MysqlPool);
				ss << "select colume_41 as net_profit from incomestatement where code = ";
				ss << secCode << " and  report_date = '" << base_from_year << "-12-31' ";
				string test = ss.str();

				row r;
				statement st = (sql.prepare << test,into(r)) ;
				st.execute();
				st.fetch();
				try{
					net_profit = r.get<double>("net_profit");
				}
				catch(...)
				{
					net_profit = 0;
				}
				net_profit = net_profit * (100 + increase_percent) / 100;
				net_profit = net_profit / 10000;	//	�� ��ԪΪ��λ

				int idx = m_sentences.size();
				m_increase_percent[idx] = increase_percent;
				m_incentive_year[idx] = incentive_year;
				m_base_from_year[idx] = base_from_year;
				m_net_profit[idx] = net_profit;
				m_sentences.insert(m_sentences.end(), sentence);

				bResult = true;
			}
			else
			{
				//	����Ϊ n ��ľ�ֵ 
				int nYear = 0;
				net_profit = 0;
				for(int b = base_from_year; b<=base_to_year; b++)
				{
					session sql(g_MysqlPool);
					ss.str("");
					ss << "select colume_41 as net_profit from incomestatement where code = ";
					ss << secCode << " and  report_date = '" << b << "-12-31' ";
					string test = ss.str();

					row r;
					statement st = (sql.prepare << test,into(r)) ;
					st.execute();
					st.fetch();
					try{
						net_profit = net_profit + r.get<double>("net_profit");
					}
					catch(...)
					{
						net_profit = 0;
						break;
					}
					nYear++;
				}

				if(net_profit>0)
				{
					net_profit = (net_profit / nYear) * (100 + increase_percent) / 100;
					net_profit = net_profit / 10000;	//	�� ��ԪΪ��λ
				}
				
				int idx = m_sentences.size();
				m_increase_percent[idx] = increase_percent;
				m_incentive_year[idx] = incentive_year;
				m_base_from_year[idx] = base_from_year;
				m_base_to_year[idx] = base_to_year;
				m_net_profit[idx] = net_profit;
				m_sentences.insert(m_sentences.end(), sentence);

				bResult = true;
			}
		}
	}

	return bResult;
}


bool CPDFStockIncentivePlan::AnalysisSentenceForSalsFromOperations(string sentence)
{
	sentence = ReplaceString(sentence, "                                            ", "");
	sentence = ReplaceString(sentence, "%", _T("��"));
	sentence = ReplaceString(sentence, " ", _T(""));

	vector<string> firstMatch;
	vector<int>		firstOffset;
	int base_from_year = 0;
	int base_to_year = 0;
	int incentive_year = 0;
	int increase_percent = 0;
	double net_profit = 0;

	if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(������)?(�����)?[\\d\\.\\,]+��Ԫ"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(������)?"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("Ӫҵ����(������)?(�����)?[\\d\\.\\,]+"), vecSplit[i] ,firstMatch, firstOffset) > 0)
			{
				string tmp = firstMatch[0];
				if(Pcre2Grep(_T("Ӫҵ����(������)?(�����)?"), tmp ,firstMatch, firstOffset) > 0)
					net_profit  = String2Double(tmp.substr(firstOffset[0] + firstMatch[0].length()));
			}

		}
	}
	else if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(������)?(�����)?[\\d\\.\\,]+��Ԫ"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(������)?"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("Ӫҵ����(������)?(�����)?[\\d\\.\\,]+"), vecSplit[i] ,firstMatch, firstOffset) > 0)
			{
				string tmp = firstMatch[0];
				if(Pcre2Grep(_T("Ӫҵ����(������)?(�����)?"), tmp ,firstMatch, firstOffset) > 0)
					net_profit  = String2Double(tmp.substr(firstOffset[0] + firstMatch[0].length())) * 10000;
			}

		}
	}
	else if(Pcre2Grep(_T("[\\d]+(��)?[\\-]+[\\d]+(��)?(.*)Ϊ����(.*)[\\d]+��(.*)Ӫҵ����(.*)����(��)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+(��)?[\\-]+[\\d]+(��)?(.*)Ϊ����"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("[\\-]+[\\d]+(��)?(.*)Ϊ����"), vecSplit[i] ,firstMatch, firstOffset) > 0)
			{
				string tmp = firstMatch[0];
				if(Pcre2Grep(_T("[\\-]+"), tmp ,firstMatch, firstOffset) > 0)
					base_to_year  = atoi(tmp.substr(firstOffset[0] + firstMatch[0].length(), 4).c_str());
			}

			if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("Ӫҵ����(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
	}
	else if(Pcre2Grep(_T("[\\d]+��(.*)Ϊ(�̶�)?��(��|׼|��)(.*)[\\d]+��(.*)Ӫҵ����(.*)����(��|����)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("[\\d]+��(.*)Ϊ(�̶�)?��(��|׼|��)"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(.*)����(��|����)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("Ӫҵ����(.*)����(��|����)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
	}
	else if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(��)?(��|��)[\\d]+��(.*)����(��)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("(��|��)[\\d]+��(.*)����(��)?������[\\d\\.]+��"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0] + 2, 4).c_str());

			if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(��)?(��|��)[\\d]+��(.*)����(��)?������[\\d\\.]+��"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("Ӫҵ����(��)?(��|��)[\\d]+��(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
		int kkk = 1;
	}
	else if(Pcre2Grep(_T("(��|��)��[\\d]+��(.*)[\\d]+��(.*)Ӫҵ����(.*)����(��)?������[\\d\\.]+��"), sentence ,firstMatch, firstOffset) > 0)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

		for(int i=0; i< vecSplit.size(); i++)
		{
			if(Pcre2Grep(_T("��[\\d]+��"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				base_from_year  = atoi(vecSplit[i].substr(firstOffset[0] + 2, 4).c_str());

			if(Pcre2Grep(_T("[\\d]+��(.*)Ӫҵ����(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				incentive_year  = atoi(vecSplit[i].substr(firstOffset[0], 4).c_str());

			if(Pcre2Grep(_T("Ӫҵ����(.*)����(��)?������"), vecSplit[i] ,firstMatch, firstOffset) > 0)
				increase_percent  = atoi(vecSplit[i].substr(firstOffset[0] + firstMatch[0].length()).c_str());
		}
		int kkk = 1;
	}
	else
	{

	}

	//	����ҵ��������ݵ� Ӫҵ����

	bool bResult = false;
	stringstream ss;
	if(incentive_year >2000)
	{
		if(net_profit>0)
		{
			//	�Ѿ�ֱ�ӻ�ȡ�� ������

			int idx = m_sentences.size();
			m_incentive_year[idx] = incentive_year;
			m_sales_from_operations[idx] = net_profit;
			m_sentences.insert(m_sentences.end(), sentence);
			bResult = true;

		}
		else if(base_from_year > 2000)
		{
			if(base_to_year ==0)
			{
				//	��ȡ���ڵľ�����
				session sql(g_MysqlPool);
				ss << "select colume_2 as sales_from_operations from incomestatement where code = ";
				ss << secCode << " and  report_date = '" << base_from_year << "-12-31' ";
				string test = ss.str();

				row r;
				statement st = (sql.prepare << test,into(r)) ;
				st.execute();
				st.fetch();
				try{
					net_profit = r.get<double>("sales_from_operations");
				}
				catch(...)
				{
					net_profit = 0;
				}
				net_profit = net_profit * (100 + increase_percent) / 100;
				net_profit = net_profit / 10000;	//	�� ��ԪΪ��λ

				int idx = m_sentences.size();
				m_increase_percent[idx] = increase_percent;
				m_incentive_year[idx] = incentive_year;
				m_base_from_year[idx] = base_from_year;
				m_sales_from_operations[idx] = net_profit;
				m_sentences.insert(m_sentences.end(), sentence);

				bResult = true;
			}
			else
			{
				//	����Ϊ n ��ľ�ֵ 
				int nYear = 0;
				net_profit = 0;
				for(int b = base_from_year; b<=base_to_year; b++)
				{
					session sql(g_MysqlPool);
					ss.str("");
					ss << "select colume_2 as sales_from_operations from incomestatement where code = ";
					ss << secCode << " and  report_date = '" << b << "-12-31' ";
					string test = ss.str();

					row r;
					statement st = (sql.prepare << test,into(r)) ;
					st.execute();
					st.fetch();
					try{
						net_profit = net_profit + r.get<double>("sales_from_operations");
					}
					catch(...)
					{
						net_profit = 0;
						break;
					}
					nYear++;
				}

				if(net_profit>0)
				{
					net_profit = (net_profit / nYear) * (100 + increase_percent) / 100;
					net_profit = net_profit / 10000;	//	�� ��ԪΪ��λ
				}

				int idx = m_sentences.size();
				m_increase_percent[idx] = increase_percent;
				m_incentive_year[idx] = incentive_year;
				m_base_from_year[idx] = base_from_year;
				m_base_to_year[idx] = base_to_year;
				m_sales_from_operations[idx] = net_profit;
				m_sentences.insert(m_sentences.end(), sentence);

				bResult = true;
			}
		}
	}

	return bResult;
}


string CPDFStockIncentivePlan::SaveAsCsv()
{
	stringstream ss;

	int zipLen = 0;
	unsigned char * pZip = NULL;
	/* ���� PDF �ļ� */

	/*2016-06-01/1202348087.PDF*/

	string test = string("http://www.cninfo.com.cn/") + adjunctUrl;
	zipLen =CUrlUtils::PostUrlOfCsindex(test, pZip);

	if(zipLen>0)
	{
		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF �ļ����� �ɹ�. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

	}
	else
	{
		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF �ļ����� ʧ��. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		return ss.str();
	}

	//////////////////////////////////////////////////////////////////////////

	TextExtractorEx extractor;

	try {
		extractor.Init( (char *)pZip , zipLen );

	} 
	catch( PdfError & e ) {

		int tt = e.GetError();

		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF TextExtractor Err. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		if(pZip)
			free(pZip);

		return ss.str();
	}

	if(pZip)
		free(pZip);


	//SaveAnalysisToDatabase(extractor.m_pdf);

	//////////////////////////////////////////////////////////////////////////


	for(int i=0; i< extractor.m_pdf.size(); i++)
	{
		vector<string> firstMatch;
		vector<int>		firstOffset;
		if(Pcre2Grep(_T("T[\\d]+��(.*)��Ч����Ŀ��"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
		{
			if(Pcre2Grep(_T("��Ч����Ŀ��<=>"), extractor.m_pdf[i].content ,firstMatch, firstOffset)>0)
				if(AnalysisSentence(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()))==false)
					AnalysisSentenceForSalsFromOperations(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()));
		}
		else if(Pcre2Grep(_T("T[\\d]+��(.*)ҵ������Ŀ��"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
		{
			if(Pcre2Grep(_T("ҵ������Ŀ��<=>"), extractor.m_pdf[i].content ,firstMatch, firstOffset)>0)
				if(AnalysisSentence(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()))==false)
					AnalysisSentenceForSalsFromOperations(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()));
		}
		else if(Pcre2Grep(_T("T[\\d]+��(.*)ҵ������ָ��"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
		{
			if(Pcre2Grep(_T("ҵ������ָ��<=>"), extractor.m_pdf[i].content ,firstMatch, firstOffset)>0)
				if(AnalysisSentence(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()))==false)
					AnalysisSentenceForSalsFromOperations(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()));
		}
		else if(Pcre2Grep(_T("T[\\d]+��(.*)����ҵ��ָ��"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
		{
			if(Pcre2Grep(_T("����ҵ��ָ��<=>"), extractor.m_pdf[i].content ,firstMatch, firstOffset)>0)
				if(AnalysisSentence(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()))==false)
					AnalysisSentenceForSalsFromOperations(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()));
		}
		else if(Pcre2Grep(_T("T[\\d]+��(.*)ҵ����������"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
		{
			if(Pcre2Grep(_T("ҵ����������<=>"), extractor.m_pdf[i].content ,firstMatch, firstOffset)>0)
				if(AnalysisSentence(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()))==false)
					AnalysisSentenceForSalsFromOperations(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()));
		}
		else if(Pcre2Grep(_T("T[\\d]+��(.*)��������"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
		{
			if(Pcre2Grep(_T("��������<=>"), extractor.m_pdf[i].content ,firstMatch, firstOffset)>0)
				if(AnalysisSentence(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()))==false)
					AnalysisSentenceForSalsFromOperations(extractor.m_pdf[i].content.substr(firstOffset[0] + firstMatch[0].length()));
		}
		else
		{
			
		}
	}

	return "AlreadyInMemory";
}


string CPDFStockIncentivePlan::SqlScript()
{
	stringstream ss;
	ss.str("");
	ss << "create table if not exists Cninfo_Incentive_Plan ( " 
		<< "announcementId varchar(32),  secCode varchar(32), secName varchar(32), announcementTime date,  "
		<< "announcementTitle varchar(128), adjunctUrl varchar(128),  content varchar(1000), "
		<< "base_from_year int, base_to_year int, incentive_year int, increase_percent decimal(6, 2),  "
		<< "net_profit decimal(15,3), sales_from_operations decimal(15,3), downloadTime date,  PRIMARY KEY ( announcementId, incentive_year ))";
	
	return ss.str();
}

void CPDFStockIncentivePlan::ImportToDatabase(string csv)
{
	if(csv=="AlreadyInMemory")
	{

	}
	else
	{
		
		return;
	}



	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	try
	{
		ss << "CPDFStockIncentivePlan::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		sql << SqlScript();

		//	ɾ��ԭ�� δ�ɹ����㾻����� ��¼
		ss.str("");
		ss << "delete from Cninfo_Incentive_Plan where announcementId = '" << announcementId << "'";
		sql << ss.str();

		if(m_net_profit.size()>0)
		{
			if(m_base_from_year.size()>0)
			{
				if(m_base_to_year.size()==0)
				{
					//	��ĳ��Ϊ����
					ss.str("");
					ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
						<< " adjunctUrl, content, base_from_year, incentive_year, increase_percent, net_profit, downloadTime ) values ";

					for( int i =0; i< m_sentences.size(); i++ )
					{
						ss	<< "( \'" << announcementId << "\' ," 
							<< "\'" << secCode << "\' ,"
							<< "\'" << secName << "\' ,"
							<< "\'" << announcementTime << "\' ,"
							<< "\'" << announcementTitle << "\' ,"
							<< "\'" << adjunctUrl << "\' ,"
							<< "\'" << m_sentences[i] << "\' ,"
							<<  m_base_from_year[i] << ","
							<<  m_incentive_year[i] << ","
							<<  m_increase_percent[i] << ","
							<<  m_net_profit[i] << ", CURDATE() )";

						if(i< m_sentences.size()-1)
							ss << ",";
					}

					string test = ss.str();
					//test = Gbk2Utf8(test);
					sql << test;
				}
				else
				{
					// �� n ��Ϊ����
					ss.str("");
					ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
						<< " adjunctUrl, content, base_from_year, base_to_year, "
						<< " incentive_year, increase_percent, net_profit, downloadTime) values ";

					for( int i =0; i< m_sentences.size(); i++ )
					{
						ss	<< "( \'" << announcementId << "\' ," 
							<< "\'" << secCode << "\' ,"
							<< "\'" << secName << "\' ,"
							<< "\'" << announcementTime << "\' ,"
							<< "\'" << announcementTitle << "\' ,"
							<< "\'" << adjunctUrl << "\' ,"
							<< "\'" << m_sentences[i] << "\' ,"
							<<  m_base_from_year[i] << ","
							<<  (m_base_to_year.count(i)>0 ? m_base_to_year[i] : 0) << ","
							<<  m_incentive_year[i] << ","
							<<  m_increase_percent[i] << ","
							<<  m_net_profit[i] << ", CURDATE() )";

						if(i< m_sentences.size()-1)
							ss << ",";
					}

					string test = ss.str();
					//test = Gbk2Utf8(test);
					sql << test;
				}
			}
			else
			{
				//	Ԥ����ֱ�ӻ�ȡ�� ������
				ss.str("");
				ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
					<< "adjunctUrl, content, incentive_year,  net_profit, downloadTime) values ";

				for( int i =0; i< m_sentences.size(); i++ )
				{
					ss	<< "( \'" << announcementId << "\' ," 
						<< "\'" << secCode << "\' ,"
						<< "\'" << secName << "\' ,"
						<< "\'" << announcementTime << "\' ,"
						<< "\'" << announcementTitle << "\' ,"
						<< "\'" << adjunctUrl << "\' ,"
						<< "\'" << m_sentences[i] << "\' ,"
						<<  m_incentive_year[i] << ","
						<<  m_net_profit[i] << ", CURDATE() )";

					if(i< m_sentences.size()-1)
						ss << ",";
				}

				string test = ss.str();
				//test = Gbk2Utf8(test);
				sql << test;
			}
		}
		else if(m_sales_from_operations.size()>0)
		{
			if(m_base_from_year.size()>0)
			{
				if(m_base_to_year.size()==0)
				{
					//	��ĳ��Ϊ����
					ss.str("");
					ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
						<< " adjunctUrl, content, base_from_year, incentive_year, increase_percent, sales_from_operations, downloadTime ) values ";

					for( int i =0; i< m_sentences.size(); i++ )
					{
						ss	<< "( \'" << announcementId << "\' ," 
							<< "\'" << secCode << "\' ,"
							<< "\'" << secName << "\' ,"
							<< "\'" << announcementTime << "\' ,"
							<< "\'" << announcementTitle << "\' ,"
							<< "\'" << adjunctUrl << "\' ,"
							<< "\'" << m_sentences[i] << "\' ,"
							<<  m_base_from_year[i] << ","
							<<  m_incentive_year[i] << ","
							<<  m_increase_percent[i] << ","
							<<  m_sales_from_operations[i] << ", CURDATE() )";

						if(i< m_sentences.size()-1)
							ss << ",";
					}

					string test = ss.str();
					//test = Gbk2Utf8(test);
					sql << test;
				}
				else
				{
					// �� n ��Ϊ����
					ss.str("");
					ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
						<< " adjunctUrl, content, base_from_year, base_to_year, "
						<< " incentive_year, increase_percent, sales_from_operations, downloadTime) values ";

					for( int i =0; i< m_sentences.size(); i++ )
					{
						ss	<< "( \'" << announcementId << "\' ," 
							<< "\'" << secCode << "\' ,"
							<< "\'" << secName << "\' ,"
							<< "\'" << announcementTime << "\' ,"
							<< "\'" << announcementTitle << "\' ,"
							<< "\'" << adjunctUrl << "\' ,"
							<< "\'" << m_sentences[i] << "\' ,"
							<<  m_base_from_year[i] << ","
							<<  (m_base_to_year.count(i)>0 ? m_base_to_year[i] : 0) << ","
							<<  m_incentive_year[i] << ","
							<<  m_increase_percent[i] << ","
							<<  m_sales_from_operations[i] << ", CURDATE() )";

						if(i< m_sentences.size()-1)
							ss << ",";
					}

					string test = ss.str();
					//test = Gbk2Utf8(test);
					sql << test;
				}
			}
			else
			{
				//	Ԥ����ֱ�ӻ�ȡ�� Ӫҵ����
				ss.str("");
				ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
					<< "adjunctUrl, content, incentive_year,  sales_from_operations, downloadTime) values ";

				for( int i =0; i< m_sentences.size(); i++ )
				{
					ss	<< "( \'" << announcementId << "\' ," 
						<< "\'" << secCode << "\' ,"
						<< "\'" << secName << "\' ,"
						<< "\'" << announcementTime << "\' ,"
						<< "\'" << announcementTitle << "\' ,"
						<< "\'" << adjunctUrl << "\' ,"
						<< "\'" << m_sentences[i] << "\' ,"
						<<  m_incentive_year[i] << ","
						<<  m_sales_from_operations[i] << ", CURDATE() )";

					if(i< m_sentences.size()-1)
						ss << ",";
				}

				string test = ss.str();
				//test = Gbk2Utf8(test);
				sql << test;
			}
		}
		else
		{
			//	�������ɹ�
			ss.str("");
			ss << " insert into Cninfo_Incentive_Plan (  announcementId, secCode, secName, announcementTime, announcementTitle,"
				<< " adjunctUrl, incentive_year,   downloadTime) values ";

			ss	<< "( \'" << announcementId << "\' ," 
				<< "\'" << secCode << "\' ,"
				<< "\'" << secName << "\' ,"
				<< "\'" << announcementTime << "\' ,"
				<< "\'" << announcementTitle << "\' ,"
				<< "\'" << adjunctUrl << "\' ,"
				<< "0 , CURDATE() )";

			sql << ss.str();
		}
		

		ss.str("");
		ss << "�������� " << m_sentences.size() ;
		ss << " OK, CPDFStockIncentivePlan::ImportToDatabase ���ݵ������. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << "\r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);
	}
}

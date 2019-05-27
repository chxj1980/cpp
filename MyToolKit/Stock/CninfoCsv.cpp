#include "StdAfx.h"
#include "CninfoCsv.h"
#include "UrlUtils.h"

#include "zlib.h"
#include "unzip.h"
#include "MyBuffer.h"

#include "stock.h"

CCninfoCsv::CCninfoCsv(void)
{
	
	m_strEnglishName = "";
}



string CCninfoCsv::SqlScript()
{
	stringstream ss;

	ss << " create table if not exists " << m_strEnglishName << " ( ";

	for(int i=0; i< m_vec_yield.size(); i++)
	{
		if(m_vec_yield[i].second=="code")
			ss << m_vec_yield[i].second << " int,";
		else if(m_vec_yield[i].second=="name")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second=="announce_date")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second=="start_date")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second=="report_date")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second=="year")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second=="union_type")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second=="report_source")
			ss << m_vec_yield[i].second << " varchar(32),";
		else if(m_vec_yield[i].second.empty()==false)
			ss <<  m_vec_yield[i].second <<  " DECIMAL(18,2),";
	}
	ss << " PRIMARY KEY(code, report_date))";		

	return ss.str();
}


CCninfoCsv::~CCninfoCsv(void)
{
}

void CCninfoCsv::KaptchaAsJpeg()
{
	unsigned char * pXls = NULL;
	char tmpCode[256] = {0};
	sprintf(tmpCode, "http://www.cninfo.com.cn/cninfo-new/Kaptcha.do?JSESSIONID=%s_%06d", m_strEnglishName.c_str(), m_nCode);

	string test = string(tmpCode);
	int xlsLen =CUrlUtils::PostUrlOfCninfo(tmpCode, pXls);
	if(xlsLen>0)
	{
		unsigned long tick =GetTickCount();
		CString target;
		target.Format("%s/%s/%d.jpeg",g_strCurrentDir.c_str(), "CninfoFinance", tick);
		string filename = target.GetBuffer();

		FILE * fp_zip=fopen(filename.c_str(),"wb");
		if(fp_zip)
		{
			fwrite(pXls,1,xlsLen ,fp_zip);
			fclose(fp_zip);
		}
		//free(pZip);
		delete[] pXls;
	}
}

// Kaptcha �� java �µ�һ����Դ��֤�����
void CCninfoCsv::Kaptcha()
{
	int xlsLen = 0;
	unsigned char * pXls = NULL;
	
	char tmpCode[256] = {0};
	sprintf(tmpCode, "http://www.cninfo.com.cn/cninfo-new/data/kaptcha");
	string test = string(tmpCode);

	sprintf(tmpCode, "JSESSIONID=%s_%06d&j_code=cdds", m_strEnglishName.c_str(), m_nCode);
	pXls = (unsigned char *)tmpCode;
	xlsLen =CUrlUtils::PostUrlOfCninfo(test, pXls);
}

string  CCninfoCsv::SaveAsCsv()
{
	stringstream ss;

	int xlsLen = 0;
	unsigned char * pXls = NULL;
	string zipurl = GetZipUrl();
	pXls = (unsigned char *)zipurl.c_str();
		
	char tmpCode[256] = {0};
	sprintf(tmpCode, "http://www.cninfo.com.cn/cninfo-new/data/download");

	string test = string(tmpCode);
	xlsLen =CUrlUtils::PostUrlOfCninfo(tmpCode, pXls);
	if(xlsLen>0)
	{
		if(xlsLen==14201)
		{
			//	˵�����ص� zip �ļ�������Ϊ��
			delete[] pXls;
			return "";
		}

		CStockDownloadData sdd = ((CStockApp *)AfxGetApp())->m_StockDataLog.SearchStockByCode(m_nCode);
		long filesize = 0;
		if(m_strEnglishName=="cninfo_balance")
			filesize = sdd.Balance_Zip;
		else if(m_strEnglishName=="cninfo_incomestatement")
			filesize = sdd.IncomeStatement_Zip;
		else if(m_strEnglishName=="cninfo_cashflows")
			filesize = sdd.CashFlows_Zip;

		if(filesize == xlsLen)
		{	
			delete[] pXls;

			// ˵�����ݿ����Ѿ����������µĲ��񱨱� ������������ϢΪ�˱��⵱���������ظ��Ӿ޳������ؼ��
			COleDateTime odt = COleDateTime::GetCurrentTime();
			string downloadTime = odt.Format("%Y-%m-%d").GetBuffer();

			if(m_strEnglishName.find("cninfo_balance")!=string::npos)
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "Balance", downloadTime);

			if(m_strEnglishName.find("cninfo_incomestatement")!=string::npos)
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "IncomeStatement", downloadTime);

			if(m_strEnglishName.find("cninfo_cashflows")!=string::npos)
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "CashFlows", downloadTime);


			return "NoMoreData";
		}

		string filename = m_strEnglishName + "_" + Int2String(m_nCode, "%06d");
		CString target;
		target.Format("%s/%s/%s.zip",g_strCurrentDir.c_str(), "CninfoFinance", filename.c_str());
		filename = target.GetBuffer();

		FILE * fp_zip=fopen(filename.c_str(),"wb");
		if(fp_zip)
		{
			fwrite(pXls,1,xlsLen ,fp_zip);
			fclose(fp_zip);
		}
		//free(pZip);
		delete[] pXls;

		if(Unzip(filename))
		{
			ss.str("");
			ss << "Zip ��������, " << m_strEnglishName << " [" << Int2String(m_nCode, "%06d") << "] \r\n";
			sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);
			return "AlreadyInMemory";
		}
	}
	return "";
}

bool CCninfoCsv::Unzip(string zipfilename )
{
	unzFile unzfile = unzOpen(zipfilename.c_str());                    
	if(unzfile == NULL)
	{
		Sleep(120*1000);
		sendToOutput("unzOpen err",m_hWnd, m_nLogType);
		return false;
	}
			
	//��ȡzip�ļ�����Ϣ
	unz_global_info* pGlobalInfo = new unz_global_info;
	int nReturnValue = unzGetGlobalInfo(unzfile, pGlobalInfo);
	if(nReturnValue != UNZ_OK)
	{
		sendToOutput("unzGetGlobalInfo err",m_hWnd, m_nLogType);
		return false;
	}

	//����zip�ļ�
	unz_file_info* pFileInfo = new unz_file_info;
	char szZipFName[MAX_PATH];                            //��Ŵ�zip�н����������ڲ��ļ���
	for(int i=0; i<pGlobalInfo->number_entry; i++)
	{
		//�����õ�zip�е��ļ���Ϣ
		nReturnValue = unzGetCurrentFileInfo(unzfile, pFileInfo, szZipFName, MAX_PATH, 
					NULL, 0, NULL, 0);
		if(nReturnValue != UNZ_OK)
		{
			sendToOutput("����zip�ļ���Ϣʧ��!",m_hWnd, m_nLogType);
			return false;
		}

		//�ж����ļ��л����ļ�
		switch(pFileInfo->external_fa)
		{
		case FILE_ATTRIBUTE_DIRECTORY:                    //�ļ���
			{
				/*CString strDiskPath = strTempPath + _T("//") + szZipFName;
				CreateDirectory(strDiskPath, NULL);*/
			}
		break;
		default:                                        //�ļ�
			{
				//�����ļ�
				MyBuffer buffer;

				//���ļ�
				nReturnValue = unzOpenCurrentFile(unzfile);
				if(nReturnValue != UNZ_OK)
				{
					sendToOutput("unzOpenCurrentFile ʧ��!",m_hWnd, m_nLogType);
					//CloseHandle(hFile);
					return false;
				}

				//��ȡ�ļ�
				const int BUFFER_SIZE = 4096;
				char szReadBuffer[BUFFER_SIZE];
				while(TRUE)
				{
					memset(szReadBuffer, 0, BUFFER_SIZE);
					int nReadFileSize = unzReadCurrentFile(unzfile, szReadBuffer, BUFFER_SIZE);
					if(nReadFileSize < 0)                //��ȡ�ļ�ʧ��
					{
						sendToOutput("��ȡ�ļ�ʧ��!",m_hWnd, m_nLogType);
						unzCloseCurrentFile(unzfile);
						//CloseHandle(hFile);
						return false;

					}
					else if(nReadFileSize == 0)            //��ȡ�ļ����
					{
						unzCloseCurrentFile(unzfile);
						//CloseHandle(hFile);

						//	�Ա��ѹ��һ���ļ�
						break;			
					}
					else                                //д���ȡ������
					{
						buffer.InputData((unsigned char *)szReadBuffer, nReadFileSize);
					}
				}

				// ���� csv �ļ�
				char * pCsv = (char *)buffer.linearize();
				if(pCsv)
				{
					vector<string>	vecLine;
					splitString(string(pCsv),"\r\n" , vecLine);
					if(vecLine.size()>2)
					{
						//	�Ƚ��� ����ͷ
						vector<string>	vecHeader;
						splitString(vecLine[0], "," , vecHeader);

						/*for(int i=0; i<vecHeader.size(); i++)
						{
							stringstream ss;
							ss << "m_vec_yield.insert(m_vec_yield.end(), make_pair(_T(\"" << vecHeader[i]  << "\") , \"\"));";
							LOG4CPLUS_DEBUG(g_logger, ss.str());
						}*/

						//	�ٽ���������
						for(int k=1; k<vecLine.size(); k++)
						{
							map<string, string>	mapRow;
							vector<string> vecRow;
							splitString(vecLine[k], "," , vecRow);
							if(vecRow.size()>0 && vecHeader.size()== vecRow.size())
							{
								for(int j=0; j< vecRow.size(); j++)
								{
									mapRow[vecHeader[j]] = ReplaceString(vecRow[j], "\"", "");
								}
								m_vec_row.insert(m_vec_row.end(), mapRow);
							}
						}

					}
					delete[] pCsv;
				}

			}
			break;
		}
		unzGoToNextFile(unzfile);
	}

	//�ر�
	if(unzfile)
	{
		unzClose(unzfile);
	}	

	if(m_vec_row.size()>0)
		return true;
	return false;
}


void CCninfoCsv::ImportToDatabase(void)
{
	stringstream ss;
	try{
		
		vector<string> vecHeader;
		map<string, string>::iterator it = m_map_yield.begin();
		for(; it!=m_map_yield.end(); it++)
		{
			if(it->second.empty()==false)
				vecHeader.push_back(it->first);
		}

		stringstream ss;
		ss << "insert into " << m_strEnglishName << " ( ";
		for(int k=0; k<vecHeader.size(); k++)
		{
			ss << m_map_yield[vecHeader[k]];
			if(k< vecHeader.size()-1)
				ss << ",";
		}
		ss << ") values ";

		for(int k=0; k<m_vec_row.size(); k++)
		{
			map<string, string>  mapRow = m_vec_row[k];
			ss << "(";
			for( int i=0; i< vecHeader.size(); i++)
			{
				ss << "\"" << mapRow[vecHeader[i]] << "\"";
				if(i < vecHeader.size()-1)
					ss << ",";
			}
			ss << ")";
			if(k < m_vec_row.size()-1)
				ss << ",";
		}

		if(m_vec_row.size()>0)
		{
			session sql(g_MysqlPool);

			string test = SqlScript();
			sql << SqlScript();

			test = "delete from " + m_strEnglishName + " where code = " + Int2String(m_nCode, "%06d");
			sql << test;

			test = ss.str();
			sql << test;
		}
		

		if(m_vec_row.size()>0)
		{
			COleDateTime odt = COleDateTime::GetCurrentTime();
			string downloadTime = odt.Format("%Y-%m-%d").GetBuffer();

			string filename = m_strEnglishName + "_" + Int2String(m_nCode, "%06d");
			CString target;
			target.Format("%s/%s/%s.zip",g_strCurrentDir.c_str(), "CninfoFinance", filename.c_str());
			filename = target.GetBuffer();
			string filesize = Int2String(GetDownloadFileSize(filename));

			if(m_strEnglishName.find("cninfo_balance")!=string::npos)
			{
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "Balance", downloadTime);
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "Balance_Zip", filesize);
			}

			if(m_strEnglishName.find("cninfo_incomestatement")!=string::npos)
			{
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "IncomeStatement", downloadTime);
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "IncomeStatement_Zip", filesize);
			}

			if(m_strEnglishName.find("cninfo_cashflows")!=string::npos)
			{
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "CashFlows", downloadTime);
				((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "CashFlows_Zip", filesize);
			}
		}
		
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);
	}
	
}


string CCninfoCsv::Yield2Key(string strYield)
{
	map<string, string>::iterator it = m_map_yield.begin();
	for(; it!=m_map_yield.end(); it++)
	{
		if(it->second==strYield)
			return it->first;
	}
	return "-";
}


void CCninfoCsv::ExportFromDatabase(double startTime, double endTime)
{

	m_vec_row.clear();
	stringstream ss;
	try
	{
		vector<string>	vecHeader;
		map<string, string>::iterator it = m_map_yield.begin();
		for(; it!= m_map_yield.end(); it++)
		{
			if(it->second.empty()==false)
			{
				vecHeader.push_back(it->second);
			}
		}

		ss.str("");
		ss << "select ";

		for(int i = 0; i< vecHeader.size(); i++)
		{
			if(i>0)
				ss << ",";
			ss << vecHeader[i];
		}

		ss << " from " << m_strEnglishName ;
		ss << " where code = " << Int2String(m_nCode, "%06d");
		string test = ss.str();

		row r;
		session sql(g_MysqlPool);

		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		while (st.fetch())
		{
			map<string, string>	mapRow;
			for(int i=0; i< vecHeader.size(); i++)
			{
				string header = vecHeader[i];
				if(header=="code")
					mapRow[Yield2Key(header)] = Int2String(r.get<int>(header, 0), "%06d");
				else if(header=="name")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else if(header=="report_source")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else if(header=="union_type")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else if(header=="report_date")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else if(header=="start_date")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else if(header=="announce_date")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else if(header=="year")
					mapRow[Yield2Key(header)] = r.get<string>(header, "");
				else 
					mapRow[Yield2Key(header)] = Double2String(r.get<double>(header, 0),  "%.2f");
 			}
			m_vec_row.insert(m_vec_row.end(), mapRow);
		}

	}
	catch (...)
	{
		/*ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);*/
	}
	
}

//////////////////////////////////////////////////////////////////////////

CCninfoIncomeStatement::CCninfoIncomeStatement(void)
{
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ID"), "code")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������"), "name")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������"), "announce_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ʼ����"), "start_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ֹ����"), "report_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������"), "year")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ϲ�����"), "union_type")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������Դ"), "report_source")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("һ��Ӫҵ������"), "overall_sales")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У�Ӫҵ���루Ԫ��"), "sales_from_operations")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӫҵ�ܳɱ�"), "overall_costs")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У�Ӫҵ�ɱ�"), "cost_of_operations")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӫҵ˰�𼰸���"), "sales_tax_and_additions")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���۷���"), "selling_and_distribution_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������"), "general_and_administrative_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��̽����"), "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������"), "financial_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ʲ���ֵ��ʧ"), "impairment_loss_on_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ����ʼ�ֵ�䶯������"), "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ������"), "investment_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У�����Ӫ��ҵ�ͺ�Ӫ��ҵ��Ͷ������"), "investment_income_from_joint_ventures_and_affiliates")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������"), "gain_or_loss_on_foreign_exchange_transactions")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӱ��Ӫҵ�����������Ŀ"), "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӫҵ����"), "profit_from_operations")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ���������"), "subsidy_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӫҵ������"), "non_operating_profit")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӫҵ��֧��"), "non_operating_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У��������ʲ�������ʧ"), "losses_from_disposal_of_non_current_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ�Ӱ�������ܶ��������Ŀ"), "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ġ������ܶ�"), "profit_before_tax")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������˰"), "income_tax_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ�Ӱ�쾻�����������Ŀ"), "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�塢������"), "net_profit")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������ĸ��˾�����ߵľ�����"), "net_profit_belonging_to_parent_company")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ɶ�����"), "minority_interest")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ÿ�����棺"), "earnings_per_share")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��һ������ÿ������"), "basic_earnings_per_share")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������ϡ��ÿ������"), "diluted_earnings_per_share")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ߡ������ۺ�����"), "other_consolidated_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ˡ��ۺ������ܶ�"), "total_consolidated_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У�������ĸ��˾"), "consolidated_income_belonging_to_parent_company")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У������������ɶ�"), "consolidated_income_belonging_to_minority_shareholders")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ϣ����"), "interest_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��׬����"), "insurance_premiums_earned")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����Ѽ�Ӷ������"), "handling_charges_and_commissions_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ϣ֧��"), "interest_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����Ѽ�Ӷ��֧��"), "handling_charges_and_commissions_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�˱���"), "refund_of_insurance_premiums")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�⸶֧������"), "net_payments_for_insurance_claims")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ȡ���պ�ͬ׼���𾻶�"), "net_provision_for_insurance_contracts")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������֧��"), "commissions_on_insurance_policies")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ֱ�����"), "cession_charges")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У��������ʲ���������"), "")); 

	for(int i=0; i< m_vec_yield.size(); i++)
	{
		m_map_yield.insert(m_vec_yield[i]);
	}

	m_strEnglishName = "cninfo_incomestatement";

}


string CCninfoIncomeStatement::GetZipUrl()
{
	COleDateTime odt = COleDateTime::GetCurrentTime();
	char tmpPost[256] = { 0};
	if(m_nCode>=600000)
		sprintf(tmpPost,  "market=sh&type=lrb&code=%06d&orgid=%s&minYear=2001&maxYear=%d", 
		m_nCode, m_cninfo_orgid.c_str(), odt.GetYear());
	else
		sprintf(tmpPost,  "market=sz&type=lrb&code=%06d&orgid=%s&minYear=2001&maxYear=%d", 
		m_nCode, m_cninfo_orgid.c_str(), odt.GetYear());
	return  string(tmpPost);
}



double CCninfoIncomeStatement::EstimateYearProfits()
{
	double nProfit = -1;
	if(m_vec_row.size()>0)
	{
		COleDateTime odt_in ;
		odt_in.ParseDateTime( m_vec_row[m_vec_row.size()-1][_T("��ֹ����")].c_str());
		int mon = odt_in.GetMonth();
		int day = odt_in.GetDay();

		nProfit = String2Double(m_vec_row[m_vec_row.size()-1][_T("������ĸ��˾�����ߵľ�����")]);  //  m_vec_net_profit
		if(mon==3)
			nProfit = 4 * nProfit;
		else if(mon==6)
			nProfit = 2 * nProfit;
		else if(mon==9)
			nProfit = 4 * nProfit / 3;
	}

	return nProfit;
}

//	ĳ�չ���ĸ��˾�����ߵľ�����
double CCninfoIncomeStatement::NetProfitBelongingToParentCompany(string currDate, string & baseDate, bool & isLast)
{
	double nProfit = -1;
	COleDateTime odt;
	int k = m_vec_row.size() - 1;
	odt.ParseDateTime(currDate.c_str());
	for(; k>=0; k--)
	{
		COleDateTime odt_in ;

		odt_in.ParseDateTime( m_vec_row[k][_T("��ֹ����")].c_str());
		if(odt_in.m_dt <= odt.m_dt)
		{
			nProfit = String2Double(m_vec_row[k][_T("������ĸ��˾�����ߵľ�����")]);
			baseDate = m_vec_row[k][_T("��ֹ����")];
			isLast = k==m_vec_row.size()-1 ? true : false;
			break;
		}
	}

	return nProfit;
}



CCninfoBalance::CCninfoBalance(void)
{

	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ID"), "code")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������"), "name")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������"), "announce_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ֹ����"), "report_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������"), "year")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ϲ�����"), "union_type")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������Դ"), "report_source")); 

	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʽ�Ԫ��") , "cash")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�Թ��ʼ�ֵ��������䶯���뵱������Ľ����ʲ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ��Ʊ��") , "notes_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ���˿�") , "accounts_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ԥ������") , "advances_to_suppliers")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӧ�տ�") , "other_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ�չ�����˾��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ����Ϣ") , "interests_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ�չ���") , "dividends_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���") , "inventories")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У������������ʲ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("һ���ڵ��ڵķ������ʲ�") , "non_current_assets_maturing_within_one_year")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���������ʲ�") , "other_current_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʲ��ϼ�") , "total_current_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ɹ����۽����ʲ�") , "available_for_sale_financial_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����������Ͷ��") , "held_to_maturity_investments")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӧ�տ�") , "long_term_receivables")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ڹ�ȨͶ��") , "long_term_equity_investments")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ���Է��ز�") , "investment_real_estates")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�̶��ʲ�") , "fixed_assets_net_value")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ڽ�����") , "construction_in_progress")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������") , "construction_supplies")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�̶��ʲ�����") , "fixed_assets_pending_disposal")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����������ʲ�") , "bearer_biological_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʲ�") , "oil_and_natural_gas_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʲ�") , "intangibel_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����֧��") , "research_and_development_costs")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����") , "goodwill")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ڴ�̯����") , "long_term_deferred_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������˰�ʲ�") , "deferred_tax_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����������ʲ�") , "other_non_current_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������ʲ��ϼ�") , "total_non_current_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ʲ��ܼ�") , "total_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ڽ��") , "short_term_borrowings")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�Թ��ʼ�ֵ��������䶯���뵱������Ľ��ڸ�ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ��Ʊ��") , "notes_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ���˿�") , "accounts_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ԥ�տ���") , "advances_from_customers")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ��ְ��н��") , "employee_benefits_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ��˰��") , "taxes_and_surcharges_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ����Ϣ") , "interests_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ������") , "dividends_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӧ����") , "other_payables")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ��������˾��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("һ���ڵ��ڵķ�������ծ") , "non_current_liabilities_maturing_within_one_year")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����������ծ") , "other_current_liablities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������ծ�ϼ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ڽ��") , "total_current_liabilities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ��ծȯ") , "debentures_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӧ����") , "long_term_payables")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ר��Ӧ����") , "specific_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ԥ�Ƹ�ծ") , "anticipation_liabilities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������˰��ծ") , "deferred_tax_liabilities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������������ծ") , "other_non_current_liablities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������ծ�ϼ�") , "total_non_current_liabilities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ծ�ϼ�") , "total_liability")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ʵ���ʱ�����ɱ���") , "registered_capital")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ʱ�����") , "capital_surplus")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ӯ�๫��") , "surplus_reserve")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ר���") , "special_reserve")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������") , "treasury_stock")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("һ�����׼��") , "provision_for_normal_risks")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("δ��������") , "undistributed_profits")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������ĸ��˾������Ȩ��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ɶ�Ȩ��") , "minority_interest")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ұ�������۲�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������Ӫ��Ŀ�������") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������Ȩ�棨��ɶ�Ȩ�棩�ϼ�") , "total_owners_equity")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ծ�������ߣ���ɶ�Ȩ�棩�ϼ�") , "total_liabilities_and_owners_equity")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ۺ�����") , "other_consolidated_income")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������-��������ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���㱸����") , "provision_of_settlement_fund")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ʽ�") , "funds_lent")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���Ŵ�����-�����ʲ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���������ʲ�") , "derivative_financial_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ�ձ���") , "insurance_premiums_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ�շֱ��˿�") , "cession_premiums_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ�շֱ���ͬ׼����") , "provision_of_cession_receivable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���뷵�۽����ʲ�") , "buying_and_selling_financial_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ϊ���д��۵��ʲ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���Ŵ�����-�������ʲ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���������н��") , "borrowings_from_central_bank")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���մ�ͬҵ���") , "deposits_from_customers_and_interbank")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʽ�") , "deposit_funds")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������ڸ�ծ") , "derivative_financial_liabilities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ع������ʲ���") , "funds_from_sales_of_financial_assets_with_repurchasement")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ�������Ѽ�Ӷ��") , "handling_charges_and_commissions_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ӧ���ֱ��˿�") , "cession_insurance_premiums_payable")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���պ�ͬ׼����") , "provision_for_insurance_contracts")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������֤ȯ��") , "funds_received_as_agent_of_stock_exchange")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������֤ȯ��") , "funds_received_as_stock_underwrite")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ϊ���д��۵ĸ�ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ԥ�Ƹ�ծ-������ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������-������ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У����ȹ�-��������ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ծ-��������ծ") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ӧ��ְ��н��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ȩ�湤��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У����ȹ�-������Ȩ��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ծ-������Ȩ��") , "")); 
	
	


	for(int i=0; i< m_vec_yield.size(); i++)
	{
		m_map_yield.insert(m_vec_yield[i]);
	}

	m_strEnglishName = "cninfo_balance";
}


string CCninfoBalance::GetZipUrl()
{
	COleDateTime odt = COleDateTime::GetCurrentTime();
	char tmpPost[256] = { 0};
	if(m_nCode>=600000)
		sprintf(tmpPost,  "market=sh&type=fzb&code=%06d&orgid=%s&minYear=2001&maxYear=%d", 
		m_nCode, m_cninfo_orgid.c_str(), odt.GetYear());
	else
		sprintf(tmpPost,  "market=sz&type=fzb&code=%06d&orgid=%s&minYear=2001&maxYear=%d", 
		m_nCode, m_cninfo_orgid.c_str(), odt.GetYear());
	return  string(tmpPost);
}


CCninfoCashFlows::CCninfoCashFlows(void)
{

	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ID"), "code")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������"), "name")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������"), "announce_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ʼ����"), "start_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ֹ����"), "report_date")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������"), "year")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ϲ�����"), "union_type")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������Դ"), "report_source")); 

	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������Ʒ���ṩ�����յ����ֽ�Ԫ��") , "cash_received_from_sales_of_goods_or_rending_of_services")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�յ���˰�ѷ���") , "refund_of_tax_and_levies")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�յ������뾭Ӫ��йص��ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ӫ��ֽ�����С��") , "cash_inflow_from_business_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������Ʒ����������֧�����ֽ�") , "cash_from_purchasement_and_receiving_service_payments")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧����ְ���Լ�Ϊְ��֧�����ֽ�") , "cash_paid_to_employee_and_for_employee")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧���ĸ���˰��") , "payments_of_all_types_of_taxes")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧�������뾭Ӫ��йص��ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ӫ��ֽ�����С��") , "sub_total_of_cash_outflows_relating_to_business_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ӫ��������ֽ���������") , "net_cash_flow_from_business_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ջ�Ͷ���յ����ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ȡ��Ͷ�������յ����ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ù̶��ʲ��������ʲ������������ʲ��ջص��ֽ𾻶�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ӹ�˾������Ӫҵ��λ�յ����ֽ𾻶�") , "net_cash_received_from_disposals_of_subsidiaries_and_other")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�յ�������Ͷ�ʻ�йص��ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ�ʻ�ֽ�����С��") , "sub_total_of_cash_inflows_relating_to_investment_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����̶��ʲ��������ʲ������������ʲ�֧�����ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ��֧�����ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ѻ������Ӷ�") , "net_increase_of_hypothecated_loan")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ȡ���ӹ�˾������Ӫҵ��λ֧�����ֽ𾻶�") , "net_cash_from_subsidiary_corporation_and_other_business")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧��������Ͷ�ʻ�йص��ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ�ʻ�ֽ�����С��") , "sub_total_of_cash_outflows_relating_to_investment_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ�ʻ�������ֽ���������") , "net_cash_flows_from_investing_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����Ͷ���յ����ֽ�") , "cash_received_from_investors")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ȡ�ý���յ����ֽ�") , "cash_from_borrowings")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ծȯ�յ����ֽ�") , "proceeds_from_issuance_of_bonds")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�յ���������ʻ�йص��ֽ�") , "cash_from_other_relevant_financing_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ʻ�ֽ�����С��") , "sub_total_of_cash_inflows")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ծ��֧�����ֽ�") , "cash_repayments_of_amount_borrowed")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������������򳥸���Ϣ֧�����ֽ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧����������ʻ�йص��ֽ�") , "other_cash_payment_relating_to_financing_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ʻ�ֽ�����С��") , "sub_total_of_cash_outflows_relating_to_financing_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ʻ�������ֽ���������") , "net_cash_flows_from_financing_activities")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ġ����ʱ䶯���ֽ��Ӱ��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��(2)������ԭ����ֽ��Ӱ��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�塢�ֽ��ֽ�ȼ��ﾻ���Ӷ�") , "net_increase_in_cash_and_cash_equivalents")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ڳ��ֽ��ֽ�ȼ������") , "cash_and_cash_equivalents_at_beginning_of_period")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ĩ�ֽ��ֽ�ȼ������") , "cash_and_cash_equivalents_at_end_of_period")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ע��") , "supplemental_information")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("1�������������Ϊ��Ӫ��ֽ�������") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("������") , "net_profit")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ��ʲ���ֵ׼��") , "provision_for_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�̶��ʲ��۾ɡ������ʲ��ۺġ������������ʲ��۾�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʲ�̯��") , "amortisation_of_intangible_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ڴ�̯����̯��") , "amortisation_of_long_term_deffered_expenses")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ù̶��ʲ��������ʲ������������ʲ�����ʧ") , "losses_on_disposal_of_fixed_intangible_and_other_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�̶��ʲ�������ʧ") , "losses_on_scrapping_of_fixed_assets")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���ʼ�ֵ�䶯��ʧ") , "losses_on_fair_value")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�������") , "finance_expense")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ����ʧ") , "losses_arsing_from_investment")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������˰�ʲ�����") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������˰��ծ����") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����ļ���") , "decrease_in_inventories")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ӫ��Ӧ����Ŀ�ļ���") , "decrease_in_operating_receivables")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ӫ��Ӧ����Ŀ������") , "increase_in_operating_receivables")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����") , "others")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��Ӫ��������ֽ���������2") , "net_cash_flow_from_business_activities_2")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("2�����漰�ֽ���֧���ش�Ͷ�ʺͳ��ʻ��") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("ծ��תΪ�ʱ�") , "debts_transfer_to_capital")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("һ���ڵ��ڵĿ�ת����˾ծȯ") , "one_year_due_convertible_bonds")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������̶��ʲ�") , "financing_rent_to_the_fixed_asset")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("3���ֽ��ֽ�ȼ��ﾻ�䶯�����") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ֽ����ĩ���") , "cash_at_the_end_of_period")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ֽ���ڳ����") , "cash_at_the_beginning_of_the_period")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ��ֽ�ȼ������ĩ���") , "cash_equivalents_at_the_end_of_the_period")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ֽ�ȼ�����ڳ����") , "cash_equivalents_at_the_beginning_of_the_period")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ӣ�����ԭ����ֽ��Ӱ��2") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ֽ��ֽ�ȼ��ﾻ���Ӷ�2") , "net_increase_in_cash_and_cash_equivalents_2")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ͻ�����ͬҵ��ſ�����Ӷ�") , "net_increase_of_customers_deposit_and_deposit_of_interbank")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���������н����Ӷ�") , "net_increase_borrowings_from_central_bank")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���������ڻ��������ʽ����Ӷ�") , "net_increase_borrowing_funds_to_other_financing_institution")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�յ�ԭ���պ�ͬ����ȡ�õ��ֽ�") , "cash_from_original_insurance_contract_premium")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�յ��ٱ���ҵ���ֽ𾻶�") , "net_cash_from_reinsurance_business")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��������Ͷ�ʿ���Ӷ�") , "net_increase_of_insured_deposit_and_investment")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����Թ��ʼ�ֵ��������䶯���뵱������Ľ����ʲ������Ӷ�") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("��ȡ��Ϣ�������Ѽ�Ӷ����ֽ�") , "interest_handling_charges_and_commissions_received")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�����ʽ����Ӷ�") , "net_increase_of_loans")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ع�ҵ���ʽ����Ӷ�") , "net_increase_of_repurchasing_business_funds")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("�ͻ���������Ӷ�") , "net_increase_of_customer_loans_and_advances")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("����������к�ͬҵ������Ӷ�") , "net_increase_depositing_in_central_bank_and_other_banks")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧��ԭ���պ�ͬ�⸶������ֽ�") , "cash_paid_for_original_insurance_contract_compensation_payment")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧����Ϣ�������Ѽ�Ӷ����ֽ�") , "interests_handling_charges_and_commissions_paid")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("֧�������������ֽ�") , "cash_paid_for_policy_dividend")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У��ӹ�˾���������ɶ�Ͷ���յ����ֽ�") , "cash_from_minority_stockholders_by_subsidiary_corporation")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("���У��ӹ�˾֧���������ɶ��Ĺ���������") , "")); 
	m_vec_yield.insert(m_vec_yield.end(), make_pair(_T("Ͷ���Է��ز����۾ɼ�̯��") , "")); 


	for(int i=0; i< m_vec_yield.size(); i++)
	{
		m_map_yield.insert(m_vec_yield[i]);
	}

	m_strEnglishName = "cninfo_cashflows";
}


string CCninfoCashFlows::GetZipUrl()
{
	COleDateTime odt = COleDateTime::GetCurrentTime();
	char tmpPost[256] = { 0};
	if(m_nCode>=600000)
		sprintf(tmpPost,  "market=sh&type=llb&code=%06d&orgid=%s&minYear=2001&maxYear=%d", 
		m_nCode, m_cninfo_orgid.c_str(), odt.GetYear());
	else
		sprintf(tmpPost,  "market=sz&type=llb&code=%06d&orgid=%s&minYear=2001&maxYear=%d", 
		m_nCode, m_cninfo_orgid.c_str(), odt.GetYear());
	return  string(tmpPost);
}
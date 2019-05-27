#include "StdAfx.h"
#include "Stock.h"
#include "CapitalFlows163.h"

#include "UrlUtils.h"

CCapitalFlows163::CCapitalFlows163(void)
{
}

CCapitalFlows163::~CCapitalFlows163(void)
{
	m_vec_report_date.clear();
	m_vec_close.clear();
	m_vec_change_rate.clear();
	m_vec_turnover_rate.clear();
	m_vec_flow_in.clear();
	m_vec_flow_out.clear();

	m_vec_net_flow.clear();
	m_vec_main_flow_in.clear();
	m_vec_main_flow_out.clear();
	m_vec_main_net_flow.clear();
}

string CCapitalFlows163::GetCsvFileName()
{
	CString tmp;
	tmp.Format("%s/CapitalFlows163/CapitalFlows163(%06d)_.csv" ,g_strCurrentDir.c_str(), m_nCode);
	return string(tmp.GetBuffer());
}


string CCapitalFlows163::SqlScript()
{
	stringstream ss;
	ss << "create table if not exists CapitalFlows163 (Code int ,TradeDate date, Close DECIMAL(10,2), Change_Rate DECIMAL(10,2),  "
		<< " Turnover_Rate DECIMAL(10,2), FlowIn DECIMAL(15,4), FlowOut DECIMAL(15,4), NetFlow DECIMAL(15,4), MainFlowIn DECIMAL(15,4), "
		<< " MainFlowOut DECIMAL(15,4),   NetMainFlow  DECIMAL(15,4), PRIMARY KEY ( Code, TradeDate))";
	return ss.str();
}



int CCapitalFlows163::CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	string header[] = {
		"����",
		"���̼�",
		"�ǵ���",
		"������",
		"�ʽ����루��Ԫ��",
		"�ʽ���������Ԫ��",
		"�����루��Ԫ��",
		"�������루��Ԫ��",
		"������������Ԫ��",
		"���������루��Ԫ��"
	};

	if(arrayHeader.size()!=10)
		return CSV_CHECK_FORMAT_ERROR;

	for(int i=0; i<10; i++)
	{
		if(arrayHeader[i]!=header[i])
			return CSV_CHECK_FORMAT_ERROR;
	}

	if(arrayData.size()==0)
		return CSV_CHECK_DATA_EXIST_ERROR;

	stringstream ss;
	try{
		ss << "select count(*) as cnt from CapitalFlows163 "
			<< " where TradeDate>=\'" << arrayData[arrayData.size()-1][0] << "\' " 
			<< " and TradeDate<=\'" << arrayData[0][0] << "\' "
			<< " and Code=" << Int2String(m_nCode) << "  ";
		string test = ss.str();

		row r;
		session sql(g_MysqlPool);
		sql << ss.str(), into(r);
		assert(r.size() == 1);
		long long existCnt = r.get<long long>("cnt") ;
		if(existCnt == arrayData.size())
		{
			ss.str("");
			ss << "CCapitalFlows163::CheckReport �Ѵ�����ؼ�¼������ȡ��.";
			sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
			return CSV_CHECK_DATA_EXIST_ERROR;
		}
	}
	catch(std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}

	return CSV_CHECK_NO_ERROR;
}



void CCapitalFlows163::ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	stringstream ss;
	/*string connectString = "dbname=stock  port=3306   host=127.0.0.1 user=root  ";
	backend_factory const &backEnd = *soci::factory_mysql();*/

	m_vec_report_date.clear();
	m_vec_close.clear();
	m_vec_change_rate.clear();
	m_vec_turnover_rate.clear();
	m_vec_flow_in.clear();
	m_vec_flow_out.clear();

	m_vec_net_flow.clear();
	m_vec_main_flow_in.clear();
	m_vec_main_flow_out.clear();
	m_vec_main_net_flow.clear();

	try
	{
		ss << "CCapitalFlows163 ParseCsvFile������������\r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		for (int row = 0; row < arrayData.size(); row++)
		{
			int colnum = arrayData[row].size();
			
			m_vec_report_date[row]=arrayData[row][0];
			m_vec_close[row]= 1<colnum ? String2Double(arrayData[row][1]):0;
			m_vec_change_rate[row]= 2<colnum ? String2Double(arrayData[row][2].substr(0, arrayData[row][2].length()-1)):0;
			m_vec_turnover_rate[row]= 3<colnum ? String2Double(arrayData[row][3].substr(0, arrayData[row][3].length()-1)):0;
			m_vec_flow_in[row]= 4<colnum ? String2Double(arrayData[row][4]):0;
			m_vec_flow_out[row]=5<colnum ? String2Double(arrayData[row][5]):0;
			m_vec_net_flow[row]=6<colnum ? String2Double(arrayData[row][6]):0;
			m_vec_main_flow_in[row]=7<colnum ? String2Double(arrayData[row][7]):0;
			m_vec_main_flow_out[row]=8<colnum ? String2Double(arrayData[row][8]):0;
			m_vec_main_net_flow[row]=9<colnum ? String2Double(arrayData[row][9]):0;

		}

		ss.str("");
		ss << "OK, CCapitalFlows163 ParseCsvFile ���.\r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}

bool CCapitalFlows163::ParseCsvFileName(string szFileName)
{
	vector<string> firstMatch;
	if(Pcre2Grep(_T("CapitalFlows163\\(\\d+\\)"), szFileName,firstMatch )<=0)
		return false;

	string::size_type pos1 = firstMatch[0].find(")");
	string codeStr = firstMatch[0].substr(16, pos1-16);
	m_nCode = atoi(codeStr.c_str());
	return true;
}

void CCapitalFlows163::ImportToDatabase(void)
{
	if(m_nCode<=0)
		return;

	stringstream ss;

	try
	{
		vector<string>  vecSqlStr;
		CStockDownloadData sdd = ((CStockApp *)AfxGetApp())->m_StockDataLog.SearchStockByCode(m_nCode);
		string maxDate = sdd.CapitalFlows163;

		for (int row = 0; row < m_vec_report_date.size(); row++)
		{
			if(m_vec_report_date[row] > sdd.CapitalFlows163)
			{
				ss.str("");
				ss << "insert into CapitalFlows163 "
					<< " select " <<  Int2String(m_nCode) << ", \'" 
					<< m_vec_report_date[row] << "\', "
					<< Double2String(m_vec_close[row])  << ", "
					<< Double2String(m_vec_change_rate[row]) << ", "
					<< Double2String(m_vec_turnover_rate[row]) << ", "
					<< Double2String(m_vec_flow_in[row]) << ", "
					<< Double2String(m_vec_flow_out[row]) << ", "
					<< Double2String(m_vec_net_flow[row]) << ", "
					<< Double2String(m_vec_main_flow_in[row]) << ", "
					<< Double2String(m_vec_main_flow_out[row]) << ", "
					<< Double2String(m_vec_main_net_flow[row]) << " "

					<< " from dual where not exists (SELECT 1 from CapitalFlows163 " 
					<< " where TradeDate=\'" << m_vec_report_date[row] << "\' " 
					<< " and Code=" << Int2String(m_nCode) << "  ) ";

				string test = ss.str();
				vecSqlStr.insert(vecSqlStr.end(), test);

				if(maxDate < m_vec_report_date[row])
					maxDate = m_vec_report_date[row];
			}
		}

		if(vecSqlStr.size()>0)
		{
			session sql(g_MysqlPool);

			ss.str("");
			ss << SqlScript();
			sql << ss.str();

			for(int i = 0; i< vecSqlStr.size(); i++)
				sql << vecSqlStr[i];

			((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateStockByCode(m_nCode, "CapitalFlows163", maxDate);

			ss.str("");
			ss << "�������� " << vecSqlStr.size() ;
			ss << " OK, CCapitalFlows163::ImportToDatabase ���ݵ������. \r\n";
			sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		}
		
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}


string CCapitalFlows163::SaveAsCsv()
{

	m_vec_report_date.clear();
	m_vec_close.clear();
	m_vec_change_rate.clear();
	m_vec_turnover_rate.clear();
	m_vec_flow_in.clear();
	m_vec_flow_out.clear();
	m_vec_net_flow.clear();
	m_vec_main_flow_in.clear();
	m_vec_main_flow_out.clear();
	m_vec_main_net_flow.clear();


	stringstream ss;

	time_t time_start;
	time_t time_end;

	//	����Ҫ���صĿ�ʼʱ��
	CStockDownloadData sdd = ((CStockApp *)AfxGetApp())->m_StockDataLog.SearchStockByCode(m_nCode);
	string strLastTradeDate = sdd.CapitalFlows163;
	if(strLastTradeDate.empty())
		strLastTradeDate = LastTradeDateFromDatabase();
	if(!strLastTradeDate.empty())
		time_start = convert_string_to_time_t(strLastTradeDate + string(" 17:30:00"));
	else
		time_start = convert_string_to_time_t("1990-01-01 00:00:00");

	time_end = time (NULL);
	if(time_end - time_start < 24 * 3600)
		return "NoMoreData";
	time_end = CBussinessUtils::CurrentTradingDate(0);
	if(time_end - time_start < 24 * 3600)
		return "NoMoreData";

	//	�ӵ�һҳ��ʼ����
	CStdioFile  targetFile;
	bool bWriteTitle = true;
	int  nTry = 0;
	int  nTotalRow = 0;
	for(int page = 0; page<16; )
	{
		try
		{
			char tmpCode[256] = {0};
			sprintf(tmpCode, "http://quotes.money.163.com/trade/lszjlx_%06d,%d.html", m_nCode, page);

			string test = string(tmpCode);

			string  strGBK=CUrlUtils::PostUrlOfSouhu(tmpCode,NULL);
			strGBK = Utf8_GBK(strGBK);

			HTML::ParserDom parser;
			parser.parse(strGBK);
			tree<HTML::Node> dom = parser.getTree();

			tree<HTML::Node>::iterator it = dom.begin();
			tree<HTML::Node>::iterator end = dom.end();
			for (; it != end; ++it)
			{
				if (it->tagName() =="table")
				{
					it->parseAttributes();

					map<string,string> attrs = it->attributes();
					if(attrs.size()>0 && attrs["class"] == "table_bg001 border_box")
					{
						break;
					}

				}
			}

			if(it!=end)
			{
				//	���ص����� OK 
				nTry = 0;
				int nChild = dom.number_of_children(it);

				bool bNewData = false;
				int	 nCount = 0 ;

				tree<HTML::Node>::sibling_iterator si_it = dom.begin(it);
				tree<HTML::Node>::sibling_iterator si_end = dom.end(it);
				for( ; si_it!=si_end; si_it++)
				{
					string tagName = si_it->tagName();
					if(tagName=="tr")
					{
						int td_index = 0;
						string strTradeDate = "";
						string strClose = "0";
						string strChange = "0";
						string strTurnoverRate = "0";
						string strFlowIn = "0";
						string strFlowOut = "0";
						string strNetFlow = "0";
						string strMainFlowIn = "0";
						string strMainFlowOut = "0";
						string strMainNetFlow = "0";

						tree<HTML::Node>::sibling_iterator td_it = dom.begin(si_it);
						tree<HTML::Node>::sibling_iterator td_end = dom.end(si_it);
						for(; td_it!=td_end; td_it++)
						{
							tree<HTML::Node>::sibling_iterator val_it = dom.begin(td_it);
							tree<HTML::Node>::sibling_iterator val_end = dom.end(td_it);
							for(; val_it!=val_end; val_it++)
							{
								string text = val_it->text();
								tree<HTML::Node>::sibling_iterator span_it = dom.begin(val_it);
								tree<HTML::Node>::sibling_iterator span_end = dom.end(val_it);
								if(span_it!=span_end)
								{
									text = span_it->text();
								}

								trimString(text);
								if(text.empty()) 
									continue;

								if(td_index==0)
									strTradeDate = text;
								if(td_index==1)
									strClose = text;	
								if(td_index==2)
									strChange = text;		
								if(td_index==3)
									strTurnoverRate = text;		
								if(td_index==4)
									strFlowIn = text;	
								if(td_index==5)
									strFlowOut = text;	
								if(td_index==6)
									strNetFlow = text;	
								if(td_index==7)
									strMainFlowIn = text;	
								if(td_index==8)
									strMainFlowOut = text;	
								if(td_index==9)
									strMainNetFlow = text;	
								td_index++ ;
								//sendToOutput(text.c_str(), m_hWnd);
							}
						}

						time_t time_current = convert_string_to_time_t(strTradeDate + string(" 00:00:00"));

						if(time_current>time_start)
						{
							if(bWriteTitle)
							{
								
								bWriteTitle = false;
							}

							m_vec_report_date[nTotalRow]=strTradeDate;
							m_vec_close[nTotalRow]= String2Double(strClose);
							m_vec_change_rate[nTotalRow]= String2Double(strChange);
							m_vec_turnover_rate[nTotalRow]=String2Double(strTurnoverRate);
							m_vec_flow_in[nTotalRow]= String2Double(strFlowIn);
							m_vec_flow_out[nTotalRow]=String2Double(strFlowOut);
							m_vec_net_flow[nTotalRow]= String2Double(strNetFlow);
							m_vec_main_flow_in[nTotalRow]= String2Double(strMainFlowIn);
							m_vec_main_flow_out[nTotalRow]= String2Double(strMainFlowOut);
							m_vec_main_net_flow[nTotalRow]= String2Double(strMainNetFlow);

							nTotalRow++;

							bNewData = true;
						}

						nCount++;
					}
				}

				if(bNewData)
				{
					//	��ҳ�ɹ��� ��ʼ��ȡ��һҳ
					CString str;
					str.Format("163 �����ʽ��������ݣ���ȡ�ɹ�.��%d�� page %d, %d ��\r\n", m_nCode, page, nCount);
					// sendToOutput(str.GetBuffer(),m_hWnd, m_nLogType);

					page++;

				}
				else
				{
					//	��ҳ���е����ݣ����ݿ��Ѿ����ڣ���û��Ҫ������һҳ
					CString str;
					str.Format("163 �����ʽ��������ݣ���ȡ�ɹ�. ���������� ��%d�� Page %d , %d ��\r\n", m_nCode, page, nCount);
					// sendToOutput(str.GetBuffer(),m_hWnd, m_nLogType);
					break;
				}

			}
			else
			{
				nTry++;
				Sleep(300);
				if(nTry>=3)
				{
					
					return "";
				}
			}
		}
		catch (std::exception const & e)
		{
			ss.str("");
			ss << "163 �����ʽ���������,�쳣��" << m_nCode << "��" ;
			ss << e.what() << ' \r\n';
			sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);
		}
	}

	// ���˴�Ϊ��������
	if(bWriteTitle==false)
	{
		//	bWriteTitle == false, ˵�����γɹ�����������
		return "AlreadyInMemory";
	}
	return "NoMoreData";
}


string CCapitalFlows163::SaveAsCsv_old()
{
	stringstream ss;

	time_t time_start;
	time_t time_end;
	
	//	����Ҫ���صĿ�ʼʱ��
	string strLastTradeDate = LastTradeDateFromDatabase();
	if(!strLastTradeDate.empty())
		time_start = convert_string_to_time_t(strLastTradeDate + string(" 00:00:00"));
	else
		time_start = convert_string_to_time_t("1990-01-01 00:00:00");

	time_end = time (NULL);
	if(time_end - time_start < 24 * 3600)
		return "NoMoreData";
	time_end = CBussinessUtils::CurrentTradingDate(0);
	if(time_end - time_start < 24 * 3600)
		return "NoMoreData";
	
	//	�ӵ�һҳ��ʼ����
	CStdioFile  targetFile;
	bool bWriteTitle = true;
	int  nTry = 0;
	for(int page = 0; page<16; )
	{
		try
		{
			char tmpCode[256] = {0};
			sprintf(tmpCode, "http://quotes.money.163.com/trade/lszjlx_%06d,%d.html", m_nCode, page);
			
			string test = string(tmpCode);

			string  strGBK=CUrlUtils::PostUrlOfSouhu(tmpCode,NULL);
			strGBK = Utf8_GBK(strGBK);

			HTML::ParserDom parser;
			parser.parse(strGBK);
			tree<HTML::Node> dom = parser.getTree();

			tree<HTML::Node>::iterator it = dom.begin();
			tree<HTML::Node>::iterator end = dom.end();
			for (; it != end; ++it)
			{
				if (it->tagName() =="table")
				{
					it->parseAttributes();

					map<string,string> attrs = it->attributes();
					if(attrs.size()>0 && attrs["class"] == "table_bg001 border_box")
					{
						break;
					}

				}
			}

			if(it!=end)
			{
				//	���ص����� OK 
				nTry = 0;
				int nChild = dom.number_of_children(it);

				bool bNewData = false;
				int	 nCount = 0 ;

				tree<HTML::Node>::sibling_iterator si_it = dom.begin(it);
				tree<HTML::Node>::sibling_iterator si_end = dom.end(it);
				for( ; si_it!=si_end; si_it++)
				{
					string tagName = si_it->tagName();
					if(tagName=="tr")
					{
						int td_index = 0;
						string strTradeDate = "";
						string strClose = "0";
						string strChange = "0";
						string strTurnoverRate = "0";
						string strFlowIn = "0";
						string strFlowOut = "0";
						string strNetFlow = "0";
						string strMainFlowIn = "0";
						string strMainFlowOut = "0";
						string strMainNetFlow = "0";

						tree<HTML::Node>::sibling_iterator td_it = dom.begin(si_it);
						tree<HTML::Node>::sibling_iterator td_end = dom.end(si_it);
						for(; td_it!=td_end; td_it++)
						{
							tree<HTML::Node>::sibling_iterator val_it = dom.begin(td_it);
							tree<HTML::Node>::sibling_iterator val_end = dom.end(td_it);
							for(; val_it!=val_end; val_it++)
							{
								string text = val_it->text();
								tree<HTML::Node>::sibling_iterator span_it = dom.begin(val_it);
								tree<HTML::Node>::sibling_iterator span_end = dom.end(val_it);
								if(span_it!=span_end)
								{
									text = span_it->text();
								}

								trimString(text);
								if(text.empty()) 
									continue;

								if(td_index==0)
									strTradeDate = text;
								if(td_index==1)
									strClose = text;	
								if(td_index==2)
									strChange = text;		
								if(td_index==3)
									strTurnoverRate = text;		
								if(td_index==4)
									strFlowIn = text;	
								if(td_index==5)
									strFlowOut = text;	
								if(td_index==6)
									strNetFlow = text;	
								if(td_index==7)
									strMainFlowIn = text;	
								if(td_index==8)
									strMainFlowOut = text;	
								if(td_index==9)
									strMainNetFlow = text;	
								td_index++ ;
								//sendToOutput(text.c_str(), m_hWnd);
							}
						}

						time_t time_current = convert_string_to_time_t(strTradeDate + string(" 00:00:00"));

						if(time_current>time_start)
						{
							if(bWriteTitle)
							{
								BOOL b = targetFile.Open(GetCsvFileName().c_str(),\
									CFile::modeWrite|CFile::shareDenyWrite|CFile::modeCreate|CFile::typeText);
								if(b==FALSE)
									return "";
														

								//	��һ��ѭ��ʱ������� CSV �ļ��ı���ͷ
								ss.str("");
								ss << "����," << "���̼�," << "�ǵ���," << "������," << "�ʽ����루��Ԫ��,";
								ss << "�ʽ���������Ԫ��," << "�����루��Ԫ��," << "�������루��Ԫ��,";
								ss << "������������Ԫ��," << "���������루��Ԫ��" << "\n";
								targetFile.WriteString(ss.str().c_str());
								bWriteTitle = false;
							}

							ss.str("");
							ss << "\"" <<strTradeDate << "\",\"" << strClose << "\",\"" << strChange << "\",\"" << strTurnoverRate << "\",\"";
							ss << strFlowIn << "\",\"" << strFlowOut << "\",\"" << strNetFlow << "\",\"" ;
							ss << strMainFlowIn << "\",\"" << strMainFlowOut << "\",\"" << strMainNetFlow << "\"\n";
							targetFile.WriteString(ss.str().c_str());
							bNewData = true;
						}
						
						nCount++;
					}
				}

				if(bNewData)
				{
					//	��ҳ�ɹ��� ��ʼ��ȡ��һҳ
					CString str;
					str.Format("163 �����ʽ��������ݣ���ȡ�ɹ�.��%d�� page %d, %d ��\r\n", m_nCode, page, nCount);
					sendToOutput(str.GetBuffer(),m_hWnd, m_nLogType);

					page++;
				
				}
				else
				{
					//	��ҳ���е����ݣ����ݿ��Ѿ����ڣ���û��Ҫ������һҳ
					CString str;
					str.Format("163 �����ʽ��������ݣ���ȡ�ɹ�. ���������� ��%d�� Page %d , %d ��\r\n", m_nCode, page, nCount);
					sendToOutput(str.GetBuffer(),m_hWnd, m_nLogType);
					break;
				}
				
			}
			else
			{
				nTry++;
				Sleep(300);
				if(nTry>=3)
				{
					//	���ֶ�����أ����Ա��α���� CSV �ļ�
					if(bWriteTitle==false)
						targetFile.Close();
					return "";
				}
			}
		}
		catch (std::exception const & e)
		{
			ss.str("");
			ss << "163 �����ʽ���������,�쳣��" << m_nCode << "��" ;
			ss << e.what() << ' \r\n';
			sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);
		}
	}

	// ���˴�Ϊ��������
	if(bWriteTitle==false)
	{
		//	bWriteTitle == false, ˵�����γɹ�����������
		targetFile.Flush();
		targetFile.Close();
		return GetCsvFileName();
	}
	return "NoMoreData";
}


void CCapitalFlows163::ExportFromDatabase(double startTime, double endTime)
{
	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	try
	{
		ss << "CCapitalFlows163 ��ʼ�� MYSQL ��ȡ����......";
		ss << "��" << m_nCode << "��";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << "select Code, TradeDate, Close, Change_Rate, Turnover_Rate, FlowIn, FlowOut, NetFlow,"
			<< " MainFlowIn, MainFlowOut, NetMainFlow "
			<< " from CapitalFlows163 where Code=" << Int2String(m_nCode);
		if(endTime > startTime)
		{
			COleDateTime start, end;
			start.m_dt = startTime;
			end.m_dt = endTime;
			ss << " and TradeDate >= \'" << start.Format("%Y-%m-%d") << "\'";
			ss << " and TradeDate <= \'" << end.Format("%Y-%m-%d") << "\'";
		}
		ss	<< " order by TradeDate";

		row r;
		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		int cnt = 0;
		while (st.fetch())
		{
			{
				std::tm  tm = r.get<std::tm>("TradeDate");
				ss.str("");
				ss << (tm.tm_year + 1900) << "-" << (tm.tm_mon + 1) << "-" << tm.tm_mday ;
				m_vec_report_date[cnt] = ss.str();
			}
			m_vec_close[cnt] = r.get<double>("Close");
			m_vec_change_rate[cnt] = r.get<double>("Change_Rate");
			m_vec_turnover_rate[cnt] = r.get<double>("Turnover_Rate");
			m_vec_flow_in[cnt] = r.get<double>("FlowIn");
			m_vec_flow_out[cnt] = r.get<double>("FlowOut");
			m_vec_net_flow[cnt] = r.get<double>("NetFlow");
			m_vec_main_flow_in[cnt] = r.get<double>("MainFlowIn");
			m_vec_main_flow_out[cnt] = r.get<double>("MainFlowOut");
			m_vec_main_net_flow[cnt] = r.get<double>("NetMainFlow");

			cnt++;
		}


		if(cnt>0)
		{
			m_nRowNum = cnt;
		}

		ss.str("");
		ss << "OK, CCapitalFlows163 �� MYSQL ��ȡ�������.";
		ss << " �� " << cnt << "�� \r\n" ;
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}


string CCapitalFlows163::LastTradeDateFromDatabase()
{
	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();
	string lastTradeDate = "";
	try
	{

		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << "select max(TradeDate) as maxdate "
			<< " from CapitalFlows163 where Code=" << Int2String(m_nCode) ;

		string test = ss.str();

		row r;
		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		int cnt = 0;
		while (st.fetch())
		{
			{
				std::tm  tm = r.get<std::tm>("maxdate");
				ss.str("");
				ss << (tm.tm_year + 1900) << "-" << (tm.tm_mon + 1) << "-" << tm.tm_mday ;
				lastTradeDate = ss.str();
				break;
			}

			cnt++;
		}

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << "CCapitalFlows163::lastTradeDate maxdate = NULL.";
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	return lastTradeDate;
}
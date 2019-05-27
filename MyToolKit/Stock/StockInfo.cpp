#include "StdAfx.h"
#include "StockInfo.h"

//////////////////////////////////////////////////////////////////////////
//	��Ʊ������Ϣ��������

string CStockInfo::SqlScript()
{
	stringstream ss;

	//	2017-3-19 ����������ʱ��

	ss << " create table if not exists StockInfo ( "
		<< " code int ,abbreviation varchar(256), name varchar(256),  "
		<< " english_name varchar(256), register_addr varchar(256), " 
		<< " a_code int , a_abbreviation varchar(256), " 
		<< " a_time_to_market date, a_total_share int ,a_circulation_share int , "
		<< " b_code int , b_abbreviation varchar(256), " 
		<< " b_time_to_market date, b_total_share int ,b_circulation_share int , "
		<< " area varchar(256), province varchar(256), city varchar(256), " 
		<< " belong_to_industry varchar(256), web_addr varchar(256),"
		<< " stock_plate varchar(256), securities_exchange varchar(256), "
		<< " a_time_to_delisting date, a_time_to_suspend,  PRIMARY KEY(code))";

	return ss.str();
}

CStockInfo::~CStockInfo()
{
	m_vec_code.clear()			;	//	"��˾����",
	m_vec_abbreviation.clear()			;	//	"��˾���",
	m_vec_name.clear()			;	//	"��˾ȫ��",
	m_vec_english_name.clear()			;	//	"Ӣ������",
	m_vec_register_addr.clear()			;	//	"ע���ַ",
	m_vec_a_code.clear()			;	//	"A�ɴ���",
	m_vec_a_abbreviation.clear()			;	//	"A�ɼ��",
	m_vec_a_time_to_market.clear()			;	//	"A����������",
	m_vec_a_total_share.clear()			;	//	"A���ܹɱ�",
	m_vec_a_circulation_share.clear()			;	//	"A����ͨ�ɱ�",
	m_vec_b_code.clear()			;	//	"B�ɴ���",
	m_vec_b_abbreviation.clear()			;	//	"B�� �� ��",
	m_vec_b_time_to_market.clear()			;	//	"B����������",
	m_vec_b_total_share.clear()			;	//	"B���ܹɱ�",
	m_vec_b_circulation_share.clear()			;	//	"B����ͨ�ɱ�",
	m_vec_area.clear()			;	//	"�� ��",
	m_vec_province.clear()			;	//	"ʡ ��",
	m_vec_city.clear()			;	//	"�� ��",
	m_vec_belong_to_industry.clear() 			;	//	"������ҵ",
	m_vec_web_addr.clear()			;	//	"��˾��ַ"
	m_vec_cninfo_orgid.clear();
	m_vec_cninfo_pinyin.clear();
}

int	 CStockInfo::SearchStockByCode(int code)
{
	int index = -1;
	if(m_vec_code.size()>0)
	{
		map<int, int>::iterator it = m_vec_code.begin();
		for(; it!=m_vec_code.end(); it++)
		{
			if(it->second == code)
				return it->first;
		}
	}
	return index;
}

void CStockInfo::GenerateMap()
{
	for(int i=0; i<m_vec_code.size(); i++)
	{
		CStockInfoData csd;
		csd.code = m_vec_code[i];
		csd.a_abbreviation = m_vec_a_abbreviation[i];
		csd.a_circulation_share = m_vec_a_circulation_share[i];
		csd.a_time_to_market = m_vec_a_time_to_market[i];
		csd.a_total_share = m_vec_a_total_share[i];
		csd.abbreviation = m_vec_abbreviation[i];
		csd.area = m_vec_area[i];
		csd.belong_to_industry = m_vec_belong_to_industry[i];
		csd.city = m_vec_city[i];
		csd.province = m_vec_province[i];
		csd.name = m_vec_name[i];
		csd.stock_plate = m_stock_plate;
		csd.web_addr = m_vec_web_addr[i];
		m_CStockInfoDataMap[csd.code] = csd;
	}

	m_vec_code.clear()			;	//	"��˾����",
	m_vec_abbreviation.clear()			;	//	"��˾���",
	m_vec_name.clear()			;	//	"��˾ȫ��",
	m_vec_english_name.clear()			;	//	"Ӣ������",
	m_vec_register_addr.clear()			;	//	"ע���ַ",
	m_vec_a_code.clear()			;	//	"A�ɴ���",
	m_vec_a_abbreviation.clear()			;	//	"A�ɼ��",
	m_vec_a_time_to_market.clear()			;	//	"A����������",
	m_vec_a_total_share.clear()			;	//	"A���ܹɱ�",
	m_vec_a_circulation_share.clear()			;	//	"A����ͨ�ɱ�",
	m_vec_b_code.clear()			;	//	"B�ɴ���",
	m_vec_b_abbreviation.clear()			;	//	"B�� �� ��",
	m_vec_b_time_to_market.clear()			;	//	"B����������",
	m_vec_b_total_share.clear()			;	//	"B���ܹɱ�",
	m_vec_b_circulation_share.clear()			;	//	"B����ͨ�ɱ�",
	m_vec_area.clear()			;	//	"�� ��",
	m_vec_province.clear()			;	//	"ʡ ��",
	m_vec_city.clear()			;	//	"�� ��",
	m_vec_belong_to_industry.clear() 			;	//	"������ҵ",
	m_vec_web_addr.clear()			;	//	"��˾��ַ"

}

//////////////////////////////////////////////////////////////////////////
//	���ڹ�Ʊ��������

CShenzhenStockInfo::CShenzhenStockInfo(void)
{
}

CShenzhenStockInfo::~CShenzhenStockInfo(void)
{
}



int  CShenzhenStockInfo::CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	string header[] = {
		"��˾����",
		"��˾���",
		"��˾ȫ��",
		"Ӣ������",
		"ע���ַ",
		"A�ɴ���",
		"A�ɼ��",
		"A����������",
		"A���ܹɱ�",
		"A����ͨ�ɱ�",
		"B�ɴ���",
		"B�ɼ��",
		"B����������",
		"B���ܹɱ�",
		"B����ͨ�ɱ�",
		"�� ��",
		"ʡ ��",
		"�� ��",
		"������ҵ",
		"��˾��ַ"
	};

	if(arrayHeader.size()!=20)
		return CSV_CHECK_FORMAT_ERROR;

	for(int i=0; i<20; i++)
	{
		if(arrayHeader[i]!=header[i])
			return CSV_CHECK_FORMAT_ERROR;
	}
	return CSV_CHECK_NO_ERROR;
}



void CShenzhenStockInfo::ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	stringstream ss;
	/*string connectString = "dbname=stock  port=3306   host=127.0.0.1 user=root  ";
	backend_factory const &backEnd = *soci::factory_mysql();*/

	m_vec_code.clear()			;	//	"��˾����",
	m_vec_abbreviation.clear()			;	//	"��˾���",
	m_vec_name.clear()			;	//	"��˾ȫ��",
	m_vec_english_name.clear()			;	//	"Ӣ������",
	m_vec_register_addr.clear()			;	//	"ע���ַ",
	m_vec_a_code.clear()			;	//	"A�ɴ���",
	m_vec_a_abbreviation.clear()			;	//	"A�ɼ��",
	m_vec_a_time_to_market.clear()			;	//	"A����������",
	m_vec_a_total_share.clear()			;	//	"A���ܹɱ�",
	m_vec_a_circulation_share.clear()			;	//	"A����ͨ�ɱ�",
	m_vec_b_code.clear()			;	//	"B�ɴ���",
	m_vec_b_abbreviation.clear()			;	//	"B�� �� ��",
	m_vec_b_time_to_market.clear()			;	//	"B����������",
	m_vec_b_total_share.clear()			;	//	"B���ܹɱ�",
	m_vec_b_circulation_share.clear()			;	//	"B����ͨ�ɱ�",
	m_vec_area.clear()			;	//	"�� ��",
	m_vec_province.clear()			;	//	"ʡ ��",
	m_vec_city.clear()			;	//	"�� ��",
	m_vec_belong_to_industry.clear() 			;	//	"������ҵ",
	m_vec_web_addr.clear()			;	//	"��˾��ַ"
	

	try
	{
		ss << "CStockInfo ParseCsvFile������������\r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		for (int row = 0; row < arrayData.size(); row++)
		{
			m_vec_code[row]=atoi(arrayData[row][0].c_str());
			m_vec_abbreviation[row]=(arrayData[row][1]);
			m_vec_name[row]=(arrayData[row][2]);
			m_vec_english_name[row]=arrayData[row][3];
			m_vec_register_addr[row]=(arrayData[row][4]);
			m_vec_a_code[row]=atoi(arrayData[row][5].c_str());
			m_vec_a_abbreviation[row]=(arrayData[row][6]);
			m_vec_a_time_to_market[row]=arrayData[row][7];
			m_vec_a_total_share[row]=atoi(arrayData[row][8].c_str());
			m_vec_a_circulation_share[row]=atoi(arrayData[row][9].c_str());
			m_vec_b_code[row]=atoi(arrayData[row][10].c_str());
			m_vec_b_abbreviation[row]=(arrayData[row][11]);
			m_vec_b_time_to_market[row]=arrayData[row][12];
			m_vec_b_total_share[row]=atoi(arrayData[row][13].c_str());
			m_vec_b_circulation_share[row]=atoi(arrayData[row][14].c_str());
			m_vec_area[row]=(arrayData[row][15]);
			m_vec_province[row]=(arrayData[row][16]);
			m_vec_city[row]=(arrayData[row][17]);
			m_vec_belong_to_industry[row]=(arrayData[row][18]);
			m_vec_web_addr[row]=arrayData[row][19];
		
		}

		ss.str("");
		ss << "OK, CStockInfo ParseCsvFile ���.\r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}

void CShenzhenStockInfo::ParseXmlElement(void)
{
}

void CShenzhenStockInfo::ExportFromDatabase(double startTime, double endTime)
{
	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	int nLine = __LINE__;
	try
	{
		ss << "\n ��ʼ�� MYSQL ��ȡ����......";
		ss << "��" << m_stock_plate << "��";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		nLine = __LINE__;
		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << "select code, abbreviation, name, english_name,register_addr,"
			<<	"a_code, a_abbreviation, a_time_to_market, a_total_share, a_circulation_share,"
			<< "b_code, b_abbreviation, b_time_to_market, b_total_share, b_circulation_share,"
			<< "area, province, city, belong_to_industry, web_addr, cninfo_orgid, cninfo_pinyin "
			<< " from StockInfo where stock_plate=\'" << /*Gbk2Utf8*/(m_stock_plate) << "\' "
			<< " and securities_exchange=\'" <<  /*Gbk2Utf8*/(m_securities_exchange) << "\' "
			<< " order by code";

		row r;
		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		nLine = __LINE__;
		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		nLine = __LINE__;
		int cnt = 0;
		while (st.fetch())
		{
			m_vec_code[cnt] = r.get<int>("code");
			m_vec_abbreviation[cnt] = /*Utf8_GBK*/(r.get<string>("abbreviation"));
			m_vec_name[cnt] =/*Utf8_GBK*/(r.get<string>("name", ""));
			m_vec_english_name[cnt] = r.get<string>("english_name", "");
			m_vec_register_addr[cnt] = /*Utf8_GBK*/(r.get<string>("register_addr", ""));

			m_vec_a_code[cnt] = r.get<int>("a_code");
			m_vec_a_abbreviation[cnt] = /*Utf8_GBK*/(r.get<string>("a_abbreviation"));
			try
			{
				std::tm  tm = r.get<std::tm>("a_time_to_market");
				ss.str("");
				ss << (tm.tm_year + 1900) << "-" << (tm.tm_mon + 1) << "-" << tm.tm_mday ;
				m_vec_a_time_to_market[cnt] = ss.str();
			}
			catch(...)
			{
				m_vec_a_time_to_market[cnt] = "0000-00-00";
			}
			m_vec_a_total_share[cnt] = r.get<int>("a_total_share", 0);
			m_vec_a_circulation_share[cnt] = r.get<int>("a_circulation_share", 0);

			m_vec_b_code[cnt] = r.get<int>("b_code", 0);
			m_vec_b_abbreviation[cnt] = /*Utf8_GBK*/(r.get<string>("b_abbreviation", ""));
			try
			{
				std::tm  tm = r.get<std::tm>("b_time_to_market");
				ss.str("");
				ss << (tm.tm_year + 1900) << "-" << (tm.tm_mon + 1) << "-" << tm.tm_mday ;
				m_vec_b_time_to_market[cnt] = ss.str();
			}
			catch(...)
			{
				m_vec_b_time_to_market[cnt] = "0000-00-00";
			}
			m_vec_b_total_share[cnt] = r.get<int>("b_total_share", 0);
			m_vec_b_circulation_share[cnt] = r.get<int>("b_circulation_share", 0);
			m_vec_area[cnt] =/*Utf8_GBK*/( r.get<string>("area", ""));
			m_vec_province[cnt] = /*Utf8_GBK*/(r.get<string>("province", ""));
			m_vec_city[cnt] = /*Utf8_GBK*/(r.get<string>("city", ""));
			m_vec_belong_to_industry[cnt] = /*Utf8_GBK*/(r.get<string>("belong_to_industry", ""));
			m_vec_web_addr[cnt] = r.get<string>("web_addr", "");

			try{
				m_vec_cninfo_orgid[cnt] = r.get<string>("cninfo_orgid");
				m_vec_cninfo_pinyin[cnt] = r.get<string>("cninfo_pinyin");
			}
			catch(...)
			{
				m_vec_cninfo_orgid[cnt] = "";
				m_vec_cninfo_pinyin[cnt] = "";
			}
			
	
			cnt++;
		}
	

		if(cnt>0)
		{
			m_nRowNum = cnt;
		}
		
		ss.str("");
		ss << "OK, �� MYSQL ��ȡ�������.";
		ss << " �� " << cnt << "�� \r\n" ;
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("CShenzhenStockInfo::ExportFromDatabase ");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}


void CShenzhenStockInfo::ImportToDatabase(void)
{

	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();
	ss << "CStockInfo ��ʼ�������ݡ�����������\r\n";
	//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

	string connectString = "dbname=stock  port=3366   host=127.0.0.1 user=root  charset=gbk ";
	//session sql(backEnd, connectString);
	session sql(g_MysqlPool);

	//sql << "delete from stockinfo where code <> a_code";

	for (int row = 0; row < m_vec_code.size(); row++)
	{
		if(m_vec_code[row]==0)
			continue;
		ss.str("");

		
		ss << "insert into StockInfo ( code, abbreviation, name, english_name, register_addr, a_code, a_abbreviation, a_time_to_market, "
			<< " a_total_share, a_circulation_share, b_code, b_abbreviation, b_time_to_market, b_total_share, b_circulation_share, "
			<< " area, province, city, belong_to_industry, web_addr, stock_plate, securities_exchange )"
			<< " select " <<  Int2String(m_vec_code[row]) << ", " 
			<< " \'" << (m_vec_abbreviation[row]) << "\', "
			<< " \'" << (m_vec_name[row]) << "\', "
			<< " \"" << m_vec_english_name[row] << "\", "
			<< " \'" << (m_vec_register_addr[row]) << "\', "
			<< "   " << Int2String(m_vec_a_code[row]) << ", "
			<< " \'" << (m_vec_a_abbreviation[row]) << "\', "
			<< " \'" << m_vec_a_time_to_market[row] << "\', "
			<< " \'" << m_vec_a_total_share[row] << "\', "
			<< " \'" << m_vec_a_circulation_share[row] << "\', "
			<< "   " << Int2String(m_vec_b_code[row]) << ", "
			<< " \'" << (m_vec_b_abbreviation[row]) << "\', "
			<< " \'" << m_vec_b_time_to_market[row] << "\', "
			<< " \'" << m_vec_b_total_share[row] << "\', "
			<< " \'" << m_vec_b_circulation_share[row] << "\', "
			<< " \'" << (m_vec_area[row]) << "\', "
			<< " \'" << (m_vec_province[row]) << "\', "
			<< " \'" << (m_vec_city[row]) << "\', "
			<< " \'" << (m_vec_belong_to_industry[row]) << "\', "
			<< " \'" << (m_vec_web_addr[row]) << "\', "
			<< " \'" << (m_stock_plate) << "\', "
			<< " \'" << (m_securities_exchange) << "\' "
			<< " from dual where not exists (SELECT 1 from StockInfo " 
			<< " where code =" << Int2String(m_vec_code[row]) << "  ) ";

		string sql1 = ss.str();
		string sql1test = sql1;

		//sql1 = Gbk2Utf8(sql1);

		ss.str("");
		ss << "update StockInfo set "
			<< " abbreviation =\'" << (m_vec_abbreviation[row]) << "\', "
			<< " name =\'" << (m_vec_name[row]) << "\', "
			<< " english_name=\"" << m_vec_english_name[row] << "\", "
			<< " register_addr=\'" << (m_vec_register_addr[row]) << "\', "
			<< " a_code = " << Int2String(m_vec_a_code[row]) << ", "
			<< " a_abbreviation =\'" << (m_vec_a_abbreviation[row]) << "\', "
			<< " a_time_to_market =\'" << m_vec_a_time_to_market[row] << "\', "
			<< " a_total_share =\'" << m_vec_a_total_share[row] << "\', "
			<< " a_circulation_share =\'" << m_vec_a_circulation_share[row] << "\', "
			<< " b_code = " << Int2String(m_vec_b_code[row]) << ", "
			<< " b_abbreviation =\'" << (m_vec_b_abbreviation[row]) << "\', "
			<< " b_time_to_market =\'" << m_vec_b_time_to_market[row] << "\', "
			<< " b_total_share=\'" << m_vec_b_total_share[row] << "\', "
			<< " b_circulation_share=\'" << m_vec_b_circulation_share[row] << "\', "
			<< " area=\'" << (m_vec_area[row]) << "\', "
			<< " province=\'" << (m_vec_province[row]) << "\', "
			<< " city=\'" << (m_vec_city[row]) << "\', "
			<< " belong_to_industry=\'" << (m_vec_belong_to_industry[row]) << "\', "
			<< " web_addr=\'" << (m_vec_web_addr[row]) << "\',  "
			<< " stock_plate=\'" << m_stock_plate << "\', "
			<< " securities_exchange=\'" << m_securities_exchange << "\' "
			<< " where code =" << Int2String(m_vec_code[row]) << "   ";

		string sql2 = ss.str();
		string sql2test = sql2;
		//sql2 = Gbk2Utf8(sql2);

		try{
			sql << sql1;
			sql << sql2;
		}
		catch (std::exception const & e)
		{
			ss.str("");
			ss << "CShenzhenStockInfo::ImportToDatabase,  code��" << m_vec_code[row] << "��";
			ss << e.what() << '\n';
			sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		}

		//sendToOutput(ss.str().c_str());
	}
	ss.str("");
	ss << "CShenzhenStockInfo::ImportToDatabase �������� " << m_vec_code.size() ;
	ss << " OK,  ���ݵ������.";
	sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		
}



string  CShenzhenStockInfo::SaveAsCsv()
{
	stringstream ss;
	string html;
	tree<HTML::Node> dom;

	try
	{
		//////////////////////////////////////////////////////////////////////////
		//	���ڱ����Ѿ��ɹ����ص� �����Ը�����
		if(CheckDownloadFileInfo(GetCsvFileName())>0)
			return "NoMoreData";

		string::size_type pos = GetCsvFileName().find(".csv");
		string xlsFileName = GetCsvFileName().substr(0, pos);
		xlsFileName += ".xls";
		

		//////////////////////////////////////////////////////////////////////////

		ifstream file(xlsFileName.c_str());
		if (!file.is_open()) 
		{
			ss.str("");
			ss << "CShenzhenStockInfo::SaveAsCsv() Error! Open " << xlsFileName; 
			sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
			return "";
		}
		else
		{
			while (1)
			{
				char buf[BUFSIZ];
				file.read(buf, BUFSIZ);
				if(file.gcount() == 0) {
					break;
				}
				html.append(buf, file.gcount());
			}
			file.close();
		}

		//html = Utf8_GBK(html);

		CStdioFile  targetFile;
		bool bWriteTitle = true;

		HTML::ParserDom parser;
		parser.parse(html);
		dom = parser.getTree();

		tree<HTML::Node>::iterator it = dom.begin();
		tree<HTML::Node>::iterator end = dom.end();
		for (; it != end; ++it)
		{
			if (it->tagName() =="table")
			{
				tree<HTML::Node>::sibling_iterator tr_it = dom.begin(it);
				tree<HTML::Node>::sibling_iterator tr_end = dom.end(it);
				for( ; tr_it!=tr_end; tr_it++)
				{
					int td_index = 0;
					string code			;	//	"��˾����",
					string abbreviation			;	//	"��˾���",
					string name			;	//	"��˾ȫ��",
					string english_name			;	//	"Ӣ������",
					string register_addr			;	//	"ע���ַ",
					string a_code			;	//	"A�ɴ���",
					string a_abbreviation			;	//	"A�ɼ��",
					string a_time_to_market			;	//	"A����������",
					string a_total_share			;	//	"A���ܹɱ�",
					string a_circulation_share			;	//	"A����ͨ�ɱ�",
					string b_code			;	//	"B�ɴ���",
					string b_abbreviation			;	//	"B�� �� ��",
					string b_time_to_market			;	//	"B����������",
					string b_total_share			;	//	"B���ܹɱ�",
					string b_circulation_share			;	//	"B����ͨ�ɱ�",
					string area			;	//	"�� ��",
					string province			;	//	"ʡ ��",
					string city			;	//	"�� ��",
					string belong_to_industry 			;	//	"������ҵ",
					string web_addr	;

					string tagName = tr_it->tagName();
					if(tagName!="tr")
						continue;

					tr_it->parseAttributes();
					map<string,string> attrs = tr_it->attributes();
					/*if(attrs["class"] != "cls-data-tr")
						continue;*/

					if(bWriteTitle)
					{
						BOOL b = targetFile.Open(GetCsvFileName().c_str(), \
							CFile::modeWrite|CFile::shareDenyWrite|CFile::modeCreate|CFile::typeText);
						
						if(b==FALSE)
							return "";
						
						ss.str("");
						ss << "��˾����," << "��˾���," << "��˾ȫ��," << "Ӣ������," << "ע���ַ,"; 
						ss << "A�ɴ���," << "A�ɼ��," << "A����������," << "A���ܹɱ�," << "A����ͨ�ɱ�,"; 
						ss << "B�ɴ���," << "B�ɼ��," << "B����������," << "B���ܹɱ�," << "B����ͨ�ɱ�,"; 
						ss << "�� ��," << "ʡ ��," << "�� ��," << "������ҵ," << "��˾��ַ" << "\n"; 
						targetFile.WriteString(ss.str().c_str());
						bWriteTitle = false;
					}

					tree<HTML::Node>::sibling_iterator td_it = dom.begin(tr_it);
					tree<HTML::Node>::sibling_iterator td_end = dom.end(tr_it);
					for( ; td_it!=td_end; td_it++)
					{
						if(td_it->tagName()!="td")
							continue;
						td_it->parseAttributes();
						map<string,string> attrs1 = td_it->attributes();
						/*if(attrs1["class"]!="cls-data-td")
							continue;*/

						tree<HTML::Node>::sibling_iterator val_it = dom.begin(td_it);
						tree<HTML::Node>::sibling_iterator val_end = dom.end(td_it);
						for(; val_it!=val_end; val_it++)
						{
							string text = val_it->text();
							if(td_index==0)		code = text;
							if(td_index==1)		abbreviation = text;	
							if(td_index==2)		name = text;		
							if(td_index==3)		english_name = ReplaceString(text, "\"", _T("��"));				
							if(td_index==4)		register_addr = ReplaceString(text, "\"", _T("��"));
							
							if(td_index==5)		a_code = text;		
							if(td_index==6)		a_abbreviation = text;			
							if(td_index==7)		a_time_to_market = text;
							if(td_index==8)		a_total_share = text;	
							if(td_index==9)		a_circulation_share = text;	

							if(td_index==10)	b_code = text;		
							if(td_index==11)	b_abbreviation = text;
							if(td_index==12)	b_time_to_market = text;	
							if(td_index==13)	b_total_share = text;		
							if(td_index==14)	b_circulation_share = text;		

							if(td_index==15)	area = text;
							if(td_index==16)	province = text;	
							if(td_index==17)	city = text;		
							if(td_index==18)	belong_to_industry = text;		
							if(td_index==19)	web_addr = text;
						}
						td_index++ ;
					}
					
					ss.str("");
					ss << "\"" << code << "\",\"" << abbreviation << "\",\"" << name << "\",\"" << english_name << "\",\"" << register_addr << "\",\""; 
					ss << a_code << "\",\"" << a_abbreviation << "\",\"" << a_time_to_market << "\",\"" << a_total_share << "\",\"" << a_circulation_share << "\",\""; 
					ss << b_code << "\",\"" << b_abbreviation << "\",\"" << b_time_to_market << "\",\"" << b_total_share << "\",\"" << b_circulation_share << "\",\""; 
					ss << area << "\",\"" << province << "\",\"" << city << "\",\"" << belong_to_industry << "\",\"" << web_addr << "\"\n"; 
					targetFile.WriteString(ss.str().c_str());
				}
			}
		}

		if(bWriteTitle==false)
		{
			targetFile.Flush();
			targetFile.Close();
			return GetCsvFileName();
		}
	}
	catch(...)
	{

	}
	return "";
}

bool CShenzhenStockInfo::ParseCsvFileName(string szFileName)
{
	vector<string> firstMatch;
	if(Pcre2Grep(m_strEnglishName.c_str(), szFileName,firstMatch )<=0)
		return false;

	return true;
}

string CShenzhenStockInfo::GetCsvFileName()
{
	CString tmp;
	tmp.Format("%s/StockInfo/%s.csv" ,g_strCurrentDir.c_str(), m_strEnglishName.c_str());
	return string(tmp.GetBuffer());
}


//////////////////////////////////////////////////////////////////////////
//	��ҵ��

string CEntrepreneurship::GetDownloadUrl()
{
	string url = "";
	char cmdline[512]; 
	CString tmp;     

	//////////////////////////////////////////////////////////////////////////
	//	���ڱ����Ѿ��ɹ����ص� �����Ը�����

	if(CheckDownloadFileInfo("./StockInfo/Entrepreneurship.xls")>0)
		return url;

	tmp.Format("wget.exe http://www.szse.cn/szseWeb/ShowReport.szse?SHOWTYPE=EXCEL&CATALOGID=1110&tab6PAGENUM=1&ENCODE=1&TABKEY=tab6 -O ./StockInfo/Entrepreneurship.xls", \
		m_nCode, m_nCode);    

	sprintf(cmdline,"%s",tmp);    
	url = string(cmdline);
	return url;
}





CStockDataModel * CEntrepreneurship::NewCopy()
{
	CEntrepreneurship * pTrading = new CEntrepreneurship();
	pTrading->m_nRowNum = m_nRowNum;


	return pTrading;
}




//////////////////////////////////////////////////////////////////////////
//	��С��ҵ��

string CSmallMidEnterprise::GetDownloadUrl()
{
	string url ="";
	char cmdline[512]; 
	CString tmp;     

	//////////////////////////////////////////////////////////////////////////
	//	���ڱ����Ѿ��ɹ����ص� �����Ը�����

	if(CheckDownloadFileInfo("./StockInfo/SmallMidEnterprise.xls")>0)
		return url;

	tmp.Format("wget.exe http://www.szse.cn/szseWeb/ShowReport.szse?SHOWTYPE=EXCEL&CATALOGID=1110&tab5PAGENUM=1&ENCODE=1&TABKEY=tab5 -O ./StockInfo/SmallMidEnterprise.xls", \
		m_nCode, m_nCode);    

	sprintf(cmdline,"%s",tmp);    
	url = string(cmdline);
	return url;
}


CStockDataModel * CSmallMidEnterprise::NewCopy()
{
	CSmallMidEnterprise * pTrading = new CSmallMidEnterprise();
	pTrading->m_nRowNum = m_nRowNum;


	return pTrading;
}


//////////////////////////////////////////////////////////////////////////
//	����A��

string CShenzhenAshares::GetDownloadUrl()
{
	string url = "";
	char cmdline[512]; 
	CString tmp;     

	//////////////////////////////////////////////////////////////////////////
	//	���ڱ����Ѿ��ɹ����ص� �����Ը�����

	if(CheckDownloadFileInfo("./StockInfo/ShenzhenAshares.xls")>0)
		return url;

	tmp.Format("wget.exe http://www.szse.cn/szseWeb/ShowReport.szse?SHOWTYPE=EXCEL&CATALOGID=1110&tab5PAGENUM=2&ENCODE=1&TABKEY=tab2 -O ./StockInfo/ShenzhenAshares.xls", \
		m_nCode, m_nCode);    

	sprintf(cmdline,"%s",tmp);    
	url = string(cmdline);
	return url;
}



CStockDataModel * CShenzhenAshares::NewCopy()
{
	CShenzhenAshares * pTrading = new CShenzhenAshares();
	pTrading->m_nRowNum = m_nRowNum;


	return pTrading;
}
#include "StdAfx.h"
#include "CsdcInvestorStat.h"

#include "UrlUtils.h"
#include "HtmlParser.h"


//////////////////////////////////////////////////////////////////////////

class CCsdcInvestorStatTitleHtmlParser: public CHtmlParser
{
public:
	CCsdcInvestorStatTitleHtmlParser(tree<HTML::Node> &dom, CCsdcInvestorStat & userContext)
		:CHtmlParser(dom),m_Stat(userContext)
	{
	}

	~CCsdcInvestorStatTitleHtmlParser()
	{

	}

	void HtmlNodeCallBack(string xpath, string val, map<string,string> attrsOfParent)
	{
		stringstream ss;
		int h, begin_year, begin_month, begin_date, end_year, end_month, end_date;

		if(sscanf_s(xpath.c_str(), "/h2[%d]", &h)==1)
		{
			if(sscanf_s(val.c_str(), "һ��Ͷ�������ͳ�Ʊ�%d.%d.%d-%d.%d.%d��", 
				&begin_year, &begin_month, &begin_date, &end_year, &end_month, &end_date)==6)
			{
				char tmp[32] = {0};
				sprintf_s(tmp,32, "%04d-%02d-%02d", begin_year, begin_month, begin_date);
				m_Stat.m_vec_begin_date.insert(m_Stat.m_vec_begin_date.end(), tmp);

				sprintf_s(tmp,32, "%04d-%02d-%02d", end_year, end_month, end_date);
				m_Stat.m_vec_end_date.insert(m_Stat.m_vec_end_date.end(), tmp);
			}
		}
			
	}

private:
	CCsdcInvestorStat & m_Stat;

};

//////////////////////////////////////////////////////////////////////////

class CCsdcInvestorStatHtmlParser: public CHtmlParser
{
public:
	CCsdcInvestorStatHtmlParser(tree<HTML::Node> &dom, CCsdcInvestorStat & userContext)
		:CHtmlParser(dom),m_Stat(userContext)
	{
	}

	~CCsdcInvestorStatHtmlParser()
	{

	}

	void HtmlNodeCallBack(string xpath, string val, map<string,string> attrsOfParent)
	{
		stringstream ss;
		int temp, tr, td, p, span;

		transform(xpath.begin(), xpath.end(), xpath.begin(), ::toupper);  
		string::size_type pos1 = xpath.find("/TABLE");
		if(pos1!=string::npos) 
			xpath = xpath.substr(pos1);
		
		vector<string> vecMatch;
		if(Pcre2Grep(_T("/TR\\[[\\d]+\\]/TD\\[[\\d]+\\]/P\\[[\\d]+\\]/SPAN\\[[\\d]+\\]"), xpath.c_str() ,vecMatch )>0)
		{
			sscanf_s(vecMatch[0].c_str(), "/TR[%d]/TD[%d]/P[%d]/SPAN[%d]", &tr, &td, &p, &span);
		}

		if(vecMatch.size()>0)
		{
			if(td==1)
			{
				switch(tr)
				{
				case 7:		/* �ѿ���A���˻�Ͷ���� ��Ȼ��*/
					m_Stat.m_vec_final_a_natural_investor.insert(m_Stat.m_vec_final_a_natural_investor.end(),
						String2Double(val.c_str()));
					break;
				case 8:		/* �ѿ���B���˻�Ͷ���� ��Ȼ��*/
					m_Stat.m_vec_final_b_natural_investor.insert(m_Stat.m_vec_final_b_natural_investor.end(),
						String2Double(val.c_str()));
					break;
				case 11:	/* �ѿ���A���˻�Ͷ����, ����Ȼ�� */
					m_Stat.m_vec_final_a_legal_investor.insert(m_Stat.m_vec_final_a_legal_investor.end(),
						String2Double(val.c_str()));
					break;
				case 12:	/* �ѿ���B���˻�Ͷ����, ����Ȼ�� */
					m_Stat.m_vec_final_b_legal_investor.insert(m_Stat.m_vec_final_b_legal_investor.end(),
						String2Double(val.c_str()));
					break;
				case 15:	/* ��ĩA�ɳֲ�Ͷ���� */
					m_Stat.m_vec_final_a_position_investor.insert(m_Stat.m_vec_final_a_position_investor.end(),
						String2Double(val.c_str()));
					break;
				case 16:
					m_Stat.m_vec_final_b_position_investor.insert(m_Stat.m_vec_final_b_position_investor.end(),
						String2Double(val.c_str()));
					break;
				case 19:	/* �ڼ���뽻��Ͷ���� */
					m_Stat.m_vec_period_a_trading_investor.insert(m_Stat.m_vec_period_a_trading_investor.end(),
						String2Double(val.c_str()));
					break;
				case 20:
					m_Stat.m_vec_period_b_trading_investor.insert(m_Stat.m_vec_period_b_trading_investor.end(),
						String2Double(val.c_str()));
					break;
				}
			}
		}
	}

private:
	int		m_rowType;			//	
	string	m_recentDate;
	CCsdcInvestorStat & m_Stat;

};

//////////////////////////////////////////////////////////////////////////

CCsdcInvestorStat::CCsdcInvestorStat(void)
{
}

CCsdcInvestorStat::~CCsdcInvestorStat(void)
{
}



string  CCsdcInvestorStat::SaveAsCsv()
{
	if(m_nCode<20150504)
		return "";

	stringstream ss;

	m_vec_begin_date.clear();
	m_vec_end_date.clear();
	m_vec_final_a_natural_investor.clear();
	m_vec_final_a_legal_investor.clear();
	m_vec_final_b_natural_investor.clear();
	m_vec_final_b_legal_investor.clear();
	m_vec_final_a_position_investor.clear();
	m_vec_final_b_position_investor.clear();
	m_vec_period_a_trading_investor.clear();
	m_vec_period_b_trading_investor.clear();

	char tmpCode[256] = {0};
	sprintf(tmpCode, "http://www.chinaclear.cn/cms-search/view.action?action=china");

	char tmpData[256] = {0};
	sprintf(tmpData, "dateType=&dateStr=%s.%s.%s&channelIdStr=6ac54ce22db4474abc234d6edbe53ae7",
		Int2String(m_nCode).substr(0,4).c_str(), 
		Int2String(m_nCode).substr(4,2).c_str(),
		Int2String(m_nCode).substr(6,2).c_str());

	/*����ʹ�� Post ������PostUrlOfSouhu �ĵڶ���������Ϊ NULL ʱʹ���� Post ������ʹ�� Get ����*/
	string htmlPage =CUrlUtils::PostUrlOfSouhu(tmpCode,tmpData);
	htmlPage = Utf8_GBK(htmlPage);

	/*�������⣬��ȡʱ��*/
	{
		HTML::ParserDom parser;
		parser.parse(htmlPage);
		tree<HTML::Node> dom = parser.getTree();

		tree<HTML::Node>::iterator it = dom.begin();
		tree<HTML::Node>::iterator end = dom.end();
		for (; it != end; ++it)
		{
			if (it->tagName() =="div")
			{
				it->parseAttributes();

				map<string,string> attrs = it->attributes();
				if(attrs.size()>0 && attrs["class"] == "SettlementTitle")
				{
					break;
				}
			}
		}

		if(it!=end)
		{
			CCsdcInvestorStatTitleHtmlParser parser(dom, *this);
			parser.Parse(it, "");
		}
		else
			return "";
	}

	/*�����������*/
	{
		HTML::ParserDom parser;
		parser.parse(htmlPage);
		tree<HTML::Node> dom = parser.getTree();

		tree<HTML::Node>::iterator it = dom.begin();
		tree<HTML::Node>::iterator end = dom.end();
		for (; it != end; ++it)
		{
			if (it->tagName() =="div")
			{
				it->parseAttributes();

				map<string,string> attrs = it->attributes();
				if(attrs.size()>0 && attrs["id"] == "settlementList")
				{
					break;
				}
			}
		}

		if(it!=end)
		{
			CCsdcInvestorStatHtmlParser parser(dom, *this);
			parser.Parse(it, "");

			int recordSize = m_vec_begin_date.size(); 
			if(recordSize==m_vec_end_date.size() && recordSize >0 &&
				recordSize==m_vec_final_a_legal_investor.size() &&
				recordSize==m_vec_final_a_natural_investor.size()&&
				recordSize==m_vec_final_b_legal_investor.size()&&
				recordSize==m_vec_final_b_natural_investor.size()&&
				recordSize==m_vec_final_b_position_investor.size())
				return "AlreadyInMemory";
		}
	}
		
	return "";

}

string CCsdcInvestorStat::SqlScript()
{
	stringstream ss;
	ss << "create table if not exists CsdcInvestorStat (begin_date date , end_date date,  " 
		<< " final_a_natural_investor DECIMAL(12,2), final_a_legal_investor DECIMAL(12,2), "
		<< " final_b_natural_investor DECIMAL(12,2), final_b_legal_investor DECIMAL(12,2), "
		<< " final_a_position_investor DECIMAL(12,2), final_b_position_investor DECIMAL(12,2), "
		<< " period_a_trading_investor DECIMAL(12,2), period_b_trading_investor DECIMAL(12,2), "
		<< " PRIMARY KEY ( begin_date ))";
	return ss.str();
}

void CCsdcInvestorStat::ImportToDatabase(void)
{
	if(m_nCode<=0)
		return;

	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	try
	{
		ss << "CCsdcInvestorStat::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		ss.str("");
		ss << SqlScript();
		sql << ss.str();

		for(int i =0; i<m_vec_begin_date.size(); i++)
		{
			ss.str("");
			ss << "insert into CsdcInvestorStat ("
				<< "begin_date, end_date,  " 
				<< " final_a_natural_investor , final_a_legal_investor , "
				<< " final_b_natural_investor , final_b_legal_investor , "
				<< " final_a_position_investor , final_b_position_investor , "
				<< " period_a_trading_investor , period_b_trading_investor ) "
				<< " select \'" << m_vec_begin_date[i] << "\', \'" 
				<< m_vec_end_date[i] << "\',"
				<< Double2String(m_vec_final_a_natural_investor[i]) << ","
				<< Double2String(m_vec_final_a_legal_investor[i]) << ", "
				<< Double2String(m_vec_final_b_natural_investor[i]) << ","
				<< Double2String(m_vec_final_b_legal_investor[i]) << ","
				<< Double2String(m_vec_final_a_position_investor[i]) << ", "
				<< Double2String(m_vec_final_b_position_investor[i]) << ", "
				<< Double2String(m_vec_period_a_trading_investor[i]) << ", "
				<< Double2String(m_vec_period_b_trading_investor[i]) << " "

				<< " from dual where not exists ( SELECT 1 from CsdcInvestorStat " 
				<< " where begin_date=\'" <<  m_vec_begin_date[i] << "\' )";

			string test = ss.str();
			//test = Gbk2Utf8(test);
			sql << test; 
		}


		ss.str("");
		ss << "��"  << Int2String(m_nCode) << "��";
		ss << "�������� " << m_vec_begin_date.size() ;
		ss << " OK, CCsdcInvestorStat::ImportToDatabase ���ݵ������. \r\n";
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

#include "StdAfx.h"
#include "CalcCsiCsrcPeDailyDownload.h"

CCalcCsiCsrcPeDailyDownload::CCalcCsiCsrcPeDailyDownload(HWND hwnd, int logType)
:CCalculateTask(hwnd, logType)
{
}

CCalcCsiCsrcPeDailyDownload::~CCalcCsiCsrcPeDailyDownload(void)
{
}


void CCalcCsiCsrcPeDailyDownload::NeedDownload1(void* firstArg)
{
	CCalcCsiCsrcPeDailyDownload * sink = (CCalcCsiCsrcPeDailyDownload *)firstArg;
	sink->NeedDownload();
}



void CCalcCsiCsrcPeDailyDownload::NeedDownload()
{
	/*������Ҫ����֤ȯ�ලίԱ����ҵ��ӯ�ʵȵ�����*/
	stringstream ss;
	map<string, int> map_trade_date;
	map_trade_date.clear();

	ss.str("");
	ss << "����" << m_nTaskID << "�� ";
	ss << "NeedDownload ��ʼ����";
	sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

	try{

		ss.str("");
		ss << "select DATE_FORMAT(TradeDate, '%Y-%m-%d') as TradeDate from sohuindexdaily where code = 1 and TradeDate > '2013-2-19'";

		session sql(g_MysqlPool);
		row r;
		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();
		while (st.fetch())
		{
			string  tradeDate = r.get<string>("TradeDate");
			string	tradeDate1 = ReplaceString(tradeDate, "-", "");

			map_trade_date[tradeDate] = atoi(tradeDate1.c_str());
		}

		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << " select DISTINCT DATE_FORMAT(TradeDate, '%Y-%m-%d') as TradeDate , count(*) as cnt  ";
		ss << " from csicsrcpedaily group by TradeDate order by TradeDate ";
		
		string test = ss.str();
		//test = Gbk2Utf8(test);

		try{
			row r;
			session sql(g_MysqlPool);

			statement st = (sql.prepare << test,into(r)) ;
			st.execute();

			int lastCnt = 0;
			while (st.fetch())
			{
				string  tradeDate = r.get<string>("TradeDate");
				int cnt = r.get<long long>("cnt");
				
				if(cnt + 5 >= lastCnt)   
				{
					//	����ļ�¼Ӧ�� >= ����ļ�¼, ������ձ���δ����, ��������������ٵ�������5��
					map_trade_date.erase(tradeDate);
				}
				lastCnt = cnt;
			}
		}
		catch(...){}

		m_vec_code.clear();
		map<string, int>::iterator it = map_trade_date.begin();
		while(it!=map_trade_date.end())
		{
			m_vec_code.push_back(it->second);
			it++;
		}

		ss.str("");
		ss << "����" << m_nTaskID << "�� ";
		ss << "��Ҫ���� ��֤�����ҵ��ӯ�ʵȡ� �������� ��";
		ss << m_vec_code.size() << " \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	catch(std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}
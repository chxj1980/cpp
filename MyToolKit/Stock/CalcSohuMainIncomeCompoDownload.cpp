#include "StdAfx.h"
#include "CalcSohuMainIncomeCompoDownload.h"

CCalcSohuMainIncomeCompoDownload::CCalcSohuMainIncomeCompoDownload(HWND hwnd, int logType)
:CCalculateTask(hwnd, logType)
{
}

CCalcSohuMainIncomeCompoDownload::~CCalcSohuMainIncomeCompoDownload(void)
{
}




void CCalcSohuMainIncomeCompoDownload::Execute1(void* firstArg)
{
	CCalcSohuMainIncomeCompoDownload * sink = (CCalcSohuMainIncomeCompoDownload *)firstArg;
	sink->Execute();
}



void CCalcSohuMainIncomeCompoDownload::Execute()
{
	/*������Ҫ������Ӫҵ�񹹳ɵĹ�Ʊ*/

	stringstream ss;
	m_vec_code.clear();

	try{

		//////////////////////////////////////////////////////////////////////////
		ss.str("");

		ss << " select a.code"  
			<< " from (SELECT code, max(report_date) as max_date FROM  sohumainincomecomposition  group by code) a"
			<< " where date_sub(now(), INTERVAL 180 day) > a.max_date "
			<< " union "
			<< " select a.code FROM "
			<< " stockinfo  a where not exists (SELECT code FROM  sohumainincomecomposition b where a.code = b.code)";

		string test = ss.str();
		//test = Gbk2Utf8(test);

		row r;
		session sql(g_MysqlPool);

		statement st = (sql.prepare << test,into(r)) ;
		st.execute();

		int cnt = 0;
		while (st.fetch())
		{
			int code = r.get<int>("code");
			m_vec_code.insert(m_vec_code.end(), code);
			cnt++;
		}

		ss.str("");
		ss << "��Ҫ���� ����Ӫҵ�񹹳ɡ� �Ĺ�Ʊ�� ��";
		ss << cnt << " \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	catch(std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}
#include "StdAfx.h"
#include "CalcFinanceReport.h"

CCalcFinanceReport::CCalcFinanceReport(HWND hwnd, int logType)
:CCalculateTask(hwnd, logType)
{
}

CCalcFinanceReport::~CCalcFinanceReport(void)
{
}




void CCalcFinanceReport::Execute1(void* firstArg)
{
	CCalcFinanceReport * sink = (CCalcFinanceReport *)firstArg;
	sink->Execute();
}



void CCalcFinanceReport::Execute()
{
	/*������Ҫ���ز��񱨱�Ĺ�Ʊ*/

	
	stringstream ss;
	zb_code.clear();
	zb_name.clear();
	sj_code.clear();

	data.clear();
	unit.clear();

	try{

		session sql(g_MysqlPool);

		//////////////////////////////////////////////////////////////////////////
		ss.str("");

		/* select �Ӿ� */
		ss << "select   ";
		if(m_vec_csrc_gate_code.size()>0)
		{
			ss << " b.csrc_gate_industry_name , b.csrc_gate_industry_code, ";
		}
		if(m_vec_csrc_big_code.size()>0)
		{
			ss << " b.csrc_big_industry_name , b.csrc_big_industry_code, ";
		}
		if(m_vec_reg_code.size()>0)
		{
			ss << " b.statsgov_area_name, b.statsgov_area_code, ";
		}
		ss << " DATE_FORMAT(a.report_date, '%Y-%m-%d') as report_date, ";
		
		if(m_vec_zb_code.size()>0)
		{
			ss << " sum(" << m_vec_zb_code[0] << ") as colume_2 ";
		}
		

		/* from �Ӿ� */
		ss << " from  " <<  m_str_db_code  << " a, stockinfo b  where a.code = b.code ";

		/* where �Ӿ� */
		if(m_vec_csrc_gate_code.size()>0)
		{
			ss << " and b.csrc_gate_industry_code in ( ";
			for(int m=0; m< m_vec_csrc_gate_code.size(); m++)
			{
				ss << "\'" << m_vec_csrc_gate_code[m] << "\'" ;

				if(m!=m_vec_csrc_gate_code.size()-1)
					ss << ",";
				else
					ss << " ) ";
			}
		}

		if(m_vec_csrc_big_code.size()>0)
		{
			ss << " and b.csrc_big_industry_code in ( ";
			for(int m=0; m< m_vec_csrc_big_code.size(); m++)
			{
				ss << "\'" << m_vec_csrc_big_code[m] << "\'" ;

				if(m!=m_vec_csrc_big_code.size()-1)
					ss << ",";
				else
					ss << " ) ";
			}
		}

		if(m_vec_reg_code.size()>0)
		{
			ss << " and  b.statsgov_area_code in ( ";
			for(int m=0; m< m_vec_reg_code.size(); m++)
			{
				ss << "\'" << m_vec_reg_code[m] << "\'" ;

				if(m!=m_vec_reg_code.size()-1)
					ss << ",";
				else
					ss << " ) ";
			}
		}

		if(m_StartDate.m_dt > 0 && m_EndDate.m_dt > 0)
		{
			ss << " and a.report_date between ";
			CString str = m_StartDate.Format("%Y-%m-%d");
			ss << "\'" << str.GetBuffer() << "\' and ";
			str = m_EndDate.Format("%Y-%m-%d");
			ss << "\'" << str.GetBuffer() << "\'";
		}
		
		/* group by �Ӿ� */
		ss << " group by  ";
		if(m_vec_csrc_gate_code.size()>0)
		{
			ss << " b.csrc_gate_industry_name , b.csrc_gate_industry_code, ";
		}
		if(m_vec_csrc_big_code.size()>0)
		{
			ss << " b.csrc_big_industry_name , b.csrc_big_industry_code, ";
		}
		if(m_vec_reg_code.size()>0)
		{
			ss << " b.statsgov_area_name, b.statsgov_area_code, ";
		}
		ss << " a.report_date ";
		
		/* order by �Ӿ� */
		ss << " order by  ";
		if(m_vec_csrc_gate_code.size()>0)
		{
			ss << " b.csrc_gate_industry_name , b.csrc_gate_industry_code, ";
		}
		if(m_vec_csrc_big_code.size()>0)
		{
			ss << " b.csrc_big_industry_name , b.csrc_big_industry_code, ";
		}
		if(m_vec_reg_code.size()>0)
		{
			ss << " b.statsgov_area_name, b.statsgov_area_code, ";
		}
		ss << " a.report_date ";

		string test = ss.str();
		//test = Gbk2Utf8(test);

		row r;
		statement st = (sql.prepare << test,into(r)) ;
		st.execute();

		int cnt = 0;
		while (st.fetch())
		{
			try{

				if(title_code.empty())
				{
					if(m_vec_zb_code.size()>0)
					{
						if(m_vec_zb_code[0]=="colume_2")
						{
							title_code = m_vec_zb_code[0];
							title_name = "��Ӫҵ������";
						}
						else if(m_vec_zb_code[0]=="colume_9")
						{
							title_code = m_vec_zb_code[0];
							title_name = "��Ӫҵ��ɱ�";
						}
					}
				}
				
			}
			catch(...)
			{
				continue;
			}


			//	ʱ��Ϊ �������ꡱ
				
			sj_code.insert(sj_code.end(),r.get<string>("report_date"));

			string strZbCode = "";
			string strZbName = "";
			if(m_vec_csrc_gate_code.size()>0)
			{
				strZbCode += r.get<string>("csrc_gate_industry_code") + "_";
				strZbName += /*Utf8_GBK*/(r.get<string>("csrc_gate_industry_name")) + "_";
			}
			if(m_vec_csrc_big_code.size()>0)
			{
				strZbCode += r.get<string>("csrc_big_industry_code") + "_";
				strZbName += /*Utf8_GBK*/(r.get<string>("csrc_big_industry_name")) + "_";
			}
			if(m_vec_reg_code.size()>0)
			{
				strZbCode += r.get<string>("statsgov_area_code") + "_";
				strZbName += /*Utf8_GBK*/(r.get<string>("statsgov_area_name")) + "_";
			}
			zb_code.insert(zb_code.end(), strZbCode);
			zb_name.insert(zb_name.end(), strZbName);

			data.insert(data.end(),r.get<double>("colume_2")/(10000 * 10000));
			unit.insert(unit.end(), "��Ԫ");

			cnt++;
		}

		ss.str("");
		ss << "CCalcFinanceReport ͳ�����";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	catch(std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}

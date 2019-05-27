#include "StdAfx.h"
#include "Stock.h"
#include "MAConvergenceDivergence.h"

CMAConvergenceDivergence::CMAConvergenceDivergence(bool bAnalysisUsed)
:CAbstractIndex(bAnalysisUsed)
{
}

CMAConvergenceDivergence::~CMAConvergenceDivergence(void)
{
}


void CMAConvergenceDivergence::BeginCalculate()
{
	stringstream ss;

	try{
		ss << "create table if not exists daily_macd (code varchar(32), tradedate date, serial_num int, remark varchar(64), "
			<< " ema12 double, ema26 double, dif double, dea double,   "
			<< " price varchar(100), peak_date varchar(256), peak_dif varchar(256), "
			<< " peak_high varchar(256), peak_low varchar(256), peak_sign varchar(256), " 
			<< " cross_date varchar(256), cross_dif varchar(256), cross_sign varchar(256), "
			<< " PRIMARY KEY ( code, tradedate)) ";

		session sql(g_MysqlPool);
		string test = ss.str();
		sql << ss.str();

		
		ss.str("");
		ss << "select code , max_date, ";
		ss << "( select serial_num from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as serial_num,";

		ss << "( select ema12 from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as ema12,";
		ss << "( select ema26 from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as ema26,";
		ss << "( select dif   from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as dif,";
		ss << "( select dea   from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as dea, ";

		ss << "( select price from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as price,";
		ss << "( select peak_date  from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as peak_date,";
		ss << "( select peak_dif   from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as peak_dif,";
		ss << "( select peak_high  from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as peak_high,";
		ss << "( select peak_low   from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as peak_low,";
		ss << "( select peak_sign  from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as peak_sign, ";

		ss << "( select cross_date  from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as cross_date,";
		ss << "( select cross_dif   from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as cross_dif,";
		ss << "( select cross_sign  from daily_macd b where b.code = a.code and b.tradedate = a.max_date ) as cross_sign ";

		ss << "from ( select code, date_format(max(tradedate), '%Y-%m-%d') as max_date from daily_macd group by code ) a ";

		test = ss.str();

		row r;
		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();
		while(st.fetch())
		{
			//	ȡ���й�Ʊ�����Ľ����գ���Ϊ�����й�Ʊͣ��
			string tmp = r.get<string>("max_date");
			if(tmp!="0000-00-00" && tmp > m_strLatest)
			{
				m_strLatest = tmp;

				ss.str("");
				ss << IndexName() << ", m_strLatest = " << m_strLatest;
				LOG4CPLUS_DEBUG(g_logger, ss.str() );
			} 

			string strCode = r.get<string>("code");
			m_mapIndex[strCode].tradedate = tmp;
			m_mapIndex[strCode].serial_num = r.get<int>("serial_num");
			m_mapIndex[strCode].ema12 = r.get<double>("ema12");
			m_mapIndex[strCode].ema26 = r.get<double>("ema26");
			m_mapIndex[strCode].dif = r.get<double>("dif");
			m_mapIndex[strCode].dea = r.get<double>("dea");


			string peak = r.get<string>("price", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				
				m_mapIndex[strCode].close = String2Double(vecYield[0]);
				m_mapIndex[strCode].high = String2Double(vecYield[1]);
				m_mapIndex[strCode].low = String2Double(vecYield[2]);
			}

			//	dif �����벨��
			peak = r.get<string>("peak_date", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].peak_date[i] = vecYield[i];
				}
			}

			peak = r.get<string>("peak_dif", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].peak_dif[i] = String2Double(vecYield[i]);
				}
			}

			peak = r.get<string>("peak_high", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].peak_high[i] = String2Double(vecYield[i]);
				}
			}

			peak = r.get<string>("peak_low", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].peak_low[i] = String2Double(vecYield[i]);
				}
			}

			peak = r.get<string>("peak_sign", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].peak_sign[i] = atoi(vecYield[i].c_str());
				}
			}

			//	��ɢ����
			peak = r.get<string>("cross_date", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].cross_date[i] = vecYield[i];
				}
			}

			peak = r.get<string>("cross_dif", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].cross_dif[i] = String2Double(vecYield[i]);
				}
			}

			peak = r.get<string>("cross_sign", "");
			if(peak.empty()==false)
			{
				vector<string>	vecYield;
				splitString(peak, ",", vecYield);
				for(int i=0; i< vecYield.size(); i++)
				{
					m_mapIndex[strCode].cross_sign[i] = atoi(vecYield[i].c_str());
				}
			}
		}
	}
	catch(...)
	{

	}
}


void CMAConvergenceDivergence::BeginTradedate(CTechnicalAnalysis & ta, string strTradedate)
{

}

string	Cross(CMAConvergenceDivergenceData macd)
{
	string remark;
	if(macd.cross_sign[0]>0)
	{
		int k= 1;
		while(k<10)
		{
			if(macd.cross_sign[k]==0)
				break;
			if(macd.cross_dif[0] * macd.cross_dif[k] < 0)
				break;
			k ++;
		};

		if(k<10)
		{
			if(k%2==0)	k-=2;
			else	k -=1;

			k = (k/2) + 1;
			stringstream ss;
			if(macd.cross_dif[0]>0)
				ss << k << "��ˮ�Ͻ��";
			else if(macd.cross_dif[0]<0)
				ss << k << "��ˮ�½��";
			remark = ss.str();
		}
		else
		{
			if(macd.cross_dif[0]>0)
				remark = _T("���ˮ�Ͻ��");
			else if(macd.cross_dif[0]<0)
				remark = _T("���ˮ�½��");
		}
	}
	else if(macd.cross_sign[0]<0)
	{
		int k= 1;
		while(k<10)
		{
			if(macd.cross_sign[k]==0)
				break;
			if(macd.cross_dif[0] * macd.cross_dif[k] < 0)
				break;
			k ++;
		};

		if(k<10)
		{
			if(k%2==0)	k-=2;
			else	k -=1;

			k = (k/2) + 1;
			stringstream ss;
			if(macd.cross_dif[0]>0)
				ss << k << "��ˮ������";
			else if(macd.cross_dif[0]<0)
				ss << k << "��ˮ������";
			remark = ss.str();
		}
		else
		{
			if(macd.cross_dif[0]>0)
				remark = _T("���ˮ������");
			else if(macd.cross_dif[0]<0)
				remark = _T("���ˮ������");
		}
	}
	return remark;
}

//	������� �������롱  �� ���ױ��롱
string	Divergence(CMAConvergenceDivergenceData macd)
{
	string remark;
	if(macd.dif>0)
	{
		if(macd.peak_sign[0] >0)
		{
			//	Ѱ�Һ��ʵ�ǰһ������
			int k = 2;
			while(k<10)
			{
				if(macd.peak_sign[k-1] < 0 && macd.peak_dif[k-1] < 0)
				{
					// ֮ǰ�Ĳ��� Խ���� 0 �ᣬֹͣѰ��
					k = 10;
					break;
				}
				if(macd.peak_sign[k]>0 && abs(macd.peak_dif[k] - macd.peak_dif[0]) > macd.close * 0.002 )
					break;
				k +=2;
			};

			if(k<10)
			{
				if(macd.peak_high[0] > macd.peak_high[k] && macd.peak_dif[0] < macd.peak_dif[k])
				{
					remark = "������";
				}
			}
		}
	}
	if(macd.dif<0)
	{
		if( macd.peak_sign[0] <0 )
		{
			//	Ѱ�Һ��ʵ�ǰһ������
			int k = 2;
			while(k<10)
			{
				if(macd.peak_sign[k-1] > 0 && macd.peak_dif[k-1] > 0)
				{
					// ֮ǰ�Ĳ��� Խ���� 0 �ᣬֹͣѰ��
					k = 10;
					break;
				}
				if(macd.peak_sign[k]<0 && abs(macd.peak_dif[k] - macd.peak_dif[0]) > macd.close * 0.002 )
					break;
				k +=2;
			};

			if(k<10)
			{
				if(macd.peak_low[0] < macd.peak_low[k] && macd.peak_dif[0] > macd.peak_dif[k])
				{
					remark = "�ױ���";
				}
			}
		}
	}
	return remark;
}

void   CMAConvergenceDivergence::Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
												string strTradedate, string strCode, string strPlate)
{
	if(today.close<0)
	{
		// ����ͣ��
		if(m_mapIndex.count(strCode)>0)
		{
			m_mapIndex[strCode].remark ="";

			// ����ͣ��, ���� ת�����ֺ졢��ɷ���,ָ���������
			if(today.bonus_cash >0 || today.bonus_share >0 || today.reserve_to_common_share >0)
			{
				CMAConvergenceDivergenceData macd = m_mapIndex[strCode];
				//	�ȶ�֮ǰ�۸������� ��λ ����ǰ��Ȩ����
				macd.ema12 = RecoverPrice(macd.ema12, today);
				macd.ema26 = RecoverPrice(macd.ema26, today);
				macd.dea = RecoverPrice(macd.dea, today);

				m_mapIndex[strCode] = macd;
			}
		}
	
		return;
	}

	// ������� ÿ�ɵ����
	if(m_mapIndex.count(strCode)==0)
	{
		m_mapIndex[strCode].tradedate = strTradedate;
		m_mapIndex[strCode].serial_num = 1;
		m_mapIndex[strCode].ema12 = today.close;
		m_mapIndex[strCode].ema26 = today.close;
		m_mapIndex[strCode].dif = 0;
		m_mapIndex[strCode].dea = 0;

		m_mapIndex[strCode].close = today.close;
		m_mapIndex[strCode].high = today.high;
		m_mapIndex[strCode].low = today.low;
	}
	else
	{
		CMAConvergenceDivergenceData macd = m_mapIndex[strCode];

		//	�ȶ�֮ǰ�۸������� ��λ ����ǰ��Ȩ����
		macd.ema12 = RecoverPrice(macd.ema12, today);
		macd.ema26 = RecoverPrice(macd.ema26, today);
		macd.dea = RecoverPrice(macd.dea, today);

		CMAConvergenceDivergenceData macd_new = macd;
		macd_new.serial_num ++;
		macd_new.tradedate = strTradedate;
		macd_new.remark = "";

		macd_new.close = today.close;
		macd_new.high = today.high;
		macd_new.low = today.low;

		macd_new.ema12 = macd.ema12 * 11 /13 + today.close * 2 /13;
		macd_new.ema26 = macd.ema26 * 25 /27 + today.close * 2 /27;
		if(macd_new.serial_num < 26)
		{
			macd_new.dif = 0;
			macd_new.dea = 0;
		}
		else if(macd_new.serial_num == 26)
		{
			macd_new.dif = macd_new.ema12 - macd_new.ema26;
			macd_new.dea = macd_new.dif;
		}
		else
		{
			macd_new.dif = macd_new.ema12 - macd_new.ema26;
			macd_new.dea = macd.dea * 8 /10 + macd_new.dif * 2/10;

			//	���� ��� �� ������ж�
			int nCrossSign = 0;
			if(macd.dif < macd.dea && macd_new.dea < macd_new.dif )
			{
				nCrossSign = 1;
			}
			else if(macd.dif > macd.dea && macd_new.dea > macd_new.dif )
			{
				nCrossSign = -1;
			}
			if(nCrossSign!=0)
			{
				for(int i=8; i >=0; i-- )
				{
					macd_new.cross_date[i+1] = macd_new.cross_date[i];
					macd_new.cross_sign[i+1] = macd_new.cross_sign[i];
					macd_new.cross_dif[i+1] = macd_new.cross_dif[i];
				}
				macd_new.cross_sign[0] = nCrossSign;
				macd_new.cross_date[0] = macd_new.tradedate;
				macd_new.cross_dif[0] = macd_new.dif;

				if(macd_new.remark.empty()==false) macd_new.remark += ","; 
				macd_new.remark = Cross(macd_new);
			}

			//	dif ��Խ 0 �����
			if(macd.dif > 0 and macd_new.dif < 0)
			{
				if(macd_new.remark.empty()==false) macd_new.remark += ","; 
				macd_new.remark += _T("dif�´�0��");
			}
			else if(macd.dif < 0 and macd_new.dif > 0)
			{
				if(macd_new.remark.empty()==false) macd_new.remark += ","; 
				macd_new.remark += _T("dif�ϴ�0��");
			}

			//	���з�ֵ ���жϣ���¼ǰ 10 ������Ͳ���
			if(macd_new.peak_sign[0] ==0 )
			{
				if(macd_new.dif > macd.dif)
				{
					//	���յ���Ϊ ����
					macd_new.peak_sign[0] = -1;
					macd_new.peak_date[0] = macd.tradedate;
					macd_new.peak_dif[0] = macd.dif;
					macd_new.peak_high[0] = macd.high;
					macd_new.peak_low[0] = macd.low;
				}
				else if(macd_new.dif < macd.dif)
				{
					//	���յ���Ϊ ����
					macd_new.peak_sign[0] = 1;
					macd_new.peak_date[0] = macd.tradedate;
					macd_new.peak_dif[0] = macd.dif;
					macd_new.peak_high[0] = macd.high;
					macd_new.peak_low[0] = macd.low;
				}
			}
			else if(macd_new.peak_sign[0] > 0)
			{
				// ֮ǰ�Ѿ��ҳ��� ����
				if(macd_new.dif > macd.dif)
				{
					//	����Ϊ �µĲ���
					for(int i=8; i >=0; i-- )
					{
						macd_new.peak_date[i+1] = macd_new.peak_date[i];
						macd_new.peak_sign[i+1] = macd_new.peak_sign[i];
						macd_new.peak_dif[i+1] = macd_new.peak_dif[i];
						macd_new.peak_high[i+1] = macd_new.peak_high[i];
						macd_new.peak_low[i+1] = macd_new.peak_low[i];
					}
					macd_new.peak_sign[0] = -1;
					macd_new.peak_date[0] = macd.tradedate;
					macd_new.peak_dif[0] = macd.dif;
					macd_new.peak_high[0] = macd.high;
					macd_new.peak_low[0] = macd.low;

					// macd_new.remark += _T(",dif �յ�����");
					if(macd_new.remark.empty()==false) macd_new.remark += ","; 
					macd_new.remark += Divergence(macd_new);
				}
			}
			else
			{
				// ֮ǰ�Ѿ��ҳ��� ����
				if(macd_new.dif < macd.dif  )
				{
					//	����Ϊ �µĲ���
					for(int i=8; i >=0; i-- )
					{
						macd_new.peak_date[i+1] = macd_new.peak_date[i];
						macd_new.peak_sign[i+1] = macd_new.peak_sign[i];
						macd_new.peak_dif[i+1] = macd_new.peak_dif[i];
						macd_new.peak_high[i+1] = macd_new.peak_high[i];
						macd_new.peak_low[i+1] = macd_new.peak_low[i];
					}
					macd_new.peak_sign[0] = 1;
					macd_new.peak_date[0] = macd.tradedate;
					macd_new.peak_dif[0] = macd.dif;
					macd_new.peak_high[0] = macd.high;
					macd_new.peak_low[0] = macd.low;

					//macd_new.remark += _T(",dif �յ�����");
					if(macd_new.remark.empty()==false) macd_new.remark += ","; 
					macd_new.remark += Divergence(macd_new);
				}
			}

			// �������������ж�
			if(macd_new.cross_sign[0]<0)
			{
				string remark ;
				/*	���ǰһ���ǽ�� ���뱾������ͬʱ��ˮ�� ���� ˮ�� */
				if(macd_new.cross_sign[1]>0 && macd_new.cross_dif[0] * macd_new.cross_dif[1]> 0)
				{
					if( (macd_new.dif < macd_new.cross_dif[1] && macd.dif >= macd_new.cross_dif[1]) 
						|| (macd_new.dif <= macd_new.cross_dif[1] && macd.dif > macd_new.cross_dif[1]) )
					{
						if(macd_new.dif < 0)
							remark += "ˮ�µ���ǰ�ν��";
						else 
							remark += "ˮ�ϵ���ǰ�ν��";
					}
				}

				if(macd_new.remark.empty()==false && remark.empty() == false) 
					macd_new.remark += ","; 
				macd_new.remark += remark;
			}
		
		}
		m_mapIndex[strCode] = macd_new;
	}

}

void CMAConvergenceDivergence::EndTradedate(CTechnicalAnalysis & ta, string strTradedate)
{

	stringstream ss;
	try
	{
		vector<string>  vecSqlStr;
		map<string, CMAConvergenceDivergenceData>::iterator it = m_mapIndex.begin();
		while(it!=m_mapIndex.end())
		{
			CMAConvergenceDivergenceData rsi = it->second;
			ss.str("");
			ss << "(\'" << it->first << "\' ,\'" << strTradedate << "\'"
				<< ", " << rsi.serial_num
				<< ", " << Double2String(rsi.ema12, "%.3f")
				<< ", " << Double2String(rsi.ema26, "%.3f")
				<< ", " << Double2String(rsi.dif, "%.3f")
				<< ", " << Double2String(rsi.dea, "%.3f")
				<< ", \'" << rsi.remark << "\'";

			ss << ",\'";
			ss << Double2String(rsi.close) << "," << Double2String(rsi.high) << "," << Double2String(rsi.low);
			ss << "\'";

			//	dif �����벨��
			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << rsi.peak_date[i];
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << Double2String(rsi.peak_dif[i], "%.3f");
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << Double2String(rsi.peak_high[i]);
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << Double2String(rsi.peak_low[i]);
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << rsi.peak_sign[i];
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			//	��ɢ����
			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << rsi.cross_date[i];
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << Double2String(rsi.cross_dif[i], "%.3f");
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ",\'";
			for(int i=0; i< 10; i++)
			{
				ss << rsi.cross_sign[i];
				if(i<9)
					ss << "," ;
			}
			ss << "\'";

			ss << ")";

			vecSqlStr.insert(vecSqlStr.end(), ss.str());
			it++;
		}

		//	������� ��ÿ�� 1000 ��
		session sql(g_MysqlPool);

		int nLoop = vecSqlStr.size()/1000;
		if(nLoop * 1000 < vecSqlStr.size())
			nLoop++;

		for(int k=0; k< nLoop; k++)
		{
			ss.str("");
			ss << "insert into daily_macd (code , tradedate, serial_num, ema12, ema26, dif, dea, remark, "
				<< " price, peak_date, peak_dif, peak_high, peak_low, peak_sign, "
				<< " cross_date, cross_dif, cross_sign "
				<< " ) values ";

			for(int i = k * 1000; i < (k+1) * 1000 && i <vecSqlStr.size(); i++)
			{
				ss << vecSqlStr[i];
				if( (i+1) != (k+1)*1000 && (i+1) != vecSqlStr.size() )
				{
					ss << ",";
				}
			}

			string test = ss.str();
			sql << ss.str();
		}

		if(nLoop > 0)
			((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateTable("daily_macd", strTradedate);
	}
	catch(...)
	{

	}
}

void CMAConvergenceDivergence::EndCalculate()
{
	
}

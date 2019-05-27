#include "StdAfx.h"
#include "Stock.h"
#include "HushenStockIndex.h"

CHushenStockIndex::CHushenStockIndex(bool bAnalysisUsed)
:CAbstractIndex(bAnalysisUsed)
{
}

CHushenStockIndex::~CHushenStockIndex()
{
}


void CHushenStockIndex::BeginCalculate()
{
	stringstream ss;


	try{
		ss << "create table if not exists daily_hushen_stock (code varchar(32), abbreviation VARCHAR(32), tradedate date,  "
			<< " circulating DECIMAL(15, 2), circulating_value DECIMAL(15, 2), repair_value DECIMAL(13, 2), change_rate DECIMAL(8,2), "
			<< " close DECIMAL(8, 2), close_index DECIMAL(8, 2), remark varchar(32), PRIMARY key( code, tradedate )) ";

		session sql(g_MysqlPool);
		string test = ss.str();
		sql << ss.str();


		ss.str("");
		ss << "select code , max_date, ";
		ss << "( select circulating from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as circulating,";
		ss << "( select circulating_value from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as circulating_value,";

		ss << "( select repair_value   from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as repair_value,";
		ss << "( select change_rate from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as change_rate,";
		ss << "( select close from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as close,";
		ss << "( select close_index from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as close_index,";
		ss << "( select remark from daily_hushen_stock b where b.code = a.code and b.tradedate = a.max_date ) as remark ";
		
		ss << "from ( select code, date_format(max(tradedate), '%Y-%m-%d') as max_date from daily_hushen_stock  group by code ) a ";

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
			string strRemark = r.get<string>("remark", "");
			if(strRemark.find("���д���")==string::npos)
			{
				m_mapIndex[strCode].tradedate = tmp;
				m_mapIndex[strCode].circulating = r.get<double>("circulating", 0);
				m_mapIndex[strCode].circulating_value = r.get<double>("circulating_value", 0);
				m_mapIndex[strCode].repair_value = r.get<double>("repair_value", 0);
				m_mapIndex[strCode].close_index = r.get<double>("close_index", 0);
				m_mapIndex[strCode].change_rate = r.get<double>("change_rate", 0);
				m_mapIndex[strCode].remark = strRemark;
			}
		}

		// ������ռ��㣬���ȡ����֮ǰ�� ��ͨ��ֵ
		if(m_mapIndex.size()==0)
		{
			ss.str("");
			ss << "select c.code, date_format(c.maxdate, '%Y-%m-%d') as maxdate, "
				<< "a_time_to_delisting, a_time_to_suspend, "
				<< "(select concat(close, '|', circulating_value) from NetEase_Trade_Daily b "
				<< " where c.code = b.code and b.TradeDate = c.maxdate) as close,"
				<< " (select  CONCAT(real_date,'|',AShares)  from capitalstructure b "
				<< " where b.code = c.Code and b.real_date <= c.maxdate  ORDER BY real_date desc limit 1) as capitalstructure"
				<< " from (select code,   (select max( b.TradeDate) "
				<< " from NetEase_Trade_Daily b where  b.TradeDate< \'"<< m_strLatest <<"\' "
				<< " and b.code = a.code and b.close > 0 ) as maxdate, "
				<< " date_format(a_time_to_delisting, '%Y-%m-%d') as a_time_to_delisting ,"
				<< " date_format(a_time_to_suspend, '%Y-%m-%d') as a_time_to_suspend "
				<< " from stockinfo a ) c ";  

			test = ss.str();

			st = (sql.prepare << ss.str(),into(r)) ;
			st.execute();
			while(st.fetch())
			{
				string strCode = Int2String(r.get<int>("code"), "%06d");
				string strTradedate = r.get<string>("maxdate", "");
				string a_time_to_delisting = r.get<string>("a_time_to_delisting", m_strLatest);
				string a_time_to_suspend = r.get<string>("a_time_to_suspend", m_strLatest);
				//	strTradedate ���ڣ�˵���Ѿ����п�ʼ����
				//	a_time_to_suspend �� a_time_to_delisting ����������˵��֮�� ����
				if(strTradedate.empty()==false && a_time_to_suspend >=m_strLatest && a_time_to_delisting >=m_strLatest)
				{
					m_mapIndex[strCode].tradedate = strTradedate;

					string capitalstructureStr = r.get<string>("capitalstructure", "");
					if(capitalstructureStr.empty()==false)
					{
						vector<string>	vecYield;
						splitString(capitalstructureStr, "|", vecYield);

						m_mapIndex[strCode].real_date = vecYield[0];
						m_mapIndex[strCode].circulating = String2Double(vecYield[1]);
					}

					string closeStr = r.get<string>("close", "");
					if(closeStr.empty()==false)
					{
						vector<string>	vecYield;
						splitString(closeStr, "|", vecYield);

						m_mapIndex[strCode].close = String2Double(vecYield[0]);
						m_mapIndex[strCode].close_index = m_mapIndex[strCode].close;
						m_mapIndex[strCode].circulating_value = String2Double(vecYield[1]);
						m_mapIndex[strCode].circulating = m_mapIndex[strCode].circulating_value/m_mapIndex[strCode].close;
					}

					/*m_mapIndex[strCode].close_index =  r.get<double>("close", 0);
					m_mapIndex[strCode].close =  r.get<double>("close", 0);
					m_mapIndex[strCode].circulating_value = m_mapIndex[strCode].circulating * m_mapIndex[strCode].close_index;*/		

					m_mapIndex[strCode].repair_value = 0;
					m_mapIndex[strCode].change_rate = 0;
					m_mapIndex[strCode].remark = "";

				}
			}


		}

		//////////////////////////////////////////////////////////////////////////
		// ��ȡ�Ѻ� �����Ϣ
		ss.str("");
		ss << "select Code, Name, Company_Number, Total_Volume, Total_Turnover, Parent_Code, Is_Stock"
			<< " from SouhuStockPlates order by Is_Stock, Parent_Code, Code " ;	/*order by Is_Stock, Parent_Code, Code*/

		test = ss.str();

		st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		while (st.fetch())
		{
			string strCode  = Int2String(r.get<int>("Code"), "%06d");
			string strName = /*Utf8_GBK*/(r.get<string>("Name", ""));
			string strParentCode = Int2String(r.get<int>("Parent_Code"),  "%06d");
			int	isStock = r.get<int>("Is_Stock");

			if(isStock)
			{
				//	��¼�ù������� ���а��
				m_mapIndex[strCode].vecParent.push_back(strParentCode);
			}
			else
			{
				m_mapPlate[strCode].is_stock = isStock;
				m_mapPlate[strCode].parent_code = strParentCode;
				m_mapPlate[strCode].code = strCode;
				m_mapPlate[strCode].name = strName;
			}
		}

		//	���ӡ���ָ֤���� �Ȱ��
		string strCode = Int2String(399102, "%06d");;
		m_mapPlate[strCode].is_stock = 0;
		m_mapPlate[strCode].parent_code = "";
		m_mapPlate[strCode].code = strCode;
		m_mapPlate[strCode].name = "��ҵ����ָ";

		strCode = Int2String(399101, "%06d");;
		m_mapPlate[strCode].is_stock = 0;
		m_mapPlate[strCode].parent_code = "";
		m_mapPlate[strCode].code = strCode;
		m_mapPlate[strCode].name = "��С����ָ";

		strCode = Int2String(399100, "%06d");;
		m_mapPlate[strCode].is_stock = 0;
		m_mapPlate[strCode].parent_code = "";
		m_mapPlate[strCode].code = strCode;
		m_mapPlate[strCode].name = "������ָ��";

		strCode = Int2String(1, "%06d");;
		m_mapPlate[strCode].is_stock = 0;
		m_mapPlate[strCode].parent_code = "";
		m_mapPlate[strCode].code = strCode;
		m_mapPlate[strCode].name = "��֤��ָ";

		//////////////////////////////////////////////////////////////////////////
		// ���ָ������
		ss.str("");
		ss << "create table if not exists daily_hushen_plate (code int, index_type varchar(32), name varchar(256), "
			<< "tradedate date, circulating_value DECIMAL(16,2), repair_value DECIMAL(14,2), division DECIMAL(11,2)," 
			<< "point DECIMAL(8,2), PRIMARY key( code,  tradedate )) ";

		test = ss.str();
		sql << ss.str();

		ss.str("");
		ss << "select code , max_date, ";
		ss << "( select repair_value from daily_hushen_plate b where b.code = a.code and b.tradedate = a.max_date ) as repair_value,";
		ss << "( select circulating_value from daily_hushen_plate b where b.code = a.code and b.tradedate = a.max_date ) as circulating_value,";
		ss << "( select division   from daily_hushen_plate b where b.code = a.code and b.tradedate = a.max_date ) as division,";
		ss << "( select point from daily_hushen_plate b where b.code = a.code and b.tradedate = a.max_date ) as point ";

		ss << "from ( select code, date_format(max(tradedate), '%Y-%m-%d') as max_date from daily_hushen_plate  group by code ) a ";

		test = ss.str();

		st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();
		while(st.fetch())
		{
			string strCode = r.get<string>("code");
			m_mapPlate[strCode].tradedate = r.get<string>("max_date");
			m_mapPlate[strCode].circulating_value = r.get<double>("circulating_value", 0);
			m_mapPlate[strCode].repair_value = r.get<double>("repair_value", 0);
			m_mapPlate[strCode].division = r.get<double>("division", 0);
			m_mapPlate[strCode].point = r.get<double>("point", 0);

		}

	}
	catch(...)
	{

	}
}


void CHushenStockIndex::BeginTradedate(CTechnicalAnalysis & ta, string strTradedate)
{
	map<string, CStockPlateData>::iterator it = m_mapPlate.begin();
	while(it!=m_mapPlate.end())
	{
		it->second.yesterday_circulating_value = it->second.circulating_value;
		it->second.repair_value = 0;
		it->second.circulating_value = 0;
		it++;
	}

}

void   CHushenStockIndex::Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
												string strTradedate, string strCode, string strPlate)
{

	if(strCode == "000968" && strTradedate == "2017-01-24")
	{
		int kkk = 1;
	}

	if(today.close<0)
	{
		// ����ͣ��
		if(m_mapIndex.count(strCode)>0 && m_mapIndex[strCode].tradedate.empty()==false)
		{
			m_mapIndex[strCode].remark ="ͣ��";

			// ��ͣ��ǰ���һ�������յ���ͨ��ֵ ��Ϊ���յ���ͨ��ֵ
			m_mapIndex[strCode].tradedate = strTradedate;
			m_mapIndex[strCode].repair_value = 0;
		}
	}
	else
	{
		// ������� ÿ�ɵ����
		if(m_mapIndex.count(strCode)==0 || m_mapIndex[strCode].tradedate.empty())
		{
			// �¹����� ���� �����������գ�����ָ������
			m_mapIndex[strCode].tradedate = strTradedate;
			m_mapIndex[strCode].close = today.close;
			m_mapIndex[strCode].close_index = today.close;
			m_mapIndex[strCode].remark = "����ָ��";
			m_mapIndex[strCode].real_date = today.real_date;
			m_mapIndex[strCode].circulating =  today.circulating_value/today.close;   //  today.circulating;

			double p_CirculatingValue =  today.circulating_value;  //today.circulating * today.close ;
			m_mapIndex[strCode].circulating_value = p_CirculatingValue;
			m_mapIndex[strCode].repair_value = p_CirculatingValue;  // ��ʼ����ָ���󣬲ſ�ʼ����ָ������
		}
		else
		{
			// ǰһ��������Ϊͣ�ƣ����ո����򣬼���ͣ������������ p_RepairValue
			// ǰһ��������Ϊ���������գ��������յ� p_RepairValue

			CHushenStockIndexData yester = m_mapIndex[strCode];

			m_mapIndex[strCode].tradedate = strTradedate;
			m_mapIndex[strCode].remark = "";
			m_mapIndex[strCode].close = today.close;
			m_mapIndex[strCode].close_index  = yester.close_index * (1 + today.change_rate/100);

			//	����δ������Ȩ����Ӧ�� p_prev_exit_right_price = yester.close 
			double p_prev_exit_right_price = today.close - today.change;
			//m_mapIndex[strCode].repair_value = (p_prev_exit_right_price * today.circulating)-(yester.close * yester.circulating);
			
			if( abs(p_prev_exit_right_price - yester.close) > 0.0001)
				m_mapIndex[strCode].remark = "���ܳ�Ȩ��";

			if(today.real_date != yester.real_date )
			{
				m_mapIndex[strCode].remark +=  today.change_reason_desc;
				//m_mapIndex[strCode].repair_value = (p_prev_exit_right_price * today.circulating)-(yester.close * yester.circulating); 
				double cirulating = today.circulating_value/today.close;
				m_mapIndex[strCode].repair_value =  (p_prev_exit_right_price * cirulating)-(yester.close * yester.circulating); 
			}
			else
				m_mapIndex[strCode].repair_value = 0; 

			m_mapIndex[strCode].real_date = today.real_date;
			m_mapIndex[strCode].circulating = today.circulating_value/today.close;  //today.circulating;
			m_mapIndex[strCode].circulating_value = today.circulating_value;  // today.circulating * today.close;
		}	
	}

	//	���д���
	if(m_mapIndex.count(strCode)>0 && today.is_exit_from_market)
	{
		m_mapIndex[strCode].remark += " ���д���";
		m_mapIndex[strCode].repair_value = -1 * m_mapIndex[strCode].circulating_value;
		m_mapIndex[strCode].circulating_value = 0;
	}
	
	//	������ָ��
	
	if(m_mapIndex.count(strCode)>0 && m_mapIndex[strCode].tradedate.empty()==false)
	{
		CHushenStockIndexData hsi = m_mapIndex[strCode];
		
		for(int i=0; i< hsi.vecParent.size(); i++)
		{
			m_mapPlate[hsi.vecParent[i]].repair_value += hsi.repair_value;
			m_mapPlate[hsi.vecParent[i]].circulating_value += hsi.circulating_value;
		}

		if(strCode>="300000" && strCode<"399999")
		{
			m_mapPlate["399102"].repair_value += hsi.repair_value;
			m_mapPlate["399102"].circulating_value += hsi.circulating_value;
		}
		if(strCode>="002000" && strCode<"002999")
		{
			m_mapPlate["399101"].repair_value += hsi.repair_value;
			m_mapPlate["399101"].circulating_value += hsi.circulating_value;
		}
		if(strCode>="000001" && strCode<"600000")
		{
			m_mapPlate["399100"].repair_value += hsi.repair_value;
			m_mapPlate["399100"].circulating_value += hsi.circulating_value;
		}
		if(strCode>="600000")
		{
			m_mapPlate["000001"].repair_value += hsi.repair_value;
			m_mapPlate["000001"].circulating_value += hsi.circulating_value;
		}
	}

}

void CHushenStockIndex::EndTradedate(CTechnicalAnalysis & ta, string strTradedate)
{

	stringstream ss;

	//	���㱾�ո������ ָ����λ
	map<string, CStockPlateData>::iterator it = m_mapPlate.begin();
	while(it!=m_mapPlate.end())
	{
		if(it->second.tradedate.empty())
		{
			// ��ʼ��λΪ 1000 ��
			if(it->second.code == "000001")
				it->second.division = it->second.circulating_value/3296.26;

			else if(it->second.code == "399102")
				it->second.division = it->second.circulating_value/2987.44;

			else if(it->second.code == "399101")
				it->second.division = it->second.circulating_value/12374.21;

			else if(it->second.code == "399100")
				it->second.division = it->second.circulating_value/10000;

			else
				it->second.division = it->second.circulating_value/1000;

		}
		else
		{
			if(it->second.repair_value!=0)
			{
				/* ������Ҫ���� ָ���ĳ��� */
				it->second.division = (it->second.yesterday_circulating_value + it->second.repair_value)/it->second.point;
			}
		}

		/* ���㱾�յ���ָ��  */
		it->second.point = it->second.circulating_value/it->second.division;
		it->second.tradedate = strTradedate;
		it++;
	}

	try
	{
		//////////////////////////////////////////////////////////////////////////
		//	������ɵ� ��ͨ��ֵ����Ϣ

		vector<string>	vecExitMarket;
		vector<string>  vecSqlStr;
		map<string, CHushenStockIndexData>::iterator it = m_mapIndex.begin();
		while(it!=m_mapIndex.end())
		{
			CHushenStockIndexData rsi = it->second;
			if(rsi.tradedate.empty()==false)
			{
				ss.str("");
				ss << "(\'" << it->first << "\' ,\'" << strTradedate << "\'"
					<< ", " << Double2String(rsi.close, "%.2f")
					<< ", \'" << rsi.remark << "\'";
				ss <<  ", " << Double2String(rsi.circulating, "%.2f");
				ss <<  ", " << Double2String(rsi.circulating_value, "%.2f");
				ss <<  ", " << Double2String(rsi.repair_value, "%.2f");
				ss <<  ", " << Double2String(rsi.close_index, "%.2f");

				ss << ")";

				vecSqlStr.insert(vecSqlStr.end(), ss.str());
			}
			
			if(rsi.remark.find("���д���")!=string::npos)
			{
				vecExitMarket.push_back(it->first);
			}

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
			ss << "insert into daily_hushen_stock (code ,tradedate, close,  remark, "
				<< " circulating,  circulating_value,	 repair_value,  close_index ) values  "; 

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

		if(nLoop >0)
		{
			((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateTable("daily_hushen_stock", strTradedate);
		}

		//////////////////////////////////////////////////////////////////////////
		// ���д���
		for(int i=0; i<vecExitMarket.size(); i++)
		{
			m_mapIndex.erase(vecExitMarket[i]);
		}
		

		//////////////////////////////////////////////////////////////////////////
		// ���� ���ĵ�λ��Ϣ

		vecSqlStr.clear();
		map<string, CStockPlateData>::iterator it1 = m_mapPlate.begin();
		while(it1!=m_mapPlate.end())
		{
			CStockPlateData rsi = it1->second;
			if(rsi.tradedate.empty()==false && rsi.division >0)
			{
				ss.str("");
				ss << "(\'" << it1->first << "\' ,\'" << strTradedate << "\'"
					<< ", \'" << rsi.name << "\'";
				ss <<  ", " << Double2String(rsi.circulating_value, "%.2f");
				ss <<  ", " << Double2String(rsi.repair_value, "%.2f");
				ss <<  ", " << Double2String(rsi.division, "%.2f");
				ss <<  ", " << Double2String(rsi.point, "%.2f");

				ss << ")";

				vecSqlStr.insert(vecSqlStr.end(), ss.str());
			}

			it1++;
		}

		//	������� ��ÿ�� 1000 ��
		nLoop = vecSqlStr.size()/1000;
		if(nLoop * 1000 < vecSqlStr.size())
			nLoop++;

		for(int k=0; k< nLoop; k++)
		{
			ss.str("");
			ss << "insert into daily_hushen_plate (code ,tradedate,  name, "
				<< " circulating_value,  repair_value,	 division,  point ) values  "; 

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

		if(nLoop >0)
		{
			((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateTable("daily_hushen_plate", strTradedate);
		}
		
	}
	catch(...)
	{

	}
}

void CHushenStockIndex::EndCalculate()
{
	
}



void CHushenStockIndex::ExportFromDatabase(string strCode, double startTime, double endTime)
{
	stringstream ss;

	try
	{
		ss << "COnBalanceVolume ��ʼ�� MYSQL ��ȡ����......";
		//ss << "��" << m_nCode << "��";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << "select code, date_format(tradedate, '%Y-%m-%d') as tradedate, "
			<< " obv_index1, obv_index2, obv_index3  "
			<< " from daily_obv where code=\'" << strCode << "\' ";
		if(endTime > startTime)
		{
			COleDateTime start, end;
			start.m_dt = startTime;
			end.m_dt = endTime;
			ss << " and tradedate >= \'" << start.Format("%Y-%m-%d") << "\'";
			ss << " and tradedate <= \'" << end.Format("%Y-%m-%d") << "\'";
		}
		ss	<< " order by tradedate";

		row r;
		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		while (st.fetch())
		{
		/*	COnBalanceVolumeData  bbd;
			bbd.tradedate = r.get<string>("tradedate");

			m_vec_index.insert(m_vec_index.end(), bbd);*/
		}

		ss.str("");
		ss << "OK, COnBalanceVolume �� MYSQL ��ȡ�������.";
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
	}
}

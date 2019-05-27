#include "StdAfx.h"
#include "AbstractIndex.h"
#include "TechAnalysisEvent.h"

#include "SimulatedAccountMacd.h"

//////////////////////////////////////////////////////////////////////////

CSimulatedAccountMacd::CSimulatedAccountMacd(string strCode)
:CSimulatedAccount(strCode)
{
	m_lastRemark = "";
	m_trade_type = SHORT_TRADE;
}

CSimulatedAccountMacd::~CSimulatedAccountMacd(void)
{
}


void CSimulatedAccountMacd::ProccessEvent(string tradedate, map<string, CStockPlateData> & mapPlate)
{
	if(m_status.nShares >0)
	{
		if(m_Event.bonus_cash > 0)
			m_status.dbCapital +=  m_status.nShares/10 * m_Event.bonus_cash;
		if(m_Event.bonus_share > 0)
			m_status.nShares += m_Event.bonus_share  * m_status.nShares/10;
		if(m_Event.reserve_to_common_share > 0)
			m_status.nShares += m_Event.reserve_to_common_share  * m_status.nShares/10;

		if(m_Event.bonus_cash > 0 || m_Event.bonus_share > 0 || m_Event.reserve_to_common_share > 0)
		{
			CSimulatedAccountTradeDetail  satd = m_status;
			satd.remark = "ת�������";
			m_vec_detail.insert(m_vec_detail.end(), satd);
		}
	}

	if(m_Event.tradedate == "0000-00-00" || m_Event.close <= 0)
	{

		return;
	}

	m_status.remark = "";

	if(m_status.nShares >0)
	{
		//	���㱾�������� ����
		double earning = m_status.nShares * m_Event.close - m_status.dbCost;

		if(earning/m_status.dbCost < -0.1)
			m_status.remark = "��������, ֹ��";
	}

	m_status.remark = "";


	do{
		if(m_status.remark.empty() == false)
			break;

		//////////////////////////////////////////////////////////////////////////
		//	������������ 
		string desc_plate = "";
		for(int i=0; i<vecParent.size(); i++)
		{
			if(mapPlate.count(vecParent[i])>0)
			{
				CStockPlateData  spd = mapPlate[vecParent[i]];
				

			}
		}


		//////////////////////////////////////////////////////////////////////////
		//	�����¼��Ľ��� 

		// ��¼ MA ϵͳ��ǰ�ĳ�����״̬
		if(m_Event.ma.empty()==false)		m_status.desc_ma = m_Event.ma;


		if(m_Event.macd.empty() /*&& m_Event.dmi.empty() */
			&& m_Event.candlesticks.empty() /*&& m_Event.boll.empty() */
			/*&& m_Event.ma.empty()*/ && m_Event.obv.empty())
			break;

		if(m_Event.macd.empty()==false 
			&& (m_Event.macd.find("����")!=string::npos
			|| m_Event.macd.find("��")!=string::npos))		
		{
			m_status.desc_macd = m_Event.macd;
		}
		// if(m_Event.dmi.empty()==false)		m_status.desc_dmi = m_Event.dmi;
		//if(m_Event.kdj.empty()==false)		m_status.desc_kdj = m_Event.kdj;
		if(m_Event.candlesticks.empty()==false)		m_status.desc_k = m_Event.candlesticks;
		// if(m_Event.ma.empty()==false)		m_status.desc_ma = m_Event.ma;
		if(m_Event.obv.empty()==false)		m_status.desc_obv = m_Event.obv;


		//////////////////////////////////////////////////////////////////////////
		//	ÿ��������������
		double width = 4 * m_Event.standard / m_Event.middle;

		
		if(m_trade_type == SHORT_TRADE)
		{
			// �����ź�
			if(m_Event.macd.find("ˮ�Ͻ��")!=string::npos)
			{
				/*if(m_Event.macd.find("1��ˮ�Ͻ��")!=string::npos||
					m_Event.macd.find("2��ˮ�Ͻ��")!=string::npos)
				{
					m_status.remark = "��������";
				}
				else
				{
					if(m_Event.dif < m_Event.close * 0.05 )
						m_status.remark = "��������";
					else
						m_status.remark = "dif���ڸ�λ���ֱҹ���";
				}*/

				if( m_Event.k_value < 80)
				{
					m_status.remark = "��������";
				}
				else
					m_status.remark = "KDJ���򣬳ֱҹ���";

				if(m_status.remark.find("��������")!=string::npos )
				{
					/*if(m_Event.change_rate>9.00)
					{
						m_status.remark = "������Ƿ�����ֹͣ����";
					}*/
				}
				
			}

			if(m_Event.macd.find("ˮ�½��")!=string::npos ||
				m_Event.macd.find("�ױ���")!=string::npos )
			{

				/*if(abs(m_Event.dif) < m_Event.close * 0.05 )
				{
					m_status.remark = "��������";
					
				}
				else
					m_status.remark = "dif����0���½�Զ�����ֱҹ���";*/

				if( m_Event.k_value < 80)
				{
					m_status.remark = "��������";
				}
				else
					m_status.remark = "KDJ���򣬳ֱҹ���";

				
			}

			//	�����ź�
			if( m_Event.macd.find("������")!=string::npos)
			{
				m_status.remark = "��������";
			}

			if(m_Event.macd.find("ˮ�ϵ���ǰ�ν��")!=string::npos)
			{
				m_status.remark = "��������";
			}

			if(m_Event.macd.find("ˮ�µ���ǰ�ν��")!=string::npos)
			{
				m_status.remark = "��������";
			}

			if(m_Event.macd.find("dif�´�0��")!=string::npos)
			{
				//m_status.remark = "��������";
				/*if(m_Event.ma.find("���ڶ�ͷ")==string::npos)
					m_status.remark = "��������";
				else
					m_status.remark = "MA�����, �ֹɵȴ�";*/
			}
		}
		else
		{
			//	�����ź�
			if(m_Event.macd.find("dif�ϴ�0��")!=string::npos)
			{
				if(m_Event.ma.find("���ڶ�ͷ")!=string::npos)
					m_status.remark = "��������";
				else
					m_status.remark = "MA�����, �ֱҹ���";
			}

			//	�����ź�
			if(m_Event.macd.find("dif�´�0��")!=string::npos)
			{
				if(m_Event.ma.find("���ڶ�ͷ")==string::npos)
					m_status.remark = "��������";
				else
					m_status.remark = "MA�����, �ֹɵȴ�";
			}
		}

		if(m_status.remark.find("��������")!=string::npos )
		{
			
			
		}

		if(m_status.remark.find("��������")!=string::npos 
			&& (m_Event.dynamic_pe > 50 || m_Event.dynamic_pe <=0))
		{
			m_status.remark = "PE����ֹͣ����";
		}

		if(m_Event.candlesticks.find("���д���ͼ")!=string::npos
			||m_Event.candlesticks.find("Ĺ��")!=string::npos
			||m_Event.candlesticks.find("��ͷ�ƽ�������")!=string::npos
			||m_Event.candlesticks.find("����")!=string::npos)
		{
			m_status.remark = "��������, " + m_Event.candlesticks;

			m_status.desc_macd = "";
			m_status.desc_dmi = "";
			m_status.desc_kdj = "";
		}
		
		if(m_Event.obv.find("�ɼ۷������")!=string::npos)
		{
			m_status.remark = "��������, �ɼ۷������";

			m_status.desc_macd = "";
			m_status.desc_dmi = "";
			m_status.desc_kdj = "";
		}

		if(m_status.remark.find("��������")!=string::npos )
		{
			for(int i=0; i<vecParent.size(); i++)
			{
				if(mapPlate.count(vecParent[i])>0)
				{
					CStockPlateData  spd = mapPlate[vecParent[i]];

					stringstream ss;
					ss << "[" << spd.name << "] ";
					
					if(spd.dif>0)	ss << "ˮ��";
					else			
					{
						ss << "ˮ��";
					}

					if(spd.dif> spd.dea)	ss << "�ѽ��";
					if(spd.dif < spd.dea)	ss << "������";
					
					if(i< vecParent.size() -1)	ss << ",";

					m_status.remark += ss.str();
				}
			}

		}


		//	�����ξ������ϴβ�ͬ�����¼���
		if( m_status.remark.empty()==false && m_lastRemark != m_status.remark)
		{
			m_lastRemark = m_status.remark;
		}
	

		m_status.desc_k = "";		//	��ָ��ĳ������岻��
		m_status.desc_obv = "";
	}while(0);

	//////////////////////////////////////////////////////////////////////////
	//	���˻�ʵ�� ��������

	double  close = m_Event.close ;

	if(m_status.remark.find("��������")!=string::npos)
	{
		int nShare =  (m_status.dbCapital/close)/100;
		if(nShare * 100 * close > m_status.dbCapital)
			nShare--;


		if(nShare > 0)
		{
			stringstream ss;
			nShare = nShare * 100;

			//	����ת��
			m_status.nShares += nShare ;
			m_status.dbCapital -=  nShare * close;
			double dbTotal = m_status.nShares * close + m_status.dbCapital;

			ss << "����" << (nShare) << "�� ";
			ss << ", ÿ�� " << Double2String(close)  << "Ԫ";
			ss << "�� ���ʲ�Ϊ " << Double2String(dbTotal) << "Ԫ";

			if(dbTotal> 10 * 10000)
				ss << ", earning ��";
			else if(dbTotal< 10 * 10000)
				ss << ", loss ��";
			m_status.action = ss.str();

			//	��¼����ɱ�
			m_status.dbCost += nShare * close;
			m_status.dbLossEarning = 0;

		}
		else
			m_status.action = "";

	}
	else if(m_status.remark.find("��������")!=string::npos)
	{
		if(m_status.nShares > 0)
		{
			stringstream ss;
			m_status.dbCapital  += (m_status.nShares  * close);

			ss << "����" << m_status.nShares  << "�� ";
			ss << ", ÿ�� " << Double2String(close) << "Ԫ";
			ss << "�� ���ʲ�Ϊ " << Double2String(m_status.dbCapital) << "Ԫ";

			if(m_status.dbCapital> 10 * 10000)
				ss << ", earning ��";
			else if(m_status.dbCapital< 10 * 10000)
				ss << ", loss ��";

			m_status.action = ss.str();

			//	���㱾�������� ����
			double earning = m_status.nShares * close - m_status.dbCost;

			m_status.dbLossEarning = earning/m_status.dbCost;
			m_status.dbCost = 0;
			m_status.nShares = 0;
		}
		else
			m_status.action = "";

	}
	else
	{
		m_status.action = "";

	}

	//	�����յ� ״̬�仯���б���
	if(m_status.remark.empty()==false)
		m_vec_detail.insert(m_vec_detail.end(), m_status);
	

	//////////////////////////////////////////////////////////////////////////
	//	��¼�������ݣ��Ա�����ʹ��
	m_Event_Of_Yesterday = m_Event;

	//	��־����������
	m_Event.tradedate = "0000-00-00";

}


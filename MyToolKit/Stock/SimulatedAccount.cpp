#include "StdAfx.h"
#include "AbstractIndex.h"
#include "TechAnalysisEvent.h"

#include "SimulatedAccount.h"

//////////////////////////////////////////////////////////////////////////
//  
//C++ʵ����һά��ɢ���ݼ�ֵ�����塢���ȣ�  
//  
//���������飬�����С  

void findPeaks(vector<double> num, vector<int> & indMax, vector<int> & indMin)  
{  
    vector<int> sign;  
    for(int i = 1;i<num.size();i++)  
    {  
        /*����ֵ��� 
		 *С��0����-1 
         *����0����1 
         *����0����0 
         */  
        int diff = num[i] - num[i-1];  
       if(diff>0)  
        {  
            sign.push_back(1);  
       }  
       else if(diff<0)  
        {  
            sign.push_back(-1);  
        }  
        else  
        {  
            sign.push_back(0);  
        }  
    }  
    //�ٶ�sign����λ����  
    //���漫��ֵ�ͼ�Сֵ��λ��  
  
   for(int j = 1;j<sign.size();j++)  
    {  
        int diff = sign[j]-sign[j-1];  
        if(diff<0)  
        {  
            indMax.push_back(j);  
        }  
        else if(diff>0)  
        {  
            indMin.push_back(j);  
        }  
    }  
}  



//////////////////////////////////////////////////////////////////////////

CSimulatedAccount::CSimulatedAccount(string strCode)
{
	m_status.Reset();

	m_strCode = strCode;
	m_status.dbCapital = 10 * 10000;	//	��ʼΪ 10 ��Ԫ
	m_status.nShares = 0;				//	��ʼΪ 0 ��

	m_status.trend_flag = "unknown";
	m_status.trend_boll = "unknown";
	m_status.trend_close = 0;

	// m_status.obv_accum = 0;
	m_bUpdated = false;
}

CSimulatedAccount::~CSimulatedAccount(void)
{
}

void CSimulatedAccount::SetLastStatus(CSimulatedAccountTradeDetail satd)
{
	m_status = satd;
}

void CSimulatedAccount::PostEvent(CTechAnalysisEventData event)
{
	m_Event = event;
}

void CSimulatedAccount::ProccessEvent(string tradedate,  map<string, CStockPlateData> & mapPlate)
{
	if(m_Event.tradedate == "0000-00-00")
	{
		if(tradedate> m_time_to_market && m_time_to_market!="0000-00-00")
		{
			stringstream ss;
			ss << "[" << m_strCode << "] Error�� ProccessEvent ����������";
			// LOG4CPLUS_DEBUG(g_logger, ss.str() );
		}
		return;
	}

	bool	bExitFromSellOrBuy = false;

	//////////////////////////////////////////////////////////////////////////
	//	�����¼��Ľ��� 

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

	if(m_status.trend_flag != "range" && m_Event.boll.find(_T("����"))!=string::npos)
	{
		//m_status.Reset();
		m_status.trend_flag = "range";
		m_status.trend_boll = "unknown";
		m_status.boll_channel_num = 0;

		//close = event.close;

		CSimulatedAccountTradeDetail  satd = m_status;
		satd.remark = m_Event.boll;
		satd.action = "";
		m_vec_detail.insert(m_vec_detail.end(), satd);

	}
	else if(m_Event.boll.find(_T("�˳�"))!=string::npos)
	{
		bExitFromSellOrBuy = true;
	}

	if(m_Event.macd.empty()==false )
	{
		m_status.desc_macd = m_Event.macd;
	}
	if(m_Event.kdj.empty()==false )
	{
		m_status.desc_kdj = m_Event.kdj;
	}
	if(m_Event.dmi.empty()==false )
	{
		m_status.desc_dmi = m_Event.dmi;
	}
	
	if(m_Event.candlesticks.empty()==false )
	{
		m_status.desc_k = m_Event.candlesticks;
	}

	//	��¼����boll ͨ��������
	if(m_status.trend_flag=="range")
	{
		m_status.boll_channel_num++;
	}

	//////////////////////////////////////////////////////////////////////////
	//	ÿ��������������
	m_status.remark = "";

	if(tradedate == "2016-09-26" && m_strCode =="603555" )
	{
		int k = 1;
	}
	
	double close = m_Event.close;
	int nScore = 0;
	if(m_status.desc_dmi.find(_T("���ϣ�up������"))!=string::npos || m_status.desc_dmi.find(_T("���ƽ������"))!=string::npos )
		nScore ++;
	else if(m_status.desc_dmi.find(_T("���£�down������"))!=string::npos || m_status.desc_dmi.find(_T("������������"))!=string::npos ) 
		nScore --;

	if(m_status.desc_macd.find(_T("���"))!=string::npos)
		nScore ++;
	else if(m_status.desc_macd.find(_T("����"))!=string::npos)
		nScore --;

	if(m_status.desc_k.find(_T("��ͷ�ƽ�������"))!=string::npos)
		nScore ++;
	else if(m_status.desc_k.find(_T("��ͷ�ƽ�������"))!=string::npos)
		nScore --;

	if(nScore >=2)
	{
		if(m_status.trend_flag=="unknown")
		{

		}
		else if(m_status.trend_flag=="down")
		{
			//	��ǰ�ж�Ϊ DOWN ����
			if(close > m_status.trend_close)
			{
				//	��ǰ���� �ж�ʧ��
				// m_status.remark = "��������";

				m_status.trend_flag = "unknown";
				m_status.trend_boll = "unknown";
			}
		}
		else if(m_status.trend_flag=="range" )
		{
			if(m_Event.standard > m_Event_Of_Yesterday.standard 
				&& (4 * m_Event.standard / m_Event.middle) > 0.085
				&& (4 * m_Event.standard / m_Event.middle) < 0.095
				&& m_Event.dynamic_pe < 100
				&& m_status.boll_channel_num > 10)
			{
				if( m_Event.ma5 >= m_Event.ma10 &&  m_Event.ma10 >= m_Event.ma20)
				{
					m_status.remark = "��������";
					m_status.trend_boll = "up";
				}
				else
				{
					m_status.remark = "���߲���꣬�ֱҹ���";
				}
			}
			else
			{
				if(m_Event.standard <= m_Event_Of_Yesterday.standard)
					m_status.remark = "BOLL ������С���ֱҹ���";
				else if((4 * m_Event.standard / m_Event.middle) <= 0.085)
					m_status.remark = "BOLL С�� 8.5% ���ֱҹ���";
				else if((4 * m_Event.standard / m_Event.middle) >= 0.095)
					m_status.remark = "BOLL ���� 9.5% ���ֱҹ���";
				else if( m_Event.dynamic_pe >= 100)
					m_status.remark = "BOLL ��̬ PE > 100 ���ֱҹ���";
				else
					m_status.remark = "BOLL ͨ������С�� 10 ���ֱҹ���";
			}
		}
	}
	else if(nScore <=-2)
	{
		if(m_status.trend_flag=="unknown")
		{

		}
		else if(m_status.trend_flag=="up")
		{
			//	��ǰ�ж�Ϊ UP ����
			if( m_Event.ma5 < m_Event.ma10)
			{
				//	��ǰ�ж�ʧ��
				m_status.remark = "��������, ��ǰ�ж�ʧ��";

				m_status.trend_flag = "unknown";
				m_status.trend_boll = "unknown";
			}
			else
			{
				m_status.remark = "���߲���꣬�ֹɵȴ�";
			}
		}
		else if(m_status.trend_flag=="range")
		{
			if(m_Event.standard > m_Event_Of_Yesterday.standard 
				&& (4 * m_Event.standard / m_Event.middle) > 0.085
				&& (4 * m_Event.standard / m_Event.middle) < 0.095
				&& m_status.boll_channel_num > 10)
			{
				if( m_Event.ma5 <= m_Event.ma10 && m_Event.ma10 <= m_Event.ma20)
				{
					m_status.remark = "��������";
					m_status.trend_boll = "down";
				}
				else
				{
					m_status.remark = "���߲���꣬�ֹɵȴ�";
				}
			}
			else
			{
				if(m_Event.standard <= m_Event_Of_Yesterday.standard)
					m_status.remark = "BOLL ������С���ֹɵȴ�";
				else if((4 * m_Event.standard / m_Event.middle) <= 0.085)
					m_status.remark = "BOLL С�� 8.5% ���ֹɵȴ�";
				else if((4 * m_Event.standard / m_Event.middle) >= 0.095)
					m_status.remark = "BOLL ���� 9.5% ���ֱҹ���";
				else
					m_status.remark = "BOLL ͨ������С�� 10 ���ֹɵȴ�";
				
			}
		}
	}

	if(bExitFromSellOrBuy)
	{		
		if(m_status.trend_boll=="unknown")
			m_status.remark = "��������, δ�ó�����";
		
	}
	

	//////////////////////////////////////////////////////////////////////////
	//	���˻�ʵ�� ��������
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

	if(bExitFromSellOrBuy)
	{
		//m_status.Reset();
		if(m_status.trend_flag=="range")
		{
			m_status.trend_flag = m_status.trend_boll;
			m_status.trend_close = close;
			m_status.trend_ma5 = m_Event.ma5;
			m_status.trend_ma10 = m_Event.ma10;
			m_status.trend_ma20 = m_Event.ma20;
		}
		else
		{
			stringstream ss;
			ss << "[" << m_strCode << "] BOLL ָ�� Error";
			LOG4CPLUS_DEBUG(g_logger, ss.str() );
		}

		CSimulatedAccountTradeDetail  satd = m_status;
		satd.remark = "====> �˳���������ʱ��";
		satd.action = "";
		m_vec_detail.insert(m_vec_detail.end(), satd);
	}

	m_status.desc_k = "";		//	��ָ��ĳ������岻��

	//////////////////////////////////////////////////////////////////////////
	//	��¼�������ݣ��Ա�����ʹ��
	m_Event_Of_Yesterday = m_Event;

	//	��־����������
	m_Event.tradedate = "0000-00-00";

}


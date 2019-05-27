#include "StdAfx.h"
#include "Stock.h"
#include "CandlesticksJapan.h"

string RecognizeCandle(double high, double low, double open, double close)
{
	string strResult = "";
	if(high > low)
	{
		double percent = abs(open - close) /(high - low);
		double change_rate = (high - low)/low;
		double change_rate_1 = abs(close - open)/open;
		double position_low = (( open > close ? close : open) - low) / (high - low);
		double position_high = (( open > close ? open : close) - low) / (high - low);

		if( percent < 0.005 )
		{
			//	ʮ���� ϵ��
			if(position_low > 0.7)
				strResult = _T("����ʮ����");
			else if(position_low < 0.01)
				strResult = _T("Ĺ��ʮ����");
			else if(change_rate > 0.05)
				strResult = _T("����ʮ����");
			else
				strResult = _T("ʮ����");

		}
		else if( percent > 0.2 && percent < 0.3  && change_rate > 0.05)
		{
			if(position_low > 0.5)
				strResult = _T("����Ӱ��");
			else if(position_high < 0.5)
				strResult = _T("����Ӱ��");
			
			if( open > close)
				strResult += _T("��ʵ��");
			else
				strResult += _T("��ʵ��");

		}
		else if(percent > 0.3 && percent < 0.5 && change_rate > 0.05 )
		{
			if(position_low > 0.5)
				strResult = _T("������");
			else if(position_high < 0.5)
				strResult = _T("��������");
			
			if( open > close)
				strResult += _T("��ʵ��");
			else
				strResult += _T("��ʵ��");

		}
		else if(percent > 0.5 && percent < 0.8 && change_rate > 0.05)
		{

			if(position_low > 0.2)
				strResult = _T("������");
			else if(position_high < 0.8)
				strResult = _T("��������");

			if( open > close)
				strResult += _T("��ʵ��");
			else
				strResult += _T("��ʵ��");

		}
		else if(percent > 0.8 && change_rate > 0.07)
		{
			if( open > close)
				strResult = _T("������");
			else
				strResult = _T("������");
		}
		else
		{
			if( open > close)
				strResult = _T("��ʵ��");
			else
				strResult = _T("��ʵ��");
		}
		
	}
	else
	{
		//	һ�� ��ͣ ���� ��ͣ
		strResult = _T("һ�ְ�");
	}
	return strResult;
}


//////////////////////////////////////////////////////////////////////////

CCandlesticksJapan::CCandlesticksJapan(bool bAnalysisUsed)
:CAbstractIndex(bAnalysisUsed)
{
}

CCandlesticksJapan::~CCandlesticksJapan(void)
{
}


void CCandlesticksJapan::BeginCalculate()
{
	stringstream ss;

	try{
		ss << "create table if not exists daily_candlesticks (code varchar(32), tradedate date, "
			<< " picture varchar(64), remark varchar(64), "
			<< " close   double, open   double , low   double, high   double, "
			<< " close_1 double, open_1 double , low_1 double, high_1 double, "
			<< " close_2 double, open_2 double , low_2 double, high_2 double, "
			<< " close_3 double, open_3 double , low_3 double, high_3 double, "
						
			<< " PRIMARY KEY ( code, tradedate))";

		session sql(g_MysqlPool);
		string test = ss.str();
		sql << ss.str();

		ss.str("");
		ss << "select code , max_date, ";
		ss << "( select close from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as close,";
		ss << "( select open from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as open,";
		ss << "( select low from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as low,";
		ss << "( select high from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as high,";

		ss << "( select close_1 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as close_1,";
		ss << "( select open_1 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as open_1,";
		ss << "( select low_1 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as low_1,";
		ss << "( select high_1 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as high_1,";

		ss << "( select close_2 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as close_2,";
		ss << "( select open_2 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as open_2,";
		ss << "( select low_2 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as low_2,";
		ss << "( select high_2 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as high_2,";

		ss << "( select close_3 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as close_3,";
		ss << "( select open_3 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as open_3,";
		ss << "( select low_3 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as low_3,";
		ss << "( select high_3 from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as high_3 ";

		/*ss << "( select picture from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as picture,";
		ss << "( select tomorrow_forcast from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as tomorrow_forcast,";
		ss << "( select tomorrow_fact from daily_candlesticks b where b.code = a.code and b.tradedate = a.max_date ) as tomorrow_fact ";*/

		ss << "from ( select code, date_format(max(tradedate), '%Y-%m-%d') as max_date from daily_candlesticks  group by code ) a ";

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

			m_mapIndex[strCode].close = r.get<double>("close");
			m_mapIndex[strCode].low = r.get<double>("low");
			m_mapIndex[strCode].open = r.get<double>("open");
			m_mapIndex[strCode].high = r.get<double>("high");

			m_mapIndex[strCode].close_1 = r.get<double>("close_1");
			m_mapIndex[strCode].low_1 = r.get<double>("low_1");
			m_mapIndex[strCode].open_1 = r.get<double>("open_1");
			m_mapIndex[strCode].high_1 = r.get<double>("high_1");

			m_mapIndex[strCode].close_2 = r.get<double>("close_2");
			m_mapIndex[strCode].low_2 = r.get<double>("low_2");
			m_mapIndex[strCode].open_2 = r.get<double>("open_2");
			m_mapIndex[strCode].high_2 = r.get<double>("high_2");

			m_mapIndex[strCode].close_3 = r.get<double>("close_3");
			m_mapIndex[strCode].low_3 = r.get<double>("low_3");
			m_mapIndex[strCode].open_3 = r.get<double>("open_3");
			m_mapIndex[strCode].high_3 = r.get<double>("high_3");

		}
	}
	catch(...)
	{

	}
}


void CCandlesticksJapan::BeginTradedate(CTechnicalAnalysis & ta, string strTradedate)
{

}

void   CCandlesticksJapan::Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
												string strTradedate, string strCode, string strPlate)
{
	
	if(today.close<0)
	{
		// ����ͣ��
		if(m_mapIndex.count(strCode)>0)
		{
			m_mapIndex[strCode].remark ="";
			m_mapIndex[strCode].picture = "";

			// ����ͣ��, ���� ת�����ֺ졢��ɷ���,ָ���������
			if(today.bonus_cash >0 || today.bonus_share >0 || today.reserve_to_common_share >0)
			{
				CCandlesticksJapanData cjd = m_mapIndex[strCode];

				//	�ȶ�֮ǰ�۸���� ǰ��Ȩ
				cjd.high = RecoverPrice(cjd.high, today);
				cjd.low = RecoverPrice(cjd.low, today);
				cjd.open = RecoverPrice(cjd.open, today);
				cjd.close = RecoverPrice(cjd.close, today);

				cjd.high_1 = RecoverPrice(cjd.high_1, today);
				cjd.low_1 = RecoverPrice(cjd.low_1, today);
				cjd.open_1 = RecoverPrice(cjd.open_1, today);
				cjd.close_1 = RecoverPrice(cjd.close_1, today);

				cjd.high_2 = RecoverPrice(cjd.high_2, today);
				cjd.low_2 = RecoverPrice(cjd.low_2, today);
				cjd.open_2 = RecoverPrice(cjd.open_2, today);
				cjd.close_2 = RecoverPrice(cjd.close_2, today);

				cjd.high_3 = RecoverPrice(cjd.high_3, today);
				cjd.low_3 = RecoverPrice(cjd.low_3, today);
				cjd.open_3 = RecoverPrice(cjd.open_3, today);
				cjd.close_3 = RecoverPrice(cjd.close_3, today);

				m_mapIndex[strCode] = cjd;
			}
		}
		return;
	}

	// ������� ÿ�ɵ����
	if(m_mapIndex.count(strCode)==0)
	{
		m_mapIndex[strCode].close = today.close;
		m_mapIndex[strCode].open = today.open;
		m_mapIndex[strCode].low = today.low;
		m_mapIndex[strCode].high = today.high;
		m_mapIndex[strCode].picture = "";
	}
	else
	{
		CCandlesticksJapanData cjd = m_mapIndex[strCode];

		//	�ȶ�֮ǰ�۸���� ǰ��Ȩ
		cjd.high = RecoverPrice(cjd.high, today);
		cjd.low = RecoverPrice(cjd.low, today);
		cjd.open = RecoverPrice(cjd.open, today);
		cjd.close = RecoverPrice(cjd.close, today);

		cjd.high_1 = RecoverPrice(cjd.high_1, today);
		cjd.low_1 = RecoverPrice(cjd.low_1, today);
		cjd.open_1 = RecoverPrice(cjd.open_1, today);
		cjd.close_1 = RecoverPrice(cjd.close_1, today);

		cjd.high_2 = RecoverPrice(cjd.high_2, today);
		cjd.low_2 = RecoverPrice(cjd.low_2, today);
		cjd.open_2 = RecoverPrice(cjd.open_2, today);
		cjd.close_2 = RecoverPrice(cjd.close_2, today);

		cjd.high_3 = RecoverPrice(cjd.high_3, today);
		cjd.low_3 = RecoverPrice(cjd.low_3, today);
		cjd.open_3 = RecoverPrice(cjd.open_3, today);
		cjd.close_3 = RecoverPrice(cjd.close_3, today);

		if(cjd.close_3 > 0)
		{
			string picture = RecognizeCandle(today.high, today.low, today.open, today.close);
			string remark;

			string picture_1 = RecognizeCandle(cjd.high, cjd.low, cjd.open, cjd.close);
			string picture_2 = RecognizeCandle(cjd.high_1, cjd.low_1, cjd.open_1, cjd.close_1);
			string picture_3 = RecognizeCandle(cjd.high_2, cjd.low_2, cjd.open_2, cjd.close_2);
			string picture_4 = RecognizeCandle(cjd.high_3, cjd.low_3, cjd.open_3, cjd.close_3);

			//////////////////////////////////////////////////////////////////////////
			if(picture_4==_T("������") && picture==_T("������")  
				&& cjd.open < cjd.open_3 && cjd.close < cjd.open_3 && cjd.open > cjd.close_3 && cjd.close > cjd.close_3 
				&& cjd.open_1 < cjd.open_3 && cjd.close_1 < cjd.open_3 && cjd.open_1 > cjd.close_3 && cjd.close_1 > cjd.close_3
				&& cjd.open_2 < cjd.open_3 && cjd.close_2 < cjd.open_3 && cjd.open_2 > cjd.close_3 && cjd.close_2 > cjd.close_3 )
			{
				picture = _T("��������ͼ");
				
				remark = picture;
			}
			else if(picture_4==_T("������") && picture==_T("������")  
				&& cjd.open < cjd.open_3 && cjd.close < cjd.open_3 && cjd.open > cjd.close_3 && cjd.close > cjd.close_3 
				&& cjd.open_1 < cjd.open_3 && cjd.close_1 < cjd.open_3 && cjd.open_1 > cjd.close_3 && cjd.close_1 > cjd.close_3
				&& cjd.open_2 < cjd.open_3 && cjd.close_2 < cjd.open_3 && cjd.open_2 > cjd.close_3 && cjd.close_2 > cjd.close_3 )
			{
				picture =  _T("ţ������ͼ");
				
				remark = picture;
			}

			//////////////////////////////////////////////////////////////////////////
			else if(picture_2==_T("������") && picture.find(_T("��ʵ��"))!=string::npos
				&& cjd.open > cjd.close_1 && cjd.close > cjd.close_1
				&& today.close < cjd.close_1 && today.close > cjd.open_1 )
			{
				picture =  _T("��������ͼ");
				
				remark = picture;
			}
			else if(picture_2==_T("������") && picture_1.find(_T("ʮ����"))!=string::npos
				&& cjd.open > cjd.close_1 && cjd.close > cjd.close_1
				&& today.close < cjd.close_1 && today.close > cjd.open_1  )
			{
				picture =  _T("����ʮ������ͼ");
				
				remark = picture;
			}
			else if(picture_2==_T("������") && picture_1.find(_T("ʵ��"))!=string::npos
				&& cjd.open < cjd.close_1 && cjd.close < cjd.close_1
				&& today.close < cjd.open_1 && today.close > cjd.close_1  )
			{
				picture =  _T("ţ�г���ͼ");
				
				remark = picture;
			}
			else if(picture_2==_T("������") && picture_1.find(_T("ʮ����"))!=string::npos
				&& cjd.open < cjd.close_1 && cjd.close < cjd.close_1
				&& today.close < cjd.open_1 && today.close > cjd.close_1 )
			{
				picture =  _T("ţ��ʮ�ֳ���ͼ");
				
				remark = picture;
			}

			else if( (picture.find(_T("�������ͺ�ʵ��"))!=string::npos || picture.find(_T("������"))!=string::npos || picture.find(_T("�������ͺ�ʵ��"))!=string::npos)  
				&& (picture_1.find(_T("�������ͺ�ʵ��"))!=string::npos || picture_1.find(_T("������"))!=string::npos || picture_1.find(_T("�������ͺ�ʵ��"))!=string::npos) 
				&& (picture_2.find(_T("�������ͺ�ʵ��"))!=string::npos || picture_2.find(_T("������"))!=string::npos || picture_2.find(_T("�������ͺ�ʵ��"))!=string::npos) 
				&& today.open >= cjd.close && today.open <= cjd.open
				&& cjd.open >= cjd.close_1 && cjd.open <= cjd.open_1)
			{
				picture = _T("������ֻ����ѻ");
				
				remark = picture;
			}
			else if((picture.find(_T("�����Ͱ�ʵ��"))!=string::npos || picture.find(_T("������"))!=string::npos || picture.find(_T("�����Ͱ�ʵ��"))!=string::npos)  
				&& (picture_1.find(_T("�����Ͱ�ʵ��"))!=string::npos || picture_1.find(_T("������"))!=string::npos || picture_1.find(_T("�����Ͱ�ʵ��"))!=string::npos) 
				&& (picture_2.find(_T("�����Ͱ�ʵ��"))!=string::npos || picture_2.find(_T("������"))!=string::npos || picture_2.find(_T("�����Ͱ�ʵ��"))!=string::npos) 
				&& today.open > cjd.open && today.open < cjd.close
				&& cjd.open > cjd.open_1 && cjd.open < cjd.close_1)
			{
				picture = _T("ţ�к�����ͼ");

				remark = picture;
			}

			//////////////////////////////////////////////////////////////////////////
			else if(picture.find(_T("ʮ����"))!=string::npos && picture_1.find(_T("ʮ����"))!=string::npos)
			{
				picture =  _T("˫ʮ����");
			}
			
			else if(( picture == _T("������")) 
				&& picture_1.find(_T("��ʵ��"))!=string::npos
				&& today.close > cjd. high && today.open < cjd.low )
			{
				picture =  _T("ţ�д�ͷ�ƽ�������");

				remark = picture;
			}
			else if((picture == _T("������")) 
				&& picture_1.find(_T("��ʵ��"))!=string::npos
				&& today.open > cjd. high && today.close < cjd.low )
			{
				picture =  _T("���д�ͷ�ƽ�������");

				remark = picture;
			}

			else if((picture_1.find(_T("��ʵ��"))!=string::npos || picture_1 == _T("������")) 
				&& picture.find(_T("��ʵ��"))!=string::npos
				&& cjd.close > today. high && cjd.open < today.low )
			{
				picture =  _T("����������");

				remark = picture;
			}
			else if((picture_1.find(_T("��ʵ��"))!=string::npos || picture_1 == _T("������")) 
				&& picture.find(_T("��ʵ��"))!=string::npos
				&& cjd.open > today. high && cjd.close < today.low )
			{
				picture =  _T("ţ��������");

				remark = picture;
			}
			else if((picture_1.find(_T("��ʵ��"))!=string::npos || picture_1 == _T("������")) 
				&& picture.find(_T("ʮ����"))!=string::npos
				&& cjd.close > today. high && cjd.open < today.low )
			{
				picture =  _T("���������׽���ͼ");

				remark = picture;
			}
			else if((picture_1.find(_T("��ʵ��"))!=string::npos || picture_1 == _T("������")) && picture.find(_T("ʮ����"))!=string::npos
				&& cjd.open > today. high && cjd.close < today.low )
			{
				picture =  _T("ţ�������׽���ͼ");

				remark = picture;
			}

			else if((picture_1.find(_T("��ʵ��"))!=string::npos || picture_1 == _T("������")) 
				&& (picture.find(_T("��ʵ��"))!=string::npos ||  picture == _T("������") )
				&& cjd.open == today. open )
			{
				picture =  _T("���з���ͼ");

				remark = picture;
			}
			else if((picture_1.find(_T("��ʵ��"))!=string::npos || picture_1 == _T("������")) 
				&& (picture.find(_T("��ʵ��"))!=string::npos ||  picture == _T("������") )
				&& cjd.open == today. open )
			{
				picture =  _T("ţ�з���ͼ");

				remark = picture;
			}

			else if((picture.find(_T("�����ͺ�ʵ��"))!=string::npos || picture.find(_T("�����ͺ�ʵ��"))!=string::npos || picture == _T("������")) 
				&& (picture_1.find(_T("�����Ͱ�ʵ��"))!=string::npos || picture_1.find(_T("�����Ͱ�ʵ��"))!=string::npos||  picture_1 == _T("������") )
				&& cjd.high < today. low )
			{
				picture =  _T("���д���ͼ");

				remark = picture;
			}
			else if((picture_1.find(_T("�����ͺ�ʵ��"))!=string::npos || picture_1.find(_T("�����ͺ�ʵ��"))!=string::npos || picture_1 == _T("������")) 
				&& (picture.find(_T("�����Ͱ�ʵ��"))!=string::npos || picture.find(_T("�����Ͱ�ʵ��"))!=string::npos || picture == _T("������") )
				&& cjd.low > today.high )
			{
				picture =  _T("ţ�д���ͼ");

				remark = picture;
			}

			// ����ͼ��
			else if( picture_1 == _T("������") 
				&& (picture.find(_T("��ʵ��"))!=string::npos ||  picture == _T("������") )
				&& cjd.open < today. close && today.close < cjd.close )
			{
				picture =  _T("�������ƸǶ�ͼ");

				remark = picture;
			}
			else if( picture_1 == _T("������") 	&& picture == _T("������")
				&& cjd.low > today.open && (cjd.low + cjd.high)/2 < today.close )
			{
				picture =  _T("ţ�л�����ͼ");
			}
			else if( picture_1 == _T("������") 	&& picture.find(_T("��ʵ��"))!=string::npos
				&& today.close < cjd.low )
			{
				picture =  _T("���о���ͼ");

				remark = picture;
			}
			else if( picture == _T("Ĺ��ʮ����") )
			{
				remark = picture;
			}

			
			m_mapIndex[strCode].picture = picture;
			m_mapIndex[strCode].remark = remark;
		}
		else
		{
			m_mapIndex[strCode].picture = "";
		}

		m_mapIndex[strCode].close_3 = cjd.close_2;
		m_mapIndex[strCode].open_3 = cjd.open_2;
		m_mapIndex[strCode].low_3 = cjd.low_2;
		m_mapIndex[strCode].high_3 = cjd.high_2;

		m_mapIndex[strCode].close_2 = cjd.close_1;
		m_mapIndex[strCode].open_2 = cjd.open_1;
		m_mapIndex[strCode].low_2 = cjd.low_1;
		m_mapIndex[strCode].high_2 = cjd.high_1;

		m_mapIndex[strCode].close_1 = cjd.close;
		m_mapIndex[strCode].open_1 = cjd.open;
		m_mapIndex[strCode].low_1 = cjd.low;
		m_mapIndex[strCode].high_1 = cjd.high;

		m_mapIndex[strCode].close = today.close;
		m_mapIndex[strCode].open = today.open;
		m_mapIndex[strCode].low = today.low;
		m_mapIndex[strCode].high = today.high;
		
	}
	
}

void CCandlesticksJapan::EndTradedate(CTechnicalAnalysis & ta, string strTradedate)
{

	stringstream ss;
	try
	{
		session sql(g_MysqlPool);

		//	�������뱾�յ�����
		ss.str("");
		ss << "insert into daily_candlesticks (code , tradedate, picture, remark,  "
			<< "open, close , low, high, "
			<< "open_1, close_1 , low_1,  high_1, "
			<< "open_2, close_2 , low_2,  high_2, "
			<< "open_3, close_3 , low_3,  high_3  "
			<< " ) values ";

		map<string, CCandlesticksJapanData>::iterator it = m_mapIndex.begin();
		while(it!=m_mapIndex.end())
		{
			CCandlesticksJapanData rsi = it->second;
			ss << "(\'" << it->first << "\' ,\'" << strTradedate << "\'"
				<< ", \'" << rsi.picture << "\'"
				<< ", \'" << rsi.remark << "\'"

				<< ", " << Double2String(rsi.open)
				<< ", " << Double2String(rsi.close)
				<< ", " << Double2String(rsi.low)
				<< ", " << Double2String(rsi.high)
				
				<< ", " << Double2String(rsi.open_1)
				<< ", " << Double2String(rsi.close_1)
				<< ", " << Double2String(rsi.low_1)
				<< ", " << Double2String(rsi.high_1)

				<< ", " << Double2String(rsi.open_2)
				<< ", " << Double2String(rsi.close_2)
				<< ", " << Double2String(rsi.low_2)
				<< ", " << Double2String(rsi.high_2)

				<< ", " << Double2String(rsi.open_3)
				<< ", " << Double2String(rsi.close_3)
				<< ", " << Double2String(rsi.low_3)
				<< ", " << Double2String(rsi.high_3)
				
				<< ")";

			it++;
			if( it!=m_mapIndex.end())
				ss << ",";
		}

		string test = ss.str();
		sql << test;


		((CStockApp *)AfxGetApp())->m_StockDataLog.UpdateTable("daily_candlesticks", strTradedate);

		
	}
	catch(...)
	{

	}
}

void CCandlesticksJapan::EndCalculate()
{
	
}

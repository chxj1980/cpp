#pragma once

class CTechnicalAnalysis;


class CTechnicalAnalysisData
{
public:
	double  open;
	double	high;
	double	low;
	double	close;
	double	volume;
	double	change;
	double	change_rate;
	double	turnover;
	double	turnover_rate;

	double	circulating_value;
	double	lclose;

	//	��ͣ���С���������
	bool	is_exit_from_market;

	//	����Ϊ��Ȩ��ʱ�� ת������ɡ��ֺ������
	double	bonus_share;
	double	reserve_to_common_share;
	double	bonus_cash;

	//	�ɱ��ṹ
	double	circulating;
	string	change_reason_desc;
	string	real_date;

	//	��������
	string	a_time_to_market;

	CTechnicalAnalysisData()
	{
		close = -1;
		lclose = -1;

		bonus_cash = -1;
		reserve_to_common_share = -1;
		bonus_share = -1;

		circulating = 0;

		is_exit_from_market = false;
		change_reason_desc = "";

		a_time_to_market = "";
	}

};

class CAbstractIndex
{
public:
	CAbstractIndex(bool bAnalysisUsed);
	~CAbstractIndex(void);

	//	��ʼ����ָ�꣬��������ָ�꣬�������������ָ������
	virtual void   BeginCalculate() = 0;
	
	//	��ʼĳ�������յļ���
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate) = 0;

	//	
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate) = 0;

	//	����ĳ�������յļ���
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate) = 0;

	//	����ָ����㣬��������ɵ�ָ�걣�����ݿ�
	virtual void   EndCalculate() = 0;

	virtual string IndexName() = 0;

	//	ǰ��Ȩ�ۣ�����ǰ�ļ۸��� ת�����ֺ� ����ת��
	double  RecoverPrice(double price, CTechnicalAnalysisData tad, bool subCash = true);

	double  RecoverVolume(double volume, CTechnicalAnalysisData tad);

public:
	//	�ϴ�ָ������ ��ֹ������
	string	m_strLatest;

};

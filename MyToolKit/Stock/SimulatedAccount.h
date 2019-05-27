#pragma once


class CSimulatedAccountTradeDetail
{
public:
	string	trend_boll ;	//	���� boll խͨ���У�Ԥ�жϵ� ����
	string	trend_flag;		//	down ���£�  range ����  �� up ���� �� unknown δ֪

	int		boll_channel_num;		//	���� boll ͨ��������

	double	trend_close;	//  
	double	trend_ma5;		//	ͬ��
	double  trend_ma10;		//	ͬ��
	double	trend_ma20;		//	ͬ��


	double	dbCapital;		//	�˻��ʽ�
	int		nShares;		//	���йɷ�

	double	dbCost;			//	��¼���������ѳɱ�
	double	dbLossEarning;	//	��¼ÿ�������� ����

	string	desc_dmi;			
	string	desc_macd;
	string	desc_kdj;
	string	desc_k;
	string	desc_ma;
	string	desc_obv;

	//double	obv_accum;
	int		score;

	string	action;			//	������ ���� ���� ����
	string	remark;			//	����˵��

	void Reset()
	{
		desc_dmi = "";
		desc_kdj = "";
		desc_macd = "";
		desc_k = "";
		action = "";
		remark = "";

		score = 0;

		dbCost = 0;
		dbLossEarning = 0;
	}
};


class CSimulatedAccount 
{
public:
	CSimulatedAccount(string strCode);
	~CSimulatedAccount(void);

	void SetLastStatus(CSimulatedAccountTradeDetail satd);
	void PostEvent(CTechAnalysisEventData event);
	virtual void ProccessEvent(string tradedate, map<string, CStockPlateData> & mapPlate);

public:
	string	m_strCode;			//	��Ʊ����
	string	m_time_to_market;	//	
	bool	m_bUpdated;			//	�˻��Ƿ���״̬�ı�, �ı�����Ҫ�������ݿ�	

public:
	CTechAnalysisEventData			m_Event;		//	�����յ�������
	CTechAnalysisEventData			m_Event_Of_Yesterday;

	vector<CSimulatedAccountTradeDetail>	m_vec_detail;	//	�����¼�������ϸ

	CSimulatedAccountTradeDetail			m_status;		//	�˻���ǰ״̬

	vector<string>	vecParent;	//	������� ID
};

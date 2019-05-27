#pragma once

#define	OBV_SMOOTHING_DAY 12


class CHushenStockIndexData
{
public:
	string	tradedate;
	string	real_date;			//	��ͨ�ɱ䶯��
	double	circulating;		//	��ͨ����
	double	circulating_value;
	double	repair_value;
	double	change_rate;
	double	close_index;		/* �����յĸ�Ȩ�� */

	vector<string>	vecParent;	//	������� ID

	//	���շ������¼� 
	string	remark;
	double  close;

	CHushenStockIndexData()
	{
		tradedate = "";
		circulating_value = 0;
		repair_value = 0;
		change_rate = 0;
		close_index = 0;
		close = 0;
		circulating = 0;

		remark = "";
	}
};


class CHushenStockIndex : public CAbstractIndex
{
public:
	CHushenStockIndex(bool bAnalysisUsed = false);
	~CHushenStockIndex(void);

	virtual void   BeginCalculate();
	virtual void   BeginTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   Calculate(CTechnicalAnalysis & ta, CTechnicalAnalysisData & today, CTechnicalAnalysisData & yesterday,
		string strTradedate, string strCode, string strPlate);
	virtual void   EndTradedate(CTechnicalAnalysis & ta, string strTradedate);
	virtual void   EndCalculate();

	virtual string  IndexName(){  return "Hushen �����Ʊָ��ָ��"; }

	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);

	int TradedateNumber(string a_time_to_market, string strTradedate);

	//	key Ϊ��Ʊ����
	map<string, CHushenStockIndexData>		m_mapIndex;

	//	key Ϊ���ID
	map<string, CStockPlateData>			m_mapPlate;

	//	���� ExportFromDatabase �Ľ��, ���ս���������
	vector<CHushenStockIndexData>		m_vec_index;

	//	������н�����
	vector<string>			m_vecTradedate;

	//	������й�˾������
	map<string, string>		m_mapAbbreviation;

};

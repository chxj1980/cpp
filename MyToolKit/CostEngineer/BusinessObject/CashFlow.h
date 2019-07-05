#pragma once


/* �����£������ţ������ֽ������� */

class CCashFlow;

class CCashFlowObj
{
public:
	CCashFlowObj();

	~CCashFlowObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode);

	/* �����յ�֧������·� */
	int  EarliestPaymentTime();
	/* ���������·� */
	int	 LatestPaymentTime();
	/* ��ֵ�����㵽�����µ���ĩ���³� */
	double FutureValueOfPartitionedProject(double i);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CCashFlowObj>& cols, CCashFlow& parent);
	static bool Update(string menuCode, int nRow, vector<CCashFlowObj>& cols);
	static bool Delete(string menuCode, int nRow, vector<CCashFlowObj>& cols);

	
	CString m_name;				//  �ֲ���������
	int		m_building_start;	//	��ʼʱ�䣨�£��ܣ�
	int		m_building_duration;//	����
	double	m_building_cost;	//	�ֲ��������
	int		m_payment_interval;	//	֧������ - ��ÿ N ���½���һ��
	int		m_payment_lag;		//  ֧���ӳ�ʱ��
	int		m_payment_time;		//	0 �ڳ�֧���� 1 ��ĩ֧��
};


class CCashFlow
{
public:
	CCashFlow();
	~CCashFlow();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	/* �������̽�����·� */
	int	 LatestPaymentTime();
	/* �������̵���ֵ�����㵽�������̵Ľ����µ���ĩ */
	double FutureValueOfWholeProject();
	/* �������̵���ֵ */
	double PresentValueOfWholeProject();
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CCashFlow>& cols);
	static bool Update(string menuCode, int nRow, vector<CCashFlow>& cols);
	static bool Delete(string menuCode, int nRow, vector<CCashFlow>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CCashFlow>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;				//	
	double  m_interest_rate;	//	����
	
	vector<CCashFlowObj>	m_objs;	
};


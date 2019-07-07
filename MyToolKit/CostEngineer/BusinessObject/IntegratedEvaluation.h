#pragma once


/* �����£�����ʮ���ۺ��������� */

class CIntegratedEvaluation;

class CIntegratedEvaluationObj
{
public:
	CIntegratedEvaluationObj();

	~CIntegratedEvaluationObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode, CIntegratedEvaluation& parent);

	/* �����յ�֧������·� */
	int  EarliestPaymentTime();
	/* ���������·� */
	int	 LatestPaymentTime();
	/* ��ֵ�����㵽�����µ���ĩ���³� */
	double FutureValueOfPartitionedProject(double i);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CIntegratedEvaluationObj>& cols, CIntegratedEvaluation& parent);
	static bool Update(string menuCode, int nRow, vector<CIntegratedEvaluationObj>& cols, CIntegratedEvaluation& parent);
	static bool Delete(string menuCode, int nRow, vector<CIntegratedEvaluationObj>& cols);

	
	CString m_name;						//  ��������
	double  m_technique_score;			//  ������ - �÷�
	double	m_technique_building_plan;	//	������ - ʩ������	
	double	m_technique_duration;		//	������ - ����
	double	m_technique_quality;			//	������ - ����
	double	m_technique_manage;			//	������ - ��Ŀ�����
	double	m_technique_credit;			//  ������ - ��ҵ����
	double	m_technique_luban;			//  ������ - ³�๤�̽�
	double	m_technique_shengyou;		//  ������ - ʡ�Ź��̽�

	double	m_business_score;			//	����� - �÷�
	double	m_business_total_price;		//	����� - �ܼ�
	double	m_business_unit_price;		//	����� - ����

};


class CIntegratedEvaluation
{
public:
	CIntegratedEvaluation();
	~CIntegratedEvaluation();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	/* �������̽�����·� */
	int	 LatestPaymentTime();
	/* �������̵���ֵ�����㵽�������̵Ľ����µ���ĩ */
	double FutureValueOfWholeProject();
	/* �������̵���ֵ */
	double PresentValueOfWholeProject();
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CIntegratedEvaluation>& cols);
	static bool Update(string menuCode, int nRow, vector<CIntegratedEvaluation>& cols);
	static bool Delete(string menuCode, int nRow, vector<CIntegratedEvaluation>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CIntegratedEvaluation>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;				//	
	CString m_evaluation_method;	//	���귨
	
	vector<CIntegratedEvaluationObj>	m_objs;	
};


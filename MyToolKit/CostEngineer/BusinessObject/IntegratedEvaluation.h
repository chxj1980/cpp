#pragma once


/* �����£�����ʮ���ۺ��������� */

class CIntegratedEvaluation;

class CIntegratedEvaluationObj
{
public:
	CIntegratedEvaluationObj();

	~CIntegratedEvaluationObj();

	virtual void Serialize(CArchive& ar, double version);

	virtual bool CreateOrUpdate(string menuCode, CIntegratedEvaluation* parent);

	/* �����յ�֧������·� */
	int  EarliestPaymentTime();
	/* ���������·� */
	int	 LatestPaymentTime();
	/* ��ֵ�����㵽�����µ���ĩ���³� */
	double FutureValueOfPartitionedProject(double i);

	

	
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
	virtual ~CIntegratedEvaluation();


	virtual CIntegratedEvaluationObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual bool AddChild(string menuCode);
	virtual bool UpdateChild(string menuCode, int nRow);
	virtual bool DeleteChild(string menuCode, int nRow);
	
	static CIntegratedEvaluation* NewParent(CString name);
	static void Serialize(CArchive& ar, double version, CIntegratedEvaluation*  & p);
	static bool CreateOrUpdate(string strMenuCode, CIntegratedEvaluation* & p);
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CIntegratedEvaluation *>& cols);
	static bool Update(string menuCode, int nRow, vector<CIntegratedEvaluation *>& cols);
	static bool Delete(string menuCode, int nRow, vector<CIntegratedEvaluation *>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CIntegratedEvaluation *>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;				//	
	CString m_evaluation_method;	//	���귨
	
	vector<CIntegratedEvaluationObj*>	m_objs;	
};

class CIntegratedEvaluationEx10 : public CIntegratedEvaluation {
	virtual CIntegratedEvaluationObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
};

class CIntegratedEvaluationEx11 : public CIntegratedEvaluation {
	virtual CIntegratedEvaluationObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
};

class CIntegratedEvaluationEx12 : public CIntegratedEvaluation {
	virtual CIntegratedEvaluationObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
};

class CIntegratedEvaluationObjEx10 : public CIntegratedEvaluationObj {
	virtual bool CreateOrUpdate(string menuCode, CIntegratedEvaluation* parent);
};

class CIntegratedEvaluationObjEx11 : public CIntegratedEvaluationObj {
	virtual bool CreateOrUpdate(string menuCode, CIntegratedEvaluation* parent);
};

class CIntegratedEvaluationObjEx12 : public CIntegratedEvaluationObj {
	virtual bool CreateOrUpdate(string menuCode, CIntegratedEvaluation* parent);
};
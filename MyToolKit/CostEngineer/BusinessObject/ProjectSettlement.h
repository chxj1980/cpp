#pragma once


/* �����£�����һ�����̽��� */

class CProjectSettlement;

class CProjectSettlementObj
{
public:
	CProjectSettlementObj();

	~CProjectSettlementObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode, CProjectSettlement& parent);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CProjectSettlementObj>& cols, CProjectSettlement& parent);
	static bool Update(string menuCode, int nRow, vector<CProjectSettlementObj>& cols, CProjectSettlement& parent);
	static bool Delete(string menuCode, int nRow, vector<CProjectSettlementObj>& cols);

	
	CString	m_month;				//  �·�
	double	m_actual_workload;		//	ʵ����ɹ�����
	double	m_schedule_workload;	//	�ƻ���ɹ�����
	double	m_party_a_material;		//	�׹�����
};


class CProjectSettlement
{
public:
	CProjectSettlement();
	~CProjectSettlement();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	/* �������̽�����·� */
	int	 LatestPaymentTime();
	/* �������̵���ֵ�����㵽�������̵Ľ����µ���ĩ */
	double FutureValueOfWholeProject();
	/* �������̵���ֵ */
	double PresentValueOfWholeProject();
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlement>& cols);
	static bool Update(string menuCode, int nRow, vector<CProjectSettlement>& cols);
	static bool Delete(string menuCode, int nRow, vector<CProjectSettlement>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CProjectSettlement>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;				//	��������
	double  m_total_price;		//	���������
	double	m_material_percent;	//	�������ϼ��豸��ռ��
	double	m_advance_payment_percent;	//	Ԥ����ռ��
	double	m_quality_bond_percent;		//	������֤��ռ��
	
	vector<CProjectSettlementObj>	m_objs;	
};


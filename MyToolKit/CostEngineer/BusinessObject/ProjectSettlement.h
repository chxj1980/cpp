#pragma once


/* �����£�����һ�����̽��� */

class CProjectSettlement;

class CProjectSettlementObj
{
public:
	CProjectSettlementObj();

	virtual ~CProjectSettlementObj();

	virtual void Serialize(CArchive& ar, double version);

	virtual bool CreateOrUpdate(string menuCode, CProjectSettlement* parent);

	
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
	

	virtual CProjectSettlementObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual bool AddChild(string menuCode);
	virtual bool UpdateChild(string menuCode, int nRow);
	virtual bool DeleteChild(string menuCode, int nRow);

	static CProjectSettlement* NewParent(CString name);
	static void Serialize(CArchive& ar, double version, CProjectSettlement*  & p);
	static bool CreateOrUpdate(string strMenuCode, CProjectSettlement* & p);
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlement*>& cols);
	static bool Update(string menuCode, int nRow, vector<CProjectSettlement*>& cols);
	static bool Delete(string menuCode, int nRow, vector<CProjectSettlement*>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CProjectSettlement*>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;				//	��������
	CString m_method;			//	����N

	double  m_total_price;		//	���������
	double	m_material_percent;	//	�������ϼ��豸��ռ��
	double	m_advance_payment_percent;	//	Ԥ����ռ��
	double	m_quality_bond_percent;		//	������֤��ռ��
		
	vector<CProjectSettlementObj *>	m_objs;	
};

/*************************************************************************************/

class CProjectSettlementEx2 : public CProjectSettlement {
	virtual CProjectSettlementObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
};
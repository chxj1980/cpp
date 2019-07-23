#pragma once


/* �����£�����һ�����̽��� */

class CProjectSettlement;

class CProjectSettlementObj
{
public:
	CProjectSettlementObj() {};
	virtual ~CProjectSettlementObj() {};

	virtual void Serialize(CArchive& ar, double version) = 0;
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlement* parent) = 0;
};


class CProjectSettlement
{
public:
	CProjectSettlement();
	~CProjectSettlement();

	virtual void Serialize(CArchive& ar, double version) = 0;
	virtual bool CreateOrUpdate() = 0;
	virtual string Description() = 0;
	
	virtual CProjectSettlementObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual bool AddChild(string menuCode);
	virtual bool UpdateChild(string menuCode, int nRow);
	virtual bool DeleteChild(string menuCode, int nRow);

	static CProjectSettlement* NewParent(CString name);
	static void Serialize(CArchive& ar, double version, CProjectSettlement*  & p);
	static bool Create(string strMenuCode, CProjectSettlement*  & p);
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlement*>& cols);
	static bool Update(string menuCode, int nRow, vector<CProjectSettlement*>& cols);
	static bool Delete(string menuCode, int nRow, vector<CProjectSettlement*>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CProjectSettlement*>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

public:
	CString	m_scheme;			//	�������� -> ȷ�����������ִ�� 
		
	vector<CProjectSettlementObj *>	m_objs;	
};

/*************************************************************************************/

class CProjectSettlementObjEx2 : public CProjectSettlementObj {
public:
	CProjectSettlementObjEx2() {
		m_month = "";
		m_actual_workload = 0;
		m_schedule_workload = 0;
		m_party_a_material = 0;
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlement* parent);

public:
	CString	m_month;				//  �·�
	double	m_actual_workload;		//	ʵ����ɹ�����
	double	m_schedule_workload;	//	�ƻ���ɹ�����
	double	m_party_a_material;		//	�׹�����
};

class CProjectSettlementEx2 : public CProjectSettlement {
public:

	CProjectSettlementEx2() {
		m_name = "";
		m_total_price = 0;
		m_advance_payment_percent = 0;
		m_material_percent = 0;
		m_quality_bond_percent = 0;
	};

	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate();
	virtual string Description();
	virtual CProjectSettlementObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);

public:
	CString m_name;				//	��������
	double  m_total_price;		//	���������
	double	m_material_percent;	//	�������ϼ��豸��ռ��
	double	m_advance_payment_percent;	//	Ԥ����ռ��
	double	m_quality_bond_percent;		//	������֤��ռ��
};

/*************************************************************************************/

class CProjectSettlementObjEx3 : public CProjectSettlementObj {
public:
	CProjectSettlementObjEx3() {
		m_month = "";
		m_actual_workload = 0;
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlement* parent);

public:
	CString	m_month;				//  �·�
	double	m_actual_workload;		//	ʵ����ɹ�����
};


class CProjectSettlementEx3 : public CProjectSettlement {
public:
	CProjectSettlementEx3() {
		m_name = "";
		m_total_workload = 0;
		m_unit_price = 0;
		m_advance_payment_percent = 0;
		m_quality_bond_percent = 0;
	};

	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate();
	virtual string Description();
	virtual CProjectSettlementObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);

public:
	CString m_name;				//	��������
	double	m_total_workload;	//	���̼ƻ�����
	double  m_unit_price;		//	����
	double	m_advance_payment_percent;	//	Ԥ����ռ��
	double	m_quality_bond_percent;		//	������֤��ռ��
};

/*************************************************************************************/

class CProjectSettlementObjEx4 : public CProjectSettlementObj {
public:
	CProjectSettlementObjEx4() {
		m_month = "";
		m_actual_fund = 0;
		m_adjust_fund = 0;

		m_ft1 = 0;
		m_ft2 = 0;
		m_ft3 = 0;
		m_ft4 = 0;
		m_ft5 = 0;
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlement* parent);

public:
	CString	m_month;			//  �·�
	double	m_actual_fund;		//	ʵ����ɹ��̿�
	double	m_adjust_fund;		//	���̱仯������

	double	m_ft1, m_ft2, m_ft3, m_ft4, m_ft5;	//	�����ڼ۸�ָ��
};


class CProjectSettlementEx4 : public CProjectSettlement {
public:
	CProjectSettlementEx4() {
		m_name = "";
		m_total_fund = 0;
		m_advance_payment_percent = 0;
		m_quality_bond_percent = 0;

		m_b0 = 0.15;
		m_b1 = 0.35;
		m_b2 = 0.23;
		m_b3 = 0.12;
		m_b4 = 0.08;
		m_b5 = 0.07;

		m_f01 = 100;
		m_f02 = 153.4;
		m_f03 = 154.4;
		m_f04 = 160.3;
		m_f05 = 144.4;

	};

	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate();
	virtual string Description();
	virtual CProjectSettlementObj* NewChild();
	virtual bool DrawChild(CGridCtrl* pGridCtrl);

public:
	CString m_name;				//	��������
	double	m_total_fund;		//	�ܺ�ͬ��
	double	m_advance_payment_percent;	//	Ԥ����ռ��
	double	m_quality_bond_percent;		//	������֤��ռ��

	double	m_b0;
	double	m_b1, m_b2, m_b3, m_b4, m_b5;		//	�ɵ�ֵ����Ȩ��
	double	m_f01, m_f02, m_f03, m_f04, m_f05;	//	���ڼ۸�ָ��
};
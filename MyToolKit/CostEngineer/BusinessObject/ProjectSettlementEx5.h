#pragma once


/* �����£�����һ�����̽��� */

class CProjectSettlementEx5;

class CProjectSettlementEx5Obj
{
public:
	CProjectSettlementEx5Obj() {};
	virtual ~CProjectSettlementEx5Obj() {};

	virtual void Serialize(CArchive& ar, double version) = 0;
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlementEx5* parent) = 0;
	virtual string Description() = 0;
	virtual double ProjectPrice() = 0;

public:
	CString	m_scheme;

	CString	m_month;	
	CString	m_name;
};

/* ����5 ���̽��� */
class CProjectSettlementEx5
{
public:
	CProjectSettlementEx5() {
		m_scheme = "";

		m_name = "";
		m_regulation_rate = 0;
		m_tax_rate = 0;
	};

	~CProjectSettlementEx5()
	{
		for (CProjectSettlementEx5Obj* e : m_objs)
			delete e;
	};

	// virtual void Serialize(CArchive& ar, double version) = 0;
	// virtual bool CreateOrUpdate() = 0;
	// virtual string Description() = 0;
	
	// virtual CProjectSettlementEx5Obj* NewChild(CString scheme);
	// virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual bool AddChild(string menuCode);
	virtual bool UpdateChild(string menuCode, int nRow);
	virtual bool DeleteChild(string menuCode, int nRow);

	static CProjectSettlementEx5* NewParent(CString name);
	static void Serialize(CArchive& ar, double version, CProjectSettlementEx5*  & p);
	static bool Create(string strMenuCode, CProjectSettlementEx5*  & p);
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlementEx5*>& cols);
	static bool Update(string menuCode, int nRow, vector<CProjectSettlementEx5*>& cols);
	static bool Delete(string menuCode, int nRow, vector<CProjectSettlementEx5*>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CProjectSettlementEx5*>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;
		
public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate();
	virtual string Description();
	virtual CProjectSettlementEx5Obj* NewChild(CString scheme);
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual void SortByMonth();

public:
	CString	m_scheme;			//	�������� -> ȷ�����������ִ�� 
	vector<CProjectSettlementEx5Obj *>	m_objs;	

public:
	CString m_name;				//	��������
	double	m_regulation_rate;	//	�����
	double	m_tax_rate;			//	˰��
};

/*************************************************************************************/

/* ���۷���ֲ����̿� */
class CProjectSettlementEx5ObjA : public CProjectSettlementEx5Obj {
public:
	CProjectSettlementEx5ObjA() {
		m_actual_workload = 0;
		m_unit_price = 0;
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlementEx5* parent);
	virtual string Description() { return " Object A "; };
	virtual double ProjectPrice();

public:
	double	m_actual_workload;		//	������
	double	m_unit_price;			//	����
};

/* ���۴�ʩ��Ŀ�� */
class CProjectSettlementEx5ObjB : public CProjectSettlementEx5Obj {
public:
	CProjectSettlementEx5ObjB() {
		m_fund = 0;
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CProjectSettlementEx5* parent);
	virtual string Description() { return " Object B "; };
	virtual double ProjectPrice();
public:
	double	m_fund;		//	��ʩ��
};



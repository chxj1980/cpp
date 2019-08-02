#pragma once


/* �����£�����һ�����̽��� */

class CFinanceAnalysis;

class CFinanceAnalysisObj
{
public:
	CFinanceAnalysisObj() {
		m_scheme = "";
		m_month = "";
		m_name = "";

		m_amount_of_money = 0;
	};
	virtual ~CFinanceAnalysisObj() {};

	virtual void Serialize(CArchive& ar, double version) = 0;
	virtual bool CreateOrUpdate(string menuCode, CFinanceAnalysis* parent) = 0;
	virtual string Description() = 0;
	virtual double AmountOfMoney() = 0;
	virtual bool Assist(CFinanceAnalysis* parent) = 0;
	virtual bool HasAssist() = 0;
	virtual bool CopyTo(CFinanceAnalysis* parent) = 0;

public:
	CString	m_scheme;

	CString	m_month;	
	CString	m_name;

	double	m_amount_of_money;		//	���
};

/* ����5 ���̽��� */
class CFinanceAnalysis
{
public:
	CFinanceAnalysis() {
		m_scheme = "";

		m_name = "";
		m_discount = "";
		m_net_residual_rate = 0;
		m_tax_surcharge_rate = 0;
		m_income_tax_rate = 0;
	};

	~CFinanceAnalysis()
	{
		for (CFinanceAnalysisObj* e : m_objs)
			delete e;
	};

	// virtual void Serialize(CArchive& ar, double version) = 0;
	// virtual bool CreateOrUpdate() = 0;
	// virtual string Description() = 0;
	
	// virtual CFinanceAnalysisObj* NewChild(CString scheme);
	// virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual bool AddChild(string menuCode);
	virtual bool UpdateChild(string menuCode, int nRow);
	virtual bool DeleteChild(string menuCode, int nRow);
	virtual bool AssistChild(string menuCode, int nRow);
	virtual bool CopyToChild(string menuCode, int nRow);

	static CFinanceAnalysis* NewParent(CString name);
	static void Serialize(CArchive& ar, double version, CFinanceAnalysis*  & p);
	static bool Create(string strMenuCode, CFinanceAnalysis*  & p);
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CFinanceAnalysis*>& cols);
	static bool Update(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols);
	static bool Delete(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols);
	static unsigned int PopupMenuId(string menuCode);
	// static void Calculate(string menuCode, vector<CFinanceAnalysis*>& cols);
	static bool Calculate(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols);
	static bool Adjust(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;
		
public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate();
	virtual string Description();
	virtual CFinanceAnalysisObj* NewChild(CString scheme);
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual void SortByMonth();
	virtual void Calculate();
	virtual void Adjust();
	virtual bool GetAmountOfMoney(CString month, CString name, double & amount);
	double AccumulativeTax(int nMonth);


public:
	CString	m_scheme;			//	�������� -> ȷ�����������ִ�� 
	vector<CFinanceAnalysisObj *>	m_objs;	

public:
	CString m_name;				//	��������
	CString m_discount;			//	�̶��ʲ��۾ɷ���
	double	m_net_residual_rate;	//	�۾���ĩ����ֵ��
	double	m_tax_surcharge_rate;	//	˰�𸽼���
	double	m_income_tax_rate;		//	����˰��

};

/*************************************************************************************/

/* ���۷���ֲ����̿� */
class CFinanceAnalysisObjA : public CFinanceAnalysisObj {
public:
	CFinanceAnalysisObjA() {
		
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CFinanceAnalysis* parent);
	virtual string Description();
	virtual double AmountOfMoney();
	virtual bool Assist(CFinanceAnalysis* parent);
	virtual bool HasAssist();
	virtual bool CopyTo(CFinanceAnalysis* parent);

public:
	
};

/* ���۴�ʩ��Ŀ�� */
class CFinanceAnalysisObjB : public CFinanceAnalysisObj {
public:
	CFinanceAnalysisObjB() {
		
	};

public:
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate(string menuCode, CFinanceAnalysis* parent);
	virtual string Description() ;
	virtual double AmountOfMoney();
	virtual bool Assist(CFinanceAnalysis* parent);
	virtual bool HasAssist();
	virtual bool CopyTo(CFinanceAnalysis* parent);
public:
	
};



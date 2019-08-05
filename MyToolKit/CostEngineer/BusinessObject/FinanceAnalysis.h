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

		m_tax_on_purchase = 0;
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
	virtual CFinanceAnalysisObj* NewChild(CString scheme) = 0;
	virtual bool DrawChild(CGridCtrl* pGridCtrl);
	virtual void SortByMonth();
	virtual void Calculate();
	virtual void Adjust();
	virtual bool GetAmountOfMoney(CString month, CString scheme, CString name, double & amount);
	virtual double AccumulativeTax(int nMonth) = 0;


public:
	CString	m_scheme;			//	�������� -> ȷ�����������ִ�� 
	vector<CFinanceAnalysisObj *>	m_objs;	

public:
	CString m_name;				//	��������
	CString m_discount;			//	�̶��ʲ��۾ɷ���
	double	m_net_residual_rate;	//	�۾���ĩ����ֵ��
	double	m_tax_surcharge_rate;	//	˰�𸽼���
	double	m_income_tax_rate;		//	����˰��

	double	m_tax_on_purchase;		//	�����ڽ���˰��

};

class CBeforeFinancing : public CFinanceAnalysis {
public:
	virtual double AccumulativeTax(int nMonth);
	virtual CFinanceAnalysisObj* NewChild(CString scheme);
};

class CAfterFinancing : public CFinanceAnalysis {
public:
	CAfterFinancing() {
		for(int i = 0; i< 5; i++)
		m_interest_rate[i] = 0;
	};
	virtual double AccumulativeTax(int nMonth);
	virtual CFinanceAnalysisObj* NewChild(CString scheme);
	virtual void Serialize(CArchive& ar, double version);
	virtual bool CreateOrUpdate();
	virtual double LoanRemaining(int nMonth, int nLoan);
public:
	double	m_interest_rate[5];		//	��� ��������
};

/*************************************************************************************/

/* �ֽ����� */
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

class CFinanceAnalysisObjA1 : public CFinanceAnalysisObj {
public:
	CFinanceAnalysisObjA1() {

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

/* �ֽ����� */
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

/* ���n */
class CFinanceAnalysisObjC : public CFinanceAnalysisObj {
public:
	CFinanceAnalysisObjC() {

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


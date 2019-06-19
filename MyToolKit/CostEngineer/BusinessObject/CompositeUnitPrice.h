#pragma once


/* �����£������ţ��ۺϵ��۷����� */

class CCompositeUnitPriceObj
{
public:
	CCompositeUnitPriceObj();

	~CCompositeUnitPriceObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode, vector<CConsumptionQuota>& quotas);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CCompositeUnitPriceObj>& cols, vector<CConsumptionQuota>& quotas);
	static bool Update(string menuCode, int nRow, vector<CCompositeUnitPriceObj>& cols, vector<CConsumptionQuota>& quotas);
	static bool Delete(string menuCode, int nRow, vector<CCompositeUnitPriceObj>& cols);

	
	CString m_consumption_quota_id;				//  ���Ķ�����
	double	m_consumption_quantity;		//	�������������
};


class CCompositeUnitPrice
{
public:
	CCompositeUnitPrice();
	~CCompositeUnitPrice();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CCompositeUnitPrice>& cols);
	static bool Update(string menuCode, int nRow, vector<CCompositeUnitPrice>& cols);
	static bool Delete(string menuCode, int nRow, vector<CCompositeUnitPrice>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CCompositeUnitPrice>& cols, vector<CConsumptionQuota>& quotas);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;			//	
	double  m_formula_quantity;		//	�����淶������
			

	vector<CCompositeUnitPriceObj>	m_materials;	//	���ֺĲ�,�˹�������������
};


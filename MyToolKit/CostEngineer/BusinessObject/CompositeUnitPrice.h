#pragma once


/* �����£������ţ��ۺϵ��۷����� */

class CCompositeUnitPriceObj
{
public:
	CCompositeUnitPriceObj();

	~CCompositeUnitPriceObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CCompositeUnitPriceObj>& cols);
	static bool Update(string menuCode, int nRow, vector<CCompositeUnitPriceObj>& cols);
	static bool Delete(string menuCode, int nRow, vector<CCompositeUnitPriceObj>& cols);

	
	CString m_name;				//  �˹� ���Ĳ�����
	double	m_quantity;			//	��������
	double	m_unit_price;		//	��λ�۸�
	CString m_unit;				//	������λ
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
	static void Calculate(string menuCode, vector<CCompositeUnitPrice>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;			//	
	double  m_formula_quantity;		//	�����淶������
	double	m_consumption_quantity;		//	�������������		

	vector<CCompositeUnitPriceObj>	m_materials;	//	���ֺĲ�,�˹�������������
};


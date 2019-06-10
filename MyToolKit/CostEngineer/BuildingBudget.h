#pragma once


/* �����£������ģ�ʩ��ͼԤ��-  ʵ������ */

class CBuildingBudgetObj
{
public:
	CBuildingBudgetObj();

	~CBuildingBudgetObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CBuildingBudgetObj>& cols);
	static bool Update(string menuCode, int nRow, vector<CBuildingBudgetObj>& cols);
	static bool Delete(string menuCode, int nRow, vector<CBuildingBudgetObj>& cols);

	
	CString m_name;				//  �˹� ���Ĳ�����
	double	m_quantity;			//	��������
	double	m_unit_price;		//	��λ�۸�
	CString m_unit;				//	������λ
};


class CBuildingBudget
{
public:
	CBuildingBudget();
	~CBuildingBudget();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CBuildingBudget>& cols);
	static bool Update(string menuCode, int nRow, vector<CBuildingBudget>& cols);
	static bool Delete(string menuCode, int nRow, vector<CBuildingBudget>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CBuildingBudget>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;			//	
	double  m_other_material_cost_percent;		//	�������Ϸ�ռ�����Ϸѵı���
	double	m_machine_tool_cost_percent;		//	ʩ������ʹ�÷�ռ�˲Ļ�֮�͵ı���		

	vector<CBuildingBudgetObj>	m_materials;	//	���ֺĲ�,�˹���
};


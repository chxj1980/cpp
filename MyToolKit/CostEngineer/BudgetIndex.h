#pragma once


/* �����£�������������ָ�귨 */

class CBudgetIndexObj
{
public:
	CBudgetIndexObj();

	~CBudgetIndexObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CBudgetIndexObj>& cols);
	static bool Update(string menuCode, int nRow, vector<CBudgetIndexObj>& cols);
	static bool Delete(string menuCode, int nRow, vector<CBudgetIndexObj>& cols);

	
	CString m_name;				//  �˹� ���Ĳ�����
	double	m_quantity;			//	��������
	double	m_unit_price;		//	��λ�۸�
	
};


class CBudgetIndex
{
public:
	CBudgetIndex();
	~CBudgetIndex();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CBudgetIndex>& cols);
	static bool Update(string menuCode, int nRow, vector<CBudgetIndex>& cols);
	static bool Delete(string menuCode, int nRow, vector<CBudgetIndex>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CBudgetIndex>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;			//	
	double  m_original_unilateral_cost;		//	ԭ���̵������
	double	m_quantity;		// �ֹ��̹�����		

	vector<CBudgetIndexObj>	m_percents;	//	���ƹ��̸����õı��� ���ֹ��������ƹ��̵Ĳ���ϵ��
};


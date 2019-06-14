#pragma once


/* �����£������������ƹ���Ԥ�㷨 */

class CSimilarEngineerBudgetObj
{
public:
	CSimilarEngineerBudgetObj();

	~CSimilarEngineerBudgetObj();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string menuCode);

	static bool Draw(CGridCtrl* pGridCtrl, vector<CSimilarEngineerBudgetObj>& cols);
	static bool Update(string menuCode, int nRow, vector<CSimilarEngineerBudgetObj>& cols);
	static bool Delete(string menuCode, int nRow, vector<CSimilarEngineerBudgetObj>& cols);

	
	CString m_name;				//  �˹��ѣ����Ϸѵ�
	double	m_percent;			//	ռ���ƹ��̵ı���
	double	m_different;		//	�ֹ�����ԭ���̵Ĳ���ϵ��
	
};


class CSimilarEngineerBudget
{
public:
	CSimilarEngineerBudget();
	~CSimilarEngineerBudget();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CSimilarEngineerBudget>& cols);
	static bool Update(string menuCode, int nRow, vector<CSimilarEngineerBudget>& cols);
	static bool Delete(string menuCode, int nRow, vector<CSimilarEngineerBudget>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CSimilarEngineerBudget>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	CString m_name;			//	
	double  m_original_unilateral_cost;		//	ԭ���̵������
	double	m_quantity;		// �ֹ��̹�����		

	vector<CSimilarEngineerBudgetObj>	m_percents;	//	���ƹ��̸����õı��� ���ֹ��������ƹ��̵Ĳ���ϵ��
};


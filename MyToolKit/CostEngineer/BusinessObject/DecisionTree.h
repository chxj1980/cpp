#pragma once
class CDecisionTree
{
public:
	CDecisionTree();

	~CDecisionTree();

	void Serialize(CArchive& ar, double version);

	bool CreateOrUpdate(string strMenuCode);

	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CDecisionTree>& cols);
	static bool Update(string menuCode, int nRow, vector<CDecisionTree>& cols);
	static bool Delete(string menuCode, int nRow, vector<CDecisionTree>& cols);
	static unsigned int PopupMenuId(string menuCode);
	
	static void Calculate(string menuCode, vector<CDecisionTree>& cols);
	static void SteelQuantity(string menuCode, vector<CDecisionTree>& cols);

	static string m_ObjectCode;
	static double m_ObjectVersion;

	int		m_code;					//  ���ڵ���
	CString m_branch_node;			//	��֧�ڵ�����	
	double	m_probability;			//	��֧�����ĸ���
	double	m_score;				//  �÷� ��һ������������
	int		m_parent_code;			//	���ڵ���
};


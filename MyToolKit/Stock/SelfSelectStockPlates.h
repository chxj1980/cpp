#pragma once

// ��ѡ�ɰ��

class CSelfSelectStockPlates
{
public:
	CSelfSelectStockPlates(void);
	~CSelfSelectStockPlates(void);

	string SqlScript();
	void ImportToDatabase();
	void ExportFromDatabase(double startTime = 0, double endTime = 0);
	vector<string> MailContents();
	
public:
	//CStockPlateTree * m_pTree;

	CStockPlateTree * m_pTree;

	HWND m_hWnd;	//	����֪ͨ��Ϣ��Ŀ�괰�ھ��
	int	m_nLogType;	//	��־�ļ���

	JMutex	m_mutex;

	map<int, int>	vec_code;
	map<int,string>	vec_name;
	map<int, int>	vec_company_number;
	map<int, int>	vec_parent_code;
	map<int, int>	vec_is_stock;	
};

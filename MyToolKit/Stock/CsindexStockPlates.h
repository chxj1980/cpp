#pragma once
#include "stockdatamodel.h"

class CCsindexStockPlates : public CStockDataModel
{
public:
	CCsindexStockPlates(void);
	~CCsindexStockPlates(void);

	string SqlScript();
	void ImportToDatabase();
	void ExportFromDatabase(double startTime = 0, double endTime = 0);
	//void UpdateFromXls(string strCode, string name, int company_number, int is_stock);

public:
	CStockPlateTree * m_pTree;

	HWND m_hWnd;	//	����֪ͨ��Ϣ��Ŀ�괰�ھ��
	int	m_nLogType;	//	��־�ļ���
};

#pragma once


class CCninfoStockChangePDF 
{
public:
	CCninfoStockChangePDF(void);
	~CCninfoStockChangePDF(void);

public:
	
	string ModelType(){ return  "CCninfoStockChangePDF"  /* �޳������� ��Ȩ�䶯 PDF �ļ����� */; }


	string SaveAsCsv();
	string SqlScript();

	void ImportToDatabase();


public:

	HWND		m_hWnd;
	int			m_nLogType;

	string					announcementId;
	string					announcementTitle;
	string					adjunctUrl;

	string					secCode;
	string					secName;
	string					announcementTime;
	map<int, CPdfCatalog>	mapCatalog;
	
	
};

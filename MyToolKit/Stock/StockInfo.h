#pragma once
#include "stockdatamodel.h"


class CStockInfoData
{
public:
	int					code			;	//	"��˾����",
	string				abbreviation			;	//	"��˾���",
	string				name			;	//	"��˾ȫ��",
	string				a_abbreviation			;	//	"A�ɼ��",
	string				a_time_to_market			;	//	"A����������",
	long				a_total_share			;	//	"A���ܹɱ�",
	long				a_circulation_share			;	//	"A����ͨ�ɱ�",
	string				area			;	//	"�� ��",
	string				province			;	//	"ʡ ��",
	string				city			;	//	"�� ��",
	string				belong_to_industry 			;	//	"������ҵ",
	string				web_addr			;	//	"��˾��ַ"

	string				stock_plate;				//	��Ʊ��飺 ��ҵ�桢��С��
	string				securities_exchange;		//	֤����

	string				cninfo_orgid;		//	�޳���

	bool operator == (const CStockInfoData &otherData)
	{
		if(code==otherData.code )
			return true;
		else
			return false;
	}
};

class CStockInfo :
	public CStockDataModel
{
public:
	CStockInfo(void){  m_CStockInfoDataMap.clear(); };
	virtual ~CStockInfo(void);

public:
	map<int, int>		m_vec_code			;	//	"��˾����",
	map<int, string>	m_vec_abbreviation			;	//	"��˾���",
	map<int, string>	m_vec_name			;	//	"��˾ȫ��",
	map<int, string>	m_vec_english_name			;	//	"Ӣ������",
	map<int, string>	m_vec_register_addr			;	//	"ע���ַ",
	map<int, int>		m_vec_a_code			;	//	"A�ɴ���",
	map<int, string>	m_vec_a_abbreviation			;	//	"A�ɼ��",
	map<int, string>	m_vec_a_time_to_market			;	//	"A����������",
	map<int, long>		m_vec_a_total_share			;	//	"A���ܹɱ�",
	map<int, long>		m_vec_a_circulation_share			;	//	"A����ͨ�ɱ�",
	map<int, int>		m_vec_b_code			;	//	"B�ɴ���",
	map<int, string>	m_vec_b_abbreviation			;	//	"B�� �� ��",
	map<int, string>	m_vec_b_time_to_market			;	//	"B����������",
	map<int, long>		m_vec_b_total_share			;	//	"B���ܹɱ�",
	map<int, long>		m_vec_b_circulation_share			;	//	"B����ͨ�ɱ�",
	map<int, string>	m_vec_area			;	//	"�� ��",
	map<int, string>	m_vec_province			;	//	"ʡ ��",
	map<int, string>	m_vec_city			;	//	"�� ��",
	map<int, string>	m_vec_belong_to_industry 			;	//	"������ҵ",
	map<int, string>	m_vec_web_addr			;	//	"��˾��ַ"

	map<int, string>	m_vec_cninfo_orgid;			//	�޳���
	map<int, string>	m_vec_cninfo_pinyin;		//	�޳���

	string	m_stock_plate;				//	��Ʊ��飺 ��ҵ�桢��С��
	string  m_securities_exchange;		//	֤����

	map<int, CStockInfoData> m_CStockInfoDataMap;

public:
	
	string SqlScript();

	int	 SearchStockByCode(int code);

	void GenerateMap();

	/*virtual string GetDownloadUrl() = 0;
	virtual bool ParseCsvFileName(string szFileName) = 0;*/

};

class CShenzhenStockInfo : public CStockInfo
{
public:
	CShenzhenStockInfo(void);
	~CShenzhenStockInfo(void);

public:
	int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData);
	void ParseXmlElement(void);
	void ImportToDatabase(void);
	void ExportFromDatabase(double startTime = 0, double endTime = 0);
	string SaveAsCsv();

	bool ParseCsvFileName(string szFileName);
	string GetCsvFileName();

protected:
	string	m_strEnglishName;
};


//////////////////////////////////////////////////////////////////////////
//	��ҵ��
class CEntrepreneurship : public CShenzhenStockInfo
{
public:
	CEntrepreneurship()
	{ 
		m_stock_plate="��ҵ��";
		m_securities_exchange = "����֤ȯ������";
		m_strEnglishName = "Entrepreneurship";
	}

	string GetDownloadUrl();
	
	CStockDataModel * NewCopy();

	string ModelType(){ return "CEntrepreneurship" /*"��ҵ���Ʊ������Ϣ"*/; }
};

//////////////////////////////////////////////////////////////////////////
//	��С��


 class CSmallMidEnterprise : public CShenzhenStockInfo
 {
 public:
	 CSmallMidEnterprise()
	 { 
		 m_stock_plate="��С��ҵ��";
		 m_securities_exchange = "����֤ȯ������";
		 m_strEnglishName = "SmallMidEnterprise";
	 }

	 string GetDownloadUrl();
	 CStockDataModel * NewCopy();

	 string ModelType(){ return "CSmallMidEnterprise"  /*"��С��ҵ���Ʊ������Ϣ"*/; }
 };

 //////////////////////////////////////////////////////////////////////////
 //	����A��


 class CShenzhenAshares : public CShenzhenStockInfo
 {
 public:
	 CShenzhenAshares()
	 { 
		 m_stock_plate="����A��";
		 m_securities_exchange = "����֤ȯ������";
		 m_strEnglishName = "ShenzhenAshares";
	 }

	 string GetDownloadUrl();
	 CStockDataModel * NewCopy();

	 string ModelType(){ return  "CShenzhenAshares"  /*"����A�ɻ�����Ϣ"*/; }
 };
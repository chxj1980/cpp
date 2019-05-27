#pragma once
#include "stockdatamodel.h"


class CStockDownloadData
{
public:
	int			code			;	//	"��˾����",
	string		cninfo_bonus;
	string		cninfo_placement_of_share;
	string		SouhuTradingDaily;
	string		SohuMainIncomeComposition;
	string		SohuPerformanceForecast;
	string		CapitalFlows163;
	string		_10jqka_bonus;
	string		CapitalStructure;
	string		NetEase_Trade_Daily;

	string		Balance;
	string		CashFlows;
	string		IncomeStatement;

	int			Balance_Zip;
	int			CashFlows_Zip;
	int			IncomeStatement_Zip;

	string		hexun_research_paper;



	bool		isUpdated;

	bool operator == (const CStockDownloadData &otherData)
	{
		if(code==otherData.code )
			return true;
		else
			return false;
	}

	CStockDownloadData()
	{
		isUpdated = false;
		code = 0;
		cninfo_bonus = "0000-00-00";
		cninfo_placement_of_share = "0000-00-00";
		SouhuTradingDaily = "0000-00-00";
		NetEase_Trade_Daily = "0000-00-00";
		SohuMainIncomeComposition = "0000-00-00";
		SohuPerformanceForecast = "0000-00-00";
		CapitalFlows163 = "0000-00-00";
		_10jqka_bonus = "0000-00-00";
		CapitalStructure = "0000-00-00";

		Balance = "0000-00-00";
		CashFlows = "0000-00-00";
		IncomeStatement = "0000-00-00";

		Balance_Zip = 0;
		CashFlows_Zip = 0;
		IncomeStatement_Zip = 0;

		hexun_research_paper = "0000-00-00";
	}
};

class CStockDataLog
{
public:
	CStockDataLog(void);
	virtual ~CStockDataLog(void);

private:
	
	map<string, CStockDownloadData> m_CStockDownloadDataMap;
	
	
	//	���ϴ��������ݿ⣬���� ���µ� �ֶ���Ŀ
	int			m_UpdatedNum;			
	JMutex		m_mutxMap;

private:
	//	����ÿ�ű� ���� ÿ��ָ�� ������������
	map<string, string>		m_TableUpdatedMap;

public:
	//	������н�����
	vector<string>			m_vecTradedate;

	//  ������й�Ʊ
	vector<string>			m_vecExitStock;
	
public:
	
	string SqlScript();
	void FetchFromDB();

	CStockDownloadData	 SearchStockByCode(int code);
	void UpdateStockByCode(int code, string tableName, string val);
	void UpdateTable(string tablename, string val);
	string SearchTableUpdated(string table_name);
	string MaxDateByTable(string tableName);

	string CheckTable(string tableName);
};

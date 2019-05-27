
// Stock.h : Stock Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CStockApp:
// �йش����ʵ�֣������ Stock.cpp
//

class CMvDocTemplate : public CMultiDocTemplate
{
public:
	CMvDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);

	virtual ~CMvDocTemplate(){}

	CRuntimeClass * GetCurrView(){return m_pViewClass;}
};

class CStockApp : public CWinAppEx
{
public:
	CStockApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	CDocTemplate* GetCurrDocTemplate(CView * pView);

	BOOL TestRequestExit();

	CWinThread * StartWorkerThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam);

	// ���ڹ�Ʊ��Ϣ
	CEntrepreneurship m_CEntrepreneurship;
	CSmallMidEnterprise m_CSmallMidEnterprise;
	CShenzhenAshares m_CShenzhenAshares;

	// �Ϻ���Ʊ��Ϣ
	CShanghaiStockInfo m_CShanghaiStock;

	//	�Ѻ���Ʊ���
	CStockPlateTree *		m_pCSouhuStockPlates;
	vector<CStockPlateData>	m_vecStockPlateArea;
	vector<CStockPlateData>	m_vecStockPlateConcept;
	vector<CStockPlateData>	m_vecStockPlateIndustry;

	//	�Զ����Ʊ���
	CSelfSelectStockPlates * m_pCSelfSelectStockPlates;

	//	���ڹ�Ʊָ�����
	CShenzhenIndexList	 m_ShenzhenIndexList;

	//	�й�֤ȯָ����˾���
	CStockPlateTree *  m_pCsindexStockPlates;

	//	�й�֤ȯָ�� ֤�����ҵ���
	CStockPlateTree *  m_pCsindexCsrcStockPlates;

	//	����ͳ�ƾ� ���¶����ݰ��
	CStockPlateTree *  m_pCStatsGovHgydPlates;

	//	����ͳ�ƾ֣� �������ݰ��
	CStockPlateTree *  m_pCStatsGovHgjdPlates;

	//	����ͳ�ƾ֣� ������ݰ��
	CStockPlateTree *  m_pCStatsGovHgndPlates;

	//	����ͳ�ƾ� ����ʡ�¶����ݰ��
	CStockPlateTree *  m_pCStatsGovFsydPlates;

	//	����ͳ�ƾ֣� ��ʡ�������ݰ��
	CStockPlateTree *  m_pCStatsGovFsjdPlates;

	//	����ͳ�ƾ֣� ��ʡ������ݰ��
	CStockPlateTree *  m_pCStatsGovFsndPlates;

	//	����Ľ����յ����ڹ�Ʊ����
	CShenzhenMarketQuotation m_CShenzhenMarketQuotation;

	//	�ض���Ʊ�����ݳ�
	map<int, CNetEaseTradeDaily>	m_mapTradingDaily;
	map<int, CCninfoCashFlows>	m_mapCashFlows;
	map<int, CCninfoBalance>		m_mapBalance;
	map<int, CCninfoIncomeStatement>	m_mapIncomeStatement;
	map<int, CCapitalStructOf10jqka>	m_mapCapitalStruct;
	map<int, CShenzhenMarketQuotation>	m_mapShenzhenQuotation;
	map<int, CCapitalFlows163>	m_mapCapitalFlows;
	map<int, CSohuPerformanceForecast>	m_CSohuPerformanceForecast;
	map<int, CSohuFundHold>		m_mapFundHold;

	//	���й�Ʊ�� ���ݸ��¼�¼
	CStockDataLog	m_StockDataLog;

	// map<int, double>	m_mapClosePrice;

	//	ͳһ������̨�Ĺ����̡߳�
	vector<CWinThread *>  m_vec_pThread;

	HANDLE	m_bAppExit;

	
	list<StockInfo_Reqeust>		m_listStockinfoReq;	
		
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
	virtual int ExitInstance();

public:
	void PostCalculateTask(void * clientData, CalculateTaskFunc * proc);
	void* FetchCalculateResult(int taskHandle);
	virtual BOOL OnIdle(LONG lCount);

protected:
	TCHAR  theAppPath[MAX_PATH];
};

extern CStockApp theApp;

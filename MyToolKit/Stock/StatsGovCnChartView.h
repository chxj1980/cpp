#pragma once
#include "BaseChartCtlView.h"

// CStatsGovCnChartView ��ͼ

class CStatsGovCnChartView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CStatsGovCnChartView)

protected:
public:
	CStatsGovCnChartView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStatsGovCnChartView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void ProccessChartMenu();


public:
	void RedrawDmGraph();
	
	virtual void OnInitialUpdate();

	void PostFocusChanged();

protected:
	CStatsGovCnDoc  m_LocalDoc;
public:
	afx_msg void OnFinanceSalesFromOperations(UINT nID);
	afx_msg void OnStatsgovHgydMenu(UINT nID);

};



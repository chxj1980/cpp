#pragma once

#include "BaseChartCtlView.h"
// CIndividualCapitalFlowView ��ͼ

class CIndiDmiView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiDmiView)

protected:
public:
	CIndiDmiView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiDmiView();

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

public:
	void RedrawDmGraph();
	void PostButtonClicked(int nWinDay);

	virtual void RedrawChart(CCalculateTask * cse);

private:
	CChartCandlestickSerie * m_pCandlestickSerie;
	CChartBarSerie*			m_pBarSeries;

	void ExportFromDatabase(string strCode, double startTime = 0, double endTime = 0);

public:
	virtual void OnInitialUpdate();

protected:
	CIndividualShareDoc m_LocalDoc;
};



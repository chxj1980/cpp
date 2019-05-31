#pragma once
#include "BaseChartCtlView.h"


// CIndiCsindexView ��ͼ

class CIndiGrossProfitRateView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiGrossProfitRateView)

protected:
public:
	CIndiGrossProfitRateView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiGrossProfitRateView();

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

private:
	//void RedrawDmGraph(CCalculateTask * cse);

public:
	virtual void OnInitialUpdate();

	afx_msg void OnIndiGrossProfitRate();

	virtual void RedrawDmGraph();

	void PostFocusChanged();

protected:
	CIndividualShareDoc m_LocalDoc;
};


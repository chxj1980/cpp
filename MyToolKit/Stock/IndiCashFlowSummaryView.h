

#include "BaseChartCtlView.h"

// CIndiCashFlowSummaryView ��ͼ

class CIndiCashFlowSummaryView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiCashFlowSummaryView)

protected:
public:
	CIndiCashFlowSummaryView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiCashFlowSummaryView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	void RedrawDmGraph();
	virtual void OnInitialUpdate();

protected:
	DECLARE_MESSAGE_MAP()


};



#pragma once

#include "basegridctlview.h"
// CPlateChangeRateSummaryView ��ͼ

class CPlateGrossProfitRateGrowthView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CPlateGrossProfitRateGrowthView)

protected:
public:
	CPlateGrossProfitRateGrowthView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPlateGrossProfitRateGrowthView();

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
	virtual void OnInitialUpdate();
};



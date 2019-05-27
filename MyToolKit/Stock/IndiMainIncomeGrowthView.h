#pragma once
#include "BaseChartCtlView.h"

// CIndiMainIncomeGrowthView ��ͼ

class CIndiMainIncomeGrowthView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiMainIncomeGrowthView)

protected:
public:
	CIndiMainIncomeGrowthView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiMainIncomeGrowthView();

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
	void RedrawDmGraph(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

public:
	virtual void OnInitialUpdate();
};




#pragma once
#include "BaseChartCtlView.h"

// CMarketSohuIndexView ��ͼ

class CMarketSohuIndexView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CMarketSohuIndexView)

protected:
public:
	CMarketSohuIndexView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMarketSohuIndexView();

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
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

public:
	void RedrawDmGraph();
	virtual void RedrawDmGraph(CCalculateTask * cse);
	virtual void OnInitialUpdate();
};



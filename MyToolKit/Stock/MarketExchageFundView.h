#pragma once

#include "BaseChartCtlView.h"

// CMarketExchageFundView ��ͼ

class CMarketExchageFundView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CMarketExchageFundView)

protected:
public:
	CMarketExchageFundView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMarketExchageFundView();

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



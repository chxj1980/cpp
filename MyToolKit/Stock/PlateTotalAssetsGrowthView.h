#pragma once

#include "BaseChartCtlView.h"
// CPlateTotalAssetsGrowthView ��ͼ

class CPlateTotalAssetsGrowthView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CPlateTotalAssetsGrowthView)

protected:
public:
	CPlateTotalAssetsGrowthView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPlateTotalAssetsGrowthView();

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



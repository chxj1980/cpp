#pragma once

#include "BaseChartCtlView.h"

// CPlateIndustryDynamicPeView ��ͼ

class CPlateCsindexDynamicPeView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CPlateCsindexDynamicPeView)

protected:
public:
	CPlateCsindexDynamicPeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPlateCsindexDynamicPeView();

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
	//virtual void RedrawDmGraph(CCalculateTask * cse);
	virtual void OnInitialUpdate();

	virtual void ProccessChartMenu();
};



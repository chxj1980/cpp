#pragma once

#include "BaseChartCtlView.h"
// CIndividualYahooPeView ��ͼ

class CIndividualYahooPeView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndividualYahooPeView)

protected:
public:
	CIndividualYahooPeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualYahooPeView();

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
	virtual void OnInitialUpdate();
};



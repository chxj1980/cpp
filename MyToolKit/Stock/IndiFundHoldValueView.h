#pragma once
#include "BaseChartCtlView.h"


// CIndiFundHoldValueView ��ͼ

class CIndiFundHoldValueView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiFundHoldValueView)

protected:
public:
	CIndiFundHoldValueView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiFundHoldValueView();

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
};



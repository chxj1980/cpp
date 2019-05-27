#pragma once

#include "IndividualDmGraphView.h"
// CIndividualCostView ��ͼ

class CIndividualCostView : public CIndividualDmGraphView
{
	DECLARE_DYNCREATE(CIndividualCostView)

protected:
public:
	CIndividualCostView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualCostView();

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

protected:
	DECLARE_MESSAGE_MAP()

private:
	void OverallCostsCurve();

};



#pragma once
#include "BaseChartCtlView.h"

// CIndiZombieAnalysisView ��ͼ

class CIndiZombieAnalysisView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiZombieAnalysisView)

protected:
public:
	CIndiZombieAnalysisView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiZombieAnalysisView();

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



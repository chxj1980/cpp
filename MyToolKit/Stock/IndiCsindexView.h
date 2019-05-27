#pragma once
#include "BaseChartCtlView.h"


// CIndiCsindexView ��ͼ

class CIndiCsindexView : public CBaseChartCtlView
{
	DECLARE_DYNCREATE(CIndiCsindexView)

protected:
public:
	CIndiCsindexView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiCsindexView();

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
	//void RedrawDmGraph(CCalculateTask * cse);

public:
	virtual void OnInitialUpdate();

	afx_msg void OnIndiCsindexAnalysis();

	virtual void RedrawDmGraph();

	void PostFocusChanged();

protected:
	CIndividualShareDoc m_LocalDoc;
};



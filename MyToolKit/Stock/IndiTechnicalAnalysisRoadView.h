#pragma once

#include "BaseMessageFormView.h"

// CPlateIndustryDynamicPeView ��ͼ

class CIndiTechnicalAnalysisRoadView : public CBaseMessageFormView
{
	DECLARE_DYNCREATE(CIndiTechnicalAnalysisRoadView)

protected:
public:
	CIndiTechnicalAnalysisRoadView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndiTechnicalAnalysisRoadView();

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

	string ExtractKeyword(string title);

	virtual void RedrawChart(CCalculateTask * cse);

	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	

};



#pragma once


#include "BaseGridCtlView.h"
// CIndividualSummaryView ��ͼ

class CIndividualSummaryView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CIndividualSummaryView)

protected:
public:
	CIndividualSummaryView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualSummaryView();

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
	virtual void OnInitialUpdate();
	
private:
	void RedrawGridCtrl();
	int SearchStockInfo(CStockInfo * pStockinfo, int code);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);
};



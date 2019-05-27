#pragma once
#include "basegridctlview.h"

// CPeStockListView ��ͼ

class CPeStockListView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CPeStockListView)

protected:
public:
	CPeStockListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPeStockListView();

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
	void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

public:
	virtual void OnInitialUpdate();
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnTableAddToSelfSelect();
};



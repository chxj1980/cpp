#pragma once
#include "basegridctlview.h"

class CPlateStockListView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CPlateStockListView)

protected:
public:
	CPlateStockListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPlateStockListView();

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
	void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
};

#pragma once
#include "basegridctlview.h"

// CStockHomePageView ��ͼ

class CStockHomePageView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CStockHomePageView)

protected:
public:
	CStockHomePageView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStockHomePageView();

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
public:
	afx_msg void OnClose();
};



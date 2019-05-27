#pragma once

#include "./GridCtrl_src/GridCtrl.h"

// CCsvView ��ͼ

class CCsvView : public CView
{
	DECLARE_DYNCREATE(CCsvView)

protected:
	CCsvView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCsvView();

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
	CGridCtrl* m_pGridCtrl;
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};



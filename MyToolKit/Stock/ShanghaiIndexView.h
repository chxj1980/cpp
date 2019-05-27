#pragma once
#include "BaseMatlabView.h"

// CShanghaiIndexView ��ͼ

class CShanghaiIndexView : public CBaseMatlabView
{
	DECLARE_DYNCREATE(CShanghaiIndexView)

protected:
public:
	CShanghaiIndexView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CShanghaiIndexView();

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
	virtual void Startup();
	afx_msg void OnSetStockRange();
	afx_msg void OnUpdateShanghaiIndex(CCmdUI *pCmdUI);
};



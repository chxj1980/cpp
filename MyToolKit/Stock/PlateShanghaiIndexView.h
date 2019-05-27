#pragma once
#include "BaseMatlabView.h"

// CShanghaiIndexView ��ͼ

class CPlateShanghaiIndexView : public CBaseMatlabView
{
	DECLARE_DYNCREATE(CPlateShanghaiIndexView)

protected:
public:
	CPlateShanghaiIndexView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPlateShanghaiIndexView();

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



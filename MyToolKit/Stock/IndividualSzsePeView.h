#pragma once

#include "IndividualDmGraphView.h"
// CIndividualSzsePeView ��ͼ

class CIndividualSzsePeView : public CIndividualDmGraphView
{
	DECLARE_DYNCREATE(CIndividualSzsePeView)

protected:
public:
	CIndividualSzsePeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualSzsePeView();

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
};



#pragma once


#include "IndividualDmGraphView.h"
// CIndividualNetProfitsView ��ͼ

class CIndividualNetProfitsView : public CIndividualDmGraphView
{
	DECLARE_DYNCREATE(CIndividualNetProfitsView)

protected:
public:
	CIndividualNetProfitsView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualNetProfitsView();

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



#pragma once


// CIndividualVolumeView ��ͼ

#include "IndividualDmGraphView.h"
class CIndividualVolumeView : public CIndividualDmGraphView
{
	DECLARE_DYNCREATE(CIndividualVolumeView)

protected:
public:
	CIndividualVolumeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualVolumeView();

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



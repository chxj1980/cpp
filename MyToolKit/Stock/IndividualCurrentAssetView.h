#pragma once

#include "IndividualDmGraphView.h"
// CIndividualCurrentAssetView ��ͼ

class CIndividualCurrentAssetView : public CIndividualDmGraphView
{
	DECLARE_DYNCREATE(CIndividualCurrentAssetView)

protected:
public:
	CIndividualCurrentAssetView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualCurrentAssetView();

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

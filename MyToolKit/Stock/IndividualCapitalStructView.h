#pragma once


#include "BaseGridCtlView.h"
// CIndividualCapitalStructView ��ͼ

class CIndividualCapitalStructView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CIndividualCapitalStructView)

protected:
public:
	CIndividualCapitalStructView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualCapitalStructView();

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

	void RedrawGridCtrl();
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);
};



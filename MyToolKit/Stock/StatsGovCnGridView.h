#pragma once

#include "basegridctlview.h"
// StatsGovCnGridView ��ͼ

class CStatsGovCnGridView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CStatsGovCnGridView)

protected:
public:
	CStatsGovCnGridView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStatsGovCnGridView();

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


private:
	void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);
	void Startup();

public:
	virtual void OnInitialUpdate();

private:
	bool	m_bCalculating;

};



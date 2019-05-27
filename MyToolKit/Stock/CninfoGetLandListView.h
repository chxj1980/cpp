#pragma once
#include "basegridctlview.h"

// CHexunResearchPaperListView ��ͼ

class CCninfoGetLandListView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CCninfoGetLandListView)

protected:
public:
	CCninfoGetLandListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCninfoGetLandListView();

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
	afx_msg void OnTableAdvancedQuery();
	afx_msg void OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI);
	void OnPageUpdate();

private:
	bool	m_bCalculating;
	string	m_strLike;
	int		m_nPlateCode;
	string	m_sPlateName;
public:
	
	afx_msg void OnTableAddToSelfSelect();

	virtual void PostGridDblClick(int nRow);
};



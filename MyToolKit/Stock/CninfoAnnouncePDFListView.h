#pragma once
#include "BaseRichEditFormView.h"

// CHexunResearchPaperListView ��ͼ

class CCninfoAnnouncePDFListView : public CBaseRichEditFormView
{
	DECLARE_DYNCREATE(CCninfoAnnouncePDFListView)

protected:
public:
	CCninfoAnnouncePDFListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCninfoAnnouncePDFListView();

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
	void Startup();

public:
	virtual void OnInitialUpdate();
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnTableAdvancedQuery();
	afx_msg void OnUpdateTableAdvancedQuery(CCmdUI *pCmdUI);
	void OnPageUpdate();

private:
	bool	m_bCalculating;
	string	m_strLike;
	int		m_nPlateCode;
	string	m_sPlateName;

	vector<string>	m_vec_catalogContent;
public:
	
	afx_msg void OnTableAddToSelfSelect();

	afx_msg void OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
};



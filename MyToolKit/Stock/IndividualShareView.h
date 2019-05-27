#pragma once


// CIndividualShareView ��ͼ

class CIndividualShareView : public CView
{
	DECLARE_DYNCREATE(CIndividualShareView)

protected:
public:
	CIndividualShareView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndividualShareView();

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
	CDMGraphCtrl	m_DMGraph;
	DATE	m_StartDate;
	DATE	m_EndDate;
	string	m_strViewType;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnUserXmlWParam(WPARAM wParam, LPARAM lParam);

private:
	void SetGraphData(VARIANT* pvarrX, VARIANT* pvarrY, LPCTSTR szName);
	void TradingDailyCurve(int nStart, int nEnd, string strViewType);
	void PeCurve(int nStart, int nEnd);
	void RedrawDmGraph();

public:
	afx_msg void OnSetStockRange();
};



#pragma once


// CBaseMessageView ��ͼ

class CBaseMessageView : public CView
{
	DECLARE_DYNCREATE(CBaseMessageView)

protected:
	CBaseMessageView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBaseMessageView();

	
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

	CBaseMessageControl	m_MessageCtrl;

public:
	

	afx_msg LRESULT OnUserXmlWParam(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserLogWParam_1(WPARAM wParam, LPARAM lParam);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3){}
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	virtual void PostFocusChanged(){};
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



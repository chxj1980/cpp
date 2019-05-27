#pragma once

#include "RealplayPannel.h"

// CRealplayView ������ͼ

class CRealplayView : public CFormView
{
	DECLARE_DYNCREATE(CRealplayView)

protected:
public:
	CRealplayView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRealplayView();

public:
	enum { IDD = IDD_REALPLAYVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	

	CRealplayPannel	m_screenPannel;
	CRect		m_VideoRect;

	COleDropTarget m_CTreeDropTarget;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
};



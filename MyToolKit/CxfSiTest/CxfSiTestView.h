
// CxfSiTestView.h : CCxfSiTestView ��Ľӿ�
//


#pragma once


class CCxfSiTestView : public CView
{
protected: // �������л�����
	CCxfSiTestView();
	DECLARE_DYNCREATE(CCxfSiTestView)

// ����
public:
	CCxfSiTestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCxfSiTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCxfsiCatalog();
	afx_msg void OnCxfsiJrtplibTest();
};

#ifndef _DEBUG  // CxfSiTestView.cpp �еĵ��԰汾
inline CCxfSiTestDoc* CCxfSiTestView::GetDocument() const
   { return reinterpret_cast<CCxfSiTestDoc*>(m_pDocument); }
#endif


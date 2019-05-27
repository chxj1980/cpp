
// GB28181ClientMDIView.h : CGB28181ClientMDIView ��Ľӿ�
//


#pragma once


class CGB28181ClientMDIView : public CView
{
protected: // �������л�����
	CGB28181ClientMDIView();
	DECLARE_DYNCREATE(CGB28181ClientMDIView)

// ����
public:
	CGB28181ClientMDIDoc* GetDocument() const;

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
	virtual ~CGB28181ClientMDIView();
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
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);

private:
	COleDropTarget m_CTreeDropTarget;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // GB28181ClientMDIView.cpp �еĵ��԰汾
inline CGB28181ClientMDIDoc* CGB28181ClientMDIView::GetDocument() const
   { return reinterpret_cast<CGB28181ClientMDIDoc*>(m_pDocument); }
#endif


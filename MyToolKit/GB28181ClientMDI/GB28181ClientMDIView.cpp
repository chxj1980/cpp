
// GB28181ClientMDIView.cpp : CGB28181ClientMDIView ���ʵ��
//

#include "stdafx.h"
#include "GB28181ClientMDI.h"

#include "GB28181ClientMDIDoc.h"
#include "GB28181ClientMDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGB28181ClientMDIView

IMPLEMENT_DYNCREATE(CGB28181ClientMDIView, CView)

BEGIN_MESSAGE_MAP(CGB28181ClientMDIView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGB28181ClientMDIView::OnFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CGB28181ClientMDIView ����/����

CGB28181ClientMDIView::CGB28181ClientMDIView()
{
	// TODO: �ڴ˴���ӹ������

}

CGB28181ClientMDIView::~CGB28181ClientMDIView()
{
}

BOOL CGB28181ClientMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CGB28181ClientMDIView ����

void CGB28181ClientMDIView::OnDraw(CDC* /*pDC*/)
{
	CGB28181ClientMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CGB28181ClientMDIView ��ӡ


void CGB28181ClientMDIView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CGB28181ClientMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGB28181ClientMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGB28181ClientMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CGB28181ClientMDIView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGB28181ClientMDIView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CGB28181ClientMDIView ���

#ifdef _DEBUG
void CGB28181ClientMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGB28181ClientMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGB28181ClientMDIDoc* CGB28181ClientMDIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGB28181ClientMDIDoc)));
	return (CGB28181ClientMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CGB28181ClientMDIView ��Ϣ�������

/*
	DROPEFFECT_MOVE������������ڴ˴��ڣ�����ʱҪɾ��ԭҵ�Ķ���
	DROPEFFECT_COPY������������ڴ˴��ڣ�����ʱ��ɾ��ԭ���Ķ���
	DROPFFECT_NONE�� ������������ڴ˴���
*/

DROPEFFECT CGB28181ClientMDIView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���

	return DROPEFFECT_COPY;
	return CView::OnDragEnter(pDataObject, dwKeyState, point);
}

void CGB28181ClientMDIView::OnDragLeave()
{
	// TODO: �ڴ����ר�ô����/����û���

	CView::OnDragLeave();
}

DROPEFFECT CGB28181ClientMDIView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���

	return DROPEFFECT_COPY;

	return CView::OnDragOver(pDataObject, dwKeyState, point);
}

BOOL CGB28181ClientMDIView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���

	HGLOBAL hgMem = NULL; 
	if (pDataObject->IsDataAvailable(CF_TEXT))
	{
		hgMem = pDataObject->GetGlobalData(CF_TEXT);

		sipd_catalog_item * pItem = (sipd_catalog_item *)GlobalLock(hgMem);

		if (pItem != NULL)
		{
			int kkk = 1;
		}
	}
	GlobalUnlock(hgMem);

	return CView::OnDrop(pDataObject, dropEffect, point);
}

int CGB28181ClientMDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	m_CTreeDropTarget.Register(this);

	return 0;
}

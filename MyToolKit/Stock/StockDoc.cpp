
// StockDoc.cpp : CStockDoc ���ʵ��
//

#include "stdafx.h"
#include "Stock.h"

#include "StockDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CStockDoc

IMPLEMENT_DYNCREATE(CStockDoc, CDocument)

BEGIN_MESSAGE_MAP(CStockDoc, CDocument)
	
END_MESSAGE_MAP()


// CStockDoc ����/����

CStockDoc::CStockDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_nRowNumOfShareholding = 0;
	m_nRowNumOfFinanceReport = 0;
	m_nRowNum = 0;
}

CStockDoc::~CStockDoc()
{
}

BOOL CStockDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CStockDoc ���л�

void CStockDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CStockDoc ���

#ifdef _DEBUG
void CStockDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStockDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CStockDoc ����

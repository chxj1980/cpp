// AutoDownloadDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "AutoDownloadDoc.h"


// CAutoDownloadDoc

IMPLEMENT_DYNCREATE(CAutoDownloadDoc, CDocument)

CAutoDownloadDoc::CAutoDownloadDoc()
{
}

BOOL CAutoDownloadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAutoDownloadDoc::~CAutoDownloadDoc()
{
}


BEGIN_MESSAGE_MAP(CAutoDownloadDoc, CDocument)
END_MESSAGE_MAP()


// CAutoDownloadDoc ���

#ifdef _DEBUG
void CAutoDownloadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CAutoDownloadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CAutoDownloadDoc ���л�

void CAutoDownloadDoc::Serialize(CArchive& ar)
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
#endif


// CAutoDownloadDoc ����

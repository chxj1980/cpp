// StatsGovCnDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "StatsGovCnDoc.h"


// CStatsGovCnDoc

IMPLEMENT_DYNCREATE(CStatsGovCnDoc, CDocument)

CStatsGovCnDoc::CStatsGovCnDoc()
{
}

BOOL CStatsGovCnDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CStatsGovCnDoc::~CStatsGovCnDoc()
{
}


BEGIN_MESSAGE_MAP(CStatsGovCnDoc, CDocument)
END_MESSAGE_MAP()


// CStatsGovCnDoc ���

#ifdef _DEBUG
void CStatsGovCnDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CStatsGovCnDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CStatsGovCnDoc ���л�

void CStatsGovCnDoc::Serialize(CArchive& ar)
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


// CStatsGovCnDoc ����

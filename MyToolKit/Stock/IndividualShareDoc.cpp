// IndividualShareDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"


// CIndividualShareDoc

IMPLEMENT_DYNCREATE(CIndividualShareDoc, CDocument)

CIndividualShareDoc::CIndividualShareDoc()
{
	m_nCode = "-1";
	m_strInput = "";

	m_StartDate = COleDateTime::GetCurrentTime();
	m_EndDate = COleDateTime::GetCurrentTime();
}


CIndividualShareDoc::CIndividualShareDoc(string code, int command_code, int is_stock)
{
	m_nCode = code;
	m_nCommandCode = command_code;
	m_nIs_Stock = is_stock;
	m_strInput = "";

	m_vecCommandCode.clear();

	m_StartDate = COleDateTime::GetCurrentTime();
	m_EndDate = COleDateTime::GetCurrentTime();
}

BOOL CIndividualShareDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CIndividualShareDoc::~CIndividualShareDoc()
{
}


BEGIN_MESSAGE_MAP(CIndividualShareDoc, CDocument)
END_MESSAGE_MAP()


// CIndividualShareDoc ���

#ifdef _DEBUG
void CIndividualShareDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualShareDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CIndividualShareDoc ���л�

void CIndividualShareDoc::Serialize(CArchive& ar)
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


// CIndividualShareDoc ����

BOOL CIndividualShareDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������

	return TRUE;
}


// GB28181ClientMDIDoc.cpp : CGB28181ClientMDIDoc ���ʵ��
//

#include "stdafx.h"
#include "GB28181ClientMDI.h"

#include "GB28181ClientMDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGB28181ClientMDIDoc

IMPLEMENT_DYNCREATE(CGB28181ClientMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CGB28181ClientMDIDoc, CDocument)
END_MESSAGE_MAP()


// CGB28181ClientMDIDoc ����/����

CGB28181ClientMDIDoc::CGB28181ClientMDIDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGB28181ClientMDIDoc::CGB28181ClientMDIDoc(string strDeviceId)
{
	m_strDeviceId = strDeviceId;
}

CGB28181ClientMDIDoc::~CGB28181ClientMDIDoc()
{
}

BOOL CGB28181ClientMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGB28181ClientMDIDoc ���л�

void CGB28181ClientMDIDoc::Serialize(CArchive& ar)
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


// CGB28181ClientMDIDoc ���

#ifdef _DEBUG
void CGB28181ClientMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGB28181ClientMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGB28181ClientMDIDoc ����

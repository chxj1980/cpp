
// CxfSiTestDoc.cpp : CCxfSiTestDoc ���ʵ��
//

#include "stdafx.h"
#include "CxfSiTest.h"

#include "CxfSiTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCxfSiTestDoc

IMPLEMENT_DYNCREATE(CCxfSiTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CCxfSiTestDoc, CDocument)
END_MESSAGE_MAP()


// CCxfSiTestDoc ����/����

CCxfSiTestDoc::CCxfSiTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CCxfSiTestDoc::~CCxfSiTestDoc()
{
}

BOOL CCxfSiTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCxfSiTestDoc ���л�

void CCxfSiTestDoc::Serialize(CArchive& ar)
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


// CCxfSiTestDoc ���

#ifdef _DEBUG
void CCxfSiTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCxfSiTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCxfSiTestDoc ����

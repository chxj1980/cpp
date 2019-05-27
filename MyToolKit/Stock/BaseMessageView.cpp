// BaseMessageView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "BaseMessageElementsParser.h"
#include "BaseMessageView.h"

#include "FindStockByPinyin.h"

//////////////////////////////////////////////////////////////////////////
// CBaseMessageView

IMPLEMENT_DYNCREATE(CBaseMessageView, CView)

CBaseMessageView::CBaseMessageView()
{
	m_MessageCtrl.SetOwnerView(this);
}

CBaseMessageView::~CBaseMessageView()
{
}

BEGIN_MESSAGE_MAP(CBaseMessageView, CView)
	ON_MESSAGE(WM_USER_XML, OnUserXmlWParam)
	ON_MESSAGE(WM_USER_LOG_1, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_2, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_3, OnUserLogWParam_1)
	ON_WM_ACTIVATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
END_MESSAGE_MAP()


// CBaseMessageView ��ͼ

void CBaseMessageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CBaseMessageView ���

#ifdef _DEBUG
void CBaseMessageView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseMessageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseMessageView ��Ϣ�������


LRESULT CBaseMessageView::OnUserXmlWParam(WPARAM wParam, LPARAM lParam)
{
	return m_MessageCtrl.OnUserXmlWParam(wParam,lParam);
}


LRESULT CBaseMessageView::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	return m_MessageCtrl.OnUserLogWParam_1(wParam, lParam);
}


void CBaseMessageView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������

	/*����ȡ����ʱ���Զ�����ߵĹ�Ʊ���������Ѱ�Ҷ�Ӧ��*/

	CString strTitle;
	GetParent()->GetWindowText(strTitle);
	
	m_MessageCtrl.OnSetFocus(strTitle);

	//////////////////////////////////////////////////////////////////////////
	PostFocusChanged();
	
}

void CBaseMessageView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������

	
	PostFocusChanged();
}

BOOL CBaseMessageView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_CHAR )
	{
		TCHAR ch = pMsg->wParam;

		if(/*(ch >='A' && ch <='Z') ||*/ (ch >='a' && ch <='z'))
		{
			CFindStockByPinyin dlg;
			dlg.m_strPinyin = ch; 
			dlg.DoModal();

			if(dlg.m_strPinyin.GetLength()>6)
			{
				CString strCode = dlg.m_strPinyin.Mid(5).Left(6);
				m_MessageCtrl.FocusStockOnLeftPane(strCode.GetBuffer());
			}

			return TRUE;
		}
		
	}

	return CView::PreTranslateMessage(pMsg);
}

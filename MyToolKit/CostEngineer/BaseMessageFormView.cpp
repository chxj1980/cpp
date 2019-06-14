// BaseMessageFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CostEngineer.h"
#include "BaseMessageFormView.h"


// CBaseMessageFormView

IMPLEMENT_DYNCREATE(CBaseMessageFormView, CFormView)

CBaseMessageFormView::CBaseMessageFormView()
	: CFormView(CBaseMessageFormView::IDD)
{
	m_MessageCtrl.SetOwnerView(this);
}

CBaseMessageFormView::~CBaseMessageFormView()
{
}

void CBaseMessageFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_GRID, m_Grid);
	DDX_Control(pDX, IDC_GRID1, m_Grid1);
}

BEGIN_MESSAGE_MAP(CBaseMessageFormView, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_USER_XML, OnUserXmlWParam)
	
	ON_WM_ACTIVATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
	ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID1, OnGridDblClick1)
	ON_NOTIFY(NM_CLICK, IDC_GRID1, OnGridClick1)
END_MESSAGE_MAP()


// CBaseMessageFormView ���

#ifdef _DEBUG
void CBaseMessageFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseMessageFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseMessageFormView ��Ϣ�������

void CBaseMessageFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	ReLayout();
}

void CBaseMessageFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	ReLayout();
}

void CBaseMessageFormView::ReLayout()
{
	if (m_Grid.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = rect.top + (rect.bottom - rect.top) * 3 / 7 - 2;
		m_Grid.MoveWindow(rect);
		m_Grid.SetEditable(FALSE);

		GetClientRect(&rect);
		rect.top = rect.bottom - (rect.bottom - rect.top) * 4 / 7 + 2;
		m_Grid1.MoveWindow(rect);
		m_Grid1.SetEditable(FALSE);
	}
}



LRESULT CBaseMessageFormView::OnUserXmlWParam(WPARAM wParam, LPARAM lParam)
{
	return m_MessageCtrl.OnUserXmlWParam(wParam,lParam);
}


LRESULT CBaseMessageFormView::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	return m_MessageCtrl.OnUserLogWParam_1(wParam, lParam);
}


void CBaseMessageFormView::OnSetFocus(CWnd* pOldWnd)
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

void CBaseMessageFormView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������


	PostFocusChanged();
}




void CBaseMessageFormView::ProcessXmlWParam(string msgType,string code,string model,\
										 string param1,string param2,string param3)
{
	if(msgType=="TaskFinished")
	{
		stringstream ss;
		ss << "����" << (param1) << "�� �������. ";

		CCalculateTask * cse = CCalculateTask::FetchTask(atol(param1.c_str()));
		RedrawChart(cse);
		if(cse!=NULL)
			delete cse;
		//sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);
	}
	else if(msgType=="ReadFinished")
		RedrawDmGraph();
}


BOOL CBaseMessageFormView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���


	return CFormView::PreTranslateMessage(pMsg);
}



void CBaseMessageFormView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(str);
	
	if (pItem->iRow>0 && pItem->iColumn <1)
		PostGridDblClick(0, pItem->iRow);
}

//���ǵ�CTREECTRL�ؼ����ʱNM_CLICK�Ĵ�����
void CBaseMessageFormView::OnGridClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNMHDR;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pItem->iRow > 0 && pItem->iColumn > 0)
		PostGridClick(0, pItem->iRow, pItem->iColumn);

	*pResult = 0;
}

void CBaseMessageFormView::OnGridDblClick1(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(str);

	if (pItem->iRow>0 && pItem->iColumn <1)
		PostGridDblClick(1, pItem->iRow);
}

//���ǵ�CTREECTRL�ؼ����ʱNM_CLICK�Ĵ�����
void CBaseMessageFormView::OnGridClick1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNMHDR;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (pItem->iRow > 0 && pItem->iColumn > 0)
		PostGridClick(1, pItem->iRow, pItem->iColumn);

	*pResult = 0;
}
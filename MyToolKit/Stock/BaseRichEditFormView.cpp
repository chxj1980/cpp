// BaseRichEditFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "BaseRichEditFormView.h"

#include "FindStockByPinyin.h"


// CBaseRichEditFormView

IMPLEMENT_DYNCREATE(CBaseRichEditFormView, CFormView)

CBaseRichEditFormView::CBaseRichEditFormView()
	: CFormView(CBaseRichEditFormView::IDD)
{
	m_MessageCtrl.SetOwnerView(this);
}

CBaseRichEditFormView::~CBaseRichEditFormView()
{
}

void CBaseRichEditFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_GridCtrl);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEdit);
}

BEGIN_MESSAGE_MAP(CBaseRichEditFormView, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_USER_XML, OnUserXmlWParam)
	ON_MESSAGE(WM_USER_LOG_1, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_2, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_LOG_3, OnUserLogWParam_1)
	ON_WM_ACTIVATE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_BN_CLICKED(IDC_BTN_FIRST, &CBaseRichEditFormView::OnBnClickedBtnFirst)
	ON_BN_CLICKED(IDC_BTN_PAGEUP, &CBaseRichEditFormView::OnBnClickedBtnPageup)
	ON_BN_CLICKED(IDC_BTN_PAGEDOWN, &CBaseRichEditFormView::OnBnClickedBtnPagedown)
	ON_BN_CLICKED(IDC_BTN_LAST, &CBaseRichEditFormView::OnBnClickedBtnLast)
END_MESSAGE_MAP()


// CBaseRichEditFormView ���

#ifdef _DEBUG
void CBaseRichEditFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseRichEditFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseRichEditFormView ��Ϣ�������



void CBaseRichEditFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	ReLayout();
}

void CBaseRichEditFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	ReLayout();
}

void CBaseRichEditFormView::ReLayout()
{
	if (m_GridCtrl.GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = rect.top + (rect.bottom - rect.top) * 3 / 5 - 2;
		rect.top = rect.top + 40;
		m_GridCtrl.MoveWindow(rect);

		m_GridCtrl.ExpandLastColumn();
		m_GridCtrl.SetEditable(FALSE);

		GetClientRect(&rect);
		rect.top = rect.bottom - (rect.bottom - rect.top) * 2 / 5 + 2;
		m_RichEdit.MoveWindow(rect);
	}

	if(m_RichEdit.GetSafeHwnd())
	{
		//	����Ϊ����Ĭ������
		CHARFORMAT cfm;
		cfm.cbSize=sizeof(CHARFORMAT);
		cfm.yHeight=222;
		cfm.dwMask=CFM_FACE|CFM_SIZE|CFM_BOLD;
		//cfm.dwEffects=CFE_BOLD;
		strcpy_s(cfm.szFaceName, "Courier New"); 
		m_RichEdit.SetDefaultCharFormat(cfm);

		//	�����ض�ѡ��ʹ�õ� ����
		CHARFORMAT2 cf;
		ZeroMemory(&cf, sizeof CHARFORMAT2);
		cf.cbSize = sizeof(CHARFORMAT2);
		cf.dwMask |= CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = RGB(255,0,0);
		m_RichEdit.SetSelectionCharFormat(cf);

	}
}



LRESULT CBaseRichEditFormView::OnUserXmlWParam(WPARAM wParam, LPARAM lParam)
{
	return m_MessageCtrl.OnUserXmlWParam(wParam,lParam);
}


LRESULT CBaseRichEditFormView::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	return m_MessageCtrl.OnUserLogWParam_1(wParam, lParam);
}


void CBaseRichEditFormView::OnSetFocus(CWnd* pOldWnd)
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

void CBaseRichEditFormView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������


	PostFocusChanged();
}




void CBaseRichEditFormView::ProcessXmlWParam(string msgType,string code,string model,\
											string param1,string param2,string param3)
{
	if(msgType=="TaskFinished")
	{
		stringstream ss;
		ss << "����" << (param1) << "�� �������. ";

		CCalculateTask * cse = CCalculateTask::FetchTask(atol(param1.c_str()));
		RedrawGridCtrl(cse);
		if(cse!=NULL)
			delete cse;
		sendToOutput(ss.str().c_str(), NULL, WM_USER_LOG_1);
	}
	else if(msgType=="ReadFinished")
		RedrawDmGraph();
}


BOOL CBaseRichEditFormView::PreTranslateMessage(MSG* pMsg)
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

	return CFormView::PreTranslateMessage(pMsg);
}

void CBaseRichEditFormView::OnBnClickedBtnFirst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (m_nPageNo == 1)
	{
		AfxMessageBox(_T("���ǵ�һҳ"));
	}
	else
	{
		m_nPageNo = 1;
		OnPageUpdate();
	}
}

void CBaseRichEditFormView::OnBnClickedBtnPageup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(m_nPageNo==1)
	{
		AfxMessageBox(_T("���ǵ�һҳ"));
	}
	if(m_nPageNo>1)
	{
		m_nPageNo--;
		OnPageUpdate();
	}
}

void CBaseRichEditFormView::OnBnClickedBtnPagedown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_nPageNo++;	
	if (m_nPageNo > m_nMaxPage)
	{			
		m_nPageNo--;
		AfxMessageBox("�������һҳ");
		return;
	}
	OnPageUpdate();
}

void CBaseRichEditFormView::OnBnClickedBtnLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (m_nPageNo == m_nMaxPage)
	{
		AfxMessageBox("�������һҳ");
		return;
	}
	else
	{
		m_nPageNo = m_nMaxPage;
		OnPageUpdate();
	}	
}



void CBaseRichEditFormView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(str);
	//////////////////////////////////////////////////////////////////////////
	//	��Ʊͣ������ʾ��ǰѡ��� ��Ʊ

	if(pItem->iRow>0)
	{
		CString str = m_GridCtrl.GetItemText(pItem->iRow, 1);
		m_MessageCtrl.FocusStockOnLeftPane(str.GetBuffer());
	}
}
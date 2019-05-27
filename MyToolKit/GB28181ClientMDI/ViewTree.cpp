
#include "stdafx.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	m_pOleSourceObj = new COleDataSource ;
}

CViewTree::~CViewTree()
{
	if(m_pOleSourceObj)
		delete m_pOleSourceObj;
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CViewTree::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ�������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}



void CViewTree::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	switch (pNMCD->dwDrawStage)
	{
	case CDDS_PREPAINT:
		// Need to process this case and set pResult to CDRF_NOTIFYITEMDRAW, 
		// otherwise parent will never receive CDDS_ITEMPREPAINT notification. (GGH) 
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;

	case CDDS_ITEMPREPAINT:
		if(this->IsWindowEnabled()==1)
		{
			if ((pNMCD->uItemState & (CDIS_FOCUS))==0
				&&(pNMCD->uItemState & (CDIS_SELECTED))==CDIS_SELECTED) // selected
			{ 
				/*this->clrTextBk=RGB(255, 255, 255);
				pCustomDraw->clrText = RGB(0, 0, 0);*/
			}
			*pResult = CDRF_NOTIFYPOSTPAINT;
			return;
		}
		else{
			*pResult = CDRF_DODEFAULT ;
			return;
		}
	case CDDS_ITEMPOSTPAINT:
		if(this->IsWindowEnabled()==1)
		{
			if ((pNMCD->uItemState & (CDIS_FOCUS))==0
				&&(pNMCD->uItemState & (CDIS_SELECTED))==CDIS_SELECTED) // selected
			{
				CRect   rcText;  
				HTREEITEM hItem=(HTREEITEM) pNMCD->dwItemSpec;
				GetItemRect(hItem,   &rcText,   true); 
				CPen penBlue(PS_SOLID ,1,RGB(0, 0, 255));
				CDC* pDC=CDC::FromHandle(pNMCD->hdc); 
				CBrush* pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				CBrush* pOldBrush = pDC->SelectObject(pBrush);
				CPen* pOldPen = pDC->SelectObject(&penBlue);
				pDC->Rectangle(&rcText);
				pDC->SelectObject(pOldBrush);
				pDC->SelectObject(pOldPen);
			}
			else if((pNMCD->uItemState & CDIS_FOCUS)==0)
			{
				CRect   rcText;  
				HTREEITEM hItem=(HTREEITEM) pNMCD->dwItemSpec;
				CString strText = GetItemText(hItem);
				string tmp = strText.GetBuffer();
				if(tmp.find(_T("(��)"))!=string::npos || tmp.find(_T("(��)"))!=string::npos)
				{
					GetItemRect(hItem,   &rcText,   true); 
					CPen penBlue(PS_SOLID ,1,RGB(255, 0, 0));		//	������ͣ���� �� ��ֹ���� ʹ�� ��ɫ��
					CDC* pDC=CDC::FromHandle(pNMCD->hdc); 
					CBrush* pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
					CBrush* pOldBrush = pDC->SelectObject(pBrush);
					CPen* pOldPen = pDC->SelectObject(&penBlue);
					pDC->Rectangle(&rcText);
					pDC->SelectObject(pOldBrush);
					pDC->SelectObject(pOldPen);
				}

				
			}
			*pResult = CDRF_SKIPDEFAULT;
			return;
		}
		else{
			*pResult = CDRF_DODEFAULT ;
			return;
		}

	}

	*pResult = 0;
}



/*******************************************************************
OnBegindrag()
	Called when drag operation begins
********************************************************************/
void CViewTree::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hTSelItem = pNMTreeView->itemNew.hItem;
	// Highlight selected item
	SelectItem(hTSelItem);
	Select(hTSelItem, TVGN_DROPHILITE);
	
	//����ȫ�ֻ��棬�������汻�ϷŶ����������ݣ�����һ����С
	HGLOBAL hgMem = GlobalAlloc(GPTR, sizeof(sipd_catalog_item));

	char * htmpMem = (char*)GlobalLock(hgMem);
	ASSERT(htmpMem != NULL);

	ZeroMemory(htmpMem, sizeof(sipd_catalog_item));
	sipd_catalog_item * pItem = (sipd_catalog_item *)GetItemData(hTSelItem);
	if(pItem)
		memcpy(htmpMem, pItem, sizeof(sipd_catalog_item));	

	GlobalUnlock((HGLOBAL)hgMem);

	// �������
	m_pOleSourceObj->Empty();
	m_pOleSourceObj->CacheGlobalData(CF_TEXT, (HGLOBAL)htmpMem);

	// Begin Drag operation
	//	�����������أ�����Ҫ�ȵ���갴ť����֮��
	DROPEFFECT dropeffect = m_pOleSourceObj->DoDragDrop();

	// Remove the highlighting
	SendMessage(TVM_SELECTITEM, TVGN_DROPHILITE,0);
	// If user is moving item by pressing Shift, delete selected item
	/*if ( dropeffect == DROPEFFECT_MOVE)
		DeleteItem(hTSelItem); */

	*pResult = 0;
}



void CViewTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM hTSelItem =GetSelectedItem(); 
	
	sipd_catalog_item * pItem = (sipd_catalog_item *)GetItemData(hTSelItem);
	if(pItem)
	{
		CString msg;
		msg.Format("����:%s\r\nϵͳ����:%s\r\n��������:%s\r\n������:%s\r\n",
			pItem->device_id, pItem->Name, pItem->CivilCode, pItem->ParentID);

		AfxMessageBox(msg);

		/*HMODULE hUser32 = LoadLibrary(_T("user32.dll"));
		if(hUser32)
		{
			MessageBoxTimeout(NULL,msg,"¼��ʧ��",MB_OK, 0, 1*2000);
		}
		FreeLibrary(hUser32);*/
	}

	*pResult = 0;
}

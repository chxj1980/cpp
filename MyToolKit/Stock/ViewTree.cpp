
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
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CViewTree::OnNMCustomdraw)
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
				if(tmp.find("(��)")!=string::npos || tmp.find("(��)")!=string::npos)
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

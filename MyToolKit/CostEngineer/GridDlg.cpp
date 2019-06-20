// PDFStructureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CostEngineer.h"
#include "GridDlg.h"


// CPDFStructureDlg �Ի���

IMPLEMENT_DYNAMIC(CGridDlg, CDialog)

CGridDlg::CGridDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridDlg::IDD, pParent)
{
	m_strTitle = "";
}

CGridDlg::~CGridDlg()
{
}

void CGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CGridDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
END_MESSAGE_MAP()


// CPDFStructureDlg ��Ϣ�������

BOOL CGridDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(m_strTitle);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CCostEngineerApp * pApp = (CCostEngineerApp *)AfxGetApp();

	try {
		m_Grid.SetRowCount(m_vecData.size() + 1);
		m_Grid.SetColumnCount(m_vecHeader.size());
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(0);
		m_Grid.SetHeaderSort(FALSE);
		m_Grid.SetEditable(FALSE);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return TRUE;
	}

	for (int row = 0; row < m_Grid.GetRowCount(); row++)
	{
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (row < 1) {
				Item.nFormat = DT_LEFT | DT_WORDBREAK;

				Item.strText.Format(_T("%s"), m_vecHeader[col].c_str());
			}
			else
			{
				if (col == 0)
					Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				else
					Item.nFormat = DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;

				if (col >0)
				{
					if (!m_Grid.SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
						return TRUE;
				}

				Item.strText.Format(_T("%s   "), m_vecData[row-1][col].c_str());
			}

			m_Grid.SetItem(&Item);
		}

	}

	m_Grid.ExpandColumnsToFit();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CGridDlg::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	//Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);

	CString str;
	str.Format(_T("Context menu called on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	//AfxMessageBox(str);

	//////////////////////////////////////////////////////////////////////////
	//	��ѡ�еĵ�Ԫ������ ������ ������

	CString source = m_Grid.GetItemText(pItem->iRow, pItem->iColumn);
	if (OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, source.GetLength() + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(source));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}

}

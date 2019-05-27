// DealDetailDateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "DealDetailDateDlg.h"


// CDealDetailDateDlg �Ի���

IMPLEMENT_DYNAMIC(CDealDetailDateDlg, CDialog)

CDealDetailDateDlg::CDealDetailDateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDealDetailDateDlg::IDD, pParent)
{

}

CDealDetailDateDlg::~CDealDetailDateDlg()
{
}

void CDealDetailDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}


BEGIN_MESSAGE_MAP(CDealDetailDateDlg, CDialog)
END_MESSAGE_MAP()


// CDealDetailDateDlg ��Ϣ�������

BOOL CDealDetailDateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	string tablename = "";
	try{
		string test = "select search_table('sinadealdetail_') as table_name from dual ";
		session sql(g_MysqlPool);
		row r;
		statement st = (sql.prepare << test,into(r)) ;
		st.execute();

		st.fetch();
		tablename = r.get<string>("table_name");
	}
	catch(...){}


	vector<string>	vecTablename;
	splitString(tablename, ",", vecTablename);

	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	m_Grid.SetRowCount(vecTablename.size() + 1);
	m_Grid.SetColumnCount(1);

	m_Grid.SetFixedRowCount(1);
	m_Grid.SetFixedColumnSelection(FALSE);
	m_Grid.SetFixedRowSelection(FALSE);
	m_Grid.EnableColumnHide();
	m_Grid.SetEditable(FALSE);

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 0;
	Item.col = 0;
	Item.strText.Format(_T("%s"), "ϵͳ�д������ݵ�����");
	m_Grid.SetItem(&Item);

	for(int i=0; i<vecTablename.size(); i++)
	{
		GV_ITEM Item;
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
		Item.row = i+1;
		Item.col = 0;
		Item.strText.Format(_T("%s"), vecTablename[i].substr(strlen("sinadealdetail_")).c_str());
		m_Grid.SetItem(&Item);
	}

	
	m_Grid.AutoSize();
	m_Grid.SetCompareFunction(CGridCtrl::pfnCellNumericCompare);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDealDetailDateDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnOK();

	int selected = m_Grid.GetSelectedCount();
	if(selected>0)
	{
		for (int row = 0; row < m_Grid.GetRowCount(); row++)
		{
			for (int col = 0; col < m_Grid.GetColumnCount(); col++)
			{
				if(m_Grid.IsCellSelected(row, col))
				{
					CString str = m_Grid.GetItemText(row, col);
					m_strDealDetailDate = str.GetBuffer();
					return;
				}
			}
		}
	}
	m_strDealDetailDate = "";
}

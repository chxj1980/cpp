// StockRangeSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "StockRangeSet.h"


// CStockRangeSet �Ի���

IMPLEMENT_DYNAMIC(CStockRangeSet, CDialog)

CStockRangeSet::CStockRangeSet(CWnd* pParent /*=NULL*/)
	: CDialog(CStockRangeSet::IDD, pParent)
	, m_StartDate(COleDateTime::GetCurrentTime())
	, m_End_Date(COleDateTime::GetCurrentTime())
{

}

CStockRangeSet::~CStockRangeSet()
{
}

void CStockRangeSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_StartDate);
	DDX_DateTimeCtrl(pDX, IDC_END_DATE, m_End_Date);
	DDX_Control(pDX, IDC_LIST_VIEWTYPE, m_listViewType);
}


BEGIN_MESSAGE_MAP(CStockRangeSet, CDialog)
END_MESSAGE_MAP()


// CStockRangeSet ��Ϣ�������

BOOL CStockRangeSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	LONG lStyle;
	lStyle = GetWindowLong(m_listViewType.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK;	//�����ʾ��ʽλ
	lStyle |= LVS_REPORT;		//����style
	SetWindowLong(m_listViewType.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_listViewType.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;		//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;		//itemǰ����checkbox�ؼ�
	m_listViewType.SetExtendedStyle(dwStyle);	//������չ���

	m_listViewType.InsertColumn(0,"��������",LVCFMT_LEFT,100);
	
	int nRow = m_listViewType.InsertItem(0, "Open");//������
	m_listViewType.InsertItem(1, "High");
	m_listViewType.InsertItem(2, "Low");
	m_listViewType.InsertItem(3, "Close");
	m_listViewType.InsertItem(4, "PE");
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CStockRangeSet::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	int k = m_listViewType.GetItemCount();
	m_strViewType = "";
	for(int i=0; i<k; i++)
	{
		if(m_listViewType.GetCheck(i))
		{
			char tmp[128];
			memset(tmp, 0 ,128);
			m_listViewType.GetItemText(i, 0, tmp,128);
			if(m_strViewType.empty()==false)
				m_strViewType += ",";
			m_strViewType += string(tmp);
		}
	}

	CDialog::OnOK();
}

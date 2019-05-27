// StockGroupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "StockGroupDlg.h"


// CStockGroupDlg �Ի���

IMPLEMENT_DYNAMIC(CStockGroupDlg, CDialog)

CStockGroupDlg::CStockGroupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockGroupDlg::IDD, pParent)
	, m_RadioReg(-1)
	, m_RadioCsrc(-1)
{

}

CStockGroupDlg::~CStockGroupDlg()
{
}

void CStockGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_REG, m_TreeReg);
	DDX_Radio(pDX, IDC_RADIO_NATION, m_RadioReg);
	DDX_Radio(pDX, IDC_RADIO_CSRC_GATE, m_RadioCsrc);
	DDX_Control(pDX, IDC_TREE_CSRC, m_TreeCsrc);
}


BEGIN_MESSAGE_MAP(CStockGroupDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_NATION, &CStockGroupDlg::OnBnClickedRadioReg)
	ON_BN_CLICKED(IDC_RADIO_PROVINCE, &CStockGroupDlg::OnBnClickedRadioReg)
	ON_NOTIFY(NM_CLICK, IDC_TREE_REG, &CStockGroupDlg::OnNMClickTreeReg)
	ON_BN_CLICKED(IDC_RADIO_CSRC_GATE, &CStockGroupDlg::OnBnClickedRadioCsrc)
	ON_BN_CLICKED(IDC_RADIO_CSRC_BIG, &CStockGroupDlg::OnBnClickedRadioCsrc)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CSRC, &CStockGroupDlg::OnNMClickTreeCsrc)
END_MESSAGE_MAP()


// CStockGroupDlg ��Ϣ�������



BOOL CStockGroupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//////////////////////////////////////////////////////////////////////////
	//	չʾ ����ʡ��
	{
		CStatsGovCn  statsGovCn;
		map<string, string> map_RegName = statsGovCn.GetOtherWds("test", "test");

		CString str;
		str.Format("%s-(%s)",  "�й�", "86");
		HTREEITEM hClass = m_TreeReg.InsertItem(str, 1, 1);
		HTREEITEM hRoot = hClass;
		m_TreeReg.SetItemData(hClass, 0);

		map<string, string>::iterator it = map_RegName.begin();
		for(; it!=map_RegName.end(); it++)
		{
			str.Format("%s-(%s)",  it->second.c_str(), it->first.c_str());
			HTREEITEM hClass = m_TreeReg.InsertItem(str,hRoot, TVI_LAST);
			m_TreeReg.SetItemData(hClass, 1);
		}

		m_TreeReg.Expand(hRoot, TVE_EXPAND /*TVE_COLLAPSE*/);
		if(m_RadioReg<0)
			m_TreeReg.EnableWindow(FALSE);
	}

	//////////////////////////////////////////////////////////////////////////
	//	չʾ��֤�����ҵ�� ��
	{
		vector<CStockPlateData> vecStockPlateData;
		CStockPlateTree * pPlates = ((CStockApp *)AfxGetApp())->m_pCsindexCsrcStockPlates;

		if(pPlates)
		{	
			//	��ĳ���ڵ�Ϊ������������������
			CStockPlateData treeNode;
			treeNode.code = Int2String(0, "%08d");
			treeNode.is_stock = 0;

			CStockPlateTree * pNode = pPlates->SearchSpecialNode(treeNode);
			if(pNode==NULL)
				pNode = pPlates;
			if(pNode)
			{
				//	�ýڵ�Ϊ���ڵ�
				CStockPlateData spd = *pNode->get();
				spd.code = Int2String(0, "%08d");
				spd.parent_code = "-1";
				spd.is_stock = 0;
				spd.company_number = -1;		//	��Ϊ���Ĳ㼶ʹ��
				if(spd.name.empty())
					spd.name = "��Ŀ¼";
				vecStockPlateData.push_back(spd);

				CStockPlateTree::pre_order_iterator pre_order_it = pNode->pre_order_begin();
				while(pre_order_it!=pNode->pre_order_end())
				{
					CStockPlateData spd = *pre_order_it;
					if(spd.is_stock==0)
					{
						if(pre_order_it.node()->parent()->is_root()==false)
						{
							spd.parent_code = pre_order_it.node()->parent()->get()->code;
						}
						else
						{
							spd.parent_code = Int2String(0, "%08d");
						}
						if(spd.code.length()==1)
							spd.company_number = 0;		//	����
						else
							spd.company_number = 1;		//	����
						vecStockPlateData.push_back(spd);
					}
					
					pre_order_it++;
				}

			}
		}

		HTREEITEM hRoot;
		map<string, HTREEITEM> mapHTree;
		for(int i =0 ; i<vecStockPlateData.size(); i++)
		{
			CString str;
			if(vecStockPlateData[i].is_stock==1)
			{
				str.Format("%s-%d(%s)",vecStockPlateData[i].name.c_str(),\
					vecStockPlateData[i].company_number, vecStockPlateData[i].code.c_str());
			}
			else
			{
				str.Format("%s-%d(%s)",vecStockPlateData[i].name.c_str(),\
					vecStockPlateData[i].company_number, vecStockPlateData[i].code.c_str());
			}

			if(vecStockPlateData[i].parent_code== "-1")
			{
				HTREEITEM hClass = m_TreeCsrc.InsertItem(str, 1, 1);
				hRoot = hClass;

				CString key;
				if(vecStockPlateData[i].is_stock==1)
					key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
				else
					key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
				mapHTree.insert(make_pair(string(key.GetBuffer()), hClass));

				m_TreeCsrc.SetItemData(hClass, (DWORD_PTR)vecStockPlateData[i].company_number);
			}
			else
			{
				CString key;
				key.Format("%s-%d", vecStockPlateData[i].parent_code.c_str(), 0);
				HTREEITEM hParent = mapHTree[string(key.GetBuffer())];
				HTREEITEM hClass = m_TreeCsrc.InsertItem(str, hParent, TVI_LAST);

				if(vecStockPlateData[i].is_stock==1)
					key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
				else
					key.Format("%s-%d", vecStockPlateData[i].code.c_str(), vecStockPlateData[i].is_stock);
				mapHTree.insert(make_pair(string(key.GetBuffer()), hClass));

				m_TreeCsrc.SetItemData(hClass, (DWORD_PTR)vecStockPlateData[i].company_number);
			}
		}

		m_TreeCsrc.Expand(hRoot, TVE_EXPAND /*TVE_COLLAPSE*/);
		if(m_RadioCsrc<0)
			m_TreeCsrc.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CStockGroupDlg::DisplayCheckBoxByRadio(HTREEITEM hitem, int nRadio)
{
	if(hitem != NULL)
	{
		HTREEITEM old_hitem = hitem;

		int nLevel = (int)m_TreeReg.GetItemData(hitem);
		if(nLevel==nRadio)
		{
			// ��ʾ����ѡ����Ĭ��Ϊ��ѡ�С�״̬
			m_TreeReg.SetItemState(hitem, 0x2000,  TVIS_STATEIMAGEMASK);
		}
		else
		{
			//	����ʡ��ȥ������ѡ���򣬲���ѡ��
			m_TreeReg.SetItemState(hitem, 0,  TVIS_STATEIMAGEMASK);
		}

		hitem = m_TreeReg.GetChildItem(hitem);
		while(hitem)
		{
			DisplayCheckBoxByRadio(hitem, nRadio);
			hitem = m_TreeReg.GetNextItem(hitem, TVGN_NEXT);
		}

		if(m_TreeReg.ItemHasChildren(old_hitem))
			m_TreeReg.Expand(old_hitem, TVE_EXPAND /*TVE_COLLAPSE*/);
	}
}

//�ݹ鷴��ѡ�񡰹�ѡ��
void CStockGroupDlg::UpdateCheckBoxByRadio(HTREEITEM hitem, int nRadio)
{
	if(hitem!=NULL)
	{
		int nLevel = m_TreeReg.GetItemData(hitem);
		if (nLevel < nRadio)
		{
			HTREEITEM hChildItem = NULL; 
			if (m_TreeReg.ItemHasChildren(hitem)) 
			{ 
				hChildItem =m_TreeReg.GetChildItem(hitem); 
				while(hChildItem!=NULL) 
				{ 
					
					UpdateCheckBoxByRadio(hChildItem, nRadio);
					hChildItem =m_TreeReg.GetNextItem(hChildItem, TVGN_NEXT);    
				}    
			} 
		}
		else if(nLevel==nRadio)
		{
			bool oldStatus = m_TreeReg.GetCheck(hitem);
			m_TreeReg.SetCheck(hitem, !oldStatus);
		}
	}
	
}


void CStockGroupDlg::GetSelectedHitemByRadio(HTREEITEM hitem, int nRadio, vector<string> & vecItem)
{
	if(hitem != NULL)
	{
		int nLevel = (int)m_TreeReg.GetItemData(hitem);
		bool bChecked = m_TreeReg.GetCheck(hitem);
		if(nLevel==nRadio && bChecked)
		{
			CString text = m_TreeReg.GetItemText(hitem);
			vecItem.push_back(text.GetBuffer());
		}
		
		hitem = m_TreeReg.GetChildItem(hitem);
		while(hitem)
		{
			GetSelectedHitemByRadio(hitem, nRadio, vecItem);
			hitem = m_TreeReg.GetNextItem(hitem, TVGN_NEXT);
		}
	}
}

void CStockGroupDlg::OnBnClickedRadioReg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if(m_RadioReg>=0)
		m_TreeReg.EnableWindow(TRUE);

	/*�������е����ڵ㣬��Ӧ�Ĳ㼶��ʾ����ѡ�����������ء���ѡ����*/
	HTREEITEM hroot = m_TreeReg.GetRootItem();
	DisplayCheckBoxByRadio(hroot, m_RadioReg);

	m_TreeReg.Expand(hroot, TVE_COLLAPSE /*TVE_COLLAPSE*/);
	m_TreeReg.Expand(hroot, TVE_EXPAND /*TVE_COLLAPSE*/);
}



void CStockGroupDlg::OnNMClickTreeReg(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CPoint point;
	GetCursorPos(&point);			//����������λ��
	m_TreeReg.ScreenToClient(&point);	//ת��Ϊ�ͻ�����
	UINT uFlags;

	HTREEITEM CurrentItem;
	CurrentItem=m_TreeReg.HitTest(point,&uFlags);//��õ�ǰ����ڵ��ITEM

	UpdateData(TRUE);
	UpdateCheckBoxByRadio(CurrentItem,m_RadioReg);

	m_TreeReg.Expand(CurrentItem, TVE_COLLAPSE /*TVE_COLLAPSE*/);
	m_TreeReg.Expand(CurrentItem, TVE_EXPAND /*TVE_COLLAPSE*/);

	*pResult = 0;
}



void CStockGroupDlg::OnBnClickedRadioCsrc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_RadioCsrc>=0)
		m_TreeCsrc.EnableWindow(TRUE);

	/*�������е����ڵ㣬��Ӧ�Ĳ㼶��ʾ����ѡ�����������ء���ѡ����*/
	HTREEITEM hroot = m_TreeCsrc.GetRootItem();
	DisplayCheckBoxByRadio(hroot, m_RadioCsrc);

	m_TreeCsrc.Expand(hroot, TVE_COLLAPSE /*TVE_COLLAPSE*/);
	m_TreeCsrc.Expand(hroot, TVE_EXPAND /*TVE_COLLAPSE*/);

	
}


void CStockGroupDlg::OnNMClickTreeCsrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint point;
	GetCursorPos(&point);			//����������λ��
	m_TreeCsrc.ScreenToClient(&point);	//ת��Ϊ�ͻ�����
	UINT uFlags;

	HTREEITEM CurrentItem;
	CurrentItem=m_TreeCsrc.HitTest(point,&uFlags);//��õ�ǰ����ڵ��ITEM

	UpdateData(TRUE);
	UpdateCheckBoxByRadio(CurrentItem,m_RadioCsrc);

	m_TreeCsrc.Expand(CurrentItem, TVE_COLLAPSE /*TVE_COLLAPSE*/);
	m_TreeCsrc.Expand(CurrentItem, TVE_EXPAND /*TVE_COLLAPSE*/);

	*pResult = 0;
}


void CStockGroupDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);

	HTREEITEM hroot = m_TreeReg.GetRootItem();
	if(m_RadioReg==1)
		GetSelectedHitemByRadio(hroot, m_RadioReg, m_vecSelectedItemReg);

	hroot = m_TreeCsrc.GetRootItem();
	if(m_RadioCsrc==0)
		GetSelectedHitemByRadio(hroot, m_RadioCsrc, m_vecSelectedItemCsrcGate);
	if(m_RadioCsrc==1)
		GetSelectedHitemByRadio(hroot, m_RadioCsrc, m_vecSelectedItemCsrcBig);

	CDialog::OnOK();
}
#include "stdafx.h"
#include "CompositeUnitPrice.h"
#include "GridDlg.h"


CCompositeUnitPriceObj::CCompositeUnitPriceObj()
{
	m_unit_price = 0;
	m_quantity = 0;
	m_name = "";
	m_unit = "";
}


CCompositeUnitPriceObj::~CCompositeUnitPriceObj()
{
}



void CCompositeUnitPriceObj::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_unit_price;
		ar << m_quantity;
		ar << m_name;
		ar << m_unit;
	}
	else {
		ar >> m_unit_price;
		ar >> m_quantity;
		ar >> m_name;
		ar >> m_unit;
	}
}




bool CCompositeUnitPriceObj::CreateOrUpdate(string menuCode) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 50;
	infd.CXEDIT = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��λ"), 64);
	if (!m_unit.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_unit;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������"), 64);
	if (m_quantity > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_quantity);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);
	if (m_unit_price > 0 )
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_unit_price);
	infd.m_vecFindItem[0][i][0].dbMin = 0;
	infd.m_vecFindItem[0][i][0].dbMax = 10000;

	
	infd.Init(_T("�������� ��������"), _T("�������� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_name = infd.m_vecFindItem[0][i++][0].strItem;
		m_unit = infd.m_vecFindItem[0][i++][0].strItem;
		m_quantity = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_unit_price = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		
		return true;
	}
	return false;
}

bool CCompositeUnitPriceObj::Draw(CGridCtrl* pGridCtrl, vector<CCompositeUnitPriceObj>& cols) {
	if (!pGridCtrl)
		return false;


	try {
		pGridCtrl->SetRowCount(cols.size() + 1);
		pGridCtrl->SetColumnCount(4 + 3);		//	������������ �� ���/�޸�/ɾ��
		pGridCtrl->SetFixedRowCount(1);
		pGridCtrl->SetFixedColumnCount(1);
		pGridCtrl->SetHeaderSort(TRUE);
		pGridCtrl->SetEditable(FALSE);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return false;
	}

	for (int row = 0; row < pGridCtrl->GetRowCount(); row++)
	{
		for (int col = 0; col < pGridCtrl->GetColumnCount(); col++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nMargin = 10;
			string val;

			if (row < 1) {
				Item.nFormat = DT_LEFT | DT_WORDBREAK;

				if (col == 0)		val = "����������(10������)";
				else if (col == 1)	val = "����";
				else if (col == 2)	val = "��λ";
				else if (col == 3)	val = "������";
				else if (col == 4)	val = "����";
				else if (col == 5)	val = "";
				else if (col == 6)	val = "";


				Item.strText.Format(_T("%s"), val.c_str());
			}
			else
			{
				if (col <= 2)
					Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				else
					Item.nFormat = DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;

				if (col >= 3 && col <= 4 || col == 0)
				{
					if (!pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
						return false;
				}
				if (col == 5) {
					Item.crFgClr = RGB(0, 120, 250);
					Item.mask |= GVIF_FGCLR;
				}
				if (col == 6) {
					Item.crFgClr = RGB(255, 0, 0);
					Item.mask |= GVIF_FGCLR;
				}

				if (col == 0)	val = Int2String(row);
				else if (col == 1) 	val = cols[row - 1].m_name.GetBuffer();
				else if (col == 2) 	val = cols[row - 1].m_unit.GetBuffer();
				else if (col == 3)  val = Double2String(cols[row - 1].m_quantity);
				else if (col == 4)  val = Double2String(cols[row - 1].m_unit_price);
				else if (col == 5)	val = "�޸ģ�update��";
				else if (col == 6)	val = "ɾ����delete��";

				Item.strText.Format(_T("%s"), val.c_str());
			}
			pGridCtrl->SetItem(&Item);
		}
	}
	//pGridCtrl->AutoFill();
	pGridCtrl->Refresh();
	pGridCtrl->ExpandColumnsToFit();
	return true;
}

bool CCompositeUnitPriceObj::Update(string menuCode, int nRow, vector<CCompositeUnitPriceObj>& cols) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return cols[nRow - 1].CreateOrUpdate(menuCode);
	return false;
}


bool CCompositeUnitPriceObj::Delete(string menuCode, int nRow, vector<CCompositeUnitPriceObj>& cols) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		int idx = 0;
		vector<CCompositeUnitPriceObj>::iterator it = cols.begin();
		for (; it != cols.end(); it++, idx++) {
			if (idx == nRow - 1)
				break;
		}
		cols.erase(it);
		return true;
	}
	return false;
}


/***********************************************************************************/


/* �ۺϵ��۷����� */
string CCompositeUnitPrice::m_ObjectCode = "01030901";
double CCompositeUnitPrice::m_ObjectVersion = 1.0;

CCompositeUnitPrice::CCompositeUnitPrice()
{
	m_name = "";
	m_formula_quantity = 0;
	m_consumption_quantity = 0;
}


CCompositeUnitPrice::~CCompositeUnitPrice()
{
}




void CCompositeUnitPrice::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_formula_quantity;
		ar << m_consumption_quantity;
		ar << m_name;
		ar << m_materials.size();
		for (int i = 0; i < m_materials.size(); i++) {
			m_materials[i].Serialize(ar, version);
		}
	}
	else {
		ar >> m_formula_quantity;
		ar >> m_consumption_quantity;
		ar >> m_name;
		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CCompositeUnitPriceObj bs;
			bs.Serialize(ar, version);
			m_materials.push_back(bs);
		}
	}
}

bool CCompositeUnitPrice::CreateOrUpdate(string menuCode) {

	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.CXEDIT = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������淶������"), 64);
	if (m_formula_quantity > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_formula_quantity);
	infd.m_vecFindItem[0][i][0].dbMin = 0.0001;
	infd.m_vecFindItem[0][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���������������"), 64);
	if (m_consumption_quantity > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_consumption_quantity);
	infd.m_vecFindItem[0][i][0].dbMin = 1;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	infd.Init(_T("�ۺϵ��۷����� ��������"), _T("�ۺϵ��۷����� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_name = infd.m_vecFindItem[0][i++][0].strItem;
		m_formula_quantity = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_consumption_quantity = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}




bool CCompositeUnitPrice::Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CCompositeUnitPrice>& cols) {
	if (!pGridCtrl)
		return false;

	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	try {
		pGridCtrl->SetRowCount(cols.size() + 1);
		pGridCtrl->SetColumnCount(3 + 4);		//	��������4�� �� ���/�޸�/ɾ��/����
		pGridCtrl->SetFixedRowCount(1);
		pGridCtrl->SetFixedColumnCount(1);
		pGridCtrl->SetHeaderSort(TRUE);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return false;
	}

	for (int row = 0; row < pGridCtrl->GetRowCount(); row++)
	{
		for (int col = 0; col < pGridCtrl->GetColumnCount(); col++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nMargin = 10;
			string val;

			if (row < 1) {
				Item.nFormat = DT_LEFT | DT_WORDBREAK;

				if (col == 0)		val = "�ۺϵ��۷�����";
				else if (col == 1)	val = "����";
				else if (col == 2)	val = "�������淶������";
				else if (col == 3)	val = "���������������";
				else if (col == 4)	val = "";
				else if (col == 5)	val = "";
				else if (col == 6)	val = "";

				Item.strText.Format(_T("%s"), val.c_str());
			}
			else
			{
				if (col <= 2)
					Item.nFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;
				else
					Item.nFormat = DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX;

				if (col >= 2 && col <= 3 || col == 0)
				{
					if (!pGridCtrl->SetCellType(row, col, RUNTIME_CLASS(CGridCellNumeric)))
						return false;
				}
				if (col == 4 || col == 6) {
					Item.crFgClr = RGB(0, 120, 250);
					Item.mask |= GVIF_FGCLR;
				}
				if (col == 5) {
					Item.crFgClr = RGB(255, 0, 0);
					Item.mask |= GVIF_FGCLR;
				}

				if (col == 0)	val = Int2String(row);
				else if (col == 1) 	val = cols[row - 1].m_name.GetBuffer();
				else if (col == 2)  val = Double2String(cols[row - 1].m_formula_quantity, "%.2f");
				else if (col == 3)  val = Double2String(cols[row - 1].m_consumption_quantity, "%.2f");
				
				else if (col == 4)	val = "�޸ģ�update��";
				else if (col == 5)	val = "ɾ����delete��";
				else if (col == 6)	val = "���ӣ�create��";

				Item.strText.Format(_T("%s"), val.c_str());
			}
			pGridCtrl->SetItem(&Item);
		}
	}
	//pGridCtrl->AutoFill();
	pGridCtrl->Refresh();
	pGridCtrl->ExpandColumnsToFit();
	return true;
}

bool CCompositeUnitPrice::Update(string menuCode, int nRow, vector<CCompositeUnitPrice>& cols) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return cols[nRow - 1].CreateOrUpdate(CCompositeUnitPrice::m_ObjectCode);
	return false;
}

bool CCompositeUnitPrice::Delete(string menuCode, int nRow, vector<CCompositeUnitPrice>& cols) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		int idx = 0;
		vector<CCompositeUnitPrice>::iterator it = cols.begin();
		for (; it != cols.end(); it++, idx++) {
			if (idx == nRow - 1)
				break;
		}
		cols.erase(it);
		return true;
	}
	return false;
}


unsigned int CCompositeUnitPrice::PopupMenuId(string menuCode) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return 0;
	return IDR_POPUP_COMPONENT;
}



void CCompositeUnitPrice::Calculate(string menuCode, vector<CCompositeUnitPrice>& cols) {
	if (menuCode != CCompositeUnitPrice::m_ObjectCode)
		return;

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("����");
	gridDlg.m_vecHeader.push_back("�������");
	

	for (int i = 0; i < cols.size(); i++)
	{
		CCompositeUnitPrice seb = cols[i];

		string str = seb.m_name.GetBuffer();
		vector<string> vec;
		vec.push_back(str);
		
		// ���ķ�
		double material = 0;
		double people = 0;
		double machine = 0;

		for (auto e : seb.m_materials)
		{
			if (e.m_unit.Find("����")>=0) {
				people += e.m_quantity * e.m_unit_price;
			} else if (e.m_unit.Find("̨��") >= 0) {
				machine += e.m_quantity * e.m_unit_price;
			} else 
				material += e.m_quantity * e.m_unit_price ;
		}
		// ��ȫ����ʩ����
		double  measure1 = (people + machine) * 0.12;
		// �����ܼ۴�ʩ��
		double	measure2 = (people + machine) * 0.08;
		// �����
		double manage = (people + machine + measure2 * 0.45) * 0.15;
		// ����
		double net = (people + machine + measure2 * 0.45) * 0.1;
		// ���
		double government = (people + measure2 * 0.35) * 0.15;
		// ��ֵ˰
		double tax = net * 0.11;
		
		double total = material + people + machine + measure1 + measure2 + manage + net + government + tax + 3000;
		
		vec.push_back(Double2String(total));
		gridDlg.m_vecData.push_back(vec);
	}
	gridDlg.DoModal();
}
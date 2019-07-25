#include "stdafx.h"
#include "ContractPrice.h"
#include "GridDlg.h"




//
//int CContractPriceObj::EarliestPaymentTime() {
//
//	return 0;
//}
//
//int CContractPriceObj::LatestPaymentTime() {
//	return 0;
//}

/***********************************************************************************/


/* ������ - ���̽��� */
string CContractPrice::m_ObjectCode = "01060501";
double CContractPrice::m_ObjectVersion = 1.0;

CContractPrice::CContractPrice()
{
	m_scheme = "";
}


CContractPrice::~CContractPrice()
{
	for (CContractPriceObj* e : m_objs)
		delete e;
}

unsigned int CContractPrice::PopupMenuId(string menuCode) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return 0;
	return IDR_POPUP_COMPONENT;
}

CContractPrice* CContractPrice::NewParent(CString scheme) {
	CContractPrice* p = NULL;
	if (scheme == "����5")
		p = new CContractPriceEx2();
	if (p) p->m_scheme = scheme;
	return p;
}


bool CContractPrice::Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CContractPrice*>& cols) {
	if (!pGridCtrl)
		return false;

	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	vector<string> vecHeader;
	vector<vector<string>> vecData;
	vecHeader.push_back("���̽��㷽��,120");
	vecHeader.push_back("��������,550");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");

	int i = 1;
	for (CContractPrice* e : cols) {
		vector<string> vec;
		vec.push_back(e->m_scheme.GetBuffer());
		vec.push_back(e->Description());
		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");
		vec.push_back("���ӣ�create��");
		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}

void CContractPrice::Serialize(CArchive& ar, double version, CContractPrice*  & p) {
	if (ar.IsStoring()) {
		ar << p->m_scheme;
		p->Serialize(ar, version);
	}
	else {
		CString scheme;
		ar >> scheme;
		p = NewParent(scheme);
		p->Serialize(ar, version);
	}
}


void CContractPrice::Calculate(string menuCode, vector<CContractPrice*>& cols) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return;

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("����");
	gridDlg.m_vecHeader.push_back("�������");


	for (int i = 0; i < cols.size(); i++)
	{


		/*vec.push_back(Double2String(total));
		gridDlg.m_vecData.push_back(vec);*/
	}
	gridDlg.DoModal();
}

bool CContractPrice::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;

	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}


CContractPriceObj* CContractPrice::NewChild(CString scheme) {
	CContractPriceObj* p = NULL;
	
	return p;
}

bool CContractPrice::AddChild(string menuCode) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "���۷����;���۴�ʩ��;�ܼ۴�ʩ��;������Ŀ��";
	infd.m_vecFindItem[0][i][0].strItem = "���۷����";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	infd.Init(_T("��ͬ�ۿ� ����ѡ��"), _T("��ͬ�ۿ� ����ѡ��"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString scheme = infd.m_vecFindItem[0][i++][0].strItem;
		CContractPriceObj* c = NewChild(scheme);
		if (c->CreateOrUpdate(menuCode, this)) {
			m_objs.push_back(c);
			return true;
		}
		else {
			delete c;
		}
	}

	return false;
}

bool CContractPrice::UpdateChild(string menuCode, int nRow) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size())
		return m_objs[nRow - 1]->CreateOrUpdate(menuCode, this);
	return false;
}


bool CContractPrice::DeleteChild(string menuCode, int nRow) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		int idx = 0;
		vector<CContractPriceObj*>::iterator it = m_objs.begin();
		for (; it != m_objs.end(); it++, idx++) {
			if (idx == nRow - 1)
				break;
		}
		m_objs.erase(it);
		return true;
	}
	return false;
}


/* "����" ���ģʽ */
bool CContractPrice::Create(string strMenuCode, CContractPrice*  & p) {
	if (strMenuCode != CContractPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "����5";
	infd.m_vecFindItem[0][i][0].strItem = "����5";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	infd.Init(_T("��ͬ�ۿ� ����ѡ��"), _T("��ͬ�ۿ� ����ѡ��"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString scheme = infd.m_vecFindItem[0][i++][0].strItem;
		p = NewParent(scheme);
		bool res = p->CreateOrUpdate();
		if (res == false) {
			delete p;
			p = NULL;
		}
		return res;
	}

	return false;
}

bool CContractPrice::Update(string menuCode, int nRow, vector<CContractPrice*>& cols) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return  cols[nRow - 1]->CreateOrUpdate();
	return false;
}

bool CContractPrice::Delete(string menuCode, int nRow, vector<CContractPrice*>& cols) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		int idx = 0;
		vector<CContractPrice*>::iterator it = cols.begin();
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

void CContractPriceEx2ObjA::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_actual_workload;
		ar << m_unit_price;
	}
	else {
		ar >> m_name;
		ar >> m_actual_workload;
		ar >> m_unit_price;
	}
}


bool CContractPriceEx2ObjA::CreateOrUpdate(string menuCode, CContractPrice* parent) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������������ף�"), 64);
	if (m_actual_workload > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_actual_workload);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����(Ԫ)"), 64);
	if (m_unit_price > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_unit_price);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("���۷���� ��������"), _T("���۷���� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_actual_workload = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_unit_price = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CContractPriceEx2ObjA::ProjectPrice() {
	return m_unit_price * m_actual_workload / 10000;
}

void CContractPriceEx2ObjB::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_fund;
	}
	else {
		ar >> m_name;
		ar >> m_fund;
	}
}


bool CContractPriceEx2ObjB::CreateOrUpdate(string menuCode, CContractPrice* parent) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ʩ��"), 64);
	if (m_fund > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_fund);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	

	infd.Init(_T("���۴�ʩ�� ��������"), _T("���۴�ʩ�� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CContractPriceEx2ObjB::ProjectPrice() {
	return m_fund;
}

void CContractPriceEx2ObjC::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_fund;
	}
	else {
		ar >> m_name;
		ar >> m_fund;
	}
}


bool CContractPriceEx2ObjC::CreateOrUpdate(string menuCode, CContractPrice* parent) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ʩ��"), 64);
	if (m_fund > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_fund);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;



	infd.Init(_T("�ܼ۴�ʩ�� ��������"), _T("�ܼ۴�ʩ�� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CContractPriceEx2ObjC::ProjectPrice() {
	return m_fund;
}



void CContractPriceEx2ObjD::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_fund;
	}
	else {
		ar >> m_name;
		ar >> m_fund;
	}
}


bool CContractPriceEx2ObjD::CreateOrUpdate(string menuCode, CContractPrice* parent) {
	if (menuCode != CContractPrice::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ʩ��"), 64);
	if (m_fund > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_fund);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;



	infd.Init(_T("������Ŀ�� ��������"), _T("������Ŀ�� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CContractPriceEx2ObjD::ProjectPrice() {
	return m_fund;
}


/* ------------------------------------------ */
CContractPriceObj* CContractPriceEx2::NewChild(CString scheme) {
	CContractPriceObj* p = NULL;

	if (scheme == "���۷����")
		p = new CContractPriceEx2ObjA();
	if (scheme == "���۴�ʩ��")
		p = new CContractPriceEx2ObjB();
	if (scheme == "�ܼ۴�ʩ��")
		p = new CContractPriceEx2ObjC();
	if (scheme == "������Ŀ��")
		p = new CContractPriceEx2ObjD();
	if (p) p->m_scheme = scheme;

	return p;
}


void CContractPriceEx2::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_regulation_rate;
		ar << m_tax_rate;
		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			ar << m_objs[i]->m_scheme;
			m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		ar >> m_name;
		ar >> m_regulation_rate;
		ar >> m_tax_rate;
		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CString scheme;
			ar >> scheme;
			CContractPriceObj* bs = NewChild(scheme);
			bs->Serialize(ar, version);
			m_objs.push_back(bs);
		}
	}
}


bool CContractPriceEx2::CreateOrUpdate() {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = m_scheme;
	infd.m_vecFindItem[0][i][0].strItem = m_scheme;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����ʣ�%��"), 64);
	if (m_regulation_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_regulation_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ֵ˰�ʣ�%��"), 64);
	if (m_tax_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_tax_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_scheme = infd.m_vecFindItem[0][i++][0].strItem;
		m_name = infd.m_vecFindItem[0][i++][0].strItem;
		m_regulation_rate = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		m_tax_rate = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		return true;
	}
	return false;
}


string CContractPriceEx2::Description() {
	stringstream ss;
	double price = 0;
	ss << "�������� : " << m_name.GetBuffer() << ",  ";
	for (int i = 0; i < m_objs.size(); i++) {
		price += m_objs[i]->ProjectPrice();
	}
	ss << "��������ۣ�����˰������Ԫ��: " << Double2String(price) << ",  ";

	price = price * (1 + m_regulation_rate) * (1 + m_tax_rate);

	ss << "��������ۣ���˰������Ԫ��: " << Double2String(price) << ",  ";
	
	return ss.str();
}


bool CContractPriceEx2::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;

	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	vecHeader.push_back("��������");
	vecHeader.push_back("����");
	vecHeader.push_back("����");

	vecHeader.push_back("");
	vecHeader.push_back("");          

	int ttt = m_objs.size();

	for (int i = 0; i < ttt; i++) {
		vector<string> vec;
		vec.push_back(m_objs[i]->m_scheme.GetBuffer());
		vec.push_back(m_objs[i]->m_name.GetBuffer());
		vec.push_back(m_objs[i]->Description());

		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");

		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}


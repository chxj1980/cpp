#include "stdafx.h"
#include "ProjectSettlement.h"
#include "GridDlg.h"




//
//int CProjectSettlementObj::EarliestPaymentTime() {
//
//	return 0;
//}
//
//int CProjectSettlementObj::LatestPaymentTime() {
//	return 0;
//}

/***********************************************************************************/


/* ������ - ���̽��� */
string CProjectSettlement::m_ObjectCode = "01060101";
double CProjectSettlement::m_ObjectVersion = 1.0;

CProjectSettlement::CProjectSettlement()
{
	m_scheme = "";
}


CProjectSettlement::~CProjectSettlement()
{
	for (CProjectSettlementObj* e : m_objs)
		delete e;
}

unsigned int CProjectSettlement::PopupMenuId(string menuCode) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return 0;
	return IDR_POPUP_COMPONENT;
}

CProjectSettlement* CProjectSettlement::NewParent(CString scheme) {
	CProjectSettlement* p = NULL;
	if (scheme == "����2")
		p = new CProjectSettlementEx2();
	if (scheme == "����3")
		p = new CProjectSettlementEx3();
	if (scheme == "����4")
		p = new CProjectSettlementEx4();

	if (p) p->m_scheme = scheme;
	return p;
}


bool CProjectSettlement::Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlement*>& cols) {
	if (!pGridCtrl)
		return false;

	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	vector<string> vecHeader;
	vector<vector<string>> vecData;
	vecHeader.push_back("���̽��㷽��,120");
	vecHeader.push_back("��������,550");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");

	int i = 1;
	for (CProjectSettlement* e : cols) {
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

void CProjectSettlement::Serialize(CArchive& ar, double version, CProjectSettlement*  & p) {
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


void CProjectSettlement::Calculate(string menuCode, vector<CProjectSettlement*>& cols) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
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

bool CProjectSettlement::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;

	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}


CProjectSettlementObj* CProjectSettlement::NewChild() {
	CProjectSettlementObj* p = new CProjectSettlementObjEx2();
	return p;
}

bool CProjectSettlement::AddChild(string menuCode) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	CProjectSettlementObj* c = NewChild();
	if (c->CreateOrUpdate(menuCode, this)) {
		m_objs.push_back(c);
		return true;
	}

	return false;
}

bool CProjectSettlement::UpdateChild(string menuCode, int nRow) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size())
		return m_objs[nRow - 1]->CreateOrUpdate(menuCode, this);
	return false;
}


bool CProjectSettlement::DeleteChild(string menuCode, int nRow) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		int idx = 0;
		vector<CProjectSettlementObj*>::iterator it = m_objs.begin();
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
bool CProjectSettlement::Create(string strMenuCode, CProjectSettlement*  & p) {
	if (strMenuCode != CProjectSettlement::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "����2;����3;����4";
	infd.m_vecFindItem[0][i][0].strItem = "����2";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	infd.Init(_T("���̽��� ����ѡ��"), _T("���̽��� ����ѡ��"));
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

bool CProjectSettlement::Update(string menuCode, int nRow, vector<CProjectSettlement*>& cols) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return  cols[nRow - 1]->CreateOrUpdate();
	return false;
}

bool CProjectSettlement::Delete(string menuCode, int nRow, vector<CProjectSettlement*>& cols) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		int idx = 0;
		vector<CProjectSettlement*>::iterator it = cols.begin();
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

void CProjectSettlementObjEx2::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_actual_workload;
		ar << m_schedule_workload;
		ar << m_party_a_material;
	}
	else {
		ar >> m_month;
		ar >> m_actual_workload;
		ar >> m_schedule_workload;
		ar >> m_party_a_material;
	}
}


bool CProjectSettlementObjEx2::CreateOrUpdate(string menuCode, CProjectSettlement* parent) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("ʵ����ɲ�ֵ(��Ԫ)"), 64);
	if (m_actual_workload > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_actual_workload);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�ƻ���ɲ�ֵ(��Ԫ)"), 64);
	if (m_schedule_workload > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_schedule_workload);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�׹������豸��ֵ(��Ԫ)"), 64);
	if (m_party_a_material > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_party_a_material);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("����ʵ����ɲ�ֵ ��������"), _T("����ʵ����ɲ�ֵ ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_actual_workload = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_schedule_workload = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_party_a_material = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}



CProjectSettlementObj* CProjectSettlementEx2::NewChild() {
	CProjectSettlementObj* p = new CProjectSettlementObjEx2();
	return p;
}


void CProjectSettlementEx2::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_total_price;
		ar << m_advance_payment_percent;
		ar << m_material_percent;
		ar << m_quality_bond_percent;
		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		ar >> m_name;
		ar >> m_total_price;
		ar >> m_advance_payment_percent;
		ar >> m_material_percent;
		ar >> m_quality_bond_percent;
		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CProjectSettlementObj* bs = NewChild();
			bs->Serialize(ar, version);
			m_objs.push_back(bs);
		}
	}
}


bool CProjectSettlementEx2::CreateOrUpdate() {
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������(��Ԫ)"), 64);
	if (m_total_price > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_total_price);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������ϼ��豸��ռ�ȣ�%��"), 64);
	if (m_material_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_material_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ԥ����ռ�ȣ�%��"), 64);
	if (m_advance_payment_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_advance_payment_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������֤��ռ�ȣ�%��"), 64);
	if (m_quality_bond_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_quality_bond_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_scheme = infd.m_vecFindItem[0][i++][0].strItem;
		m_name = infd.m_vecFindItem[0][i++][0].strItem;
		m_total_price = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_material_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		m_advance_payment_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		m_quality_bond_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		return true;
	}
	return false;
}


string CProjectSettlementEx2::Description() {
	stringstream ss;
	ss << "�������� : " << m_name.GetBuffer() << ",  ";
	ss << "������ۣ���Ԫ��: " << Double2String(m_total_price) << ",  ";
	ss << "�������ϼ��豸��ռ�ȣ�%��: " << Double2String(m_material_percent * 100, "%.2f") << ",  ";
	ss << "Ԥ����ռ�ȣ�%��: " << Double2String(m_advance_payment_percent * 100, "%.2f") << ",  ";
	ss << "������֤��ռ�ȣ�%��: " << Double2String(m_quality_bond_percent * 100, "%.2f") << ",  ";
	return ss.str();
}


bool CProjectSettlementEx2::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;

	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	vecHeader.push_back("�·�");
	vecHeader.push_back("��ɲ�ֵ");
	vecHeader.push_back("�ƻ���ֵ");
	vecHeader.push_back("�׹����ϼ�ֵ");

	vecHeader.push_back("�ۼƹ��̿�");
	vecHeader.push_back("Ԥ����ۻ�");
	vecHeader.push_back("������֤�����");
	vecHeader.push_back("���̿����");
	vecHeader.push_back("���ȿ�");

	vecHeader.push_back("");
	vecHeader.push_back("");

	/* Ԥ���� */
	double advance = m_total_price * m_advance_payment_percent;
	/* ���̿���۵� */
	double deductValue = advance / m_material_percent;
	deductValue = m_total_price - deductValue;

	/* �ۼƹ��̿� */
	double value = 0;
	/* �ۼ�������֤�� */
	double quality = 0;
	/* �ۼƿ������̿� */
	double detain = 0;

	int ttt = m_objs.size();

	for (int i = 0; i < ttt; i++) {
		CProjectSettlementObjEx2 e = *(CProjectSettlementObjEx2 *)m_objs[i];
		vector<string> vec;
		vec.push_back(e.m_month.GetBuffer());
		vec.push_back(Double2String(e.m_actual_workload, "%.2f"));
		vec.push_back(Double2String(e.m_schedule_workload, "%.2f"));
		vec.push_back(Double2String(e.m_party_a_material, "%.2f"));

		/* �ۼƹ��̿� */
		value += e.m_actual_workload;
		vec.push_back(Double2String(value, "%.2f"));

		/* ���̽��ȿ� */
		double progress = e.m_actual_workload;

		double deduct = 0;	/* Ӧ�ۻ�Ԥ���� */
		if (value > deductValue) {
			if (value - e.m_actual_workload > deductValue) {
				/* �ϸ��� ���̿���ѳ��� ��۵� */
				deduct = e.m_actual_workload * m_material_percent;
			}
			else {
				/* ���¿�ʼ��� */
				deduct = (value - deductValue) * m_material_percent;
			}
			advance = advance - deduct;
		}

		/* ���ȿ��п۳� Ԥ����Ŀۻ� */
		progress -= deduct;
		vec.push_back(Double2String(deduct, "%.2f"));

		/* ���ȿ��п۳� ������֤�� */
		progress -= e.m_actual_workload * m_quality_bond_percent;
		quality += e.m_actual_workload * m_quality_bond_percent;
		vec.push_back(Double2String(e.m_actual_workload * m_quality_bond_percent, "%.2f"));

		/* ���ȿ��п۳� ���̿���� */
		if (e.m_actual_workload < e.m_schedule_workload) {
			if ((e.m_schedule_workload - e.m_actual_workload) / e.m_schedule_workload >= 0.1) {
				progress -= e.m_actual_workload * 0.05;
				detain += e.m_actual_workload * 0.05;
				vec.push_back(Double2String(e.m_actual_workload * 0.05, "%.2f"));
			}
			else
				vec.push_back(Double2String(0, "%.2f"));
		}
		else
			vec.push_back(Double2String(0, "%.2f"));

		/* ���ȿ��п۳� �׹����ϼ�ֵ */
		progress -= e.m_party_a_material;
		/* ���ȿ� */
		vec.push_back(Double2String(progress, "%.2f"));

		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");

		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}


/***********************************************************************/

void CProjectSettlementObjEx3::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_actual_workload;
	}
	else {
		ar >> m_month;
		ar >> m_actual_workload;
	}
}


bool CProjectSettlementObjEx3::CreateOrUpdate(string menuCode, CProjectSettlement* parent) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("ʵ����ɲ�ֵ(��Ԫ)"), 64);
	if (m_actual_workload > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_actual_workload);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("����ʵ����ɲ�ֵ ��������"), _T("����ʵ����ɲ�ֵ ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_actual_workload = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}



CProjectSettlementObj* CProjectSettlementEx3::NewChild() {
	CProjectSettlementObj* p = new CProjectSettlementObjEx3();
	return p;
}



void CProjectSettlementEx3::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_total_workload;
		ar << m_unit_price;
		ar << m_advance_payment_percent;
		ar << m_quality_bond_percent;
		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		ar >> m_name;
		ar >> m_total_workload;
		ar >> m_unit_price;
		ar >> m_advance_payment_percent;
		ar >> m_quality_bond_percent;
		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CProjectSettlementObj* bs = NewChild();
			bs->Serialize(ar, version);
			m_objs.push_back(bs);
		}
	}
}

bool CProjectSettlementEx3::CreateOrUpdate() {
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�ƻ�����(������)"), 64);
	if (m_total_workload > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_total_workload);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����(Ԫ/������)"), 64);
	if (m_unit_price > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_unit_price);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ԥ����ռ�ȣ�%��"), 64);
	if (m_advance_payment_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_advance_payment_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������֤��ռ�ȣ�%��"), 64);
	if (m_quality_bond_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_quality_bond_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_scheme = infd.m_vecFindItem[0][i++][0].strItem;
		m_name = infd.m_vecFindItem[0][i++][0].strItem;
		m_total_workload = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_unit_price = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_advance_payment_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		m_quality_bond_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		return true;
	}
	return false;
}


string CProjectSettlementEx3::Description() {
	stringstream ss;
	ss << "�������� : " << m_name.GetBuffer() << ",  ";
	ss << "�ƻ�����(������): " << Double2String(m_total_workload) << ",  ";
	ss << "����(Ԫ/������): " << Double2String(m_unit_price) << ",  ";
	ss << "Ԥ����ռ�ȣ�%��: " << Double2String(m_advance_payment_percent * 100, "%.2f") << ",  ";
	ss << "������֤��ռ�ȣ�%��: " << Double2String(m_quality_bond_percent * 100, "%.2f") << ",  ";
	/* Ԥ������۵� */
	double deductValue = m_total_workload * m_unit_price  * 0.3;
	ss << "Ԥ������۵� : " << Double2String(deductValue, "%.2f");
	return ss.str();
}



bool CProjectSettlementEx3::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;

	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	vecHeader.push_back("�·�");
	vecHeader.push_back("��ɹ������������ף�");

	vecHeader.push_back("���۽��ȿ�");
	vecHeader.push_back("�ۼƹ��̿�");
	vecHeader.push_back("�ۼƹ������������ף�");
	
	vecHeader.push_back("������֤�����");
	vecHeader.push_back("Ԥ����ۻ�");

	vecHeader.push_back("���ȿ�");

	vecHeader.push_back("");
	vecHeader.push_back("");

	/* Ԥ���� */
	double advance = m_total_workload * m_unit_price * m_advance_payment_percent;
	/* Ԥ������۵� */
	double deductValue = m_total_workload * m_unit_price  * 0.3;
	/* �������仯�����۵����� */
	double adjustWorkload = m_total_workload * 1.15;

	/* �ۼƹ��̿� */
	double accValue = 0;
	/* �ۼƹ����� */
	double accWorkload = 0;
	/* �ۼ�������֤�� */
	double accQuality = 0;
	/* �ۼƿ������̿� */
	double accDetain = 0;
	
	/* Ӧ�ۻ�Ԥ���� */
	double deduct = 0;	
	int deductStart, deductEnd;
	int ttt = m_objs.size();
	deductStart = deductEnd = ttt;

	for (int i = 0; i < ttt; i++) {
		CProjectSettlementObjEx3 e = *(CProjectSettlementObjEx3 *)m_objs[i];
		vector<string> vec;
		vec.push_back(e.m_month.GetBuffer());
		vec.push_back(Double2String(e.m_actual_workload, "%.2f"));

		
		/* ���̽��ȿ� */
		double progress;
		if ((accWorkload + e.m_actual_workload) < adjustWorkload) {
			progress = e.m_actual_workload * m_unit_price;
		}
		else if (accWorkload < adjustWorkload && (accWorkload + e.m_actual_workload) > adjustWorkload) {
			progress = (adjustWorkload - accWorkload) * m_unit_price;
			progress += (accWorkload + e.m_actual_workload - adjustWorkload) * m_unit_price * 0.9;
		}
		else  {
			progress = e.m_actual_workload * m_unit_price * 0.9;
		}
		vec.push_back(Double2String(progress, "%.2f"));

		
		/* �ۼƹ��̿� */
		accValue += progress;
		vec.push_back(Double2String(accValue, "%.2f"));

		/* �ۼƹ����� */
		accWorkload += e.m_actual_workload;
		vec.push_back(Double2String(accWorkload, "%.2f"));
		
		/* ���ȿ��п۳� ������֤�� */
		accQuality += progress * m_quality_bond_percent;
		vec.push_back(Double2String(progress * m_quality_bond_percent, "%.2f"));
		progress -= progress * m_quality_bond_percent;

		/* ������󼸸��µ� Ӧ��Ԥ���� */
		if (deduct == 0) {
			if (accValue > deductValue) {
				int n = ttt - 2 - i;
				if (n > 0) deduct = advance / n;
				deductStart = i + 1;
				deductEnd = ttt - 2;
			}
		}

		/* ���ȿ��п۳� Ԥ����Ŀۻ� */
		if ( i >= deductStart &&  i <= deductEnd) {
			progress -= deduct;
			vec.push_back(Double2String(deduct, "%.2f"));
		}
		else {
			vec.push_back(Double2String(0, "%.2f"));
		}
		

		if (accDetain + progress < 150000) {
			accDetain += progress;
			progress = 0;
		}
		else {
			progress = accDetain + progress;
			accDetain = 0;
		}

		/* ���ȿ� */
		vec.push_back(Double2String(progress, "%.2f"));

		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");

		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}

/***********************************************************************/

void CProjectSettlementObjEx4::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_actual_fund;
		ar << m_adjust_fund;
		ar << m_ft1;
		ar << m_ft2;
		ar << m_ft3;
		ar << m_ft4;
		ar << m_ft5;
	}
	else {
		ar >> m_month;
		ar >> m_actual_fund;
		ar >> m_adjust_fund;
		ar >> m_ft1;
		ar >> m_ft2;
		ar >> m_ft3;
		ar >> m_ft4;
		ar >> m_ft5;
	}
}


bool CProjectSettlementObjEx4::CreateOrUpdate(string menuCode, CProjectSettlement* parent) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ɹ��̿�(��Ԫ)"), 64);
	if (m_actual_fund > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_actual_fund);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�䶯������(��Ԫ)"), 64);
	if (m_adjust_fund != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_adjust_fund);
	infd.m_vecFindItem[0][i][0].dbMin = -1000000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ڼ۸�ָ��1"), 64);
	if (m_ft1 > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_ft1);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ڼ۸�ָ��2"), 64);
	if (m_ft2 > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_ft2);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ڼ۸�ָ��3"), 64);
	if (m_ft3 > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_ft3);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ڼ۸�ָ��4"), 64);
	if (m_ft4 > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_ft4);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ڼ۸�ָ��5"), 64);
	if (m_ft5 > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_ft5);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	infd.Init(_T("����ʵ����ɲ�ֵ ��������"), _T("����ʵ����ɲ�ֵ ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_actual_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_adjust_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_ft1 = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_ft2 = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_ft3 = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_ft4 = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_ft5 = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}



CProjectSettlementObj* CProjectSettlementEx4::NewChild() {
	CProjectSettlementObj* p = new CProjectSettlementObjEx4();
	return p;
}



void CProjectSettlementEx4::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_total_fund;
		ar << m_advance_payment_percent;
		ar << m_quality_bond_percent;
		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		ar >> m_name;
		ar >> m_total_fund;
		ar >> m_advance_payment_percent;
		ar >> m_quality_bond_percent;
		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CProjectSettlementObj* bs = NewChild();
			bs->Serialize(ar, version);
			m_objs.push_back(bs);
		}
	}
}

bool CProjectSettlementEx4::CreateOrUpdate() {
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ͬ�ܼ�(��Ԫ)"), 64);
	if (m_total_fund > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_total_fund);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ԥ����ռ�ȣ�%��"), 64);
	if (m_advance_payment_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_advance_payment_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������֤��ռ�ȣ�%��"), 64);
	if (m_quality_bond_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_quality_bond_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_scheme = infd.m_vecFindItem[0][i++][0].strItem;
		m_name = infd.m_vecFindItem[0][i++][0].strItem;
		m_total_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_advance_payment_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		m_quality_bond_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		return true;
	}
	return false;
}


string CProjectSettlementEx4::Description() {
	stringstream ss;
	ss << "�������� : " << m_name.GetBuffer() << ",  ";
	ss << "��ͬ�ܼ�(��Ԫ): " << Double2String(m_total_fund) << ",  ";
	ss << "Ԥ����ռ�ȣ�%��: " << Double2String(m_advance_payment_percent * 100, "%.2f") << ",  ";
	ss << "������֤��ռ�ȣ�%��: " << Double2String(m_quality_bond_percent * 100, "%.2f") << ",  ";
	/* Ԥ������۵� */
	double deductValue = 0.3;
	ss << "Ԥ������۵� : " << Double2String(deductValue, "%.2f");
	return ss.str();
}



bool CProjectSettlementEx4::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;

	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	vecHeader.push_back("�·�");
	
	vecHeader.push_back("��ͬ���ȿ�");
	vecHeader.push_back("��ֵ����ȿ�");

	vecHeader.push_back("������֤�����");
	vecHeader.push_back("Ԥ����ۻ�");

	vecHeader.push_back("���ȿ�");

	vecHeader.push_back("");
	vecHeader.push_back("");

	/* Ԥ���� */
	double advance = m_total_fund * m_advance_payment_percent;
	

	/* �ۼƹ��̿� */
	double accValue = 0;
	
	/* �ۼ�������֤�� */
	double accQuality = 0;
	/* �ۼƿ������̿� */
	double accDetain = 0;

	/* Ӧ�ۻ�Ԥ���� */
	double deduct = advance / 2;

	int ttt = m_objs.size();

	for (int i = 0; i < ttt; i++) {
		CProjectSettlementObjEx4 e = *(CProjectSettlementObjEx4 *)m_objs[i];
		vector<string> vec;
		vec.push_back(e.m_month.GetBuffer());
		vec.push_back(Double2String(e.m_actual_fund, "%.2f"));


		/* ���̽��ȿ �ȵ�ֵ�� �������� */
		double progress;
		progress = m_b0 + (m_b1 * e.m_ft1 / m_f01 + m_b2 * e.m_ft2 / m_f02 + m_b3 * e.m_ft3 / m_f03 + m_b4 * e.m_ft4 / m_f04 + m_b5 * e.m_ft5 / m_f05);
		progress = progress * e.m_actual_fund  ;
		vec.push_back(Double2String(progress, "%.2f"));

		
		/* ���ȿ��п۳� ������֤�� */
		accQuality += progress * m_quality_bond_percent;
		vec.push_back(Double2String(progress * m_quality_bond_percent, "%.2f"));
		progress -= progress * m_quality_bond_percent;

		/* ���ȿ��п۳� Ԥ����Ŀۻ� */
		if (i >= ttt - 2 && i <= ttt -1) {
			progress -= deduct;
			vec.push_back(Double2String(deduct, "%.2f"));
		}
		else {
			vec.push_back(Double2String(0, "%.2f"));
		}

		progress += e.m_adjust_fund;
		/* ���ȿ� */
		vec.push_back(Double2String(progress, "%.2f"));

		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");

		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}
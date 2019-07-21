#include "stdafx.h"
#include "ProjectSettlement.h"
#include "GridDlg.h"





CProjectSettlementObj::CProjectSettlementObj()
{
	m_month = "";
	m_actual_workload = 0;
	m_schedule_workload = 0;
	m_party_a_material = 0;
}


CProjectSettlementObj::~CProjectSettlementObj()
{
}


void CProjectSettlementObj::Serialize(CArchive& ar, double version) {
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


bool CProjectSettlementObj::CreateOrUpdate(string menuCode, CProjectSettlement* parent) {
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
	m_name = "";
	m_total_price = 0;
	m_advance_payment_percent = 0;
	m_material_percent = 0;
	m_quality_bond_percent = 0;
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

CProjectSettlement* CProjectSettlement::NewParent(CString method) {
	CProjectSettlement* p = NULL;
	p = new CProjectSettlementEx2();

	return p;
}

void CProjectSettlement::Serialize(CArchive& ar, double version, CProjectSettlement*  & p) {
	if (ar.IsStoring()) {
		ar << p->m_name;
		ar << p->m_total_price;
		ar << p->m_advance_payment_percent;
		ar << p->m_material_percent;
		ar << p->m_quality_bond_percent;
		ar << p->m_objs.size();
		for (int i = 0; i < p->m_objs.size(); i++) {
			p->m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		p = NewParent("");
		ar >> p->m_name;
		ar >> p->m_total_price;
		ar >> p->m_advance_payment_percent;
		ar >> p->m_material_percent;
		ar >> p->m_quality_bond_percent;
		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CProjectSettlementObj* bs = p->NewChild();
			bs->Serialize(ar, version);
			p->m_objs.push_back(bs);
		}
	}
}

bool CProjectSettlement::CreateOrUpdate(string strMenuCode, CProjectSettlement* & p) {

	if (strMenuCode != CProjectSettlement::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
	if (p && !p->m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = p->m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������(��Ԫ)"), 64);
	if (p && p->m_total_price > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", p->m_total_price);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������ϼ��豸��ռ�ȣ�%��"), 64);
	if (p && p->m_material_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", p->m_material_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ԥ����ռ�ȣ�%��"), 64);
	if (p && p->m_advance_payment_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", p->m_advance_payment_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������֤��ռ�ȣ�%��"), 64);
	if (p && p->m_quality_bond_percent > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", p->m_quality_bond_percent * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	
	infd.Init(_T("���귨 ��������"), _T("���귨 ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		if (!p) p = NewParent("");
		p->m_name = infd.m_vecFindItem[0][i++][0].strItem;
		p->m_total_price = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		p->m_material_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer())/100;
		p->m_advance_payment_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer())/100;
		p->m_quality_bond_percent = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer()) / 100;
		return true;
	}
	return false;
}


bool CProjectSettlement::Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlement*>& cols) {
	if (!pGridCtrl)
		return false;

	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	vector<string> vecHeader;
	vector<vector<string>> vecData;
	vecHeader.push_back("���̽����");
	vecHeader.push_back("��������");
	vecHeader.push_back("������ۣ���Ԫ��");
	vecHeader.push_back("�������ϼ��豸��ռ�ȣ�%��");
	vecHeader.push_back("Ԥ����ռ�ȣ�%��");
	vecHeader.push_back("������֤��ռ�ȣ�%��");
	vecHeader.push_back("");
	vecHeader.push_back("");
	vecHeader.push_back("");

	int i = 1;
	for (CProjectSettlement* e : cols) {
		vector<string> vec;
		vec.push_back(Int2String(i++));
		vec.push_back(e->m_name.GetBuffer());
		vec.push_back(Double2String(e->m_total_price));
		vec.push_back(Double2String(e->m_material_percent * 100, "%.2f"));
		vec.push_back(Double2String(e->m_advance_payment_percent * 100, "%.2f"));
		vec.push_back(Double2String(e->m_quality_bond_percent * 100, "%.2f"));
		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");
		vec.push_back("���ӣ�create��");
		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}

bool CProjectSettlement::Update(string menuCode, int nRow, vector<CProjectSettlement*>& cols) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return  CProjectSettlement::CreateOrUpdate(CProjectSettlement::m_ObjectCode, cols[nRow - 1]);
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



void CProjectSettlement::Calculate(string menuCode, vector<CProjectSettlement*>& cols) {
	if (menuCode != CProjectSettlement::m_ObjectCode)
		return;

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("����");
	gridDlg.m_vecHeader.push_back("�������");
	

	for (int i = 0; i < cols.size(); i++)
	{
		CProjectSettlement seb = *cols[i];

		string str = seb.m_name.GetBuffer();
		vector<string> vec;
		vec.push_back(str);
		
			
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
	CProjectSettlementObj* p = new CProjectSettlementObj();
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



/***********************************************************************************/

CProjectSettlementObj* CProjectSettlementEx2::NewChild() {
	CProjectSettlementObj* p = new CProjectSettlementObj();
	return p;
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
		CProjectSettlementObj e = *m_objs[i];
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
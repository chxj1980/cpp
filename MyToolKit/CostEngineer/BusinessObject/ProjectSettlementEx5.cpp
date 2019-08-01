#include "stdafx.h"
#include "ProjectSettlementEx5.h"
#include "GridDlg.h"




//
//int CProjectSettlementEx5Obj::EarliestPaymentTime() {
//
//	return 0;
//}
//
//int CProjectSettlementEx5Obj::LatestPaymentTime() {
//	return 0;
//}


void CProjectSettlementEx5ObjA::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_name;
		ar << m_actual_workload;
		ar << m_material_change;
		ar << m_people_change;
	}
	else {
		ar >> m_month;
		ar >> m_name;
		ar >> m_actual_workload;
		ar >> m_material_change;
		ar >> m_people_change;
	}
}


bool CProjectSettlementEx5ObjA::CreateOrUpdate(string menuCode, CProjectSettlementEx5* parent) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���Ϸѱ䶯(������Ѻ�˰��)��Ԫ��"), 64);
	if (m_material_change != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_material_change);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�˹��ѱ䶯(������Ѻ�˰��)��Ԫ��"), 64);
	if (m_people_change != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_people_change);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;

	infd.Init(_T("������������ ��������"), _T("������������ ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_actual_workload = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_material_change = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		m_people_change = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CProjectSettlementEx5ObjA::ProjectPrice() {
	return m_actual_workload ;
}

string CProjectSettlementEx5ObjA::Description() {
	stringstream ss;
	ss << "������ �� " << Double2String(m_actual_workload, "%.2f");
	if (m_material_change != 0)
		ss << ", " << "���Ϸѱ䶯 : " << Double2String(m_material_change, "%.2f");
	if (m_people_change != 0)
		ss << ", " << "�˹��ѱ䶯 : " << Double2String(m_people_change, "%.2f");
	return ss.str();
}

void CProjectSettlementEx5ObjB::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_name;
		ar << m_fund;
	}
	else {
		ar >> m_month;
		ar >> m_name;
		ar >> m_fund;
	}
}


bool CProjectSettlementEx5ObjB::CreateOrUpdate(string menuCode, CProjectSettlementEx5* parent) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���(������Ѻ�˰��)"), 64);
	if (m_fund > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_fund);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;



	infd.Init(_T("������ ��������"), _T("������ ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_fund = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CProjectSettlementEx5ObjB::ProjectPrice() {
	return m_fund;
}

string CProjectSettlementEx5ObjB::Description() {
	return string("���ȿ� �� ") + Double2String(m_fund, "%.2f");
}

/***********************************************************************************/


/* ������ - ���̽��� */
string CProjectSettlementEx5::m_ObjectCode = "01060502";
double CProjectSettlementEx5::m_ObjectVersion = 1.0;




unsigned int CProjectSettlementEx5::PopupMenuId(string menuCode) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return 0;
	return IDR_POPUP_COMPONENT;
}

CProjectSettlementEx5* CProjectSettlementEx5::NewParent(CString scheme) {
	CProjectSettlementEx5* p = NULL;
	if (scheme == "����5")
		p = new CProjectSettlementEx5();
	if (p) p->m_scheme = scheme;
	return p;
}


bool CProjectSettlementEx5::Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CProjectSettlementEx5*>& cols) {
	if (!pGridCtrl)
		return false;

	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	vector<string> vecHeader;
	vector<vector<string>> vecData;
	vecHeader.push_back("���̽��㷽��,120");
	vecHeader.push_back("��������,550");
	vecHeader.push_back(",80");
	vecHeader.push_back(",80");
	vecHeader.push_back(",80");
	vecHeader.push_back(",80");
	vecHeader.push_back(",80");

	int i = 1;
	for (CProjectSettlementEx5* e : cols) {
		vector<string> vec;
		vec.push_back(e->m_scheme.GetBuffer());
		vec.push_back(e->Description());
		vec.push_back("�޸�" + ActionType2String(ActionType::Update));
		vec.push_back("ɾ��" + ActionType2String(ActionType::Delete));
		vec.push_back("����" + ActionType2String(ActionType::Create));
		vec.push_back("����" + ActionType2String(ActionType::Calculate));
		vec.push_back("���������" + ActionType2String(ActionType::Assist));
		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}

void CProjectSettlementEx5::Serialize(CArchive& ar, double version, CProjectSettlementEx5*  & p) {
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




CProjectSettlementEx5Obj* CProjectSettlementEx5::NewChild(CString scheme) {
	CProjectSettlementEx5Obj* p = NULL;

	if (scheme == "�������������")
		p = new CProjectSettlementEx5ObjA();
	if (scheme == "����������")
		p = new CProjectSettlementEx5ObjB();
	
	if (p) p->m_scheme = scheme;

	return p;
}


void CProjectSettlementEx5::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_manage_rate;
		ar << m_net_rate;
		ar << m_regulation_rate;
		ar << m_tax_rate;

		ar << m_unit_measure;
		ar << m_total_measure;

		ar << m_provisional_sum;
		ar << m_daywork_labor;
		ar << m_estimate_engineering;
		ar << m_estimate_material;
		ar << m_general_constracting_service_fee;

		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			ar << m_objs[i]->m_scheme;
			m_objs[i]->Serialize(ar, version);
		}

		ar << m_mapProjectUnitPrice.size();
		for (map<string, double>::iterator it = m_mapProjectUnitPrice.begin(); it != m_mapProjectUnitPrice.end(); it++) {
			CString proj = it->first.c_str();
			ar << proj;
			ar << it->second;
		}

		ar << m_mapProjectWorkload.size();
		for (map<string, double>::iterator it = m_mapProjectWorkload.begin(); it != m_mapProjectWorkload.end(); it++) {
			CString proj = it->first.c_str();
			ar << proj;
			ar << it->second;
		}
	}
	else {
		ar >> m_name;
		ar >> m_manage_rate;
		ar >> m_net_rate;
		ar >> m_regulation_rate;
		ar >> m_tax_rate;

		ar >> m_unit_measure;
		ar >> m_total_measure;

		ar >> m_provisional_sum;
		ar >> m_daywork_labor;
		ar >> m_estimate_engineering;
		ar >> m_estimate_material;
		ar >> m_general_constracting_service_fee;

		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CString scheme;
			ar >> scheme;
			CProjectSettlementEx5Obj* bs = NewChild(scheme);
			bs->Serialize(ar, version);
			m_objs.push_back(bs);
		}
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CString proj;	double db;
			ar >> proj;		ar >> db;
			m_mapProjectUnitPrice[proj.GetBuffer()] = db;
		}
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CString proj;	double db;
			ar >> proj;		ar >> db;
			m_mapProjectWorkload[proj.GetBuffer()] = db;
		}
		SortByMonth();
	}
}


bool CProjectSettlementEx5::CreateOrUpdate() {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������ʣ�%��"), 64);
	if (m_manage_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_manage_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ʣ�%��"), 64);
	if (m_net_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_net_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

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

	/* ��ʩ��Ŀ�� */
	i=0;
	infd.m_vecFindItem[1][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[1][i][0].caption, _T("���۴�ʩ��Ŀ�ѣ���Ԫ��"), 64);
	if (m_unit_measure > 0)
		infd.m_vecFindItem[1][i][0].strItem.Format("%.2f", m_unit_measure);
	infd.m_vecFindItem[1][i][0].dbMin = 0.00;
	infd.m_vecFindItem[1][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[1][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[1][i][0].caption, _T("�ܼ۴�ʩ��Ŀ�ѣ���Ԫ��"), 64);
	if (m_total_measure > 0)
		infd.m_vecFindItem[1][i][0].strItem.Format("%.2f", m_total_measure);
	infd.m_vecFindItem[1][i][0].dbMin = 0.00;
	infd.m_vecFindItem[1][i][0].dbMax = 100000;

	/* ������Ŀ�� */
	i = 0;
	infd.m_vecFindItem[2][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[2][i][0].caption, _T("���н���Ԫ��"), 64);
	if (m_provisional_sum > 0)
		infd.m_vecFindItem[2][i][0].strItem.Format("%.2f", m_provisional_sum);
	infd.m_vecFindItem[2][i][0].dbMin = 0.00;
	infd.m_vecFindItem[2][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[2][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[2][i][0].caption, _T("�����ݹ����ۣ���Ԫ��"), 64);
	if (m_estimate_material > 0)
		infd.m_vecFindItem[2][i][0].strItem.Format("%.2f", m_estimate_material);
	infd.m_vecFindItem[2][i][0].dbMin = 0.00;
	infd.m_vecFindItem[2][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[2][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[2][i][0].caption, _T("רҵ�����ݹ��ۣ���Ԫ��"), 64);
	if (m_estimate_engineering > 0)
		infd.m_vecFindItem[2][i][0].strItem.Format("%.2f", m_estimate_engineering);
	infd.m_vecFindItem[2][i][0].dbMin = 0.00;
	infd.m_vecFindItem[2][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[2][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[2][i][0].caption, _T("���չ�����Ԫ��"), 64);
	if (m_daywork_labor > 0)
		infd.m_vecFindItem[2][i][0].strItem.Format("%.2f", m_daywork_labor);
	infd.m_vecFindItem[2][i][0].dbMin = 0.00;
	infd.m_vecFindItem[2][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[2][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[2][i][0].caption, _T("�ܳа�����ѣ���Ԫ��"), 64);
	if (m_general_constracting_service_fee > 0)
		infd.m_vecFindItem[2][i][0].strItem.Format("%.2f", m_general_constracting_service_fee);
	infd.m_vecFindItem[2][i][0].dbMin = 0.00;
	infd.m_vecFindItem[2][i][0].dbMax = 100000;


	/* ��ȡ���еķ���� */
	g = 3;
	i = 0;
	map<string, double>::iterator it1 = m_mapProjectUnitPrice.begin();
	for (; it1 != m_mapProjectUnitPrice.end(); it1++) {
		infd.m_vecFindItem[g][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[g][i][0].caption, (it1->first + "���ۣ�Ԫ/�����ף�").c_str() , 64);
		if (it1->second > 0)
			infd.m_vecFindItem[g][i][0].strItem.Format("%.2f", it1->second);
		infd.m_vecFindItem[g][i][0].dbMin = 0.01;
		infd.m_vecFindItem[g][i][0].dbMax = 10000000;
		i++;
	}

	g = 4;
	i = 0;
	map<string, double>::iterator it2 = m_mapProjectWorkload.begin();
	for (; it2 != m_mapProjectWorkload.end(); it2++) {
		infd.m_vecFindItem[g][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[g][i][0].caption, (it2->first + "�������������ף�").c_str(), 64);
		if (it2->second > 0)
			infd.m_vecFindItem[g][i][0].strItem.Format("%.2f", it2->second);
		infd.m_vecFindItem[g][i][0].dbMin = 0.01;
		infd.m_vecFindItem[g][i][0].dbMax = 10000000;
		i++;
	}
	

	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		m_scheme = infd.m_vecFindItem[g][i++][0].strItem;
		m_name = infd.m_vecFindItem[g][i++][0].strItem;
		m_manage_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_net_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_regulation_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_tax_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;

		i = 0;
		g = 1;
		m_unit_measure = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		m_total_measure = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

		i = 0;
		g = 2;
		m_provisional_sum = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		m_estimate_material = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		m_estimate_engineering = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		m_daywork_labor = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		m_general_constracting_service_fee = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

		i = 0;
		g = 3;
		map<string, double>::iterator it1 = m_mapProjectUnitPrice.begin();
		for (; it1 != m_mapProjectUnitPrice.end(); it1++) {
			it1->second = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		}

		i = 0;
		g = 4;
		map<string, double>::iterator it2 = m_mapProjectWorkload.begin();
		for (; it2 != m_mapProjectWorkload.end(); it2++) {
			it2->second = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		}

		return true;
	}
	return false;
}


string CProjectSettlementEx5::Description() {
	stringstream ss;
	double price = 0;
	ss << "�������� : " << m_name.GetBuffer() << ",  ";

	for (map<string, double>::iterator it = m_mapProjectWorkload.begin(); it != m_mapProjectWorkload.end(); it++) {
		double p = it->second * m_mapProjectUnitPrice[it->first] / 10000;
		price += p;
	}
	price += m_daywork_labor;
	price += m_estimate_engineering;
	price += m_general_constracting_service_fee;
	price += m_provisional_sum;
	price += m_total_measure;
	price += m_unit_measure;
	price = price * (1 + m_regulation_rate);
	ss << "��������ۣ�����˰������Ԫ��: " << Double2String(price) << ",  ";
	price = price * (1 + m_tax_rate);
	ss << "��������ۣ���˰������Ԫ��: " << Double2String(price) << ",  ";

	/* ͳ��ʵ�ʹ����� */
	map<string, double> mapProjectWorkload = m_mapProjectWorkload;
	for (map<string, double>::iterator it = mapProjectWorkload.begin(); it != mapProjectWorkload.end(); it++) {
		it->second = 0;
	}
	for (int i = 0; i < m_objs.size(); i++) {
		if (m_objs[i]->m_scheme == "�������������") {
			string proj = m_objs[i]->m_name.GetBuffer();
			mapProjectWorkload[proj] += m_objs[i]->ProjectPrice();
		}
	}
	for (map<string, double>::iterator it = mapProjectWorkload.begin(); it != mapProjectWorkload.end(); it++) {
		ss << it->first <<  "ʵ�ʹ����� : " << Double2String(it->second) << ", " ;
	}

	return ss.str();
}

void CProjectSettlementEx5::SortByMonth() {
	struct sort_deref
	{
		bool operator() (CProjectSettlementEx5Obj* lhs, CProjectSettlementEx5Obj* rhs)
		{
			return String2Double(lhs->m_month.GetBuffer()) < String2Double(rhs->m_month.GetBuffer());
		}
	};

	std::sort(m_objs.begin(), m_objs.end(), sort_deref());

	/* ��ȡ���еķ���� */
	map<string, double> mapProjectUnitPrice;
	map<string, double> mapProjectWorkload;
	for (int i = 0; i < m_objs.size(); i++) {
		if (m_objs[i]->m_scheme == "�������������") {
			string proj = m_objs[i]->m_name.GetBuffer();
			if (mapProjectUnitPrice.count(proj) == 0) {
				mapProjectUnitPrice[proj] = 0;
				mapProjectWorkload[proj] = 0;
			}
		}
	}
	for (map<string, double>::iterator it = mapProjectUnitPrice.begin(); it != mapProjectUnitPrice.end(); it++) {
		if (m_mapProjectUnitPrice.count(it->first) > 0)
			it->second = m_mapProjectUnitPrice[it->first];
	}
	for (map<string, double>::iterator it = mapProjectWorkload.begin(); it != mapProjectWorkload.end(); it++) {
		if (m_mapProjectWorkload.count(it->first) > 0)
			it->second = m_mapProjectWorkload[it->first];
	}
	m_mapProjectUnitPrice = mapProjectUnitPrice;
	m_mapProjectWorkload = mapProjectWorkload;
}

void CProjectSettlementEx5::Calculate() 
{
	bool bOK = true;
	for (map<string, double>::iterator it = m_mapProjectUnitPrice.begin(); it != m_mapProjectUnitPrice.end(); it++) {
		if (it->second == 0 ) bOK = false;
	}
	if (!bOK) {
		AfxMessageBox("��Ϊ��������á����ۡ�");
		return;
	}

	for (map<string, double>::iterator it = m_mapProjectWorkload.begin(); it != m_mapProjectWorkload.end(); it++) {
		if (it->second == 0) bOK = false;
	}
	if (!bOK) {
		AfxMessageBox("��Ϊ��������á���������");
		return;
	}

	/* ��¼ʩ���·ݵĽ��ȿ� */
	map<string, double> mapMonth;
	for (int i = 0; i < m_objs.size(); i++) {
		string month = m_objs[i]->m_month.GetBuffer();
		if (mapMonth.count(month) == 0) {
			mapMonth[month] = 0;
		}
	}

	/* ��¼��ǰ�µ����з���̵��ۼƹ����� */
	map<string, double> mapWorkload = m_mapProjectWorkload;
	for (map<string, double>::iterator it = mapWorkload.begin(); it != mapWorkload.end(); it++) {
		it->second = 0;
	}

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("�·�");
	gridDlg.m_vecHeader.push_back("���ȿ�(��Ԫ)");

	/* ���»��ܼ��� */
	map<string, double>::iterator it = mapMonth.begin();
	for (; it != mapMonth.end(); it++) {
		string month = it->first;
		string desc;
		for (int i = 0; i < m_objs.size(); i++) {
			if (m_objs[i]->m_month.GetBuffer() == month) {
				double price;
				if (m_objs[i]->m_scheme == "�������������") {
					string proj = m_objs[i]->m_name.GetBuffer();
					CProjectSettlementEx5ObjA * pa = (CProjectSettlementEx5ObjA *)m_objs[i];
					/* ��������������ȿ� */
					if (mapWorkload[proj] > m_mapProjectWorkload[proj] * 1.15) {
						price = m_mapProjectUnitPrice[proj] * 0.9 * pa->m_actual_workload;
					}
					else if (mapWorkload[proj] + pa->m_actual_workload > m_mapProjectWorkload[proj] * 1.15) {
						price = (m_mapProjectWorkload[proj] * 1.15 - mapWorkload[proj]) * m_mapProjectUnitPrice[proj];
						price += (mapWorkload[proj] + pa->m_actual_workload - m_mapProjectWorkload[proj] * 1.15)  * m_mapProjectUnitPrice[proj] * 0.9;
					}
					else {
						price = m_mapProjectUnitPrice[proj] * pa->m_actual_workload;
					}
					mapWorkload[proj] += pa->m_actual_workload;
					
					/* ���Ϸѱ䶯�� */
					price += pa->m_material_change;
					/* �˹��ѱ䶯�� */
					price += pa->m_people_change;

					price = price / 10000;
					
				}
				else {
					price = m_objs[i]->ProjectPrice();
				}
				if (!desc.empty())	desc += " , ";
				desc += m_objs[i]->m_name.GetBuffer() + string(" : ") + Double2String(price, "%.3f");
				/* ���� ÿ�µĹ��̿� ������ ��Ѻ�˰�� */
				mapMonth[month] += price;
			}
		}
		if (!desc.empty())	desc += " , ";
		desc += "���깤�̿� �� " + Double2String(mapMonth[month] * (1+m_regulation_rate) * (1+ m_tax_rate), "%.3f");

		vector<string> vec;
		vec.push_back(month);
		vec.push_back(desc);
		gridDlg.m_vecData.push_back(vec);
	}
	gridDlg.DoModal();
}

/* �����˹��� �����Ϸѵȵĵ����� */
void CProjectSettlementEx5::Adjust() {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;

	int g = 0;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������/�Ͷ���"), 64);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���۵�����(Ԫ)"), 64);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("������ʣ�%��"), 64);
	if (m_manage_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_manage_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ʣ�%��"), 64);
	if (m_net_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_net_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

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

	infd.Init(_T("��������� ��������"), _T("��������� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		double amount = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		double unit_price = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

		double manage_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		double net_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		double regulation_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		double tax_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;

		double price = amount * unit_price * (1 + manage_rate) * (1 + net_rate) ;
		double price1 = price * (1 + regulation_rate) * (1 + tax_rate);
		string msg = "������(������Ѻ�˰��)(Ԫ�� : " + Double2String(price, "%.2f");
		msg += ",   ������(Ԫ�� : " + Double2String(price1, "%.2f");
		AfxMessageBox(msg.c_str());
	}
}

bool CProjectSettlementEx5::DrawChild(CGridCtrl* pGridCtrl)
{
	if (!pGridCtrl)
		return false;
	
	vector<string>			vecHeader;
	vector<vector<string>>	vecData;

	vecHeader.push_back("�·�");
	vecHeader.push_back("��������");
	vecHeader.push_back("��������");
	vecHeader.push_back("����");

	vecHeader.push_back("");
	vecHeader.push_back("");

	int ttt = m_objs.size();

	for (int i = 0; i < ttt; i++) {
		vector<string> vec;
		vec.push_back(m_objs[i]->m_month.GetBuffer());
		vec.push_back(m_objs[i]->m_name.GetBuffer());
		vec.push_back(m_objs[i]->m_scheme.GetBuffer());
		vec.push_back(m_objs[i]->Description());

		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");

		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}



bool CProjectSettlementEx5::AddChild(string menuCode) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "�������������;����������";
	infd.m_vecFindItem[0][i][0].strItem = "�������������";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	infd.Init(_T("���̽��� ����ѡ��"), _T("���̽��� ����ѡ��"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString scheme = infd.m_vecFindItem[0][i++][0].strItem;
		CProjectSettlementEx5Obj* c = NewChild(scheme);
		if (c->CreateOrUpdate(menuCode, this)) {
			m_objs.push_back(c);

			SortByMonth();
			return true;
		}
		else {
			delete c;
		}
	}

	return false;
}

bool CProjectSettlementEx5::UpdateChild(string menuCode, int nRow) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		bool res =  m_objs[nRow - 1]->CreateOrUpdate(menuCode, this);
		SortByMonth();
		return res;
	}
	return false;
}


bool CProjectSettlementEx5::DeleteChild(string menuCode, int nRow) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		int idx = 0;
		vector<CProjectSettlementEx5Obj*>::iterator it = m_objs.begin();
		for (; it != m_objs.end(); it++, idx++) {
			if (idx == nRow - 1)
				break;
		}
		m_objs.erase(it);
		SortByMonth();
		return true;
	}
	return false;
}


/* "����" ���ģʽ */
bool CProjectSettlementEx5::Create(string strMenuCode, CProjectSettlementEx5*  & p) {
	if (strMenuCode != CProjectSettlementEx5::m_ObjectCode)
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

bool CProjectSettlementEx5::Update(string menuCode, int nRow, vector<CProjectSettlementEx5*>& cols) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return  cols[nRow - 1]->CreateOrUpdate();
	return false;
}

bool CProjectSettlementEx5::Delete(string menuCode, int nRow, vector<CProjectSettlementEx5*>& cols) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		int idx = 0;
		vector<CProjectSettlementEx5*>::iterator it = cols.begin();
		for (; it != cols.end(); it++, idx++) {
			if (idx == nRow - 1)
				break;
		}
		cols.erase(it);
		return true;
	}
	return false;
}


bool CProjectSettlementEx5::Calculate(string menuCode, int nRow,  vector<CProjectSettlementEx5*>& cols) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		cols[nRow - 1]->Calculate();
	}
	return true;
}

bool CProjectSettlementEx5::Adjust(string menuCode, int nRow, vector<CProjectSettlementEx5*>& cols) {
	if (menuCode != CProjectSettlementEx5::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		cols[nRow - 1]->Adjust();
	}
	return true;
}

/***********************************************************************************/


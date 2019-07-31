#include "stdafx.h"
#include "FinanceAnalysis.h"
#include "GridDlg.h"




//
//int CFinanceAnalysisObj::EarliestPaymentTime() {
//
//	return 0;
//}
//
//int CFinanceAnalysisObj::LatestPaymentTime() {
//	return 0;
//}


void CFinanceAnalysisObjA::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_name;
		ar << m_amount_of_money;
	}
	else {
		ar >> m_month;
		ar >> m_name;
		ar >> m_amount_of_money;
	}
}


bool CFinanceAnalysisObjA::CreateOrUpdate(string menuCode, CFinanceAnalysis* parent) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "����Ͷ��;�����ʽ�Ͷ��;��Ӫ�ɱ�(��������˰);����˰��;Ӧ����ֵ˰;��ֵ˰����;��������˰;����֧��";
	if(!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else 
		infd.m_vecFindItem[0][i][0].strItem = "����Ͷ��";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("�ֽ����� ��������"), _T("�ֽ����� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CFinanceAnalysisObjA::ProjectPrice() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjA::Description() {
	stringstream ss;
	ss << "�ֽ����� �� " << Double2String(m_amount_of_money, "%.2f");
	
	return ss.str();
}

bool CFinanceAnalysisObjA::HasAssist() {
	if (m_name == "Ӧ����ֵ˰")
		return true;
	else if (m_name == "��ֵ˰����")
		return true;
	else if (m_name == "��������˰")
		return true;
	else
		return false;
}

bool CFinanceAnalysisObjA::Assist(CFinanceAnalysis* parent) {

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	if (m_name == "Ӧ����ֵ˰") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰��"), 64);
		if(parent->GetAmountOfMoney(m_month, "����˰��", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰��"), 64);
		if (parent->GetAmountOfMoney(m_month, "����˰��", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double tax1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double tax2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			m_amount_of_money = tax1 - tax2;
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name == "��ֵ˰����") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ӧ����ֵ˰"), 64);
		if (parent->GetAmountOfMoney(m_month, "Ӧ����ֵ˰", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("˰�𸽼ӷ���(%)"), 64);
		if (parent->m_tax_surcharge_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", parent->m_tax_surcharge_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double tax1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double tax2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) /100;
			m_amount_of_money = tax1 * tax2;
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name == "��������˰") {

		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ӫҵ����(��������˰)"), 64);
		if (parent->GetAmountOfMoney(m_month, "Ӫҵ����(��������˰)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
		if (parent->GetAmountOfMoney(m_month, "��������", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��Ӫ�ɱ�(��������˰)"), 64);
		if (parent->GetAmountOfMoney(m_month, "��Ӫ�ɱ�(��������˰)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("Ӧ����ֵ˰"), 64);
		if (parent->GetAmountOfMoney(m_month, "Ӧ����ֵ˰", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ֵ˰����"), 64);
		if (parent->GetAmountOfMoney(m_month, "Ӧ����ֵ˰", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�۾ɷ�"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰��(%)"), 64);
		if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", parent->m_income_tax_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double input1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double input2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			double output1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double output2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double output3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double output4 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			double rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			m_amount_of_money = input1 + input2 - output1 - output2 - output3 - output4;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	return false;
}

/* --------------------------------------------- */

void CFinanceAnalysisObjB::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_month;
		ar << m_name;
		ar << m_amount_of_money;
	}
	else {
		ar >> m_month;
		ar >> m_name;
		ar >> m_amount_of_money;
	}
}


bool CFinanceAnalysisObjB::CreateOrUpdate(string menuCode, CFinanceAnalysis* parent) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "Ӫҵ����(��������˰);����˰��;�̶��ʲ�����;���������ʽ�;��������";
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = "Ӫҵ����(��������˰)";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("�ֽ����� ��������"), _T("�ֽ����� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		m_month = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_name = infd.m_vecFindItem[0][i++][0].strItem.GetBuffer();
		m_amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());

		return true;
	}
	return false;
}

double CFinanceAnalysisObjB::ProjectPrice() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjB::Description() {
	return string("�ֽ����� �� ") + Double2String(m_amount_of_money, "%.2f");
}

bool CFinanceAnalysisObjB::HasAssist() {
	if (m_name == "�̶��ʲ�����")
		return true;
	else
		return false;
}

bool CFinanceAnalysisObjB::Assist(CFinanceAnalysis* parent) {

	return false;
}

/***********************************************************************************/


/* ������ - ���̽��� */
string CFinanceAnalysis::m_ObjectCode = "01010401";
double CFinanceAnalysis::m_ObjectVersion = 1.0;


unsigned int CFinanceAnalysis::PopupMenuId(string menuCode) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return 0;
	return IDR_POPUP_COMPONENT;
}

CFinanceAnalysis* CFinanceAnalysis::NewParent(CString scheme) {
	CFinanceAnalysis* p = NULL;
	if (scheme == "����4")
		p = new CFinanceAnalysis();
	if (p) p->m_scheme = scheme;
	return p;
}


bool CFinanceAnalysis::Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CFinanceAnalysis*>& cols) {
	if (!pGridCtrl)
		return false;

	if (menuCode != CFinanceAnalysis::m_ObjectCode)
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
	for (CFinanceAnalysis* e : cols) {
		vector<string> vec;
		vec.push_back(e->m_scheme.GetBuffer());
		vec.push_back(e->Description());
		vec.push_back("�޸ģ�update��");
		vec.push_back("ɾ����delete��");
		vec.push_back("���ӣ�create��");
		vec.push_back("���㣨operate1��");
		vec.push_back("��������㣨operate2��");
		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}

void CFinanceAnalysis::Serialize(CArchive& ar, double version, CFinanceAnalysis*  & p) {
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




CFinanceAnalysisObj* CFinanceAnalysis::NewChild(CString scheme) {
	CFinanceAnalysisObj* p = NULL;

	if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjA();
	if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjB();
	
	if (p) p->m_scheme = scheme;

	return p;
}


void CFinanceAnalysis::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_manage_rate;
		ar << m_net_rate;
		ar << m_tax_surcharge_rate;
		ar << m_income_tax_rate;

		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			ar << m_objs[i]->m_scheme;
			m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		ar >> m_name;
		ar >> m_manage_rate;
		ar >> m_net_rate;
		ar >> m_tax_surcharge_rate;
		ar >> m_income_tax_rate;

		int nNum;
		ar >> nNum;
		for (int i = 0; i < nNum; i++) {
			CString scheme;
			ar >> scheme;
			CFinanceAnalysisObj* bs = NewChild(scheme);
			bs->Serialize(ar, version);
			m_objs.push_back(bs);
		}
		
		SortByMonth();
	}
}


bool CFinanceAnalysis::CreateOrUpdate() {
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("˰�𸽼ӷ��ʣ�%��"), 64);
	if (m_tax_surcharge_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_tax_surcharge_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰�ʣ�%��"), 64);
	if (m_income_tax_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.2f", m_income_tax_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		m_scheme = infd.m_vecFindItem[g][i++][0].strItem;
		m_name = infd.m_vecFindItem[g][i++][0].strItem;
		m_manage_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_net_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_tax_surcharge_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_income_tax_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;

		return true;
	}
	return false;
}


string CFinanceAnalysis::Description() {
	stringstream ss;
	double price = 0;
	ss << "�������� : " << m_name.GetBuffer() << ",  ";

	return ss.str();
}

void CFinanceAnalysis::SortByMonth() {
	struct sort_deref
	{
		bool operator() (CFinanceAnalysisObj* lhs, CFinanceAnalysisObj* rhs)
		{
			return String2Double(lhs->m_month.GetBuffer()) < String2Double(rhs->m_month.GetBuffer());
		}
	};

	std::sort(m_objs.begin(), m_objs.end(), sort_deref());
}

void CFinanceAnalysis::Calculate() 
{
	bool bOK = true;
	map<string, double> mapMonth;

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("�·�");
	gridDlg.m_vecHeader.push_back("���ȿ�(��Ԫ)");

	/* ���»��ܼ��� */
	map<string, double>::iterator it = mapMonth.begin();
	for (; it != mapMonth.end(); it++) {
		string month = it->first;
		string desc;
		
		vector<string> vec;
		vec.push_back(month);
		vec.push_back(desc);
		gridDlg.m_vecData.push_back(vec);
	}
	gridDlg.DoModal();
}


void CFinanceAnalysis::Adjust() {
	
}

bool CFinanceAnalysis::GetAmountOfMoney(CString month, CString name, double & amount) {
	for (CFinanceAnalysisObj * p : m_objs) {
		if (String2Double(p->m_month.GetBuffer()) == String2Double(month.GetBuffer())
			&& p->m_name.CompareNoCase(name) == 0) {
			amount = p->m_amount_of_money;
			return true;
		}
	}
	return false;
}

bool CFinanceAnalysis::AssistChild(string menuCode, int nRow) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		bool res = m_objs[nRow - 1]->Assist(this);
		SortByMonth();
		return res;
	}
	return false;
}

bool CFinanceAnalysis::DrawChild(CGridCtrl* pGridCtrl)
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
		if (m_objs[i]->HasAssist())	
			vec.push_back("�������㣨operate1��");
		else
			vec.push_back("");

		vecData.push_back(vec);
	}

	return DrawGrid(pGridCtrl, vecHeader, vecData);
}



bool CFinanceAnalysis::AddChild(string menuCode) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "�ֽ�����;�ֽ�����";
	infd.m_vecFindItem[0][i][0].strItem = "�ֽ�����";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	infd.Init(_T("�ֽ����� ����ѡ��"), _T("�ֽ����� ����ѡ��"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString scheme = infd.m_vecFindItem[0][i++][0].strItem;
		CFinanceAnalysisObj* c = NewChild(scheme);
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

bool CFinanceAnalysis::UpdateChild(string menuCode, int nRow) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		bool res =  m_objs[nRow - 1]->CreateOrUpdate(menuCode, this);
		SortByMonth();
		return res;
	}
	return false;
}


bool CFinanceAnalysis::DeleteChild(string menuCode, int nRow) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		int idx = 0;
		vector<CFinanceAnalysisObj*>::iterator it = m_objs.begin();
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
bool CFinanceAnalysis::Create(string strMenuCode, CFinanceAnalysis*  & p) {
	if (strMenuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "����4";
	infd.m_vecFindItem[0][i][0].strItem = "����4";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	infd.Init(_T("������� ����ѡ��"), _T("������� ����ѡ��"));
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

bool CFinanceAnalysis::Update(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size())
		return  cols[nRow - 1]->CreateOrUpdate();
	return false;
}

bool CFinanceAnalysis::Delete(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		int idx = 0;
		vector<CFinanceAnalysis*>::iterator it = cols.begin();
		for (; it != cols.end(); it++, idx++) {
			if (idx == nRow - 1)
				break;
		}
		cols.erase(it);
		return true;
	}
	return false;
}


bool CFinanceAnalysis::Calculate(string menuCode, int nRow,  vector<CFinanceAnalysis*>& cols) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		cols[nRow - 1]->Calculate();
	}
	return true;
}

bool CFinanceAnalysis::Adjust(string menuCode, int nRow, vector<CFinanceAnalysis*>& cols) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= cols.size()) {
		cols[nRow - 1]->Adjust();
	}
	return true;
}

/***********************************************************************************/


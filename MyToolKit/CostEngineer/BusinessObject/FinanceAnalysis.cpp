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
	infd.CYCOMBOX = 30;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.����Ͷ��;2.�����ʽ�Ͷ��;3.��Ӫ�ɱ�(��������˰);4.����˰��;5.Ӧ����ֵ˰;6.��ֵ˰����;7.ά����ӪͶ��;8.��������˰";
	if(!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else 
		infd.m_vecFindItem[0][i][0].strItem = "1.����Ͷ��";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("�ֽ����� ��������"), _T("�ֽ����� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* ���� */
			bCheck = true;
		}
		else {
			/* �޸� */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, name, amount)) {
				AfxMessageBox("�Ѵ�����ͬ��");
				return false;
			}
		}
		m_month = month;
		m_name = name;
		m_amount_of_money = amount_of_money;
		return true;
	}
	return false;
}

double CFinanceAnalysisObjA::AmountOfMoney() {
	return  - m_amount_of_money;
}

string CFinanceAnalysisObjA::Description() {
	stringstream ss;
	ss << "�ֽ����� �� " << Double2String(m_amount_of_money, "%.3f");
	
	return ss.str();
}

bool CFinanceAnalysisObjA::HasAssist() {
	if (m_name == "5.Ӧ����ֵ˰")
		return true;
	else if (m_name == "6.��ֵ˰����")
		return true;
	else if (m_name == "8.��������˰")
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

	if (m_name == "5.Ӧ����ֵ˰") {
		i = 0;
		int nMonth = String2Double(m_month.GetBuffer());
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�ۼƽ�ֹ����Ӧ����ֵ˰"), 64);
		amount = parent->AccumulativeTax(nMonth);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�ۼƽ�ֹ����Ӧ����ֵ˰"), 64);
		amount = parent->AccumulativeTax(nMonth - 1);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
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
	else if (m_name == "6.��ֵ˰����") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("5.Ӧ����ֵ˰"), 64);
		if (parent->GetAmountOfMoney(m_month, "5.Ӧ����ֵ˰", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("˰�𸽼ӷ���(%)"), 64);
		if (parent->m_tax_surcharge_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_tax_surcharge_rate * 100);
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
	else if (m_name == "8.��������˰") {

		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("1.Ӫҵ����(��������˰)"), 64);
		if (parent->GetAmountOfMoney(m_month, "1.Ӫҵ����(��������˰)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.��������"), 64);
		if (parent->GetAmountOfMoney(m_month, "3.��������", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.��Ӫ�ɱ�(��������˰)"), 64);
		if (parent->GetAmountOfMoney(m_month, "3.��Ӫ�ɱ�(��������˰)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("6.��ֵ˰����"), 64);
		if (parent->GetAmountOfMoney(m_month, "6.��ֵ˰����", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("7.ά����ӪͶ��"), 64);
		if (parent->GetAmountOfMoney(m_month, "7.ά����ӪͶ��", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�۾ɷ�"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰��(%)"), 64);
		if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);
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
			m_amount_of_money = m_amount_of_money * rate;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	
	return false;
}


bool CFinanceAnalysisObjA::CopyTo(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ʼ���"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("��������"), _T("��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_name, amount)) {
				/* �����ڣ������ */
				CFinanceAnalysisObjA * p = new CFinanceAnalysisObjA();
				p->m_month = Int2String(i).c_str();
				p->m_scheme = m_scheme;
				p->m_name = m_name;
				p->m_amount_of_money = m_amount_of_money;
				parent->m_objs.push_back(p);
			}
		}
		return true;
	}
	return false;
}

/* ------------------------------------------------------------ */


void CFinanceAnalysisObjA1::Serialize(CArchive& ar, double version) {
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


bool CFinanceAnalysisObjA1::CreateOrUpdate(string menuCode, CFinanceAnalysis* parent) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.CYCOMBOX = 30;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�·�"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.��Ŀ�ʱ���;2.���𳥻�;3.�����Ϣ����;4.�����ʽ�Ͷ��;5.��Ӫ�ɱ�(��������˰);6.����˰��;7.Ӧ����ֵ˰;8.��ֵ˰����;9.ά����ӪͶ��;10.����˰";
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = "1.��Ŀ�ʱ���";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("�ֽ����� ��������"), _T("�ֽ����� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* ���� */
			bCheck = true;
		}
		else {
			/* �޸� */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, name, amount)) {
				AfxMessageBox("�Ѵ�����ͬ��");
				return false;
			}
		}
		m_month = month;
		m_name = name;
		m_amount_of_money = amount_of_money;
		return true;
	}
	return false;
}

double CFinanceAnalysisObjA1::AmountOfMoney() {
	return  -m_amount_of_money;
}

string CFinanceAnalysisObjA1::Description() {
	stringstream ss;
	ss << "�ֽ����� �� " << Double2String(m_amount_of_money, "%.3f");

	return ss.str();
}

bool CFinanceAnalysisObjA1::HasAssist() {
	if (m_name == "3.�����Ϣ����")
		return true;
	else if (m_name == "7.Ӧ����ֵ˰")
		return true;
	else if (m_name == "8.��ֵ˰����")
		return true;
	else if (m_name == "10.����˰")
		return true;
	else
		return false;
}



bool CFinanceAnalysisObjA1::Assist(CFinanceAnalysis* p) {

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;
	CAfterFinancing * parent = (CAfterFinancing *)p;

	if (m_name == "3.�����Ϣ����") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("ʣ������"), 64);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������(%)"), 64);
		if (parent->m_interest_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_interest_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double tax1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double tax2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			m_amount_of_money = tax1 * tax2;
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name == "7.Ӧ����ֵ˰") {
		i = 0;
		int nMonth = String2Double(m_month.GetBuffer());
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�ۼƽ�ֹ����Ӧ����ֵ˰"), 64);
		amount = parent->AccumulativeTax(nMonth);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�ۼƽ�ֹ����Ӧ����ֵ˰"), 64);
		amount = parent->AccumulativeTax(nMonth - 1);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
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
	else if (m_name == "8.��ֵ˰����") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("7.Ӧ����ֵ˰"), 64);
		if (parent->GetAmountOfMoney(m_month, "7.Ӧ����ֵ˰", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("˰�𸽼ӷ���(%)"), 64);
		if (parent->m_tax_surcharge_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_tax_surcharge_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double tax1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double tax2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			m_amount_of_money = tax1 * tax2;
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name == "10.����˰") {

		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("1.Ӫҵ����(��������˰)"), 64);
		if (parent->GetAmountOfMoney(m_month, "1.Ӫҵ����(��������˰)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.��������"), 64);
		if (parent->GetAmountOfMoney(m_month, "3.��������", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.�����Ϣ����"), 64);
		if (parent->GetAmountOfMoney(m_month, "3.�����Ϣ����", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("5.��Ӫ�ɱ�(��������˰)"), 64);
		if (parent->GetAmountOfMoney(m_month, "5.��Ӫ�ɱ�(��������˰)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;


		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("8.��ֵ˰����"), 64);
		if (parent->GetAmountOfMoney(m_month, "8.��ֵ˰����", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("9.ά����ӪͶ��"), 64);
		if (parent->GetAmountOfMoney(m_month, "9.ά����ӪͶ��", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�۾ɷ�"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;




		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰��(%)"), 64);
		if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);
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
			double output5 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			double rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			m_amount_of_money = input1 + input2 - output1 - output2 - output3 - output4 - output5;
			m_amount_of_money = m_amount_of_money * rate;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}

	return false;
}


bool CFinanceAnalysisObjA1::CopyTo(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ʼ���"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("��������"), _T("��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_name, amount)) {
				/* �����ڣ������ */
				CFinanceAnalysisObjA1 * p = new CFinanceAnalysisObjA1();
				p->m_month = Int2String(i).c_str();
				p->m_scheme = m_scheme;
				p->m_name = m_name;
				p->m_amount_of_money = m_amount_of_money;
				parent->m_objs.push_back(p);
			}
		}
		return true;
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
	infd.m_vecFindItem[0][i][0].strData = "1.Ӫҵ����(��������˰);2.����˰��;3.��������;4.���չ̶��ʲ���ֵ;5.���������ʽ�";
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = "1.Ӫҵ����(��������˰)";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("�ֽ����� ��������"), _T("�ֽ����� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* ���� */
			bCheck = true;
		}
		else {
			/* �޸� */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, name, amount)) {
				AfxMessageBox("�Ѵ�����ͬ��");
				return false;
			}
		}
		m_month = month;
		m_name = name;
		m_amount_of_money = amount_of_money;
		return true;
	}
	return false;
}

double CFinanceAnalysisObjB::AmountOfMoney() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjB::Description() {
	return string("�ֽ����� �� ") + Double2String(m_amount_of_money, "%.3f");
}

bool CFinanceAnalysisObjB::HasAssist() {

	if (m_name == "4.���չ̶��ʲ���ֵ")
		return true;
	else
		return false;
}

bool CFinanceAnalysisObjB::Assist(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	if (m_name == "4.���չ̶��ʲ���ֵ") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("1.����Ͷ��"), 64);
		if (parent->GetAmountOfMoney(m_month, "1.����Ͷ��", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -0.01;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�̶��ʲ�����˰��"), 64);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("ʹ������"), 64);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ĩ����ֵ��(%)"), 64);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("ʣ��ʹ������"), 64);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			double v4 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			double v = (v1 - v2) * (1 - rate) / v3;
			v = v * v4 + (v1 - v2) * rate;
			m_amount_of_money = v;
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	
	return false;
}

bool CFinanceAnalysisObjB::CopyTo(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ʼ���"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("��������"), _T("��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_name, amount)) {
				/* �����ڣ������ */
				CFinanceAnalysisObjB * p = new CFinanceAnalysisObjB();
				p->m_month = Int2String(i).c_str();
				p->m_scheme = m_scheme;
				p->m_name = m_name;
				p->m_amount_of_money = m_amount_of_money;
				parent->m_objs.push_back(p);
			}
		}

		return true;
	}
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
	if (scheme == "����ǰ")
		p = new CBeforeFinancing();
	if (scheme == "���ʺ�")
		p = new CAfterFinancing();
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
	vecHeader.push_back("��������,400");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");
	vecHeader.push_back(",140");

	int i = 1;
	for (CFinanceAnalysis* e : cols) {
		vector<string> vec;
		vec.push_back(e->m_scheme.GetBuffer());
		vec.push_back(e->Description());
		vec.push_back("�޸�" + ActionType2String(ActionType::Update));
		vec.push_back("ɾ��" + ActionType2String(ActionType::Delete));
		vec.push_back("����" + ActionType2String(ActionType::Create));
		vec.push_back("����" + ActionType2String(ActionType::Calculate));
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





void CFinanceAnalysis::Serialize(CArchive& ar, double version) {
	if (ar.IsStoring()) {
		ar << m_name;
		ar << m_discount;
		ar << m_net_residual_rate;
		ar << m_tax_surcharge_rate;
		ar << m_income_tax_rate;
		ar << m_tax_on_purchase;	

		ar << m_objs.size();
		for (int i = 0; i < m_objs.size(); i++) {
			ar << m_objs[i]->m_scheme;
			m_objs[i]->Serialize(ar, version);
		}
	}
	else {
		ar >> m_name;
		ar >> m_discount;
		ar >> m_net_residual_rate;
		ar >> m_tax_surcharge_rate;
		ar >> m_income_tax_rate;
		ar >> m_tax_on_purchase;

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
	infd.m_vecFindItem[0][i][0].strData = m_scheme;	// ���㷽�� �����Ը���
	infd.m_vecFindItem[0][i][0].strItem = m_scheme;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��������"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "ֱ�߷�;˫�����ݼ���";
	if (!m_discount.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_discount;
	else
		infd.m_vecFindItem[0][i][0].strItem = "ֱ�߷�";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�۾ɷ�"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("��ĩ����ֵ�ʣ�%��"), 64);
	if (m_net_residual_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_net_residual_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("˰�𸽼ӷ��ʣ�%��"), 64);
	if (m_tax_surcharge_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_tax_surcharge_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����˰�ʣ�%��"), 64);
	if (m_income_tax_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_income_tax_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�����ڽ���˰��"), 64);
	if (m_tax_on_purchase > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_tax_on_purchase);
	infd.m_vecFindItem[0][i][0].dbMin = 0.00;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		infd.m_vecFindItem[g][i++][0].strItem;  // ���㷽�� �����Ը���
		m_name = infd.m_vecFindItem[g][i++][0].strItem;
		m_discount = infd.m_vecFindItem[g][i++][0].strItem;
		m_net_residual_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_tax_surcharge_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_income_tax_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
		m_tax_on_purchase = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
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
			int left = String2Double(lhs->m_month.GetBuffer());
			int right = String2Double(rhs->m_month.GetBuffer());
			if (left < right) return true;
			if (left == right) {
				string lscheme = lhs->m_scheme.GetBuffer();
				string rscheme = rhs->m_scheme.GetBuffer();
				if (lscheme != rscheme) {
					if (lscheme == "�ֽ�����") return true;
				}
				else {
					string lname = lhs->m_name.GetBuffer();
					string rname = rhs->m_name.GetBuffer();
					left = lname.find(".");
					right = rname.find(".");
					left = atoi(lname.substr(0, left).c_str());
					right = atoi(rname.substr(0, right).c_str());
					if (left < right) return true;
				}
				
			}
			return false;
		}
	};

	std::sort(m_objs.begin(), m_objs.end(), sort_deref());
}

void CFinanceAnalysis::Calculate() 
{
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.�ֽ�������;2.��̬Ͷ�ʻ�����;3.������ֵ;4.�����ڲ�������";
	infd.m_vecFindItem[0][i][0].strItem = "1.�ֽ�������";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������"), 64);


	infd.Init(_T("��������"), _T("��������"));
	/*if (infd.DoModal() != IDOK) {
		return;
	}*/
	
	bool bOK = true;
	map<int, double> mapMonth;

	for (CFinanceAnalysisObj* e : m_objs) {
		int nMonth = String2Double(e->m_month.GetBuffer());
		if (mapMonth.count(nMonth) == 0) {
			mapMonth[nMonth] = e->AmountOfMoney();
		}
		else {
			mapMonth[nMonth] += e->AmountOfMoney();
		}
	}

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("�·�");
	gridDlg.m_vecHeader.push_back("���¿�(��Ԫ)");
	gridDlg.m_vecHeader.push_back("��������ֵ(��Ԫ)");
	gridDlg.m_vecHeader.push_back("�ۼƿ��̬�����ڣ�(��Ԫ)");
	gridDlg.m_vecHeader.push_back("�ۼ�����ֵ(��Ԫ)");

	/* ���»��ܼ��� */
	double accStatic = 0;
	double accDynamic = 0;
	map<int, double>::iterator it = mapMonth.begin();
	for (; it != mapMonth.end(); it++) {
		int nMonth = it->first;
		double money = it->second;
		
		vector<string> vec;
		vec.push_back(Int2String(nMonth));
		vec.push_back(Double2String(money, "%.3f"));

		double present = Future2Present(0.1, nMonth, 4) * money;
		vec.push_back(Double2String(present, "%.3f"));

		accStatic += money;
		vec.push_back(Double2String(accStatic, "%.3f"));

		accDynamic += present;
		vec.push_back(Double2String(accDynamic, "%.3f"));
		
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

bool CFinanceAnalysis::CopyToChild(string menuCode, int nRow) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	if (nRow > 0 && nRow <= m_objs.size()) {
		bool res = m_objs[nRow - 1]->CopyTo(this);
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
	vecHeader.push_back("");

	int ttt = m_objs.size();

	for (int i = 0; i < ttt; i++) {
		vector<string> vec;
		vec.push_back(m_objs[i]->m_month.GetBuffer());
		vec.push_back(m_objs[i]->m_name.GetBuffer());
		vec.push_back(m_objs[i]->m_scheme.GetBuffer());
		vec.push_back(m_objs[i]->Description());

		vec.push_back("�޸�" + ActionType2String(ActionType::Update));
		vec.push_back("ɾ��" + ActionType2String(ActionType::Delete));
		vec.push_back("���Ƶ�" + ActionType2String(ActionType::CopyTo));
		if (m_objs[i]->HasAssist())	
			vec.push_back("��������" + ActionType2String(ActionType::Assist));
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
	infd.m_vecFindItem[0][i][0].strData = "����ǰ;���ʺ�";
	infd.m_vecFindItem[0][i][0].strItem = "����ǰ";
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

/* ��ֹ�����£��ۼ�Ӧ����ֵ˰ */
double CBeforeFinancing::AccumulativeTax(int nMonth) {
	double tax = 0;
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "2.����˰��", amount)) {
			tax += amount;
		}
	}
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "4.����˰��", amount)) {
			tax -= amount;
		}
	}
	tax -= m_tax_on_purchase;
	if (tax < 0) tax = 0;
	return tax;
}

/* ��ֹ�����£��ۼ�Ӧ����ֵ˰ */
double CAfterFinancing::AccumulativeTax(int nMonth) {
	double tax = 0;
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "2.����˰��", amount)) {
			tax += amount;
		}
	}
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "6.����˰��", amount)) {
			tax -= amount;
		}
	}
	tax -= m_tax_on_purchase;
	if (tax < 0) tax = 0;
	return tax;
}

CFinanceAnalysisObj* CBeforeFinancing::NewChild(CString scheme) {
	CFinanceAnalysisObj* p = NULL;

	if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjA();
	if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjB();

	if (p) p->m_scheme = scheme;

	return p;
}

CFinanceAnalysisObj* CAfterFinancing::NewChild(CString scheme) {
	CFinanceAnalysisObj* p = NULL;

	if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjA1();
	if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjB();

	if (p) p->m_scheme = scheme;

	return p;
}

void CAfterFinancing::Serialize(CArchive& ar, double version) {
	CFinanceAnalysis::Serialize(ar, version);
	if (ar.IsStoring()) {
		ar << m_interest_rate;
	}
	else {
		ar >> m_interest_rate;
	}
}

bool CAfterFinancing::CreateOrUpdate() {
	if (CFinanceAnalysis::CreateOrUpdate()) {
		CDyncItemGroupDlg infd;
		infd.CXCAPTION = 100;
		infd.GROUP_NUM_PER_LINE = 3;
		int g = 0;
		int i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("�������ʣ�%��"), 64);
		if (m_interest_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_interest_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0.001;
		infd.m_vecFindItem[0][i][0].dbMax = 100;



		infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			m_interest_rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			return true;
		}
	}
	
	return false;
}
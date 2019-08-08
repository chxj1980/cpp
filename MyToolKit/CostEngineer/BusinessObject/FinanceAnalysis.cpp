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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("月份"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.建设投资;2.流动资金投资;3.经营成本(不含进项税);4.进项税额;5.应纳增值税;6.增值税附加;7.维持运营投资;8.调整所得税";
	if(!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else 
		infd.m_vecFindItem[0][i][0].strItem = "1.建设投资";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("流出款项"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("金额"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("现金流出 参数设置"), _T("现金流出 参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* 新增 */
			bCheck = true;
		}
		else {
			/* 修改 */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, m_scheme, name, amount)) {
				AfxMessageBox("已存在相同项");
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
	ss << "现金流出 ： " << Double2String(m_amount_of_money, "%.3f");
	
	return ss.str();
}

bool CFinanceAnalysisObjA::HasAssist() {
	if (m_name == "5.应纳增值税")
		return true;
	else if (m_name == "6.增值税附加")
		return true;
	else if (m_name == "8.调整所得税")
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

	if (m_name == "5.应纳增值税") {
		i = 0;
		int nMonth = String2Double(m_month.GetBuffer());
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("累计截止本月应纳增值税"), 64);
		amount = parent->AccumulativeTax(nMonth);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("累计截止上月应纳增值税"), 64);
		amount = parent->AccumulativeTax(nMonth - 1);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("参数设置"), _T("参数设置"));
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
	else if (m_name == "6.增值税附加") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("5.应纳增值税"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "5.应纳增值税", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("税金附加费率(%)"), 64);
		if (parent->m_tax_surcharge_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_tax_surcharge_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("参数设置"), _T("参数设置"));
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
	else if (m_name == "8.调整所得税") {

		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("1.营业收入(不含销项税)"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流入", "1.营业收入(不含销项税)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.补贴收入"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流入", "3.补贴收入", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.经营成本(不含进项税)"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "3.经营成本(不含进项税)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("6.增值税附加"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "6.增值税附加", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("7.维持运营投资"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "7.维持运营投资", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("折旧费"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("摊销费"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("所得税率(%)"), 64);
		if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("参数设置"), _T("参数设置"));
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("开始年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("结束年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("参数设置"), _T("参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_scheme, m_name, amount)) {
				/* 不存在，则添加 */
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("月份"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.项目资本金;2.借款本金偿还;3.借款利息偿还;4.流动资金投资;5.经营成本(不含进项税);6.进项税额;7.应纳增值税;8.增值税附加;9.维持运营投资;10.所得税";
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = "1.项目资本金";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("流出款项"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("金额"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("现金流出 参数设置"), _T("现金流出 参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* 新增 */
			bCheck = true;
		}
		else {
			/* 修改 */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, m_scheme, name, amount)) {
				AfxMessageBox("已存在相同项");
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
	ss << "现金流出 ： " << Double2String(m_amount_of_money, "%.3f");

	return ss.str();
}

bool CFinanceAnalysisObjA1::HasAssist() {
	if (m_name == "7.应纳增值税")
		return true;
	else if (m_name == "8.增值税附加")
		return true;
	else if (m_name == "10.所得税")
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

	if (m_name == "7.应纳增值税") {
		i = 0;
		int nMonth = String2Double(m_month.GetBuffer());
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("累计截止本月应纳增值税"), 64);
		amount = parent->AccumulativeTax(nMonth);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("累计截止上月应纳增值税"), 64);
		amount = parent->AccumulativeTax(nMonth - 1);
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("参数设置"), _T("参数设置"));
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
	else if (m_name == "8.增值税附加") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("7.应纳增值税"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "7.应纳增值税", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("税金附加费率(%)"), 64);
		if (parent->m_tax_surcharge_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_tax_surcharge_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("参数设置"), _T("参数设置"));
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
	else if (m_name == "10.所得税") {

		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("1.营业收入(不含销项税)"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流入", "1.营业收入(不含销项税)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.补贴收入"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流入", "3.补贴收入", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("3.借款利息偿还"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "3.借款利息偿还", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("5.经营成本(不含进项税)"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "5.经营成本(不含进项税)", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;


		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("8.增值税附加"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "8.增值税附加", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("9.维持运营投资"), 64);
		if (parent->GetAmountOfMoney(m_month, "现金流出", "9.维持运营投资", amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -100000;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("折旧费"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("摊销费"), 64);
		/*if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);*/
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;


		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("所得税率(%)"), 64);
		if (parent->m_income_tax_rate > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", parent->m_income_tax_rate * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		infd.Init(_T("参数设置"), _T("参数设置"));
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
			double output6 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			double rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			m_amount_of_money = input1 + input2 - output1 - output2 - output3 - output4 - output5 - output6;
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("开始年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("结束年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("参数设置"), _T("参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_scheme, m_name, amount)) {
				/* 不存在，则添加 */
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("月份"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.营业收入(不含销项税);2.销项税额;3.补贴收入;4.回收固定资产余值;5.回收流动资金";
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = "1.营业收入(不含销项税)";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("流入款项"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("金额"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("现金流入 参数设置"), _T("现金流入 参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* 新增 */
			bCheck = true;
		}
		else {
			/* 修改 */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, m_scheme, name, amount)) {
				AfxMessageBox("已存在相同项");
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
	return string("现金流入 ： ") + Double2String(m_amount_of_money, "%.3f");
}

bool CFinanceAnalysisObjB::HasAssist() {

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

	if (m_name == "4.回收固定资产余值") {
		
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
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("开始年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("结束年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("参数设置"), _T("参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_scheme, m_name, amount)) {
				/* 不存在，则添加 */
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

/* --------------------------------------------- */

void CFinanceAnalysisObjC::Serialize(CArchive& ar, double version) {
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


bool CFinanceAnalysisObjC::CreateOrUpdate(string menuCode, CFinanceAnalysis* parent) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;

	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("月份"), 64);
	if (!m_month.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_month;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "1.借入;2.还本;3.付息";
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = "1.借入";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("贷款"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("金额"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("贷款 参数设置"), _T("贷款 参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString month = infd.m_vecFindItem[0][i++][0].strItem;
		CString name = infd.m_vecFindItem[0][i++][0].strItem;
		double amount_of_money = String2Double(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		bool bCheck = false;
		if (m_name.IsEmpty()) {
			/* 新增 */
			bCheck = true;
		}
		else {
			/* 修改 */
			if (String2Double(month.GetBuffer()) != String2Double(m_month.GetBuffer()) || name.CompareNoCase(m_name) != 0) {
				bCheck = true;
			}
		}
		if (bCheck) {
			double amount;
			if (parent->GetAmountOfMoney(month, m_scheme, name, amount)) {
				AfxMessageBox("已存在相同项");
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

double CFinanceAnalysisObjC::AmountOfMoney() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjC::Description() {
	return string("金额 ： ") + Double2String(m_amount_of_money, "%.3f");
}

bool CFinanceAnalysisObjC::HasAssist() {

	if (m_name == "3.付息")
		return true;
	else
		return false;
}

bool CFinanceAnalysisObjC::Assist(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;
	CAfterFinancing*  p = (CAfterFinancing *)parent;
	int nMonth = atoi(m_month.GetBuffer());
	int nLoan = atoi(m_scheme.Mid(m_scheme.GetLength() - 1, 1).GetBuffer());

	if (m_name == "3.付息") {
		i = 0;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("截止本期初，贷款余额"), 64);
		amount = p->LoanRemaining(nMonth, nLoan);
		if (amount > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = -0.01;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;


		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("本期新借入"), 64);
		if (p->GetAmountOfMoney(m_month, m_scheme, "1.借入", amount) > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;
			   
		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
		memcpy(infd.m_vecFindItem[0][i][0].caption, _T("贷款利率(%)"), 64);
		if (p->m_interest_rate[nLoan - 1] > 0)
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", p->m_interest_rate[nLoan - 1] * 100);
		infd.m_vecFindItem[0][i][0].dbMin = 0;
		infd.m_vecFindItem[0][i][0].dbMax = 1000000;

		i++;
		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
		memcpy(infd.m_vecFindItem[0][i][0].caption, "首年利息减半", 64);
		infd.m_vecFindItem[0][i][0].strData = "yes;no";
		if (p->m_interest_half[i])
			infd.m_vecFindItem[0][i][0].strItem = "yes";
		else
			infd.m_vecFindItem[0][i][0].strItem = "no";


		infd.Init(_T("本期新产生利息"), _T("本期新产生利息"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			bool bHalf = true;
			if (infd.m_vecFindItem[g][i++][0].strItem.CompareNoCase("no") == 0)
				bHalf = false;
			m_amount_of_money = v1 * rate +  v2 * (bHalf? 0.5:1) * rate;
			
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}

	return false;
}

bool CFinanceAnalysisObjC::CopyTo(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("开始年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 1;
	infd.m_vecFindItem[0][i][0].nMax = 1000000;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("结束年度"), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMin = 1000000;

	infd.Init(_T("参数设置"), _T("参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		int v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		int v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		if (v2 < v1) v2 = v1;

		for (int i = v1; i <= v2; i++) {
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_scheme, m_name, amount)) {
				/* 不存在，则添加 */
				CFinanceAnalysisObjC * p = new CFinanceAnalysisObjC();
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


/* 第六章 - 工程结算 */
string CFinanceAnalysis::m_ObjectCode = "01010401";
double CFinanceAnalysis::m_ObjectVersion = 1.0;


unsigned int CFinanceAnalysis::PopupMenuId(string menuCode) {
	if (menuCode != CFinanceAnalysis::m_ObjectCode)
		return 0;
	return IDR_POPUP_COMPONENT;
}

CFinanceAnalysis* CFinanceAnalysis::NewParent(CString scheme) {
	CFinanceAnalysis* p = NULL;
	if (scheme == "融资前")
		p = new CBeforeFinancing();
	if (scheme == "融资后")
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
	vecHeader.push_back("工程结算方案,120");
	vecHeader.push_back("工程描述,400");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");
	vecHeader.push_back(",120");
	vecHeader.push_back(",140");

	int i = 1;
	for (CFinanceAnalysis* e : cols) {
		vector<string> vec;
		vec.push_back(e->m_scheme.GetBuffer());
		vec.push_back(e->Description());
		vec.push_back("修改" + ActionType2String(ActionType::Update));
		vec.push_back("删除" + ActionType2String(ActionType::Delete));
		vec.push_back("增加" + ActionType2String(ActionType::Create));
		vec.push_back("计算" + ActionType2String(ActionType::Calculate));
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
	infd.m_vecFindItem[0][i][0].strData = m_scheme;	// 计算方案 不可以更改
	infd.m_vecFindItem[0][i][0].strItem = m_scheme;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("计算方案"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("工程名称"), 64);
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "直线法;双倍余额递减法";
	if (!m_discount.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_discount;
	else
		infd.m_vecFindItem[0][i][0].strItem = "直线法";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("折旧法"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("期末净残值率（%）"), 64);
	if (m_net_residual_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_net_residual_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("税金附加费率（%）"), 64);
	if (m_tax_surcharge_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_tax_surcharge_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("所得税率（%）"), 64);
	if (m_income_tax_rate > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_income_tax_rate * 100);
	infd.m_vecFindItem[0][i][0].dbMin = 0.01;
	infd.m_vecFindItem[0][i][0].dbMax = 100;

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("建设期进项税额"), 64);
	if (m_tax_on_purchase > 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_tax_on_purchase);
	infd.m_vecFindItem[0][i][0].dbMin = 0.00;
	infd.m_vecFindItem[0][i][0].dbMax = 100;


	infd.Init(_T("工程结算 参数设置"), _T("工程结算 参数设置"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		infd.m_vecFindItem[g][i++][0].strItem;  // 计算方案 不可以更改
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
	ss << "工程名称 : " << m_name.GetBuffer() << ",  ";

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
				bool lLoan = lscheme.find("借款") != string::npos;
				bool rLoan = rscheme.find("借款") != string::npos;
				if (lscheme != rscheme) {
					if (lLoan && rLoan) return lscheme < rscheme;
					else if (lLoan) return true;
					else if (rLoan) return false;
					else if (lscheme == "现金流入") return true;
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
	infd.m_vecFindItem[0][i][0].strData = "1.现金流量表;2.静态投资回收期;3.财务净现值;4.财务内部收益率";
	infd.m_vecFindItem[0][i][0].strItem = "1.现金流量表";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("流入款项"), 64);


	infd.Init(_T("参数设置"), _T("参数设置"));
	/*if (infd.DoModal() != IDOK) {
		return;
	}*/
	
	bool bOK = true;
	map<int, double> mapMonth;

	for (CFinanceAnalysisObj* e : m_objs) {
		int nMonth = String2Double(e->m_month.GetBuffer());
		if (e->m_scheme.Find("现金") != string::npos) {
			if (mapMonth.count(nMonth) == 0) {
				mapMonth[nMonth] = e->AmountOfMoney();
			}
			else {
				mapMonth[nMonth] += e->AmountOfMoney();
			}
		}
	}

	CGridDlg gridDlg;
	gridDlg.m_vecHeader.push_back("月份");
	gridDlg.m_vecHeader.push_back("本月款(万元)");
	gridDlg.m_vecHeader.push_back("本月折现值(万元)");
	gridDlg.m_vecHeader.push_back("累计款（静态回收期）(万元)");
	gridDlg.m_vecHeader.push_back("累计折现值(万元)");

	/* 逐月汇总计算 */
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

bool CFinanceAnalysis::GetAmountOfMoney(CString month, CString scheme, CString name, double & amount) {
	for (CFinanceAnalysisObj * p : m_objs) {
		if (scheme.CompareNoCase(p->m_scheme) == 0) {
			if (String2Double(p->m_month.GetBuffer()) == String2Double(month.GetBuffer())
				&& p->m_name.CompareNoCase(name) == 0) {
				amount = p->m_amount_of_money;
				return true;
			}
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

	vecHeader.push_back("月份");
	vecHeader.push_back("款项类型");
	vecHeader.push_back("款项名称");
	vecHeader.push_back("描述");

	vecHeader.push_back("");
	vecHeader.push_back("");
	vecHeader.push_back("");
	vecHeader.push_back("");

	int ttt = m_objs.size();

	for (int i = 0; i < ttt; i++) {
		vector<string> vec;
		vec.push_back(m_objs[i]->m_month.GetBuffer());
		vec.push_back(m_objs[i]->m_scheme.GetBuffer());
		vec.push_back(m_objs[i]->m_name.GetBuffer());
		vec.push_back(m_objs[i]->Description());

		vec.push_back("修改" + ActionType2String(ActionType::Update));
		vec.push_back("删除" + ActionType2String(ActionType::Delete));
		vec.push_back("复制到" + ActionType2String(ActionType::CopyTo));
		if (m_objs[i]->HasAssist())	
			vec.push_back("辅助计算" + ActionType2String(ActionType::Assist));
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
	infd.m_vecFindItem[0][i][0].strData = "现金流出;现金流入;借款1;借款2;借款3;借款4;借款5";
	infd.m_vecFindItem[0][i][0].strItem = "现金流出";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("计算方案"), 64);

	infd.Init(_T("现金类型 方案选择"), _T("现金类型 方案选择"));
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


/* "工厂" 设计模式 */
bool CFinanceAnalysis::Create(string strMenuCode, CFinanceAnalysis*  & p) {
	if (strMenuCode != CFinanceAnalysis::m_ObjectCode)
		return false;

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int i = 0;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = "融资前;融资后";
	infd.m_vecFindItem[0][i][0].strItem = "融资前";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("计算方案"), 64);

	infd.Init(_T("财务分析 方案选择"), _T("财务分析 方案选择"));
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

/* 截止到本月，累计应纳增值税 */
double CBeforeFinancing::AccumulativeTax(int nMonth) {
	double tax = 0;
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "现金流入", "2.销项税额", amount)) {
			tax += amount;
		}
	}
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "现金流出", "4.进项税额", amount)) {
			tax -= amount;
		}
	}
	tax -= m_tax_on_purchase;
	if (tax < 0) tax = 0;
	return tax;
}

/* 截止到本月，累计应纳增值税 */
double CAfterFinancing::AccumulativeTax(int nMonth) {
	double tax = 0;
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "现金流入", "2.销项税额", amount)) {
			tax += amount;
		}
	}
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "现金流出", "6.进项税额", amount)) {
			tax -= amount;
		}
	}
	tax -= m_tax_on_purchase;
	if (tax < 0) tax = 0;
	return tax;
}

/* 截止到本期初，贷款余额 */
double CAfterFinancing::LoanRemaining(int nMonth, int nLoan) {
	
	if (nLoan >5 || nLoan < 1 ) return 0;
	string loanScheme = "借款" + Int2String(nLoan);

	/* remain 保存截止前几期末的 贷款余额 */
	double remain = 0;
	for (int i = 1; i < nMonth; i++) {
		double amount;
		remain = remain * (1 + m_interest_rate[nLoan - 1]);
		if (GetAmountOfMoney(Int2String(i).c_str(), loanScheme.c_str(), "1.借入", amount)) {
			remain += amount;
			if (m_interest_half[nLoan - 1]) {
				/* 新借入，本期利息减半 */
				remain += amount * 0.5 * m_interest_rate[nLoan - 1];
			}
			else {
				remain += amount * m_interest_rate[nLoan - 1];
			}
			
		}
		
		if (GetAmountOfMoney(Int2String(i).c_str(), loanScheme.c_str(), "2.还本", amount)) {
			remain -= amount;
		}

		if (GetAmountOfMoney(Int2String(i).c_str(), loanScheme.c_str(), "3.付息", amount)) {
			remain -= amount;
		}
	}
	
	return remain;
}

CFinanceAnalysisObj* CBeforeFinancing::NewChild(CString scheme) {
	CFinanceAnalysisObj* p = NULL;

	if (scheme == "现金流出")
		p = new CFinanceAnalysisObjA();
	if (scheme == "现金流入")
		p = new CFinanceAnalysisObjB();

	if (p) p->m_scheme = scheme;

	return p;
}

CFinanceAnalysisObj* CAfterFinancing::NewChild(CString scheme) {
	CFinanceAnalysisObj* p = NULL;

	if (scheme == "现金流出")
		p = new CFinanceAnalysisObjA1();
	else if (scheme == "现金流入")
		p = new CFinanceAnalysisObjB();
	else if (scheme.Find("借款") >= 0)
		p = new CFinanceAnalysisObjC();

	if (p) p->m_scheme = scheme;

	return p;
}

void CAfterFinancing::Serialize(CArchive& ar, double version) {
	CFinanceAnalysis::Serialize(ar, version);
	if (ar.IsStoring()) {
		for (int i = 0; i < 5; i++) {
			ar << m_interest_rate[i];
			ar << m_interest_half[i];
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			ar >> m_interest_rate[i];
			ar >> m_interest_half[i];
		}
	}
}

bool CAfterFinancing::CreateOrUpdate() {
	if (CFinanceAnalysis::CreateOrUpdate()) {
		CDyncItemGroupDlg infd;
		infd.CXCAPTION = 100;
		infd.GROUP_NUM_PER_LINE = 3;
		int g = 0;
		int i = 0;
		for (i = 0; i < 5; i++) {
			string caption = "借款" + Int2String(i+1) + " - 贷款利率（%）";
			infd.m_vecFindItem[0][2*i][0].nType = CDlgTemplateBuilder::EDIT;
			memcpy(infd.m_vecFindItem[0][2*i][0].caption, caption.c_str(), 64);
			if (m_interest_rate[i] > 0.00001)
				infd.m_vecFindItem[0][2*i][0].strItem.Format("%.3f", m_interest_rate[i] * 100);
			infd.m_vecFindItem[0][2*i][0].dbMin = 0;
			infd.m_vecFindItem[0][2*i][0].dbMax = 100;

			caption = "借款" + Int2String(i + 1) + " - 首年利息减半";
			infd.m_vecFindItem[0][2 * i + 1][0].nType = CDlgTemplateBuilder::COMBOBOX;
			memcpy(infd.m_vecFindItem[0][2 * i + 1][0].caption, caption.c_str(), 64);
			infd.m_vecFindItem[0][2 * i + 1][0].strData = "yes;no";
			if (m_interest_half[i])
				infd.m_vecFindItem[0][2 * i + 1][0].strItem = "yes";
			else
				infd.m_vecFindItem[0][2 * i + 1][0].strItem = "no";
		}
		
		infd.Init(_T("工程结算 参数设置"), _T("工程结算 参数设置"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			for (i = 0; i < 5; i++) {
				m_interest_rate[i] = String2Double(infd.m_vecFindItem[g][2*i][0].strItem.GetBuffer()) / 100;
				if (infd.m_vecFindItem[g][2 * i + 1][0].strItem.CompareNoCase("yes") == 0)
					m_interest_half[i] = true;
				else
					m_interest_half[i] = false;

			}
			return true;
		}
	}
	
	return false;
}
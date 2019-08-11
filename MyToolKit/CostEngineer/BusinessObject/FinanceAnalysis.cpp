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
				bool lLoan = lscheme.find("���") != string::npos;
				bool rLoan = rscheme.find("���") != string::npos;
				bool lCost = lscheme.find("�ܳɱ�����") != string::npos;
				bool rCost = rscheme.find("�ܳɱ�����") != string::npos;
				bool lProfit = lscheme.find("�����������") != string::npos;
				bool rProfit = rscheme.find("�����������") != string::npos;
				bool lInput = lscheme.find("�ֽ�����") != string::npos;
				bool rInput = rscheme.find("�ֽ�����") != string::npos;
				bool lOutput = lscheme.find("�ֽ�����") != string::npos;
				bool rOutput = rscheme.find("�ֽ�����") != string::npos;
				if (lscheme != rscheme) {
					if (lLoan && rLoan) return lscheme < rscheme;
					else if (lLoan) return true;
					else if (rLoan) return false;
					else if (lCost) return true;
					else if (rCost) return false;
					else if (lInput) return true;
					else if (rInput) return false;
					else if (lOutput) return true;
					else if (rOutput) return false;
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
	bool bOK = true;
	map<int, double> mapMonth;
	map<int, double> mapMonthInput;
	map<int, double> mapMonthOutput;

	for (CFinanceAnalysisObj* e : m_objs) {
		int nMonth = String2Double(e->m_month.GetBuffer());
		if (e->m_scheme.Find("�ֽ�����") >= 0) {
			if (mapMonthInput.count(nMonth) == 0) {
				mapMonthInput[nMonth] = e->AmountOfMoney();
			}
			else {
				mapMonthInput[nMonth] += e->AmountOfMoney();
			}
		}
		if (e->m_scheme.Find("�ֽ�����") >= 0) {
			if (mapMonthOutput.count(nMonth) == 0) {
				mapMonthOutput[nMonth] = e->AmountOfMoney();
			}
			else {
				mapMonthOutput[nMonth] += e->AmountOfMoney();
			}
		}
		if (e->m_scheme.Find("�ֽ�") >= 0) {
			if (mapMonth.count(nMonth) == 0) {
				mapMonth[nMonth] = e->AmountOfMoney();
			}
			else {
				mapMonth[nMonth] += e->AmountOfMoney();
			}
		}
	}

	CGridDlg gridDlg;
	gridDlg.m_strTitle = "�ֽ�������";
	gridDlg.m_vecHeader.push_back("���");
	gridDlg.m_vecHeader.push_back("�ֽ�����(��Ԫ)");
	gridDlg.m_vecHeader.push_back("�ֽ�����(��Ԫ)");
	gridDlg.m_vecHeader.push_back("���ֽ�����(��Ԫ)");
	gridDlg.m_vecHeader.push_back("���־��ֽ�����(��Ԫ)");
	gridDlg.m_vecHeader.push_back("�ۼƿ��̬�����ڣ�(��Ԫ)");
	gridDlg.m_vecHeader.push_back("�ۼ�����ֵ(��Ԫ)");

	/* ���»��ܼ��� */
	double accStatic = 0;
	double accDynamic = 0;
	map<int, double>::iterator it = mapMonth.begin();
	for (; it != mapMonth.end(); it++) {
		int nMonth = it->first;
		double money = it->second;
		double input = mapMonthInput[nMonth];
		double output = mapMonthOutput[nMonth];
				
		vector<string> vec;
		vec.push_back(Int2String(nMonth));
		vec.push_back(Double2String(input, "%.3f"));
		vec.push_back(Double2String(output, "%.3f"));
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
				&& p->m_name.Find(name) >= 0) {
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
		vec.push_back(m_objs[i]->m_scheme.GetBuffer());
		vec.push_back(m_objs[i]->m_name.GetBuffer());
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
	infd.m_vecFindItem[0][i][0].strData = "�ֽ�����;�ֽ�����;�ܳɱ�����;�����������;���1;���2;���3;���4;���5";
	infd.m_vecFindItem[0][i][0].strItem = "�ֽ�����";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���㷽��"), 64);

	i++;
	string caption = "��ȣ���������ѡ�";
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, caption.c_str(), 64);
	infd.m_vecFindItem[0][i][0].nMin = 0;
	infd.m_vecFindItem[0][i][0].nMax = 100;

	infd.Init(_T("���� ����ѡ��"), _T("���� ����ѡ��"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		CString scheme = infd.m_vecFindItem[0][i++][0].strItem;
		int nMonth = atoi(infd.m_vecFindItem[0][i++][0].strItem.GetBuffer());
		CFinanceAnalysisObj* c = NewChild(scheme);
		if (nMonth <= 0) {
			if (c->CreateOrUpdate(menuCode, this)) {
				m_objs.push_back(c);

				SortByMonth();
				return true;
			}
			else {
				delete c;
			}
		}
		else {
			/* ��Ӹ��·ݵ�����ѡ�� */
			c->m_month = Int2String(nMonth).c_str();
			vector<string> options = c->GetOptions();
			for (string e : options) {
				c->m_name = e.c_str();
				double amount;
				if (GetAmountOfMoney(c->m_month, c->m_scheme, c->m_name, amount) == false) {
					CFinanceAnalysisObj * p = c->Clone();
					m_objs.push_back(p);
				}
			}
			delete c;
			SortByMonth();
			return true;
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
		if (GetAmountOfMoney(Int2String(i).c_str(), "�ֽ�����", "2.����˰��", amount)) {
			tax += amount;
		}
	}
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "�ֽ�����", "4.����˰��", amount)) {
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
		if (GetAmountOfMoney(Int2String(i).c_str(), "�ֽ�����", "2.����˰��", amount)) {
			tax += amount;
		}
	}
	for (int i = 1; i <= nMonth; i++) {
		double amount;
		if (GetAmountOfMoney(Int2String(i).c_str(), "�ֽ�����", "6.����˰��", amount)) {
			tax -= amount;
		}
	}
	tax -= m_tax_on_purchase;
	if (tax < 0) tax = 0;
	return tax;
}

/* ��ֹ�����ڳ���������� */
double CAfterFinancing::LoanRemaining(int nMonth, int nLoan) {
	
	if (nLoan >5 || nLoan < 1 ) return 0;
	string loanScheme = "���" + Int2String(nLoan);

	/* remain �����ֹǰ����ĩ�� ������� */
	double remain = 0;
	for (int i = 1; i < nMonth; i++) {
		double amount;
		remain = remain * (1 + m_loan_rate[nLoan - 1]);
		if (GetAmountOfMoney(Int2String(i).c_str(), loanScheme.c_str(), "1.����", amount)) {
			remain += amount;
			if (m_loan_borrow[nLoan - 1].CompareNoCase("����")==0) {
				/* �½��룬������Ϣ���� */
				remain += amount * 0.5 * m_loan_rate[nLoan - 1];
			}
			else  if (m_loan_borrow[nLoan - 1].CompareNoCase("�ڳ�") == 0) {
				remain += amount * m_loan_rate[nLoan - 1];
			} 
			
		}
		
		if (GetAmountOfMoney(Int2String(i).c_str(), loanScheme.c_str(), "2.����", amount)) {
			remain -= amount;
		}

		if (GetAmountOfMoney(Int2String(i).c_str(), loanScheme.c_str(), "3.��Ϣ", amount)) {
			remain -= amount;
		}
	}
	
	return remain;
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
	else if (scheme == "�ֽ�����")
		p = new CFinanceAnalysisObjB();
	else if (scheme.Find("���") >= 0)
		p = new CFinanceAnalysisObjC();
	else if (scheme.Find("�ܳɱ�����") >= 0)
		p = new CFinanceAnalysisObjD();
	else if (scheme.Find("�����������") >= 0)
		p = new CFinanceAnalysisObjE();

	if (p) p->m_scheme = scheme;

	return p;
}

void CAfterFinancing::Serialize(CArchive& ar, double version) {
	CFinanceAnalysis::Serialize(ar, version);
	if (ar.IsStoring()) {
		for (int i = 0; i < 5; i++) {
			ar << m_loan_rate[i];
			ar << m_loan_borrow[i];
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			ar >> m_loan_rate[i];
			ar >> m_loan_borrow[i];
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
			string caption = "���" + Int2String(i+1) + " - �������ʣ�%��";
			infd.m_vecFindItem[0][2*i][0].nType = CDlgTemplateBuilder::EDIT;
			memcpy(infd.m_vecFindItem[0][2*i][0].caption, caption.c_str(), 64);
			if (m_loan_rate[i] > 0.00001)
				infd.m_vecFindItem[0][2*i][0].strItem.Format("%.3f", m_loan_rate[i] * 100);
			infd.m_vecFindItem[0][2*i][0].dbMin = 0;
			infd.m_vecFindItem[0][2*i][0].dbMax = 100;

			caption = "���" + Int2String(i + 1) + " - ����ʱ��";
			infd.m_vecFindItem[0][2 * i + 1][0].nType = CDlgTemplateBuilder::COMBOBOX;
			memcpy(infd.m_vecFindItem[0][2 * i + 1][0].caption, caption.c_str(), 64);
			infd.m_vecFindItem[0][2 * i + 1][0].strData = "�ڳ�;����;��ĩ";
			if (m_loan_borrow[i].IsEmpty() == false)
				infd.m_vecFindItem[0][2 * i + 1][0].strItem = m_loan_borrow[i];
			else
				infd.m_vecFindItem[0][2 * i + 1][0].strItem = "�ڳ�";
		}
		
		infd.Init(_T("���̽��� ��������"), _T("���̽��� ��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			for (i = 0; i < 5; i++) {
				m_loan_rate[i] = String2Double(infd.m_vecFindItem[g][2*i][0].strItem.GetBuffer()) / 100;
				m_loan_borrow[i] = infd.m_vecFindItem[g][2 * i + 1][0].strItem;
			}
			return true;
		}
	}
	
	return false;
}

void CAfterFinancing::Calculate()
{
	{
		/* ȷ���ʽ�ȱ�ڣ��Ա�ȷ���Ƿ���Ҫ ��ʱ��� */
		map<int, double> mapMonth;
		for (CFinanceAnalysisObj* e : m_objs) {
			int nMonth = String2Double(e->m_month.GetBuffer());
			if (e->m_scheme.Find("�ֽ�") >= 0) {
				if (e->m_name.Find("�ʱ���") < 0) {
					if (mapMonth.count(nMonth) == 0) {
						mapMonth[nMonth] = e->AmountOfMoney();
					}
					else {
						mapMonth[nMonth] += e->AmountOfMoney();
					}
				}
			}
		}

		CGridDlg gridDlg;
		gridDlg.m_strTitle = "����ʽ�ȱ�ڱ�";
		gridDlg.m_vecHeader.push_back("���");
		gridDlg.m_vecHeader.push_back("�ʽ�ȱ��(��Ԫ)");


		map<int, double>::iterator it = mapMonth.begin();
		for (; it != mapMonth.end(); it++) {
			int nMonth = it->first;
			double money = it->second;

			vector<string> vec;
			vec.push_back(Int2String(nMonth));
			vec.push_back(Double2String(money, "%.3f"));

			gridDlg.m_vecData.push_back(vec);
		}
		gridDlg.DoModal();
	}

	{
		/* ����� */
		map<int, double> mapMonth;
		for (CFinanceAnalysisObj* e : m_objs) {
			int nMonth = String2Double(e->m_month.GetBuffer());
			if (e->m_scheme.Find("�ֽ�") >= 0) {
				double amount;

				if (e->m_name.Find("�ʱ���") < 0) {
					if (mapMonth.count(nMonth) == 0) {
						mapMonth[nMonth] = e->AmountOfMoney();
					}
					else {
						mapMonth[nMonth] += e->AmountOfMoney();
					}
				}
			}
		}
	}

	CFinanceAnalysis::Calculate();
}

/*****************************************************************************************/


void CFinanceAnalysisObj::SetDlgEditItem(CDyncItemGroupDlg & infd, CFinanceAnalysis * p, int i, string scheme, string caption, double dbMin, double dbMax, double def) {
	double amount;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, caption.c_str(), 64);
	if (scheme.empty() == false) {
		if (p->GetAmountOfMoney(m_month, scheme.c_str(), caption.c_str(), amount))
			infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", amount);
	}
	else {
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", def);
	}
	infd.m_vecFindItem[0][i][0].dbMin = dbMin;
	infd.m_vecFindItem[0][i][0].dbMax = dbMax;
}

void CFinanceAnalysisObj::Serialize(CArchive& ar, double version) {
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

bool CFinanceAnalysisObj::CopyTo(CFinanceAnalysis* parent) {
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
			if (!parent->GetAmountOfMoney(Int2String(i).c_str(), m_scheme, m_name, amount)) {
				/* �����ڣ������ */
				CFinanceAnalysisObj * p = Clone();
				p->m_month = Int2String(i).c_str();
				parent->m_objs.push_back(p);
			}
		}

		return true;
	}
	return false;
}

bool CFinanceAnalysisObj::CreateOrUpdate(string menuCode, CFinanceAnalysis* parent) {
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

	vector<string> options = GetOptions();
	string option; 
	for (int k = 0; k < options.size(); k++) {
		option += options[k];
		if (k < options.size() - 1)
			option += ";";
	}
	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
	infd.m_vecFindItem[0][i][0].strData = option.c_str();
	if (!m_name.IsEmpty())
		infd.m_vecFindItem[0][i][0].strItem = m_name;
	else
		infd.m_vecFindItem[0][i][0].strItem = options.size() > 0 ? options[0].c_str() : "";
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("����"), 64);

	i++;
	infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::EDIT;
	memcpy(infd.m_vecFindItem[0][i][0].caption, _T("���"), 64);
	if (m_amount_of_money != 0)
		infd.m_vecFindItem[0][i][0].strItem.Format("%.3f", m_amount_of_money);
	infd.m_vecFindItem[0][i][0].dbMin = -100000;
	infd.m_vecFindItem[0][i][0].dbMax = 1000000;


	infd.Init(_T("��������"), _T("��������"));
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
			if (parent->GetAmountOfMoney(month, m_scheme, name, amount)) {
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

/* ------------------------------------------------------------- */

 vector<string> CFinanceAnalysisObjA::GetOptions() {
	 vector<string> options;
	 options.push_back("1.����Ͷ��");
	 options.push_back("2.�����ʽ�Ͷ��");
	 options.push_back("3.��Ӫ�ɱ�(��������˰)");
	 options.push_back("4.����˰��");
	 options.push_back("5.Ӧ����ֵ˰");
	 options.push_back("6.��ֵ˰����");
	 options.push_back("7.ά����ӪͶ��");
	 options.push_back("8.��������˰");
	 return options;
}

double CFinanceAnalysisObjA::AmountOfMoney() {
	return  -m_amount_of_money;
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
		int nMonth = String2Double(m_month.GetBuffer());
		amount = parent->AccumulativeTax(nMonth);
		i = 0;
		SetDlgEditItem(infd, parent, i++, "", "�ۼƽ�ֹ����Ӧ����ֵ˰", 0, 100000, amount);

		amount = parent->AccumulativeTax(nMonth - 1);
		SetDlgEditItem(infd, parent, i++, "", "�ۼƽ�ֹ����Ӧ����ֵ˰", 0, 100000, amount);



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
		SetDlgEditItem(infd, parent, i++, "�ֽ�����", "Ӧ����ֵ˰", -100000, 100000);

		SetDlgEditItem(infd, parent, i++, "", "˰�𸽼ӷ���(%)", 0, 100000, parent->m_tax_surcharge_rate * 100);


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
	else if (m_name == "8.��������˰") {
		i = 0;
		SetDlgEditItem(infd, parent, i++, "�ֽ�����", "Ӫҵ����(��������˰)", -100000, 100000);

		SetDlgEditItem(infd, parent, i++, "�ֽ�����", "��������", -100000, 100000);

		SetDlgEditItem(infd, parent, i++, "�ֽ�����", "��Ӫ�ɱ�(��������˰)", -100000, 100000);

		SetDlgEditItem(infd, parent, i++, "�ֽ�����", "��ֵ˰����", -100000, 100000);

		SetDlgEditItem(infd, parent, i++, "�ֽ�����", "ά����ӪͶ��", -100000, 100000);

		SetDlgEditItem(infd, parent, i++, "�ܳɱ�����", "�۾ɷ�", 0, 100000);

		SetDlgEditItem(infd, parent, i++, "�ܳɱ�����", "̯����", 0, 100000);

		SetDlgEditItem(infd, parent, i++, "", "����˰��(%)", 0, 100000, parent->m_income_tax_rate * 100);


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

/* ------------------------------------------------------------ */

vector<string> CFinanceAnalysisObjA1::GetOptions() {
	vector<string> options;
	options.push_back("1.��Ŀ�ʱ���");
	options.push_back("2.���𳥻�");
	options.push_back("3.�����Ϣ����");
	options.push_back("4.�����ʽ�Ͷ��");
	options.push_back("5.��Ӫ�ɱ�(��������˰)");
	options.push_back("6.����˰��");
	options.push_back("7.Ӧ����ֵ˰");
	options.push_back("8.��ֵ˰����");
	options.push_back("9.ά����ӪͶ��");
	options.push_back("10.����˰");
	return options;
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
	if (m_name == "7.Ӧ����ֵ˰")
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

	if (m_name == "7.Ӧ����ֵ˰") {
		int nMonth = String2Double(m_month.GetBuffer());
		amount = parent->AccumulativeTax(nMonth);
		i = 0;
		SetDlgEditItem(infd, p, i++, "", "�ۼƽ�ֹ����Ӧ����ֵ˰", 0, 100000, amount);

		amount = parent->AccumulativeTax(nMonth - 1);
		SetDlgEditItem(infd, p, i++, "", "�ۼƽ�ֹ����Ӧ����ֵ˰", 0, 100000, amount);


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
		SetDlgEditItem(infd, p, i++, "�ֽ�����", "Ӧ����ֵ˰", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "", "˰�𸽼ӷ���(%)", 0, 100000, parent->m_tax_surcharge_rate * 100);
		

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
		SetDlgEditItem(infd, p, i++, "�����������", "�����ܶ�", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�����������", "��ǰ��ȿ���", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "", "����˰��(%)", -100000, 100000, p->m_income_tax_rate);

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			m_amount_of_money = (v1 - v2) * v3;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}

	return false;
}


/* --------------------------------------------- */

vector<string> CFinanceAnalysisObjB::GetOptions() {
	vector<string> options;
	options.push_back("1.Ӫҵ����(��������˰)");
	options.push_back("2.����˰��");
	options.push_back("3.��������");
	options.push_back("4.���չ̶��ʲ���ֵ");
	options.push_back("5.���������ʽ�");
	return options;
}


double CFinanceAnalysisObjB::AmountOfMoney() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjB::Description() {
	return string("�ֽ����� �� ") + Double2String(m_amount_of_money, "%.3f");
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

	if (m_name == "4.���չ̶��ʲ���ֵ") {

	}

	return false;
}

/* --------------------------------------------- */

vector<string> CFinanceAnalysisObjC::GetOptions() {
	vector<string> options;
	options.push_back("1.����");
	options.push_back("2.����");
	options.push_back("3.��Ϣ");
	return options;
}


double CFinanceAnalysisObjC::AmountOfMoney() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjC::Description() {
	return string("��� �� ") + Double2String(m_amount_of_money, "%.3f");
}

bool CFinanceAnalysisObjC::HasAssist() {

	if (m_name == "3.��Ϣ")
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

	if (m_name == "3.��Ϣ") {
		i = 0;
		amount = p->LoanRemaining(nMonth, nLoan);
		SetDlgEditItem(infd, p, i++, "", "��ֹ���ڳ����������", -0.01, 100000, amount);

		SetDlgEditItem(infd, p, i++, m_scheme.GetBuffer(), "��������(%)", 0, 100000, p->m_loan_rate[nLoan - 1] * 100);

		SetDlgEditItem(infd, p, i++, "", "����", 0, 100000);
	

		infd.m_vecFindItem[0][i][0].nType = CDlgTemplateBuilder::COMBOBOX;
		memcpy(infd.m_vecFindItem[0][i][0].caption, "�������ʱ��", 64);
		infd.m_vecFindItem[0][i][0].strData = "�ڳ�;����;��ĩ";
		if (p->m_loan_borrow[nLoan - 1].IsEmpty() == false)
			infd.m_vecFindItem[0][i][0].strItem = p->m_loan_borrow[nLoan - 1];
		else
			infd.m_vecFindItem[0][i][0].strItem = "�ڳ�";


		infd.Init(_T("�����²�����Ϣ"), _T("�����²�����Ϣ"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double rate = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;
			if (infd.m_vecFindItem[g][i++][0].strItem.CompareNoCase("����") == 0) {
				m_amount_of_money = v1 * rate + v2 * 0.5 * rate;
			}
			else if (infd.m_vecFindItem[g][i++][0].strItem.CompareNoCase("�ڳ�") == 0) {
				m_amount_of_money = v1 * rate + v2 * rate;
			}
			else {
				m_amount_of_money = v1 * rate;
			}
			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}

	return false;
}


/* --------------------------------------------- */

vector<string> CFinanceAnalysisObjD::GetOptions() {
	vector<string> options;
	options.push_back("1.�۾ɷ�");
	options.push_back("2.̯����");
	
	return options;
}


double CFinanceAnalysisObjD::AmountOfMoney() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjD::Description() {
	return string("�ɱ����� �� ") + Double2String(m_amount_of_money, "%.3f");
}

bool CFinanceAnalysisObjD::HasAssist() {

	return false;
}

bool CFinanceAnalysisObjD::Assist(CFinanceAnalysis* parent) {
	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;

	if (m_name == "4.���չ̶��ʲ���ֵ") {

	}

	return false;
}



/* --------------------------------------------- */

vector<string> CFinanceAnalysisObjE::GetOptions() {
	vector<string> options;
	options.push_back("1.�����ܶ�");
	options.push_back("2.��ǰ��ȿ���");
	options.push_back("3.������");
	options.push_back("4.�ɹ���������");
	options.push_back("5.����ӯ�๫����");
	options.push_back("6.Ӧ��Ͷ���߸�������");
	options.push_back("7.δ��������");
	options.push_back("7.���ڻ���δ��������");
	options.push_back("8.ʣ��δ��������");

	return options;
}


double CFinanceAnalysisObjE::AmountOfMoney() {
	return m_amount_of_money;
}

string CFinanceAnalysisObjE::Description() {
	return string("����������� �� ") + Double2String(m_amount_of_money, "%.3f");
}

bool CFinanceAnalysisObjE::HasAssist() {

	if (m_name.Find("�����ܶ�") >= 0)
		return true;
	return false;
}

bool CFinanceAnalysisObjE::Assist(CFinanceAnalysis* p) {

	CDyncItemGroupDlg infd;
	infd.CXCAPTION = 80;
	infd.CXCOMBOX = 100;
	infd.GROUP_NUM_PER_LINE = 3;
	int g = 0;
	int i = 0;
	double amount = 0;
	CAfterFinancing * parent = (CAfterFinancing *)p;

	if (m_name.Find("�����ܶ�") >= 0) {
		i = 0;
		SetDlgEditItem(infd, p, i++, "�ֽ�����", "Ӫҵ����(��������˰)", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ֽ�����", "��������", -100000, 100000); 

		SetDlgEditItem(infd, p, i++, "�ֽ�����", "�����Ϣ����", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ֽ�����", "��Ӫ�ɱ�(��������˰)", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ֽ�����", "��ֵ˰����", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ֽ�����", "ά����ӪͶ��", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ܳɱ�����", "�۾ɷ�", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ܳɱ�����", "̯����", -100000, 100000);
				

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
			double output6 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			m_amount_of_money = input1 + input2 - output1 - output2 - output3 - output4 - output5 - output6;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name.Find("������") >= 0) {
		i = 0;
		SetDlgEditItem(infd, p, i++, "�����������", "�����ܶ�", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�����������", "��ǰ��ȿ���", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "", "����˰��(%)", -100000, 100000, p->m_income_tax_rate);

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			
			m_amount_of_money = (v1 - v2) * v3;
			m_amount_of_money = v1 - m_amount_of_money;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name.Find("�ɹ���������") >= 0) {
		i = 0;
		SetDlgEditItem(infd, p, i++, "�����������", "������", -100000, 100000);
		
		SetDlgEditItem(infd, p, i++, "", "����ʣ��δ��������", -100000, 100000);

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			m_amount_of_money = (v1 + v2);

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name.Find("����ӯ�๫����") >= 0) {
		i = 0;
		SetDlgEditItem(infd, p, i++, "�����������", "������", 0, 100000);
		
		SetDlgEditItem(infd, p, i++, "", "����ӯ����(%)", -100000, 100000, 10);

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			m_amount_of_money = (v1 * v2);

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name.Find("Ӧ��Ͷ���߸�������") >= 0) {
		i = 0;
		SetDlgEditItem(infd, p, i++, "�����������", "�ɹ���������", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�����������", "����ӯ�๫����", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "", "Լ���ķ������", -100000, 100000, 10);

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;

			m_amount_of_money = (v1 - v2) * v3;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}

	}
	else if (m_name.Find("δ��������") >= 0) {
	i = 0;
	SetDlgEditItem(infd, p, i++, "�����������", "�ɹ���������", -100000, 100000);

	SetDlgEditItem(infd, p, i++, "�����������", "����ӯ�๫����", -100000, 100000);

	SetDlgEditItem(infd, p, i++, "�����������", "Ӧ��Ͷ���߸�������", -100000, 100000);

	infd.Init(_T("��������"), _T("��������"));
	if (infd.DoModal() == IDOK) {
		i = 0;
		g = 0;
		double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
		double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer()) / 100;

		m_amount_of_money = v1 - v2 - v3;

		if (m_amount_of_money < 0) m_amount_of_money = 0;
		return true;
	}

	}
	else if (m_name.Find("���ڻ���δ��������") >= 0) {
		double sum = 0;
		if(p->GetAmountOfMoney(m_month, "���1", "����", amount)) 
			sum += amount;
		if(p->GetAmountOfMoney(m_month, "���2", "����", amount))
			sum += amount;
		if(p->GetAmountOfMoney(m_month, "���3", "����", amount))
			sum += amount;
		if(p->GetAmountOfMoney(m_month, "���4", "����", amount))
			sum += amount;
		if(p->GetAmountOfMoney(m_month, "���5", "����", amount))
			sum += amount;

		i = 0;
		SetDlgEditItem(infd, p, i++, "", "Ӧ������", 0, 100000, sum);

		SetDlgEditItem(infd, p, i++, "�����������", "�ɹ���������", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�ܳɱ�����", "�۾ɷ�", 0, 100000);

		SetDlgEditItem(infd, p, i++, "�ܳɱ�����", "̯����", 0, 100000);


		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v4 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			m_amount_of_money = 0;
			if (v1 > (v2 + v3 + v4)) {
				m_amount_of_money = v2;

				CString source;
				source.Format("�ʽ�ȱ��:  %.3f", v1 - (v2 + v3 + v4));
				AfxMessageBox(source);
				paste(source);
			}
			else {
				m_amount_of_money = v1 - (v3 + v4);
			}

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}
	else if (m_name.Find("ʣ��δ��������") >= 0) {
		i = 0;
		SetDlgEditItem(infd, p, i++, "�����������", "������", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�����������", "����ӯ�๫����", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�����������", "Ӧ��Ͷ���߸�������", -100000, 100000);

		SetDlgEditItem(infd, p, i++, "�����������", "���ڻ���δ��������", -100000, 100000);

		infd.Init(_T("��������"), _T("��������"));
		if (infd.DoModal() == IDOK) {
			i = 0;
			g = 0;
			double v1 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v2 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v3 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());
			double v4 = String2Double(infd.m_vecFindItem[g][i++][0].strItem.GetBuffer());

			m_amount_of_money = v1 - v2 - v3 - v4;

			if (m_amount_of_money < 0) m_amount_of_money = 0;
			return true;
		}
	}

	return false;
}

// IndividualCsvFileView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "IndividualCsvFileView.h"


#include "BalanceCsvFileShow.h"
#include "IncomeStatementCsvFileShow.h"
#include "CashFlowsCsvFileShow.h"
#include "SohuFundHoldCsvFileShow.h"

// CIndividualCsvFileView

IMPLEMENT_DYNCREATE(CIndividualCsvFileView, CBaseGridCtlView)

CIndividualCsvFileView::CIndividualCsvFileView()
{
	m_pCsvFileShow = NULL;
}

CIndividualCsvFileView::~CIndividualCsvFileView()
{
}

BEGIN_MESSAGE_MAP(CIndividualCsvFileView, CBaseGridCtlView)
END_MESSAGE_MAP()


// CIndividualCsvFileView ��ͼ

void CIndividualCsvFileView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualCsvFileView ���

#ifdef _DEBUG
void CIndividualCsvFileView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualCsvFileView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndividualCsvFileView ��Ϣ�������


void CIndividualCsvFileView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	RedrawGridCtrl();
}


void CIndividualCsvFileView::ProcessXmlWParam(string msgType,string code,string model,\
											  string param1,string param2,string param3)
{
	RedrawGridCtrl();
}

//bool CIndividualCsvFileView::NeedSpecialDisplay(string val)
//{
//	if(val=="һ����Ӫ��������ֽ�����" ||
//		val=="" ||
//		val=="")
//		return true;
//	return false;
//}

void CIndividualCsvFileView::RedrawGridCtrl()
{

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		string strCsvFileName = "";
		if(pDoc->m_nCommandCode==ID_INDIVIDUAL_CSV_INCOME)
		{
			CIncomeStatement income;
			income.m_nCode = atoi(pDoc->m_nCode.c_str());
			strCsvFileName = income.GetCsvFileName();
			m_pCsvFileShow = new CIncomeStatementCsvFileShow();
		}
		if(pDoc->m_nCommandCode==ID_INDIVIDUAL_CSV_BALANCE)
		{
			CBalance income;
			income.m_nCode = atoi(pDoc->m_nCode.c_str());
			strCsvFileName = income.GetCsvFileName();
			m_pCsvFileShow = new CBalanceCsvFileShow();
		}
		if(pDoc->m_nCommandCode==ID_INDIVIDUAL_CSV_TRADING)
		{
			CNetEaseTradeDaily income;
			income.m_nCode = atoi(pDoc->m_nCode.c_str());
			strCsvFileName = income.GetCsvFileName();

		}
		if(pDoc->m_nCommandCode==ID_INDIVIDUAL_CSV_CASHFLOWS)
		{
			CCashFlows income;
			income.m_nCode = atoi(pDoc->m_nCode.c_str());
			strCsvFileName = income.GetCsvFileName();
			m_pCsvFileShow = new CCashFlowsCsvFileShow();
		}
		if(pDoc->m_nCommandCode==ID_INDIVIDUAL_CSV_FUND_HOLD)
		{
			CSohuFundHold income;
			income.m_nCode = atoi(pDoc->m_nCode.c_str());
			strCsvFileName = income.GetCsvFileName();
			m_pCsvFileShow = new CSohuFundHoldCsvFileShow();
		}
		
		if(strCsvFileName.empty()) return;

		//	���� CSV �ļ����ڴ�
		CCSVFile csvFile(strCsvFileName.c_str());
		csvFile.ReadAllData(m_arrayHeader, m_arrayData);
		csvFile.Close();

		if(m_arrayHeader.size()<=0)
		{
			CString str;
			str.Format("CSV �ļ���%s���쳣", strCsvFileName.c_str());
			AfxMessageBox(str);
			return;
		}

		try {
			m_pGridCtrl->SetRowCount(m_arrayData.size()+1);
			m_pGridCtrl->SetColumnCount(m_arrayHeader.size());
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		for (int row = 0; row < m_pGridCtrl->GetRowCount(); row++)
		{
			for (int col = 0; col < m_pGridCtrl->GetColumnCount(); col++)
			{ 
				string val;
				if(row < 1)
					val = m_arrayHeader[col];
				else 
					val = m_arrayData[row-1][col];
				if(m_pCsvFileShow)
				{
					GV_ITEM Item = m_pCsvFileShow->ProcessCell(row, col, val);
					if( m_arrayHeader[col].find("1231")!=string::npos)
					{
						// ��ȱ�����ı䱳��ɫ
						Item.crBkClr = RGB(196, 236, 196);
						Item.mask |= GVIF_BKCLR;
					}

					m_pGridCtrl->SetItem(&Item);
				}
				
			}
			int k = 1;
		}

		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetColumnWidth(0, 200);
	}

}

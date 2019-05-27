// IndividualCurrentAssetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "IndividualCurrentAssetView.h"


// CIndividualCurrentAssetView

IMPLEMENT_DYNCREATE(CIndividualCurrentAssetView, CIndividualDmGraphView)

CIndividualCurrentAssetView::CIndividualCurrentAssetView()
{

}

CIndividualCurrentAssetView::~CIndividualCurrentAssetView()
{
}

BEGIN_MESSAGE_MAP(CIndividualCurrentAssetView, CIndividualDmGraphView)
END_MESSAGE_MAP()


// CIndividualCurrentAssetView ��ͼ

void CIndividualCurrentAssetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualCurrentAssetView ���

#ifdef _DEBUG
void CIndividualCurrentAssetView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualCurrentAssetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndividualCurrentAssetView ��Ϣ�������


void CIndividualCurrentAssetView::RedrawDmGraph()
{
	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CStockApp * pApp = (CStockApp *)AfxGetApp();

	ASSERT_VALID(pDoc);	

	HRESULT hr;
	vector<string>   vec_annotion;
	vector<COLORREF> vec_clr;
	vector<double>	 vec_percent;
	map<int, double> map_summary_in;
	bool isHaveData;

	CCninfoBalance balance;
	CBussinessUtils::GetBalance(atoi(pDoc->m_nCode.c_str()), balance);
	if(balance.m_vec_row.size()>0)
	{
		int nStart = 0, nEnd = balance.m_vec_row.size()-1;
		if(m_StartDate> 0 && m_EndDate> m_StartDate)
		{
			//	Ѱ�ҡ���ʼ���ļ�¼
			for(int i=0 ; i<balance.m_vec_row.size(); i++)
			{
				COleDateTime odt ;
				odt.ParseDateTime(balance.m_vec_row[i][_T("��ֹ����")].c_str());
				if(odt.m_dt >= m_StartDate)
				{
					nStart = i;
					break;
				}
			}

			//	Ѱ�ҡ��������ļ�¼
			for(int i=balance.m_vec_row.size() - 1; i>=0; i--)
			{
				COleDateTime odt ;
				odt.ParseDateTime(balance.m_vec_row[i][_T("��ֹ����")].c_str());
				if(odt.m_dt<= m_EndDate)
				{
					nEnd = i;
					break;
				}
			}
		}

		CComVariant varrX, varrY;
		varrX.parray = SafeArrayCreateVector(VT_R8, 0, nEnd - nStart +1);
		if(varrX.parray == NULL)
			return ;
		varrX.vt = VT_ARRAY|VT_R8;

		varrY.parray = SafeArrayCreateVector(VT_R8, 0,  nEnd - nStart +1);
		if(varrY.parray == NULL)
			return ;
		varrY.vt = VT_ARRAY|VT_R8;

		for(long i=0; i<  nEnd - nStart +1; i++)
		{
			COleDateTime odt ;
			double yy = 0.0;
			odt.ParseDateTime(balance.m_vec_row[nStart + i][_T("��ֹ����")].c_str());
			hr = SafeArrayPutElement(varrX.parray, &i, &odt.m_dt);
			hr = SafeArrayPutElement(varrY.parray, &i, &yy);
		}
		SetGraphData(&varrX, &varrY, "��λ��", RGB(0,0,0));

		//////////////////////////////////////////////////////////////////////////
		// �����ʽ�

		CURRENT_ASSET_CURVE(m_vec_cash,"�����ʽ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_notes_receivable,"Ӧ��Ʊ��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_provision_of_settlement_fund,"���㱸����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_funds_lent,"����ʽ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_financial_assets_held_for_trading,"�����Խ����ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_derivative_financial_assets,"���������ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_notes_receivable,"Ӧ��Ʊ��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_accounts_receivable,"Ӧ���˿�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_advances_to_suppliers,"Ԥ������", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_insurance_premiums_receivable,"Ӧ�ձ���", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_cession_premiums_receivable,"Ӧ�շֱ��˿�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_provision_of_cession_receivable,"Ӧ�շֱ���ͬ׼����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_interests_receivable,"Ӧ����Ϣ", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_dividends_receivable,"Ӧ�չ���", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_other_receivable,"����Ӧ�տ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_export_tax_rebate,"Ӧ�ճ�����˰", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_subsidy_receivable,"Ӧ�ղ�����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_receivable_deposit,"Ӧ�ձ�֤��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_internal_receivables,"�ڲ�Ӧ�տ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_buying_and_selling_financial_assets,"���뷵�۽����ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_inventories,"���", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_deferred_expenses,"��̯����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_profit_and_loss_to_be_treated,"�����������ʲ�����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_non_current_assets_maturing_within_one_year,"һ���ڵ��ڵķ������ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_other_current_assets,"���������ʲ�", RGB(255, 128, 128), 2, 1)

		
		//////////////////////////////////////////////////////////////////////////
		// �������ߵ�ע��

		m_DMGraph.AutoRange();
		double xmin,xmax,ymin,ymax;
		m_DMGraph.GetAutoRange(&xmin, &xmax, &ymin, &ymax);
		double ystep = (ymax - ymin) /25;
		for(int k = 0; k<vec_annotion.size(); k++)
		{
			double sum = map_summary_in[nEnd];
			double percent = (vec_percent[k]/map_summary_in[nEnd]) * 100;
			char tmp[256];
			sprintf_s(tmp, 256, "  %.2f��", percent);
			string annotation = vec_annotion[k] + string(tmp); 
			SetGraphAnnotation(xmin, ymax - ystep*(vec_annotion.size() - k), annotation, vec_clr[k]);
		}
		m_DMGraph.SetRange(xmin, xmax , ymin, ymax + (ymax - ymin) * 0.02);
	}

	

}
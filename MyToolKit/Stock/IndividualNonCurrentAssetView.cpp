// IndividualNonCurrentAssetView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "IndividualNonCurrentAssetView.h"


// CIndividualNonCurrentAssetView

IMPLEMENT_DYNCREATE(CIndividualNonCurrentAssetView, CIndividualDmGraphView)

CIndividualNonCurrentAssetView::CIndividualNonCurrentAssetView()
{

}

CIndividualNonCurrentAssetView::~CIndividualNonCurrentAssetView()
{
}

BEGIN_MESSAGE_MAP(CIndividualNonCurrentAssetView, CIndividualDmGraphView)
END_MESSAGE_MAP()


// CIndividualNonCurrentAssetView ��ͼ

void CIndividualNonCurrentAssetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualNonCurrentAssetView ���

#ifdef _DEBUG
void CIndividualNonCurrentAssetView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualNonCurrentAssetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndividualNonCurrentAssetView ��Ϣ�������


void CIndividualNonCurrentAssetView::RedrawDmGraph()
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

	CCninfoBalance balance ;
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
		// 
		
		CURRENT_ASSET_CURVE(m_vec_loans_and_payments_on_behalf,"���Ŵ�����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_available_for_sale_financial_assets,"�ɹ����۽����ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_held_to_maturity_investments,"����������Ͷ��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_long_term_receivables,"����Ӧ�տ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_long_term_equity_investments,"���ڹ�ȨͶ��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_other_long_term_investments,"��������Ͷ��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_investment_real_estates,"Ͷ���Է��ز�", RGB(255, 128, 128), 2, 1)
		//NON_CURRENT_ASSET_CURVE(m_vec_original_value_of_fixed_assets,"�̶��ʲ�ԭֵ", RGB(255, 128, 128), 2, 1)
		//NON_CURRENT_ASSET_CURVE(m_vec_accumulated_depreciation,"�ۼ��۾�", RGB(255, 128, 128), 2, 1)
		//NON_CURRENT_ASSET_CURVE(m_vec_fixed_assets_net_value,"�̶��ʲ���ֵ", RGB(255, 128, 128), 2, 1)
		//NON_CURRENT_ASSET_CURVE(m_vec_fixed_assets_impairment_provision,"�̶��ʲ���ֵ׼��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_fixed_assets_net_book_value,"�̶��ʲ�����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_construction_in_progress,"�ڽ�����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_construction_supplies,"��������", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_fixed_assets_pending_disposal,"�̶��ʲ�����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_bearer_biological_assets,"�����������ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_public_welfare_biological_assets,"�����������ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_oil_and_natural_gas_assets,"�����ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_intangibel_assets,"�����ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_research_and_development_costs,"����֧��", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_goodwill,"����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_long_term_deferred_expenses,"���ڴ�̯����", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_circulation_right_for_equity_separation,"��Ȩ������ͨȨ", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_deferred_tax_assets,"��������˰�ʲ�", RGB(255, 128, 128), 2, 1)
		CURRENT_ASSET_CURVE(m_vec_other_non_current_assets,"�����������ʲ�", RGB(255, 128, 128), 2, 1)




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
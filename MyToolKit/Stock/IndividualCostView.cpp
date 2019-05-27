// IndividualCostView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "IndividualCostView.h"


// CIndividualCostView

IMPLEMENT_DYNCREATE(CIndividualCostView, CIndividualDmGraphView)

CIndividualCostView::CIndividualCostView()
{

}

CIndividualCostView::~CIndividualCostView()
{
}

BEGIN_MESSAGE_MAP(CIndividualCostView, CIndividualDmGraphView)
END_MESSAGE_MAP()


// CIndividualCostView ��ͼ

void CIndividualCostView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualCostView ���

#ifdef _DEBUG
void CIndividualCostView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualCostView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndividualCostView ��Ϣ�������

void CIndividualCostView::RedrawDmGraph()
{
	OverallCostsCurve();
}


void CIndividualCostView::OverallCostsCurve()
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

	CCninfoIncomeStatement balance;
	CBussinessUtils::GetIncomestatement(atoi(pDoc->m_nCode.c_str()), balance);
		
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
		varrX.parray = SafeArrayCreateVector(VT_R8, 0, balance.m_vec_row.size());
		if(varrX.parray == NULL)
			return ;
		varrX.vt = VT_ARRAY|VT_R8;

		varrY.parray = SafeArrayCreateVector(VT_R8, 0, balance.m_vec_row.size());
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
				
		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ�ɱ�", RGB(255, 128, 128), 2, 1)

		//////////////////////////////////////////////////////////////////////////
		
		CURRENT_ASSET_CURVE(m_vec_cash,"��Ϣ֧��",  RGB(rand()%128 + 128, rand()%128 + 128, rand()%128 + 128), 2, 1)


		//////////////////////////////////////////////////////////////////////////
		
		CURRENT_ASSET_CURVE(m_vec_cash,"�����Ѽ�Ӷ��֧��",  RGB(rand()%128 + 128, rand()%128 + 128, rand()%128 + 128), 2, 1)

		//////////////////////////////////////////////////////////////////////////
		
		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ˰�𼰸���",  RGB(rand()%128 + 128, rand()%128 + 128, rand()%128 + 128), 2, 1)


		//////////////////////////////////////////////////////////////////////////
		

		CURRENT_ASSET_CURVE(m_vec_cash,"���۷���", RGB(128, 255, 128), 2, 1)


		//////////////////////////////////////////////////////////////////////////
		

		CURRENT_ASSET_CURVE(m_vec_cash,"�������", RGB(128, 128, 255), 2, 1)

		//////////////////////////////////////////////////////////////////////////
		

		CURRENT_ASSET_CURVE(m_vec_cash,"�������", RGB(255, 255, 128), 2, 1)

		//////////////////////////////////////////////////////////////////////////
		

		CURRENT_ASSET_CURVE(m_vec_cash,"�ʲ���ֵ��ʧ", RGB(255, 128, 255), 2, 1)

		//////////////////////////////////////////////////////////////////////////
		// �����ӡ��Ӫҵ�����롱

		
		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ������", RGB(255, 0, 0), 0, 2)

		//////////////////////////////////////////////////////////////////////////
		// �������ߵ�ע��

		m_DMGraph.AutoRange();
		double xmin,xmax,ymin,ymax;
		m_DMGraph.GetAutoRange(&xmin, &xmax, &ymin, &ymax);
		double ystep = (ymax - ymin) /25;
		for(int k = 0; k<vec_annotion.size(); k++)
		{
			SetGraphAnnotation(xmin, ymax - ystep*(vec_annotion.size() - k), vec_annotion[k], vec_clr[k]);
		}
	
	}

}
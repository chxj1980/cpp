// IndividualNetProfitsView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "IndividualNetProfitsView.h"


// CIndividualNetProfitsView

IMPLEMENT_DYNCREATE(CIndividualNetProfitsView, CIndividualDmGraphView)

CIndividualNetProfitsView::CIndividualNetProfitsView()
{

}

CIndividualNetProfitsView::~CIndividualNetProfitsView()
{
}

BEGIN_MESSAGE_MAP(CIndividualNetProfitsView, CIndividualDmGraphView)
END_MESSAGE_MAP()


// CIndividualNetProfitsView ��ͼ

void CIndividualNetProfitsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CIndividualNetProfitsView ���

#ifdef _DEBUG
void CIndividualNetProfitsView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIndividualNetProfitsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIndividualNetProfitsView ��Ϣ�������



void CIndividualNetProfitsView::RedrawDmGraph()
{
	// ���ԡ�Yahoo �ɼ����ߡ� �� ͨ����Ϲɱ��ṹ����Ķ�̬��ӯ��

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
	CStockApp * pApp = (CStockApp *)AfxGetApp();

	ASSERT_VALID(pDoc);	

	HRESULT hr;
	vector<string>   vec_annotion;
	vector<COLORREF> vec_clr;
	vector<double>	 vec_percent;
	map<int, double> map_summary_in;
	map<int, double> map_summary_out;
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
		// Ӫҵ������
		
		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ������", RGB(255, 128, 128), 2, 1)
		
		//////////////////////////////////////////////////////////////////////////
		// +Ͷ������
		
		CURRENT_ASSET_CURVE(m_vec_cash,"Ͷ������", RGB(255, 128, 128), 1, 1)

		//////////////////////////////////////////////////////////////////////////
		// +Ӫҵ������
		
		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ������", RGB(255, 128, 128), 0, 1)

		//////////////////////////////////////////////////////////////////////////
		// Ӫҵ�ܳɱ�
		
		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ�ܳɱ�", RGB(128, 255, 128), 2, 1)


		//////////////////////////////////////////////////////////////////////////
		// +Ӫҵ��֧��
		

		CURRENT_ASSET_CURVE(m_vec_cash,"Ӫҵ��֧��", RGB(128, 255, 128), 1, 1)


		//////////////////////////////////////////////////////////////////////////
		// ����˰����
		
		CURRENT_ASSET_CURVE(m_vec_cash,"����˰����", RGB(128, 255, 128), 0, 1)

	}



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

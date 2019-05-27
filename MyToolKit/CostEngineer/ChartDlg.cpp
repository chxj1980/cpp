// PDFStructureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CostEngineer.h"
#include "ChartDlg.h"


// CPDFStructureDlg �Ի���

IMPLEMENT_DYNAMIC(CChartDlg, CDialog)

CChartDlg::CChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDlg::IDD, pParent)
{

}

CChartDlg::~CChartDlg()
{
}

void CChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHART, m_Chart);
}


BEGIN_MESSAGE_MAP(CChartDlg, CDialog)
END_MESSAGE_MAP()


// CPDFStructureDlg ��Ϣ�������

BOOL CChartDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CCostEngineerApp * pApp = (CCostEngineerApp *)AfxGetApp();

		
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/////////////////////////////////////////////////////////////////////////
BOOL CChartBarDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	double ymin, ymax;
	ymin = 1000000;
	ymax = -1000000;
	for (int i = 0; i < m_vecY.size(); i++)
	{
		if (ymin > m_vecY[i])	ymin = m_vecY[i];
		if (ymax < m_vecY[i])	ymax = m_vecY[i];
	}

	double xmin, xmax;
	xmin = 1000000;
	xmax = -1000000;
	for (int i = 0; i < m_vecX.size(); i++)
	{
		if (xmin > m_vecX[i])	xmin = m_vecX[i];
		if (xmax < m_vecX[i])	xmax = m_vecX[i];
	}

	CChartStandardAxis* pLeftAxis = m_Chart.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetMinMax(0, ymax + 3);

	CChartStandardAxis* pBottomAxis = m_Chart.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetMinMax(0, xmax + 1);

	CChartBarSerie* pBarSeries = m_Chart.CreateBarSerie(false, false);
	pBarSeries->SetBaseLine(false, 0);
	pBarSeries->SetGroupId(1);
	pBarSeries->SetBarWidth(5);
	pBarSeries->SetName("�ۼƴ���");

	for (long i = 0; i < m_vecY.size(); i++)
	{
		/*COleDateTime odt;
		odt.ParseDateTime(capital.m_vec_report_date[i].c_str());*/
		pBarSeries->AddPoint(m_vecX[i], m_vecY[i]);
	}

	m_Chart.RefreshCtrl();
	m_Chart.GetLegend()->SetVisible(true);
	return true;
}
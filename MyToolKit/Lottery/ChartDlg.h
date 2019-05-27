#pragma once
#include "afxcmn.h"
#include "../ChartCtrl/ChartCtrl.h"

#include "ChartCandlestickSerie.h"
#include "ChartBarSerie.h"
#include "ChartSurfaceSerie.h"
#include "ChartLineSerie.h"
#include "ChartPointsSerie.h"
#include "ChartLabel.h"

#include "ChartAxisLabel.h"


// CPDFStructureDlg �Ի���

class CChartDlg : public CDialog
{
	DECLARE_DYNAMIC(CChartDlg)

public:
	CChartDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChartDlg();

// �Ի�������
	enum { IDD = IDD_CHART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CChartCtrl m_Chart;
	

	vector<string>			m_vecHeader;
	vector<vector<string>>	m_vecData;

	virtual BOOL OnInitDialog();
};

class CChartBarDlg : public CChartDlg
{
	//DECLARE_DYNAMIC(CChartDlg)

public:
	CChartBarDlg(CWnd* pParent = NULL) {}
	virtual ~CChartBarDlg() {}

	vector<double>	m_vecX;
	vector<double>	m_vecY;

	virtual BOOL OnInitDialog();
};
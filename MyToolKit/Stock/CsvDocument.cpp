// CsvDocument.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "CsvDocument.h"




// CCsvDocument

IMPLEMENT_DYNCREATE(CCsvDocument, CDocument)

CCsvDocument::CCsvDocument()
{
	m_nCurrStockData = -1;
	m_vecStockDataModel.push_back(new CIncomeStatement);
	m_vecStockDataModel.push_back(new CTradingDaily);
	m_vecStockDataModel.push_back(new CNetEaseTradeDaily);

	m_vecStockDataModel.push_back(new CBalance);
	m_vecStockDataModel.push_back(new CCashFlows);
	m_vecStockDataModel.push_back(new CEntrepreneurship);
	m_vecStockDataModel.push_back(new CSmallMidEnterprise);
	m_vecStockDataModel.push_back(new CShenzhenAshares);
	m_vecStockDataModel.push_back(new CCapitalStructure);
	m_vecStockDataModel.push_back(new CShanghaiStockInfo);
	m_vecStockDataModel.push_back(new CCapitalFlows163);
	m_vecStockDataModel.push_back(new CSohuPerformanceForecast);
	m_vecStockDataModel.push_back(new CSohuMainIncomeComposition);
	m_vecStockDataModel.push_back(new CSohuFundHold);
}

BOOL CCsvDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CCsvDocument::~CCsvDocument()
{
	for(int i=0; i<m_vecStockDataModel.size(); i++)
	{
		delete m_vecStockDataModel[i];
		m_vecStockDataModel[i] = NULL;
	}
}


BEGIN_MESSAGE_MAP(CCsvDocument, CDocument)
	ON_COMMAND(ID_CSV_OPEN, &CCsvDocument::OnCsvOpen)
	ON_COMMAND(ID_CSV_IMPORT, &CCsvDocument::OnCsvImport)
END_MESSAGE_MAP()


// CCsvDocument ���

#ifdef _DEBUG
void CCsvDocument::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CCsvDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CCsvDocument ���л�

void CCsvDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
#endif


// CCsvDocument ����

void CCsvDocument::OnCsvOpen()
{
	// TODO: �ڴ���������������

	TCHAR szFileName[_MAX_PATH] = { 0 };
	OPENFILENAMEA ofn = {0};
	LPCTSTR szFilter = "Comma separated values (*.CSV)\0*.CSV\0All files (*.*)\0*.*\0", defExt = "CSV";
	static TCHAR szDir[_MAX_DIR] = { 0 };
	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= theApp.GetMainWnd()->m_hWnd;
	ofn.hInstance		= NULL; //theApp.getInstance();
	ofn.lpstrFilter		= szFilter;
	ofn.lpstrFile		= szFileName;
	ofn.nMaxFile		= _MAX_PATH;
	ofn.Flags			= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR /*���ı䵱ǰĿ¼*/;
	ofn.lpstrDefExt		= defExt;

	if(GetOpenFileNameA(&ofn) == 0)
		return ;

		
	//	���ļ������л�ȡ����Ʊ���롱
	int k = 0;
	for(; k<m_vecStockDataModel.size(); k++)
	{
		if(m_vecStockDataModel[k]->ParseCsvFileName(szFileName))
		{
			CString str;
			str.Format("CSV �ļ����ƽ����ɹ�������Ʊ���� %d ��\"%s\"", \
				m_vecStockDataModel[k]->m_nCode, \
				m_vecStockDataModel[k]->ModelType().c_str());
			AfxMessageBox(str);
			break;
		}
	}
	if(k== m_vecStockDataModel.size())
	{
		AfxMessageBox("CSV �ļ����Ͳ�֧��");
		return;
	}

	//	���浱ǰ���ļ������л�ȡ����������
	m_nCurrStockData = k;

	//	���� CSV �ļ����ڴ�
	CCSVFile csvFile(szFileName);
	csvFile.ReadAllData(m_arrayHeader, m_arrayData);
	csvFile.Close();
	
	UpdateAllViews(NULL);

	return;
}

//	���뵽���ݿ�
UINT CsvImportThreadFunc(LPVOID param)
{
	stringstream ss;
	CStockDataModel * pModel = (CStockDataModel *)param;

	pModel->ImportToDatabase();
	delete pModel;
	return 0;
}


void CCsvDocument::OnCsvImport()
{
	// TODO: �ڴ���������������

	int k = 0;
	if(m_nCurrStockData >=0 && m_nCurrStockData < m_vecStockDataModel.size())
	{
		if(m_vecStockDataModel[m_nCurrStockData]->CheckReport(m_arrayHeader, m_arrayData)>=0)
		{
			CString str;
			str.Format("CSV �ļ������ݷ��� \"%s\"��ȷ����ʼ�������ݿ�", \
				m_vecStockDataModel[m_nCurrStockData]->ModelType().c_str());
			AfxMessageBox(str);
			m_vecStockDataModel[m_nCurrStockData]->ParseCsvFile(m_arrayHeader, m_arrayData);
			m_vecStockDataModel[m_nCurrStockData]->ImportToDatabase();
			
		}
		else
			AfxMessageBox("CSV �ļ����ݲ�ƥ��");
		
	}
	else
	{
		AfxMessageBox("CSV �ļ�����δ֪");
	}

}

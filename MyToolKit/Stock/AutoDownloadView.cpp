// AutoDownloadView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "IndividualShareDoc.h"
#include "AutoDownloadView.h"
#include "BaseMessageElementsParser.h"


//////////////////////////////////////////////////////////////////////////
// CAutoDownloadView

IMPLEMENT_DYNCREATE(CAutoDownloadView, CEditView)

CAutoDownloadView::CAutoDownloadView()
{
	m_bDownloading = NULL;
	m_bAutoClose = false;
}

CAutoDownloadView::~CAutoDownloadView()
{
}

BEGIN_MESSAGE_MAP(CAutoDownloadView, CEditView)
	ON_COMMAND(ID_AUTO_DOWNLOAD_LIST, &CAutoDownloadView::OnAutoDownloadList)
	ON_COMMAND(ID_DOWNLOAD_STOCKINFO_SHENZHEN_ASHARE, &CAutoDownloadView::OnDownloadStockinfoShenzhenAshare)
	ON_COMMAND(ID_DOWNLOAD_STOCKINFO_SMALLANDMID, &CAutoDownloadView::OnDownloadStockinfoSmallandmid)
	ON_COMMAND(ID_DOWNLOAD_STOCKINFO_ENTERPRENEUR, &CAutoDownloadView::OnDownloadStockinfoEnterpreneur)
	ON_COMMAND(ID_DOWNLOAD_TRADINGDAILY_ENTERPRENUER, &CAutoDownloadView::OnDownloadTradingdailyEnterprenuer)
	ON_COMMAND(ID_DOWNLOAD_FINANCE_ENTERPRENUER, &CAutoDownloadView::OnDownloadFinanceEnterprenuer)
	ON_MESSAGE(WM_USER_LOG_1, OnUserLogWParam_1)
	ON_MESSAGE(WM_USER_XML, OnUserXmlWParam)
	ON_COMMAND(ID_DOWNLOAD_STOCKINFO_SHANGHAI, &CAutoDownloadView::OnDownloadStockinfoShanghai)
	ON_COMMAND(ID_DOWNLOAD_TRADINGDAILY_SHENZHEN_ASHARE, &CAutoDownloadView::OnDownloadTradingdailyShenzhenAshare)
	ON_COMMAND(ID_DOWNLOAD_TRADINGDAILY_SMALL_AND_MID, &CAutoDownloadView::OnDownloadTradingdailySmallAndMid)
	ON_COMMAND(ID_DOWNLOAD_TRADINGDAILY_SHANGHAISTOCK, &CAutoDownloadView::OnDownloadTradingdailyShanghaistock)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_TRADINGDAILY_SHANGHAISTOCK, &CAutoDownloadView::OnUpdateDownloadTradingdailyShanghaistock)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_TRADINGDAILY_SHENZHEN_ASHARE, &CAutoDownloadView::OnUpdateDownloadTradingdailyShenzhenAshare)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_TRADINGDAILY_SMALL_AND_MID, &CAutoDownloadView::OnUpdateDownloadTradingdailySmallAndMid)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_TRADINGDAILY_ENTERPRENUER, &CAutoDownloadView::OnUpdateDownloadTradingdailyEnterprenuer)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FINANCE_ENTERPRENUER, &CAutoDownloadView::OnUpdateDownloadFinanceEnterprenuer)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FINANCE_SHANGHAI, &CAutoDownloadView::OnUpdateDownloadFinanceShanghai)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FINANCE_SMALL_AND_MID, &CAutoDownloadView::OnUpdateDownloadFinanceSmallAndMid)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FINANCE_SHENZHEN_ASHARE, &CAutoDownloadView::OnUpdateDownloadFinanceShenzhenAshare)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CAPITIALSTRUCT_SHANGHAI, &CAutoDownloadView::OnUpdateDownloadCapitialstructShanghai)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STOCKINFO_SHENZHEN_ASHARE, &CAutoDownloadView::OnUpdateDownloadStockinfoShenzhenAshare)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STOCKINFO_SMALLANDMID, &CAutoDownloadView::OnUpdateDownloadStockinfoSmallandmid)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STOCKINFO_ENTERPRENEUR, &CAutoDownloadView::OnUpdateDownloadStockinfoEnterpreneur)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STOCKINFO_SHANGHAI, &CAutoDownloadView::OnUpdateDownloadStockinfoShanghai)
	ON_COMMAND(ID_DOWNLOAD_FINANCE_SHENZHEN_ASHARE, &CAutoDownloadView::OnDownloadFinanceShenzhenAshare)
	ON_COMMAND(ID_DOWNLOAD_FINANCE_SMALL_AND_MID, &CAutoDownloadView::OnDownloadFinanceSmallAndMid)
	ON_COMMAND(ID_DOWNLOAD_FINANCE_SHANGHAI, &CAutoDownloadView::OnDownloadFinanceShanghai)
	ON_COMMAND(ID_DOWNLOAD_CAPITIALSTRUCT_SHANGHAI, &CAutoDownloadView::OnDownloadCapitialstructShanghai)
	ON_COMMAND(ID_DOWNLOAD_CAPITIALSTRUCT_SHENZHEN, &CAutoDownloadView::OnDownloadCapitialstructShenzhen)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CAPITIALSTRUCT_SHENZHEN, &CAutoDownloadView::OnUpdateDownloadCapitialstructShenzhen)
	ON_COMMAND(ID_DOWNLOAD_SOUHU_STOCK_PLATE, &CAutoDownloadView::OnDownloadSouhuStockPlate)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_SOUHU_STOCK_PLATE, &CAutoDownloadView::OnUpdateDownloadSouhuStockPlate)
	ON_COMMAND(ID_DOWNLOAD_CAPITALFLOW_SHENZHEN_ASHARE, &CAutoDownloadView::OnDownloadCapitalflowShenzhenAshare)
	ON_COMMAND(ID_DOWNLOAD_CAPITALFLOW_SMALL_AND_MID, &CAutoDownloadView::OnDownloadCapitalflowSmallAndMid)
	ON_COMMAND(ID_DOWNLOAD_CAPITALFLOW_ENTERPRENUER, &CAutoDownloadView::OnDownloadCapitalflowEnterprenuer)
	ON_COMMAND(ID_DOWNLOAD_CAPITALFLOW_SHANGHAISTOCK, &CAutoDownloadView::OnDownloadCapitalflowShanghaistock)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CAPITALFLOW_SHENZHEN_ASHARE, &CAutoDownloadView::OnUpdateDownloadCapitalflowShenzhenAshare)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CAPITALFLOW_SMALL_AND_MID, &CAutoDownloadView::OnUpdateDownloadCapitalflowSmallAndMid)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CAPITALFLOW_ENTERPRENUER, &CAutoDownloadView::OnUpdateDownloadCapitalflowEnterprenuer)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CAPITALFLOW_SHANGHAISTOCK, &CAutoDownloadView::OnUpdateDownloadCapitalflowShanghaistock)
	ON_COMMAND(ID_DOWNLOAD_PERFORMANCE_FORECAST, &CAutoDownloadView::OnDownloadPerformanceForecast)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_PERFORMANCE_FORECAST, &CAutoDownloadView::OnUpdateDownloadPerformanceForecast)
	ON_COMMAND(ID_DOWNLOAD_INCOME_COMPOSITION, &CAutoDownloadView::OnDownloadIncomeComposition)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_INCOME_COMPOSITION, &CAutoDownloadView::OnUpdateDownloadIncomeComposition)
	ON_COMMAND(ID_DOWNLOAD_FUND_HOLD_SHENZHEN_ASHARE, &CAutoDownloadView::OnDownloadFundHoldShenzhenAshare)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FUND_HOLD_SHENZHEN_ASHARE, &CAutoDownloadView::OnUpdateDownloadFundHoldShenzhenAshare)
	ON_COMMAND(ID_DOWNLOAD_FUND_HOLD_ENTERPRENUER, &CAutoDownloadView::OnDownloadFundHoldEnterprenuer)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FUND_HOLD_ENTERPRENUER, &CAutoDownloadView::OnUpdateDownloadFundHoldEnterprenuer)
	ON_COMMAND(ID_DOWNLOAD_FUND_HOLD_SMALL_AND_MID, &CAutoDownloadView::OnDownloadFundHoldSmallAndMid)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FUND_HOLD_SMALL_AND_MID, &CAutoDownloadView::OnUpdateDownloadFundHoldSmallAndMid)
	ON_COMMAND(ID_DOWNLOAD_FUND_HOLD_SHANGHAI, &CAutoDownloadView::OnDownloadFundHoldShanghai)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_FUND_HOLD_SHANGHAI, &CAutoDownloadView::OnUpdateDownloadFundHoldShanghai)
	ON_COMMAND(ID_DOWNLOAD_HEXUN_RESEARCH_PAPER, &CAutoDownloadView::OnDownloadHexunResearchPaper)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_HEXUN_RESEARCH_PAPER, &CAutoDownloadView::OnUpdateDownloadHexunResearchPaper)
	ON_COMMAND(ID_DOWNLOAD_HUSHENG300_INDEX, &CAutoDownloadView::OnDownloadHusheng300Index)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_HUSHENG300_INDEX, &CAutoDownloadView::OnUpdateDownloadHusheng300Index)
	ON_COMMAND(ID_DOWNLOAD_CFFEX_FUTURE_DAILY, &CAutoDownloadView::OnDownloadCffexFutureDaily)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CFFEX_FUTURE_DAILY, &CAutoDownloadView::OnUpdateDownloadCffexFutureDaily)
	ON_COMMAND(ID_DOWNLOAD_STATSGOV_HGYD, &CAutoDownloadView::OnDownloadStatsgovHgyd)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STATSGOV_HGYD, &CAutoDownloadView::OnUpdateDownloadStatsgovHgyd)
	ON_COMMAND(ID_DOWNLOAD_STATSGOV_HGJD, &CAutoDownloadView::OnDownloadStatsgovHgjd)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STATSGOV_HGJD, &CAutoDownloadView::OnUpdateDownloadStatsgovHgjd)
	ON_COMMAND(ID_DOWNLOAD_STATSGOV_HGND, &CAutoDownloadView::OnDownloadStatsgovHgnd)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STATSGOV_HGND, &CAutoDownloadView::OnUpdateDownloadStatsgovHgnd)
	ON_COMMAND(ID_DOWNLOAD_STATSGOV_FSYD, &CAutoDownloadView::OnDownloadStatsgovFsyd)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STATSGOV_FSYD, &CAutoDownloadView::OnUpdateDownloadStatsgovFsyd)
	ON_COMMAND(ID_DOWNLOAD_STATSGOV_FSJD, &CAutoDownloadView::OnDownloadStatsgovFsjd)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STATSGOV_FSJD, &CAutoDownloadView::OnUpdateDownloadStatsgovFsjd)
	ON_COMMAND(ID_DOWNLOAD_STATSGOV_FSND, &CAutoDownloadView::OnDownloadStatsgovFsnd)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_STATSGOV_FSND, &CAutoDownloadView::OnUpdateDownloadStatsgovFsnd)
	ON_COMMAND(ID_DOWNLOAD_CNINFO_ANNOUNCEMENT, &CAutoDownloadView::OnDownloadCninfoAnnouncement)
	ON_UPDATE_COMMAND_UI(ID_DOWNLOAD_CNINFO_ANNOUNCEMENT, &CAutoDownloadView::OnUpdateDownloadCninfoAnnouncement)
END_MESSAGE_MAP()


// CAutoDownloadView ���

#ifdef _DEBUG
void CAutoDownloadView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CAutoDownloadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG

LRESULT CAutoDownloadView::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;
	
	// make sure passed string is valid (this is important to prevent unexpected
	// results if an invalid string is passed)
	if (CMessageString::IsStringValid(pString))
	{
		CString curString;
		GetEditCtrl().GetWindowText(curString);
		if(curString.GetLength()>2 * 1024)
		{
			curString = curString.Right(2 * 1024);
		}

		curString += *pString;
		GetEditCtrl().SetWindowText(curString);
		GetEditCtrl().LineScroll(GetEditCtrl().GetLineCount()-1, 0 );
		delete pString;
	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}


void CAutoDownloadView::StartupDownloadThread(int downloadType)
{
	if(m_bDownloading==NULL)
	{
		CDownloadRequest * req = new CDownloadRequest;
		req->m_nDownloadType = downloadType;
		req->m_hwnd = m_hWnd;
		req->m_nLogType = WM_USER_LOG_1;
		CWinThread * pThread = ((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
		m_bDownloading =pThread->m_hThread;
	}
}

void CAutoDownloadView::OnUpdateCmdUIDownload(CCmdUI *pCmdUI)
{
	if(m_bDownloading==NULL)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

// CAutoDownloadView ��Ϣ�������

void CAutoDownloadView::OnAutoDownloadList()
{
	// TODO: �ڴ���������������

	// CWinThread * pThread = AfxBeginThread(AutoDownloadThreadFunc, this);
	
}

void CAutoDownloadView::OnDownloadStockinfoShenzhenAshare()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STOCKINFO_SHENZHEN_ASHARE);
}

void CAutoDownloadView::OnDownloadStockinfoSmallandmid()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STOCKINFO_SMALLANDMID);

}

void CAutoDownloadView::OnDownloadStockinfoEnterpreneur()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STOCKINFO_ENTERPRENEUR);

}

void CAutoDownloadView::OnDownloadTradingdailyEnterprenuer()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_TRADINGDAILY_ENTERPRENUER);

}

void CAutoDownloadView::OnDownloadFinanceEnterprenuer()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FINANCE_ENTERPRENUER);
}


void CAutoDownloadView::OnDownloadFinanceShenzhenAshare()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FINANCE_SHENZHEN_ASHARE);
}

void CAutoDownloadView::OnDownloadFinanceSmallAndMid()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FINANCE_SMALL_AND_MID);
}

void CAutoDownloadView::OnDownloadFinanceShanghai()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FINANCE_SHANGHAI);

}


void CAutoDownloadView::OnDownloadStockinfoShanghai()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STOCKINFO_SHANGHAI);

}

void CAutoDownloadView::OnDownloadTradingdailyShenzhenAshare()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_TRADINGDAILY_SHENZHEN_ASHARE);

}

void CAutoDownloadView::OnDownloadTradingdailySmallAndMid()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_TRADINGDAILY_SMALL_AND_MID);

}

void CAutoDownloadView::OnDownloadTradingdailyShanghaistock()
{
	// TODO: �ڴ���������������

	StartupDownloadThread(ID_DOWNLOAD_TRADINGDAILY_SHANGHAISTOCK);
	
}


void CAutoDownloadView::OnDownloadCapitialstructShanghai()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CAPITIALSTRUCT_SHANGHAI);
}

void CAutoDownloadView::OnDownloadCapitialstructShenzhen()
{
	// TODO: �ڴ���������������
	/*CCapitalStructOf10jqka * pCapital = new CCapitalStructOf10jqka;
	pCapital->m_nCode = 300067;

	pCapital->SaveAsCsv();
	delete pCapital;*/
	StartupDownloadThread(ID_DOWNLOAD_CAPITIALSTRUCT_SHENZHEN);

}

//////////////////////////////////////////////////////////////////////////
//	�˵���״̬����

void CAutoDownloadView::OnUpdateDownloadTradingdailyShanghaistock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}



void CAutoDownloadView::OnUpdateDownloadTradingdailyShenzhenAshare(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);

}

void CAutoDownloadView::OnUpdateDownloadTradingdailySmallAndMid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);

}

void CAutoDownloadView::OnUpdateDownloadTradingdailyEnterprenuer(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);

}

void CAutoDownloadView::OnUpdateDownloadFinanceEnterprenuer(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadFinanceShanghai(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadFinanceSmallAndMid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadFinanceShenzhenAshare(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadCapitialstructShanghai(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadStockinfoShenzhenAshare(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadStockinfoSmallandmid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadStockinfoEnterpreneur(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadStockinfoShanghai(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadCapitialstructShenzhen(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	
	// TODO: �ڴ����ר�ô����/����û���

	//CFont* ptf=GetEditCtrl().GetFont();	// �õ�ԭ��������
	//LOGFONT lf; 
	//ptf->GetLogFont(&lf); 
	//lf.lfHeight = 20; // �ı�����߶� 
	//strcpy (lf.lfFaceName, "����");			// �ı��������� 
	//m_editFont.CreateFontIndirect(&lf); 

	m_editFont.CreatePointFont(100, "����_GB2312");   

	GetEditCtrl().SetFont(&m_editFont);	// ����������


	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	m_bAutoClose = true;
	if(m_bDownloading==NULL && pDoc->m_vecCommandCode.size()>0)
	{
		/* ���ղ˵������е������������  */

		vector<int>::iterator it =  pDoc->m_vecCommandCode.begin();
		int nCommand = *it;
		pDoc->m_vecCommandCode.erase(it);

		StartupDownloadThread(nCommand);
	}
	else if(m_bDownloading==NULL && pDoc->m_nCommandCode>0)
	{
		/* ���ղ˵����ϵ������������  */

		StartupDownloadThread(pDoc->m_nCommandCode);
	}
	else if(m_bDownloading==NULL && atoi(pDoc->m_nCode.c_str())>=0)
	{
		/* ������������ */
		CDownloadRequest * req = new CDownloadRequest;
		 req->m_nDownloadType = ID_DOWNLOAD_INDIVIDUAL;
		 req->m_hwnd = m_hWnd;
		 req->m_vecCode.push_back(atoi(pDoc->m_nCode.c_str()));
		 req->m_nLogType = WM_USER_LOG_1;

		CWinThread * pThread = ((CStockApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc,req);
		
		m_bDownloading = pThread->m_hThread;
	}
	else
	{
		m_bAutoClose = false;
	}

	if( 1 /*m_bAutoClose*/)
	{
		//ʹ����ܴ��ڵġ�Close��ϵͳ�˵�����ʧЧ
		CMenu* pMenu=GetParentFrame()->GetSystemMenu(false);
		// pMenu->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_GRAYED);
		pMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND);

	}
}



LRESULT CAutoDownloadView::OnUserXmlWParam(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;

	// make sure passed string is valid (this is important to prevent unexpected
	// results if an invalid string is passed)
	if (CMessageString::IsStringValid(pString))
	{
		CBaseMessageElementsParser parser(this);
		parser.Parse(pString->GetBuffer(), pString->GetLength());
		delete pString;
	
		if(parser.msg_type=="DownloadFinished")
		{
			m_bDownloading = NULL;

			/*�Ӳ˵��������ȡ����һ��ִ��*/
			CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();
			if(pDoc->m_vecCommandCode.size()>0)
			{
				vector<int>::iterator it =  pDoc->m_vecCommandCode.begin();
				int nCommand = *it;
				pDoc->m_vecCommandCode.erase(it);

				StartupDownloadThread(nCommand);
			}
			else if(m_bAutoClose)
			{
				/* ������ɣ��رձ���ͼ */
				this->GetParentFrame()->PostMessage(WM_CLOSE);
			}
		}
	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}
void CAutoDownloadView::OnDownloadSouhuStockPlate()
{
	// TODO: �ڴ���������������

	StartupDownloadThread(ID_DOWNLOAD_SOUHU_STOCK_PLATE);
}

void CAutoDownloadView::OnUpdateDownloadSouhuStockPlate(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadCapitalflowShenzhenAshare()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CAPITALFLOW_SHENZHEN_ASHARE);
}

void CAutoDownloadView::OnDownloadCapitalflowSmallAndMid()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CAPITALFLOW_SMALL_AND_MID);
}

void CAutoDownloadView::OnDownloadCapitalflowEnterprenuer()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CAPITALFLOW_ENTERPRENUER);
}

void CAutoDownloadView::OnDownloadCapitalflowShanghaistock()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CAPITALFLOW_SHANGHAISTOCK);
}

void CAutoDownloadView::OnUpdateDownloadCapitalflowShenzhenAshare(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadCapitalflowSmallAndMid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadCapitalflowEnterprenuer(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnUpdateDownloadCapitalflowShanghaistock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadPerformanceForecast()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_PERFORMANCE_FORECAST);
}

void CAutoDownloadView::OnUpdateDownloadPerformanceForecast(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadIncomeComposition()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_INCOME_COMPOSITION);
}

void CAutoDownloadView::OnUpdateDownloadIncomeComposition(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadFundHoldShenzhenAshare()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FUND_HOLD_SHENZHEN_ASHARE);

}

void CAutoDownloadView::OnUpdateDownloadFundHoldShenzhenAshare(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadFundHoldEnterprenuer()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FUND_HOLD_ENTERPRENUER);

}

void CAutoDownloadView::OnUpdateDownloadFundHoldEnterprenuer(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadFundHoldSmallAndMid()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FUND_HOLD_SMALL_AND_MID);

}

void CAutoDownloadView::OnUpdateDownloadFundHoldSmallAndMid(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadFundHoldShanghai()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_FUND_HOLD_SHANGHAI);

}

void CAutoDownloadView::OnUpdateDownloadFundHoldShanghai(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadHexunResearchPaper()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_HEXUN_RESEARCH_PAPER);
}

void CAutoDownloadView::OnUpdateDownloadHexunResearchPaper(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadHusheng300Index()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_HUSHENG300_INDEX);
}


void CAutoDownloadView::OnUpdateDownloadHusheng300Index(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadCffexFutureDaily()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CFFEX_FUTURE_DAILY);
}

void CAutoDownloadView::OnUpdateDownloadCffexFutureDaily(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadStatsgovHgyd()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STATSGOV_HGYD);
}

void CAutoDownloadView::OnUpdateDownloadStatsgovHgyd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadStatsgovHgjd()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STATSGOV_HGJD);
}

void CAutoDownloadView::OnUpdateDownloadStatsgovHgjd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadStatsgovHgnd()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STATSGOV_HGND);
}

void CAutoDownloadView::OnUpdateDownloadStatsgovHgnd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadStatsgovFsyd()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STATSGOV_FSYD);
}

void CAutoDownloadView::OnUpdateDownloadStatsgovFsyd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadStatsgovFsjd()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STATSGOV_FSJD);
}

void CAutoDownloadView::OnUpdateDownloadStatsgovFsjd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadStatsgovFsnd()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_STATSGOV_FSND);
}

void CAutoDownloadView::OnUpdateDownloadStatsgovFsnd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

void CAutoDownloadView::OnDownloadCninfoAnnouncement()
{
	// TODO: �ڴ���������������
	StartupDownloadThread(ID_DOWNLOAD_CNINFO_ANNOUNCEMENT);
}

void CAutoDownloadView::OnUpdateDownloadCninfoAnnouncement(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCmdUIDownload(pCmdUI);
}

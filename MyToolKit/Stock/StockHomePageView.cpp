// StockHomePageView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "StockHomePageView.h"


// CStockHomePageView

IMPLEMENT_DYNCREATE(CStockHomePageView, CBaseGridCtlView)

CStockHomePageView::CStockHomePageView()
{

}

CStockHomePageView::~CStockHomePageView()
{
}

BEGIN_MESSAGE_MAP(CStockHomePageView, CBaseGridCtlView)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CStockHomePageView ��ͼ

void CStockHomePageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CStockHomePageView ���

#ifdef _DEBUG
void CStockHomePageView::AssertValid() const
{
	CBaseGridCtlView::AssertValid();
}

#ifndef _WIN32_WCE
void CStockHomePageView::Dump(CDumpContext& dc) const
{
	CBaseGridCtlView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStockHomePageView ��Ϣ�������


void CStockHomePageView::OnInitialUpdate()
{
	CBaseGridCtlView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	RedrawGridCtrl();
}




void CStockHomePageView::RedrawGridCtrl()
{

	CIndividualShareDoc * pDoc = (CIndividualShareDoc *)GetDocument();

	if(m_pGridCtrl)
	{
		CStockApp * pApp = (CStockApp *)AfxGetApp();

		//////////////////////////////////////////////////////////////////////////
		//	

		map<string, string>  mapUrl;
		
		mapUrl["ͬ��˳"] = "http://www.10jqka.com.cn/";
		mapUrl["��Ѷ��"] = "http://www.hexun.com/";
		mapUrl["�в���"] = "http://data.cfi.cn/cfidata.aspx";
		mapUrl["�����Ƹ���"] = "http://data.eastmoney.com/cjsj/hbgyl.html";

		mapUrl["�й�ָ�����޹�˾"] = "http://www.csindex.com.cn/sseportal/csiportal/hy_syl/syl.jsp";
		mapUrl["�й�֤ȯͶ���߱�������"] = "http://www.sipf.com.cn/zjjk/tjsj/";
		mapUrl["�й�֤ȯ�Ǽǽ����������ι�˾"] = "http://www.chinaclear.cn/";

		mapUrl["�Ϻ�֤ȯ������"] = "http://www.sse.com.cn/";
		mapUrl["����֤ȯ������"] = "http://www.szse.cn/";
		mapUrl["�й������ڻ�������"] = "http://www.cffex.com.cn/";
		mapUrl["�й�����ͳ�ƾ�"] = "http://www.stats.gov.cn/tjsj/tjbz/201301/t20130114_8675.html";

		mapUrl["�����ծ�Ǽǽ����������ι�˾"] = "http://www.chinabond.com.cn/d2s/index.html";
		mapUrl["�޳���Ѷ"] = "http://www.cninfo.com.cn/cninfo-new/index";


		m_pGridCtrl->SetRowCount(mapUrl.size()+1 + 20);
		m_pGridCtrl->SetColumnCount(3);
		m_pGridCtrl->SetFixedRowCount(1);
		m_pGridCtrl->SetFixedColumnCount(1);
		m_pGridCtrl->SetHeaderSort(TRUE);

		SetGridCell(0, 0, true, "���");
		SetGridCell(0, 1, true, "��˾");
		SetGridCell(0, 2, true, "���ӣ�URL��");

		map<string, string>::iterator it = mapUrl.begin();
		for(int i=1; it!= mapUrl.end(); i++, it++)
		{
			char tmp[5] = {0};
			sprintf_s(tmp, 5, "%d", i);
			SetGridCell(i,0, true, tmp);

			SetGridCell(i,1, false, it->first.c_str());
			
			if (!m_pGridCtrl->SetCellType(i, 2, RUNTIME_CLASS(CGridURLCell)))
				return;
			SetGridCell(i, 2, false, it->second.c_str());
		}
				
		m_pGridCtrl->AutoSize();
		m_pGridCtrl->SetColumnWidth(1, 230);
		m_pGridCtrl->SetColumnWidth(2, 560);
	}

}

void CStockHomePageView::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	int kkk = 1;
	//CBaseGridCtlView::OnClose();
}

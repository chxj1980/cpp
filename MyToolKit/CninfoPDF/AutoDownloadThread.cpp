
#include "stdafx.h"
#include "CninfoAnnouncePDF.h"
#include "PDFHaveCatalog.h"
#include "PDFGetLand.h"
#include "PDFStockIncentivePlan.h"
#include "PDFShareHolding.h"

UINT AutoDownloadThreadFunc(LPVOID param)
{

	stringstream ss;

	/*{
		ss.str("");
		ss << "PDF ����  ���ؿ�ʼ.\r\n";
		sendToOutput(ss.str().c_str(), NULL );

		CPDFShareHolding  pdf;
		pdf.announcementId = "1202742046";
		pdf.adjunctUrl = "/finalpage/2015-04-23/1200889625.PDF";
		pdf.announcementTitle = "1202742046";
		pdf.secCode = "000069";
		pdf.m_hWnd = NULL;

		pdf.SaveAsCsv();

		int kkk = 1;
		return 0 ;
	}*/

	/*{
		CPDFShareHolding  pdf;
		pdf.UpdateQuarter();
		return 0;
	}*/


	while(true)
	{
		list<CCninfoAnnouncePDF *> lstPdf;
		//////////////////////////////////////////////////////////////////////////
		//	����������Ҫ������ PDF �ļ�Ŀ¼
		/*{
			CPDFHaveCatalog pdf1;
			list<CCninfoAnnouncePDF *> lst1 = pdf1.CreatePDF();
			list<CCninfoAnnouncePDF *>::iterator it = lst1.begin();
			for(; it!=lst1.end(); it++)
			{
				lstPdf.push_back(*it);
			}
		}*/
		
		{
			CPDFShareHolding pdf1;
			list<CCninfoAnnouncePDF *> lst1 = pdf1.CreatePDF();
			list<CCninfoAnnouncePDF *>::iterator it = lst1.begin();
			for(; it!=lst1.end(); it++)
			{
				lstPdf.push_back(*it);
			}
		}

		{
			CPDFGetLand pdf1;
			list<CCninfoAnnouncePDF *> lst1 = pdf1.CreatePDF();
			list<CCninfoAnnouncePDF *>::iterator it = lst1.begin();
			for(; it!=lst1.end(); it++)
			{
				lstPdf.push_back(*it);
			}
		}
		
		{
			CPDFStockIncentivePlan pdf1;
			list<CCninfoAnnouncePDF *> lst1 = pdf1.CreatePDF();
			list<CCninfoAnnouncePDF *>::iterator it = lst1.begin();
			for(; it!=lst1.end(); it++)
			{
				lstPdf.push_back(*it);
			}
		}
	
		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << " ============================== PDF �ļ����ؿ�ʼ.";
		ss << " �� " << lstPdf.size() << "���ļ� \r\n";
		sendToOutput(ss.str().c_str(), NULL );

		if(lstPdf.size()==0)
		{
			//	��� Stock.exe �����Ƿ���ڣ��Ա�����Ƿ�رձ�����
			if(CheckProcessOnlyOne("Stock.exe")==0)
			{
				// TerminateProcess(GetCurrentProcess(), 1 );
				sendToOutput(_T("�������"), NULL);
			}
			else
				Sleep(600 * 1000);
		}
		

		//////////////////////////////////////////////////////////////////////////
		//	��ʼ����� ���ط���

		int nPDF = 1;
		while(lstPdf.size()>0)
		{

			if(lstPdf.size()==1)
			{
				int kkk = 1;
			}
			CCninfoAnnouncePDF *  pdf = *lstPdf.begin();

			ss.str("");
			ss << "��" << nPDF << "��PDF" << "(" <<  pdf->announcementTitle << ")���ؿ�ʼ.\r\n";
			sendToOutput(ss.str().c_str(), NULL );
			
			pdf->m_hWnd = NULL;

			string csv = pdf->SaveAsCsv();
			pdf->ImportToDatabase(csv);

			delete pdf;

			lstPdf.pop_front();

			nPDF++;
		}

		Sleep(10 * 1000);
	}
	
	return 0;
}
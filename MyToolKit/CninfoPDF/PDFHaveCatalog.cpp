#include "StdAfx.h"
#include "PDFHaveCatalog.h"

#include "UrlUtils.h"
#include "TextExtractor.h"

CPDFHaveCatalog::CPDFHaveCatalog(void)
{
}

CPDFHaveCatalog::~CPDFHaveCatalog(void)
{
	mapCatalog.clear();
}

list<CCninfoAnnouncePDF *> CPDFHaveCatalog::CreatePDF()
{
	list<string>	announcementId;
	list<string>	adjunctUrl;
	list<string>	announcementTitle;

	list<string>	announcementTime;
	list<string>	secCode;
	list<string>	secName;

	stringstream ss;
	try
	{
		
		session sql(g_MysqlPool);

		//////////////////////////////////////////////////////////////////////////

		sql << SqlScript();

		ss.str("");
		ss << "select announcementId, secCode, secName, adjunctUrl, announcementTitle, " 
			"DATE_FORMAT(announcementTime, '%Y-%m-%d') as announcementTime from cninfoannouncement b "
			"where announcementTime > '2014-1-1' and adjunctType = 'PDF'  " 
			"and ( announcementTitle like '%��Ʊ����%'  or announcementTitle like '%���й�Ʊ%' "
			"or announcementTitle like '%����A�ɹ�Ʊ%' ) "
			"and ( announcementTitle like '%�ݰ���'  or announcementTitle like '%�ݰ�'  "
			"or announcementTitle like '%Ԥ����' or announcementTitle like '%Ԥ��'  "
			"or announcementTitle like '%��������' or announcementTitle like '%�޶���' " 
			"or announcementTitle like '%�޶���' or announcementTitle like '%�޶��壩' )  "
			"and not exists (select 1 from cninfoannouncepdf a where a.announcementId = b.announcementId ) "
			"order by announcementTime desc ";

		string tttt = ss.str();

		row r;
		statement st = (sql.prepare << /*Gbk2Utf8*/ ss.str(), into(r)) ;
		st.execute();

		while (st.fetch())
		{
			announcementId.push_back( r.get<string>("announcementId"));			
			adjunctUrl.push_back(  r.get<string>("adjunctUrl"));
			announcementTitle.push_back( r.get<string>("announcementTitle"));

			announcementTime.push_back( r.get<string>("announcementTime"));
			secCode.push_back( r.get<string>("secCode"));
			secName.push_back( r.get<string>("secName"));
		}

		//////////////////////////////////////////////////////////////////////////
		//	���ع�Ȩ�䶯

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), NULL);
	}

	list<CCninfoAnnouncePDF *>  lst;

	int nPDF = 1;
	while(adjunctUrl.size()>0)
	{
		ss.str("");
		ss << "��" << nPDF << "��PDF" << "(" <<  *announcementTitle.begin() << ")���ؿ�ʼ.\r\n";
		sendToOutput(ss.str().c_str(), NULL );

		CCninfoAnnouncePDF *  pdf = new CPDFHaveCatalog;
		pdf->announcementId = *announcementId.begin();
		pdf->adjunctUrl = *adjunctUrl.begin();
		pdf->announcementTitle = *announcementTitle.begin();

		pdf->announcementTime = *announcementTime.begin();
		pdf->secCode = *secCode.begin();
		pdf->secName = *secName.begin();
		pdf->m_hWnd = NULL;

		lst.push_back(pdf);

		announcementId.pop_front();
		adjunctUrl.pop_front();
		announcementTitle.pop_front();
		announcementTime.pop_front();
		secCode.pop_front();
		secName.pop_front();

		nPDF++;
	}

	return lst;
}


void CPDFHaveCatalog::ImportToDatabase(string csv)
{

	if(csv=="AlreadyInMemory")
	{
				
	}
	else if(csv.empty()==false)
	{
		CPdfCatalog  pdfCatalog;
		pdfCatalog.nPage = 0;
		pdfCatalog.strName =  "Error! " + csv;
		pdfCatalog.strContent = "Error! " + csv;
		mapCatalog[0] = pdfCatalog;
				
	}
	/*if(m_nCode<=0)
		return;*/

	if(mapCatalog.size()<=0)
		return;

	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	try
	{
		ss << "CPDFHaveCatalog::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		sql << SqlScript();

		ss.str("");
		ss << " insert into CninfoAnnouncePDF (  announcementId, secCode, secName, announcementTime,  "
			<< "announcementTitle, adjunctUrl, isDisplay, catalogNo, catalogName, catalogContent ) values ";

		map<int, CPdfCatalog>::iterator it = mapCatalog.begin();
		for( ; it!= mapCatalog.end(); )
		{
			ss	<< "( \'" << announcementId << "\' ," 
				<< "\'" << secCode << "\' ,"
				<< "\'" << secName << "\' ,"
				<< "\'" << announcementTime << "\' ,"
				<< "\'" << announcementTitle << "\' ,"
				<< "\'" << adjunctUrl << "\' ,"
				<< 0 << ","
				<< it->first << ", \'"
				<< it->second.strName << "\', \'"
				<< ReplaceString(it->second.strContent, "\'", "\"") << "\' )";

			it++;
			if(it != mapCatalog.end())
				ss << ",";
		}

		string test = ss.str();
		//test = Gbk2Utf8(test);
		sql << test;
		
		ss.str("");
		ss << "�������� " << mapCatalog.size() ;
		ss << " OK, CPDFHaveCatalog::ImportToDatabase ���ݵ������. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(), m_hWnd);
	}
}




string CPDFHaveCatalog::SqlScript()
{
	stringstream ss;
	ss << "create table if not exists CninfoAnnouncePDF ( " 
		<< "announcementId varchar(32), secCode varchar(16), secName varchar(32), announcementTime date, "
		<< "announcementTitle varchar(128), adjunctUrl varchar(128), catalogNo int, catalogName varchar(128),  "
		<< "isDisplay int, catalogContent varchar(4000),  PRIMARY KEY ( announcementId, catalogNo ))";
	return ss.str();
}


int  AdjustCatalog(TextExtractor &extractor, int nCatalogPage, int nLastCatalog, map<int, CPdfCatalog> & mapCatalogTmp)
{
	int nTry = 15;
	do
	{
		nTry--;
		if(extractor.m_mapPageContent.count(mapCatalogTmp[nLastCatalog].nPage)<=0)
		{
			map<int, CPdfCatalog>::iterator it = mapCatalogTmp.begin();
			for(; it!=mapCatalogTmp.end(); it++)
			{
				it->second.nPage -= 1;
			}
			continue;
		}

		string  strPage0 = extractor.m_mapPageContent[mapCatalogTmp[nLastCatalog].nPage];
		strPage0 = ReplaceString(strPage0, "                                                                     ", "");
		strPage0 = ReplaceString(strPage0, "��������������������������������������������������������", "");  // ȫ�ǿո�
		strPage0 = ReplaceString(strPage0, "��", "");  // ȫ�ǿո�
		strPage0 = ReplaceString(strPage0, " ", "");
		string  strKey = ReplaceString(mapCatalogTmp[nLastCatalog].strName, " ", "");

		// ��һ��Ŀ¼ָ����������� �ض����� Ŀ¼ҳ����
		if(strPage0.find(strKey)!=string::npos && mapCatalogTmp[nLastCatalog].nPage != nCatalogPage)
			break;

		map<int, CPdfCatalog>::iterator it = mapCatalogTmp.begin();
		for(; it!=mapCatalogTmp.end(); it++)
		{
			it->second.nPage -= 1;
		}

	}while(nTry>=0);

	return nTry;
}


string  CPDFHaveCatalog::SaveAsCsv()
{
	stringstream ss;

	int zipLen = 0;
	unsigned char * pZip = NULL;
	/* ���� PDF �ļ� */
	
	/*2016-06-01/1202348087.PDF*/

	string test = string("http://www.cninfo.com.cn/") + adjunctUrl;
	zipLen =CUrlUtils::PostUrlOfCsindex(test, pZip);

	if(zipLen>0)
	{
		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF �ļ����� �ɹ�. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

	}
	else
	{
		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF �ļ����� ʧ��. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		return ss.str();
	}
	
	//////////////////////////////////////////////////////////////////////////

	TextExtractor extractor;

	try {
		extractor.Init( (char *)pZip , zipLen );

	} 
	catch( PdfError & e ) {

		int tt = e.GetError();

		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF TextExtractor Err. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		if(pZip)
			free(pZip);

		return ss.str();
	}

	if(pZip)
		free(pZip);

	//	��ȡǰ 20 ҳ�棬�Ա���Ѱ��Ŀ¼��
	vector<string>		vecMatch;
	vector<int>			firstOffset;
	int  nCatalogPage = -1;
	for(int i=0; i<20; i++)
	{
		if(extractor.m_mapPageContent.count(i)>0 && 
			Pcre2Grep(_T("Ŀ[\\s\\t]*¼"), extractor.m_mapPageContent[i].c_str() ,vecMatch, firstOffset )>0)
		{
			nCatalogPage = i;
			break;
		}
	}
	if(nCatalogPage < 0)
	{
		//	û�� Ŀ¼�� pdf �ļ��ݲ�������
		ss.str("");
		ss << "��"  << announcementTitle << "��";
		ss << " PDF û�� Ŀ¼. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		return ss.str();
	}

	string strQqjl = "";
	for(int i=nCatalogPage; i<20; i++)
	{
		if(extractor.m_mapPageContent.count(i)>0 )
		{
			strQqjl += extractor.m_mapPageContent[i];
		}
		else 
			break;
	}

	if(Pcre2Grep(_T("Ŀ[\\s\\t]*¼"), strQqjl.c_str() ,vecMatch, firstOffset )>0)
	{
		string::size_type pos1 = strQqjl.find(vecMatch[0]);
		if(pos1!=string::npos)
			strQqjl = strQqjl.substr(pos1 + vecMatch[0].length());
	}

	
	if(Pcre2Grep(_T("[^\\-\\d\\t\\.]+[\\.]{3,}[\\-\\s\\t]*[\\d]+"), strQqjl.c_str() ,vecMatch, firstOffset )>0)
	{
		int k = vecMatch.size()-1;
		string::size_type startPos = strQqjl.find(vecMatch[k]);
		startPos += vecMatch[k].length();

		strQqjl = strQqjl.substr(startPos);

		//	Ŀ¼�ַ����ˣ� ����ȷ������ Ŀ¼ҳ��ʱʹ�õ� Ŀ¼��, ��һ��ʹ�����һ�
		int nLastCatalog = 0 ;
		for(int k = 0; k< vecMatch.size(); k++)
		{
			vector<string> firstMatch;
			if(Pcre2Split(_T("[\\.]+[\\-\\s\\t]*"), vecMatch[k].c_str(), firstMatch )>0)
			{
				if(firstMatch.size()!=2)
				{
					mapCatalog.clear();
					ss.str("");
					ss << "��"  << announcementTitle << "��";
					ss << " PDF Ŀ¼��������. \r\n";
					sendToOutput(ss.str().c_str(), m_hWnd);

					return ss.str();
				}
				else
				{
					//	�ƺ� 6 ҳ��ʼ���� Ŀ¼ҳ��
					mapCatalog[k].nPage = atoi(firstMatch[1].c_str()) + 10;
					mapCatalog[k].strName = firstMatch[0];
					nLastCatalog = k;
				}
				
			}

		}

		//	����Ŀ¼ҳ�ţ��е��ĵ�����ҳ���Ϊ 1�� �еı��Ϊ 0, �еı��Ϊ - 1 �� 
		if(mapCatalog.size()>=3)
		{
			map<int, CPdfCatalog> mapCatalogTmp1 = mapCatalog;
			map<int, CPdfCatalog> mapCatalogTmp2 = mapCatalog;
			map<int, CPdfCatalog> mapCatalogTmp3 = mapCatalog;
			int nTry1 = AdjustCatalog(extractor, nCatalogPage, nLastCatalog, mapCatalogTmp1);
			int nTry2 = AdjustCatalog(extractor, nCatalogPage, nLastCatalog -1, mapCatalogTmp2);
			int nTry3 = AdjustCatalog(extractor, nCatalogPage, nLastCatalog -2, mapCatalogTmp3);
	
			if(nTry1>=0 && nTry2>=0 && mapCatalogTmp1[nLastCatalog].nPage == mapCatalogTmp2[nLastCatalog].nPage)
				mapCatalog = mapCatalogTmp1;
			else if(nTry1>=0 && nTry3>=0 && mapCatalogTmp1[nLastCatalog].nPage == mapCatalogTmp3[nLastCatalog].nPage)
				mapCatalog = mapCatalogTmp1;
			else if(nTry2>=0 && nTry3>=0 && mapCatalogTmp2[nLastCatalog].nPage == mapCatalogTmp3[nLastCatalog].nPage)
				mapCatalog = mapCatalogTmp2;
			else
			{
				//	δ����ȷ���� ҳ���
				mapCatalog.clear();

				ss.str("");
				ss << "��"  << adjunctUrl << "��";
				ss << " PDF δ����ȷ���� ҳ��� Err. \r\n";
				sendToOutput(ss.str().c_str(), m_hWnd);

				return ss.str();
			}
			
			//	������Ŀ¼�������֤��ɾ�����в��ϸ�Ŀ¼��
			{
				
				vector<int>	vecDel;
				int nTotal = mapCatalog.size();
				for(int k=0; k<nTotal; k++)
				{
					string  strPage0 = extractor.m_mapPageContent[mapCatalog[k].nPage];
					//	���� ReplaceString ���õݹ��㷨��������Ȳ�����������ɾ�� �����Ŀո񣨺�ȫ�ǣ�
					strPage0 = ReplaceString(strPage0, "                                                                     ", "");
					strPage0 = ReplaceString(strPage0, "��������������������������������������������������������", "");  // ȫ�ǿո�
					strPage0 = ReplaceString(strPage0, "��", "");  // ȫ�ǿո�
					strPage0 = ReplaceString(strPage0, " ", "");
					string  strKey = ReplaceString(mapCatalog[k].strName, " ", "");

					if(strPage0.find(strKey)==string::npos)
					{
						vecDel.insert(vecDel.end(), k);
						mapCatalog.erase(k);
					}
				}

				if(vecDel.size()> 3 &&  (vecDel.size() * 10.0/nTotal)> 1.0)
				{
					mapCatalog.clear();

					ss.str("");
					ss << "��"  << adjunctUrl << "��";
					ss << " PDF ������ҳ��ţ�����ͨ����֤ Err. ɾ���� " << vecDel.size();
					ss << ",��Ŀ¼�� " << nTotal << "\r\n";
					sendToOutput(ss.str().c_str(), m_hWnd);

					return ss.str();
				}
				else if(vecDel.size()>0)
				{
					ss.str("");
					ss << "��"  << adjunctUrl << "�� PDF ������ҳ���, ɾ����ҳ�� ";
					for( int k = 0; k< vecDel.size(); k++)
					{
						ss <<  vecDel[k] << "," ;
					}
					
					ss << " ��Ŀ¼�� " << nTotal << "\r\n";
					sendToOutput(ss.str().c_str(), m_hWnd);
				}
			}
		}
		else
		{
			//	Ŀ¼�����̫��
			mapCatalog.clear();

			ss.str("");
			ss << "��"  << adjunctUrl << "��";
			ss << " PDF Ŀ¼�����̫�� Err. \r\n";
			sendToOutput(ss.str().c_str(), m_hWnd);

			return ss.str();
		}

		//////////////////////////////////////////////////////////////////////////
		//	��ȡÿ��Ŀ¼������
		map<int, CPdfCatalog>::iterator  it = mapCatalog.begin();
		for(; it!= mapCatalog.end(); it++)
		{
			//	ȷ����Ŀ¼���� ��ʼҳ �� ���ҳ
			int nPage = it->second.nPage;
			string strName = it->second.strName;

			int nNextPage = extractor.m_mapPageContent.size() -1;
			string strNextName = "";
			it++;
			if( it != mapCatalog.end())
			{
				nNextPage = it->second.nPage;
				strNextName = it->second.strName;
			}
			it--;

			if(nPage== nNextPage)
			{
				string startContent =  extractor.m_mapPageContent[nPage];
				string::size_type pos1 = startContent.find(strName);

				if(pos1!= string::npos)
					startContent = startContent.substr(pos1);

				if(strNextName.empty()!=true)
				{
					pos1 = startContent.find(strNextName);
					if(pos1!= string::npos)
						startContent = startContent.substr(0, pos1);
				}

				it->second.strContent = startContent;
			}
			else if(nPage < nNextPage)
			{
				//	��һҳ
				string startContent =  extractor.m_mapPageContent[nPage];
				string::size_type pos1 = startContent.find(strName);

				if(pos1!= string::npos)
					startContent = startContent.substr(pos1);

				it->second.strContent = startContent;

				//	�м�ҳ
				int nCurrPage = nPage + 1;
				while(nCurrPage < nNextPage)
				{
					it->second.strContent += extractor.m_mapPageContent[nCurrPage];
					nCurrPage++;
				}

				//	���ҳ
				startContent = extractor.m_mapPageContent[nNextPage];
				if(strNextName.empty()!=true)
				{
					pos1 = startContent.find(strNextName);
					if(pos1!= string::npos)
						startContent = startContent.substr(0, pos1);
				}

				it->second.strContent += startContent;
			}
		}
	}
	
	if( mapCatalog.size() > 0)
	{
		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF �������� " << mapCatalog.size()  << ". \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);
		return "AlreadyInMemory";
	}

	return "NoMoreData";
}




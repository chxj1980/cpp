#include "StdAfx.h"
#include "PDFShareHolding.h"

#include "UrlUtils.h"
#include "TextExtractorEx.h"

CPDFShareHolding::CPDFShareHolding(void)
{
	
}

CPDFShareHolding::~CPDFShareHolding(void)
{
}

string CPDFShareHolding::ParseYearQuarter(string title)
{
	string strResult;
	vector<string> firstMatch;
	vector<int>		firstOffset;
	if(Pcre2Grep(_T("[\\d]{4}��"),title, firstMatch, firstOffset) > 0)
	{
		string strMatch = firstMatch[0];
		if(Pcre2Grep(_T("[\\d]{4}��"), strMatch, firstMatch, firstOffset) > 0)
		{
			strResult = firstMatch[0];
		}
	}

	if(strResult.empty()==false)
	{
		if(title.find("������")!=string::npos)
		{
			strResult += "3����";
		}
		else if(title.find("��һ��")!=string::npos)
		{
			strResult += "1����";
		}
		else if(title.find("�����")!=string::npos)
		{
			strResult += "2����";
		}
		else if(title.find("���")!=string::npos)
		{
			strResult += "4����";
		}
	}
	return strResult;

}


void CPDFShareHolding::UpdateQuarter()
{
	vector<string>	announcementId;
	vector<string>	announcementTitle;


	stringstream ss;
	try
	{

		session sql(g_MysqlPool);

		//////////////////////////////////////////////////////////////////////////
		sql << "call add_col('Cninfo_Share_Holding', 'year_quarter', 'varchar(32)', '')";
		

		ss.str("");
		ss << "select announcementId, secCode, secName, adjunctUrl, announcementTitle, " 
			"DATE_FORMAT(announcementTime, '%Y-%m-%d') as announcementTime from cninfoannouncement b "
			"where announcementTime > '2015-1-1' and adjunctType = 'PDF'  " 
			"and ( announcementTypeName like '%�ȱ���' ) "
			"and ( announcementTitle  like '%ժҪ%' "
			"or announcementTitle  like '%����%' ) "
			"and announcementTitle not like '%��ȡ��%'"
			"and announcementId  in "
			"( select DISTINCT announcementId from Cninfo_Share_Holding  ) "
			"order by announcementTime desc ";

		string tttt = ss.str();

		row r;
		statement st = (sql.prepare << /*Gbk2Utf8*/ ss.str(), into(r)) ;
		st.execute();

		while (st.fetch())
		{
			announcementId.insert( announcementId.end(), r.get<string>("announcementId"));			
			announcementTitle.insert(announcementTitle.end(), r.get<string>("announcementTitle"));
		}

		//////////////////////////////////////////////////////////////////////////
		//	���ع�Ȩ�䶯

		for(int i = 0; i< announcementId.size(); i++)
		{
			string strResult = ParseYearQuarter(announcementTitle[i]);
			ss.str("");
			ss << "update Cninfo_Share_Holding set year_quarter = \'";
			ss << strResult << "\' where announcementId = \'" ;
			ss << announcementId[i] << "\' ";

			sql << ss.str();
		}

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), NULL);
	}
}





list<CCninfoAnnouncePDF *> CPDFShareHolding::CreatePDF()
{
	list<string>	announcementId;
	list<string>	adjunctUrl;
	list<string>	announcementTitle;

	list<string>	announcementTime;
	list<string>	secCode;
	list<string>	secName;


	list<string>	announcementId_1;
	list<string>	adjunctUrl_1;
	list<string>	announcementTitle_1;

	list<string>	announcementTime_1;
	list<string>	secCode_1;
	list<string>	secName_1;

	vector<string>	vecYearQuarter;
	vector<string>	vecSecCode;

	stringstream ss;
	try
	{

		session sql(g_MysqlPool);

		//////////////////////////////////////////////////////////////////////////
		//	������ժҪ

		sql << SqlScript();

		ss.str("");
		ss << "select announcementId, secCode, secName, adjunctUrl, announcementTitle, " 
			"DATE_FORMAT(announcementTime, '%Y-%m-%d') as announcementTime from cninfoannouncement b "
			"where announcementTime > '2015-1-1' and adjunctType = 'PDF'  " 
			"and ( announcementTypeName like '%�ȱ���' ) "
			"and ( announcementTitle  like '%ժҪ%' "
			"or announcementTitle  like '%����%' ) "
			"and announcementTitle not like '%��ȡ��%'"
			"and announcementId not in "
			"( select DISTINCT announcementId from Cninfo_Share_Holding  ) "
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
		//	�����µ� ��������

		ss.str("");
		ss << "select announcementId, secCode, secName, adjunctUrl, announcementTitle, " 
			"DATE_FORMAT(announcementTime, '%Y-%m-%d') as announcementTime from cninfoannouncement b "
			"where announcementTime > '2015-1-1' and adjunctType = 'PDF'  " 
			"and ( announcementTypeName like '%�ȱ���' ) "
			"and ( announcementTitle  like '%�ȱ���' "
			"or announcementTitle  like '%ȫ��%' ) "
			"and announcementTitle not like '%��ȡ��%'"
			"and announcementId not in "
			"( select DISTINCT announcementId from Cninfo_Share_Holding  ) "
			"order by announcementTime desc ";

		tttt = ss.str();
		
		st = (sql.prepare << /*Gbk2Utf8*/ ss.str(), into(r)) ;
		st.execute();

		while (st.fetch())
		{
			announcementId_1.push_back( r.get<string>("announcementId"));			
			adjunctUrl_1.push_back(  r.get<string>("adjunctUrl"));
			announcementTitle_1.push_back( r.get<string>("announcementTitle"));

			announcementTime_1.push_back( r.get<string>("announcementTime"));
			secCode_1.push_back( r.get<string>("secCode"));
			secName_1.push_back( r.get<string>("secName"));
		}

		//	
		ss.str("");
		ss << "select announcementId, secCode, secName, adjunctUrl, announcementTitle, " 
			"DATE_FORMAT(announcementTime, '%Y-%m-%d') as announcementTime from cninfoannouncement b "
			"where announcementTime > '2015-1-1' and adjunctType = 'PDF'  " 
			"and ( announcementTypeName like '%�ȱ���' ) "
			"and ( announcementTitle  like '%ժҪ%' "
			"or announcementTitle  like '%����%' ) "
			"and announcementTitle not like '%��ȡ��%'"
			"order by announcementTime desc ";

		tttt = ss.str();

		st = (sql.prepare << /*Gbk2Utf8*/ ss.str(), into(r)) ;
		st.execute();

		while (st.fetch())
		{
			vecSecCode.insert(vecSecCode.end(), r.get<string>("secCode"));

			string title =  r.get<string>("announcementTitle");
			title = ParseYearQuarter(title);
			vecYearQuarter.insert(vecYearQuarter.end(), title);
			
		}


		while(adjunctUrl_1.size()>0)
		{
			bool isExist = false;
			string title = ParseYearQuarter( *announcementTitle_1.begin());
			string strSecCode = *secCode_1.begin(); 
			for(int k =0; k< vecYearQuarter.size(); k++)
			{
				if(vecYearQuarter[k] == title && vecSecCode[k]== strSecCode )
				{
					isExist = true;
					break;
				}
			}

			if(isExist == false)
			{
				announcementId.push_back(*announcementId_1.begin());			
				adjunctUrl.push_back( *adjunctUrl_1.begin());
				announcementTitle.push_back( *announcementTitle_1.begin());

				announcementTime.push_back(*announcementTime_1.begin());
				secCode.push_back( *secCode_1.begin());
				secName.push_back( *secName_1.begin());

			}
			
			announcementId_1.pop_front();
			adjunctUrl_1.pop_front();
			announcementTitle_1.pop_front();
			announcementTime_1.pop_front();
			secCode_1.pop_front();
			secName_1.pop_front();

			
		}


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

		CCninfoAnnouncePDF *  pdf = new CPDFShareHolding;
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



string CPDFShareHolding::SaveAsCsv()
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

	TextExtractorEx extractor;

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


	//SaveAnalysisToDatabase(extractor.m_pdf);

	//////////////////////////////////////////////////////////////////////////
	
	// �ҳ�Ŀ�� ��� ������Ŀ��������ұ߽�
	bool bLoop = true;
	vector<CLineOrCell> vecTarget;
	double left_limit = 1000;		
	double right_limit = 0;
	int i=0;
	for(; i< extractor.m_mapTable.size() && bLoop; i++)
	{
		vector<CLineOrCell> & vecTmp = extractor.m_mapTable[i];
		for(int k = 0; k< vecTmp.size(); k++)
		{
			string texxx = vecTmp[k].content;
			texxx = ReplaceString(texxx, "                    ", "");
			texxx = ReplaceString(texxx, "          ", "");
			texxx = ReplaceString(texxx, " ", "");

			if(bLoop && Pcre2Find(texxx, "ǰ(.*)(��|��)(��ͨ��)?�ɶ��ֹ����"))
			{
				bLoop = false;
			}
			else if(bLoop && Pcre2Find(texxx, "�ֹ�5%���ϵĹɶ��ֹ����"))
			{
				bLoop = false;
			}
			else if(bLoop == false)
			{
				vecTarget.insert(vecTarget.end(), vecTmp[k]);
				if(texxx.empty() == false)
				{
					if(vecTmp[k].rect.GetLeft() < left_limit )
						left_limit = vecTmp[k].rect.GetLeft();

					if(vecTmp[k].rect.GetLeft() + vecTmp[k].rect.GetWidth() > right_limit )
						right_limit = vecTmp[k].rect.GetLeft() + vecTmp[k].rect.GetWidth();
				}
			
			}
		}
	}

	if(bLoop==false && vecTarget.size() ==0 && i < extractor.m_mapTable.size())
	{
		//	�ֲ� ����ͷ �� ������ ��������
		vector<CLineOrCell> & vecTmp = extractor.m_mapTable[i];
		for(int k = 0; k< vecTmp.size(); k++)
		{
			vecTarget.insert(vecTarget.end(), vecTmp[k]);

			string texxx = vecTmp[k].content;
			texxx = ReplaceString(texxx, "                          ", "");
			texxx = ReplaceString(texxx, "          ", "");
			texxx = ReplaceString(texxx, " ", "");
			if(texxx.empty() == false)
			{
				
				if(vecTmp[k].rect.GetLeft() < left_limit )
					left_limit = vecTmp[k].rect.GetLeft();

				if(vecTmp[k].rect.GetLeft() + vecTmp[k].rect.GetWidth() > right_limit )
					right_limit = vecTmp[k].rect.GetLeft() + vecTmp[k].rect.GetWidth();
			}
		}
	}

	// Ŀ������ܿ�ҳ���������д���
	double nCurrentBottom = 1000;
	double nCurrentLeft = 0;
	vector<CLineOrCell>  curRow;
	vector<CLineOrCell>	 lastRow;
	bool	bNewPage = false;
	vector<CLineOrCell> vecNewTarget;		//	���洦���� ���

	for(int i=0; i< vecTarget.size(); i++)
	{
		if(vecTarget[i].rect.GetLeft() - nCurrentLeft < 2 || vecTarget[i].rect.GetBottom() - nCurrentBottom < -5 )
		{
			//	������
			bool bReplace = true;	

			if(bNewPage)
			{
				bNewPage = false;
				
				//	�������ҳ�ĵ�һ�У���������������һ�е��٣����Թ鲢����һ��
				double totalWidth = 0;
				for(int k =0; k< curRow.size(); k++ )
				{
					totalWidth += curRow[k].rect.GetWidth();
				}
				if( abs( totalWidth - (right_limit - left_limit) ) > 15)
				{
					bReplace = false;
				}
			

				if(bReplace == false)
				{
					// ���Թ鲢����һ��
					for(int k= 0; k< curRow.size(); k++)
					{
						for(int m=0; m< lastRow.size(); m++)
						{
							if(abs(lastRow[m].rect.GetLeft() - curRow[k].rect.GetLeft()) <2 &&
								abs(lastRow[m].rect.GetWidth() - curRow[k].rect.GetWidth()) <2)
							{
								lastRow[m].content += curRow[k].content;
								curRow[k].content = "123-123-123";
							}
						}
					}
					for(int k= 0; k< curRow.size(); k++)
					{
						if(curRow[k].content.find("123-123-123") == string::npos)
						{
							//	��Ӧδ�ҵ��鲢��ģ�ֱ����ӵ���һ��, ��Ӧ����ͷ�� ���ɷ�״̬�� �� �������������ѵ���ҳ�����
							bool bInserted = false;
							vector<CLineOrCell>::iterator it = lastRow.begin();
							for(; it!=lastRow.end(); it++)
							{
								if(curRow[k].rect.GetLeft() - it->rect.GetLeft() < -2)
								{
									lastRow.insert(it, curRow[k]);
									bInserted = true;
									break;
								}
							}
							if(bInserted == false)
								lastRow.insert(lastRow.end(), curRow[k]);
						}
					}
				}
				
			}
			else
			{
				//	��ͨ�����, ����ҳ�� ��һ��
				if(lastRow.size()>0)
				{
					double totalWidth = 0;
					for(int k =0; k< curRow.size(); k++ )
					{
						totalWidth += curRow[k].rect.GetWidth();
					}
					if( abs( totalWidth - (right_limit - left_limit) ) > 15)
					{
						//	���п���ʱ ��Ԫ���б����Ѵ���ģ��硰�ɷ�״̬�� ���ܷ��ѳɡ����ᡱ�͡���Ѻ������������Ԫ��
						//  �����ر�̣�ֱ�� ����
						bReplace = false;
					}
				}
			}
			
			if(bReplace)
			{
				for(int m=0; m< lastRow.size(); m++)
				{
					vecNewTarget.insert(vecNewTarget.end(), lastRow[m]);
				}
				lastRow = curRow;
			}
			curRow.clear();

			if(vecTarget[i].rect.GetBottom() - nCurrentBottom > 30)
			{
				//	��ҳ��
				bNewPage = true;
			}
		}

		curRow.insert(curRow.end(), vecTarget[i]);
		
		nCurrentBottom = vecTarget[i].rect.GetBottom();
		nCurrentLeft = vecTarget[i].rect.GetLeft();
	}

	for(int m=0; m< lastRow.size(); m++)
	{
		vecNewTarget.insert(vecNewTarget.end(), lastRow[m]);
	}
	for(int m=0; m< curRow.size(); m++)
	{
		vecNewTarget.insert(vecNewTarget.end(), curRow[m]);
	}
	
	// �Ա���ҳ�����Ľ�� ����������ȡ
	bool bRecord = false;
	vector<string>	vecRecord;
	map<string, int>	mapHeader;
	int	nColumn = 0;	//	���ݱ�ͷ��ͳ������Ŀ
	for(int k = 0; k< vecNewTarget.size(); k++)
	{
		string texxx = vecNewTarget[k].content;
		texxx = ReplaceString(texxx, "                           ", "");
		texxx = ReplaceString(texxx, "          ", "");
		texxx = ReplaceString(texxx, " ", "");

		if(bRecord == false)
		{
			if(Pcre2Find(texxx, "��Ѻ(��)?����(��)?���"))
				mapHeader["��Ѻ�򶳽����"] = -1;

			else if(texxx.find("���")!=string::npos)
			{
				mapHeader["���"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("�ɶ�����")!=string::npos)
			{
				mapHeader["�ɶ�����"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("����")!=string::npos)
			{
				mapHeader["�ֹɱ���"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("�ɶ�����")!=string::npos)
			{
				mapHeader["�ɶ�����"] = nColumn;
				nColumn++;
			}
			else if(Pcre2Find(texxx, "��(��)?(��ͨ)?��(��)?(����|����)"))
			{
				mapHeader["������ĩ�ֹ�����"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("����")!=string::npos)
			{
				mapHeader["�������������䶯���"] = nColumn;
				nColumn++;
			}
			else if(Pcre2Find(texxx, "��������������(��)?(�ɷ�|��ͨ��)����") || 
				Pcre2Find(texxx, "���з���ͨ������"))
			{
				mapHeader["���������������Ĺɷ�����"] = nColumn;
				nColumn++;
			}
			else if(Pcre2Find(texxx,"��������������(��)?�ɷ�����"))
			{
				mapHeader["���������������Ĺɷ�����"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("�ɷ����")!=string::npos)
			{
				mapHeader["�ɷ����"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("��Ѻ�򶳽�Ĺɷ�����")!=string::npos)
			{
				mapHeader["��Ѻ�򶳽�Ĺɷ�����"] = nColumn;
				nColumn++;
				
				/*mapHeader["����"] = nColumn;
				nColumn++;*/
			}
			else if(texxx.find("�ɷ�״̬")!=string::npos)
			{
				mapHeader["�ɷ�״̬"] = nColumn;
				nColumn++;
			}
			else if(texxx.find("����")!=string::npos)
			{
				mapHeader["����"] = nColumn;
				nColumn++;
			}
			else
			{
				// ��ͷ�����������ݿ�ʼ��
				bRecord  = true;
				if(k+nColumn < vecNewTarget.size())
				{
					CLineOrCell line = vecNewTarget[k + nColumn];
					if(line.rect.GetLeft() - vecNewTarget[k].rect.GetLeft() > 5)
					{
						// ���� ��ͷ ����Ѻ�򶳽�Ĺɷ������� �������У���������
						nColumn ++;
					}				
				}
				
			}
		}

		if(bRecord && vecRecord.size() < nColumn * 10)
			vecRecord.insert(vecRecord.end(), texxx);

		if(nColumn >0 && vecRecord.size() >= nColumn * 10)
			break;
	}

	if(vecRecord.size()>0)
	{
		m_nShareHolder = vecRecord.size()/ nColumn;
		// ������Щ��Ʊ������ 10 �ˣ���軨�ɷ�
		for(int i=0; i<m_nShareHolder * nColumn; i++)
		{
			map<string ,int>::iterator it = mapHeader.begin();
			for(; it!=mapHeader.end(); it++)
			{
				if(it->second == (i%nColumn))
				{
					if(it->first=="�ɶ�����")
						m_ShareHolder[i/nColumn] = ReplaceString(vecRecord[i], "'", " ");

					else if(it->first=="������ĩ�ֹ�����")
						m_NumberOfHolding[i/nColumn] = String2Double(vecRecord[i].c_str());

					else if(it->first=="�ֹɱ���")
						m_SharePercent[i/nColumn] = String2Double(vecRecord[i]);

					else if(it->first=="���������������Ĺɷ�����")
						m_NumberOfRestrict[i/nColumn] = String2Double(vecRecord[i].c_str());

					else if(it->first=="�ɶ�����")
						m_Character[i/nColumn] = vecRecord[i];
				}
			}
		}
	}
	

	return "AlreadyInMemory";
}

string CPDFShareHolding::SqlScript()
{
	stringstream ss;
	ss.str("");
	ss << "create table if not exists Cninfo_Share_Holding ( " 
		<< "announcementId varchar(32),  secCode varchar(32), secName varchar(32), announcementTime date,  "
		<< "announcementTitle varchar(128), adjunctUrl varchar(128),  holder_num int ,share_holder varchar(64), "
		<< "number_of_holding int, share_percent decimal(5,2), number_of_restrict int,"
		<< "holder_character  varchar(32), year_quarter varchar(32), "
		<< " PRIMARY KEY ( announcementId, holder_num ))";

	return ss.str();
}

void CPDFShareHolding::ImportToDatabase(string csv)
{
	if(csv=="AlreadyInMemory")
	{

	}
	else
	{

		return;
	}

	stringstream ss;
	string test;

	try
	{
		ss << "CPDFShareHolding::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		sql << SqlScript();

		if(m_nShareHolder>3)
		{
			ss.str("");
			ss << " insert into Cninfo_Share_Holding (  announcementId, secCode, secName, announcementTime, announcementTitle,"
				<< " adjunctUrl, holder_num, share_holder, number_of_holding, share_percent, number_of_restrict, year_quarter, holder_character) values ";

			for( int i =0; i< m_nShareHolder; i++ )
			{
				ss	<< "( \'" << announcementId << "\' ," 
					<< "\'" << secCode << "\' ,"
					<< "\'" << secName << "\' ,"
					<< "\'" << announcementTime << "\' ,"
					<< "\'" << announcementTitle << "\' ,"
					<< "\'http://www.cninfo.com.cn/" << adjunctUrl << "\' ," << (i+1) << ", "
					<< "\'" << m_ShareHolder[i] << "\' ,"
					<< "\'" << m_NumberOfHolding[i] << "\',"
					<< "\'" << m_SharePercent[i] << "\',"
					<< "\'" << m_NumberOfRestrict[i] << "\',"
					<< "\'" << ParseYearQuarter(announcementTitle) << "\',"
					<< "\'" << m_Character[i] << "\'  )";

				if(i< m_nShareHolder-1)
					ss << ",";
			}

			test = ss.str();
			sql << test;
		}
		else
		{
			//	�������ɹ�
			ss.str("");
			ss << " insert into Cninfo_Share_Holding (  announcementId, secCode, secName, announcementTime, announcementTitle,"
				<< " adjunctUrl, holder_num, share_holder ) values ";

			ss	<< "( \'" << announcementId << "\' ," 
				<< "\'" << secCode << "\' ,"
				<< "\'" << secName << "\' ,"
				<< "\'" << announcementTime << "\' ,"
				<< "\'" << announcementTitle << "\' ,"
				<< "\'http://www.cninfo.com.cn/" << adjunctUrl << "\' ,"
				<< "0 , '�������ɹ�(��)' )";

			test = ss.str();
			sql << ss.str();
		}

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << "\r\n";
		string tttt = ss.str();
		sendToOutput(ss.str().c_str(), m_hWnd);
	}
}

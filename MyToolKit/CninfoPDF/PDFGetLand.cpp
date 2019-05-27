#include "StdAfx.h"
#include "PDFGetLand.h"

#include "UrlUtils.h"
#include "TextExtractorEx.h"

CPDFGetLand::CPDFGetLand(void)
{
	m_nDealMoney = 0;
	m_nLandName = 0;
	m_nLandLocation = 0;
	m_nLandPurpose = 0;
	m_nLandArea = 0;
	m_nRateOfCapacity = 0;
	m_nAreaOfStructure = 0;
}

CPDFGetLand::~CPDFGetLand(void)
{
}

list<CCninfoAnnouncePDF *> CPDFGetLand::CreatePDF()
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
			"and ( announcementTitle like '%����%����%' or announcementTitle like '%����%����%' "
			"or  announcementTitle like '%�������ز���Ŀ%' "
			"or  announcementTitle like '%��������ʹ��Ȩ%' "
			"or  announcementTitle like '%�б�����%' "
			"or  announcementTitle like '%������Ŀ�Ĺ���%' "
			"or  announcementTitle like '%��ȡ���ز���Ŀ%' "
			"or  announcementTitle like '%ȡ��%�õ�ʹ��Ȩ%' "
			"or  announcementTitle like '%��ȡ%����ʹ��Ȩ%' "
			"or  announcementTitle like '%����%�õ�ʹ��Ȩ%' "
			"or  announcementTitle like '%�������ش���%' "
			"or  announcementTitle like '%��÷��ز���Ŀ%' or  announcementTitle like '%�������ʹ��Ȩ%' ) "
			"and announcementId not in "
			"( select DISTINCT announcementId from cninfo_get_land  ) "
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

		CCninfoAnnouncePDF *  pdf = new CPDFGetLand;
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



bool CPDFGetLand::ProcessSentence(string sentence, bool needCheck)
{
	int nCount = 0;
	if(sentence.find(_T("���"))!=string::npos)	
		nCount++;
	if(sentence.find(_T("����"))!=string::npos)	
		nCount++;
	if(sentence.find(_T("�ݻ���"))!=string::npos)	
		nCount++;
	if(sentence.find(_T("���"))!=string::npos)	
		nCount++;
	if(sentence.find(_T("��;"))!=string::npos ||
		sentence.find(_T("����"))!=string::npos)	
		nCount++;

	if(nCount<3 && needCheck)	
		return false;

	// һ�������а����� ĳ���ؿ��������Ϣ
	vector<string> vecSplit;
	Pcre2Split(_T("(��|��|��)"), sentence, vecSplit);

	for(int i = 0; i< vecSplit.size(); i++)
	{
		string title = vecSplit[i];
		ProcessItem(title, title);
	}

	return true;
}

void CPDFGetLand::ProcessItem(string title, string strVal)
{

	if(title.find(_T("��������"))!=string::npos||
		title.find(_T("�ؿ�����"))!=string::npos ||
		title.find(_T("���ر��"))!=string::npos ||
		title.find(_T("�ڵر��"))!=string::npos ||
		title.find(_T("���Ʊ��"))!=string::npos ||
		title.find(_T("�ؿ���"))!=string::npos)
	{
		m_LandName[m_nLandName] = strVal;
		m_nLandName ++;
	}
	else if(title.find(_T("�������"))!=string::npos ||
		title.find(_T("�������"))!=string::npos ||
		title == _T("���"))
	{
		m_LandArea[m_nLandArea] = strVal;
		m_nLandArea++;
	}
	else if(title.find(_T("��;"))!=string::npos ||
		title.find(_T("�õ�����"))!=string::npos ||
		title.find(_T("ʹ������"))!=string::npos)
	{
		m_LandPurpose[m_nLandPurpose] = strVal;
		m_nLandPurpose++;
	}
	else if(title.find(_T("�ݻ���"))!=string::npos)
	{
		m_RateOfCapacity[m_nRateOfCapacity] = strVal;
		m_nRateOfCapacity++;
	}
	
	else if(title.find(_T("�ؿ�λ��"))!=string::npos||
		title.find(_T("����λ��"))!=string::npos)
	{
		m_LandLocation[m_nLandLocation] = strVal;
		m_nLandLocation++;
	}
	else if(title.find(_T("�������"))!=string::npos ||
		title.find(_T("�������ƹ�ģ"))!=string::npos)
	{
		//	�еĹ������ ����������еĹ�������� �ݻ���
		m_AreaOfStructure[m_nAreaOfStructure] = strVal;
		m_nAreaOfStructure++;
	}
	else if(title.find(_T("�ɽ����"))!=string::npos ||
		title.find(_T("�ɽ��ܼ�"))!=string::npos ||
		title.find(_T("�������"))!=string::npos ||
		title.find(_T("�ɽ��۸�"))!=string::npos ||
		title.find(_T("���üۿ�"))!=string::npos ||
		title.find(_T("�ɽ��ؼۿ�"))!=string::npos ||
		title.find(_T("�ɽ���"))!=string::npos)
	{
		m_DealMoney[m_nDealMoney] = strVal;
		m_nDealMoney++;
	}
	
}

void CPDFGetLand::ProcessTable(string sentence)
{
	//	�Ա�����ݽ��д���
	vector<string> vecSplit;
	Pcre2Split(_T("��"), sentence, vecSplit);
	for(int j=0; j< vecSplit.size(); j++)
	{
		string::size_type pos1 = vecSplit[j].find("<=>");
		if(pos1!=string::npos)
		{
			string title = vecSplit[j].substr(0, pos1);
			string strVal = vecSplit[j].substr(pos1 + 3);
			ProcessItem(title, strVal);
		}
	}
}


bool CPDFGetLand::AnalysisClause(vector<string> vecWord, string originalWord)
{
	string strType = "";
	string strUnit = "";
	bool isOk = false;
	for(int i =0; i< vecWord.size(); i++)
	{
		if(strType.empty())
		{
			if(vecWord[i].find(_T("�ݻ���"))!=string::npos)
				strType = "�ݻ���";

			if(vecWord[i].find(_T("�������"))!=string::npos ||
				vecWord[i].find(_T("�������ƹ�ģ"))!=string::npos)
			{
				strType = "�������";
				if(originalWord.find("<=>")!=string::npos && i+1 < vecWord.size())
				{
					//	���ı�ͷ�а����� ��λ
					double nVal = String2Double(vecWord[i+1]);
					if(nVal==0)
						strUnit = vecWord[i+1];
				}
			}

			if(vecWord[i].find(_T("�ܼۿ�"))!=string::npos || 
				vecWord[i].find(_T("�ɽ���"))!=string::npos ||
				vecWord[i].find(_T("�ܵؼ�"))!=string::npos || 
				vecWord[i].find(_T("���üۿ�"))!=string::npos ||
				vecWord[i].find(_T("�ɽ���"))!=string::npos ||
				vecWord[i].find(_T("�ɽ��۸�"))!=string::npos ||
				vecWord[i].find(_T("�ɽ��ܼ�"))!=string::npos ||
				vecWord[i].find(_T("�ɽ����"))!=string::npos || 
				vecWord[i].find(_T("�ɽ��ۿ�"))!=string::npos || 
				vecWord[i].find(_T("�����ܼ�"))!=string::npos || 
				vecWord[i].find(_T("���ü۸�"))!=string::npos || 
				vecWord[i].find(_T("�������"))!=string::npos || 
				vecWord[i].find(_T("�����ܽ��"))!=string::npos ||
				vecWord[i].find(_T("�ɽ��ؼۿ�"))!=string::npos || 
				vecWord[i].find(_T("�ܼ������"))!=string::npos )
			{
				strType = "�ɽ��ۿ�";
				if(originalWord.find("<=>")!=string::npos && i+1 < vecWord.size())
				{
					//	���ı�ͷ�а����� ��λ
					double nVal = String2Double(vecWord[i+1]);
					if(nVal==0)
						strUnit = vecWord[i+1];
				}
			}

			if(vecWord[i].find(_T("�������"))!=string::npos ||
				vecWord[i].find(_T("�������"))!=string::npos || 
				vecWord[i].find(_T("�õ����"))!=string::npos || 
				vecWord[i].find(_T("�ڵ����"))!=string::npos || 
				vecWord[i].find(_T("���"))==0 )
			{
				strType = "�������";
				if(originalWord.find("<=>")!=string::npos && i+1 < vecWord.size())
				{
					//	���ı�ͷ�а����� ��λ
					double nVal = String2Double(vecWord[i+1]);
					if(nVal==0)
						strUnit = vecWord[i+1];
				}
			}

			if(vecWord[i].find(_T("������;"))!=string::npos ||
				vecWord[i].find(_T("�õ�����"))!=string::npos ||
				vecWord[i].find(_T("�滮��;"))!=string::npos ||
				vecWord[i].find(_T("��;"))==0 )
				strType = "������;";
			
		}
		else
		{
			if(strType=="�ݻ���")
			{
				if(isOk==false)
				{
					double nVal = String2Double(vecWord[i]);
					if(nVal>0)
					{
						m_RateOfCapacity[m_nRateOfCapacity] = originalWord;
						m_nRateOfCapacity++;
						isOk = true;

					}
				}
				/*else
					m_RateOfCapacity[m_nRateOfCapacity -1] += vecWord[i];*/
				
			}

			if(strType=="�������")
			{

				if(isOk==false)
				{
					double nVal = String2Double(vecWord[i]);
					if(nVal>0)
					{
						m_LandArea[m_nLandArea] = vecWord[i];
						m_nLandArea++;
						isOk = true;
					}
				}
				else
					m_LandArea[m_nLandArea - 1] += vecWord[i];

				//	��񣬲��䵥λ
				if(strUnit.empty()==false && i == vecWord.size()-1 )
					m_LandArea[m_nLandArea - 1] += strUnit;

			}

			if(strType=="�ɽ��ۿ�")
			{

				if(isOk==false)
				{
					double nVal = String2Double(vecWord[i]);
					if(nVal>0)
					{
						m_DealMoney[m_nDealMoney] = vecWord[i];
						m_nDealMoney++;
						isOk = true;
					}
				}
				else if(m_DealMoney[m_nDealMoney - 1].find("Ԫ")==string::npos)
					m_DealMoney[m_nDealMoney - 1] += vecWord[i];

				//	��񣬲��䵥λ
				if(strUnit.empty()==false && i == vecWord.size()-1 )
					m_DealMoney[m_nDealMoney - 1] += strUnit;
				
			}

			if(strType=="������;")
			{
				if(isOk==false)
				{
					m_LandPurpose[m_nLandPurpose] = vecWord[i];
					isOk = true;
					m_nLandPurpose++;
				}
				else
					m_LandPurpose[m_nLandPurpose - 1] += vecWord[i];
			}

			if(strType=="�������")
			{

				if(isOk==false)
				{
					double nVal = String2Double(vecWord[i]);
					if(nVal>0)
					{
						m_AreaOfStructure[m_nAreaOfStructure] = vecWord[i];
						m_nAreaOfStructure++;
						isOk = true;
					}
				}
				else
					m_AreaOfStructure[m_nAreaOfStructure - 1] += vecWord[i];

				//	��񣬲��䵥λ
				if(strUnit.empty()==false && i == vecWord.size()-1 )
					m_AreaOfStructure[m_nAreaOfStructure - 1] += strUnit;

			}
		}
	}
	
	return true;
}


bool CPDFGetLand::AnalysisSegment(string segment, bool isTableCell)
{
	friso_task_t task;
	task = friso_new_task();

	// ������ֽ�ɾ���
	vector<string> vecSentence;
	if(isTableCell)
		Pcre2Split(_T("(��)"), segment, vecSentence);
	else
		Pcre2Split(_T("(��|��)"), segment, vecSentence);

	// ������������
	if(vecSentence.size()==0)
		vecSentence.insert(vecSentence.end(), segment);
	for(int i = 0; i< vecSentence.size(); i++)
	{
		vector<string> firstMatch;
		vector<int>		firstOffset;
		
		//	�����ӷֽ���Ӿ�
		string sentence = vecSentence[i].c_str();
		vector<string> vecClause;
		Pcre2Split(_T("(��)"), sentence, vecClause);
		if(vecClause.size()==0)
			vecClause.insert(vecClause.end(), sentence);

		// ���Ӿ���С����ķִʡ�
		for(int k=0; k< vecClause.size(); k++)
		{
			//set the task.
			friso_set_text( task, (char *)vecClause[k].c_str() );
			vector<string> vecWord;
			while ( ( g_config->next_token( g_friso, g_config, task ) ) != NULL ) 
			{
				string strWord = task->token->word;
				unsigned char uType = task->token->type;
				int kkk = 1;
				vecWord.insert(vecWord.end(), strWord);
			}
			AnalysisClause(vecWord, vecClause[k]);
		}
			
	}

	friso_free_task( task );

	return true;
}

bool CPDFGetLand::ProcessLevel(vector<CLineOrCell> & extractor)
{

	return true;
}


bool CPDFGetLand::ProcessNoLevel(vector<CLineOrCell> & pdf)
{
	//////////////////////////////////////////////////////////////////////////
	//	�޲�ε� PDF

	//	�Ѷ���ֽ⣬Ȼ�����еľ��Ӻϲ�
	vector<string>	sentences;
	for(int i=0; i< pdf.size(); i++)
	{
		vector<string> vecSplit;
		Pcre2Split(_T("(��)"), pdf[i].content, vecSplit);
		for(int j=0; j< vecSplit.size(); j++)
		{
			string tmpStr =  vecSplit[j];
			if(tmpStr.find(_T("��"))==string::npos)
				tmpStr += _T("��");
			sentences.insert(sentences.end(), tmpStr);
		}

	}

	//	�Ƿ�������
	m_bTable = false;
	for(int i=0; i< sentences.size(); i++)
	{
		vector<string> firstMatch;
		vector<int>		firstOffset;
		if(Pcre2Grep(_T("T[\\d]+��"), sentences[i] ,firstMatch, firstOffset) > 0)
		{
			AnalysisSegment(sentences[i], true);
			m_bTable = true;
			break;
		}
	}

	if(m_bTable)
	{
		if(m_nDealMoney==0)
		{
			ProcessDealMoney(pdf);
		}

	}
	else
	{
		//	�޲��
		//	������ �����ͷ������־���

		bool bBegin = false;
		for(int i=0; i< pdf.size(); i++)
		{
			AnalysisSegment(pdf[i].content);
		}


		if(m_nDealMoney==0)
		{
			//if( secCode == "002244" /*��������*/)
				ProcessDealMoney(pdf);
		}

	}
	return true;
}


void CPDFGetLand::ProcessDealMoney(vector<CLineOrCell> & pdf)
{
	for(int i=0; i<pdf.size(); i++)
	{
		// ������ֽ���Ӿ�
		vector<string> vecClause;
		Pcre2Split(_T("(��|��|��)"), pdf[i].content, vecClause);

		// ���������Ӿ�
		if(vecClause.size()==0)
			vecClause.insert(vecClause.end(), pdf[i].content);
		for(int k = 0; k< vecClause.size(); k++)
		{
			vector<string> firstMatch;
			vector<int>		firstOffset;
			if(Pcre2Grep(_T("��(.*)(�����)?[\\d\\,\\.]+(��|��)?Ԫ(.*)(����|����|��ȡ)"),vecClause[k], 
				firstMatch, firstOffset) > 0)
			{
				string strMatch = firstMatch[0];
				if(Pcre2Grep(_T("[\\d\\,\\.]+(��|��)?Ԫ"), strMatch, firstMatch, firstOffset) > 0)
				{
					m_DealMoney[m_nDealMoney] = firstMatch[0];
					m_nDealMoney++;
				}
			}

		}
	
	}			
}

string CPDFGetLand::SaveAsCsv()
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
	
	// �ж��Ƿ�Ϊ�в�ε�����
	m_bLevel = false;
	for(int i=0; i< extractor.m_pdf.size(); i++)
	{
		if(extractor.m_pdf[i].parent != -1)
		{
			m_bLevel = true;
			break;
		}
	}

	static int nTotal = 0;
	static int nMatch = 0;
	if(!m_bLevel)
	{

		ProcessNoLevel(extractor.m_pdf);
		
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		//	�в�εĹ���
		m_bTable = false;
		for(int i=0; i<extractor.m_pdf.size(); i++)
		{
			vector<string>	firstMatch;
			vector<int>		firstOffset;
			if(Pcre2Grep(_T("T[\\d]+��"), extractor.m_pdf[i].content ,firstMatch, firstOffset) > 0)
			{
				//ProcessTable(extractor.m_pdf[i].content);
				AnalysisSegment(extractor.m_pdf[i].content, true);
				m_bTable = true;
			}
		}

		if(m_bTable )
		{
			if(m_nDealMoney==0)
				//if(secName == _T("�ٰ��ز�") || secName ==_T("̩�̼���"))
					ProcessDealMoney(extractor.m_pdf);
		}
		else
		{
			//	�в�Σ����ޱ�����Ȳ���Ŀ�길���
						
			for(int i=0; i< extractor.m_pdf.size(); i++)
			{
				AnalysisSegment(extractor.m_pdf[i].content);
			}

			//if( secCode == "000069" /*���ȳǣ�*/)
			if(m_nDealMoney==0)
				ProcessDealMoney(extractor.m_pdf);
		}
	}



	/*string strContent = "";
	for(int i = 0; i< extractor.m_mapPageContent.size(); i++)
	{
		if(extractor.m_mapPageContent.count(i)>0 )
		{
			strContent += extractor.m_mapPageContent[i];
		}
	}*/

	//////////////////////////////////////////////////////////////////////////

	/*HANDLE hEvtRequestSubmitted = OpenEvent(EVENT_ALL_ACCESS , 
		FALSE, "RequestSubmitted"); 

	HANDLE hEvtResultReturned = OpenEvent(EVENT_ALL_ACCESS , 
		FALSE,	"ResultReturned"); 

	if(hEvtResultReturned==NULL || hEvtRequestSubmitted == NULL)
	{
		if(hEvtRequestSubmitted)	CloseHandle(hEvtRequestSubmitted);
		if(hEvtResultReturned)		CloseHandle(hEvtResultReturned);

		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF OpenEvent Err. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		return ss.str();
	}

	HANDLE hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, 
		FALSE, 
		"ShareMemoryTest"); 
	if (NULL == hFileMapping) 
	{ 
		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF OpenFileMapping Err." ;
		ss << "GetLastError = " << GetLastError() << " \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		return ss.str();
	} 

	LPVOID lpShareMemory = MapViewOfFile(hFileMapping, 
		FILE_MAP_ALL_ACCESS, 0, 0, 0); 

	if (NULL == lpShareMemory) 
	{ 
		if (NULL != hFileMapping)    CloseHandle(hFileMapping); 

		ss.str("");
		ss << "��"  << adjunctUrl << "��";
		ss << " PDF MapViewOfFile Err." ;
		ss << "GetLastError = " << GetLastError() << " \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);

		return ss.str();
	} */

	//	�� FlexBisonTest �������������󣬲��ȴ�����������
	/*char * p = (char *)lpShareMemory;
	memset(p, 0, 4096);
	memcpy(p, strContent.c_str(), strContent.length());
	SetEvent(hEvtRequestSubmitted);

	WaitForSingleObject(hEvtResultReturned, INFINITE);

		
	if(hEvtRequestSubmitted)	CloseHandle(hEvtRequestSubmitted);
	if(hEvtResultReturned)		CloseHandle(hEvtResultReturned);

	if (NULL != lpShareMemory)   UnmapViewOfFile(lpShareMemory); 
	if (NULL != hFileMapping)    CloseHandle(hFileMapping);*/ 

	return "AlreadyInMemory";
}

string CPDFGetLand::SqlScript()
{
	stringstream ss;
	ss.str("");
	ss << "create table if not exists Cninfo_Get_Land ( " 
		<< "announcementId varchar(32),  secCode varchar(32), secName varchar(32), announcementTime date,  "
		<< "announcementTitle varchar(128), adjunctUrl varchar(128),  land_num int ,land_name varchar(64), "
		<< "deal_money varchar(128), rate_of_capacity varchar(32), Land_Purpose varchar(32),"
		<< "area_of_structure  varchar(64),"
		<< "land_area varchar(64),  PRIMARY KEY ( announcementId, land_num ))";

	return ss.str();
}

void CPDFGetLand::ImportToDatabase(string csv)
{
	if(csv=="AlreadyInMemory")
	{

	}
	else
	{

		return;
	}

	stringstream ss;
	

	try
	{
		ss << "CPDFGetLand::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		sql << SqlScript();

		if(m_nDealMoney > 0 )
		{
			ss.str("");
			ss << " insert into Cninfo_Get_Land (  announcementId, secCode, secName, announcementTime, announcementTitle,"
				<< " adjunctUrl, land_num, deal_money, rate_of_capacity, Land_Purpose, land_area, area_of_structure) values ";

			for( int i =0; i< m_nDealMoney; i++ )
			{
				ss	<< "( \'" << announcementId << "\' ," 
					<< "\'" << secCode << "\' ,"
					<< "\'" << secName << "\' ,"
					<< "\'" << announcementTime << "\' ,"
					<< "\'" << announcementTitle << "\' ,"
					<< "\'http://www.cninfo.com.cn/" << adjunctUrl << "\' ," << i << ", "
					<< "\'" << m_DealMoney[i] << "\' ,"
					<< "\'" << (i<m_nRateOfCapacity? m_RateOfCapacity[i]:"") << "\',"
					<< "\'" << (i<m_nLandPurpose? m_LandPurpose[i]:"") << "\',"
					<< "\'" << (i<m_nLandArea? m_LandArea[i]:"") << "\',"
					<< "\'" << (i<m_nAreaOfStructure? m_AreaOfStructure[i]:"") << "\'  )";

				if(i< m_nDealMoney-1)
					ss << ",";
			}

			string test = ss.str();
			sql << test;
		}
		else
		{
			//	�������ɹ�
			ss.str("");
			ss << " insert into Cninfo_Get_Land (  announcementId, secCode, secName, announcementTime, announcementTitle,"
				<< " adjunctUrl, land_num, deal_money ) values ";

			ss	<< "( \'" << announcementId << "\' ," 
				<< "\'" << secCode << "\' ,"
				<< "\'" << secName << "\' ,"
				<< "\'" << announcementTime << "\' ,"
				<< "\'" << announcementTitle << "\' ,"
				<< "\'http://www.cninfo.com.cn/" << adjunctUrl << "\' ,"
				<< "0 , '�������ɹ�(��)' )";

			sql << ss.str();
		}

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << "\r\n";
		sendToOutput(ss.str().c_str(), m_hWnd);
	}
}

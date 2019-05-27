#include "StdAfx.h"
#include "CninfoAnnouncement.h"

#include "UrlUtils.h"

map<string, string>	CCninfoAnnouncement::map_plate;
map<string, string>	CCninfoAnnouncement::map_category;
map<string, string>	CCninfoAnnouncement::map_trade;


CCninfoAnnouncement::CCninfoAnnouncement(void)
{
}

CCninfoAnnouncement::~CCninfoAnnouncement(void)
{
	
}



int CCninfoAnnouncement::CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	return CSV_CHECK_NO_ERROR;
}



void CCninfoAnnouncement::ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData)
{
	
}

void CCninfoAnnouncement::ParseXmlElement(void)
{
}

bool CCninfoAnnouncement::ParseCsvFileName(string szFileName)
{
	vector<string> firstMatch;
	if(Pcre2Grep(_T("SouhuTradingDaily\\(\\d+\\)"), szFileName,firstMatch )<=0)
		return false;

	string::size_type pos1 = firstMatch[0].find(")");
	string codeStr = firstMatch[0].substr(18, pos1-18);
	m_nCode = atoi(codeStr.c_str());
	return true;
}

void CCninfoAnnouncement::ImportToDatabase(void)
{
	/*if(m_nCode<=0)
		return;*/

	stringstream ss;
	try
	{
		ss << "CCninfoAnnouncement::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		sql << SqlScript();

		ss.str("");
		ss << " insert into CninfoAnnouncement ( secCode, secName,orgId, announcementId, announcementTitle, "
			<< "announcementTime, adjunctUrl, adjunctSize, adjunctType, storageTime, columnId, pageColumn, "
			<< "announcementType, announcementTypeName ) values ";
		for(int i =0 ; i< announcementId.size(); i++)
		{
			struct tm curr_tm;
			char tmp[256] = { 0 };
			
			time_t time_announcementTime =  String2Double(announcementTime[i])/1000;
			localtime_s(&curr_tm, &time_announcementTime);
			snprintf (tmp, 255, "%4d-%02d-%02d", 1900 + curr_tm.tm_year, curr_tm.tm_mon+1, curr_tm.tm_mday);
			string strAnnouncementTime  = tmp;

			time_t time_storageTime = String2Double(storageTime[i])/1000.0 ;
			localtime_s(&curr_tm, &time_storageTime);
			snprintf (tmp, 255, "%4d-%02d-%02d", 1900 + curr_tm.tm_year, curr_tm.tm_mon+1, curr_tm.tm_mday);
			string strStorageTime = tmp;

			ss	<< "( \'" << secCode[i] << "\' , \'" 
				<< secName[i] << "\', \'"
				<< orgId[i] << "\', \'"
				<< announcementId[i] << "\', \'"
				<< announcementTitle[i] << "\', \'"
				<< strAnnouncementTime << "\', \'"
				<< adjunctUrl[i] << "\', \'"
				<< adjunctSize[i] << "\', \'"
				<< adjunctType[i] << "\', \'"
				<< strStorageTime << "\', \'"
				<< columnId[i] << "\', \'"
				<< pageColumn[i] << "\', \'"
				<< announcementType[i] << "\', \'"
				<< announcementTypeName[i] << "\' )";

			if(i< announcementId.size() - 1)
				ss << ",";
		}

		string test = ss.str();
		//test = Gbk2Utf8(test);
		sql << test;
		
		ss.str("");
		ss << "�������� " << announcementId.size() ;
		ss << " OK, CCninfoAnnouncement::ImportToDatabase ���ݵ������. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
		//return EXIT_SUCCESS;
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}

	//	���������� PDF �ĵ�
	for(int i = 0 ; i< vecPDF.size(); i++)
	{
		if(vecPDF[i].mapCatalog.size()>0)
		{
			vecPDF[i].ImportToDatabase();
		}
	}
	
}

CStockDataModel * CCninfoAnnouncement::NewCopy()
{
	return NULL;
}



string CCninfoAnnouncement::GetDownloadUrl()
{
	return "";
}


string CCninfoAnnouncement::SqlScript()
{
	stringstream ss;
	ss << "create table if not exists CninfoAnnouncement (secCode varchar(16) ,secName varchar(32), orgId varchar(32), " 
		<< "announcementId varchar(32), announcementTitle varchar(128), announcementTime date, adjunctUrl varchar(128), "
		<< "adjunctSize int, adjunctType varchar(32), storageTime date, columnId varchar(256), pageColumn varchar(256),  "
		<< "announcementType varchar(32), announcementTypeName varchar(128), PRIMARY KEY ( announcementId ))";
	return ss.str();
}



string  CCninfoAnnouncement::SaveAsCsv()
{
	stringstream ss;

	/*�������ء����桱������Ϣ*/
	if(map_category.size()==0)
	{
		string jsonPage =CUrlUtils::PostUrlOfSouhu("http://www.cninfo.com.cn//cninfo-new/js/data/szse.json",NULL);
		jsonPage = Utf8_GBK(jsonPage);

		Json::Value jsonRoot;
		Json::Reader reader(Json::Features::strictMode());
		bool parsingSuccessful = reader.parse(jsonPage, jsonRoot);
		if(parsingSuccessful )
		{
			Json::Value json_result = jsonRoot["category"];
			if(1)
			{
				vector<string>  vecKey =  json_result.getMemberNames();
				for(int i=0; i<vecKey.size(); i++)
				{
					map_category[vecKey[i]] = json_result[vecKey[i]].asString();
				}
			}
			
		}
	}

	time_t time_start;
	time_t time_end;

	/* ����Ҫ���صĿ�ʼʱ�� */
	string strLastTradeDate = LastTradeDateFromDatabase();
	if(!strLastTradeDate.empty())
		time_start = convert_string_to_time_t(strLastTradeDate + string(" 01:00:00"));
	else
		time_start = convert_string_to_time_t("1990-01-01 00:00:00");

	time_start += 24 * 3600;

	char tmp[256] = { 0 };
	struct tm curr_tm;
	localtime_s(&curr_tm, &time_start);
	snprintf (tmp, 255, "%4d-%02d-%02d", 1900 + curr_tm.tm_year, curr_tm.tm_mon+1, curr_tm.tm_mday);
	string strStart = string(tmp);

	time_end = time(NULL);
	localtime_s(&curr_tm, &time_end);
	snprintf (tmp, 255, "%4d-%02d-%02d", 1900 + curr_tm.tm_year, curr_tm.tm_mon+1, curr_tm.tm_mday);
	string strEnd = string(tmp);

	/*�����ೢ���Ƿ����µ�����*/

	memset(tmp, 0, 256);
	snprintf(tmp, 255, "%06d", m_nCode);

	// szse_sme    relation   ; ��С�塢 ��ҵ�� ���������� sse ��  
	ss.str("");
	ss << "stock=" << string(tmp) << "%2C" << m_orgId << "%3B&searchkey=&plate=&category="   
		<< "&trade=&column=sse&columnTitle=%E5%8E%86%E5%8F%B2%E5%85%AC%E5%91%8A%E6%9F%A5%E8%AF%A2"
		<< "&pageNum=1&pageSize=30"  
		<< "&tabName=fulltext&sortName=time&sortType=asc&limit=&seDate=" << strStart << "+~+" << strEnd;

	string postUrl = ss.str();
	string jsonPage =CUrlUtils::PostUrlOfSouhu("http://www.cninfo.com.cn/cninfo-new/announcement/query",(char *)(postUrl).c_str());
	jsonPage = Utf8_GBK(jsonPage);

	if(jsonPage.find("\"announcements\":[]")!=string::npos)
	{
		return "NoMoreData";
	}

	if(jsonPage.find("\"totalAnnouncement\":0,")!=string::npos)
	{
		return "NoMoreData";
	}

	if(m_orgId.empty())
	{
		ss.str("");
		ss << "CCninfoAnnouncement::SaveAsCsv��m_orgId Ϊ�� ���� " ;
		sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);
		return "";
	}

	
	/* ��ʼ�������� */
	map<string, string>::iterator it = map_category.begin();
	for(; it!=map_category.end(); it++)
	{
		/*����Ĺؼ���*/
		string strKey = it->first;

		int pageNum = 1;
		int pageSize = 30;
		bool bSuccess = true;
		do{
			char tmp[256] = { 0 };
			snprintf(tmp, 255, "%06d", m_nCode);

			ss.str("");
			ss << "stock=" << string(tmp) << "%2C" << m_orgId << "%3B&searchkey=&plate=&category=" << strKey  
				<< "&trade=&column=szse&columnTitle=%E5%8E%86%E5%8F%B2%E5%85%AC%E5%91%8A%E6%9F%A5%E8%AF%A2"
				<< "&pageNum=" + Int2String(pageNum) << "&pageSize=" << Int2String(pageSize)  
				<< "&tabName=fulltext&sortName=time&sortType=asc&limit=&seDate=" << strStart << "+~+" << strEnd;

			string postUrl = ss.str();
			string jsonPage =CUrlUtils::PostUrlOfSouhu("http://www.cninfo.com.cn/cninfo-new/announcement/query",(char *)(postUrl).c_str());
			//jsonPage = Utf8_GBK(jsonPage);

			if(jsonPage.empty())
			{
				break;
			}

			if(jsonPage.find("\"announcements\":[]")!=string::npos)
			{
				break;
			}

			if(jsonPage.find("\"totalAnnouncement\":0,")!=string::npos)
			{
				break;
			}


			if(jsonPage.find("\"announcements\":[{")!=string::npos)
			{
				Json::Value jsonRoot;
				Json::Reader reader(Json::Features::strictMode());

				/*char tmp[10000] = { 0 };
				FILE * f_in = fopen("c:/jsontest.txt" , "rb+");
				fread(tmp, sizeof(char), 10000, f_in);
				fclose(f_in);

				jsonPage = string(tmp);
				jsonPage = Utf8_GBK(jsonPage);*/

				bool parsingSuccessful = reader.parse(jsonPage, jsonRoot);
				if (!parsingSuccessful) {
					ss.str("");
					ss << "CCninfoAnnouncement::SaveAsCsv������ JSON ���� " ;
					ss << reader.getFormattedErrorMessages().c_str();
					sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);

					bSuccess = false;
					break;
				}
				else
				{
					Json::Value json_result = jsonRoot["announcements"];
					if(json_result.type()== Json::arrayValue)
					{
						int size = json_result.size();
						if(size>0)
						{
							for(int index = 0; index< size; index++)
							{
								Json::Value  struction = json_result[index];

								string  aid =  struction["announcementId"].asString();
								bool bExist = false;
								for(int w = 0; w < announcementId.size(); w++)
								{
									if(announcementId[w] == aid)
									{
										//	���Ӹù��������ķ���
										announcementTypeName[w] = announcementTypeName[w] + "," + map_category[strKey];
										bExist = true;
										break;
									}
								}

								if(bExist==false)
								{
									secCode.insert(secCode.end(), struction["secCode"].asString());
									secName.insert(secName.end(), Utf8_GBK(struction["secName"].asString()));
									orgId.insert(orgId.end(), struction["orgId"].asString());
									announcementId.insert(announcementId.end(), struction["announcementId"].asString());
									string strTitle =  struction["announcementTitle"].asString();
									strTitle = Utf8_GBK(strTitle);
									strTitle = ReplaceString(strTitle, _T("'"), _T("��"));
									announcementTitle.insert(announcementTitle.end(), strTitle);
									announcementTime.insert(announcementTime.end(), struction["announcementTime"].asString());
									adjunctUrl.insert(adjunctUrl.end(), struction["adjunctUrl"].asString());
									adjunctSize.insert(adjunctSize.end(), struction["adjunctSize"].asString());
									adjunctType.insert(adjunctType.end(), struction["adjunctType"].asString());
									storageTime.insert(storageTime.end(), struction["storageTime"].asString());
									columnId.insert(columnId.end(), struction["columnId"].asString());
									pageColumn.insert(pageColumn.end(), struction["pageColumn"].asString());
									announcementType.insert(announcementType.end(), struction["announcementType"].asString());
									announcementTypeName.insert(announcementTypeName.end(), map_category[strKey]);
								}
							}
						}
						ss.str("");
						ss << "CCninfoStockInfo::SaveAsCsv����ȡ JSON ���ݳɹ�.";
						//sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);

						if(size < pageSize)
							break;
						else
							pageNum++;
					}
					else
					{
						ss.str("");
						ss << "CCninfoStockInfo::SaveAsCsv����ȡ JSON �е� Result ����ʧ��." ;
						sendToOutput(ss.str().c_str(),m_hWnd, m_nLogType);

						bSuccess = false;
						break;
					}

				}
			}
		}while(1);

		if(bSuccess==false)
			return "";

		/* ��ʼ������һ���ķ��๫�� */
	}
	


	int nSize = secCode.size();
	if(nSize==secName.size()&&
		nSize==orgId.size()&&
		nSize==secName.size()&&
		nSize==announcementId.size()&&
		nSize==announcementTitle.size()&&
		nSize==announcementTime.size()&&
		nSize==adjunctUrl.size()&&
		nSize==adjunctSize.size()&&
		nSize==adjunctType.size()&&
		nSize==storageTime.size()&&
		nSize==columnId.size()&&
		nSize==pageColumn.size()&&
		nSize==announcementType.size()&&
		nSize==announcementTypeName.size()&&
		nSize > 0)
	{
		//	�ж��Ƿ���Ҫ���� PDF ���н�һ������
		for(int i = 0; i< announcementTitle.size(); i++)
		{

			if(announcementTitle[i].find("���»����")!=string::npos)
				continue;
			if(announcementTitle[i].find("��֪ͨ")!=string::npos)
				continue;
			if(announcementTitle[i].find("��������")!=string::npos)
				continue;
			if(announcementTitle[i].find("����ժҪ")!=string::npos)
				continue;

			if(announcementTitle[i].find("ҵ���챨")!=string::npos)
				continue;
			if(announcementTitle[i].find("��������")!=string::npos)
				continue;
			if(announcementTitle[i].find("��������")!=string::npos)
				continue;
			if(announcementTitle[i].find("���������")!=string::npos)
				continue;

			if(announcementTitle[i].find("��ʾ�Թ���")!=string::npos)
				continue;
			if(announcementTitle[i].find("�Ĺ���")!=string::npos)
				continue;
			if(announcementTitle[i].find("��չ����")!=string::npos)
				continue;
			if(announcementTitle[i].find("�������")!=string::npos)
				continue;

			if(announcementTitle[i].find("������")!=string::npos)
				continue;
			if(announcementTitle[i].find("������")!=string::npos)
				continue;
			if(announcementTitle[i].find("��������")!=string::npos)
				continue;
			if(announcementTitle[i].find("�������")!=string::npos)
				continue;

			if(announcementTitle[i].find("�˲����")!=string::npos)
				continue;
			if(announcementTitle[i].find("�غ�")!=string::npos)
				continue;
			if(announcementTitle[i].find("ͣ�ƹ���")!=string::npos)
				continue;
			if(announcementTitle[i].find("�䶯����")!=string::npos)
				continue;

			if(announcementTitle[i].find("�������")!=string::npos)
				continue;
			if(announcementTitle[i].find("���׹���")!=string::npos)
				continue;
			if(announcementTitle[i].find("���֪ͨ��")!=string::npos)
				continue;
			if(announcementTitle[i].find("�䶯����")!=string::npos)
				continue;


			// ��������Ч�����⣬�öδ��벻�ã���Ϊ �ڶ����� exe �н��� ���� pdf �Ľ���
			if(/*announcementTitle[i].find("")!=string::npos*/ 0)
			{
				/*CCninfoAnnouncePDF pdf;
				pdf.announcementId = announcementId[i];
				pdf.adjunctUrl = adjunctUrl[i];
				pdf.announcementTitle = announcementTitle[i];
				pdf.m_hWnd = m_hWnd;
				pdf.m_nLogType = m_nLogType;
				pdf.SaveAsCsv();

				vecPDF.push_back(pdf);*/
			}
		}

		return "AlreadyInMemory";
	}

	return "NoMoreData";
}

string CCninfoAnnouncement::GetCsvFileName()
{
	return "";
}


void CCninfoAnnouncement::ExportFromDatabase(double startTime, double endTime)
{
	
}


string CCninfoAnnouncement::LastTradeDateFromDatabase()
{
	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();
	string lastTradeDate = "";
	try
	{
		
		//////////////////////////////////////////////////////////////////////////
		char tmp[256] = { 0 };
		snprintf(tmp, 255, "%06d", m_nCode);

		session sql(g_MysqlPool);
		sql << "call add_ind('CninfoAnnouncement', 'secCode', 'idx_secCode')";
		sql << "call add_ind('CninfoAnnouncement', 'announcementTime', 'idx_announcementTime')";

		ss.str("");
		ss << "select max(announcementTime) as maxdate "
			<< " from CninfoAnnouncement where secCode=\'" << string(tmp)<<"\'" ;

		string test = ss.str();

		row r;
		//session sql(backEnd, m_ConnectString);
		

		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		int cnt = 0;
		while (st.fetch())
		{
			{
				std::tm  tm = r.get<std::tm>("maxdate");
				ss.str("");
				ss << (tm.tm_year + 1900) << "-" << (tm.tm_mon + 1) << "-" << tm.tm_mday ;
				lastTradeDate = ss.str();
				break;
			}

			cnt++;
		}

	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	return lastTradeDate;
}

void CCninfoAnnouncement::NotifyDatabaseImportedToWindow()
{
	/*stringstream ss;
	ss << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>";
	ss << "<root>";
	ss << "<msg_type code=\"" << m_nCode << "\" ";
	ss << " model=\"" << ModelType() << "\" ";
	ss << " >DatabaseImported</msg_type>";
	ss << "<data " ;
	if(m_vec_close.size()>0)
	{
		ss << " param1=\"" << m_vec_report_date[0] << "\" ";
		ss << " param2=\"" << Double2String(m_vec_close[0]) << "\" ";
	}
	ss << " >";
	ss << "</data></root>";

	sendToOutput(ss.str().c_str(), m_hWnd);*/
}

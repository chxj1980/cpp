#include "StdAfx.h"
#include "Stock.h"
#include "CalcUpdateStockInfo.h"

CCalcUpdateStockInfo::CCalcUpdateStockInfo(HWND hwnd, int logType)
:CCalculateTask(hwnd, logType)
{
}

CCalcUpdateStockInfo::~CCalcUpdateStockInfo(void)
{
}




void CCalcUpdateStockInfo::Execute1(void* firstArg)
{
	CCalcUpdateStockInfo * sink = (CCalcUpdateStockInfo *)firstArg;
	sink->Execute();
}

string Sohu2StatsGovAreaCode(map<string, string> & mapReg, string areaName)
{
	static map<string, string>	mapStatsGov;
	if(mapStatsGov.count(areaName)>0)
		return mapStatsGov[areaName];

	string::size_type pos = areaName.find("���");
	string strTmp = areaName.substr(0, pos);
	map<string ,string>::iterator it = mapReg.begin();
	for(; it!=mapReg.end(); it++)
	{
		string strSecond = it->second;
		if(strSecond.find(strTmp)!=string::npos)
		{
			mapStatsGov[areaName] = it->first;
			return it->first;
		}
	}
	return "";
}

void CCalcUpdateStockInfo::Execute()
{
	/*������Ҫ���ز��񱨱�Ĺ�Ʊ*/

	stringstream ss;
	try{
		
		session sql(g_MysqlPool);
		CStockPlateTree * pPlates = NULL;
		//////////////////////////////////////////////////////////////////////////
		//	���� ��֤��ҵ��Ϣ
		pPlates = ((CStockApp *)AfxGetApp())->m_pCsindexStockPlates;
		if(pPlates)
		{
			sql << "call add_col('stockinfo', 'csi_first_industry_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'csi_first_industry_name', 'varchar(64)', '')";

			sql << "call add_col('stockinfo', 'csi_second_industry_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'csi_second_industry_name', 'varchar(64)', '')";

			sql << "call add_col('stockinfo', 'csi_third_industry_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'csi_third_industry_name', 'varchar(64)', '')";

			sql << "call add_col('stockinfo', 'csi_fourth_industry_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'csi_fourth_industry_name', 'varchar(64)', '')";

			CStockPlateTree::pre_order_iterator pre_order_it = pPlates->pre_order_begin();
			while(pre_order_it!=pPlates->pre_order_end())
			{
				CStockPlateData spd = *pre_order_it;
				if(spd.is_stock==1)
				{
					vector<CStockPlateData>		vecData;
					vecData.insert(vecData.end(), spd);
					CStockPlateTree * pNode = (CStockPlateTree *)pre_order_it.node()->parent();
					while(pNode->is_root()==false)
					{
						spd = *pNode->get();
						vecData.insert(vecData.end(), spd);
						pNode = (CStockPlateTree *)pNode->parent();
					}
					//	���� StockInfo ���ж�Ӧ��Ʊ��¼

					ss.str("");
					ss << "update stockinfo set "
						<< " csi_fourth_industry_code=\'" << vecData[1].code << "\' ,"
						<< " csi_fourth_industry_name=\'" << vecData[1].name << "\' ,"

						<< " csi_third_industry_code=\'" << vecData[2].code << "\' ,"
						<< " csi_third_industry_name=\'" << vecData[2].name << "\' ,"

						<< " csi_second_industry_code=\'" << vecData[3].code << "\' ,"
						<< " csi_second_industry_name=\'" << vecData[3].name << "\' ,"

						<< " csi_first_industry_code=\'" << vecData[4].code << "\' ,"
						<< " csi_first_industry_name=\'" << vecData[4].name << "\' "
						<< " where code = " << vecData[0].code ;

					sql << /*Gbk2Utf8*/(ss.str());

				}
				
				pre_order_it++;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//	���� ֤�����ҵ��Ϣ

		pPlates = ((CStockApp *)AfxGetApp())->m_pCsindexCsrcStockPlates;
		if(pPlates)
		{
			sql << "call add_col('stockinfo', 'csrc_gate_industry_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'csrc_gate_industry_name', 'varchar(64)', '')";

			sql << "call add_col('stockinfo', 'csrc_big_industry_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'csrc_big_industry_name', 'varchar(64)', '')";

			CStockPlateTree::pre_order_iterator pre_order_it = pPlates->pre_order_begin();
			while(pre_order_it!=pPlates->pre_order_end())
			{
				CStockPlateData spd = *pre_order_it;
				if(spd.is_stock==1)
				{
					vector<CStockPlateData>		vecData;
					vecData.insert(vecData.end(), spd);
					CStockPlateTree * pNode = (CStockPlateTree *)pre_order_it.node()->parent();
					while(pNode->is_root()==false)
					{
						spd = *pNode->get();
						vecData.insert(vecData.end(), spd);
						pNode = (CStockPlateTree *)pNode->parent();
					}
					//	���� StockInfo ���ж�Ӧ��Ʊ��¼

					ss.str("");
					ss << "update stockinfo set "
						<< " csrc_big_industry_code=\'" << vecData[1].code << "\' ,"
						<< " csrc_big_industry_name=\'" << vecData[1].name << "\' ,"

						<< " csrc_gate_industry_code=\'" << vecData[2].code << "\' ,"
						<< " csrc_gate_industry_name=\'" << vecData[2].name << "\' "
						<< " where code = " << vecData[0].code ;

					sql << /*Gbk2Utf8*/(ss.str());

				}

				pre_order_it++;
			}
		}


		//////////////////////////////////////////////////////////////////////////
		//	���� ʡ����Ϣ

		pPlates = ((CStockApp *)AfxGetApp())->m_pCSouhuStockPlates;
		CStockPlateData treeNode;
		treeNode.code = Int2String(1632, "%08d");		//	1632 ������
		treeNode.is_stock = 0;

		pPlates = pPlates->SearchSpecialNode(treeNode);
		if(pPlates)
		{
			sql << "call add_col('stockinfo', 'statsgov_area_code', 'varchar(32)', '')";
			sql << "call add_col('stockinfo', 'statsgov_area_name', 'varchar(64)', '')";

			CStatsGovCn  statsGov;
			map<string, string> mapReg = statsGov.GetOtherWds("", "");

			CStockPlateTree::pre_order_iterator pre_order_it = pPlates->pre_order_begin();
			while(pre_order_it!=pPlates->pre_order_end())
			{
				CStockPlateData spd = *pre_order_it;
				if(spd.is_stock==1)
				{
					vector<CStockPlateData>		vecData;
					vecData.insert(vecData.end(), spd);
					CStockPlateTree * pNode = (CStockPlateTree *)pre_order_it.node()->parent();
					while(pNode->is_root()==false)
					{
						spd = *pNode->get();
						vecData.insert(vecData.end(), spd);
						pNode = (CStockPlateTree *)pNode->parent();
					}
					//	���� StockInfo ���ж�Ӧ��Ʊ��¼
				
					string strStatsGovCode = Sohu2StatsGovAreaCode(mapReg, vecData[1].name);

					if(strStatsGovCode.empty()==false)
					{
						ss.str("");
						ss << "update stockinfo set "
							<< " statsgov_area_code=\'" << strStatsGovCode << "\' ,"
							<< " statsgov_area_name=\'" << mapReg[strStatsGovCode] << "\' "
							<< " where code = " << vecData[0].code ;

						sql << /*Gbk2Utf8*/(ss.str());
					}
				}
				pre_order_it++;
			}
		}

		ss.str("");
		ss << "CCalcUpdateStockInfo �������";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	catch(std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}

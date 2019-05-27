#include "StdAfx.h"
#include "SelfSelectStockPlates.h"
#include "..\SLClib\slc.h"

CSelfSelectStockPlates::CSelfSelectStockPlates(void)
{
	m_pTree = new CStockPlateTree;

	m_mutex.Init();

	/*CStockPlateData root;
	root.code = 0;
	root.name = "Root";
	root.is_stock = 0;
	root.parent_code = -1;
	m_pTree->InsertChild(root);*/
}

CSelfSelectStockPlates::~CSelfSelectStockPlates(void)
{
	if(m_pTree!=NULL)
		delete m_pTree;
}


string CSelfSelectStockPlates::SqlScript()
{
	stringstream ss;
	ss << "create table if not exists SelfSelectStockPlates (Code int , Name varchar(256), Company_Number int, "
		<< " Parent_Code int, Is_Stock int,  PRIMARY KEY ( Code, Parent_Code))";
	return ss.str();
}



void CSelfSelectStockPlates::ExportFromDatabase(double startTime, double endTime)
{
	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	

	try
	{
		ss << "SelfSelectStockPlates ��ʼ�� MYSQL ��ȡ����......";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		//////////////////////////////////////////////////////////////////////////
		ss.str("");
		ss << "select Code, Name, Company_Number, Parent_Code, Is_Stock"
			<< " from SelfSelectStockPlates order by Is_Stock, Parent_Code, Code" ;

		row r;
		//session sql(backEnd, m_ConnectString);
		session sql(g_MysqlPool);

		string test =  ss.str();

		statement st = (sql.prepare << ss.str(),into(r)) ;
		st.execute();

		int cnt = 0;
		while (st.fetch())
		{
			vec_code[cnt] = r.get<int>("Code");
			vec_name[cnt] = /*Utf8_GBK*/(r.get<string>("Name"));
			vec_company_number[cnt] = r.get<int>("Company_Number");
			vec_parent_code[cnt] = r.get<int>("Parent_Code");
			vec_is_stock[cnt] = r.get<int>("Is_Stock");

			cnt++;
		}

		if(m_pTree!=NULL){
			delete m_pTree;
		}
		m_pTree = new CStockPlateTree;

		CStockPlateTree::iterator it;   // ����һ�� child iterator

		CStockPlateTree * pNode = NULL;
		for(int i=0; i<vec_code.size(); i++)
		{
			CStockPlateData treeNode;
			treeNode.code = Int2String(vec_code[i], vec_is_stock[i]==1? "%06d" : "%08d");
			treeNode.name = vec_name[i];
			treeNode.company_number = vec_company_number[i];
			treeNode.is_stock = vec_is_stock[i];

			CStockPlateData treeNodeParent;
			treeNodeParent.code = Int2String(vec_parent_code[i], "%08d");
			treeNodeParent.is_stock = 0;

			if(pNode)
			{
				CStockPlateData spd = *pNode->get();
				if(spd.code != treeNodeParent.code || spd.is_stock!=0)
					pNode = NULL;
			}

			if(pNode==NULL)
				pNode = m_pTree->SearchSpecialNode(treeNodeParent);
			if(pNode)
			{
				pNode->insert(treeNode);
			}
			else
			{
				//if(treeNodeParent.code==-1)
					m_pTree->insert(treeNode);
			}

			//do{
			//	CStockPlateTree * pNodeTmp = m_pTree->SearchSpecialNode(treeNodeParent, pNode);
			//	if(pNodeTmp)
			//	{
			//		pNode=pNodeTmp;
			//		break;
			//	}

			//	//	�򸸽ڵ���ݣ�ֱ���ɹ�
			//	if(pNode->is_root()==false)
			//	{
			//		pNode = (CStockPlateTree *)pNode->parent();
			//	}
			//	else
			//		break;
			//}while(1);

			//pNode->insert(treeNode);
		}

		ss.str("");
		ss << "OK, �� MYSQL ��ȡ�������.";
		ss << " �� " << cnt << "�� \r\n" ;
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << ' \r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}

vector<string> CSelfSelectStockPlates::MailContents()
{
	vector<string> vecContents;
	stringstream  ss ;
	for(int i= 0; i<vec_code.size(); i++)
	{
		ss.str("");
		char tmp[32];
		memset(tmp, 0 ,32);
		snprintf(tmp,32, "%06d", vec_code[i]);
		ss << string(tmp) << "," << vec_is_stock[i] << "," << vec_name[i] << "," ;

		memset(tmp, 0 ,32);
		snprintf(tmp,32, "%06d", vec_parent_code[i]);
		ss << string(tmp) << "<br>";

		/*unsigned char _des[512]={0};
		string strSrc = Gbk2Utf8(ss.str());
		memset(_des,0,512);
		EncryptData(_des, (unsigned char *)strSrc.c_str(), (unsigned char *)"ybcxfyrnyrz");*/

		vecContents.insert(vecContents.end(),  Gbk2Utf8(ss.str()));
	}
	return vecContents;
}

void CSelfSelectStockPlates::ImportToDatabase(void)
{
	//	�������������
	//m_pTree->DisplayTree(1);

	vector<CStockPlateData>  vec_stockplate;
	CStockPlateTree::pre_order_iterator pre_order_it = m_pTree->pre_order_begin();
	while(pre_order_it!=m_pTree->pre_order_end())
	{
		CStockPlateData spd = *pre_order_it;

		if(pre_order_it.node()->parent()->is_root()==false)
		{
			spd.parent_code = pre_order_it.node()->parent()->get()->code;
		}
		else
		{
			spd.parent_code = "-1";
		}
		vec_stockplate.push_back(spd);
		pre_order_it++;
	}

	if( vec_stockplate.size()<=0)
		return;

	stringstream ss;
	backend_factory const &backEnd = *soci::factory_mysql();

	try
	{
		ss << "SelfSelectStockPlates::ImportToDatabase ��ʼ��������.....\r\n";
		//sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);

		session sql(g_MysqlPool);

		// ɾ������ʱ���İ�����
		/*ss.str("");
		ss << "delete  from SelfSelectStockPlates where (Code, Parent_Code) not in( ";
		for (int row = 0; row < vec_stockplate.size(); row++)
		{
			ss << "(" << vec_stockplate[row].code << "," << vec_stockplate[row].parent_code << ")";
			if(row < vec_stockplate.size()-1)
				ss << ",";
		}
		ss << ")";
		string test1 = ss.str();
		sql << test1; 

		for (int row = 0; row < vec_stockplate.size(); row++)
		{
			ss.str("");
			ss << "insert into SelfSelectStockPlates "
				<< " select " <<  vec_stockplate[row].code << ", \'" 
				<< vec_stockplate[row].name << "\', "
				<< Int2String(vec_stockplate[row].company_number) << ", "
				<< vec_stockplate[row].parent_code << ", "
				<< Int2String(vec_stockplate[row].is_stock) << " "

				<< " from dual where not exists (SELECT 1 from SelfSelectStockPlates " 
				<< " where Parent_Code=" << vec_stockplate[row].parent_code << " " 
				<< " and Code=" << vec_stockplate[row].code << "  ) ";

			string test = ss.str();
			test = Gbk2Utf8(ss.str());
			sql << test; 

			ss.str("");
			ss << "update SelfSelectStockPlates "
				<< " set Code=" <<  vec_stockplate[row].code << ", Name=\'" 
				<< vec_stockplate[row].name << "\', Company_Number="
				<< Int2String(vec_stockplate[row].company_number)  
				<< ", Parent_Code="
				<< vec_stockplate[row].parent_code << ", Is_Stock="
				<< Int2String(vec_stockplate[row].is_stock) << " "

				<< " where Parent_Code=" << vec_stockplate[row].parent_code << " " 
				<< " and Code=" << vec_stockplate[row].code << "  ";

			test = Gbk2Utf8(ss.str());
			sql << test; 
		}*/


		//	ɾ��������ѡ���
		ss.str("");
		ss << "delete  from SelfSelectStockPlates  ";
		string test = ss.str();
		//string test = Gbk2Utf8(ss.str());
		sql << test; 

		// �������
		ss.str("");
		ss << "insert into SelfSelectStockPlates "
			<< " ( Code, Name, Company_Number, Parent_Code, Is_Stock ) "
			<< " values ";
		for (int row = 0; row < vec_stockplate.size(); row++)
		{
			ss	<< "( " << (vec_stockplate[row].code)  << " , \'" 
				<< vec_stockplate[row].name << "\', "
				<< vec_stockplate[row].company_number << ","
				<< vec_stockplate[row].parent_code << ", "
				<< vec_stockplate[row].is_stock << " )" ;

			if(row< vec_stockplate.size() - 1)
				ss << ",";
		}

		test = ss.str();
		//test = Gbk2Utf8(ss.str());
		sql << test; 

		ss.str("");
		ss << "�������� " <<  vec_stockplate.size() ;
		ss << " OK, CSelfSelectStockPlates::ImportToDatabase ���ݵ������. \r\n";
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
	catch (std::exception const & e)
	{
		ss.str("");
		ss << e.what() << '\r\n';
		sendToOutput(ss.str().c_str(), m_hWnd, m_nLogType);
	}
}
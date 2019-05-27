#include "InterfaceGlobal.h"


Logger g_InterfaceLogger=Logger::getInstance( LOG4CPLUS_TEXT("GWInterface") );


//********************************************************************
// function: �����ַ�������������ո����������
// parameter:src[in]-Դ�ַ������������ַ���
//           reg[in]-�ָ���
//           strFil[in]-������Ĭ��Ϊ"0"
// return:����õ��ַ���
//********************************************************************
list<string> splitStr(string src,string reg,string strFil="0")
{
	list<string> listStr;
	int nPos=0,nLen=0,nBegin=0;
	string strSub;
	nBegin = 0;
	while(nPos!=-1)
	{	
		nPos = src.find(reg,nBegin);
		nLen = nPos!=-1 ? nPos-nBegin : src.length()-nBegin;
		strSub.clear();
		strSub = src.substr(nBegin,nLen);
		if (strSub.length() != 0)//�ҵ����ַ���
		{
			listStr.push_back(strSub);
		}	 
		else//û�ҵ��ַ���
		{
			// 			if (nPos != -1)//����reg֮��û���ַ���
			// 			{
			listStr.push_back(strFil);
			//			}
		}
		nBegin = nPos+1;
	}
	return listStr;
}


//�������ļ�
bool ReadCfg()
{


	return true;
}

void splitString(string s, string dim, vector<string>& resultVector)
{
	string::size_type  position=0; 
	string::size_type  lastPosition=0;  
	while((position=s.find_first_of(dim, position))!=string::npos)  
	{  
		//position=s.find_first_of(flag,position);   
		string elem = s.substr(lastPosition,position-lastPosition);
		resultVector.push_back(elem);
		position++;
		lastPosition = position;
	}  
	string elem = s.substr(lastPosition);
	resultVector.push_back(elem);

}

//	ip �а���һ̨�����ϵĶ�� IP ��ַ������һ�����ӳɹ���������, �������Կ�ʹ�õ�·��
int MultiSocketTest(string ip, int port)
{
	SOCKET sk;
	SOCKADDR_IN saddr;
	fd_set r;
	//���ó�ʱʱ��
	unsigned long ul = 1;
	struct timeval timeo = {1, 0};

	sk=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//�����׽ӿ�
	if(sk==INVALID_SOCKET)
	{
		printf("Create scoket fail:%d\n",GetLastError());
		return -1;
	}
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(port);
	saddr.sin_addr.S_un.S_addr=inet_addr(ip.c_str());

	//���ӳ�ʱ�жϣ�����Լ����ܷ���
	//���÷�����
	if(ioctlsocket(sk, FIONBIO, (unsigned long*)&ul) == SOCKET_ERROR)
	{
		printf("ioctlsocket fail");
		closesocket(sk);
		return -1;
	}
	//��������
	if(connect(sk, (struct sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		FD_ZERO(&r);
		FD_SET(sk, &r);
		if(select(0,0,&r,0, &timeo) <= 0) //��Ҫע��select������һ��������winsock��������,��linux������sock+1;
		{
			printf("connect fail\n");
			closesocket(sk);
			return -1;
		}
	}
	closesocket(sk);
	return 1;
}
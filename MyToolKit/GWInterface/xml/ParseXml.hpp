#ifndef _PARSEXML_HPP
#define _PARSEXML_HPP
#include <string>
#include <list>
#include <map>
using namespace std;


// #define REQ_ID "REQUEST_ID"
// #define SESS_ID "SESSION_ID"

string GetXMLFieldValue(string strXML,string strName,char *cXmlNode);

/**********************************************
*��  �ܣ���ȡָ���ڵ����ĵ�һ���ڵ�
*��  ����strXML[in]--xml�ַ�����strName[in]--�ڵ���
*����ֵ��true--�ɹ���false--ʧ��
**********************************************/
bool FindFirstNode(string strXML,string strName="data");

/**********************************************
*��  �ܣ���ȡ��ǰ�ڵ����һ���ڵ�
*��  ����pCurNode[in]--��ǰ�ڵ�
*����ֵ��true--�ɹ���false--ʧ��
**********************************************/
bool FindNextNode1();

/**********************************************
*��  �ܣ���ȡ�ڵ���ض�����ֵ
*��  ����pCurNode[in]--��ǰ�ڵ�,strName[in]--�ڵ�������
*����ֵ������ֵ
**********************************************/
string GetXMLNodePropValue(string strName);

/**********************************************
*��  �ܣ���ȡ���нڵ�ĵ���������ֵ
*��  ����strXML[in]--��ǰ�ڵ�,lstString[in]--�ڵ������б�
*����ֵ����������ֵ
**********************************************/
bool GetXMLAllNodePropValues( string strXML,list<string> &lstString,list<map<string,string > > &lstPropMap );

#endif //_PARSEXML_HPP


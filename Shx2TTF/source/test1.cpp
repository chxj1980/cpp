// test1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ShapeFont.h"
#include "fontchrlink.h"
int _tmain(int argc, _TCHAR* argv[])
{
	ShapeFont* m_font = new ShapeFont();
	if(m_font->Load("ACADCHN6.SHX")){
		printf("�Ѵ�");
		printf("%i",m_font->Count());//�ֿ���������ַ�
		//��ʼ���·�� �� '��' ��
		CString str("��");
		//��� '��' �ֱ���
		char* kk=str.GetBuffer(0);
		wchar_t buf1[100];
		char key[8];
		MultiByteToWideChar(CP_OEMCP,0,str.GetBuffer(0),6,buf1,100);
		WideCharToMultiByte(932,0,buf1,3,key,6,NULL,NULL);
		unsigned short k1;
		memcpy(&k1,&kk[0],2);
		//���shx����·��
		string patch = m_font->Patch(k1,20,20,1,1);
		printf("%s",patch.c_str());
	}
	else{
		printf("�ֿ�򿪴���");
	}

	return 0;
}


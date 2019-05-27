// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// pcre2test.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

#include <iconv.h>


string Gbk2Utf8(string strGBK)
{
	string target;
	char*bufout, *sin, *sout;
	int lenin, lenout, ret;

	sin    = (char *)strGBK.c_str();
	lenin  = strlen(sin) + 1;
	lenout =lenin*10;

	bufout=(char *)calloc(lenout,sizeof(char));
	sout   = bufout;

	iconv_t c_pt=iconv_open("utf-8", "gbk");
	if (c_pt==(iconv_t)-1) return ("ConvertEnc iconv_open error");


	iconv(c_pt, NULL, NULL, NULL, NULL);
	ret = iconv(c_pt, (const char **)&sin, (size_t *)&lenin, &sout, (size_t *)&lenout);

	if (ret == -1) return ("ConvertEnc Convert Failed");

	iconv_close(c_pt);

	target = string(bufout);
	free(bufout);
	return target;
}



string Utf8_GBK(string strUtf8)
{
	string target;
	char*bufout, *sin, *sout;
	int lenin, lenout, ret;

	do{
		sin    = (char *)(strUtf8.c_str());
		lenin  = strlen(sin) + 1;
		lenout =lenin*3;

		bufout=(char *)calloc(lenout,sizeof(char));
		if (bufout==NULL) 
		{
			target = "ConvertEnc calloc Failed";
			break;
		}
		sout   = bufout;

		iconv_t c_pt=iconv_open("gbk//IGNORE", "utf-8");
		if (c_pt==(iconv_t)-1)
		{
			target = "ConvertEnc iconv_open error";
			break;
		}

		iconv(c_pt, NULL, NULL, NULL, NULL);
		ret = iconv(c_pt, (const char **)&sin, (size_t *)&lenin, &sout, (size_t *)&lenout);

		iconv_close(c_pt);

		if (ret == -1) 
			target = "ConvertEnc Convert Failed";
		else
			target = string(bufout);

	}while(0);

	if(bufout)
		free(bufout);
	return target;
}
//slc.h


/************************************************************************/
/* ���ܺ��� 
������
     Deststr�����ܵõ�������
     Sourcetr������
	 Keystr: ��Կ                                                       */
/************************************************************************/
extern "C" bool  EncryptData(unsigned char *Deststr,unsigned char *Sourcetr,unsigned char *Keystr);

/************************************************************************/
/* ���ܺ��� 
������
     Deststr�����ܵõ�������
     Sourcetr��������Ϣ
	 Keystr: ��Կ                                                       */
/************************************************************************/
extern "C" bool  DecryptData(unsigned char *Deststr,unsigned char *Sourcetr,unsigned char *Keystr);


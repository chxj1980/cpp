#pragma once


#pragma pack(push) //�������״̬
#pragma pack (1)     /*ָ����1�ֽڶ���*/

typedef struct
{
	int thread_id;		//���͵�thead IDר��
	int msg_len;
	char para[1];	//��Ϣ��������ͬ����Ϣ��Ӧ��ͬ����Ϣ����
} SN_MSG;

#pragma pack(pop)//�ָ�����״̬

class UsageEnvironment
{
public:
	UsageEnvironment(void);
	~UsageEnvironment(void);

	void SendMessageEx(int srcid,  int msgtype, void *data, int msg_len);

	static DWORD WINAPI MessageHandler1(void *data);

	virtual void MessageHandler(MSG * msg) = 0;

	

protected:
	DWORD m_ThreadId;
	HANDLE m_ThreadHandle;

	

public:
	//	�豸 uri �� �豸ע���ַ

	
	// a pointer to additional, optional, client-specific state
	void* liveMediaPriv;
	Logger  m_Logger;
};

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

#define  CATALOG_SESSION_NUM 1
#define  DEVICEINFO_SESSION_NUM 1
#define  STATUSINFO_SESSION_NUM 1

class UsageEnvironment
{
public:
	UsageEnvironment(void);
	~UsageEnvironment(void);

	void SendMessageEx(int srcid,  int msgtype, void *data, int msg_len);
	static DWORD WINAPI MessageHandler1(void *data);
	virtual void MessageHandler(MSG * msg){};

	bool PostCallBack(CCommandCallback * cb);
	static DWORD WINAPI CallbackHandler1(void *data);
	DWORD  CallbackHandler();

	//	�������Ļص�����
	bool PostDataCallBack(CCommandCallback * cb);
	static DWORD WINAPI DataCallbackHandler1(void *data);
	DWORD  DataCallbackHandler();

	int PostCommand(AbstractCommand * cmd);
	static DWORD WINAPI CommandHandler1(void *data);
	DWORD  CommandHandler();

	//	��Ӧ Superior
	int PostRequest(AbstractCommand * cmd);
	static DWORD WINAPI RequestHandler1(void *data);
	DWORD  RequestHandler();

	int	  fetchSerialNumber();
	void  MonitorSession();
	CAbstractObject * SearchSession(string sessionType, int nId);

	static UsageEnvironment& getInstance();

private:
	static UsageEnvironment * instance;

protected:
	static int g_SerialNumber;

	//	��Ӧ Junior ʹ�õ��߳�
	DWORD m_ThreadId;
	HANDLE m_ThreadHandle;

	DWORD m_ThreadId_Callback;
	HANDLE m_ThreadHandle_Callback;

	DWORD m_ThreadId_DataCallback;
	HANDLE m_ThreadHandle_DataCallback;

	//	��Ӧ Superior ʹ�õ��߳�
	DWORD m_ThreadId_request;
	HANDLE m_ThreadHandle_request;

	DWORD m_ThreadId_response;
	HANDLE m_ThreadHandle_response;

public:
	JMutex		m_mtxObjects;
	map<int, CAbstractObject *>	m_mapObjects;

	//	��Ӧ Superior
	JMutex		m_mtxRequest;
	vector<AbstractCommand *>   m_vecRequests;
	JMutex		m_mtxRequests;


	//	��Ӧ Junior 
	int m_nDeviceControlSession; 
	int m_nDeviceinfoSession;
	int m_nStateinfoSession;
	int m_nCataloginfoSession;
	int m_nSearchRecordfileSession;
	int m_nMediaSession;

	vector<AbstractCommand *>   m_vecCommandsCataloginfo;
	vector<AbstractCommand *>   m_vecCommandsDeviceinfo;
	vector<AbstractCommand *>   m_vecCommandsStateinfo;
	vector<AbstractCommand *>   m_vecCommands;
	JMutex		m_mtxCommands;

	vector<CCommandCallback *>   m_vecCallbacks;
	JMutex		m_mtxCallbacks;

	vector<CCommandCallback *>   m_vecDataCallbacks;
	JMutex		m_mtxDataCallbacks;

	
	
	// a pointer to additional, optional, client-specific state
	void* liveMediaPriv;
	Logger  m_Logger;

	SIPD_GATEWAY_CFG	m_cfg;

	int					m_iRtpPort;		//	���浱ǰ�Ѿ���ʹ�õ� ���˿�

	unsigned long  m_tvMonitorSession;
	unsigned long  m_tvMonitorSessionLog;

	map<int, int> m_mapDataInput;	//	���������ķ������ ����ͳ��
	map<int, int> m_mapDataOutput;	//	���������ķ������ ����ͳ��
};

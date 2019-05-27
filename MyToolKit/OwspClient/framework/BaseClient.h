
#ifndef _BASECLIENT_HH
#define _BASECLIENT_HH

class BaseClient : public Medium
{
public:
	BaseClient(UsageEnvironment& env, char const* strIPAddr, int nPort);

	~BaseClient(void);
	void Reclaim(void);

	void OnInitialize(CIOCPBuffer *pOverlapBuff);
	void OnRead(CIOCPBuffer *pOverlapBuff);
	void OnReadCompleted(DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);

	void OnWrite(DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);
	void OnWriteCompleted(DWORD dwIoSize,CIOCPBuffer *pOverlapBuff);

	/*virtual void OnZeroByteRead(CIOCPBuffer *pOverlapBuff)= 0;
	virtual void OnZeroByteReadCompleted(DWORD dwIoSize,CIOCPBuffer *pOverlapBuff) = 0;*/

	void Disconnect();

	static unsigned responseBufferSize;

protected:
	
	BOOL ASend( const unsigned char * buf, int len );
	BOOL ARead(CIOCPBuffer *pOverlapBuff=NULL);

	virtual void handleResponseBytes(int newBytesRead) = 0;
	virtual void handleConnected() = 0;		//	�����ӳɹ�ʱ
	virtual void handleDestoryed() = 0;		//	�����ӳ�ʱ���Է����ӶϿ��� �������� Client ��������

	int openConnection(); // -1: failure; 0: pending; 1: success
	int openConnection_Old();
	int connectToServer_Old(SOCKET	socketNum, int remotePortNum);
	int connectToServer(SOCKET	socketNum, int remotePortNum);
	void resetResponseBuffer();

	virtual string ClientClass(){  return string("BaseClient");  }

protected:
	SOCKET	m_Socket; // The Connection socket.

	unsigned char* fResponseBuffer;				//	������յ�������
	unsigned fResponseBytesAlreadySeen, fResponseBufferBytesLeft;

	string	fServerAddress;
	int		fServerPortNum;

private:
	friend class UsageEnvironment;
	int		m_nNumberOfPendlingIO;		// δ��ɵ� IO ������
	

	Boolean fIsActive;
	
};

#endif
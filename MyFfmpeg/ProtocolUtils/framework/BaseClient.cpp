
/*
	https://msdn.microsoft.com/en-us/library/windows/desktop/ms742203(v=vs.85).aspx
*/

#include "StdAfx.h"

#include "Medium.h"
#include "UsageEnvironment.h"
#include "BaseClient.h"

#include "mswsock.h"


unsigned BaseClient::responseBufferSize = 102400; // default value; you can reassign this in your application if you need to

BaseClient::BaseClient(UsageEnvironment& env, char const* strIPAddr, int nPort)
:Medium(env)
{

	stringstream ss;
	ss << " ���� " << ClientClass();
	CString str1(ss.str().c_str());
	envir().AppendLog(str1);

	m_nNumberOfPendlingIO = 0;
	m_Socket = INVALID_SOCKET;

	fServerPortNum = nPort;
	fServerAddress = string(strIPAddr);

	fIsActive = TRUE;

	fResponseBuffer = new unsigned char[responseBufferSize+1];
	resetResponseBuffer();
}

BaseClient::~BaseClient(void)
{

	stringstream ss;
	ss << " ~���� " << ClientClass();
	CString str1(ss.str().c_str());
	envir().AppendLog(str1);

	delete[] fResponseBuffer;
}

void BaseClient::Reclaim(void)
{
	Disconnect();
	handleDestoryed();
	Medium::close(this);
}



/*
* Makes An Asyncorn Send. 
*
*/
BOOL BaseClient::ASend( const unsigned char * buf, int len )
{
	if(m_Socket==INVALID_SOCKET)
		return FALSE;
	
	int left = len;
	int begin = 0;
	while(left>0)
	{
		CIOCPBuffer *pOverlapBuff = g_BufferMgr.AllocateBuffer(IOWrite);
		if(pOverlapBuff)
		{
			len = left>MAXIMUMPACKAGESIZE ? MAXIMUMPACKAGESIZE : left;

			if(pOverlapBuff->AddData(buf + begin, len)==FALSE)
			{
				g_BufferMgr.ReleaseBuffer(pOverlapBuff);
				return FALSE;
			}

			BOOL bSuccess = envir().PostQueuedCompletionStatus( this, pOverlapBuff);
			if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
			{            
				g_BufferMgr.ReleaseBuffer(pOverlapBuff);
				return FALSE;
			}
			
			CString msg;
			msg.Format(_T("BaseClient::ASend , len = %d, Used = %d "), len, pOverlapBuff->GetUsed());
			envir().AppendLog(msg);

			begin += len;
			left -= len;
		
		}
		else
		{
			return FALSE;
		}
	}
	return TRUE;
	
}


//	��������������ӳɹ�
void BaseClient::OnInitialize(CIOCPBuffer *pOverlapBuff)
{
	g_BufferMgr.ReleaseBuffer(pOverlapBuff);

	ARead();

	handleConnected();
}


/*
* Makes a asynchrony Read by posting a IORead message into completion port 
* who invoces a Onread.
*
* The read is not made directly to distribute CPU power fairly between the connections. 
*/

BOOL BaseClient::ARead(CIOCPBuffer *pOverlapBuff)
{

	if(m_Socket!=INVALID_SOCKET )
	{
		if(pOverlapBuff==NULL)
			pOverlapBuff= g_BufferMgr.AllocateBuffer(IORead);


		if(pOverlapBuff==NULL) 
		{			
			envir().AppendLog(_T("AllocateBuffer(IORead) == NULL."));
			return FALSE;
		}

		pOverlapBuff->SetOperation(IORead);
		BOOL bSuccess = envir().PostQueuedCompletionStatus( this, pOverlapBuff);  	
		if ( (!bSuccess && GetLastError( ) != ERROR_IO_PENDING))
		{            
			g_BufferMgr.ReleaseBuffer(pOverlapBuff);
			return FALSE;
		}
		return TRUE;
	}

	return FALSE;
}


void BaseClient::OnWrite(DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{

	if(m_Socket!=INVALID_SOCKET && pOverlapBuff)
	{
		CString msg;
		msg.Format(_T(" BaseClient::OnWrite , dwIoSize = %d, Used = %d"), dwIoSize, pOverlapBuff->GetUsed());
		envir().AppendLog(msg);

		pOverlapBuff->SetOperation(IOWriteCompleted);
		pOverlapBuff->SetupWrite();		//	���� m_wsabuf ���÷��͵�׼��
		ULONG ulFlags = 0;				//	MSG_PARTIAL;
		DWORD dwSendNumBytes = 0;

		int nRetVal = WSASend(m_Socket, 
			pOverlapBuff->GetWSABuffer(),
			1,
			NULL,	//	&dwSendNumBytes, 
			ulFlags,
			&pOverlapBuff->m_ol, 
			NULL);

		if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING ) 
		{
			if(WSAGetLastError()!=WSAENOTSOCK)
			{

				// Remove Unnecessary disconnect messages in release mode.. 
				if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)

				{	
					CString msg;
					msg.Format(_T("Error in OnWrite..: %s"),envir().ErrorCode2Text(WSAGetLastError()));
					envir().AppendLog(msg);
				}
			}
			Disconnect();
			g_BufferMgr.ReleaseBuffer(pOverlapBuff);
		}
		else if(nRetVal == SOCKET_ERROR)
		{
			CString msg;
			msg.Format(_T("���ͱ��Ƴ� in OnWrite..: %s"),envir().ErrorCode2Text(WSAGetLastError()));
			envir().AppendLog(msg);
		}
		else
		{
			//	�첽�������ݳɹ�
			CString msg;
			msg.Format(_T("���ͳɹ� in OnWrite..: ������ %d �ֽ�"), dwSendNumBytes);
			envir().AppendLog(msg);
		}
	}
	
}



void BaseClient::OnWriteCompleted( DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{
	if (pOverlapBuff!=NULL)
	{
		if(pOverlapBuff->GetUsed()!=dwIoSize)
		{
			CString msg;
			msg.Format(_T("The whole message was not Sent.: %s"),envir().ErrorCode2Text(WSAGetLastError()));
			envir().AppendLog(msg);
		}
		else
		{
			
		}
		//	������ɺ󣬻��ջ���

		CString msg;
		msg.Format(_T(" BaseClient::OnWriteCompleted, ������ɺ󣬻��ջ��棬dwIoSize = %d , Used = %d"), dwIoSize, \
			pOverlapBuff->GetUsed());
		envir().AppendLog(msg);

		g_BufferMgr.ReleaseBuffer(pOverlapBuff);
	}
}



void BaseClient::OnRead(CIOCPBuffer *pOverlapBuff)
{
	// issue a read request 
	if(m_Socket!=INVALID_SOCKET && pOverlapBuff)
	{
		pOverlapBuff->SetOperation(IOReadCompleted);
		pOverlapBuff->SetupRead();

		DWORD dwIoSize=0;
		ULONG	ulFlags = MSG_PARTIAL;
		UINT nRetVal = WSARecv(m_Socket, 
			pOverlapBuff->GetWSABuffer(),
			1,
			&dwIoSize, 
			&ulFlags,
			&pOverlapBuff->m_ol, 
			NULL);
		if ( nRetVal == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING) 
		{
			if(WSAGetLastError()!=WSAENOTSOCK)
			{

				// Remove Unnecessary disconnect messages in release mode.. 
				if(WSAGetLastError()!=WSAECONNRESET&&WSAGetLastError()!=WSAECONNABORTED)
				{
					CString msg;
					msg.Format(_T("Disconnect in Onread Possible Socket Error: %s"),envir().ErrorCode2Text(WSAGetLastError()));
					envir().AppendLog(msg);
				}
			}
			g_BufferMgr.ReleaseBuffer(pOverlapBuff);
			
			Disconnect();
		}
	}
}



void BaseClient::OnReadCompleted(DWORD dwIoSize,CIOCPBuffer *pOverlapBuff)
{

	if (dwIoSize == 0|| pOverlapBuff==NULL)
	{
		CString msg;
		msg.Format(_T("Disconnection in OnReadCompleted (dwIoSize == 0||pOverlapBuff==NULL) errcode: %s"),
			envir().ErrorCode2Text(WSAGetLastError()));
		envir().AppendLog(msg);
		Disconnect();
		g_BufferMgr.ReleaseBuffer(pOverlapBuff);
		return;
	}

	while(fIsActive)
	{
		if(dwIoSize <= fResponseBufferBytesLeft)
		{
			memmove(&fResponseBuffer[fResponseBytesAlreadySeen], pOverlapBuff->GetBuffer(),dwIoSize);
			fResponseBufferBytesLeft -= dwIoSize;
			fResponseBytesAlreadySeen += dwIoSize;
			handleResponseBytes(dwIoSize);
			
			break;
		}
		else
		{
			int newBytes = fResponseBufferBytesLeft;
			memmove(&fResponseBuffer[fResponseBytesAlreadySeen], pOverlapBuff->GetBuffer(),newBytes);
			fResponseBufferBytesLeft -= newBytes;
			fResponseBytesAlreadySeen += newBytes;
			handleResponseBytes(newBytes);
			dwIoSize = dwIoSize - newBytes;
		}

	}
	if(fIsActive)
	{
		if(ARead(pOverlapBuff))
		{
			//envir().AppendLog("���� Aread �ɹ�");
		}
		else
			envir().AppendLog(_T("���� Aread ʧ��"));
	}
	else
		g_BufferMgr.ReleaseBuffer(pOverlapBuff);

}


int BaseClient::connectToServer_Old(SOCKET	socketNum, int remotePortNum) 
{
	SOCKADDR_IN	SockAddr;
	int			nRet=-1;

	// Clear the SockAddr. 
	memset(&SockAddr,0,sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = inet_addr(fServerAddress.c_str());
	SockAddr.sin_port = htons(remotePortNum);
	nRet = connect(socketNum,(sockaddr*)&SockAddr, sizeof(SockAddr));

	if (nRet == SOCKET_ERROR)
	{
		if( WSAGetLastError() != WSAEWOULDBLOCK)
		{
			CString msg;
			msg.Format(_T("Connection Error: %s"),envir().ErrorCode2Text(WSAGetLastError()));
			envir().AppendLog(msg);
			return -1;
		}
		else
		{
			CString msg;
			msg.Format(_T("Connection Error: %s"),envir().ErrorCode2Text(WSAGetLastError()));
			envir().AppendLog(msg);

			return 1;		//	return 0 ԭ����Ҫ�ȴ� ���ӳɹ�
		}
	}
	else
	{
		return 1;
		
	}
}


int BaseClient::connectToServer(SOCKET	socketNum, int remotePortNum) 
{
	int			nRet=-1;
	
	CIOCPBuffer * pOverlapBuff= g_BufferMgr.AllocateBuffer(IOInitialize);
	if(pOverlapBuff==NULL) 
	{			
		envir().AppendLog(_T("AllocateBuffer(IOConnect) == NULL."));
		return -1;
	}

	//   �ص�  
	LPFN_CONNECTEX lpfnConnectEx = NULL ; 
	DWORD dwBytes = 0; 
	GUID GuidConnectEx = WSAID_CONNECTEX ; 

	//   �ص㣬���ConnectEx ������ָ��
	if (SOCKET_ERROR == WSAIoctl (socketNum , SIO_GET_EXTENSION_FUNCTION_POINTER , 
		&GuidConnectEx , sizeof (GuidConnectEx ), 
		&lpfnConnectEx , sizeof (lpfnConnectEx ), &dwBytes , 0, 0)) 
	{ 
		//TRACE ( "WSAIoctl is failed. Error code = %d" , WSAGetLastError ()); 
		return -1 ; 
	} 

	//   ��������Ŀ���ַ  
	SOCKADDR_IN	SockAddr;
	memset(&SockAddr,0,sizeof(SockAddr));
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = inet_addr(fServerAddress.c_str());
	SockAddr.sin_port = htons(remotePortNum);
	
	int nLen = sizeof (SockAddr ); 
	DWORD dwBytesSent = 0; 

	BOOL bResult = lpfnConnectEx(socketNum , 
		(sockaddr *)&SockAddr ,				// [in]   �Է���ַ 
		nLen ,								// [in]   �Է���ַ���� 
		NULL ,								// [in]   ���Ӻ�Ҫ���͵����ݣ����ﲻ�� 
		0 ,									// [in]   �������ݵ��ֽ��� �����ﲻ�� 
		&dwBytesSent ,						// [out]   �����˶��ٸ��ֽڣ����ﲻ��  
		(OVERLAPPED *)&pOverlapBuff->m_ol ); // [in]   �ⶫ�����ӣ���һƪ����� 

	if (!bResult )      //   ����ֵ���� 
	{ 
		if ( WSAGetLastError () != ERROR_IO_PENDING )   //   ����ʧ��  
		{ 
			envir().AppendLog(_T("ConnextEx error "));
			return -1 ; 
		} 
		else //  ����δ�������ڽ����� �� )
		{ 
			return 0;
		} 
	} 

	return 1;
}

int BaseClient::openConnection()
{
	do{
		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_Socket == INVALID_SOCKET) break;

		//  ���µİ󶨺���Ҫ��Ҳ������©���ġ���������˰󶨣��� ConnextEx  ʱ���õ�������룺10022  �� �ṩ��һ����Ч�Ĳ��� 
		sockaddr_in local_addr ; 
		ZeroMemory (&local_addr , sizeof (sockaddr_in )); 
		local_addr .sin_family = AF_INET ; 
		int irt = ::bind (m_Socket , (sockaddr *)(&local_addr ), sizeof (sockaddr_in )); 


		//  �� Socket ������ IOCP 
		if (!envir().AssociateClientWithCompletionPort(this))
		{
			CString msg;
			msg.Format(_T("AssociateClientWithCompletionPort Failed: %s"),envir().ErrorCode2Text(WSAGetLastError()));
			envir().AppendLog(msg);

			break;
		}

		int connectResult = connectToServer(m_Socket, fServerPortNum);
		if (connectResult < 0) break;
		
		return connectResult;

	}while(0);

	::closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
	return -1;
}


int BaseClient::openConnection_Old()
{
	do{
		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_Socket == INVALID_SOCKET) break;

		const char chOpt = 1;
		int nErr = setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(char));
		if (nErr == -1)
		{
			CString msg;
			msg.Format(_T("setsockopt() error: %s"),envir().ErrorCode2Text(WSAGetLastError()));
			envir().AppendLog(msg);
			break;
		}

		int connectResult = connectToServer(m_Socket, fServerPortNum);
		if (connectResult < 0) break;
		else if (connectResult > 0) {
			// The connection succeeded.  Arrange to handle responses to requests sent on it:

			if (!envir().AssociateClientWithCompletionPort(this))
			{
				CString msg;
				msg.Format(_T("AssociateClientWithCompletionPort Failed: %s"),envir().ErrorCode2Text(WSAGetLastError()));
				envir().AppendLog(msg);
				
				break;
			}

						
			//	˵�����ӳɹ������� ������
			CIOCPBuffer *pOverlapBuff = g_BufferMgr.AllocateBuffer(IOInitialize);
			envir().PostQueuedCompletionStatus(this, pOverlapBuff);

		}
		return connectResult;

	}while(0);

	::closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
	return -1;
}


void BaseClient::resetResponseBuffer() 
{
	fResponseBytesAlreadySeen = 0;
	fResponseBufferBytesLeft = responseBufferSize;
}

void BaseClient::Disconnect()
{
	if(m_Socket!=INVALID_SOCKET)
	{
		::CancelIo((HANDLE)m_Socket);
		::closesocket(m_Socket );
		m_Socket = INVALID_SOCKET;
	}

}
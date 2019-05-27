
#include "stdafx.h"
#include "Lottery.h"
#include "LottoMxn.h"

UINT AutoDownloadThreadFunc(LPVOID param)
{
	CDownloadRequest * pStock  = (CDownloadRequest *)param; 
	pStock->m_strResult = "NoMoreData";

	//	����Ҫ���صı������
	vector<CLotteryDataModel *> vecStockModel;

	vector<LotteryInfo>	vecInfo = ((CLotteryApp *)AfxGetApp())->m_vec_lottery_info;

	//AcquireReadLock(&g_RWlock);
	{
		//	��ƱƱ��������
		for(int i=0; i< vecInfo.size(); i++)
		{
			CLottoMxn * mxn = new CLottoMxn;
			mxn->m_lottery_name = vecInfo[i].name;
			mxn->m_lottery_code = vecInfo[i].code;
			mxn->m_regular_num = vecInfo[i].regularnum;
			mxn->m_special_num = vecInfo[i].specialnum;

			mxn->m_hWnd = pStock->m_hwnd;
			mxn->m_nLogType = pStock->m_nLogType;
			vecStockModel.push_back(mxn);
		}
		
	}
	//ReleaseReadLock(&g_RWlock);


	CString strOutput;  
	int	nTry = 0;
	while( vecStockModel.size()>0 && ((CLotteryApp *)AfxGetApp())->TestRequestExit()==FALSE)
	{
		// ͨ��������Ϣ�� AutoDownloadView�� �����ж��Ƿ���ͼ�Ѿ����رգ��ر����˳��߳�
		int nRemains = vecStockModel.size();
		CString strBegin;
		strBegin.Format("�������� %s, ���� %d �� \r\n", 
			vecStockModel[0]->ModelType().c_str(), nRemains);
		strOutput = strBegin;


		/*if(nRemains%10 == 1 && sendToOutput(strOutput, pStock->m_hwnd, pStock->m_nLogType)==FALSE)
		{
			break;
		}*/


		//	���ڶ������ʧ�ܵ�����ȡ��
		if(nTry>=3)
		{
			delete vecStockModel[0];
			vecStockModel.erase(vecStockModel.begin());
			nTry = 0;
			continue;
		}
		nTry ++;
		if(nTry>1)
			Sleep(100);

		string downloadUrl = vecStockModel[0]->GetDownloadUrl();
		if(downloadUrl.empty()==false && ((CLotteryApp *)AfxGetApp())->TestRequestExit()==FALSE)
		{
			//////////////////////////////////////////////////////////////////////////
			//	�����ܵ��������� wget.exe ����ͨ��
			SECURITY_ATTRIBUTES sa;    
			HANDLE hRead,hWrite;    

			sa.nLength = sizeof(SECURITY_ATTRIBUTES);    
			sa.lpSecurityDescriptor = NULL;    
			sa.bInheritHandle = TRUE;    
			if(!CreatePipe(&hRead,&hWrite,&sa,0))    
			{     
				AfxMessageBox("CreatePipe Failed");    
				break;    
			}    

			//////////////////////////////////////////////////////////////////////////
			//	���� wget.exe ���̣���ʼ��������
			STARTUPINFO si;     
			PROCESS_INFORMATION pi;    
			ZeroMemory(&si,sizeof(STARTUPINFO));    
			si.cb = sizeof(STARTUPINFO);    
			GetStartupInfo(&si);     
			si.hStdError = hWrite;    
			si.hStdOutput = hWrite;    
			si.wShowWindow = SW_HIDE;     
			si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;    



			if(!CreateProcess(NULL,(LPSTR)downloadUrl.c_str(),NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))    
			{     
				AfxMessageBox("CreateProcess failed!");    
				break;    
			}     

			HANDLE hThreads[2];
			hThreads[0]=pi.hProcess;
			hThreads[1]=((CLotteryApp *)AfxGetApp())->m_bAppExit;
			//WaitForSingleObject( pi.hProcess, INFINITE );

			bool bAppExit = false;
			int  nTimeoutNum = 0;
			while(1)
			{
				DWORD wfm = WaitForMultipleObjects(2, hThreads, FALSE, 1000 /*INFINITE*/);
				if(wfm==WAIT_OBJECT_0 + 1)
				{
					// �������˳�
					bAppExit = true;
					break;
				}
				else if(wfm == WAIT_TIMEOUT)
				{
					nTimeoutNum ++;
					/*��ʱ�����жϳ��� 10 �룬��ֹ wget.exe ����*/
					if(nTimeoutNum>=10)
					{
						TerminateProcess(pi.hProcess,0);
						break;
					}
				}
				else 
				{
					/*wget.exe ������Ϻ���ֹ*/
					break;
				}
			}
			if(bAppExit)
				break;

			CloseHandle(pi.hProcess);

			CloseHandle(hWrite);    

			//////////////////////////////////////////////////////////////////////////
			//	��� wget.exe �����

			char buffer[4096] = {0};    
			DWORD bytesRead;    

			while(1)    
			{     
				if(NULL == ReadFile(hRead,buffer,4095,&bytesRead,NULL))     
				{     
					break;    
				}     

				//strOutput += buffer;     
				strOutput = buffer;    
				sendToOutput(strOutput, pStock->m_hwnd,  pStock->m_nLogType);
				Sleep(500);    
			}    
			CloseHandle(hRead);    

		}

		//////////////////////////////////////////////////////////////////////////
		//	ת�� CSV �ļ�
		string strCsvFile = vecStockModel[0]->SaveAsCsv();
		if(strCsvFile.empty()==false &&((CLotteryApp *)AfxGetApp())->TestRequestExit()==FALSE)
		{
			if(strCsvFile=="NoMoreData")
			{
				// ��ǰ���ݿ�����Ϊ��������

				//	���͡����ݿ⵼��ɹ���֪ͨ
				vecStockModel[0]->NotifyDatabaseImportedToWindow();

				//	ɾ���Ѿ��ɹ�������
				delete vecStockModel[0];
				vecStockModel.erase(vecStockModel.begin());
				nTry = 0;

				Sleep(100);
			}
			else if(strCsvFile=="AlreadyInMemory")
			{
				vecStockModel[0]->ImportToDatabase();

				//	���͡����ݿ⵼��ɹ���֪ͨ
				vecStockModel[0]->NotifyDatabaseImportedToWindow();

				//	ɾ���Ѿ��ɹ�������
				delete vecStockModel[0];
				vecStockModel.erase(vecStockModel.begin());
				nTry = 0;

				pStock->m_strResult = "NewData";
			}
			else
			{
				
			}
		}

		Sleep(20);
	}

	for(int m=0; m< vecStockModel.size(); m++)
	{
		if(vecStockModel[m])
			delete vecStockModel[m];
	}


	{
		//	֪ͨ�����Դ���ڣ��������
		stringstream ss;
		ss << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>";
		ss << "<root>";
		ss << "<msg_type>DownloadFinished</msg_type>";
		ss << "<data param1=\"" << pStock->m_nDownloadType << "\" " ;
		ss << " param2=\"" << pStock->m_strResult << "\" >";
		ss << "</data></root>";

		//sendToOutput(ss.str().c_str(), pStock->m_hwnd);
	}

	int nDownType = pStock->m_nDownloadType;
	delete pStock;

	return 0;
}

#include "StdAfx.h"
#include "Lottery.h"
#include "CalculateTask.h"

//	����ȫ��Ψһ�������ʶ
LONG g_nTaskID;

//	�������Ĺ���
JMutex g_mtxListTask;
map<LONG, CCalculateTask *> g_mapTask;

//	���������б�
JMutex g_mtxListTaskRequest;
list<CCalculateTask *> g_listTaskRequest;


CCalculateTask::CCalculateTask(HWND hwnd, int logType)
{
	m_nTaskID = InterlockedIncrement(&g_nTaskID);
	m_hWnd = hwnd;
	m_nLogType = logType;

	m_windowInMatlab = -1;
	m_StartDate = -1.0;
	m_EndDate = -1.0;

	{
		JMutexAutoLock lock(g_mtxListTask);
		g_mapTask.insert(make_pair(m_nTaskID, this));
	}

	stringstream ss;
	ss.str("");
	ss << "����" << m_nTaskID << "�� ������Ͷ�� OK " << " \r\n";
	sendToOutput(ss.str().c_str(), NULL, m_nLogType);
}

CCalculateTask::~CCalculateTask(void)
{
	JMutexAutoLock lock(g_mtxListTask);
	map<LONG, CCalculateTask *>::iterator it = g_mapTask.find(m_nTaskID);
	if(it!=g_mapTask.end())
		g_mapTask.erase(it);
	
}


void CCalculateTask::ScheduleTask(CalculateTaskFunc * proc)
{
	JMutexAutoLock lock(g_mtxListTaskRequest);
	m_proc = proc;
	g_listTaskRequest.push_back(this);

}

void CCalculateTask::NotifyTaskFinished()
{
	//	֪ͨ�����Դ���ڣ��������
	stringstream ss;
	ss << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>";
	ss << "<root>";
	ss << "<msg_type ";
	ss << " model=\"" << ClassName() << "\" ";
	ss << ">TaskFinished</msg_type>";
	ss << "<data param1=\"" << m_nTaskID << "\" >";
	ss << "</data></root>";

	sendToOutput(ss.str().c_str(), m_hWnd);
}

CCalculateTask * CCalculateTask::FetchTask(LONG taskID)
{
	JMutexAutoLock lock(g_mtxListTask);
	map<LONG, CCalculateTask *>::iterator it = g_mapTask.find(taskID);
	if(it!=g_mapTask.end())
	{
		return (it->second);
	}
	return NULL;
}

void CCalculateTask::init()
{
	if(g_mtxListTask.IsInitialized()==false)
		g_mtxListTask.Init();
	if(g_mtxListTaskRequest.IsInitialized()==false)
		g_mtxListTaskRequest.Init();

	//	��������ִ���߳�
	((CLotteryApp *)AfxGetApp())->StartWorkerThread(CCalculateTask::CalculateThreadFunc,(LPVOID)NULL);

	((CLotteryApp *)AfxGetApp())->StartWorkerThread(CCalculateTask::CalculateThreadFunc,(LPVOID)NULL);

	((CLotteryApp *)AfxGetApp())->StartWorkerThread(CCalculateTask::CalculateThreadFunc,(LPVOID)NULL);
	
	

}

void CCalculateTask::unInit()
{
	JMutexAutoLock lock(g_mtxListTask);
	while(g_mapTask.size()>0)
	{
		map<LONG, CCalculateTask *>::iterator it = g_mapTask.begin();
		CCalculateTask * ct = it->second;
		delete ct;
		g_mapTask.erase(it);
	}
}


UINT CCalculateTask::CalculateThreadFunc(LPVOID param)
{
	CLotteryApp * pApp = (CLotteryApp *)AfxGetApp();
	while(pApp->TestRequestExit()==FALSE)
	{
		//	�����������ȡ������ִ��
		CCalculateTask * req = NULL;
		{
			JMutexAutoLock lock(g_mtxListTaskRequest);
			if(g_listTaskRequest.size()>0)
			{
				req = *g_listTaskRequest.begin();
				g_listTaskRequest.erase(g_listTaskRequest.begin());
			}
		}

		if(req==NULL)
		{
			Sleep(300);
			continue;
		}

		if(req->m_proc!=NULL)
		{
			req->m_proc(req);
			req->NotifyTaskFinished();
		}
		
	}
	return 0;
}

void CCalculateTask::AddPoint(string strZbCode, string strZbName, string strSjCode, string strUnit, double dbData,double dbData1,double dbData2,double dbData3)
{
	sj_code.insert(sj_code.end(), strSjCode);
	zb_code.insert(zb_code.end(), strZbCode);

	zb_name.insert(zb_name.end(), strZbName);
	data.insert(data.end(), dbData);
	unit.insert(unit.end(), strUnit);

	data1.insert(data1.end(), dbData1);
	data2.insert(data2.end(), dbData2);
	data3.insert(data3.end(), dbData3);
}


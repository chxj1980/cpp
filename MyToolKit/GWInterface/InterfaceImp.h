#ifndef _INTERFACE_IMP_HPP
#define _INTERFACE_IMP_HPP

#include "StandardInc.hpp"
#include "GWInterfaceDef.h"
#include "./thread/jmutexautolock.h"

#include "./ThreadPool/tasks.h"
#include "./ThreadPool/Worker.h"
#include "./jms/JMSNotify.h"
#include "./xml/xmlClient.hpp"
#include "./db/DBOperator.h"



#define MAX_QUERY_POOL 50
#define MAX_CONTROL_POOL 50
#define HEART_TIME	10000 //10s

typedef enum TASK_TYPE{TASK_PTZ,TASK_QUERY_RECORD,TASK_QUERY_DEVICE,TASK_QUERY_DEV_CATA,TASK_QUERY_DEV_STATE,TASK_ALARM_CONTROL,TASK_RECORD_CONTROL};

typedef struct _LocalCfg
{
	string strWebIP;
	string strDBIP;
	string strMediaServerIP;
	string strGateway;
	int nDBPort;
	int nWebPort;
	int nMediaServerPort;

	_LocalCfg()
	{
		strWebIP = "";
		strDBIP = "";
		strGateway = "";
		nDBPort = 0;
		nWebPort = 0;
	}
}LocalCfg,*LPLocalCfg;

typedef struct _TaskInfo
{
	LPVOID lparam;
	int nTaskType;
	void *param1;
	//void *param2;
	_TaskInfo()
	{
		lparam = NULL;
		nTaskType = 0;
		param1 = NULL;
		//param2 = NULL;
	}
}TaskInfo,*LPTaskInfo;

typedef struct _MediaRequestInfo
{
	sipd_media_session sipMediaSeesion;
	int nMediaRequestType;
	char npt[128];
	char cSpeed[8];
	char cPause[64];
	_MediaRequestInfo()
	{
		memset(&sipMediaSeesion,0,sizeof(sipd_media_session));
		nMediaRequestType = 0;
		memset(npt,0,sizeof(npt));
		memset(cSpeed,0,sizeof(cSpeed));
	}
}MediaRequestInfo,*LPMediaRequestInfo;



class InterfaceImp
{
	
public:
	~InterfaceImp();
	InterfaceImp();
	int Init();
	int Start();
	int ReadCfg();
	int StartConnectCMS();
	int StartConnectMediaSever();
	void ProcCMSNotify(char *cMessage);
	void ProcMediaServerMessage(char *cMessage);
	bool CheckDeviceRight();
	void SetDeviceRight(string strDeviceID,int nDeviceRight);
	void AddTask(LPTaskInfo pTaskInfo,int nTaskType);//nTaskType 0:��ѯ 1:����
	int GetAllDevice();
	int GetAllDevicePos();
	int GetGWCfg();
	int GetUserID();
	int GetServerInfo();
	void DoTask(void *param);
	int QueryRecord(sipd_recordinfo_req * pRecordFileReq);
	int QuerySingleRecord(SN_DEVICE snDevice,ServerInfo VODServer,char *cRecordStartTime,char *cRecordEndTime,list<RecordInfo>&RecordTimeLst);


	int InvitePlay(sipd_media_session* pMediaInfo);
	/*******************���ûص�����**********************/
	int SetServerConfigCB(sip_config_pcb_func config_fun);
	int SetAlarmIndCB(sip_alarm_ind_pcb_func config_fun);
	int SetControlRspCB(sip_control_req_pcb_func config_fun);
	int SetInfoRspCB(sip_info_req_pcb_func config_fun);
	int SetMediaControlCB(sip_media_pcb_func config_fun);

	int RecordControl(sipd_record_control * pRecordControl);

	void ProcJMSNotify(char *cMessage);

	int GetDevPos(int nGetType,char *DevPosID,char *Devpos);

	int setSipServerCfg(SIPD_GATEWAY_CFG* pCfg);

	int PTZControl(void *PTZCmd,int nPTZtype);

	int RequestDeviceInfo(sipd_deviceinfo_req * pDeviceinfoReq);

	int RequestDeviceState(sipd_devicestate_req * pStateInfoReq);

	int RequestDevCataloginfo(sipd_catalog_req * pCatalogReq);

	int RequestSetDevAlarmStatus(sipd_alarm_control * pAlarmControl);

	int RequestSipCfg();

	int parseSipCfgMessage(char *cMessage);

	int RequestMedia(int nType);//1:�������� 2:�������

	int SendMediaRequest(MediaRequestInfo MediaSession);
	
	int SendMediaSetupRequest(sipd_media_session MediaSession);

	int SendMediaPlayRequest(sipd_media_session MediaSession);

	int SendMediaControlRequest(MediaRequestInfo MediaSession);

	int SendMediaStopRequest(MediaRequestInfo MediaSession);

	int SendMediaRebootRequest();

	int AddMediaRequest(int did, int tid,int nRequestType,sipd_media_session* pMediaInfo,char *pRtspInfo);

	void SipCfgChangeNotify(SIPD_GATEWAY_CFG new_cfg);

	int RebootDevice(sipd_id_info * pIdInfo);

	int RebootDeviceImp(ServerInfo DMSServer,SN_DEVICE SnDevice);

	int QueryDevAlarmStatus(ServerInfo DMSServer,SN_DEVICE SnDevice,int &nAlarmStatus);

	int GetDevChannel(string strDevGBID,list<SN_DEVICE>&SnDevice,int nType,list<SN_DEVICE>&SnUperDev);

	int GetParentDev(string strDevGBID,list<SN_DEVICE>&SnDevice,list<SN_DEVICE>&SnUperDev);

	int SendPTZControlRequest(LPPTZControlInfo pPTZControlInfo);

	int re_cms_logon(string strSourceIP,ServerInfo &cmsInfo,LPThreadInfo pThreadInfo,bool bFirst=false);
	

public:
	ServerInfo m_CMSServer; //cms server��Ϣ
	ServerInfo m_DMSServer; //dms server��Ϣ
	ServerInfo m_VODServer;
	ServerInfo m_mediaServer;
	LocalCfg m_LocalCfg;//����������Ϣ
	sipd_servercfg_config_ind m_SipServerCfg; //sip������Ϣ
	string m_strLocalIP;
	ThreadInfo m_cmsThread;
	ThreadInfo m_MediaServerProcThread;

	//JMS
	JMSConsumer *m_pJMSConsumer; //JMS����
	JMSProducer *m_pJMSProducer; //JMS����
	

	map<string,SN_DEVICE> m_DeviceMap; //�豸�б� key=GBID
	JMutex m_DeviceMapMutex;

	map<string,SN_Position> m_DevicePosMap; //�豸λ���б� key=posid
	JMutex m_DevicePosMapMutex;

	map<string,DeviceRight> m_DeviceRightMap;
	JMutex m_DeviceRightMapMutex;

	list<PTZControlInfo> m_PTZControlLst; //PTZ�����б�
	JMutex m_PTZControlLstMutex;

	CThreadPool<CMyWorker> m_QueryThreadPool; //��ѯ�̳߳�
	JMutex m_QueryThreadPoolMutex;

	CThreadPool<CMyWorker> m_ControlThreadPool; //��������̳߳�
	JMutex m_ControlThreadPoolMutex;

	map<int,sipd_media_session> m_MediaSeesionMap;
	list<MediaRequestInfo> m_MediaRequestLst;
	JMutex m_MediaSeesionMapMutex;

	int m_ReadSipCfgStep;

	/*******************�ص�����**********************/
	sip_config_pcb_func m_pConfigCB; //������Ϣ���֪ͨ�ص�����
	sip_alarm_ind_pcb_func m_pAlarmCB;	//����֪ͨ�ص�����
	sip_control_req_pcb_func m_pControlReqCB; //���Ʒ���֪ͨ�ص�����
	sip_info_req_pcb_func m_pInfoReqCB; //�����֪ͨ�ص�����
	sip_media_pcb_func m_pMediaCB; //ý�彻��֪ͨ�ص�����



};

extern InterfaceImp *g_pInterfaceImp;
DWORD WINAPI CMSProc(LPVOID lparam);
void WorkerProc(LPVOID lpparam);
void JMSNotifyProc(LPVOID lpparam,char *cMessage);
DWORD WINAPI MediaServerProc(LPVOID lparam);
void JMSQueryNotifyProc(LPVOID lpparam,char *cMessage);
#endif
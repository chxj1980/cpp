#ifndef _DB_OPERATOR_HPP
#define _DB_OPERATOR_HPP

#include "./StandardInc.hpp"
#include "../GWInterfaceDef.h"

#define CMS_SERVER_ID	"1"
#define DMS_SERVER_ID	"3"
#define VOD_SERVER_ID	"9"



typedef struct  _SnDevice
{
	string	strDevId;		// dvr �� nvr �� ipc ���豸ID
	string   strParentDevId;
	string  strGBID;	//����ID
	string	strDevName;
	string	strDevIP;
	string	strDevUser;
	string	strDevPass;
	string  strConnectType;
	string  strInstallTime;
	string  strPosID;
	int		nDevState;
	int		nChannelCnt;
	int		nAlarmInIOCnt;
	int		nAlarmOutCnt;
	int		nDevPort;
	int		nDevTypeId; //1:�����豸 2:�����豸
	int		nDevFirm;	//�豸����
	int		nDevChannelNum;	//	dvr ���� ipc �豸��ͨ����

	string	strDevFirm;
	string	strDevSN;
	int	nDevTypeChild;	// �������� sn_device 1:DVR 2:IPC 3:NVR	
	int		nVideoPort;		//	���� sn_video_dvr
	int		nMobilePort;	// ���� sn_video_dvr
	int     nWebPort;		//	���� sn_video_dvr
	int		nChannelNO; //ͨ����
	int		nMode;	//Э�� 4:onvif
	_SnDevice()
	{
		strDevId = "";
		strParentDevId = "";
		strGBID = "";
		strDevName = "";
		strDevIP = "";
		strDevUser = "";
		strDevPass = "";
		nDevPort = 0;
		nDevTypeId = 0;
		nDevChannelNum = 0;
		strDevFirm = "";
		
		strDevSN = "";
		strConnectType = "";
		strInstallTime = "";
		strPosID = "";
		nVideoPort = 0;
		nMobilePort = 0;
		nWebPort = 0;
		nChannelNO = 0;
		nChannelCnt = 0;
		nAlarmInIOCnt = 0;
		nAlarmOutCnt=0;
		nDevFirm = 0;
		nDevTypeChild = 0;
	}
}SN_DEVICE,*LPSN_DEVICE;

typedef struct _SN_Position
{
	string strPosID;
	string strParentPosID;
	string strPosName;
	string strPosAddr;
	string strDoMail; //�ʱ�
	string strAbsoluteAddr; //���Ե�ַ
	int nPosLevel; //���ȼ�
	
	_SN_Position()
	{
		strPosID = "";
		strParentPosID = "";
		strPosName = "";
		strPosAddr = "";
		strDoMail = "";
		strAbsoluteAddr = "";
		nPosLevel = -1;
	}
	
}SN_Position,*LPSN_Position;

typedef struct _AlarmInfo
{
	string strAlarmID;
	string strDevID;
	string strParentDevID;
	string strAlarmTime;
	int nAlarmLevel;
	int nAlarmType;

	_AlarmInfo()
	{
		strAlarmID = "";
		strDevID = "";
		strParentDevID = "";
		strAlarmTime = "";
		nAlarmLevel = 0;
		nAlarmType = 0;
	}
}AlarmInfo,*LPAlarmInfo;

int getUserID(string strDBAddr,int nPort,string strUserName,string &strUserID);
int getServer(string server_type_id,string strDBAddr,int nDBPort,string &strCMSAddr,int &nCMSPort);
int getAllGBSnDevice(string strDBAddr,int nPort,map<string,SN_DEVICE> &SnDeviceLst,string strUserName);
int UpdateSnDeviceByID(string strDBAddr,int nPort,SN_DEVICE &SnDevice);
int GetSnPosition(string strDBAddr,int nPort,map<string,SN_Position> &SnPositionLst);
int read_profile_string( const char *section, const char *key,char *value, int size, const char *default_value, const char *file);
int ParaseAlarmReport(string strDBAddr,int nPort,char *cAlarmReport,list<AlarmInfo> &alarmLst);

int GetDevTypeName(int nDevType,char *cDevName);

static int load_ini_file(const char *file, char *buf,int *file_size);
static int parse_file(const char *section, const char *key, const char *buf,int *sec_s,int *sec_e, int *key_s,int *key_e, int *value_s, int *value_e);
#endif
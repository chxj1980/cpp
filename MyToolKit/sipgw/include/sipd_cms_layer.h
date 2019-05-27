#ifndef __SIPD_CMS_H_84892883498903__
#define __SIPD_CMS_H_84892883498903__

/*@jidayao 2014-1-9:Adapter Layer for SIP server*/

#define MAX_SIPD_DEVICE_ID_LEN					(20)
#define MAX_SIPD_NORMAL_LEN			(64)
#define MAX_SIPD_URI					(128)
#define MAX_SIPD_TIME_LEN				(32)
#define MAX_SIPD_LONGITUDE_LEN			(32)
#define MAX_SIPD_LATITUDE_LEN			(32)
#define MAX_SIPD_MANUFACTURER_NAME_LEN		(64)
#define MAX_SIPD_MODEL_NAME_LEN				(32)
#define MAX_SIPD_FIREWARE_LEN					(32)


#define MAX_SIPD_ITEM_RSP				(10)
#define MAX_SIPD_ALARM_ITEM_RSP		(30)



/*�������ò���*/
typedef struct SIPD_GATEWAY_CFG
{
	char local_domain_name[MAX_SIPD_DEVICE_ID_LEN+1];/*����SIP����������,��3501040000*/
	char local_domain_id[MAX_SIPD_DEVICE_ID_LEN+1];/*����SIP��������ţ���35010400002000000001*/
	int local_port;/*����SIP�������˿ں�*/
	char local_ip[MAX_SIPD_NORMAL_LEN+1];/*����SIP������IP*/
	char local_gateway[MAX_SIPD_NORMAL_LEN+1];
	char upper_server_name[MAX_SIPD_DEVICE_ID_LEN+1];/*�ϼ�SIP����������*/
	char upper_server_id[MAX_SIPD_DEVICE_ID_LEN+1];/*�ϼ�SIP���������*/
	char upper_server_ip[MAX_SIPD_NORMAL_LEN+1];/*�ϼ�SIP������IP��ַ*/
	int upper_server_port;/*�ϼ�SIP�������˿ں�*/
	char register_upper_server_passwd[MAX_SIPD_NORMAL_LEN+1];/*����ϵͳ���ϼ�������ע���ע������*/
	int register_keepalive;/*����ϵͳ���ϼ���������ע����,Ĭ��3600��*/
	int keepalive_internal; /*�������,Ĭ��Ϊ60*/
} SIPD_GATEWAY_CFG;

/*���ñ仯֪ͨ����
SIPD_CONFIG_NOTIFY_CB_IP ��ʾIP��ַ�仯��
SIPD_CONFIG_NOTIFY_CB_CFG ��ʾ�����������ò����仯*/
enum SIPD_CONFIG_NOTIFY_CB_TYPE{ SIPD_CONFIG_NOTIFY_CB_IP = 0, SIPD_CONFIG_NOTIFY_CB_CFG = 1};

/*���������������ϵͳ��IP��ַ�仯֪ͨ��Ϣ*/
typedef struct sipd_ip_config_ind
{
	char old_ip[MAX_SIPD_NORMAL_LEN+1];/*�ı�ǰIP��ַ��Ϣ*/
       char new_ip[MAX_SIPD_NORMAL_LEN+1];/*�ı��IP��ַ��Ϣ*/
} sipd_ip_config_ind;

/*�������ò����仯֪ͨ*/
typedef struct sipd_servercfg_config_ind
{
	SIPD_GATEWAY_CFG old_cfg; /*�ı�ǰ��������Ϣ*/
      SIPD_GATEWAY_CFG  new_cfg; /*�ı���������Ϣ*/
} sipd_servercfg_config_ind;

/*��������*/
enum SIPD_ALARM_TYPE {SIPD_ALARM_IO = 1, SIPD_ALARM_VIDEO = 2, SIPD_ALARM_OTHER = 3};
/*��������*/
enum sipd_alarm_level {sipd_alarm_levle_all = 0, sipd_alarm_levle_one = 1,sipd_alarm_levle_two = 2, sipd_alarm_levle_three = 3, sipd_alarm_levle_four = 4};


/*����֪ͨ*/
typedef struct sipd_alarm_ind
{
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*���������¼���IPC������ID*/
	char  alarm_id[MAX_SIPD_DEVICE_ID_LEN+1];/*���������¼���IPC�������������ID*/
	enum SIPD_ALARM_TYPE alarm_type;/*��������*/
    enum sipd_alarm_level alarm_priority;/*�������ȼ�*/
    char  alarm_time[30];/*����ʱ���ַ�������ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/

	int did; /*�Ự��ʶ*/
	int tid; /*��Ӧ���ӵ�sip����id*/
} sipd_alarm_ind;

typedef struct
{
    unsigned short Year; 		                /* �� */
    unsigned short Month; 	                    /* �� */
    unsigned short Day; 		                /* �� */
    unsigned short Hour; 	                    /* ʱ */
    unsigned short Minute; 	                    /* �� */
    unsigned short Second; 	                    /* �� */
} SIPD_TIME;

/*�豸ID��Ϣ*/
typedef struct sipd_id_info
{
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸���*/
} sipd_id_info;

/*PTZ���������룬����������ƶ����䱶���佹����Ȧ��
SIPD_PTZ_MOVE_STOP ��ʾֹͣ��ǰPTZ�Ĳ�����������������䱶���佹����Ȧ��Ѳ����*/
enum SIPD_PTZ_MOVE_OPER {SIPD_PTZ_MOVE_UP = 0, SIPD_PTZ_MOVE_DOWN = 1, SIPD_PTZ_MOVE_LEFT = 2, SIPD_PTZ_MOVE_RIGHT = 3, SIPD_PTZ_MOVE_LU = 4, SIPD_PTZ_MOVE_LD = 5, SIPD_PTZ_MOVE_RU = 6, SIPD_PTZ_MOVE_RD = 7, SIPD_PTZ_MOVE_STOP = 8, SIPD_PTZ_ZOOMTELE = 9, SIPD_PTZ_ZOOMWIDE = 10, SIPD_PTZ_FOCUS_NEAR = 11, SIPD_PTZ_FOCUS_FAR = 12, SIPD_PTZ_HALLO_SMALL = 13, SIPD_PTZ_HALLO_LARGE = 14};

/*PTZ���ƽṹ��*/
typedef struct sipd_ptz_control
{
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸ID���*/
       enum SIPD_PTZ_MOVE_OPER cmd_type;/*PTZ��������*/
	unsigned short speed;/*PTZ�����ٶ�*/
} sipd_ptz_control;

/*Ѳ����������*/
enum SIP_PTZ_TOUR_OPER {SIPD_PTZ_TOUR_ADD = 0, SIPD_PTZ_TOUR_DEL = 1, SIPD_PTZ_TOUR_START = 2, SIPD_PTZ_TOUR_SET_STAYTIME = 3, SIPD_PTZ_TOUR_SET_SPEED = 4, SIPD_PTZ_TOUR_STOP = 5};

/*Ѳ�����ƽṹ��*/
typedef struct sipd_tour_control
{
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸ID���*/
       enum SIP_PTZ_TOUR_OPER  tour_cmd;/*Ѳ����������*/
	unsigned char  tour_id;  /*Ѳ���ţ���0��255*/
       unsigned char  preset_id; /*Ԥ�õ�ţ���1��255*/
       unsigned short  time;/*Ѳ����Ѳ��ͣ��ʱ��*/
	unsigned short speed;/*Ѳ����Ѳ���ٶ�*/
} sipd_tour_control;

/*Ԥ��λ��������*/
enum SIPD_PTZ_PRESET_OPER {SIPD_PTZ_PRESET_ADD = 0, SIPD_PTZ_PRESET_DEL = 1, SIPD_PTZ_PRESET_GOTO = 2};

/*Ԥ��λ���ƽṹ��*/
typedef struct sipd_preset_control
{
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸���*/
      enum SIPD_PTZ_PRESET_OPER cmd_type;/*Ԥ��λ��������*/
	unsigned char  preset_id; /*Ԥ��λID����1��ʼ��1��255*/
}sipd_preset_control;

/*�Զ�ɨ����������*/
enum SIPD_PTZ_AUTOSCAN_OPER {SIPD_PTZ_AUTOSCAN_START = 0};

/*�Զ�ɨ����ƽṹ��*/
typedef struct sipd_autoscan_control
{
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸���*/
     enum SIPD_PTZ_AUTOSCAN_OPER cmd_type;/*����ɨ���������*/
} sipd_autoscan_control;



/*¼���������*/
enum SIPD_RECORD_CONTROL_OPER {SIPD_RECORD_CONTROL_START = 0, SIPD_RECORD_CONTROL_STOP = 1};
/*¼����ƽṹ*/	
typedef struct sipd_record_control
{
       char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
       char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���*/
      enum SIPD_RECORD_CONTROL_OPER cmd_type;
} sipd_record_control;

/*��������/�������������λ����
SIPD_ALARM_CONTROL_SET_GUARD ����������
SIPD_ALARM_CONTROL_RESET_GUARD����������
SIPD_ALARM_CONTROL_RESET_ALARM��������λ */
enum SIPD_ALARM_CONTROL_OPER { SIPD_ALARM_CONTROL_SET_GUARD = 0, SIPD_ALARM_CONTROL_RESET_GUARD = 1, SIPD_ALARM_CONTROL_RESET_ALARM = 2};
/*��������/������������λ�ṹ*/
typedef struct sipd_alarm_control
{
       char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
       char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
      char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���*/
    enum SIPD_ALARM_CONTROL_OPER cmd_type;/*��������������λ����*/
} sipd_alarm_control;

typedef struct sipd_control_rsp
{
       char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
      char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
     char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���*/
    int result; /*0:�ɹ��� 1ʧ��*/
} sipd_control_rsp;

/*�豸Ŀ¼��ѯ/��������*/
typedef struct sipd_catalog_req
{
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
    char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���豸/��ȫ������Ƶ�������ϵͳ/�������*/
	char StartTime[MAX_SIPD_TIME_LEN+1]; /*�����豸����ʼʱ�䣨��ѡ��,�ձ�ʾ���ޡ���ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char EndTime[MAX_SIPD_TIME_LEN+1]; /*�����豸����ֹʱ�䣨��ѡ��,�ձ�ʾ����ǰʱ�䡣��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/

	int did; /*���ĻỰ��ʶ*/
	int tid; /*��Ӧ���ĵ�SIP����id*/
	int	expires;	/*���Ĺ���ʱ�䣬��λ��*/
} sipd_catalog_req;

/*������ѯ/��������*/
typedef struct sipd_alarm_req
{
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���豸/��ȫ������Ƶ�������ϵͳ/�������*/
	char StartTime[MAX_SIPD_TIME_LEN+1]; /*�����豸����ʼʱ�䣨��ѡ��,�ձ�ʾ���ޡ���ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char EndTime[MAX_SIPD_TIME_LEN+1]; /*�����豸����ֹʱ�䣨��ѡ��,�ձ�ʾ����ǰʱ�䡣��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/

	int	StartAlarmPriority;
	int	EndAlarmPriority;
	int	AlarmMethod;

	int did; /*���ĻỰ��ʶ*/
	int tid; /*��Ӧ���ĵ�SIP����id*/
	int	expires;	/*���Ĺ���ʱ�䣬��λ��*/
} sipd_alarm_req;

/*�豸Ԥ�Ƶ��ѯ����*/
typedef struct sipd_perset_query_req
{
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���豸/��ȫ������Ƶ�������ϵͳ/�������*/
	char StartTime[MAX_SIPD_TIME_LEN+1]; /*�����豸����ʼʱ�䣨��ѡ��,�ձ�ʾ���ޡ���ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char EndTime[MAX_SIPD_TIME_LEN+1]; /*�����豸����ֹʱ�䣨��ѡ��,�ձ�ʾ����ǰʱ�䡣��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
} sipd_perset_query_req;

/*�豸Ŀ¼��ѯ/����Ӧ�������Ϣ*/
typedef struct sipd_catalog_rsp_basic_info
{	
        char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
      char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
      char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���豸/��ȫ������Ƶ�������ϵͳ/�������*/
      int SumNum;/*��ѯ�������*/
     int DeviceList_Num;/*Ŀ¼�����,���ȡֵΪMAX_SIPD_ITEM_RSP*/

	 int did; /*�Ự��ʶ*/
	 int tid; /*��Ӧ���ӵ�sip����id*/
} sipd_catalog_rsp_basic_info;

/*���ȫģʽ*/
enum SIPD_SAFETY_WAY_TYPE{ SIPD_SAFETY_WAY_NONE = 0, SIPD_SAFETY_WAY_SMIME = 2, SIPD_SAFETY_WAY_SMIME_DES = 3, SIPD_SAFETY_WAY_DIGEST = 4};
/*�豸״̬��SIPD_STATUS_ON ���豸���ߣ�SIPD_STATUS_OFF���豸����*/
enum SIPD_STATUS_TYPE{SIPD_STATUS_ON = 0, SIPD_STATUS_OFF = 1};
/*�豸Ŀ¼��ѯӦ����豸Ŀ¼����Ϣ*/
typedef struct sipd_catalog_item
{
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1];/*�豸/����/ϵͳ����*/
	char Name[MAX_SIPD_NORMAL_LEN+1];/*�豸/����/ϵͳ����*/
	char Manufacturer[MAX_SIPD_MANUFACTURER_NAME_LEN+1];/*��Ϊ�豸ʱ���豸����*/
	char Model[MAX_SIPD_MODEL_NAME_LEN +1];/*��Ϊ�豸ʱ���豸�ͺ�*/
	char Owner[MAX_SIPD_NORMAL_LEN+1];/*��Ϊ�豸ʱ���豸����*/
	char CivilCode[MAX_SIPD_NORMAL_LEN+1];/*��������*/
	char Block[MAX_SIPD_NORMAL_LEN+1];/*��������ѡ��*/
	char Address[MAX_SIPD_URI+1];/*��Ϊ�豸ʱ����װ��ַ*/
	int Parental;/*��Ϊ�豸ʱ���Ƿ������豸��1�У�0û��*/
	char ParentID[MAX_SIPD_DEVICE_ID_LEN+1];/*���豸/����/ϵͳID����ѡ���и��豸��Ҫ��д��*/
	/*���ȫģʽ����ѡ��ȱʡΪ0.  0�������ã�2��S/MIMEǩ����ʽ��3��S/MIME����ǩ��ͬʱ���÷�ʽ��4������ժҪ��ʽ*/
	int SafteyWay;
	/*ע�᷽ʽ��ȱʡΪ1��1������SIP 3261��׼����֤ע��ģʽ��2�����ڿ����˫����֤ע��ģʽ��3����������֤���˫����֤ע��ģʽ*/
	int RegisterWay;
	char CertNum[MAX_SIPD_URI+1];/*֤�����кţ���֤����豸��ѡ��*/
	/*֤����Ч��ʶ����֤����豸��ѡ��ȱʡΪ0.  0����Ч��1����Ч*/
	int Certifiable;
	/*��Чԭ���루��֤�鵫֤����Ч���豸��ѡ��*/
	int ErrCode;
	/*֤����ֹ��Ч�ڣ���֤����豸��ѡ��. ��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char EndTime[MAX_SIPD_TIME_LEN+1];
	int Secrecy;/*�������ԣ�ȱʡΪ0. 0�������ܣ�1������*/
	char IPAddress[MAX_SIPD_NORMAL_LEN+1];/*IP��ַ����ѡ��*/
	int Port;/*�˿ںţ���ѡ��*/
	char Password[MAX_SIPD_NORMAL_LEN+1];/*�豸�����ѡ��*/
	enum SIPD_STATUS_TYPE Status; /*�豸״̬*/
	char Longitude[MAX_SIPD_LONGITUDE_LEN+1];/*���ȣ���ѡ��*/
	char Latitude[MAX_SIPD_LATITUDE_LEN+1];/*γ�ȣ���ѡ��*/

	/* ״̬�ı��¼� ON �����ߣ� OFF �� ���ߣ� VLOST ����Ƶ��ʧ�� DEFECT �� ���ϣ� 
		ADD �� ���ӣ� DEL �� ɾ���� UPDATE �� ���� */
	char Event[MAX_SIPD_NORMAL_LEN];
} sipd_catalog_item;

/*�豸��Ϣ��ѯ����*/
typedef struct sipd_deviceinfo_req
{	
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸����*/
}sipd_deviceinfo_req;

enum SIPD_RESULT_TYPE {SIPD_RESULT_OK = 0, SIPD_RESULT_ERROR = 1};
/*�豸��Ϣ��ѯӦ��*/
typedef struct sipd_deviceinfo_rsp
{
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char  device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸/����/ϵͳ�ı���*/
	enum SIPD_RESULT_TYPE Result;/*��ѯ���*/
	char manufacturer[MAX_SIPD_MANUFACTURER_NAME_LEN];/*�豸�����̣���ѡ��*/
	char model[MAX_SIPD_MODEL_NAME_LEN];/*�豸�ͺţ���ѡ��*/
	char firmware[MAX_SIPD_FIREWARE_LEN];/*�豸�̼��汾����ѡ��*/
	char DeviceType[MAX_SIPD_NORMAL_LEN]; /*IPC, DVR, DECODER, NVR, etc.*/
	int MaxCamera;/*ͨ��������ipcһ��ͨ��(��ѡ)*/
	int MaxAlarm;/*�����������*/
}sipd_deviceinfo_rsp;

/*�豸״̬��ѯ����*/
typedef struct sipd_devicestate_req
{	
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���豸/����ϵͳ����*/
}sipd_devicestate_req;

enum SIPD_STATUS_ONLINE_TYPE { SIPD_STATUS_ONLINE_TYPE_ONLINE = 0, SIPD_STATUS_ONLINE_TYPE_OFFLINE = 1};
/*�豸״̬��ѯӦ�������Ϣ*/
typedef struct sipd_devicestate_rsp_basic_info
{	
	char from_uri[MAX_SIPD_URI];/*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ���豸���豸/����ϵͳ����*/
	enum SIPD_RESULT_TYPE Result;/*��ѯ���*/
	enum SIPD_STATUS_ONLINE_TYPE Online;/*�Ƿ�����*/
	enum SIPD_RESULT_TYPE Status;/*�Ƿ���������*/
	char Reason[MAX_SIPD_URI+1];/*����������ԭ�򣨿�ѡ��*/
	enum SIPD_STATUS_TYPE Encode;/*�Ƿ���루��ѡ��*/
	enum SIPD_STATUS_TYPE Record;/*�Ƿ�¼�񣨿�ѡ��*/
	char DeviceTime[MAX_SIPD_TIME_LEN+1];/*�豸ʱ������ڣ���ѡ. ��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09��*/
	int AlaramDeviceNum;/*�����豸״̬�б����,���ȡֵΪMAX_SIPD_ALARM_ITEM_RSP*/
} sipd_devicestate_rsp_basic_info;
/*�����豸״̬�������豸ָ���Ǳ��������豸��*/
enum SIPD_ALARM_STATUS_TYPE{ SIPD_ALARM_STATUS_ONDUTY = 0, SIPD_ALARM_STATUS_OFFDUTY = 1, SIPD_ALARM_STATUS_ALARM = 2};
/*�����豸״̬�б���*/
typedef struct sipd_alarm_status_item
{
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�����豸���루�����豸ָ���Ǳ��������豸��*/
    	enum SIPD_ALARM_STATUS_TYPE Status;/*�����豸״̬*/
} sipd_alarm_status_item;

/*�ص����صĲ������͡�
SIPD_INFO_RSP_CB_CATALOG���ظ�Ŀ¼��ѯ
SIPD_INFO_RSP_CB_DEVICEINFO���ظ��豸��Ϣ��ѯ
SIPD_INFO_RSP_CB_DEVICESTATE���ظ��豸״̬��ѯ
SIPD_INFO_RSP_CB_RECORDFILE���ظ�¼���ļ�������ѯ*/
enum SIPD_INFO_RSP_CB_TYPE{SIPD_INFO_RSP_CB_CATALOG = 1, SIPD_INFO_RSP_CB_DEVICEINFO = 2,  SIPD_INFO_RSP_CB_DEVICESTATE = 3, SIPD_INFO_RSP_CB_RECORDFILE = 4};


/*¼���������*/
enum SIPD_RECORD_INFO_TYPE{SIPD_RECORD_INFO_TYPE_ALL = 1, SIPD_RECORD_INFO_TYPE_TIME = 2, SIPD_RECORD_INFO_TYPE_ALARM = 3, SIPD_RECORD_INFO_TYPE_MANUAL = 4};

/*����Ƶ�ļ���������*/
typedef struct sipd_recordinfo_req
{
	char from_uri[MAX_SIPD_URI]; /*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*Ŀ¼�豸/��ȫ������Ƶ�������ϵͳ/����*/
	char StartTime[MAX_SIPD_TIME_LEN]; /*¼����ʼʱ�䣨��ѡ���ձ�ʾ����. ��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char EndTime[MAX_SIPD_TIME_LEN]; /*����¼����ֹʱ�䣨��ѡ���ձ�ʾ����ǰʱ��. ��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char FilePath[MAX_SIPD_URI]; /*�ļ�·��������ѡ����ע�������·����������һ��ý��洢���������豸����*/
	char Address[MAX_SIPD_URI]; /*¼���ַ����ѡ ,֧�ֲ���ȫ��ѯ��*/
	int Secrecy;/*�������ԣ���ѡ��ȱʡΪ0.  0:������1:����*/
	enum SIPD_RECORD_INFO_TYPE Type;/*¼��������ͣ���ѡ��*/
	char RecorderID[MAX_SIPD_DEVICE_ID_LEN+1]; /*¼�񴥷���ID����ѡ, ��ĳ�������û�������������û�Ҳ��������б��룬��ĳ���ͻ��ˣ������¼��*/
} sipd_recordinfo_req;

/*����Ƶ�ļ���������Ӧ�������Ϣ*/
typedef struct sipd_recordinfo_rsp_basic_info
{
	char from_uri[MAX_SIPD_URI]; /*������URI*/
	char to_uri[MAX_SIPD_URI];/*������URI*/
	char SN[MAX_SIPD_DEVICE_ID_LEN+1];/*�������к�*/
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*�豸/����*/
	char Name[MAX_SIPD_NORMAL_LEN+1]; /*�豸/��������*/
	int SumNum; /*��ѯ�������*/
	int RecordListNum; /*�ļ�Ŀ¼�����,���ȡֵΪMAX_SIPD_ITEM_RSP*/
} sipd_recordinfo_rsp_basic_info
;
/*����Ƶ�ļ�����Ӧ����ļ�Ŀ¼����Ϣ*/
typedef struct sipd_file_item
{
	char device_id[MAX_SIPD_DEVICE_ID_LEN+1];/*�豸/�������*/
	char Name[MAX_SIPD_NORMAL_LEN+1];/*�豸/��������*/
	char FilePath[MAX_SIPD_URI+1];/*�ļ�·��������ѡ��*/
	char Address[MAX_SIPD_URI+1];/*¼���ַ����ѡ��*/
	char StartTime[MAX_SIPD_TIME_LEN+1];/*¼��ʼʱ�䣨��ѡ��. ��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	char EndTime[MAX_SIPD_TIME_LEN+1];/*¼�����ʱ�䣨��ѡ��. ��ʽΪYYYY-MM-DDThh:mm:ss����2009-12-04T13:05:09*/
	int Secrecy;/*�������ԣ�ȱʡΪ0. 0�������ܣ�1������*/
	enum SIPD_RECORD_INFO_TYPE Type;/*¼��������ͣ���ѡ��*/
	char RecorderID[MAX_SIPD_DEVICE_ID_LEN+1];/*¼�񴥷���ID����ѡ��*/
}sipd_file_item;


/*IP��ַ���ͣ����Ԥ������ǰʵ��ֻ֧��IPv4*/
enum SIPD_IPType {SIPD_IPType_IPv4 = 0, SIPD_IPType_IPv6 = 1};

/* SIPD_STREAM_TYPE_PLAY ��ʾʵʱ�㲥
SIPD_STREAM_TYPE_PLAYBACK ��ʾ��ʷ����Ƶ�ط�
SIPD_STREAM_TYPE_DOWNLOAD ��ʾ��ʷ����Ƶ����*/
enum SIPD_STREAM_TYPE{SIPD_STREAM_TYPE_PLAY = 1, SIPD_STREAM_TYPE_PLAYBACK = 2, SIPD_STREAM_TYPE_DOWNLOAD = 3};

/*ý�����ͣ���Ƶ/��Ƶ/����Ƶ����ȡֵΪSIPD_MEDIA_TYPE_NONE ʱ�豸�����Լ������Ĭ�Ϸ�����Ƶ��������Ƶ���Ƽ�ֻ������Ƶ����*/
enum SIPD_MEDIA_TYPE{SIPD_MEDIA_TYPE_NONE = 0, SIPD_MEDIA_TYPE_VIDEO = 1, SIPD_MEDIA_TYPE_AUDIO = 2, SIPD_MEDIA_TYPE_MIX = 3};

/*��Ƶ�����ʽ����ȡֵΪSIPD_MEDIA_F_VIDEO_TYPE_DEF ʱ�豸ʹ���Լ���Ĭ����Ƶ�����ʽ���Ƽ���ʱʹ��H264*/
enum SIPD_MEDIA_F_VIDEO_TYPE{SIPD_MEDIA_F_VIDEO_TYPE_DEF = 0, SIPD_MEDIA_F_VIDEO_TYPE_MPEG4 = 1, SIPD_MEDIA_F_VIDEO_TYPE_H264 = 2, SIPD_MEDIA_F_VIDEO_TYPE_SVAC = 3, SIPD_MEDIA_F_VIDEO_TYPE_3GP = 4};

/*��Ƶ�ֱ��ʣ���ȡֵΪSIPD_MEDIA_F_VIDEO_RESOLUTION_DEF ʱ�豸ʹ���Լ���Ĭ�Ϸֱ���*/
enum SIPD_MEDIA_F_VIDEO_RESOLUTION{SIPD_MEDIA_F_VIDEO_RESOLUTION_DEF = 0, SIPD_MEDIA_F_VIDEO_RESOLUTION_QCIF = 1, SIPD_MEDIA_F_VIDEO_RESOLUTION_CIF = 2, SIPD_MEDIA_F_VIDEO_RESOLUTION_4CIF = 3, SIPD_MEDIA_F_VIDEO_RESOLUTION_D1 = 4, SIPD_MEDIA_F_VIDEO_RESOLUTION_720P = 5, SIPD_MEDIA_F_VIDEO_RESOLUTION_1080P = 6};

/*��Ƶ�������ͣ���ȡֵΪSIPD_MEDIA_F_VIDEO_RATE_TYPE_DEF ʱ�豸ʹ���Լ�Ĭ�ϵ���������*/
enum SIPD_MEDIA_F_VIDEO_RATE_TYPE{SIPD_MEDIA_F_VIDEO_RATE_TYPE_DEF = 0, SIPD_MEDIA_F_VIDEO_RATE_TYPE_CBR = 1, SIPD_MEDIA_F_VIDEO_RATE_TYPE_VBR = 2};


/*��Ƶ�����ʽ����ȡֵΪSIPD_MEDIA_F_ AUDIO _TYPE_DEF ʱ�豸ʹ���Լ���Ĭ����Ƶ�����ʽ���Ƽ���ʱʹ��G711*/
enum SIPD_MEDIA_F_AUDIO_TYPE{SIPD_MEDIA_F_AUDIO_TYPE_DEF = 0, SIPD_MEDIA_F_AUDIO_TYPE_G711 = 1, SIPD_MEDIA_F_AUDIO_TYPE_G723 = 2, SIPD_MEDIA_F_AUDIO_TYPE_G729 = 3, SIPD_MEDIA_F_AUDIO_TYPE_G722 = 4};

/*��Ƶ���ʴ�С����ΪSIPD_MEDIA_F_AUDIO_BITRATE_DEF ʱ�豸ʹ���Լ�Ĭ�ϵ����ʴ�С��
SIPD_MEDIA_F_AUDIO_BITRATE_5P3 ��ʾ5.3 kbps
SIPD_MEDIA_F_AUDIO_BITRATE_6P3 ��ʾ6.3 kbps 
SIPD_MEDIA_F_AUDIO_BITRATE_8 ��ʾ8 kbps 
SIPD_MEDIA_F_AUDIO_BITRATE_16 ��ʾ16 kbps 
SIPD_MEDIA_F_AUDIO_BITRATE_24 ��ʾ24 kbps 
SIPD_MEDIA_F_AUDIO_BITRATE_32 ��ʾ32kbps 
SIPD_MEDIA_F_AUDIO_BITRATE_48 ��ʾ48 kbps 
SIPD_MEDIA_F_AUDIO_BITRATE_64 ��ʾ64 kbps */
enum SIPD_MEDIA_F_AUDIO_BITRATE{SIPD_MEDIA_F_AUDIO_BITRATE_DEF = 0, SIPD_MEDIA_F_AUDIO_BITRATE_5P3 = 1, SIPD_MEDIA_F_AUDIO_BITRATE_6P3 = 2, SIPD_MEDIA_F_AUDIO_BITRATE_8 = 3, SIPD_MEDIA_F_AUDIO_BITRATE_16 = 4, SIPD_MEDIA_F_AUDIO_BITRATE_24 = 5, SIPD_MEDIA_F_AUDIO_BITRATE_32 = 6, SIPD_MEDIA_F_AUDIO_BITRATE_48 = 7, SIPD_MEDIA_F_AUDIO_BITRATE_64 = 8};

/*��Ƶ�����ʣ���ΪSIPD_MEDIA_F_AUDIO_SAMPLE_RATE_DEF ʱ�豸ʹ���Լ�Ĭ�ϵ���Ƶ�����ʡ�
SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_8��ʾ 8kHz
SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_14��ʾ14kHz
SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_16��ʾ16kHz
SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_32��ʾ32kHz*/
enum SIPD_MEDIA_F_AUDIO_SAMPLE_RATE{SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_DEF = 0, SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_8 = 1, SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_14 = 2, SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_16 = 3, SIPD_MEDIA_F_AUDIO_SAMPLE_RATE_32 = 4};


typedef struct sipd_media_session
{
	int did; /*��ʵʱ/�ط�/�������ӵĻỰ��ʶ*/
	int tid; /*��Ӧ���ӵ�SIP����id*/
	/*����ʵʱ��Ƶ�㲥��˵��o_id��ʾý�巢���豸ID���룬��IPC��DVR/NVR���롣���ڻطź�������˵��o_id��ʾ¼���ļ������ߵı���*/
	char o_id[MAX_SIPD_DEVICE_ID_LEN+1];
	char channel_id[MAX_SIPD_DEVICE_ID_LEN+1];/*�㲥/�ط�/����ͨ��*/
	enum SIPD_RECORD_INFO_TYPE Type;/*�ط�����/��������*/
	enum SIPD_STREAM_TYPE stream_type; /*�������ͣ�ʵʱ�㲥��طŻ�����*/
    /*ý����������IP��ַ����*/
	enum SIPD_IPType media_recv_ip_type;
/*ý����������IP��ַ*/
	char media_recv_ip[MAX_SIPD_URI];
    /*ý����������RTP�˿ں�*/
	char media_recv_port[MAX_SIPD_NORMAL_LEN];
	enum SIPD_MEDIA_TYPE media_type;/*ý������*/
	/*start_time��end_time�������ֶζ���stream_type == SIPD_STREAM_TYPE_PLAY ʵʱ�㲥��˵���������ֶζ�ȡֵΪ"0"��"0".
	���ڻط�SIPD_STREAM_TYPE_PLAYBACK������SIPD_STREAM_TYPE_DOWNLOAD��˵���������ֶα�ʾ��ʼ�ͽ���ʱ�䡣ʱ���ʽ��IETF RFC 4566��5.9����ʼʱ��ͽ���ʱ�䶼��Ҫ�طŻ����ص�����Ƶ�ļ�¼��ʱ����е�ĳ��ʱ�̡���start_timeΪ"1288625085"  
	,end_timeΪ"1288625871"*/
    	char t_start_time[MAX_SIPD_NORMAL_LEN];
	char t_end_time[MAX_SIPD_NORMAL_LEN];
	/*ʮ���������ַ�����ʾSSRCֵ*/
	char ssrc[MAX_SIPD_NORMAL_LEN];
	/*��Ƶ�����ʽ*/
	enum SIPD_MEDIA_F_VIDEO_TYPE f_video_type;
    /*��Ƶ�ֱ���*/
	enum SIPD_MEDIA_F_VIDEO_RESOLUTION f_resolution;
    /*��Ƶ֡�ʣ�0��99*/
	int f_framerate;
    /*��������*/
	enum SIPD_MEDIA_F_VIDEO_RATE_TYPE f_rate_type;
    /*���ʴ�С*/
	int bitrate;
    /*��Ƶ�����ʽ*/
	enum SIPD_MEDIA_F_AUDIO_TYPE audio_type;
    /*��Ƶ���ʴ�С*/
	enum SIPD_MEDIA_F_AUDIO_BITRATE audio_bitrate;
    /*��Ƶ������*/
	enum SIPD_MEDIA_F_AUDIO_SAMPLE_RATE audio_samplerate;	
} sipd_media_session;

typedef struct sipd_sender_sdp_info
{
	int did; /*��ʵʱ/�ط�/�������ӵĻỰ��ʶ*/
	int tid; /*��Ӧ���ӵ�sip����id*/
    /*ý�巢�����豸ID��ţ���IPC��DVR�豸���*/
	char media_sender_id[MAX_SIPD_DEVICE_ID_LEN+1];
	/*ý����������IP��ַ����*/
	enum SIPD_IPType media_send_ip_type;
	/*ý����������IP��ַ*/
	char media_send_ip[MAX_SIPD_URI];
    /*ý����������RTP�˿ں�*/
	char media_send_port[MAX_SIPD_NORMAL_LEN];
	char ssrc[MAX_SIPD_NORMAL_LEN];
} sipd_sender_sdp_info;

typedef struct sipd_media_file_end_ind
{
	int did; /*��ʵʱ/�ط�/�������ӵĻỰ��ʶ*/
	int tid;/*��Ӧ���ӵ�sip����id*/
	
	/*����ʵʱ��Ƶ�㲥��˵��o_id��ʾý�巢���豸ID���룬��IPC��DVR/NVR���롣���ڻطź�������˵��o_id��ʾ¼���ļ������ߵı���*/
	char o_id[MAX_SIPD_DEVICE_ID_LEN+1]; /*ȡ��sipd_media_session�е�ͬ���ֶ�*/
} sipd_media_file_end_ind;

/*ý����ƻص�����*/
enum SIPD_MEDIA_CONTROL_CB_TYPE{ SIPD_MEDIA_CONTROL_CB_INVITE_RSP = 0, SIPD_MEDIA_CONTROL_CB_FILE_TO_END = 1};

/*���Ļص�����*/
enum SIPD_SUBSCRIBE_CB_TYPE{ SIPD_SUBSCRIBE_CB_CATALOG_RSP = 0, SIPD_SUBSCRIBE_CB_ALARM_RSP = 1};

/*�������ؿ���ý�����ص���������
SIPD_TO_CMS_CMD_TYPE_START ��ʼ����
SIPD_TO_CMS_CMD_TYPE_STOP ��������
SIPD_TO_CMS_CMD_TYPE _PLAYBACK_CONTROL_RTSP �طſ���*/
enum SIPD_TO_CMS_CMD_TYPE{ SIPD_TO_CMS_CMD_TYPE_START = 1, SIPD_TO_CMS_CMD_TYPE_STOP = 2,  SIPD_TO_CMS_CMD_TYPE_PLAYBACK_CONTROL_RTSP = 3};

#define MAX_SIPD_INFO_LENGTH			(1024)
/*����طſ��Ƶ�RTSP����*/
typedef struct sipd_playback_mans_rtsp_ind
{
	char rtsp_des[MAX_SIPD_INFO_LENGTH+1];/* �طſ��Ƶ�RTSP����*/
    int len;/*���ĳ���*/
} sipd_playback_mans_rtsp_ind;





typedef void(*sip_config_pcb_func)(int* type, void* param1);
typedef void(*sip_alarm_ind_pcb_func)( sipd_alarm_ind * alarm_info);
typedef void(*sip_control_req_pcb_func)( sipd_control_rsp* pControlRsp);
typedef void(*sip_info_req_pcb_func)(int* type, void* param1, void* param2);
typedef void(*sip_media_pcb_func)(int* type, void* param1);
typedef void(*sip_subscribe_pcb_func)(int* type, void* param1);


 //-----------------------------------------------------------------------
/*����˵��:��ʼ��
/*����:��
/*����ֵ:0��ʾ�ɹ���<0��ʾʧ��*/
//-----------------------------------------------------------------------
extern int Sipd_Init();

//-----------------------------------------------------------------------
/*����˵��:����ʼ
/*����:��
/*����ֵ:0��ʾ�ɹ���<0��ʾʧ��*/
//-----------------------------------------------------------------------
extern int Sipd_Start();

extern int Sipd_GetSIPServerCfg (SIPD_GATEWAY_CFG* pCfg);
extern int Sipd_Register_ServerConfig_CB (sip_config_pcb_func config_fun);
extern int Sipd_Register_AlarmInd_CB (sip_alarm_ind_pcb_func alarm_ind_fun);
extern int Sipd_settime(const sipd_id_info * pDeviceID,  const SIPD_TIME* pTime);
extern int Sipd_PTZ_Move(const sipd_ptz_control* pControl);
extern int Sipd_PTZ_Tour(const sipd_tour_control * pTourControl);
extern int Sipd_PTZ_Preset(const sipd_preset_control * pPresetControl);
extern int Sipd_PTZ_AutoScan(const sipd_autoscan_control * pAutoScanControl);
extern int Sipd_Reboot(const sipd_id_info * pIdInfo);
extern int Sipd_record_control (const sipd_record_control * pRecordControl);
extern int Sipd_alarm_control (const sipd_alarm_control * pAlarmControl);
extern int Sipd_Register_ControlRsp_CB(sip_control_req_pcb_func control_rsp_fun);
extern int Sipd_cataloginfo_request(const sipd_catalog_req * pCatalogReq);
extern int Sipd_deviceinfo_request(const sipd_deviceinfo_req * pDeviceinfoReq);
extern int Sipd_stateinfo_request(const sipd_devicestate_req * pStateInfoReq);
extern int Sipd_Register_InfoRsp_CB(sip_info_req_pcb_func rsp_fun);
extern int Sipd_search_recordfile_req (sipd_recordinfo_req * pRecordFileReq);
extern int Sipd_Register_MediaControl_CB(sip_media_pcb_func media_control_fun);
extern int Invite_play_playback_download(const sipd_media_session* pMediaInfo);
extern int Sipd_media_control_notify_CMS(const int did, const int tid, const enum SIPD_TO_CMS_CMD_TYPE cmd_type, const sipd_playback_mans_rtsp_ind* playback_rtsp_control);


//-----------------------------------------------------------------------
/*����˵��:ֹͣ
/*����:��
/*����ֵ:0��ʾ�ɹ�������ֵ��ʾʧ��*/
//-----------------------------------------------------------------------

extern int Sipd_Stop();

//-----------------------------------------------------------------------
/*����˵��:����ʼ��
/*����:��
/*����ֵ:0��ʾ�ɹ�������ֵ��ʾʧ��*/
//-----------------------------------------------------------------------

extern int Sipd_Uninit();






#endif


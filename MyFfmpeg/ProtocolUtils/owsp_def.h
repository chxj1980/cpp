/*
 *  Version 3.5
 *  Time: 20090226
 */
 
#ifndef __LVSP_DEF_H_INCLUDED__
#define __LVSP_DEF_H_INCLUDED__


#define STR_LEN_32		32
#define STR_LEN_16		16

#define MAX_TLV_LEN		65535		//���TLV��Ϊ(64K-1)

//�汾��Ϣ
#define VERSION_MAJOR	3
#define VERSION_MINOR	8

//
//  ����Ѿ�����
//
#ifndef u_int32
typedef unsigned long	u_int32;
typedef unsigned short	u_int16;
typedef unsigned char	u_int8;
#endif

#pragma pack(push)
#pragma pack(4)

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM								0x0001
#endif 

#ifndef WAVE_FORMAT_MPEGLAYER3
#define WAVE_FORMAT_MPEGLAYER3					    0x0055	// ISO/MPEG Layer 3 ��ʽ���
#endif                                      
                                            
#ifndef WAVE_FORMAT_QUALCOMM_PUREVOICE      
#define WAVE_FORMAT_QUALCOMM_PUREVOICE	    	    0x0150
#endif                                      
                                            
//AMR_NB CBR wave format                    
#ifndef WAVE_FORMAT_AMR_CBR                 
#define WAVE_FORMAT_AMR_CBR 						0x7A21 
#endif                                      
                                            
//AMR VBR Not support yet                   
#ifndef WAVE_FORMAT_AMR_VBR                 
#define WAVE_FORMAT_AMR_VBR 						0x7A22
#endif                                      
                                            
//AMR_WB Wave format                        
#ifndef WAVE_FORMAT_VOICEAGE_AMR_WB         
#define WAVE_FORMAT_VOICEAGE_AMR_WB			        0xA104
#endif                                      
                                            
#define CODEC_H264									0x34363248	//H264
#define CODEC_H265									0x35363248	//H265


/* TLV ���������� */

#define TLV_T_VERSION_INFO_ANSWER			   39
#define TLV_T_VERSION_INFO_REQUEST		   40
#define TLV_T_LOGIN_REQUEST					     41
#define TLV_T_LOGIN_ANSWER						   42
#define TLV_T_TOTAL_CHANNEL						   43		//NOT USED
#define TLV_T_SENDDATA_REQUEST				     44		//ͨ������
#define TLV_T_SENDDATA_ANSWER					 45		//ͨ������Ӧ��
#define TLV_T_TOTAL_CHANEL_ANSWER				 46		//Not used
#define TLV_T_SUSPENDSENDDATA_REQUEST		     47		//ֹͣ��������
#define TLV_T_SUSPENDSENDDATA_ANSWER		     48
#define TLV_T_DEVICE_KEEP_ALIVE					 49		//������
#define TLV_T_DEVICE_FORCE_EXIT					 50		
#define TLV_T_CONTROL_REQUEST					 51		//��̨�ȿ�������
#define TLV_T_CONTROL_ANSWER					 52		//��̨����Ӧ
#define TLV_T_RECORD_REQUEST				     53		//¼������
#define TLV_T_RECORD_ANSWER						 54
#define TLV_T_DEVICE_SETTING_REQUEST			 55		//�豸������������
#define TLV_T_DEVICE_SETTING_ANSWER				 56		//�豸��������Ӧ��
#define TLV_T_KEEP_ALIVE_ANSWER					 57		//��������Ӧ
#define TLV_T_DEVICE_RESET						 58		//֪ͨ�豸����
#define TLV_T_DEVICE_RESET_ANSWER				 59		//�豸���յ�������������Ӧ��ͨ�����÷���
#define TLV_T_ALERT_REQUEST     				 60   //�����������豸����
#define TLV_T_ALERT_ANSWER      				 61   //���������Ӧ���ɷ�����������ͨ�����Բ��÷���
#define TLV_T_ALERT_SEND_PHOTO    			     62   //�������豸�ɼ���ʱ��ͼƬ�����͵�������
#define TLV_T_ALERT_SEND_PHOTO_ANSWER 	         63   //�豸����MSG_CMD_ALERT_SEND_PHOTO�󣬷������Ļ�Ӧ
#define TLV_T_CHANNLE_REQUEST		    		 64   		//�л�����һͨ��
#define TLV_T_CHANNLE_ANSWER					 65   		//�л���һͨ��Ӧ��
#define TLV_T_SUSPEND_CHANNLE_REQUEST		     66   		//����ĳһͨ��
#define TLV_T_SUSPEND_CHANNLE_ANSWER			 67   		//Ӧ��
#define TLV_T_VALIDATE_REQUEST					 68   		//������֤����
#define TLV_T_VALIDATE_ANSWER					 69   		//Ӧ��
#define TLV_T_DVS_INFO_REQUEST					 70			//�豸DVS֪ͨ���ӷ��豸��Ϣ����
#define TLV_T_DVS_INFO_ANSWER					 71			//
#define TLV_T_PHONE_INFO_REQUEST					 72			//�ֻ�֪ͨ���ӷ��ֻ���Ϣ����
#define TLV_T_PHONE_INFO_ANSWER					 73			//



//vod & live
#define TLV_T_AUDIO_INFO							 0x61   //97		��Ƶ��Ϣ, ��ʾVΪ��Ƶ��Ϣ
#define TLV_T_AUDIO_DATA							 0x62   //98		��Ƶ����, ��ʾVΪ��Ƶ����
#define TLV_T_VIDEO_FRAME_INFO					     0x63   //99    ��Ƶ֡��Ϣ, ��ʾV����������֡��Ϣ
#define TLV_T_VIDEO_IFRAME_DATA					     0x64   //100   ��Ƶ�ؼ�֡���ݣ���ʾV������Ϊ�ؼ�֡
#define TLV_T_VIDEO_PFRAME_DATA					     0x66   //102   ��ƵP֡(�ο�֡)����, ��ʾV������Ϊ�ο�֡
#define TLV_T_VIDEO_FRAME_INFO_EX				     0x65   //101   ��չ��Ƶ֡��Ϣ֧��>=64KB����Ƶ֡
#define TLV_T_STREAM_FORMAT_INFO				     200    //			����ʽ��Ϣ ,������Ƶ����,��Ƶ����

//vod
#define TLV_T_STREAM_FILE_INDEX						 213
#define TLV_T_STREAM_FILE_ATTRIBUTE				     214
#define TLV_T_STREAM_FILE_END					     0x0000FFFF

// ���� owsp_def.h �����²��䶨�� owsp Э�����������
#define TLV_T_DISCONNECT		220
#define TLV_T_SAY_BYE				221

//	¼��ط� 2015-9-7
#define	TLV_T_SEARCH_RECORD_REQ						0x014d		//	¼���ѯ����
#define	TLV_T_SEARCH_RECORD_RSP						0x014e		//	����¼���ļ�Ӧ��
#define	TLV_T_RECORD_INFO							0x014f		//	¼���ļ���Ϣ		
#define	TLV_T_PLAY_RECORD_REQ						0x0150		//	¼��ط�����
#define	TLV_T_PLAY_RECORD_RSP						0x0151		//	¼��ط�Ӧ��


/* response result */
#define _RESPONSECODE_SUCC						 0x01		//	�ɹ�
#define _RESPONSECODE_USER_PWD_ERROR			 0x02		//  �û����������
#define _RESPONSECODE_PDA_VERSION_ERROR			 0x04		//	�汾��һ��
#define _RESPONSECODE_MAX_USER_ERROR			 0x05	
#define _RESPONSECODE_DEVICE_OFFLINE			 0x06		//	�豸�Ѿ�����
#define _RESPONSECODE_DEVICE_HAS_EXIST			 0x07		//  �豸�Ѿ�����
#define _RESPONSECODE_DEVICE_OVERLOAD				 0x08		//  �豸���ܳ���(�豸æ)
#define _RESPONSECODE_INVALID_CHANNLE				 0x09		//  �豸��֧�ֵ�ͨ��
#define _RESPONSECODE_PROTOCOL_ERROR				0X0A		//Э���������
#define _RESPONSECODE_NOT_START_ENCODE			0X0B		//δ��������
#define _RESPONSECODE_TASK_DISPOSE_ERROR		0X0C		//��������̳���



//��̨������,ȡֵ��ΧΪ0~255
 typedef enum _OWSP_ACTIONCode
 {
   OWSP_ACTION_MD_STOP      = 0,            // ֹͣ�˶�
   OWSP_ACTION_ZOOMReduce=5,
   OWSP_ACTION_ZOOMADD=6,
   OWSP_ACTION_FOCUSADD=7,    //����
   OWSP_ACTION_FOCUSReduce=8,
   OWSP_ACTION_MD_UP=9,                    // ����
   OWSP_ACTION_MD_DOWN=10,              // ����
   OWSP_ACTION_MD_LEFT=11,              // ����
   OWSP_ACTION_MD_RIGHT=12,            // ����
   OWSP_ACTION_Circle_Add = 13,    //��Ȧ
   OWSP_ACTION_Circle_Reduce = 14,    //
   OWSP_ACTION_AUTO_CRUISE = 15,			//�Զ�Ѳ��
   OWSP_ACTION_GOTO_PRESET_POSITION = 16, 	//��תԤ��λ
   OWSP_ACTION_SET_PRESET_POSITION = 17, 	//����Ԥ��λ��
   OWSP_ACTION_CLEAR_PRESET_POSITION = 18, //���Ԥ��λ��
   OWSP_ACTION_ACTION_RESET = 20,

   OWSP_ACTION_MD_LEFT_UP=21,             // ����
   OWSP_ACTION_MD_LEFT_DOWN=22,              // ����
   OWSP_ACTION_MD_RIGHT_UP=23,              // ����
   OWSP_ACTION_MD_RIGHT_DOWN=24,            // ����

   OWSP_ACTION_TV_SWITCH = 128,		//�л���ƵԴ,��Ϣ����ΪINT*,1--TV, 2--SV,3--CV1, 4--CV2 
   OWSP_ACTION_TV_TUNER = 129,		//�л�Ƶ��, ��Ϣ����ΪINT*, ΪƵ����
   OWSP_ACTION_TV_SET_QUALITY  = 130,		//��������, ����,ɫ��,���Ͷ�,�ԱȶȽṹ��
 } OWSP_ACTIONCode;

//�������࣬Ŀǰֻ֧��̽ͷ������Ҳ����ATC_INFRARED
typedef enum _AlertTypeCode
{
	ATC_VIDEO = 0,//��Ƶ֡Ԥ��
	ATC_DEVICE_SERSTART = 1,	/* �豸���� */	
	ATC_MOTION = 2,						/* �ƶ���ⱨ�� */
	ATC_VIDEOLOST = 3,				/* ��Ƶ��ʧ���� */
	ATC_DISKFULL = 4,					/* Ӳ�������� */
	ATC_HIDEALARM=5,					/* ��Ƶ�ڵ����� */	
	ATC_STOP = 6,							/* ������ֹͣ */
	ATC_SDERROR = 7,         	/* SD���쳣*/
	ATC_INFRARED = 20					//������̽ͷ���������̽ͷ��
}AlertTypeCode;

//����������Ҫ���֡Ԥ�⣬������̽ͷ����ʱ��ֵͳһΪ0��Ŀǰֻ֧��̽ͷ����������������ʱ�����ͱ�������ALC_ALERT��������ֹͣʱ������ALC_STOP
typedef enum _AlertLevelCode
{
	ALC_ALERT = 0,//����������������ߣ�ͨ���û�������̽ͷ
	ALC_LEVEL1 = 10,//1�����棬AlertLevelCode��ֵԽ�󣬾��漶��Խ��
	ALC_STOP = 255//����ֹͣ������ֹͣ��Ϣ
}AlertLevelCode;



//��������  2015-9-7
typedef enum _OWSP_StreamType
{
	OWSP_STREAM_MAIN	= 0,        //����������
	OWSP_STREAM_SUB	= 1,        //���������1
	OWSP_STREAM_SUB1	= 2,        //���������2
	OWSP_STREAM_VOD	= 3,        //����¼���ļ�
	OWSP_MODE_SETTING	= 4         //Զ������ģʽ�� 
} OWSP_StreamType;

//��������
typedef enum _OWSP_StreamDataType
{
	OWSP_VIDEO_DATA	= 0,    // video data only
	OWSP_AUDIO_DATA	= 1,    // audio data only
	OWSP_MIXED_DATA	= 2     // video & audio data
} OWSP_StreamDataType;

// ���ſ�������
typedef enum _OWSP_PlayCommand
{
	PlayCommandStart  = 1,  //����
	PlayCommandPause  = 2,  //��ͣ
	PlayCommandResume = 3,  //����
	PlayCommandStop   = 4   //ֹͣ
} OWSP_PlayCommand;

/* the common packet header, must be placed in front of any packets. */
typedef struct _OwspPacketHeader
{
	u_int32 packet_length;		//length of the following packet, donot include this header
	u_int32 packet_seq;			//packet sequence �����,ÿ����һ����������
	
} OwspPacketHeader;

/////////////////////////////////////////////////////////////////////////
//For TLV 
//////////////////////////////////////////////////////////////////////////
struct _TLV_Header {
	u_int16 tlv_type;
	u_int16 tlv_len;
};
//__attribute ((packed));
typedef struct _TLV_Header  TLV_HEADER;

/* version info: remote -> streaming server.  No response need */
// TLV_T: TLV_T_VERSION_INFO_ANSWER
// TLV_L: sizeof(TLV_V_VersionInfoRequest)
typedef struct _TLV_V_VersionInfoRequest
{
	u_int16   versionMajor;		// major version
	u_int16   versionMinor;		// minor version
}TLV_V_VersionInfoRequest;

// TLV_T: TLV_T_VERSION_INFO_ANSWER
// TLV_L: sizeof(TLV_V_VersionInfoResponse)
typedef struct _TLV_V_VersionInfoResponse
{
	u_int16 result;				//result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
}TLV_V_VersionInfoResponse;

/* login request: remote -> streaming server */
typedef struct _TLV_V_LoginRequest
{
	char userName[STR_LEN_32];			//�û���, ���治�㲿��Ϊ����0      (ΪASCII�ַ���)
	char password[STR_LEN_16];			//����, ���治�㲿��Ϊ����0        (ΪASCII�ַ���) 
	u_int32 deviceId;					//�豸ID. CSģʽ���ɷ�����ͳһ����, P2Pģʽ��Ϊ�̶�ֵ
	u_int8  flag;						//should be set to 1 to be compatible with the previous version.
	u_int8  channel;					//channel
	//u_int8  reserve[2];
	u_int8	streamMode;
	u_int8	dataType;
} TLV_V_LoginRequest;


/* login response, streaming server -> remote */
typedef struct _TLV_V_LoginResponse
{
	u_int16 result;				//result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_LoginResponse;

 
/* send data request, streaming server -> remote. 
 * Now this command is ignored, the remote will send data to server actively and immidietely after logining.*/
typedef struct _TLV_V_SendDataRequest
{
	u_int32 deviceId;			//device id generating by the remote device
	u_int8  videoChannel;	
	u_int8  audioChannel;   
	u_int16 reserve;
} TLV_V_SendDataRequest;

/* send data response, remote -> streaming server */
typedef struct _TLV_V_SendDataResponse
{
	u_int16 result;			//result of send data request
	u_int16 reserve;
} TLV_V_SendDataResponse;

/* suspend sending data request, streaming server -> remote */
typedef struct _TLV_V_SuspendSendDataRequest
{
	u_int32 deviceId;			//device id generating by the remote device
	u_int8  videoChannel;
	u_int8  audioChannel; 
	u_int16 reserve;
} TLV_V_SuspendSendDataRequest;

/* suspend sending data response, remote -> streaming server */
typedef struct _TLV_V_SuspendSendDataResponse
{
	u_int16 result;			//result of send data request
	u_int16 reserve;
} TLV_V_SuspendSendDataResponse;



/* specify the format of video, this info is sent to server immidiately after StreamDataFormat*/
typedef struct _OWSP_VideoDataFormat
{
	u_int32 codecId;			//FOUR CC code����H264��
	u_int32 bitrate;			//bps
	u_int16 width;				//image widht
	u_int16 height;				//image height
	u_int8 framerate;			//fps
	u_int8 colorDepth;			//should be 24 bits 
	u_int16 reserve;		

} OWSP_VideoDataFormat;

/* specify the format of audio, this info is sent to server immidiately after StreamDataFormat or VideoDataFormat*/
typedef struct _OWSP_AudioDataFormat
{
	u_int32 samplesPerSecond;		//samples per second
	u_int32 bitrate;			//bps
	u_int16 waveFormat;			//wave format, such as WAVE_FORMAT_PCM,WAVE_FORMAT_MPEGLAYER3
	u_int16 channelNumber;		//audio channel number
	u_int16 blockAlign;			//block alignment defined by channelSize * (bitsSample/8)
	u_int16 bitsPerSample;			//bits per sample
	u_int16 frameInterval;		//interval between frames, in milliseconds
	u_int16 reserve;

} OWSP_AudioDataFormat;

/* this format should be sent to the server before any other stream data,
 Plus if any format of video/audio has changed, it should send this info to server at the first time.
 followed by VideoDataFormat/AudioDataFormat*/
typedef struct _TLV_V_StreamDataFormat
{
	u_int8 videoChannel;					//��Ƶͨ����
	u_int8 audioChannel;					//��Ƶͨ����
	u_int8 dataType;							//����������, ȡֵ��StreamDataType
	u_int8 reserve;								//����
	OWSP_VideoDataFormat videoFormat;	//��Ƶ��ʽ
	OWSP_AudioDataFormat audioFormat;  //��Ƶ��ʽ
} TLV_V_StreamDataFormat;


/* ��Ƶ֡��Ϣ TLV */
typedef struct _TLV_V_VideoFrameInfo
{
	u_int8  channelId;			//ͨ��ID
	u_int8  reserve;				//����
	u_int16 checksum;				//У���.ĿǰΪ0δ��
	u_int32 frameIndex;			//��Ƶ֡���
	u_int32 time;				    //ʱ���.
} TLV_V_VideoFrameInfo;

//֮������Ƶ����TLV, V��������Ƶ������Raw Data.

/* ��չ��Ƶ֡��Ϣ TLV, ����Ƶ����>64Kʱʹ�� */
typedef struct _TLV_V_VideoFrameInfoEx
{
	u_int8  channelId;			//ͨ��ID
	u_int8  reserve;				//����
	u_int16 checksum;				//У���.ĿǰΪ0δ��
	u_int32 frameIndex;			//��Ƶ֡���
	u_int32 time;				    //ʱ���.
	u_int32 dataSize;				//��Ƶ���ݳ���
} TLV_V_VideoFrameInfoEx;

//֮�������ɸ���Ƶ����TLV, V��������Ƶ������Raw Data.


/* ��Ƶ��Ϣ TLV */
typedef struct _TLV_V_AudioInfo
{
	u_int8 channelId;			//channel id
	u_int8  reserve;			//����
	u_int16 checksum;			//checksum of audio data.
	u_int32 time;					// specify the time when this audio data is created.
} TLV_V_AudioInfo;

//֮������Ƶ����TLV, V���־�����Ƶ������Raw Data.

/* ��չ����Э��, ������̨��TV���� */
typedef struct _TLV_V_ControlRequest
{
		u_int32 deviceId;			// device id generating by the remote device
		u_int8  channel;			// channel id 
		u_int8  cmdCode;			// ���������֣��μ�_PTZCode
		u_int16 size;				// ���Ʋ������ݳ���,���size==0 ��ʾ�޿��Ʋ���
} TLV_V_ControlRequest;

//u_int8 * data;		//array of data followed.
// size = sizeof(PTZArgData);
//������������ң�ǣ�浽�ٶȵĻ�����ˮƽ�ٶ�arg1����ֱ�ٶ�arg2��
//�����Ԥ��λ�Ļ��������ڼ���Ԥ��λʹ��arg1����
//��������Ԥ��λ�������ڼ���Ԥ��λʹ��arg1���������0xffffffff��ʾ���ȫ��
//������Զ�Ѳ����arg1=1��ʾ������0��ʾֹͣ
typedef struct _ControlArgData
{		
		u_int32 arg1;
		u_int32 arg2;
		u_int32 arg3;
		u_int32 arg4;
} ControlArgData;

/* ��̨������Ӧ */
typedef struct _TLV_V_ControlResponse
{
	u_int16 result;				//result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_ControlResponse;

/* 
  ͨ������Э�� 
  Streaming server -> Device
*/
typedef struct _TLV_V_ChannelRequest
{
	u_int32 deviceId;
	u_int8  sourceChannel;	//Դͨ��ID
	u_int8  destChannel;		//�л���Ŀ��ͨ��ID
	u_int8	reserve[2];		
} TLV_V_ChannelRequest;

/*
  ͨ��������Ӧ
  Device -> Streaming server
  message: MSG_CMD_CHANNEL_RESPONSE
*/
typedef struct _TLV_V_ChannelResponse
{
  u_int16 result;					//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
  u_int8	currentChannel;	//�����֧�ֵ�ͨ�����򷵻ص�ǰͨ����
	u_int8 reserve;	
} TLV_V_ChannelResponse;


/* 
	ͨ������Э�� 
  Streaming server -> Device 
  message: MSG_CMD_CHANNEL_SUSPEND
*/
typedef struct _TLV_V_ChannelSuspendRequest
{
	u_int8  channelId;	//Chanel id
	u_int8  reserve[3];	
} TLV_V_ChannelSuspendRequest;

/*
  ͨ��������Ӧ
  Device -> Streaming server
  message: MSG_CMD_SUSPEND_RESPONSE
*/
typedef struct _TLV_V_ChannelSuspendResponse
{
  u_int16 result;				//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;	
} TLV_V_ChannelSuspendResponse;


/*
  ������
  Device -> Streaming server
  message: MSG_CMD_DEVICE_KEEP_ALIVE
*/
typedef struct _TLV_V_KeepAliveRequest
{
	u_int8  channelID;	//Channel id
	u_int8  reserve[3];	
} TLV_V_KeepAliveRequest;

/*
  ��������Ӧ
  Streaming server -> Device
  message: MSG_CMD_KEEP_ALIVE_ANSWER
*/
typedef struct _TLV_V_KeepAliveResponse
{
  u_int16 result;				//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;	
} TLV_V_KeepAliveResponse;

/* ��չ����Э�飬�豸���������� */
typedef struct _TLV_V_AlertRequest
{
  u_int32  	deviceId;   	// device id generating by the remote device
  u_int8   	channelId;   	// channel id 
  u_int8  	alertType;   	// �������࣬�μ� _AlertTypeCode
  u_int8  	alertLevel;   // �������𣬲μ� _AlertLevelCode
	u_int8  	reserve;    	//����
  u_int8   	localTime[14];			//����ʱ����ʱ���ַ�������ʽΪyyyymmddhhmmss,��"20080919132059"����2008��9��19��13��20��59�룬ʱ�侫��Ϊ��
  u_int16  	size;     		// array of data size followed��default =  0
} TLV_V_AlertRequest;

/* ����������Ӧ�����������͵��豸 */
typedef struct _TLV_V_AlertResponse
{
 u_int16 result;    //result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
 u_int16 reserve;
} TLV_V_AlertResponse;


/* ���ڶ��� */
typedef struct _OWSP_DATE
{
	u_int16 	m_year;			//��,2009
	u_int8		m_month;		//��,1-12
	u_int8		m_day;			//��,1-31
}OWSP_DATE;

/* ʱ�䶨�� */
typedef struct _OWSP_TIME
{
	u_int8		m_hour;			//0-24
	u_int8		m_minute;		//0-59
	u_int8		m_second;		//0-59
	u_int16		m_microsecond;	//����	0-1000
}OWSP_TIME;


/* DVS�����豸��Ϣ */
typedef struct _TLV_V_DVSInfoRequest
{
	char		companyIdentity[STR_LEN_16];			//��˾ʶ����,���16���ַ�,���治�㲿��Ϊ����0      (ΪASCII�ַ���)
	char   		equipmentIdentity[STR_LEN_16];			//�豸ʶ����,���ֶ���ΪDVS�������ַ,��MAC��ַ,���治�㲿��Ϊ����0  (ΪASCII�ַ���)
	char		equipmentName[STR_LEN_16];				//�豸����,���16���ַ�,���治�㲿��Ϊ����0        (ΪASCII�ַ���)
	char		equipmentVersion[STR_LEN_16];			//�豸������汾,���16���ַ�, ���治�㲿��Ϊ����0 (ΪASCII�ַ���)
	OWSP_DATE	equipmentDate;							//�豸�ĳ�������20090120 
	u_int8		channleNumber;			//�豸֧�ֶ��ٸ�ͨ��
	u_int8		reserve1;						//����
	u_int8		reserve2;						//����
	u_int8		reserve3;						//����
} TLV_V_DVSInfoRequest;

/* DVS�����豸��ϢӦ�� */
typedef struct _TLV_V_DVSInfoResponse
{
	u_int16 result;    //result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_DVSInfoResponse;


/* �ֻ������豸��Ϣ */
typedef struct _TLV_V_PhoneInfoRequest
{
	u_int8   	equipmentIdentity[STR_LEN_16];		//�豸ʶ����,���ֶ���ΪDVS�������ַ,��MAC��ַ
	u_int8   	equipmentOS[STR_LEN_16];						//�ֻ��Ĳ���ϵͳ
	u_int8		reserve1;						//����
	u_int8		reserve2;						//����
	u_int8		reserve3;						//����
	u_int8		reserve4;						//����
} TLV_V_PhoneInfoRequest;

/* �ֻ������豸��ϢӦ�� */
typedef struct _TLV_V_PhoneInfoResponse
{
	u_int16 result;    //result of login request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;
} TLV_V_PhoneInfoResponse;

/////////////////////////////////////////////////////////////////////////
//For TLV 
//////////////////////////////////////////////////////////////////////////
struct _TLV {
    u_int16 tlv_type;
    u_int16 tlv_len;
    u_int8  tlv_data[0];
};				//	 __attribute ((packed))
typedef struct _TLV  TLV;


#define FILEFLAG	"DSV"
//////////////////////////////////////////////////////////////////////////
//For vod streaming  only Keyframe 
//////////////////////////////////////////////////////////////////////////
typedef struct _TLV_V_FileAttributeData
{
	u_int32 totalframes;
	u_int32 totaltimes;
}TLV_V_FileAttributeData;

typedef struct _TLV_V_StreamIndexDataHeader
{
	u_int32 count;			//
	u_int32 reserve;		//���ļ�
	u_int32 datasize;		//
}TLV_V_StreamIndexDataHeader;

typedef struct _TLV_V_StreamIndexData
{
	u_int32 timestamp;
	u_int32 pos;		//���ļ�
}TLV_V_StreamIndexData;

typedef struct _TLV_V_StreamEndData
{
	u_int32 timestamp;
	u_int16 result;				//result of request. _RESPONSECODE_SUCC - succeeded, others - failed
	u_int16 reserve;	
} TLV_V_StreamEndData;

typedef struct _TLV_V_StreamFileDataHeader
{
	u_int32 timestamp;
}TLV_V_StreamFileDataHeader;


#pragma pack(pop)

//////////////////////////////////////////////////////////////////////////
//	2015-9-7	¼���ļ��ط�
//////////////////////////////////////////////////////////////////////////

#pragma pack(push)
#pragma pack(1)


typedef struct _OWSP_DateTime
{
	u_int16 m_year;			//��,2009
	u_int8	m_month;		//��,1-12
	u_int8	m_day;			//��,1-31
	u_int8	m_hour;			//0-24
	u_int8	m_minute;		//0-59
	u_int8	m_second;		//0-59
} OWSP_DateTime;

typedef struct _TLV_V_SearchRecordRequest
{
	u_int32 deviceId;           //�豸��ţ�Ĭ��Ϊ0��
	u_int8  channel;           //ͨ����
	u_int8  recordTypeMask;    //¼���������� 0x01 = �������澯¼��, 0x02 = �ƶ����¼��, 0x04 = ��ʱ¼��, 0x08 = �ֶ�¼��
	u_int8	count;            //��������¼����
	OWSP_DateTime startTime;   //��ѯ��ʼʱ��
	OWSP_DateTime endTime;   //��ѯ��ֹʱ��
	u_int8  reserve[3];
} TLV_V_SearchRecordRequest;


typedef struct _TLV_V_SearchRecordResponse
{
	u_int8	result;                //���
	u_int8	count;                //��ѯ�����¼��
	u_int8	reserve;
} TLV_V_SearchRecordResponse;

typedef struct _TLV_V_RecordInfo
{
	u_int32          deviceId;
	OWSP_DateTime	startTime;
	OWSP_DateTime	endTime;
	u_int8	        channel;
	u_int8           recordTypeMask;    //¼���������� 0x01 = �������澯¼��, 0x02 = �ƶ����¼��, 0x04 = ��ʱ¼��, 0x08 = �ֶ�¼��;
	u_int8           reserve[2];
} TLV_V_RecordInfo;


typedef struct _TLV_V_PlayRecordRequest
{
	u_int32       deviceId;
	OWSP_DateTime	startTime;         //��ͣ��������ֹͣ������Ч
	u_int8        channel;
	u_int8        command;            //�طſ�������
	u_int8        reserve;

} TLV_V_PlayRecordRequest;


typedef struct _TLV_V_PlayRecordResponse
{
	u_int8	result;
	u_int8	reserve;
} TLV_V_PlayRecordResponse;

#pragma pack(pop)

#endif
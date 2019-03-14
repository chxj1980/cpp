// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FFPLAYSDL2_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FFPLAYSDL2_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FFPLAYSDL2_EXPORTS
#define FFPLAYSDL2_API __declspec(dllexport)
#else
#define FFPLAYSDL2_API __declspec(dllimport)
#endif

// This class is exported from the FfplaySdl2.dll
class FFPLAYSDL2_API CFfplaySdl2 {
public:
	CFfplaySdl2(void);
	// TODO: add your methods here.
};

extern FFPLAYSDL2_API int nFfplaySdl2;

FFPLAYSDL2_API int fnFfplaySdl2(void);


//�����Ĳ��������� SDL 2.0, �ṩһ���̣߳��������е��¼���Events����ȡ����Ӧ����
//֧�ִ���������ڣ��ṩһ����ʱˢ���̸߳������д�������Ƶ�Ĳ���



//	
FFPLAYSDL2_API int player_init();

FFPLAYSDL2_API int player_unInit();

FFPLAYSDL2_API int player_stream_open(char * filename, HWND hwnd);


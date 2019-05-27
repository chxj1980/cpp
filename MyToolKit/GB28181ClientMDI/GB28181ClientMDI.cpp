
// GB28181ClientMDI.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"



#include "GB28181ClientMDI.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "GB28181ClientMDIDoc.h"
#include "GB28181ClientMDIView.h"

#include "RealplayView.h"
#include "PlaybackView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////

int Dll_search_recordfile_response_Callback(int commandport, int type, int result, 
											sipd_recordinfo_rsp_basic_info* pStateBasicInfo, sipd_file_item* pFileItem)
{
	HWND hwnd = NULL;
	{
		JMutexAutoLock lock(g_mtxNet);
		if(g_mapNet2Hwnd.count(commandport)>0)
			hwnd = g_mapNet2Hwnd[commandport];
	}

	if(hwnd)
	{
		if(type==1)
		{
			// ��������

			sipd_recordinfo_rsp_basic_info * pBasicInfo = new sipd_recordinfo_rsp_basic_info;
			memcpy(pBasicInfo, pStateBasicInfo, sizeof(sipd_recordinfo_rsp_basic_info));

			sipd_file_item * pItem = new sipd_file_item[pBasicInfo->RecordListNum];
			for(int i=0; i< pBasicInfo->RecordListNum; i++)
			{
				memcpy(pItem + i, pFileItem + i, sizeof(sipd_file_item));
			}

			::PostMessage(hwnd, WM_USER_RECORDFILE_DATA, (WPARAM)pBasicInfo, (LPARAM)pItem);
		}
		else
		{
			::PostMessage(hwnd, WM_USER_RECORDFILE_COMM, (WPARAM)result, 0);
		}
	}
	return 0;
}

int Dll_cataloginfo_response_Callback(int commandport, int type, int result, 
									  sipd_catalog_rsp_basic_info* pCataBasicInfo, sipd_catalog_item* pCataItem)
{
	HWND hwnd = NULL;
	{
		JMutexAutoLock lock(g_mtxNet);
		if(g_mapNet2Hwnd.count(commandport)>0)
			hwnd = g_mapNet2Hwnd[commandport];
	}
	if(hwnd)
	{
		if(type==1)
		{
			// ��������
			
			sipd_catalog_rsp_basic_info * pBasicInfo = new sipd_catalog_rsp_basic_info;
			memcpy(pBasicInfo, pCataBasicInfo, sizeof(sipd_catalog_rsp_basic_info));

			sipd_catalog_item * pItem = new sipd_catalog_item[pBasicInfo->DeviceList_Num];
			for(int i=0; i< pBasicInfo->DeviceList_Num; i++)
			{
				memcpy(pItem + i, pCataItem + i, sizeof(sipd_catalog_item));
			}

			::PostMessage(hwnd, WM_USER_CATALOG_DATA, (WPARAM)pBasicInfo, (LPARAM)pItem);
		}
		else
		{
			::PostMessage(hwnd, WM_USER_CATALOG_COMM, (WPARAM)result, 0);
		}
	}
	
	return 0;
}


int Dll_Call_Response_Callback(int netport, int type, int result, unsigned char * pBuffer, int nBufSize)
{
	static FILE * fp = NULL;
	if(type ==0 )
	{
	
		HWND hwnd = NULL;
		{
			/*JMutexAutoLock lock(g_mtxNet);
			if(g_mapNet2Hwnd.count(netport)>0)
				hwnd = g_mapNet2Hwnd[netport];*/
		}
		if(hwnd)
		{
			::PostMessage(hwnd, WM_USER_CALL_RESP, (WPARAM)result, 0);
		}
	}
	else if(type == 1)
	{
		//	�������ص�
		int playerid = -1;
		{
			JMutexAutoLock lock(g_mtxNet);
			if(g_mapNet2Player.count(netport)>0)
				playerid = g_mapNet2Player[netport];
		}
		if(playerid > 0)
		{
			H264_PARAM * pHeader = (H264_PARAM *)pBuffer;
			if(pHeader->knd==0)
			{
				/* �ص������� pts �� us Ϊ��λ�� ����������Ҫ�� time_base Ϊ��λ�� �ں���avpriv_set_pts_info �����õ� */
				/* ����Ľ�� ÿ�� new_pts ʱ���Ӧ����� 3600 ���� */

				u_int64 new_pts = pHeader->pts/(1000000.0/90000);
				stringstream ss;
				ss << "Video  pts = " << pHeader->pts << ", new_pts = " <<  new_pts << ", playerid = " << playerid; 
				//LOG4CPLUS_DEBUG(g_Logger, ss.str() );

				player_stream_input_data(playerid, PLAYER_MEDIA_TYPE_VIDEO, pBuffer+ 72, nBufSize-76, new_pts /*0x8000000000000000*/);
			}
			else if(pHeader->knd!=10)
			{
				u_int64 new_pts = pHeader->pts/(1000000.0/8000);
				stringstream ss;
				ss << "Audio  pts = " << pHeader->pts << ", new_pts = " <<  new_pts << ", playerid = " << playerid;
				//LOG4CPLUS_DEBUG(g_Logger, ss.str() );

				player_stream_input_data(playerid, PLAYER_MEDIA_TYPE_AUDIO, pBuffer+ 72, nBufSize-76, new_pts);
			}

		}
		else
		{
			/*if(fp==NULL)
			{
				fp = fopen("gb_28181_client.snv", "wb");
			}
			if(fp)
				fwrite(pBuffer, 1, nBufSize, fp);*/
		}		
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// CGB28181ClientMDIApp

BEGIN_MESSAGE_MAP(CGB28181ClientMDIApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGB28181ClientMDIApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CGB28181ClientMDIApp ����

CGB28181ClientMDIApp::CGB28181ClientMDIApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CGB28181ClientMDIApp ����

CGB28181ClientMDIApp theApp;


// CGB28181ClientMDIApp ��ʼ��

BOOL CGB28181ClientMDIApp::InitInstance()
{

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


	//////////////////////////////////////////////////////////////////////////

	g_mtxNet.Init();

	//	��ʼ��log4cplus
	PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplus.properties"));	
	g_Logger =  Logger::getInstance(LOG4CPLUS_TEXT("Test_28181"));

	SIPD_GATEWAY_CFG cfg;
	memset(&cfg, 0, sizeof(SIPD_GATEWAY_CFG));
	strncpy(cfg.local_domain_name, "3402000000", MAX_SIPD_DEVICE_ID_LEN);
	strncpy(cfg.local_domain_id, LOCAL_DOMAIN_ID, MAX_SIPD_DEVICE_ID_LEN);		//	202 ý��ַ�������
	cfg.local_port = LOCAL_PORT;
	strncpy(cfg.local_ip, LOCAL_IP, MAX_SIPD_NORMAL_LEN);			//	�˴����� ����ӳ�� IP 
	strncpy(cfg.local_gateway, "10.18.72.254", MAX_SIPD_NORMAL_LEN);

	strncpy(cfg.upper_server_name, "35010400", MAX_SIPD_DEVICE_ID_LEN);
	strncpy(cfg.upper_server_id, "35010400002000000005", MAX_SIPD_DEVICE_ID_LEN);		//	200 ��С������Ʒ�����
	strncpy(cfg.upper_server_ip, "10.18.72.35", MAX_SIPD_NORMAL_LEN);
	//strncpy(cfg.upper_server_ip, "192.168.1.109", MAX_SIPD_NORMAL_LEN);
	cfg.upper_server_port = 5068;
	strncpy(cfg.register_upper_server_passwd, "12345678", MAX_SIPD_NORMAL_LEN);

	cfg.register_keepalive = 3600;
	cfg.keepalive_internal = 60;


	DLL_Init(&cfg);
	//Register_Dll_Register_Request(Dll_Register_Request_Callback);
	Register_Dll_cataloginfo_response(Dll_cataloginfo_response_Callback);

	//Register_Dll_deviceinfo_response(Dll_deviceinfo_response_Callback);
	//Register_Dll_stateinfo_response(Dll_stateinfo_response_Callback);

	//Register_Dll_Alarm_Request(Dll_Alarm_Request_Callback);

	Register_Dll_search_recordfile_response(Dll_search_recordfile_response_Callback);
	//Register_Dll_ptz_response(Dll_ptz_response_Callback);

	Register_Dll_Call_Response(Dll_Call_Response_Callback);

	//	��ʼ�� ������
	player_init();


	//////////////////////////////////////////////////////////////////////////

	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_GB28181ClientMDTYPE,
		RUNTIME_CLASS(CGB28181ClientMDIDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CGB28181ClientMDIView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_GB28181ClientMDTYPE,
		RUNTIME_CLASS(CGB28181ClientMDIDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CRealplayView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(IDR_GB28181ClientMDTYPE,
		RUNTIME_CLASS(CGB28181ClientMDIDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CPlaybackView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������


	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//	�޸��������һ�����ͽ������ĵ�
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CGB28181ClientMDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CGB28181ClientMDIApp �Զ������/���淽��

void CGB28181ClientMDIApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CGB28181ClientMDIApp::LoadCustomState()
{
}

void CGB28181ClientMDIApp::SaveCustomState()
{
}



CDocTemplate* CGB28181ClientMDIApp::GetCurrDocTemplate(CView * pView)
{
	ASSERT_VALID(pView);
	// CDocTemplate* pDocTemp = NULL;
	CMvDocTemplate * pDocTemp = NULL;


	// Get the first document template position and iterate through the document template
	POSITION posDocTemplate = GetFirstDocTemplatePosition();
	while (posDocTemplate != NULL)
	{
		pDocTemp = (CMvDocTemplate *)GetNextDocTemplate(posDocTemplate);
		ASSERT_VALID(pDocTemp);

		CRuntimeClass * pClassView = pDocTemp->GetCurrView();		
		if(pView->IsKindOf(pClassView))	
		{
			return pDocTemp;
		}	
	}
	return NULL;
}

// CGB28181ClientMDIApp ��Ϣ�������




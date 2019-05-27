
// CxfSiTest.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "CxfSiTest.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "CxfSiTestDoc.h"
#include "CxfSiTestView.h"

#include "UsageEnvironment.h"
#include "GbUsageEnvironment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCxfSiTestApp

BEGIN_MESSAGE_MAP(CCxfSiTestApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCxfSiTestApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CCxfSiTestApp ����

CCxfSiTestApp::CCxfSiTestApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CCxfSiTestApp ����

CCxfSiTestApp theApp;


// CCxfSiTestApp ��ʼ��

BOOL CCxfSiTestApp::InitInstance()
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

	// ��ʼ��log4cplus
	PropertyConfigurator::doConfigure("log4cplus.properties");

	g_strLocalDomainID = "35010400002000000005";

	//	���� Sip ����
	SIPD_GATEWAY_CFG cfg;
	memset(&cfg, 0, sizeof(SIPD_GATEWAY_CFG));
	strncpy(cfg.local_domain_name, "35010400", MAX_SIPD_DEVICE_ID_LEN);
	strncpy(cfg.local_domain_id, g_strLocalDomainID.c_str(), MAX_SIPD_DEVICE_ID_LEN);
	cfg.local_port = 5068;
	/*strncpy(cfg.local_ip, "192.168.1.105", MAX_SIPD_NORMAL_LEN);
	strncpy(cfg.local_gateway, "192.168.1.1", MAX_SIPD_NORMAL_LEN);*/
	strncpy(cfg.local_ip, "10.18.72.35", MAX_SIPD_NORMAL_LEN);
	strncpy(cfg.local_gateway, "10.18.72.254", MAX_SIPD_NORMAL_LEN);

	strncpy(cfg.upper_server_name, "43000000", MAX_SIPD_DEVICE_ID_LEN);
	strncpy(cfg.upper_server_id, "43000000002000000000", MAX_SIPD_DEVICE_ID_LEN);
	strncpy(cfg.upper_server_ip, "10.18.72.35", MAX_SIPD_NORMAL_LEN);
	//strncpy(cfg.upper_server_ip, "192.168.1.109", MAX_SIPD_NORMAL_LEN);
	cfg.upper_server_port = 5060;
	strncpy(cfg.register_upper_server_passwd, "12345678", MAX_SIPD_NORMAL_LEN);
	cfg.register_keepalive = 3600;
	cfg.keepalive_internal = 60;

	//	���� sip ��Ϣ����
	CGbUsageEnvironment::getInstance()->init(cfg);

	sipd_init(&cfg);

	

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CxfSiTestTYPE,
		RUNTIME_CLASS(CCxfSiTestDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CCxfSiTestView));
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
void CCxfSiTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCxfSiTestApp �Զ������/���淽��

void CCxfSiTestApp::PreLoadState()
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

void CCxfSiTestApp::LoadCustomState()
{
}

void CCxfSiTestApp::SaveCustomState()
{
}

// CCxfSiTestApp ��Ϣ�������




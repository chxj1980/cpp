
// CninfoPDF.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CninfoPDF.h"
#include "TabDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCninfoPDFApp

BEGIN_MESSAGE_MAP(CCninfoPDFApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCninfoPDFApp ����

CCninfoPDFApp::CCninfoPDFApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCninfoPDFApp ����

CCninfoPDFApp theApp;


// CCninfoPDFApp ��ʼ��

BOOL CCninfoPDFApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
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

	AfxEnableControlContainer();

	if( ! ::AfxInitRichEdit() )
	{
		return FALSE ;
	}

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//////////////////////////////////////////////////////////////////////////
	//	���� MYSQL ���ݿ�����ӳ�, ���� GBK �ͻ���

	stringstream ss;
	try{
		string connectString_ =  "dbname=stock  port=3366   host=127.0.0.1 user=root  charset=gbk ";
		backend_factory const &backEndFactory_ = *soci::factory_mysql();

		for (std::size_t i = 0; i != MYSQL_POOL_SIZE; ++i)
		{
			session & sql = g_MysqlPool.at(i);
			sql.open(backEndFactory_, connectString_);
		}
	}catch (std::exception const & e)
	{
		ss.str("");
		ss << "Error ����ʼ�� Mysql ���ӳ�ʧ�ܣ����������ݷ�ʽ�� Mysql ���ݿ�";
		ss << e.what() << ' \r\n';
		AfxMessageBox(ss.str().c_str());
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////

	g_friso = friso_new();
	g_config = friso_new_config();

	if ( friso_init_from_ifile(g_friso, g_config, "friso.ini") != 1 ) {
		printf("fail to initialize friso and config.");
		return FALSE;
	}
	

	//////////////////////////////////////////////////////////////////////////
	

	CTabDialog dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	friso_free_config(g_config);
	friso_free(g_friso);
	
	TerminateProcess(GetCurrentProcess(), 1);  

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


CWinThread * CCninfoPDFApp::StartWorkerThread(AFX_THREADPROC pfnThreadProc, LPVOID pParam)
{
	CWinThread * pThread = AfxBeginThread(pfnThreadProc, pParam, \
		/*THREAD_PRIORITY_BELOW_NORMAL*/ THREAD_PRIORITY_NORMAL, 1 * 1024 * 1024, CREATE_SUSPENDED);
	pThread->m_bAutoDelete = FALSE;
	pThread->ResumeThread();

	return pThread;
}
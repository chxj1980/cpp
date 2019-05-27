// TabDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CninfoPDF.h"
#include "TabDialog.h"

#include "CompileUtf8RangeDlg.h"
#include "CninfoPDFDlg.h"

// CTabDialog �Ի���

IMPLEMENT_DYNAMIC(CTabDialog, CDialog)

CTabDialog::CTabDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTabDialog::~CTabDialog()
{
}

void CTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}


BEGIN_MESSAGE_MAP(CTabDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_NOTIFY_FROM_TRAY,OnNotifyIcon)
	ON_MESSAGE(WM_USER_LOG_1,OnUserLogWParam_1)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTabDialog ��Ϣ�������

BOOL CTabDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//////////////////////////////////////////////////////////////////////////
	//	�����Զ����� PDF �������߳�

	((CCninfoPDFApp *)AfxGetApp())->StartWorkerThread(AutoDownloadThreadFunc, NULL);	

	ToTray();

	//	����ʱ���ش���
	SetTimer(1, 100, 0);


	//////////////////////////////////////////////////////////////////////////
	CCompileUtf8RangeDlg * dialog1 = new CCompileUtf8RangeDlg;
	CCninfoPDFDlg * dialog2 = new CCninfoPDFDlg;

	m_TabCtrl.AddPage("�޳���PDF ����", dialog2, IDD_CNINFOPDF_DIALOG);
	m_TabCtrl.AddPage("������ʽ", dialog1, IDD_COMPILE_UTF8_RANGE);
	m_TabCtrl.Show();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTabDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTabDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//////////////////////////////////////////////////////////////////////////
//	��С�������̴���

void CTabDialog::ToTray()
{ 
	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(NOTIFYICONDATA);
	nid.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nid.uID = IDR_MAINFRAME;
	nid.hWnd=m_hWnd;
	lstrcpy(nid.szTip,_T("�޳��� PDF ����"));
	nid.uCallbackMessage= WM_NOTIFY_FROM_TRAY;
	nid.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD,&nid);
}


LRESULT CTabDialog::OnNotifyIcon(WPARAM wParam,LPARAM IParam)
{
	if ((IParam == WM_LBUTTONDOWN) || (IParam == WM_RBUTTONDOWN))
	{ 
		//ModifyStyleEx( WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
		ModifyStyleEx(0,WS_EX_TOPMOST);
		ShowWindow(SW_SHOW);
		this->UpdateWindow();
		//Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//��������ͼ��
	}
	return 0;
}

void CTabDialog::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;
	nid.uCallbackMessage= WM_NOTIFY_FROM_TRAY;			//�Զ������Ϣ����
	nid.hIcon= AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	strcpy(nid.szTip,"�޳��� PDF ����");				//��Ϣ��ʾ��Ϊ���ƻ��������ѡ�
	Shell_NotifyIcon(NIM_DELETE,&nid);					//��������ɾ��ͼ��
}

void CTabDialog::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	DeleteTray();
}

void CTabDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	switch(nID)
	{
	case SC_MINIMIZE:
		ShowWindow(SW_HIDE);
		break;
	case SC_CLOSE:
		{
			int nRes = AfxMessageBox(_T("������ɺ���Զ��رգ�ȷ�������˳���"), MB_OKCANCEL | MB_ICONQUESTION);
			if(nRes == IDOK)
				CDialog::OnSysCommand(nID, lParam);
		}
		break;
	default:
		CDialog::OnSysCommand(nID, lParam);
		break;
	}


	//CDialog::OnSysCommand(nID, lParam);
}

void CTabDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);

	KillTimer(1);

	CDialog::OnTimer(nIDEvent);
}


//////////////////////////////////////////////////////////////////////////



LRESULT CTabDialog::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;
	int		logType = (int)lParam;

	if (CMessageString::IsStringValid(pString))
	{
		string strMsg = string(pString->GetBuffer());
		delete pString;
	
		if(strMsg.find("�������")!=string::npos)
		{
			//this->EndDialog(IDOK);
		}
		else
		{
			m_TabCtrl.ProcessMessage(strMsg);
		}
	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}
void CTabDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

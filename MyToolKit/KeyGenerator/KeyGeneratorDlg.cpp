
// KeyGeneratorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KeyGenerator.h"
#include "KeyGeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKeyGeneratorDlg �Ի���

CKeyGeneratorDlg *g_Maindlg=NULL; 


CKeyGeneratorDlg::CKeyGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyGeneratorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SET_WNDNO, OnShowStepWnd)
	ON_MESSAGE(WM_CLOSE_WND, OnCloseWindow)
	ON_MESSAGE(WM_GET_SLC, OnGetSLC)
END_MESSAGE_MAP()


// CKeyGeneratorDlg ��Ϣ�������

BOOL CKeyGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CenterWindow();
	g_Maindlg =this;

	if (step1.GetSafeHwnd()==NULL)
	{
		step1.Create(IDD_DLG_STEP1,this);
	}
	if (step2.GetSafeHwnd()==NULL)
	{
		step2.Create(IDD_DLG_STEP2,this);
	}
	if (step3.GetSafeHwnd()==NULL)
	{
		step3.Create(IDD_DLG_STEP3,this);
	}	

	ShowStepWnd(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKeyGeneratorDlg::OnPaint()
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
HCURSOR CKeyGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKeyGeneratorDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	int nWnd = 1;
	::SendMessage(g_Maindlg->m_hWnd,WM_SET_WNDNO,(WPARAM)&nWnd,0);

}




HRESULT CKeyGeneratorDlg::OnShowStepWnd(WPARAM wParam, LPARAM lParam)
{
	int nWndNo = *(int*)wParam;

	ShowStepWnd(nWndNo);
	return 0;
}

HRESULT CKeyGeneratorDlg::OnCloseWindow(WPARAM wParam, LPARAM lParam)
{
	CDialog::OnCancel();
	return 0;
}

HRESULT CKeyGeneratorDlg::OnGetSLC(WPARAM wParam, LPARAM lParam)
{
	unsigned char _src[512]={0};
	unsigned char _des[512]={0};
	unsigned char _key[512]={0};



	FILE *fpIni;	
	char g_szWorkDir[MAX_PATH]={0};
	char szFileName[MAX_PATH]={0};
	CString strInfo;
	CString _srcinfo;
	CString msg;

	GetModuleFileName(NULL,g_szWorkDir,MAX_PATH); 
	(_tcsrchr(g_szWorkDir,'\\'))[1] = 0; 
	g_szWorkDir[strlen(g_szWorkDir)-1] = 0;

	sprintf(szFileName, "%s\\DLK.ini", g_szWorkDir);

	//����ļ������򸲸�,�������򴴽�
	fpIni = fopen(szFileName,"w");

	if(fpIni == NULL)
	{
		fclose(fpIni);
		AfxMessageBox("���ļ�ʧ��");
		return -1;
	}

	// ��ȡ�������ڣ���Ϊ Key
	struct tm  curr_tm;
	time_t nowTime = time(NULL);
	localtime_s(&curr_tm, &nowTime);
	_snprintf ((char *)_key, 255, "%4d%02d%02d", 1900 + curr_tm.tm_year, curr_tm.tm_mon+1, curr_tm.tm_mday);


	//��SLCд��
	strInfo.Format("$SLC\r\n");
	fwrite(strInfo,1,strlen(strInfo),fpIni);
	/*strInfo.Format("%s\r\n",step1.m_strSlc);*/

	sprintf((char*)_src,"%s",step1.m_strSlc);
	memset(_des,0,512);
	EncryptData(_des,_src,_key);
	strInfo.Format("%s\r\n",_des);
	fwrite(strInfo,1,strlen(strInfo),fpIni);

	//��MAC(���)ѭ������

	strInfo.Format("$MAC\r\n");
	fwrite(strInfo,1,strlen(strInfo),fpIni);

	POSITION pos = step2.listMac.GetHeadPosition();
	while(pos)
	{
		_srcinfo =step2.listMac.GetNext(pos);
		sprintf((char*)_src,"%s",_srcinfo);
		memset(_des,0,512);
		EncryptData(_des,_src,_key);
		strInfo.Format("%s\r\n",_des);
		fwrite(strInfo,1,strlen(strInfo),fpIni);
		Sleep(50);
	}

	//���豸ID(���)ѭ������
	strInfo.Format("$ID\r\n");
	fwrite(strInfo,1,strlen(strInfo),fpIni);

	pos = step3.listDVID.GetHeadPosition();
	while(pos)
	{
		_srcinfo =step3.listDVID.GetNext(pos);
		sprintf((char*)_src,"%s",_srcinfo);
		memset(_des,0,512);
		EncryptData(_des,_src,_key);
		strInfo.Format("%s\r\n",_des);
		fwrite(strInfo,1,strlen(strInfo),fpIni);
		Sleep(50);
	}
	fclose(fpIni);

}

void CKeyGeneratorDlg::ShowStepWnd(int nStep)
{
	switch(nStep)
	{
	case 0:
		g_Maindlg->ShowWindow(SW_SHOW);
		step1.ShowWindow(SW_HIDE);
		step2.ShowWindow(SW_HIDE);
		step3.ShowWindow(SW_HIDE);
		break;
	case 1:
		g_Maindlg->ShowWindow(SW_HIDE);
		step1.ShowWindow(SW_SHOW);
		step2.ShowWindow(SW_HIDE);
		step3.ShowWindow(SW_HIDE);
		break;
	case 2:
		g_Maindlg->ShowWindow(SW_HIDE);
		step1.ShowWindow(SW_HIDE);
		step2.ShowWindow(SW_SHOW);
		step3.ShowWindow(SW_HIDE);	
		break;
	case 3:
		g_Maindlg->ShowWindow(SW_HIDE);
		step1.ShowWindow(SW_HIDE);
		step2.ShowWindow(SW_HIDE);
		step3.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

// SimpleInputBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "SimpleInputBox.h"


// CSimpleInputBox �Ի���

IMPLEMENT_DYNAMIC(CSimpleInputBox, CDialog)

CSimpleInputBox::CSimpleInputBox(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleInputBox::IDD, pParent)
	, m_strInput(_T(""))
{
	m_strCaption=_T("����Ի���");
}

CSimpleInputBox::~CSimpleInputBox()
{
}

void CSimpleInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_CBString(pDX, IDC_COMBO1, m_strInput);
}


BEGIN_MESSAGE_MAP(CSimpleInputBox, CDialog)
END_MESSAGE_MAP()


// CSimpleInputBox ��Ϣ�������

BOOL CSimpleInputBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(m_strCaption);

	for(int i = 0; i< m_ComboString.size(); i++)
	{
		m_ComboBox.AddString(m_ComboString[i].c_str());
	}

	/*m_ComboBox.AddString("��Ȩ����");
	m_ComboBox.AddString("��Ʊ�����ƻ����ݰ���");
	m_ComboBox.AddString("ͣ�ƹ���");
	m_ComboBox.AddString("ͣ�ƽ�չ����");
	m_ComboBox.AddString("���ƹ���");
	m_ComboBox.AddString("��ƱԤ��");
	m_ComboBox.AddString("�޶���");*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

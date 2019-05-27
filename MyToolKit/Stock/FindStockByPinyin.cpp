// FindStockByPinyin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Stock.h"
#include "MainFrm.h"

#include "FindStockByPinyin.h"


// CFindStockByPinyin �Ի���

IMPLEMENT_DYNAMIC(CFindStockByPinyin, CDialog)

CFindStockByPinyin::CFindStockByPinyin(CWnd* pParent /*=NULL*/)
	: CDialog(CFindStockByPinyin::IDD, pParent)
	, m_strPinyin(_T(""))
{

}

CFindStockByPinyin::~CFindStockByPinyin()
{
}

void CFindStockByPinyin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_CBString(pDX, IDC_COMBO1, m_strPinyin);
	DDV_MaxChars(pDX, m_strPinyin, 32);
}


BEGIN_MESSAGE_MAP(CFindStockByPinyin, CDialog)
END_MESSAGE_MAP()


// CFindStockByPinyin ��Ϣ�������

BOOL CFindStockByPinyin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if(m_strPinyin.IsEmpty()==FALSE)
	{
		int nIndex = CB_ERR;
		m_Combo1.ResetContent();

		CStockApp * pApp = (CStockApp *)AfxGetApp();
		// ���˴�ҵ��
		for(int i=0; i< pApp->m_CEntrepreneurship.m_nRowNum; i++)
		{
			if(pApp->m_CEntrepreneurship.m_vec_cninfo_pinyin[i][0] == m_strPinyin[0])
			{
				CString str;
				str.Format("%-4s %06d %s",pApp->m_CEntrepreneurship.m_vec_cninfo_pinyin[i].c_str(), \
					pApp->m_CEntrepreneurship.m_vec_a_code[i], \
					pApp->m_CEntrepreneurship.m_vec_abbreviation[i].c_str());
				m_Combo1.AddString(str);
			}
		}

		// ������С��
		for(int i=0; i< pApp->m_CSmallMidEnterprise.m_nRowNum; i++)
		{
			if(pApp->m_CSmallMidEnterprise.m_vec_cninfo_pinyin[i][0] == m_strPinyin[0])
			{
				CString str;
				str.Format("%-4s %06d %s",pApp->m_CSmallMidEnterprise.m_vec_cninfo_pinyin[i].c_str(), \
					pApp->m_CSmallMidEnterprise.m_vec_a_code[i], \
					pApp->m_CSmallMidEnterprise.m_vec_abbreviation[i].c_str());
				m_Combo1.AddString(str);
			}
		}

		// ��������A��
		for(int i=0; i< pApp->m_CShenzhenAshares.m_nRowNum; i++)
		{
			if(pApp->m_CShenzhenAshares.m_vec_cninfo_pinyin[i][0] == m_strPinyin[0])
			{
				CString str;
				str.Format("%-4s %06d %s",pApp->m_CShenzhenAshares.m_vec_cninfo_pinyin[i].c_str(), \
					pApp->m_CShenzhenAshares.m_vec_a_code[i], \
					pApp->m_CShenzhenAshares.m_vec_abbreviation[i].c_str());
				m_Combo1.AddString(str);
			}
		}

		// �����Ϻ�A��
		for(int i=0; i< pApp->m_CShanghaiStock.m_nRowNum; i++)
		{
			if(pApp->m_CShanghaiStock.m_vec_cninfo_pinyin[i][0] == m_strPinyin[0])
			{
				CString str;
				str.Format("%-4s %06d %s",pApp->m_CShanghaiStock.m_vec_cninfo_pinyin[i].c_str(), \
					pApp->m_CShanghaiStock.m_vec_a_code[i], \
					pApp->m_CShanghaiStock.m_vec_abbreviation[i].c_str());
				m_Combo1.AddString(str);
			}
		}

		// ģ����̣��� m_Combo1 ����������ղŵİ�����ĸ
		m_Combo1.PostMessage(WM_CHAR,  m_strPinyin[0]);
	}

	m_Combo1.SetEditTooltip(TRUE);
	m_Combo1.SetListTooltip(TRUE);

	m_Combo1.SetMode(CComboBoxExt::MODE_AUTOCOMPLETE);
	m_Combo1.SetFocus();	// ������뽹��

	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CFindStockByPinyin::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	UpdateData(TRUE);


	CDialog::OnOK();
}

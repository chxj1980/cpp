#pragma once
#include "afxcmn.h"
#include "../GridCtrl_src/GridCtrl.h"
#include "../GridCtrl_src/TreeGridCtrl.h"


// CPDFStructureDlg �Ի���

class CPDFStructureDlg : public CDialog
{
	DECLARE_DYNAMIC(CPDFStructureDlg)

public:
	CPDFStructureDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPDFStructureDlg();

// �Ի�������
	enum { IDD = IDD_PDF_STRUCTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	CTreeGridCtrl m_Grid;
	string		m_announcementId;

	virtual BOOL OnInitDialog();
};

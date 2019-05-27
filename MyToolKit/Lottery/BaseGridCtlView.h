#pragma once


#include "BaseMessageView.h"
#include "./GridCtrl_src/GridCtrl.h"

#include "./NewCellTypes/GridURLCell.h"
#include "./NewCellTypes/GridCellCombo.h"
#include "./NewCellTypes/GridCellCheck.h"
#include "./NewCellTypes/GridCellNumeric.h"
#include "./NewCellTypes/GridCellDateTime.h"


// CBaseGridCtlView ��ͼ

class CBaseGridCtlView : public CBaseMessageView
{
	DECLARE_DYNCREATE(CBaseGridCtlView)

protected:
	CBaseGridCtlView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBaseGridCtlView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

protected:
	CGridCtrl* m_pGridCtrl;

	CStatic *	m_pStaticShowPage;
	CButtonST * m_pButtonFirst;
	CButtonST * m_pButtonPageUp;
	CButtonST * m_pButtonPageDown;
	CButtonST * m_pButtonLast;
	CButtonST * m_pButtonSaveAsExcel;
	CStatic *	m_pStaticTip;

	CFont		m_editFont; 

	int		m_nPageNo;
	int		m_nMaxPage;
	bool	m_bPagination;		//	�Ƿ���ʾ��ҳ��

	//	������ͼ��ʾ�� ������Χ
	int		m_start_number;
	int		m_end_number;
		
	vector<LotteryNumber>	m_vec_lottery_number;		//	�������ݵĲ�ѯ���
	int		m_accumulative[64];		//	�ۼƴ���
	int		m_interval[64];			//	�������
	LotteryNumber	m_selected_lottery_number;

protected:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetGridCell(int row, int col, bool isHeader, string text);
	void SetGridCell(int row, int col, bool isHeader,  string text, COLORREF crFgClr);
	virtual void OnPageUpdate(){};
	void TableAddToSelfSelect();

	void RefreshStatusBar();
	void Startup();

	afx_msg void OnBtnFirst();
	afx_msg void OnBtnPageup();
	afx_msg void OnBtnPagedown();
	afx_msg void OnBtnLast();

	afx_msg void OnBtnSaveAsExcel();

	virtual void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);

	virtual void PostGridDblClick(int nRow)
	{
		
	}

	static int CALLBACK pfnCellCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

};



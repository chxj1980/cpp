#pragma once
#include "afxwin.h"
//#include "e:\workspace_c3\mytoolkit\stock\gridctrl_src\gridctrl.h"
//#include "e:\workspace_c3\mytoolkit\stock\chartctrl\chartctrl.h"


#include "../GridCtrl_src/GridCtrl.h"
#include "ChartCtrl.h"
#include "GraphCtrl.h"



// CBaseMessageFormView ������ͼ

class CBaseMessageFormView : public CFormView
{
	DECLARE_DYNCREATE(CBaseMessageFormView)

protected:
public:
	CBaseMessageFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBaseMessageFormView();

public:
	enum { IDD = IDD_BASEMESSAGEFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CBaseMessageControl	m_MessageCtrl;
public:
	CButton m_btn1;
	
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridClick(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnGridDblClick1(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridClick1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnAddNodeToGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddEdgeToGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditNodeInGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelNodeInGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMoveNodeInGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEditEdgeInGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDelEdgeInGraph(NMHDR *pNMHDR, LRESULT *pResult);

	virtual void PostGridDblClick(int gridId, int nRow)
	{

	}

	virtual void PostGridClick(int gridId, int nRow, int nCol) {

	}


	virtual void PostAddNodeToGraph(int x, int y) {

	}

	virtual void PostAddEdgeToGraph(int from, int to) {

	}

	virtual void PostMoveNodeInGraph(int idx, int x, int y) {

	}

	virtual void PostEditNodeInGraph(int idx) {

	}

	virtual void PostEditEdgeInGraph(int idx) {

	}

	virtual void PostDelNodeInGraph(int idx) {

	}

	virtual void PostDelEdgeInGraph(int idx) {

	}
	

	void ReLayout();
	CGridCtrl m_Grid;
	CGridCtrl m_Grid1;
	CGraphCtrl m_Graph;

	enum DisplayModes
	{
		Grid_Grid,
		Grid,
		Dijkstra,
		Grid_Dijkstra,
		None
	};

	DisplayModes m_display_mode;
	int m_upper_percent;	//	�ϱ��ռ��
	int	m_down_percent;		//	�±��ռ��

public:

	virtual void RedrawDmGraph()
	{
		int w = 6;
	} ;

	virtual void RedrawChart(CCalculateTask * cse){};

	afx_msg LRESULT OnUserXmlWParam(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserLogWParam_1(WPARAM wParam, LPARAM lParam);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);

	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	virtual void PostFocusChanged(){};
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};



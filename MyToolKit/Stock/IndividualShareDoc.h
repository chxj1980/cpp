#pragma once

// CIndividualShareDoc �ĵ�

class CIndividualShareDoc : public CDocument
{
	DECLARE_DYNCREATE(CIndividualShareDoc)

public:
	CIndividualShareDoc();
	CIndividualShareDoc(string code, int command_code = 0, int is_stock = 0);
	virtual ~CIndividualShareDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()

public:
	string m_nCode;
	int m_nCommandCode;
	int m_nIs_Stock;

	//	���Һ󣬼���õ��Ĳ�ѯĿ�꼯��

	vector<string>		m_vec_request_code;		
	vector<int>		m_vec_request_is_stock;

	/* ����������ͼ�ȣ����Գ�ʼʱ�������Ĳ˵�����Զ�ִ�� */
	vector<int>	m_vecCommandCode;	

	vector<string>	m_vec_zb_code;
	vector<string>	m_vec_reg_code;
	
	string m_strInput;

	COleDateTime		m_StartDate;
	COleDateTime		m_EndDate;

	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};

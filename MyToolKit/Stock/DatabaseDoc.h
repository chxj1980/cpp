#pragma once

// CDatabaseDoc �ĵ�

class CDatabaseDoc : public CDocument
{
	DECLARE_DYNCREATE(CDatabaseDoc)

public:
	CDatabaseDoc();
	virtual ~CDatabaseDoc();
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
	vector<string>	m_log_vector;
	afx_msg void OnBnClickedMysqlTest();
	afx_msg void OnBnClickedStockDbSetup();
	afx_msg void OnBnClickedCurlTest();
};
